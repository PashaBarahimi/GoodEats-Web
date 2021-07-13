function addShelf(shelf) {
    if (!(shelf instanceof Shelf)) {
        throw "Wrong Shelf!";
    }

    var aTag = document.createElement("a");
    aTag.href = "shelf?shelfId=" + shelf.id;
    aTag.innerHTML = shelf.toHTMLForList();
    var element = document.getElementById("shelves");
    element.appendChild(aTag);
}

for (let i = 0; i < shelvesList.length; i++) {
    addShelf(shelvesList[i]);
}