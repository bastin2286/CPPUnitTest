import * as names from 'names.js';

function invokeMenuItem(menu, item)
{
    activateItem(waitForObjectItem({"type": "QMenuBar"}, menu));
    activateItem(waitForObjectItem({"title": menu, "type": "QMenu"}, item));
}


function addNameAndAddress(oneNameAndAddress)
{
    invokeMenuItem("Edit", "Add...");
    type(waitForObject(names.forenameLineEdit), oneNameAndAddress[0]);
    type(waitForObject(names.surnameLineEdit), oneNameAndAddress[1]);
    type(waitForObject(names.emailLineEdit), oneNameAndAddress[2]);
    type(waitForObject(names.phoneLineEdit), oneNameAndAddress[3]);

    clickButton(waitForObject(names.addressBookAddOKQPushButton));
}


function closeWithoutSaving()
{
    invokeMenuItem("File", "Quit");
    clickButton(waitForObject(names.addressBookNoQPushButton));
}


function main()
{
    startApplication("addressbook");
    invokeMenuItem("File", "New");
    var table = waitForObject({"type": "QTableWidget"});
    test.verify(table.rowCount == 0);
    var data = new Array(
        new Array("Andy", "Beach", "andy.beach@nowhere.com", "555 123 6786"),
        new Array("Candy", "Deane", "candy.deane@nowhere.com", "555 234 8765"),
        new Array("Ed", "Fernleaf", "ed.fernleaf@nowhere.com", "555 876 4654"));
    for (var row = 0; row < data.length; ++row)
        addNameAndAddress(data[row]);

    //test.compare(table.rowCount, data.length, "table contains as many rows as added data");
    closeWithoutSaving();
}

