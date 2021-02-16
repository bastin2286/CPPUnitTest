/*
    Copyright (c) 2009-11 froglogic GmbH. All rights reserved.

    This file is part of an example program for Squish---it may be used,
    distributed, and modified, without limitation.

    Note that the icons used are from KDE (www.kde.org) and subject to
    the KDE's license.

    The Qt translations are copied from Qt 4.6.3 and subject to Qt's
    licenses.
*/

#include "mainwindow.h"
#include <qapplication.h>
#include <qfont.h>
#include <qtextstream.h>
#include <qtranslator.h>
#ifdef Q_WS_X11
#  include <qstylefactory.h>
#endif
#include "../../../include/qtbuiltinhook.h"

static void showUsage( QTextStream &ts )
{
    ts << "usage: addressbook [en|de|fr] [--allow-native-file-dialogs] [--use-builtin-hook|--use-builtin-hook-port=<port>]" << endl
       << " --allow-native-file-dialogs may require 'UseNativeDialogs=1' in SQUISH_DIR/etc/qtwrapper.ini, too." << endl;
}

int main(int argc, char *argv[])
{
#ifdef Q_WS_X11
    // Avoid Gtk problems
    QStyle *windowsStyle = QStyleFactory::create( QLatin1String( "windows" ) );
    if ( windowsStyle ) {
        QApplication::setStyle( windowsStyle );
    }
#endif
    QApplication app(argc, argv);
#if defined(Q_OS_AIX) || defined(Q_OS_VXWORKS)
    Squish::installBuiltinHook(); // On AIX/VxWorks we must manually install a hook
#endif

#ifdef Q_OS_SOLARIS
    app.setFont( QFont( "Terminal", 12 ) );
#endif

    QTranslator qtTranslator;
    QTranslator appTranslator;

    const QStringList args = app.arguments();
    if ( args.size() > 1 ) {
        for ( QStringList::const_iterator it = ++args.begin(); it != args.end(); ++it ) {
            const QString &arg = *it;
            if ( arg == "--allow-native-file-dialogs" ) {
                // reparsed in mainwindow.cpp
            } else if ( arg == "--use-builtin-hook" ) {
                QTextStream( stdout ) << "Using built-in hook" << endl;
                Squish::installBuiltinHook();
            } else if ( arg.startsWith( "--use-builtin-hook-port=" ) ) {
                const QString parameter = arg.mid( arg.indexOf( '=' ) + 1 );
                const unsigned short port = parameter.toUShort();
                if ( port == 0 ) {
                    QTextStream errStream( stderr );
                    errStream << "Invalid port number: " << parameter << endl;
                    showUsage( errStream );
                    return 1;
                }
                QTextStream( stdout ) << "Using built-in hook with port " << port << endl;
                Squish::allowAttaching( port );
            } else if ( arg == "en" || arg == "de" || arg == "fr" ) {
                qtTranslator.load( ":/qt_" + arg );
                appTranslator.load( ":/addressbook_" + arg );
                app.installTranslator( &qtTranslator );
                app.installTranslator( &appTranslator );
            } else if ( arg == "-h" || arg == "--help" ) {
                QTextStream outStream( stdout );
                showUsage( outStream );
                return 0;
            } else {
                QTextStream errStream( stderr );
                showUsage( errStream );
                return 1;
            }
        }
    }

    MainWindow mainWindow;
#ifndef Q_OS_ANDROID
    mainWindow.resize(640, 480);
#endif
    mainWindow.show();
    return app.exec();
}
