#include "prepare.h"

Prepare::Prepare(const std::string &filePath)
{
    std::ifstream in(filePath);
    std::string line;
    while(getline(in,line))
    {
        keywords.insert(line);
    }
}

void Prepare::removeEmptyLines(std::string &str)
{
    std::string strtemp;
    std::istringstream iss (str);
    std::string sout;

    while(getline(iss,strtemp))
    {
        while(strtemp.length()==0)
            getline(iss,strtemp);

        sout+=("\n"+strtemp);
    }
    str = sout;
}

void Prepare::removeKeywords(std::string &str)
{
    std::string sout=str;
    std::set<std::string>::iterator it = keywords.begin();
    while(it!=keywords.end())
    {
        if(sout.find(*it)!=std::string::npos) // check if keyword even exists in code
        {
            size_t p = -1;

            std::string tempWord = *it;
            while ((p = sout.find(*it)) != std::string::npos)
                sout.replace(p, tempWord.length(), "");
        }
        it++;
    }
    str = sout;
}


void Prepare::DeleteComments(std::string &fl)
{
    std::istringstream file(fl);
    std::string code;
    getline(file,code,'\0');
    while(code.find(comstart) != std::string::npos)
    {
        unsigned long long b = code.find(comstart);
        code.erase(b, (code.find(comend,b)-b)+2);
    }
    while(code.find(slcom) != std::string::npos)
    {
        unsigned long long b = code.find(slcom);
        code.erase(b, (code.find(newline,b)-b));
    }
    fl = code;
}
