#include "include/Recipe.hpp"
#include "include/Chef.hpp"
#include "include/User.hpp"
#include "include/AlgorithmSideFunctions.hpp"

Recipe::Recipe(std::string& name, int id, bool isVegetarian, std::vector<std::string>& ingredients,
	int minutesToReady, std::vector<std::string>& tags, std::string& imageAddress) :
	name_(std::move(name)), id_(id), isVegetarian_(isVegetarian), ingredients_(ingredients),
	minutesToReady_(minutesToReady), tags_(std::move(tags)), imageAddress_(std::move(imageAddress)) { }

bool Recipe::hasTag(const std::string& tag) const
{
	for (const std::string& tagItem : tags_)
		if (tag == tagItem)
			return true;
	return false;
}

double Recipe::roundedUpRate() const
{
	double tenXRate = 10 * rating_;
	tenXRate = ceil(tenXRate);
	return tenXRate / 10;
}

void Recipe::rate(User* user, double rate)
{
	const auto itr = std::find_if(rates_.begin(), rates_.end(), [user](Rate rating)
		{ return rating.first == user; });
	double rateSum = rating_ * rates_.size();
	if (itr != rates_.end())
	{
		rateSum -= (*itr).second;
		rateSum += rate;
		rating_ = rateSum / rates_.size();
		(*itr).second = rate;
	}
	else
	{
		rateSum += rate;
		rating_ = rateSum / static_cast<double>(rates_.size() + 1);
		rates_.emplace_back(user, rate);
	}
}

Recipe::InterfaceRecipe Recipe::getInterfaceRecipe(User* user)
{
	double usersRating = 0;
	const auto itr = std::find_if(rates_.begin(), rates_.end(), [user](Rate rating)
		{ return rating.first == user; });
	if (itr != rates_.end())
		usersRating = (*itr).second;
	return InterfaceRecipe::getRecipe(name_, id_, isVegetarian_, ingredients_, minutesToReady_, tags_, imageAddress_, roundedUpRate(), usersRating);
}
