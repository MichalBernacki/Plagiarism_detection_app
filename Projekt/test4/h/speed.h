#ifndef SPEED_H
#define SPEED_H

#include <QObject>

class Speed : public QObject
{
    Q_OBJECT
public:
    explicit Speed(QObject *parent = nullptr);
    double get();
private:
    bool hasFirstValue = false;
    bool hasSecondValue = false;
    int firstValue = 0;
    int secondValue = 0;
public slots:
    void onDisplace(double val);
};

#endif // SPEED_H
