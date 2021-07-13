#ifndef RECIPE_HPP
#define RECIPE_HPP

#include <string>
#include <vector>
#include <utility>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <cmath>

class User;

typedef std::pair<User*, double> Rate;

class Recipe
{
public:
	struct InterfaceRecipe
	{
		std::string name;
		int id = -1;
		bool isVegetarian = false;
		std::vector<std::string> ingredients;
		int minutesToReady = 0;
		std::vector<std::string> tags;
		std::string imageAddress;
		double rating = 0;
		double usersRating = 0;
		static InterfaceRecipe getRecipe(const std::string& name__, int id__, bool isVegetarian__, const std::vector<std::string>& ingredients__,
			int minutesToReady__, const std::vector<std::string>& tags__, const std::string& imageAddress__, double rating__, double usersRating__)
		{
			InterfaceRecipe rec;
			rec.name = name__;
			rec.id = id__;
			rec.isVegetarian = isVegetarian__;
			rec.ingredients = ingredients__;
			rec.minutesToReady = minutesToReady__;
			rec.tags = tags__;
			rec.imageAddress = imageAddress__;
			rec.rating = rating__;
			rec.usersRating = usersRating__;
			return rec;
		}
	};
	Recipe(std::string& name, int id, bool isVegetarian, std::vector<std::string>& ingredients, int minutesToReady,
		std::vector<std::string>& tags, std::string& imageAddress);
	void rate(User* user, double rate);
	double getRating() const { return rating_; }
	bool isVegetarian() const { return isVegetarian_; }
	bool checkIdCredential(int& id) const { return id == id_; }
	int minutesToReady() const { return minutesToReady_; }
	bool hasTag(const std::string& tag) const;
	std::string getName() const { return name_; }
	InterfaceRecipe getInterfaceRecipe(User* user = nullptr);
private:
	std::string name_;
	int id_;
	bool isVegetarian_;
	std::vector<std::string> ingredients_;
	int minutesToReady_;
	std::vector<std::string> tags_;
	std::string imageAddress_;
	double rating_ = 0;
	std::vector<Rate> rates_;
	double roundedUpRate() const;
};

#endif
