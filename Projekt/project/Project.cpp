#include "Project.h"

#include <iostream>

Project::Project(const std::string& path): m_Name{}, m_Path{path}{

    std::filesystem::directory_entry file(path);
    if(file.is_directory()){
        m_Name = file.path().filename();
        for(auto& p: std::filesystem::recursive_directory_iterator(file))
            if(p.is_regular_file())
                m_Files.emplace_back(p.path());
    }
}
