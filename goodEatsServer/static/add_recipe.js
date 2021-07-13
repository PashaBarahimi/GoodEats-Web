function addRecipe(recipe) {
    if (!(recipe instanceof Recipe)){
        throw "Wrong Recipe";
    }
    
    var aTag = document.createElement("a");
    aTag.href="recipe?id=" + recipe.id;
    aTag.innerHTML = recipe.toHTML();
    var element = document.getElementById("recipes");
    element.appendChild(aTag);
}

for (let i = 0; i < recipesList.length; i++) {
    addRecipe(recipesList[i]);
}