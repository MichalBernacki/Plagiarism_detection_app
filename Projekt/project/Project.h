#ifndef PROJECT_H
#define PROJECT_H

#include <vector>
#include <filesystem>

#include "File.h"

class Project
{
public:
    std::vector<File> m_Files;

    std::string m_Path;

public:
    Project(const std::string& path);
};

#endif // PROJECT_H
