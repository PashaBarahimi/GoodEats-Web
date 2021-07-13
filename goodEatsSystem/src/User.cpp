#include "include/User.hpp"
#include "include/GoodEatsErrors.hpp"

User::User(const std::string& username, const std::string& password) : username_(username), password_(password) { }

User::~User()
{
	deleteFilter();
}

void User::logout()
{
	deleteFilter();
}

void User::addShelf(Shelf* shelf)
{
	shelves_.push_back(shelf);
}

bool User::doesShelfExist(Shelf* shelf)
{
	const auto itr = std::find(shelves_.begin(), shelves_.end(), shelf);
	return itr != shelves_.end();
}

std::vector<Shelf::InterfaceShelf> User::getInterfaceShelves()
{
	std::vector<Shelf::InterfaceShelf> shelves;
	for (Shelf* shelf : shelves_)
		shelves.push_back(shelf->getInterfaceShelf());
	return shelves;
}

void User::makeTagFilter(std::string& tag)
{
	if (tag.empty())
		return;
	deleteFilter(static_cast<int>(Filter::FilterIndex::TagFilter));
	filters_[static_cast<int>(Filter::FilterIndex::TagFilter)] = new TagFilter(tag);
	filterStatus_.tag = tag;
}

void User::makeVegetarianFilter()
{
	deleteFilter(static_cast<int>(Filter::FilterIndex::VegetarianFilter));
	filters_[static_cast<int>(Filter::FilterIndex::VegetarianFilter)] = new VegetarianFilter;
	filterStatus_.isVegetarian = true;
}

void User::makeTimeFilter(int min, int max)
{
	if (min >= max)
		throw BadRequest("Wrong Values Entered!");
	deleteFilter(static_cast<int>(Filter::FilterIndex::ReadyTimeFilter));
	filters_[static_cast<int>(Filter::FilterIndex::ReadyTimeFilter)] = new ReadyTimeFilter(min, max);
	filterStatus_.minTime = min;
	filterStatus_.maxTime = max;
}

void User::makeRatingFilter(double min, double max)
{
	if (min >= max || min < 0 || max > 5)
		throw BadRequest("Wrong Values Entered!");
	deleteFilter(static_cast<int>(Filter::FilterIndex::RatingFilter));
	filters_[static_cast<int>(Filter::FilterIndex::RatingFilter)] = new RatingFilter(min, max);
	filterStatus_.minRating = min;
	filterStatus_.maxRating = max;
}

void User::deleteFilter(int index) noexcept
{
	if (index == -1)
	{
		for (Filter*& filter : filters_)
			if (filter != nullptr)
			{
				delete filter;
				filter = nullptr;
			}
		filterStatus_.reset();
	}
	else if (filters_[index] != nullptr)
	{
		delete filters_[index];
		filters_[index] = nullptr;
	}
}

void User::FilterStatus::reset() noexcept
{
	tag.clear();
	isVegetarian = false;
	minTime = 0;
	maxTime = 200;
	minRating = 0;
	maxRating = 5;
}
