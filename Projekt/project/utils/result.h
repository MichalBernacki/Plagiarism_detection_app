#ifndef RESULT_H
#define RESULT_H

#include <iostream>

#include "file.h"

struct Result{
    std::string algorithmName;
    float value;

    File* bestMatch1 = nullptr;
    File* bestMatch2 = nullptr;
};

#endif // RESULT_H
