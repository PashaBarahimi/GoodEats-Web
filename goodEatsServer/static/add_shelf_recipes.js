function addRecipe(recipe) {
    if (!(recipe instanceof Recipe)){
        throw "Wrong Recipe";
    }
    
    var aTag = document.createElement("a");
    aTag.href= "/shelf_recipe?id=" + recipe.id + "&shelfId=" + shelfId;
    aTag.innerHTML = recipe.toHTML();
    var element = document.getElementById("recipes");
    element.appendChild(aTag);
}

function addSelectableRecipe(recipe, i) {
    if (!(recipe instanceof Recipe)){
        throw "Wrong Recipe";
    }
    
    var aTag = document.createElement("a");
    aTag.href= "javascript:void(0)";
    aTag.innerHTML = recipe.toHTMLWithSecondClass('selectableRecipe', (recipe.isSelected == true ? 'selected' : 'notSelected'), 'r' + i);
    var element = document.getElementById("editableRecipes");
    element.appendChild(aTag);
}

for (let i = 0; i < recipesList.length; i++) {
    addRecipe(recipesList[i]);
}

for (let i = 0; i < allRecipes.length; i++) {
    addSelectableRecipe(allRecipes[i], i);
}
