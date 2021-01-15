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
private:
    std::string DeleteComments(std::string &fl);
    const std::string newline = "\n";
    const std::string comstart = "/*";
    const std::string slcom = "//";
    const std::string comend = "*/";

};
#endif // PREPARE_H
#include <string>
#include <algorithm>