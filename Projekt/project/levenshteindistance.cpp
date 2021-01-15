#include "levenshteindistance.h"

LevenshteinDistance::LevenshteinDistance()
{

}
float LevenshteinDistance::compare(std::string s1, std::string s2)
{
    size_t n = s1.size(), m = s2.size();
    int d[n+1][m+1];
    d[0][0]=0;
    for(size_t i = 1; i <= n; ++i)
        d[i][0] = i;
    for(size_t j = 1; j <= m; ++j)
        d[0][j] = j;
    char cost=0;
    for(size_t i = 1; i <= n; ++i)
        for(size_t j = 1; j <= m; ++j)
        {
            if( s1[i-1]==s2[j-1])
                cost=0;
            else
                cost=1;
            d[i][j]= std::min({ d[i-1][j]+1 , d[i][j-1]+1 , d[i-1][j-1]+cost});
        }
    return 1-((float)d[n][m])/(std::max(n,m));
}
