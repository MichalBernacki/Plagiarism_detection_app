#ifndef COUNTER_H
#define COUNTER_H

#include <QObject>

class Counter : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int value READ get WRITE set NOTIFY changed)
public:
    explicit Counter(QObject *parent = nullptr);

    void initialise(int v);

    int get() const;
    void set(int v);

signals:
    void changed();

public slots:
    void increment();

private:
    int value;
};

#endif // COUNTER_H
