function addRecipe(recipe) {
    if (!(recipe instanceof Recipe)){
        throw "Wrong Recipe";
    }
    
    var aTag = document.createElement("a");
    aTag.href= "javascript:void(0)";
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
    aTag.innerHTML = recipe.toHTMLWithSecondClass('selectableRecipe', 'notSelected', 'r' + i);
    var element = document.getElementById("editableRecipes");
    element.appendChild(aTag);
}

for (let i = 0; i < recipesList.length; i++) {
    addRecipe(recipesList[i]);
    addSelectableRecipe(recipesList[i], i);
}