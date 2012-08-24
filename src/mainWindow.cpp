#include "mainWindow.h"
#include <QDebug>

// Initialisation
// ----------------------------------------------------------------------------
MainWindow::MainWindow()
{

}

void MainWindow::init()
{
    createActions();

    createTrayIcon();
    trayIcon->show();
    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));

    setWindowTitle(tr("Systray"));

    connect(qApp, SIGNAL(aboutToQuit()), this, SLOT(aboutToQuit()));
}

// Events
// ----------------------------------------------------------------------------
void MainWindow::closeEvent(QCloseEvent *event)
{
    if (trayIcon->isVisible()) {
        QMessageBox::information(this, tr("Systray"),
                                 tr("The program will keep running in the "
                                    "system tray. To terminate the program, "
                                    "choose <b>Quit</b> in the context menu "
                                    "of the system tray entry."));
        hide();
        event->ignore();
    }
}

void MainWindow::aboutToQuit()
{
    qDebug() << "aboutToQuit";
}

// Slots
// ----------------------------------------------------------------------------
void MainWindow::trayAboutToShow()
{
    bool top = false;

    QPoint p = trayIcon->geometry().center();
    if (p.isNull()) {
        p = QCursor::pos();
    }

    QDesktopWidget dw;

    QRect qr = dw.screenGeometry(p);

    if (p.y() < (qr.height() / 2))
        top = true;

    trayIconMenu->clear();
    if (top) {
        trayIconMenu->addAction(restoreAction);
        trayIconMenu->addSeparator();
        trayIconMenu->addAction(quitAction);
    } else {
        trayIconMenu->addAction(quitAction);
        trayIconMenu->addSeparator();;
        trayIconMenu->addAction(restoreAction);
    }

}

void MainWindow::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {
    case QSystemTrayIcon::Trigger:
    case QSystemTrayIcon::DoubleClick:
        qDebug() << "dblclick";
        break;
    default:
        ;
    }
}

void MainWindow::restoreIsTriggered()
{
    qDebug() << "restore";
}

// Tray Icon
// ----------------------------------------------------------------------------
void MainWindow::createTrayIcon()
{
    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(QIcon(":/heart.svg"));
    trayIcon->setToolTip("Tray Icon");

#ifndef Q_OS_MAC
    trayIcon->show();
#endif

    trayIconMenu = new QMenu(this);
    connect(trayIconMenu, SIGNAL(aboutToShow()), this, SLOT(trayAboutToShow()));
    trayAboutToShow();
    trayIcon->setContextMenu(trayIconMenu);
}

// Context Menu
// ----------------------------------------------------------------------------
void MainWindow::createActions()
{
    restoreAction = new QAction(tr("&Restore"), this);
    connect(restoreAction, SIGNAL(triggered()), this, SLOT(showNormal()));

    quitAction = new QAction(tr("&Quit"), this);
    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));

}
