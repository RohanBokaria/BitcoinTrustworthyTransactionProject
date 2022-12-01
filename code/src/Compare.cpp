#include "Compare.h"

bool Compare::operator()(std::pair<int,int> p1, std::pair<int, int> p2) {
    return p1.second > p2.second;
}