#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include <QSystemTrayIcon>
#include <QDialog>

QT_BEGIN_NAMESPACE
class QMenu;
QT_END_NAMESPACE

class MainWindow : public QDialog
{
    Q_OBJECT

public:
    MainWindow();
    void init();

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    /* Application */
    void aboutToQuit();

    /* Tray Icon */
    void iconActivated(QSystemTrayIcon::ActivationReason reason);
    void trayAboutToShow();

    /* Actions */
    void restoreIsTriggered();

private:
    void createActions();
    void createTrayIcon();

private:
    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;

    QAction *restoreAction;
    QAction *quitAction;
};

#endif
