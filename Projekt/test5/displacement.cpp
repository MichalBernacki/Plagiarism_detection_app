#include "displacement.h"

Displacement::Displacement(QObject *parent) : QObject(parent)
{

}
void Displacement::set(double value)
{
    this->value = value;
    emit change(this->value);
}
