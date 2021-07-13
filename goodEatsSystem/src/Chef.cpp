#include "include/Chef.hpp"
#include "include/AlgorithmSideFunctions.hpp"

Chef::Chef(const std::string& username, const std::string& password) : username_(username), password_(password) { }

void Chef::addRecipe(Recipe* recipe)
{
	recipes_.insert(std::upper_bound(recipes_.begin(), recipes_.end(), recipe, compareByName<Recipe*>), recipe);
}

void Chef::removeRecipe(Recipe* recipe)
{
	for (unsigned i = 0; i < recipes_.size(); i++)
		if (recipe == recipes_[i])
		{
			recipes_.erase(recipes_.begin() + i);
			return;
		}
}

bool Chef::doesRecipeExist(Recipe* recipe) const
{
	for (Recipe* item : recipes_)
		if (recipe == item)
			return true;
	return false;
}

double Chef::getRatings() const
{
	double sum = 0;
	int counter = 0;
	for (Recipe* recipe : recipes_)
		if (static_cast<int>(recipe->getRating()) != 0)
		{
			sum += recipe->getRating();
			counter++;
		}
	if (counter == 0)
		return 0;
	sum /= counter;
	double tenXRate = 10 * sum;
	tenXRate = ceil(tenXRate);
	return tenXRate / 10;
}

std::vector<Recipe::InterfaceRecipe> Chef::getInterfaceRecipes() const
{
	std::vector<Recipe::InterfaceRecipe> recipes;
	for (Recipe* rec : recipes_)
		recipes.push_back(rec->getInterfaceRecipe());
	return recipes;
}
