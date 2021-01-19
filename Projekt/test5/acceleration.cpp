#include "acceleration.h"

Acceleration::Acceleration(QObject *parent) : QObject(parent)
{

}
void Acceleration::onDisplace(double val)
{
    if(!this->hasFirstValue) {
            this->firstValue = val;
            this->hasFirstValue=true;
    }
    else if(!this->hasSecondValue) {
            this->secondValue = val;
            this->hasSecondValue=true;
            return;
    }
    else if(!this->hasThirdValue) {
            this->thirdValue = val;
            this->hasThirdValue=true;
    }
    else
    {
            this->firstValue=this->secondValue;
            this->secondValue=this->thirdValue;
            this->thirdValue=val;
    }
}

double Acceleration::get() {
    if(this->hasFirstValue && this->hasSecondValue && this->hasThirdValue)
    {
        return ((this->thirdValue-this->secondValue)-(this->secondValue-this->firstValue));
    }
    return 0.0;
}
