#include "simplealg.h"
#include "stdio.h"
SimpleAlg::SimpleAlg()
{

}
float SimpleAlg::compare(std::string s1, std::string s2)
{
    std::istringstream iss1 (s1);
    std::istringstream iss2 (s2);

    std::set<std::string> set2;

    std::string line;

    while(getline(iss2,line))
    {
       set2.insert(line);
    }

    int sameLines=0;
    int lineCounter=0;
    while(getline(iss1,line))
    {
       std::set<std::string>::iterator tempit;
       if((tempit=set2.find(line))!=set2.end())
       {
           set2.erase(tempit);
           sameLines++;
       }
         lineCounter++;
    }
    float res=(float)sameLines/(float)lineCounter;

    return res;
}
