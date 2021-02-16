import * as names from 'names.js';

function main() {
    startApplication("addressbook");
    activateItem(waitForObjectItem(names.addressBookQMenuBar, "File"));
    activateItem(waitForObjectItem(names.addressBookFileQMenu, "Open..."));
    clickButton(waitForObject(names.qFileDialogDetailModeButtonQToolButton));
    doubleClick(waitForObjectItem(names.stackedWidgetTreeViewQTreeView, "MyAddresses\\.adr"), 66, 8, 0, Qt.LeftButton);
    var table = waitForObject(names.addressBookMyAddressesAdrFileQTableWidget)
    test.compare(table.rowCount, 125);
    doubleClick(waitForObjectItem(names.addressBookMyAddressesAdrFileQTableWidget, "3/1"), 40, 16, 0, Qt.LeftButton);
    type(waitForObject(names.fileLineEdit), "Doe");
    type(waitForObject(names.fileLineEdit), "<Return>");
    clickButton(waitForObject(names.addressBookMyAddressesAdrAddQToolButton));
    type(waitForObject(names.forenameLineEdit), "Jane");
    type(waitForObject(names.forenameLineEdit), "<Tab>");
    type(waitForObject(names.surnameLineEdit), "Doe");
    type(waitForObject(names.surnameLineEdit), "<Tab>");
    type(waitForObject(names.emailLineEdit), "Jane.doe@nowhere.com");
    type(waitForObject(names.emailLineEdit), "<Tab>");
    type(waitForObject(names.phoneLineEdit), "123 555 1212");
    clickButton(waitForObject(names.addressBookAddOKQPushButton));
    test.compare(table.rowCount, 126);
    test.compare(waitForObjectExists(names.file30QModelIndex).text, "Jane");
    test.compare(waitForObjectExists(names.file31QModelIndex).text, "Doe");
    test.compare(waitForObjectExists(names.file32QModelIndex).text, "Jane.doe@nowhere.com");
    test.compare(waitForObjectExists(names.file33QModelIndex).text, "123 555 1212");

    mouseClick(waitForObjectItem(names.addressBookMyAddressesAdrFileQTableWidget, "2/1"), 53, 11, 0, Qt.LeftButton);
    clickButton(waitForObject(names.addressBookMyAddressesAdrRemoveQToolButton));
    clickButton(waitForObject(names.addressBookYesQPushButton));
    test.compare(table.rowCount, 125);
    activateItem(waitForObjectItem(names.addressBookMyAddressesAdrQMenuBar, "File"));
    activateItem(waitForObjectItem(names.addressBookMyAddressesAdrFileQMenu, "Quit"));
    clickButton(waitForObject(names.addressBookNoQPushButton));
}
