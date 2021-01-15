#ifndef PREPARE_H
#define PREPARE_H
#include <iostream>
#include <sstream>
#include <set>
#include <fstream>

class Prepare
{
public:
    Prepare(const std::string &filePath);
    std::string removeEmptyLines(std::string &str);
    std::string removeKeywords(std::string &str);
    std::set<std::string> keywords;
};

#endif // PREPARE_H
