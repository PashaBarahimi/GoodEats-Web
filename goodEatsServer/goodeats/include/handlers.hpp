#ifndef HANDLERS_HPP
#define HANDLERS_HPP

#include "../../server/server.hpp"
#include "../../../goodEatsSystem/src/include/System.hpp"

std::string recipeArray(const std::vector<Recipe::InterfaceRecipe>& recipes, std::string arrayName);
std::string containArray(const std::vector<Recipe::InterfaceRecipe>& shelfRecipes, const std::vector<Recipe::InterfaceRecipe>& allRecipes, int shelfId);
std::string recipeLine(Recipe::InterfaceRecipe rec, int shelfId = -1, bool isSelected = false);
std::string shelfArray(const std::vector<Shelf::InterfaceShelf>& shelves);
void trimLeft(std::string& str);
void trimRight(std::string& str);
void trim(std::string& str);
std::vector<std::string> separateByComma(std::string line);

class ExceptionHandler : public RequestHandler
{
public:
	ExceptionHandler() = default;
	Response* callback(Request* req) override;
	std::string setError(const std::string& basicInfo, const std::string& moreInfo);
private:
	std::string basicInfo_;
	std::string moreInfo_;
};

class ShowJsPage : public RequestHandler
{
public:
	ShowJsPage(std::string path) : showPage_(new ShowPage(std::move(path))) {  }
	~ShowJsPage() override { delete showPage_; }
	Response* callback(Request* req) override;
private:
	ShowPage* showPage_;
};

class CheckReqSessionId : public RequestHandler
{
public:
	CheckReqSessionId(System* system, ExceptionHandler* exc, RequestHandler* request, System::MemberType member) :
	system_(system), exceptionHandler_(exc), request_(request), member_(member) {  }
	~CheckReqSessionId() override { delete request_; }
	Response* callback(Request* req) override;
private:
	System* system_;
	ExceptionHandler* exceptionHandler_;
	RequestHandler* request_;
	System::MemberType member_;
};

class HomePageHandler : public RequestHandler
{
public:
	HomePageHandler(System* system, ExceptionHandler* exc, std::string loginUrl, std::string userUrl, std::string chefUrl) : system_(system),
		exceptionHandler_(exc), loginAndSignUpHandler_(new ShowPage(std::move(loginUrl))), userHome_(new ShowPage(std::move(userUrl))),
		chefHome_(new ShowPage(std::move(chefUrl))) {}
	Response* callback(Request* req) override;
	~HomePageHandler() override;
private:
	System* system_;
	ExceptionHandler* exceptionHandler_;
	ShowPage* loginAndSignUpHandler_;
	ShowPage* userHome_;
	ShowPage* chefHome_;
};

class LoginHandler : public RequestHandler
{
public:
	LoginHandler(System* system, ExceptionHandler* exc) : system_(system), exceptionHandler_(exc) {}
	Response* callback(Request* req) override;
private:
	System* system_;
	ExceptionHandler* exceptionHandler_;
};

class SignUpHandler : public RequestHandler
{
public:
	SignUpHandler(System* system, ExceptionHandler* exc) : system_(system), exceptionHandler_(exc) {}
	Response* callback(Request* req) override;
private:
	System* system_;
	ExceptionHandler* exceptionHandler_;
};

class LogoutHandler : public RequestHandler
{
public:
	LogoutHandler(System* system, ExceptionHandler* exc) : system_(system), exceptionHandler_(exc) {  }
	Response* callback(Request* req) override;
private:
	System* system_;
	ExceptionHandler* exceptionHandler_;
};

class UserRecipesHandler : public RequestHandler
{
public:
	UserRecipesHandler(System* system, ExceptionHandler* exc) : system_(system), exceptionHandler_(exc) {  }
	Response* callback(Request* req) override;
private:
	System* system_;
	ExceptionHandler* exceptionHandler_;
};

class FilterStatus : public RequestHandler
{
public:
	FilterStatus(System* system, ExceptionHandler* exc) : system_(system), exceptionHandler_(exc) {  }
	Response* callback(Request* req) override;
private:
	System* system_;
	ExceptionHandler* exceptionHandler_;
};

class FilterRecipes : public RequestHandler
{
public:
	FilterRecipes(System* system, ExceptionHandler* exc) : system_(system), exceptionHandler_(exc) {  }
	Response* callback(Request* req) override;
private:
	System* system_;
	ExceptionHandler* exceptionHandler_;
};

class FilterReset : public RequestHandler
{
public:
	FilterReset(System* system, ExceptionHandler* exc) : system_(system), exceptionHandler_(exc) {  }
	Response* callback(Request* req) override;
private:
	System* system_;
	ExceptionHandler* exceptionHandler_;
};

class NewShelf : public RequestHandler
{
public:
	NewShelf(System* system, ExceptionHandler* exc) : system_(system), exceptionHandler_(exc) {  }
	Response* callback(Request* req) override;
private:
	System* system_;
	ExceptionHandler* exceptionHandler_;
};

class ShelvesList : public RequestHandler
{
public:
	ShelvesList(System* system, ExceptionHandler* exc) : system_(system), exceptionHandler_(exc) {  }
	Response* callback(Request* req) override;
private:
	System* system_;
	ExceptionHandler* exceptionHandler_;
};

class RecipeHandler : public TemplateHandler
{
public:
	RecipeHandler(std::string filePath) : TemplateHandler(filePath) {  }
	std::map<std::string, std::string> handle(Request* req) override;
};

class RecipeIdHandler : public RequestHandler
{
public:
	RecipeIdHandler(System* system, ExceptionHandler* exc) : system_(system), exceptionHandler_(exc) {  }
	Response* callback(Request* req) override;
private:
	System* system_;
	ExceptionHandler* exceptionHandler_;
};

class RateHandler : public RequestHandler
{
public:
	RateHandler(System* system, ExceptionHandler* exc) : system_(system), exceptionHandler_(exc) {  }
	Response* callback(Request* req) override;
private:
	System* system_;
	ExceptionHandler* exceptionHandler_;
};

class NewRecipe : public RequestHandler
{
public:
	NewRecipe(System* system, ExceptionHandler* exc) : system_(system), exceptionHandler_(exc) {  }
	Response* callback(Request* req) override;
private:
	System* system_;
	ExceptionHandler* exceptionHandler_;
};

class ChefRecipes : public RequestHandler
{
public:
	ChefRecipes(System* system, ExceptionHandler* exc) : system_(system), exceptionHandler_(exc) {  }
	Response* callback(Request* req) override;
private:
	System* system_;
	ExceptionHandler* exceptionHandler_;
};

class DeleteRecipeHandler : public RequestHandler
{
public:
	DeleteRecipeHandler(System* system, ExceptionHandler* exc) : system_(system), exceptionHandler_(exc) {  }
	Response* callback(Request* req) override;
private:
	System* system_;
	ExceptionHandler* exceptionHandler_;
};

class ShelvesRecipes : public RequestHandler
{
public:
	ShelvesRecipes(System* system, ExceptionHandler* exc) : system_(system), exceptionHandler_(exc) {  }
	Response* callback(Request* req) override;
private:
	System* system_;
	ExceptionHandler* exceptionHandler_;
};

class ShelfRecipesHandler : public TemplateHandler
{
public:
	ShelfRecipesHandler(std::string filePath) : TemplateHandler(std::move(filePath)) {  }
	std::map<std::string, std::string> handle(Request* req) override;
};

class ShelfSingleRecipeHandler : public TemplateHandler
{
public:
	ShelfSingleRecipeHandler(std::string filePath) : TemplateHandler(std::move(filePath)) {  }
	std::map<std::string, std::string> handle(Request* req) override;
};

class EditShelfRecipes : public RequestHandler
{
public:
	EditShelfRecipes(System* system, ExceptionHandler* exc) : system_(system), exceptionHandler_(exc) {  }
	Response* callback(Request* req) override;
private:
	System* system_;
	ExceptionHandler* exceptionHandler_;
};
#endif
