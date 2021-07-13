class Recipe {
    constructor(name, id, isVegetarian, ingredients, minutesToReady, tags, imageAddress, rating, userRating, shelfId, isSelected) {
        this.name = name;
        this.id = id;
        this.isVegetarian = isVegetarian;
        this.ingredients = ingredients;
        this.minutesToReady = minutesToReady;
        this.tags = tags;
        this.imageAddress = imageAddress;
        this.rating = rating;
        this.userRating = userRating;
        this.shelfId = shelfId;
        this.isSelected = isSelected
    }

    toHTML(){
        return "<p class='recipe'><img src='" + this.imageAddress + "' alt='goodeats' class='recImage'>\n" + 
        this.name + " (ID = " + this.id + ")<br>\n" + 
        "Is Vegetarian : " + this.isVegetarian + "<br>\n" +
        "Rating : " + this.rating + "<br>\n" +
        "Ingredients : " + this.ingredients + "<br>\n" +
        "Ready Time : " + this.minutesToReady + "<br>\n" +
        "Tags : " + this.tags + "<br>\n" + 
        "</p>"
    }

    toHTMLWithSecondClass(firstClass, secondClass, tagId) {
        return "<p class='" + firstClass + " " + secondClass + "' id='" + tagId + "' onclick='checkSelection(this)'><img src='" + this.imageAddress + "' alt='goodeats' class='recImage'>\n" + 
        this.name + " (ID = " + this.id + ")<br>\n" + 
        "Is Vegetarian : " + this.isVegetarian + "<br>\n" +
        "Rating : " + this.rating + "<br>\n" +
        "Ingredients : " + this.ingredients + "<br>\n" +
        "Ready Time : " + this.minutesToReady + "<br>\n" +
        "Tags : " + this.tags + "<br>\n" + 
        "</p>"
    }
}