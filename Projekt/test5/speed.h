#ifndef SPEED_H
#define SPEED_H

#include <QObject>

class Speed : public QObject
{
    Q_OBJECT
    Q_PROPERTY(double value READ get)

public:
    explicit Speed(QObject *parent = nullptr);
    Q_INVOKABLE double get();
private:
    bool hasFirstValue = false;
    bool hasSecondValue = false;
    int firstValue = 0;
    int secondValue = 0;
public slots:
    void onDisplace(double val);
};

#endif // SPEED_H
