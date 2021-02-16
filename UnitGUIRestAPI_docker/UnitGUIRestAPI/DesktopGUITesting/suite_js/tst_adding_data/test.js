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

function checkNameAndAddress(table, record)
{
    for (var column = 0; column < testData.fieldNames(record).length; ++column)
        test.compare(table.item(0, column).text(), // New addresses are inserted at the start
                     testData.field(record, column));
}

function main()
{
    startApplication("addressbook");
    invokeMenuItem("File", "New");
    var table = waitForObject({"type": "QTableWidget"});
    test.verify(table.rowCount == 0);
    var limit = 10; // To avoid testing 100s of rows since that would be boring
    var records = testData.dataset("MyAddresses.tsv");
    for (var row = 0; row < records.length; ++row) {
        var record = records[row];
        var forename = testData.field(record, "Forename");
        var surname = testData.field(record, "Surname");
        var email = testData.field(record, "Email");
        var phone = testData.field(record, "Phone");
        table.setCurrentCell(0, 0); // always insert at the start
        addNameAndAddress(new Array(forename, surname, email, phone));
        checkNameAndAddress(table, record);
        if (row > limit)
            break;
    }
    //test.compare(table.rowCount, row + 1, "table contains as many rows as added data");
    closeWithoutSaving();
}
