greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
HEADERS   += lineedit.h
HEADERS   += dialog.h
SOURCES   += dialog.cpp
HEADERS   += mainwindow.h
SOURCES   += mainwindow.cpp
SOURCES   += main.cpp
RESOURCES += addressbook.qrc
TRANSLATIONS += translations/addressbook_de.ts
TRANSLATIONS += translations/addressbook_fr.ts

boot2qt {
    target.path = /data/user/qt/$$TARGET
    INSTALLS += target
}
