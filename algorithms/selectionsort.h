#ifndef SELECTIONSORT_H
#define SELECTIONSORT_H

#include <vector>

#include "../models/sortingstep.h"
#include "../models/sortingstatistics.h"

class SelectionSort
{
public:
    static std::vector<SortingStep> sort(
        std::vector<int> data,
        SortingStatistics &statistics
        );
};

#endif // SELECTIONSORT_H