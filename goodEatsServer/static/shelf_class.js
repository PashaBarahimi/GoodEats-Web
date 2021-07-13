class Shelf {
    constructor(name, id) {
        this.name = name;
        this.id = id;
    }
    toHTMLForList() {
        return "<p class='shelf'><img src='shelf.png' alt='shelf' class='shelfImage'>\n" +
        this.name + " (ID = " + this.id + ")\n</p>"
    }
}