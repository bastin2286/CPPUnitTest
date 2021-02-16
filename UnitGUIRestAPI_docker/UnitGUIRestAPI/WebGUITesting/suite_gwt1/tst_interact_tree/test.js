function main()
{
    loadUrl("http://gwt.google.com/samples/Showcase/Showcase.html#!CwTree");
    waitForObject(":gwt-Tree_DIV");
    
    var tree = findObject(":gwt-Tree_DIV");
    var beethovenItem = tree.findItem("Beethoven");
    
    test.compare(beethovenItem.selected, false);
    test.compare(beethovenItem.open, false);
    
    clickItem(":gwt-Tree_DIV", "Beethoven");
    clickTreeHandle(":gwt-Tree_DIV", "Beethoven");
    
    test.verify(beethovenItem.selected);
    test.verify(beethovenItem.open);
    
    clickTreeHandle(":gwt-Tree_DIV", "Sonatas");
    
    var sonataItem = tree.findItem("Sonata in F Major");
    test.compare(sonataItem.selected, false);
    
    clickItem(":gwt-Tree_DIV", "Sonata in F Major");
    
    test.compare(beethovenItem.selected, false);
    test.verify(sonataItem.selected);
    
    closeWindow(":[Window]");
}
