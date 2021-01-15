#pragma once
#include <fstream>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <string>
class Prepare
{
public:
    Prepare();
    std::string DeleteComments(std::string &fl);
private:
    const std::string newline = "\n";
    const std::string slcom = "//";
    const std::string comstart = "/*";
    const std::string comend = "*/";

};
