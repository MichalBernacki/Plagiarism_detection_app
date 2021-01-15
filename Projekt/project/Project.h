#ifndef PROJECT_H
#define PROJECT_H

#include <vector>
#include <filesystem>

#include "File.h"

class Project
{
private:
    std::vector<File> m_Files;

    std::string m_Name;
    std::string m_Path;

public:
    Project(const std::string& path);

    const std::vector<File>& GetFiles() const { return m_Files; }
    std::string GetName() const { return m_Name; }
    std::string GetPath() const { return m_Path; }
};

#endif // PROJECT_H
