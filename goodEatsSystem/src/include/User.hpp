#ifndef USER_HPP
#define USER_HPP

#include "Recipe.hpp"
#include "Filter.hpp"
#include "Shelf.hpp"

#include <string>
#include <vector>
#include <sstream>
#include <array>

class User
{
public:
	struct FilterStatus
	{
		std::string tag;
		bool isVegetarian = false;
		int minTime = 0;
		int maxTime = 200;
		double minRating = 0;
		double maxRating = 5;
		void reset() noexcept;
	};
	User(const std::string& username, const std::string& password);
	~User();
	bool checkNameCredential(std::string& username) const { return username == username_; }
	bool isPasswordCorrect(const std::string& password) const { return password == password_; }
	bool doesShelfExist(Shelf* shelf);
	std::vector<Shelf::InterfaceShelf> getInterfaceShelves();
	std::string getName() const { return username_; }
	void addShelf(Shelf* shelf);
	void logout();
	std::array<Filter*, 4>  getFilters() const { return filters_; }
	void makeTagFilter(std::string& tag);
	void makeVegetarianFilter();
	void makeTimeFilter(int min, int max);
	void makeRatingFilter(double min, double max);
	void deleteFilter(int index = -1) noexcept;
	FilterStatus getFilterStatus() const { return filterStatus_; }
private:
	std::string username_;
	std::string password_;
	FilterStatus filterStatus_;
	std::array<Filter*, 4> filters_ = { nullptr,nullptr,nullptr,nullptr };
	std::vector<Shelf*> shelves_;
};

#endif
