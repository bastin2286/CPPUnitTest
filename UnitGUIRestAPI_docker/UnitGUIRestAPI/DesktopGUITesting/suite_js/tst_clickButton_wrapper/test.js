import * as names from 'names.js';

function addLoggingToClickButton(clickButtonFunction) // Add this function
{
    return function(button, logText) {
        if (!logText)
            logText = "clickButton() called";
        test.log(logText, button);
        clickButtonFunction(button);
    }
}

function main()
{
    startApplication("addressbook");
    clickButton = addLoggingToClickButton(clickButton) // Add this line
    // ...
    activateItem(waitForObjectItem(names.addressBookQMenuBar, "File"));
    activateItem(waitForObjectItem(names.addressBookFileQMenu, "Open..."));
    clickButton(waitForObject(names.addressBookChooseFileDetailModeButtonQToolButton));
    waitForObjectItem(names.stackedWidgetTreeViewQTreeView, "MyAddresses\\.adr");
    clickItem(names.stackedWidgetTreeViewQTreeView, "MyAddresses\\.adr", 75, 13, 0, Qt.LeftButton);
    clickButton(waitForObject(names.addressBookChooseFileOpenQPushButton), "File Open clicked");
    waitForObjectItem(names.addressBookMyAddressesAdrFileQTableWidget, "1/0");
    clickItem(names.addressBookMyAddressesAdrFileQTableWidget, "1/0", 74, 16, 0, Qt.LeftButton);
    var table = waitForObject(names.addressBookMyAddressesAdrFileQTableWidget);
    test.verify(table.rowCount == 125);
    activateItem(waitForObjectItem(names.addressBookMyAddressesAdrQMenuBar, "Edit"));
    activateItem(waitForObjectItem(names.addressBookMyAddressesAdrEditQMenu, "Add..."));
    type(waitForObject(names.forenameLineEdit), "Jane");
    type(waitForObject(names.forenameLineEdit), "<Tab>");
    type(waitForObject(names.surnameLineEdit), "Doe");
    type(waitForObject(names.surnameLineEdit), "<Tab>");
    type(waitForObject(names.emailLineEdit), "jane.doe@nowhere.com");
    type(waitForObject(names.emailLineEdit), "<Tab>");
    type(waitForObject(names.phoneLineEdit), "555 123 4567");
    clickButton(waitForObject(names.addressBookAddOKQPushButton));
    waitForObjectItem(names.addressBookMyAddressesAdrFileQTableWidget, "3/1");
    clickItem(names.addressBookMyAddressesAdrFileQTableWidget, "3/1", 21, 22, 0, Qt.LeftButton);
    type(waitForObject(names.addressBookMyAddressesAdrFileQTableWidget), "<Shift>");
    type(waitForObject(names.addressBookMyAddressesAdrFileQTableWidget), "D");
    type(waitForObject(names.addressBookMyAddressesAdr31LineEdit), "oe");
    type(waitForObject(names.addressBookMyAddressesAdr31LineEdit), "<Return>");
    waitForObjectItem(names.addressBookMyAddressesAdrFileQTableWidget, "0/1");
    test.verify(table.rowCount == 126);
    clickItem(names.addressBookMyAddressesAdrFileQTableWidget, "0/1", 25, 16, 0, Qt.LeftButton);
    activateItem(waitForObjectItem(names.addressBookMyAddressesAdrQMenuBar, "Edit"));
    activateItem(waitForObjectItem(names.addressBookMyAddressesAdrEditQMenu, "Remove..."));
    clickButton(waitForObject(names.addressBookYesQPushButton));
    test.compare(waitForObjectExists(names.file00QModelIndex).text, "Jane");
    test.compare(waitForObjectExists(names.file01QModelIndex).text, "Doe");
    test.compare(waitForObjectExists(names.file02QModelIndex).text, "jane.doe@nowhere.com");
    test.compare(waitForObjectExists(names.file03QModelIndex).text, "555 123 4567");

    test.verify(table.rowCount == 125);
    activateItem(waitForObjectItem(names.addressBookMyAddressesAdrQMenuBar, "File"));
    activateItem(waitForObjectItem(names.addressBookMyAddressesAdrFileQMenu, "Quit"));
    clickButton(waitForObject(names.addressBookNoQPushButton));
}
