function checkSelection(element) {
    if (element.className == "selectableRecipe selected") {
        element.className = "selectableRecipe notSelected";
    }
    else if (element.className == "selectableRecipe notSelected") {
        element.className = "selectableRecipe selected";
    }
}

function showEditPage() {
    document.getElementById("recipes").style.display = "none";
    document.getElementById("editableRecipes").style.display = "block";
    document.getElementById("firstPart").style.display = "none";
    document.getElementById("secondPart").style.display = "block";
}

function cancelEdit() {
    for (let i = 0; i < allRecipes.length; i++) {
        document.getElementById("r" + i).className = "selectableRecipe " + (allRecipes[i].isSelected == true ? 'selected' : 'notSelected');
    }
    document.getElementById("recipes").style.display = "block";
    document.getElementById("editableRecipes").style.display = "none";
    document.getElementById("firstPart").style.display = "block";
    document.getElementById("secondPart").style.display = "none";
}

function editSelected() {
    var hiddenElement = document.getElementById("included");
    var isFirst = true;
    for (let i = 0; i < allRecipes.length; i++)  {
        if (document.getElementById("r" + i).className == "selectableRecipe selected") {
            if (isFirst == false) {
                hiddenElement.value += ",";
            }
            else {
                isFirst = false;
            }
            hiddenElement.value += allRecipes[i].id;
        }
    }
    document.getElementById("editForm").submit();
}