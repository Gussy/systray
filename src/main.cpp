#include <QtGui>

#include "mainWindow.h"

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(systray);

    QApplication app(argc, argv);
    QApplication::setQuitOnLastWindowClosed(false);
    if (!QSystemTrayIcon::isSystemTrayAvailable()) {
        QMessageBox::critical(0, QObject::tr("Systray"),
                              QObject::tr("I couldn't detect any system tray "
                                          "on this system."));
        return 1;
    }

    // Call the window constructor
    MainWindow window;
    window.init();

    return app.exec();
}
