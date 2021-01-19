#ifndef DISPLACEMENT_H
#define DISPLACEMENT_H

#include <QObject>

class Displacement : public QObject
{
    Q_OBJECT
    Q_PROPERTY(double value WRITE set NOTIFY change)

public:
    explicit Displacement(QObject *parent = nullptr);
    Q_INVOKABLE void set(double value);
signals:
    void change(double val);
private:
    double value;
};

#endif // DISPLACEMENT_H
