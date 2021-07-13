#include "include/Filter.hpp"

TagFilter::TagFilter(std::string& tag) : tag_(tag) { }

ReadyTimeFilter::ReadyTimeFilter(int minMinutes, int maxMinutes) : minMinutes_(minMinutes), maxMinutes_(maxMinutes) { }

RatingFilter::RatingFilter(double minRating, double maxRating) : minRating_(minRating), maxRating_(maxRating) { }

std::vector<Recipe*> TagFilter::meetFilter(std::vector<Recipe*>& totalRecipes) const
{
	std::vector<Recipe*> filteredRecipes;
	for (Recipe*& recipe : totalRecipes)
		if (recipe->hasTag(tag_))
			filteredRecipes.push_back(recipe);
	return filteredRecipes;
}

std::vector<Recipe*> VegetarianFilter::meetFilter(std::vector<Recipe*>& totalRecipes) const
{
	std::vector<Recipe*> filteredRecipes;
	for (Recipe*& recipe : totalRecipes)
		if (recipe->isVegetarian())
			filteredRecipes.push_back(recipe);
	return filteredRecipes;
}

std::vector<Recipe*> ReadyTimeFilter::meetFilter(std::vector<Recipe*>& totalRecipes) const
{
	std::vector<Recipe*> filteredRecipes;
	for (Recipe*& recipe : totalRecipes)
		if (recipe->minutesToReady() <= maxMinutes_ && recipe->minutesToReady() >= minMinutes_)
			filteredRecipes.push_back(recipe);
	return filteredRecipes;
}

std::vector<Recipe*> RatingFilter::meetFilter(std::vector<Recipe*>& totalRecipes) const
{
	std::vector<Recipe*> filteredRecipes;
	for (Recipe*& recipe : totalRecipes)
		if (recipe->getRating() <= maxRating_ && recipe->getRating() >= minRating_)
			filteredRecipes.push_back(recipe);
	return filteredRecipes;
}
