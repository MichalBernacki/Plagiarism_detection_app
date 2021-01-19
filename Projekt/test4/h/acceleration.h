#ifndef ACCELERATION_H
#define ACCELERATION_H

#include <QObject>

class Acceleration : public QObject
{
    Q_OBJECT
public:
    explicit Acceleration(QObject *parent = nullptr);
    double get();
private:
    bool hasFirstValue = false;
    bool hasSecondValue = false;
    bool hasThirdValue = false;
    int firstValue = 0;
    int secondValue = 0;
    int thirdValue = 0;
public slots:
    void onDisplace(double val);
};

#endif // ACCELERATION_H
