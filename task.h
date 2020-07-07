#ifndef TASK_H
#define TASK_H

#include <QObject>
#include <QTimer>
#include <QSystemTrayIcon>

class task : public QObject
{
    Q_OBJECT
public:
    explicit task(QObject *parent = nullptr);

    //getters and setters
    void setDuration(int duration);
    int getDuration();
    void setType(bool type);
    bool getType();
    bool getActive();
    void setActive(bool val);

    //entry points
    void startDebug(QString text);
    void startSearch();

signals:
    void missingText();

public slots:
    void print();
    void output();

private:
    void setText(QString text);
    QString getText();
    int counter;
    bool isActive = false;
    QTimer *timerFile;
    QTimer *timer;
    int duration;
    QString debugText;
    bool type;
};

#endif // TASK_H
