#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include <QPushButton>
#include <QLineEdit>
#include <QWidget>
#include <QBoxLayout>
#include <QLabel>
#include "task.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void createLayout();
    QSystemTrayIcon *trayIco;

protected:
    QWidget *wdg;

private slots:
    void createDebugTask();
    void warn();
    void createResearchTask();
    void queueSearch();
    void queueDebug();

private:
    void createTrayIcon();
    void createActions();
    void closeEvent(QCloseEvent *event) override;
    task *t1;

    //layout items
    Ui::MainWindow *ui;
    QVBoxLayout *vlay;
    QPushButton *btn1;
    QPushButton *btn2;
    QLabel *label;
    QLabel *label2;
    QLineEdit *nameLine;

    //trayIcon parts
    QAction *minimizeAction;
    QAction *maximizeAction;
    QAction *restoreAction;
    QAction *quitAction;
    QMenu *trayIconMenu;
};

#endif // MAINWINDOW_H
