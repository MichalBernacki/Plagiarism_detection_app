#pragma once
#include <string>
#include <vector>
#include <algorithm>
class LevenshteinDistance
{
public:
    LevenshteinDistance();
    float compare(const std::string& s1, const std::string& s2);
};

