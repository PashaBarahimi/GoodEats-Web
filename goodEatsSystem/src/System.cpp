#include "include/System.hpp"

System::~System()
{
	for (Chef* chef : chefs_)
		delete chef;
	for (User* user : users_)
		delete user;
	for (Shelf* shelf : shelves_)
		delete shelf;
	for (Recipe* recipe : recipes_)
		delete recipe;
	for (Recipe* recipe : deletedRecipes_)
		delete recipe;
}

std::string System::randString(int length)
{
	std::string str(length, '0');
	const char charset[] =
		"0123456789"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz";
	std::generate_n(str.begin(), length, [charset]() -> char {return charset[rand() % (sizeof(charset) - 1)]; });
	return str;
}

std::string System::sessionIdGenerator()
{
	while (true)
	{
		const std::string id = randString(9);
		const auto uItr = userIds_.find("u" + id);
		if (uItr != userIds_.end())
			continue;
		const auto cItr = chefIds_.find("c" + id);
		if (cItr != chefIds_.end())
			continue;
		return id;
	}
}

std::string System::signUp(std::string& username, std::string& password, MemberType type)
{
	checkMemberType(MemberType::NA);
	if (findInstance(username, users_, &User::checkNameCredential) != nullptr ||
		findInstance(username, chefs_, &Chef::checkNameCredential) != nullptr)
		throw BadRequest("Username Already Exists!");
	User* user;
	Chef* chef;
	const std::string sessionId = sessionIdGenerator();
	switch (type)
	{
	case MemberType::User:
		user = new User(username, password);
		userIds_["u" + sessionId] = user;
		users_.insert(std::upper_bound(users_.begin(), users_.end(), user, compareByName<User*>), user);
		return "u" + sessionId;
	case MemberType::Chef:
		chef = new Chef(username, password);
		chefIds_["c" + sessionId] = chef;
		chefs_.insert(std::upper_bound(chefs_.begin(), chefs_.end(), chef, compareByName<Chef*>), chef);
		return "c" + sessionId;
	case MemberType::NA:
		throw BadRequest("Wrong Member Type!");
	}
	return std::string();
}

std::string System::login(std::string& username, std::string& password)
{
	checkMemberType(MemberType::NA);
	const std::string sessionId = sessionIdGenerator();
	User* user = findInstance(username, users_, &User::checkNameCredential);
	if (user != nullptr)
	{
		if (user->isPasswordCorrect(password))
		{
			userIds_["u" + sessionId] = user;
			return "u" + sessionId;
		}
		throw BadRequest("Wrong Password!");
	}
	Chef* chef = findInstance(username, chefs_, &Chef::checkNameCredential);
	if (chef == nullptr)
		throw BadRequest("Username Doesn't Exist!");
	if (chef->isPasswordCorrect(password))
	{
		chefIds_["c" + sessionId] = chef;
		return "c" + sessionId;
	}
	throw BadRequest("Wrong Password!");
}

System::MemberType System::checkSessionId(std::string id)
{
	if (id.empty())
	{
		loggedInMember_ = MemberType::NA;
		return MemberType::NA;
	}
	const char identifier = id[0];
	if (identifier == 'u')
	{
		const auto itr = userIds_.find(id);
		if (itr == userIds_.end())
			return MemberType::NA;
		user_ = (*itr).second;
		chef_ = nullptr;
		loggedInMember_ = MemberType::User;
		return MemberType::User;
	}
	if (identifier == 'c')
	{
		const auto itr = chefIds_.find(id);
		if (itr == chefIds_.end())
			return MemberType::NA;
		user_ = nullptr;
		chef_ = (*itr).second;
		loggedInMember_ = MemberType::Chef;
		return MemberType::Chef;
	}
	loggedInMember_ = MemberType::NA;
	return MemberType::NA;
}

void System::logout(std::string sessionId)
{
	if (loggedInMember_ == MemberType::NA)
		throw PermissionDenied("Login First!");
	if (loggedInMember_ == MemberType::User)
	{
		user_->logout();
		const auto itr = userIds_.find(sessionId);
		if (itr != userIds_.end())
			userIds_.erase(itr);
	}
	else if (loggedInMember_ == MemberType::Chef)
	{
		const auto itr = chefIds_.find(sessionId);
		if (itr != chefIds_.end())
			chefIds_.erase(itr);
	}
}

std::vector<Recipe::InterfaceRecipe> System::getRecipesList() const
{
	checkMemberType(MemberType::User);
	std::vector<Recipe::InterfaceRecipe> recipes;
	auto mainRecipes = recipes_;
	auto filters = user_->getFilters();
	for (auto* filter : filters)
		if (filter != nullptr)
			mainRecipes = filter->meetFilter(mainRecipes);
	for (Recipe* rec : mainRecipes)
		recipes.push_back(rec->getInterfaceRecipe());
	return recipes;
}

std::vector<Recipe::InterfaceRecipe> System::getAllRecipesForShelfEdit(int shelfId) const
{
	checkMemberType(MemberType::User);
	std::vector<Recipe::InterfaceRecipe> recipes;
	for (auto* rec : recipes_)
		recipes.push_back(rec->getInterfaceRecipe());
	Shelf* shelf = findInstance(shelfId, shelves_, &Shelf::checkIdCredential);
	if (shelf == nullptr)
		throw NotFoundError("Shelf Not Found!");
	std::vector<Recipe::InterfaceRecipe> shelfRecipes = shelf->getInterfaceShelf().recipes;
	std::vector<Recipe::InterfaceRecipe> deletedRecipes;
	for (auto* rec : deletedRecipes_)
		deletedRecipes.push_back(rec->getInterfaceRecipe());
	for (const auto& rec : shelfRecipes)
	{
		const auto itr = std::find_if(deletedRecipes.begin(), deletedRecipes.end(), [&rec](Recipe::InterfaceRecipe& recipe) ->bool
			{return rec.id == recipe.id; });
		if (itr != deletedRecipes.end())
			recipes.insert(std::upper_bound(recipes.begin(), recipes.end(), rec,
				[](const Recipe::InterfaceRecipe& first, const Recipe::InterfaceRecipe& second) -> bool {return first.name < second.name; }), rec);
	}
	return recipes;
}

Recipe::InterfaceRecipe System::getRecipeInfo(int recipeId) const
{
	checkMemberType(MemberType::User);
	Recipe* recipe = findInstance(recipeId, recipes_, &Recipe::checkIdCredential);
	if (recipe == nullptr)
		throw NotFoundError("Recipe Not Found!");
	return recipe->getInterfaceRecipe(user_);
}

void System::deleteAllShelfRecipes(int shelfId)
{
	checkMemberType(MemberType::User);
	Shelf* shelf = findInstance(shelfId, shelves_, &Shelf::checkIdCredential);
	if (shelf == nullptr)
		throw NotFoundError("Shelf Not Found!");
	shelf->deleteAllRecipes();
}

void System::rate(int recipeId, double score)
{
	checkMemberType(MemberType::User);
	Recipe* recipe = findInstance(recipeId, recipes_, &Recipe::checkIdCredential);
	if (recipe == nullptr)
		throw NotFoundError("Recipe Not Found!");
	if (score < 0 || score > 5)
		throw BadRequest("Wrong Score!");
	recipe->rate(user_, score);
}

void System::makeShelf(std::string& name)
{
	checkMemberType(MemberType::User);
	Shelf* shelf = new Shelf(name, static_cast<int>(shelves_.size() + 1));
	shelves_.push_back(shelf);
	user_->addShelf(shelf);
}

std::vector<Shelf::InterfaceShelf> System::getUsersShelves() const
{
	checkMemberType(MemberType::User);
	return user_->getInterfaceShelves();
}

void System::addRecipeToShelf(int shelfId, int recipeId)
{
	checkMemberType(MemberType::User);
	Shelf* shelf = findInstance(shelfId, shelves_, &Shelf::checkIdCredential);
	if (shelf == nullptr)
		throw PermissionDenied("Shelf Not Found!"); // Either Not Found or Bad Request or Permission Denied
	if (!user_->doesShelfExist(shelf))
		throw PermissionDenied("This Shelf Is Not Yours!");
	Recipe* recipe = findInstance(recipeId, recipes_, &Recipe::checkIdCredential);
	if (recipe == nullptr)
	{
		recipe = findInstance(recipeId, deletedRecipes_, &Recipe::checkIdCredential);
		if (recipe == nullptr)
			throw NotFoundError("Recipe Not Found!"); // Either Not Found or Bad Request
	}
	if (!shelf->addRecipe(recipe))
		throw BadRequest("Recipe Already Exists!");
}

Shelf::InterfaceShelf System::getShelf(int shelfId) const
{
	checkMemberType(MemberType::User);
	Shelf* shelf = findInstance(shelfId, shelves_, &Shelf::checkIdCredential);
	if (shelf == nullptr)
		throw NotFoundError("Shelf Not Found!");
	return shelf->getInterfaceShelf();
}

void System::deleteRecipeFromShelf(int shelfId, int recipeId)
{
	checkMemberType(MemberType::User);
	Shelf* shelf = findInstance(shelfId, shelves_, &Shelf::checkIdCredential);
	if (shelf == nullptr)
		throw PermissionDenied("Shelf Doesn't Exist!"); // Either Permission Denied or Not Found
	if (!user_->doesShelfExist(shelf))
		throw PermissionDenied("This Shelf Is Not Yours!");
	Recipe* recipe = findInstance(recipeId, recipes_, &Recipe::checkIdCredential);
	if (recipe == nullptr)
		throw BadRequest("Recipe Doesn't Exist!"); // Either Bad Request or Not Found
	if (!shelf->removeRecipe(recipe))
		throw BadRequest("Recipe Is Not In The Shelf!");
}

void System::makeRecipe(std::string& title, std::vector<std::string>& ingredients, bool isVegetarian, int minutesToReady,
	std::vector<std::string>& tags, std::string& imageAddress)
{
	checkMemberType(MemberType::Chef);
	Recipe* recipe = new Recipe(title, recipesCount_ + 1, isVegetarian, ingredients, minutesToReady, tags, imageAddress);
	recipesCount_++;
	chef_->addRecipe(recipe);
	recipes_.insert(std::upper_bound(recipes_.begin(), recipes_.end(), recipe, compareByName<Recipe*>), recipe);
}

void System::deleteRecipe(int recipeId)
{
	checkMemberType(MemberType::Chef);
	Recipe* recipe = findInstance(recipeId, recipes_, &Recipe::checkIdCredential);
	if (recipe == nullptr)
		throw PermissionDenied("Recipe Doesn't Exist!"); // Either Permission Denied or Not Found
	if (!chef_->doesRecipeExist(recipe))
		throw PermissionDenied("This Recipe Is Not Yours!");
	chef_->removeRecipe(recipe);
	deletedRecipes_.push_back(recipe);
	const auto itr = std::find(recipes_.begin(), recipes_.end(), recipe);
	recipes_.erase(itr);
}

std::vector<Recipe::InterfaceRecipe> System::getChefsRecipes() const
{
	checkMemberType(MemberType::Chef);
	return chef_->getInterfaceRecipes();
}

void System::makeTagFilter(std::string& tag)
{
	checkMemberType(MemberType::User);
	user_->makeTagFilter(tag);
}

void System::makeVegetarianFilter()
{
	checkMemberType(MemberType::User);
	user_->makeVegetarianFilter();
}

void System::makeTimeFilter(int min, int max)
{
	checkMemberType(MemberType::User);
	user_->makeTimeFilter(min, max);
}

void System::makeRatingFilter(double min, double max)
{
	checkMemberType(MemberType::User);
	user_->makeRatingFilter(min, max);
}

void System::deleteFilter()
{
	checkMemberType(MemberType::User);
	user_->deleteFilter();
}

User::FilterStatus System::getFilterStatus() const
{
	checkMemberType(MemberType::User);
	return user_->getFilterStatus();
}

template <typename T, typename U>
T* System::findInstance(U& argument, const std::vector<T*>& instances, bool (T::* ptr)(U& arg) const) const
{
	auto itr = std::find_if(instances.begin(), instances.end(), [&argument, ptr](T* t) { return (t->*ptr)(argument); });
	if (itr == instances.end())
		return nullptr;
	return *itr;
}

void System::checkMemberType(MemberType member) const
{
	switch (member)
	{
	case MemberType::User:
		if (loggedInMember_ != member)
			throw PermissionDenied("You Should Be Logged In As A Normal User To Use This Command!");
		break;
	case MemberType::Chef:
		if (loggedInMember_ != member)
			throw PermissionDenied("You Should Be Logged In As A Chef To Use This Command!");
		break;
	case MemberType::NA:
		if (loggedInMember_ != member)
			throw BadRequest("Logout First To Use This Command!");
		break;
	}
}
