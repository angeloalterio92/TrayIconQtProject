#include "task.h"
#include "mainwindow.h"
#include <QDebug>
#include <QDir>

//Created to stop loops
const int loopCounter = 3;

task::task(QObject *parent) : QObject(parent)
{

}

//Getters and setters
void task::setDuration(int dur)
{
    duration = dur;
}

int task::getDuration()
{
    return duration;
}

void task::setType(bool typ)
{
    type = typ;
}

bool task::getType()
{
    return type;
}

bool task::getActive()
{
    return isActive;
}

void task::setActive(bool val)
{
    isActive = val;
}

void task::setText(QString text)
{
    debugText = text;
}

QString task::getText()
{
    return debugText;
}

//Entry point debug task
void task::startDebug(QString text)
{
    //start timer
    timer = new QTimer(this);
    setText(text);
    counter = 0;

    //connect timer signals to action
    connect(timer, SIGNAL(timeout()), this, SLOT(print()));
    timer->start(duration);

    //variable to avoid simultaneous task
    setActive(true);
}


//Entry point search task
void task::startSearch()
{
    //start timer
    timerFile = new QTimer(this);
    counter = 0;

    //connect timer signals to action
    connect(timerFile, SIGNAL(timeout()), this, SLOT(output()));
    timerFile->start(duration);

    //variable to avoid simultaneous task
    setActive(true);
}

//slot debug
void task::print()
{
    ++counter;
    //exit condition for loop
    if (counter >= loopCounter) {
        timer->stop();
        setActive(false);
    } else if (debugText == ""){ //No text inserted! Raise a warning via trayIcon
        timer->stop();
        setActive(false);
        emit missingText(); //emit signal for TrayIcon
    } else {
        //print message in debug
        qDebug() << debugText;
    }
}

void task::output()
{
    ++counter;
    //exit condition for loop
    if (counter >= loopCounter) {
        timerFile->stop();
        setActive(false);
    } else {
        //search file in specified diretory
        QDir directory("C:/");
        QStringList file = directory.entryList(QStringList() << "ESEMPIO.txt",QDir::Files);
        if (file.length() == 0) {
            qDebug() << "File not found";
        }
    }
}
