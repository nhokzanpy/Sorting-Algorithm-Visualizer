#ifndef BUBBLESORT_H
#define BUBBLESORT_H

#include <vector>

#include "../models/sortingstep.h"
#include "../models/sortingstatistics.h"

class BubbleSort
{
public:
    static std::vector<SortingStep> sort(
        std::vector<int> data,
        SortingStatistics &statistics
        );
};

#endif // BUBBLESORT_H