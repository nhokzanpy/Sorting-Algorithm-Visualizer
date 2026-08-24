#ifndef INSERTIONSORT_H
#define INSERTIONSORT_H

#include <vector>

#include "../models/sortingstep.h"
#include "../models/sortingstatistics.h"

class InsertionSort
{
public:
    static std::vector<SortingStep> sort(
        std::vector<int> data,
        SortingStatistics &statistics
        );
};

#endif // INSERTIONSORT_H