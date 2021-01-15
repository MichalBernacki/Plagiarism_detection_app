#include "prepare.h"

Prepare::Prepare()
{

}
std::string Prepare::DeleteComments(std::string &fl)
{
    std::istringstream file(fl);
    std::string code;
    getline(file,code,'\0');
    while(code.find(comstart) != std::string::npos)
    {
        size_t b = code.find(comstart);
        code.erase(b, (code.find(comend,b)-b)+2);
    }
    while(code.find(slcom) != std::string::npos)
    {
        size_t b = code.find(slcom);
        code.erase(b, (code.find(newline,b)-b));
    }
    return code;
}
