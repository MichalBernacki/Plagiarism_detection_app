#ifndef RESULT_H
#define RESULT_H

#include <iostream>

#include "file.h"

struct Result{
    Result(const std::string& name) : algorithmName{name}, value{0}, bestMatchValue{-1} {}

    std::string algorithmName;
    float value;

    float bestMatchValue;
    const File* bestMatch1 = nullptr;
    const File* bestMatch2 = nullptr;
};

#endif // RESULT_H
