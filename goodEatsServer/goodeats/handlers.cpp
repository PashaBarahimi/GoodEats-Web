#include "include/handlers.hpp"

std::string recipeArray(const std::vector<Recipe::InterfaceRecipe>& recipes, std::string arrayName)
{
	std::ostringstream str;
	str << "var " << arrayName << " = [\n";
	for (const auto& rec : recipes)
		str << recipeLine(rec) << ",\n";
	str << "];";
	return str.str();
}

std::string containArray(const std::vector<Recipe::InterfaceRecipe>& shelfRecipes, const std::vector<Recipe::InterfaceRecipe>& allRecipes, int shelfId)
{
	std::ostringstream str;
	str << "var allRecipes = [\n";
	for (const auto& rec : allRecipes)
	{
		const auto itr = std::find_if(shelfRecipes.begin(), shelfRecipes.end(), [&rec](const Recipe::InterfaceRecipe& recipe) ->bool
			{return rec.id == recipe.id; });
		const bool contains = (itr != shelfRecipes.end());
		str << recipeLine(rec, shelfId, contains) << ",\n";
	}
	str << "];";
	return str.str();
}

std::string recipeLine(Recipe::InterfaceRecipe rec, int shelfId, bool isSelected)
{
	std::ostringstream str;
	std::ostringstream ingredients;
	for (unsigned i = 0; i < rec.ingredients.size(); i++)
	{
		ingredients << rec.ingredients[i];
		if (i < rec.ingredients.size() - 1)
			ingredients << ", ";
	}
	std::ostringstream tags;
	for (unsigned i = 0; i < rec.tags.size(); i++)
	{
		tags << rec.tags[i];
		if (i < rec.tags.size() - 1)
			tags << ", ";
	}
	str << "new Recipe('" << rec.name << "', " << rec.id << ", '" << (rec.isVegetarian ? "Yes'" : "No'") << ", '"
	<< ingredients.str() << "', " << rec.minutesToReady << ", '" << tags.str() << "', '" << rec.imageAddress << "', "
	<< rec.rating << ", " << rec.usersRating << ", " << shelfId << ", " << (isSelected ? "true" : "false") << ")";
	return str.str();
}

std::string shelfArray(const std::vector<Shelf::InterfaceShelf>& shelves)
{
	std::ostringstream str;
	str << "const shelvesList = [\n";
	for (const auto& shelf : shelves)
		str << "new Shelf('" << shelf.name << "', " << shelf.id << "),\n";
	str << "];";
	return str.str();
}

void trimLeft(std::string& str)
{
	str.erase(str.begin(), std::find_if(str.begin(), str.end(), [](unsigned char ch) { return !std::isspace(ch); }));
}

void trimRight(std::string& str)
{
	str.erase(std::find_if(str.rbegin(), str.rend(), [](unsigned char ch) { return !std::isspace(ch); }).base(), str.end());
}

void trim(std::string& str)
{
	trimLeft(str);
	trimRight(str);
}

std::vector<std::string> separateByComma(std::string line)
{
	std::istringstream str(line);
	std::vector<std::string> words;
	std::string word;
	while (std::getline(str, word, ','))
	{
		trim(word);
		if (!word.empty())
			words.push_back(word);
	}
	return words;
}

Response* ExceptionHandler::callback(Request* req)
{
	auto* res = new Response;
	res->setHeader("Content-Type", "text/javascript");
	std::ostringstream stream;
	stream << "document.getElementById('basicInfo').innerHTML = \"" << basicInfo_ << "\";\n";
	stream << "document.getElementById('moreInfo').innerHTML = \"" << moreInfo_ << "\";\n";
	res->setBody(stream.str());
	return res;
}

std::string ExceptionHandler::setError(const std::string& basicInfo, const std::string& moreInfo)
{
	basicInfo_ = basicInfo;
	moreInfo_ = moreInfo;
	return "/error_occurrence";
}

Response* ShowJsPage::callback(Request* req)
{
	auto* res = showPage_->callback(req);
	res->setHeader("Content-Type", "text/javascript");
	return res;
}

Response* CheckReqSessionId::callback(Request* req)
{
	try
	{
		if (system_->checkSessionId(req->getSessionId()) != member_)
			throw PermissionDenied("You Don't Have Permission To Access This Page!");
	}
	catch (Error& err)
	{
		Response* res = Response::redirect(exceptionHandler_->setError(err.what(), err.moreInfo()));
		return res;
	}
	return request_->callback(req);
}

Response* HomePageHandler::callback(Request* req)
{
	const System::MemberType user = system_->checkSessionId(req->getSessionId());
	switch (user)
	{
	case System::MemberType::User:
		return userHome_->callback(req);
	case System::MemberType::Chef:
		return chefHome_->callback(req);
	case System::MemberType::NA:
		auto* res = loginAndSignUpHandler_->callback(req);
		res->setSessionId("");
		return res;
	}
	return loginAndSignUpHandler_->callback(req);
}

HomePageHandler::~HomePageHandler()
{
	delete loginAndSignUpHandler_;
	delete userHome_;
	delete chefHome_;
}

Response* LoginHandler::callback(Request* req)
{
	std::string username = req->getBodyParam("lUsername");
	std::string password = req->getBodyParam("lPWord");
	system_->checkSessionId(req->getSessionId());
	std::string id;
	try
	{
		id = system_->login(username, password);
	}
	catch (Error& err)
	{
		Response* res = Response::redirect(exceptionHandler_->setError(err.what(), err.moreInfo()));
		return res;
	}
	Response* res = Response::redirect("/");
	res->setSessionId(id);
	return res;
}

Response* SignUpHandler::callback(Request* req)
{
	std::string username = req->getBodyParam("sUsername");
	std::string password = req->getBodyParam("sPWord");
	const std::string userType = req->getBodyParam("userType");
	system_->checkSessionId(req->getSessionId());
	std::string id;
	System::MemberType type;
	if (userType == "normalUser")
		type = System::MemberType::User;
	else if (userType == "chef")
		type = System::MemberType::Chef;
	else
		type = System::MemberType::NA;
	try
	{
		id = system_->signUp(username, password, type);
	}
	catch (Error& err)
	{
		Response* res = Response::redirect(exceptionHandler_->setError(err.what(), err.moreInfo()));
		return res;
	}
	Response* res = Response::redirect("/");
	res->setSessionId(id);
	return res;
}

Response* LogoutHandler::callback(Request* req)
{
	system_->checkSessionId(req->getSessionId());
	try
	{
		system_->logout(req->getSessionId());
	}
	catch (Error& err)
	{
		Response* res = Response::redirect(exceptionHandler_->setError(err.what(), err.moreInfo()));
		return res;
	}
	Response* res = Response::redirect("/");
	res->setSessionId("");
	return res;
}

Response* UserRecipesHandler::callback(Request* req)
{
	system_->checkSessionId(req->getSessionId());
	std::vector<Recipe::InterfaceRecipe> recipes;
	try
	{
		recipes = system_->getRecipesList();
	}
	catch (Error& err)
	{
		Response* res = Response::redirect(exceptionHandler_->setError(err.what(), err.moreInfo()));
		return res;
	}
	auto* res = new Response;
	res->setHeader("Content-Type", "text/javascript");
	res->setBody(recipeArray(recipes, "recipesList"));
	return res;
}

Response* FilterStatus::callback(Request* req)
{
	system_->checkSessionId(req->getSessionId());
	User::FilterStatus status;
	try
	{
		status = system_->getFilterStatus();
	}
	catch (Error& err)
	{
		Response* res = Response::redirect(exceptionHandler_->setError(err.what(), err.moreInfo()));
		return res;
	}
	auto* res = new Response;
	res->setHeader("Content-Type", "text/javascript");
	std::ostringstream stream;
	stream << "filterStatus = new Filter('" << status.tag << "', " << (status.isVegetarian ? "true" : "false") << ", "
		<< status.minRating << ", " << status.maxRating << ", " << status.minTime << ", " << status.maxTime << ");";
	res->setBody(stream.str());
	return res;
}

Response* FilterRecipes::callback(Request* req)
{
	system_->checkSessionId(req->getSessionId());
	std::string tag = req->getBodyParam("tag");
	const bool vegetarian = req->getBodyParam("vegetarian") == "on";
	const double minRating = std::stod(req->getBodyParam("minRating"));
	const double maxRating = std::stod(req->getBodyParam("maxRating"));
	const int minTime = std::stoi(req->getBodyParam("minTime"));
	const int maxTime = std::stoi(req->getBodyParam("maxTime"));
	try
	{
		system_->deleteFilter();
		system_->makeTagFilter(tag);
		if (vegetarian) system_->makeVegetarianFilter();
		system_->makeRatingFilter(minRating, maxRating);
		system_->makeTimeFilter(minTime, maxTime);
	}
	catch (Error& err)
	{
		Response* res = Response::redirect(exceptionHandler_->setError(err.what(), err.moreInfo()));
		return res;
	}
	Response* res = Response::redirect("/");
	return res;
}

Response* FilterReset::callback(Request* req)
{
	system_->checkSessionId(req->getSessionId());
	try
	{
		system_->deleteFilter();
	}
	catch (Error& err)
	{
		Response* res = Response::redirect(exceptionHandler_->setError(err.what(), err.moreInfo()));
		return res;
	}
	Response* res = Response::redirect("/");
	return res;
}

Response* NewShelf::callback(Request* req)
{
	system_->checkSessionId(req->getSessionId());
	std::string name = req->getBodyParam("shelfName");
	try
	{
		system_->makeShelf(name);
	}
	catch (Error& err)
	{
		Response* res = Response::redirect(exceptionHandler_->setError(err.what(), err.moreInfo()));
		return res;
	}
	Response* res = Response::redirect("/shelves");
	return res;
}

Response* ShelvesList::callback(Request* req)
{
	system_->checkSessionId(req->getSessionId());
	std::vector<Shelf::InterfaceShelf> shelves;
	try
	{
		shelves = system_->getUsersShelves();
	}
	catch (Error& err)
	{
		Response* res = Response::redirect(exceptionHandler_->setError(err.what(), err.moreInfo()));
		return res;
	}
	auto* res = new Response;
	res->setHeader("Content-Type", "text/javascript");
	res->setBody(shelfArray(shelves));
	return res;
}

std::map<std::string, std::string> RecipeHandler::handle(Request* req)
{
	std::map<std::string, std::string> context;
	context["id"] = req->getQueryParam("id");
	return context;
}

Response* RecipeIdHandler::callback(Request* req)
{
	system_->checkSessionId(req->getSessionId());
	Recipe::InterfaceRecipe recipe;
	try
	{
		recipe = system_->getRecipeInfo(std::stoi(req->getQueryParam("id")));
	}
	catch (Error& err)
	{
		Response* res = Response::redirect(exceptionHandler_->setError(err.what(), err.moreInfo()));
		return res;
	}
	const std::string js = "const recipeInfo = " + recipeLine(recipe) + ";";
	auto* res = new Response;
	res->setHeader("Content-Type", "text/javascript");
	res->setBody(js);
	return res;
}

Response* RateHandler::callback(Request* req)
{
	system_->checkSessionId(req->getSessionId());
	try
	{
		system_->rate(std::stoi(req->getBodyParam("recipeId")), std::stod(req->getBodyParam("rating")));
	}
	catch (Error& err)
	{
		Response* res = Response::redirect(exceptionHandler_->setError(err.what(), err.moreInfo()));
		return res;
	}
	catch (...)
	{
		Response* res = Response::redirect("/");
		return res;
	}
	Response* res = Response::redirect("/recipe?id=" + req->getBodyParam("recipeId"));
	return res;
}

Response* NewRecipe::callback(Request* req)
{
	system_->checkSessionId(req->getSessionId());
	std::string recipeName = req->getBodyParam("recipeName");
	std::vector<std::string> ingredients = separateByComma(req->getBodyParam("ingredients"));
	float readyTime;
	try
	{
		readyTime = std::stof(req->getBodyParam("readyTime"));
	}
	catch (...)
	{
		readyTime = 0;
	}
	std::vector<std::string> tags = separateByComma(req->getBodyParam("tags"));
	std::string imageAddress = req->getBodyParam("imageAddress");
	const bool isVegetarian = (req->getBodyParam("vegetarian") == "on");
	try
	{
		system_->makeRecipe(recipeName, ingredients, isVegetarian, static_cast<int>(readyTime), tags, imageAddress);
	}
	catch (Error& err)
	{
		Response* res = Response::redirect(exceptionHandler_->setError(err.what(), err.moreInfo()));
		return res;
	}
	Response* res = Response::redirect("/");
	return res;
}

Response* ChefRecipes::callback(Request* req)
{
	system_->checkSessionId(req->getSessionId());
	std::vector<Recipe::InterfaceRecipe> recipes;
	try
	{
		recipes = system_->getChefsRecipes();
	}
	catch (Error& err)
	{
		Response* res = Response::redirect(exceptionHandler_->setError(err.what(), err.moreInfo()));
		return res;
	}
	auto* res = new Response;
	res->setHeader("Content-Type", "text/javascript");
	res->setBody(recipeArray(recipes, "recipesList"));
	return res;
}

Response* DeleteRecipeHandler::callback(Request* req)
{
	system_->checkSessionId(req->getSessionId());
	std::vector<std::string> idStrings = separateByComma(req->getBodyParam("deletedRecipes"));
	std::vector<int> ids;
	for (const std::string& str : idStrings)
	{
		try
		{
			const int id = std::stoi(str);
			ids.push_back(id);
		}
		catch (...)
		{
		}
	}
	try
	{
		for (int id : ids)
			system_->deleteRecipe(id);
	}
	catch (Error& err)
	{
		Response* res = Response::redirect(exceptionHandler_->setError(err.what(), err.moreInfo()));
		return res;
	}
	Response* res = Response::redirect("/");
	return res;
}

Response* ShelvesRecipes::callback(Request* req)
{
	system_->checkSessionId(req->getSessionId());
	std::vector<Recipe::InterfaceRecipe> shelfRecipes;
	std::vector<Recipe::InterfaceRecipe> allRecipes;
	const int shelfId = std::stoi(req->getQueryParam("shelfId"));
	try
	{
		shelfRecipes = system_->getShelf(shelfId).recipes;
		allRecipes = system_->getAllRecipesForShelfEdit(shelfId);
	}
	catch (Error& err)
	{
		Response* res = Response::redirect(exceptionHandler_->setError(err.what(), err.moreInfo()));
		return res;
	}
	auto* res = new Response;
	res->setHeader("Content-Type", "text/javascript");
	res->setBody(recipeArray(shelfRecipes, "recipesList") + '\n' + containArray(shelfRecipes, allRecipes, shelfId));
	return res;
}

std::map<std::string, std::string> ShelfRecipesHandler::handle(Request* req)
{
	std::map<std::string, std::string> context;
	context["shelfId"] = req->getQueryParam("shelfId");
	return context;
}

std::map<std::string, std::string> ShelfSingleRecipeHandler::handle(Request* req)
{
	std::map<std::string, std::string> context;
	context["id"] = req->getQueryParam("id");
	context["shelfId"] = req->getQueryParam("shelfId");
	return context;
}

Response* EditShelfRecipes::callback(Request* req)
{
	system_->checkSessionId(req->getSessionId());
	std::vector<std::string> idStrings = separateByComma(req->getBodyParam("included"));
	std::vector<int> ids;
	const int shelfId = std::stoi(req->getQueryParam("shelfId"));
	for (const std::string& str : idStrings)
	{
		try
		{
			const int id = std::stoi(str);
			ids.push_back(id);
		}
		catch (...)
		{
		}
	}
	try
	{
		system_->deleteAllShelfRecipes(shelfId);
		for (int id : ids)
			system_->addRecipeToShelf(shelfId, id);
	}
	catch (Error& err)
	{
		Response* res = Response::redirect(exceptionHandler_->setError(err.what(), err.moreInfo()));
		return res;
	}
	Response* res = Response::redirect("/shelf?shelfId=" + std::to_string(shelfId));
	return res;
}
