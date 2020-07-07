#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "task.h"
#include <QPushButton>
#include <QBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    createLayout();
    t1 = new task();
    createActions();
    createTrayIcon();
    trayIco->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

//Overwrite close event to let the TrayIcon command the closure
void MainWindow::closeEvent(QCloseEvent *event)
{
    if (trayIco->isVisible()) {
            this->hide();
            event->ignore();
        }
}

//Add GUI elements and connectors
void MainWindow::createLayout() {
    wdg = new QWidget(this);
    nameLine = new QLineEdit;
    vlay = new QVBoxLayout(wdg);
    label = new QLabel(this);
    label->setText("Task 1\nInsert a message to print in debug");
    vlay->addWidget(label);
    vlay->addWidget(nameLine);
    btn1 = new QPushButton("Print Now!");
    vlay->addWidget(btn1);

    //connect slot entry point for first task
    connect(btn1, SIGNAL(clicked(bool)), this, SLOT(createDebugTask()));

    label2 = new QLabel(this);
    label2->setText("Task 2\nPress to search file C:/ESEMPIO.txt");
    vlay->addWidget(label2);
    btn2 = new QPushButton("Search");

    //connect slot entry point for second task
    connect(btn2, SIGNAL(clicked(bool)), this, SLOT(createResearchTask()));

    vlay->addWidget(btn2);
    setCentralWidget(wdg);
}

//First task, acquire text from GUI and send in debug
void MainWindow::createDebugTask()
{
    //check if a task is already running
    if (t1->getActive()) {
        QTimer::singleShot(5000, this, SLOT(queueDebug()));
    } else {
        t1->setDuration(10000);
        t1->setType(true);
        t1->startDebug(nameLine->text());
    }
}

//No text inserted warn
void MainWindow::warn()
{
    trayIco->showMessage("Warning", "Please insert a message to print");
}

//Second task, search for a file in specified directory
void MainWindow::createResearchTask()
{
    //check if a task is already running
    if (t1->getActive()) {
        QTimer::singleShot(1000, this, SLOT(queueSearch()));
    } else {
        t1->setDuration(30000);
        t1->setType(false);
        t1->startSearch();
    }
}

//Queue slot for search
void MainWindow::queueSearch()
{
    createResearchTask();
}

//Queue slot for debug
void MainWindow::queueDebug()
{
    createDebugTask();
}

//Initialize trayIcon
void MainWindow::createTrayIcon()
{
    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(minimizeAction);
    trayIconMenu->addAction(maximizeAction);
    trayIconMenu->addAction(restoreAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);

    trayIco = new QSystemTrayIcon();
    trayIco->setContextMenu(trayIconMenu);
}

//connect trayIcon actions
void MainWindow::createActions()
{
    minimizeAction = new QAction(tr("Mi&nimize"), this);
    connect(minimizeAction, &QAction::triggered, this, &QWidget::hide);

    maximizeAction = new QAction(tr("Ma&ximize"), this);
    connect(maximizeAction, &QAction::triggered, this, &QWidget::showMaximized);

    restoreAction = new QAction(tr("&Restore"), this);
    connect(restoreAction, &QAction::triggered, this, &QWidget::showNormal);

    quitAction = new QAction(tr("&Quit"), this);
    connect(quitAction, &QAction::triggered, qApp, &QCoreApplication::quit);

    connect(t1, SIGNAL(missingText()), this, SLOT(warn()));
}
