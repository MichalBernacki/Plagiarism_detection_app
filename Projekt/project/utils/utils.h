#ifndef UTILS_H
#define UTILS_H

#include "utils_global.h"

#include <unordered_set>
#include <assert.h>

template<typename T>
const T& SetGetNth(const std::unordered_set<T>& set, size_t n){
    assert (n < set.size() );

    auto it = set.begin();
    std::advance(it, n);
    return *it;
}

class UTILS_EXPORT Utils
{
public:
    Utils();
};

#endif // UTILS_H
