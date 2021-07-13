function checkSelection(element) {
    if (element.className == "selectableRecipe selected") {
        element.className = "selectableRecipe notSelected";
    }
    else if (element.className == "selectableRecipe notSelected") {
        element.className = "selectableRecipe selected";
    }
}

function showDeletingPage() {
    document.getElementById("addForm").reset();
    document.getElementById("addRecipe").style.display = "none";
    document.getElementById("deleteRecipe").style.display = "block";
    document.getElementById("recipes").style.display = "none";
    document.getElementById("editableRecipes").style.display = "block";
}

function cancelEdit() {
    for (let i = 0; i < recipesList.length; i++) {
        document.getElementById("r" + i).className = "selectableRecipe notSelected";
    }
    document.getElementById("addRecipe").style.display = "block";
    document.getElementById("deleteRecipe").style.display = "none";
    document.getElementById("recipes").style.display = "block";
    document.getElementById("editableRecipes").style.display = "none";
}

function deleteSelected() {
    var hiddenElement = document.getElementById("deletedRecipes");
    var isFirst = true;
    for (let i = 0; i < recipesList.length; i++) {
        if (document.getElementById("r" + i).className == "selectableRecipe selected") {
            if (isFirst == false) {
                hiddenElement.value += ",";
            }
            else {
                isFirst = false;
            }
            hiddenElement.value += recipesList[i].id;
        }
    }
    document.getElementById("deleteForm").submit();
}