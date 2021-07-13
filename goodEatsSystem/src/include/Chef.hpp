#ifndef CHEF_HPP
#define CHEF_HPP

#include "Recipe.hpp"

#include <vector>
#include <string>
#include <sstream>
#include <iomanip>

class Chef
{
public:
	Chef(const std::string& username, const std::string& password);
	std::vector<Recipe::InterfaceRecipe> getInterfaceRecipes() const;
	bool doesRecipeExist(Recipe* recipe) const;
	bool checkNameCredential(std::string& username) const { return username == username_; }
	bool isPasswordCorrect(const std::string& password) const { return password == password_; }
	void addRecipe(Recipe* recipe);
	void removeRecipe(Recipe* recipe);
	std::string getName() const { return username_; }
private:
	std::string username_;
	std::string password_;
	std::vector <Recipe*> recipes_;
	double getRatings() const;
};

#endif
