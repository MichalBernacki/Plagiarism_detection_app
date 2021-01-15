#ifndef FILE_H
#define FILE_H

#include <string>
#include <filesystem>

class File
{
public:
    File(std::filesystem::path path);

    std::string m_Name;
    std::string m_Path;
    std::string m_OriginalContent;
};

#endif // FILE_H
