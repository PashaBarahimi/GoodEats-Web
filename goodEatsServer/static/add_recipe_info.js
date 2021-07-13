function addRecipe(recipe) {
    if (!(recipe instanceof Recipe)){
        throw "Wrong Recipe";
    }
    
    var element = document.getElementById("recipes");
    element.innerHTML = recipe.toHTML();
}


addRecipe(recipeInfo);
document.getElementById("rating").value = recipeInfo.userRating;
document.getElementById("ratingLabel").innerHTML = recipeInfo.userRating;
document.getElementById("recipeId").value = recipeInfo.id;
