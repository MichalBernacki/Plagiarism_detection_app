#include "speed.h"

Speed::Speed(QObject *parent) : QObject(parent)
{

}
void Speed::onDisplace(double val)
{
    if(!this->hasFirstValue)
    {
        this->firstValue = val;
        this->hasFirstValue=true;
    }
    else if(!this->hasSecondValue)
    {
        this->secondValue = val;
        this->hasSecondValue=true;
    }
    else
    {
        this->firstValue=this->secondValue;
        this->secondValue=val;
    }
}
double Speed::get()
{
    if(this->hasFirstValue && this->hasSecondValue)
    {
            return (this->secondValue-this->firstValue);
    }
    return 0.0;
}

