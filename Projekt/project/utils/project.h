#ifndef PROJECT_H
#define PROJECT_H

#include <vector>
#include <filesystem>

#include "file.h"

class NotADirectory : public std::exception{
public:
    const char* what() const noexcept override{
        return "Selected file is not a directory";
    }
};

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

    bool operator==( const Project &other ) const { return m_Path == other.m_Path; }
};

template<>
struct std::hash<Project>{
    size_t operator()(const Project& project) const{
        return std::hash<std::string>()(project.GetPath());
    }
};

#endif // PROJECT_H
