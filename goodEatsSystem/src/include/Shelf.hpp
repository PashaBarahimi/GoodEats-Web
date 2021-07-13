#ifndef SHELF_HPP
#define SHELF_HPP

#include "Recipe.hpp"

#include <vector>
#include <string>
#include <sstream>

class Shelf
{
public:
	struct InterfaceShelf
	{
		std::string name;
		int id = -1;
		std::vector<Recipe::InterfaceRecipe> recipes;
		static InterfaceShelf getShelf(const std::string& name__, int id__, const std::vector<Recipe::InterfaceRecipe>& recipes__)
		{
			InterfaceShelf shelf;
			shelf.name = name__;
			shelf.id = id__;
			shelf.recipes = recipes__;
			return shelf;
		}
	};
	Shelf(std::string& name, int id);
	bool addRecipe(Recipe* recipe);
	bool removeRecipe(Recipe* recipe);
	bool checkIdCredential(int& id) const { return id == id_; }
	void deleteAllRecipes() { recipes_.clear(); }
	InterfaceShelf getInterfaceShelf();
private:
	std::string name_;
	int id_;
	std::vector<Recipe*> recipes_;
};

#endif
