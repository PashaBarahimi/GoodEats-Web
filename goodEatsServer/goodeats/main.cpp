#include "../server/server.hpp"
#include "../goodeats/include/handlers.hpp"

using namespace std;

const string STATIC_PATH = "goodEatsServer/static/";
const string TEMPLATE_PATH = "goodEatsServer/template/";

int main()
{
	try
	{
		Server server(5000);
		server.setNotFoundErrPage(STATIC_PATH + "404.html");
		System system;
		auto* const exc = new ExceptionHandler;
		server.get("/error_message.js", exc);
		server.get("/error_occurrence", new ShowPage(STATIC_PATH + "error.html"));
		server.get("/error_style.css", new ShowPage(STATIC_PATH + "error_style.css"));
		server.get("/favicon.ico", new ShowImage(STATIC_PATH + "favicon.png"));
		server.get("/", new HomePageHandler(&system, exc, STATIC_PATH + "home.html", STATIC_PATH + "user.html", STATIC_PATH + "chef.html"));
		server.get("/background3.png", new ShowImage(STATIC_PATH + "background3.png"));
		server.get("/user_style.css", new ShowPage(STATIC_PATH + "user_style.css"));
		server.get("/common_style.css", new ShowPage(STATIC_PATH + "common_style.css"));
		server.get("/home_style.css", new ShowPage(STATIC_PATH + "home_style.css"));
		server.get("/home_forms_actions.js", new ShowJsPage(STATIC_PATH + "home_forms_actions.js"));
		server.get("/background1.png", new ShowImage(STATIC_PATH + "background1.png"));
		server.get("/background1_blurred.png", new ShowImage(STATIC_PATH + "background1_blurred.png"));
		server.get("/all_recipes.js", new UserRecipesHandler(&system, exc));
		server.get("/recipe_class.js", new ShowJsPage(STATIC_PATH + "recipe_class.js"));
		server.get("/add_recipe.js", new ShowJsPage(STATIC_PATH + "add_recipe.js"));
		server.get("/range_check.js", new ShowJsPage(STATIC_PATH + "range_check.js"));
		server.get("/filter_class.js", new ShowJsPage(STATIC_PATH + "filter_class.js"));
		server.get("/filter_status.js", new ShowJsPage(STATIC_PATH + "filter_status.js"));
		server.get("/user_filter.js", new FilterStatus(&system, exc));
		server.post("/filter", new FilterRecipes(&system, exc));
		server.post("/reset_filter", new FilterReset(&system, exc));
		server.get("/logo_v2.png", new ShowImage(STATIC_PATH + "logo_v2.png"));
		server.post("/login", new LoginHandler(&system, exc));
		server.post("/sign_up", new SignUpHandler(&system, exc));
		server.post("/logout", new LogoutHandler(&system, exc));
		server.get("/shelves", new CheckReqSessionId(&system, exc, new ShowPage(STATIC_PATH + "shelves.html"), System::MemberType::User));
		server.get("/shelf_class.js", new ShowJsPage(STATIC_PATH + "shelf_class.js"));
		server.get("/add_shelf.js", new ShowJsPage(STATIC_PATH + "add_shelf.js"));
		server.post("/shelves", new NewShelf(&system, exc));
		server.get("/shelf.png", new ShowImage(STATIC_PATH + "shelf.png"));
		server.get("/shelves_style.css", new ShowPage(STATIC_PATH + "shelves_style.css"));
		server.get("/all_shelves.js", new ShelvesList(&system, exc));
		server.get("/recipe", new CheckReqSessionId(&system, exc, new RecipeHandler(TEMPLATE_PATH + "recipe.html"), System::MemberType::User));
		server.get("/recipe_style.css", new ShowPage(STATIC_PATH + "recipe_style.css"));
		server.get("/add_recipe_info.js", new ShowJsPage(STATIC_PATH + "add_recipe_info.js"));
		server.get("/recipe_info.js", new RecipeIdHandler(&system, exc));
		server.post("/rate", new RateHandler(&system, exc));
		server.get("/chef_style.css", new ShowPage(STATIC_PATH + "chef_style.css"));
		server.post("/recipe", new NewRecipe(&system, exc));
		server.get("/chef_recipes_list.js", new ChefRecipes(&system, exc));
		server.get("/add_chef_recipes.js", new ShowJsPage(STATIC_PATH + "add_chef_recipes.js"));
		server.get("/chef_recipes_selection.js", new ShowJsPage(STATIC_PATH + "chef_recipes_selection.js"));
		server.post("/delete_recipes", new DeleteRecipeHandler(&system, exc));
		server.get("/shelf_recipes.js", new ShelvesRecipes(&system, exc));
		server.get("/shelf_recipe", new CheckReqSessionId(&system, exc, new ShelfSingleRecipeHandler(TEMPLATE_PATH + "shelf_recipe.html"), System::MemberType::User));
		server.get("/shelf_style.css", new ShowPage(STATIC_PATH + "shelf_style.css"));
		server.get("/shelf", new CheckReqSessionId(&system, exc, new ShelfRecipesHandler(TEMPLATE_PATH + "shelf.html"), System::MemberType::User));
		server.get("/add_shelf_recipes.js", new ShowJsPage(STATIC_PATH + "add_shelf_recipes.js"));
		server.get("/shelf_recipes_selection.js", new ShowJsPage(STATIC_PATH + "shelf_recipes_selection.js"));
		server.post("/edit_shelf_recipes", new EditShelfRecipes(&system, exc));
		server.run();
	}
	catch (Server::Exception& e)
	{
		std::cerr << e.getMessage() << std::endl;
	}
}