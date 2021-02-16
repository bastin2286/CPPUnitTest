function main()
{
    loadUrl("http://gwt.google.com/samples/Showcase/Showcase.html#!CwTree");
    waitForObject(":gwt-Tree_DIV");
    
    var tree = findObject(":gwt-Tree_DIV");
    
    var i = tree.childItem();
    test.compare(i.text, "Beethoven");
    test.compare(i.itemView().realType, "gwttree");
    
    test.compare(i.open, false);
    test.compare(i.selected, false);
    i.open = true;
    i.selected = true;
    test.verify(i.open);
    test.verify(i.selected);
    
    i = i.childItem();
    test.compare(i.text, "Concertos");
    
    i = i.nextSibling();
    test.compare(i.text, "Quartets");
    
    i = i.nextSibling();
    test.compare(i.text, "Sonatas");
    
    i = i.parentItem();
    test.compare(i.text, "Beethoven");
    
    i = i.nextSibling();
    test.compare(i.text, "Brahms");
    
    i = i.parentItem();
    test.verify(isNull(i));
    
    closeWindow(":[Window]");
}
