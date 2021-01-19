#ifndef ACCELERATION_H
#define ACCELERATION_H

#include <QObject>

class Acceleration : public QObject
{
    Q_OBJECT
    Q_PROPERTY(double value READ get)
public:
    explicit Acceleration(QObject *parent = nullptr);
    Q_INVOKABLE double get();
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
