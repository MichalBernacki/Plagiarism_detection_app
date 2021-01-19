#include "counter.h"

#include <QDebug>

Counter::Counter(QObject *parent) : QObject(parent), value(0)
{
    qDebug() << "Counter::Counter(QObject *)";
}

void Counter::initialise(int v)
{
    qDebug() << "Counter::initialise(int)";
    qDebug() << v;
    value = v;

    emit changed();
}

int Counter::get() const
{
    return value;
}

void Counter::set(int v)
{
    qDebug() << "Counter::set(int)";

    value = v;

    emit changed();
}

void Counter::increment()
{
    qDebug() << "Counter::increment()";

    value += 10;

    emit changed();
}

