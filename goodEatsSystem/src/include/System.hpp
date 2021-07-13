#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include "Chef.hpp"
#include "User.hpp"
#include "Filter.hpp"
#include "Recipe.hpp"
#include "Shelf.hpp"
#include "GoodEatsErrors.hpp"
#include "AlgorithmSideFunctions.hpp"

#include <string>
#include <vector>
#include <sstream>
#include <unordered_map>

class System
{
public:
	System() { srand(static_cast<unsigned>(time(nullptr))); }
	~System();
	enum class MemberType
	{
		User,
		Chef,
		NA
	};
	std::string signUp(std::string& username, std::string& password, MemberType type);
	std::string login(std::string& username, std::string& password);
	MemberType checkSessionId(std::string id);
	void logout(std::string sessionId);
	std::vector<Recipe::InterfaceRecipe> getRecipesList() const;
	std::vector<Recipe::InterfaceRecipe> getAllRecipesForShelfEdit(int shelfId) const;
	Recipe::InterfaceRecipe getRecipeInfo(int recipeId) const;
	void deleteAllShelfRecipes(int shelfId);
	void rate(int recipeId, double score);
	void makeShelf(std::string& name);
	std::vector<Shelf::InterfaceShelf> getUsersShelves() const;
	void addRecipeToShelf(int shelfId, int recipeId);
	Shelf::InterfaceShelf getShelf(int shelfId) const;
	void deleteRecipeFromShelf(int shelfId, int recipeId);
	void makeRecipe(std::string& title, std::vector<std::string>& ingredients, bool isVegetarian, int minutesToReady,
		std::vector<std::string>& tags, std::string& imageAddress);
	void deleteRecipe(int recipeId);
	std::vector<Recipe::InterfaceRecipe> getChefsRecipes() const;
	void makeTagFilter(std::string& tag);
	void makeVegetarianFilter();
	void makeTimeFilter(int min, int max);
	void makeRatingFilter(double min, double max);
	void deleteFilter();
	User::FilterStatus getFilterStatus() const;
private:
	std::unordered_map<std::string, User*> userIds_;
	std::unordered_map<std::string, Chef*> chefIds_;
	MemberType loggedInMember_ = MemberType::NA;
	User* user_ = nullptr;
	Chef* chef_ = nullptr;
	int recipesCount_ = 0;
	std::vector<Chef*> chefs_;
	std::vector<User*> users_;
	std::vector<Recipe*> recipes_;
	std::vector<Recipe*> deletedRecipes_;
	std::vector<Shelf*> shelves_;
	template<typename T, typename U>
	T* findInstance(U& argument, const std::vector<T*>& instances, bool (T::* ptr)(U& arg) const) const;
	void checkMemberType(MemberType member) const;
	static std::string randString(int length = 10);
	std::string sessionIdGenerator();
};

#endif
