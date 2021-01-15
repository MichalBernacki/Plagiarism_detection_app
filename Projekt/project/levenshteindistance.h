#pragma once
#include <string>
#include <vector>
#include <algorithm>
class LevenshteinDistance
{
public:
    LevenshteinDistance();
    float compare(std::string s1, std::string s2);
};

