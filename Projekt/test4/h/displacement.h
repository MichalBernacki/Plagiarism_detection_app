#ifndef DISPLACEMENT_H
#define DISPLACEMENT_H

#include <QObject>

class Displacement : public QObject
{
    Q_OBJECT
public:
    explicit Displacement(QObject *parent = nullptr);
    void set(double value);
signals:
    void change(double val);
private:
    double value;
};

#endif // DISPLACEMENT_H
