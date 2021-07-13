#include "include/Shelf.hpp"
#include "include/AlgorithmSideFunctions.hpp"

Shelf::Shelf(std::string& name, int id) : name_(std::move(name)), id_(id) { }

bool Shelf::addRecipe(Recipe* recipe)
{
	const auto itr = std::find(recipes_.begin(), recipes_.end(), recipe);
	if (itr != recipes_.end())
		return false;
	recipes_.insert(std::upper_bound(recipes_.begin(), recipes_.end(), recipe, compareByName<Recipe*>), recipe);
	return true;
}

bool Shelf::removeRecipe(Recipe* recipe)
{
	const auto itr = std::find(recipes_.begin(), recipes_.end(), recipe);
	if (itr == recipes_.end())
		return false;
	recipes_.erase(itr);
	return true;
}

Shelf::InterfaceShelf Shelf::getInterfaceShelf()
{
	std::vector<Recipe::InterfaceRecipe> recipes;
	for (Recipe* rec : recipes_)
		recipes.push_back(rec->getInterfaceRecipe());
	return InterfaceShelf::getShelf(name_, id_, recipes);
}
