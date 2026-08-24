#ifndef MERGESORT_H
#define MERGESORT_H

#include <vector>

#include "../models/sortingstep.h"
#include "../models/sortingstatistics.h"

class MergeSort
{
public:
    static std::vector<SortingStep> sort(
        std::vector<int> data,
        SortingStatistics &statistics
        );

private:
    static void mergeSort(
        std::vector<int> &data,
        int left,
        int right,
        std::vector<SortingStep> &steps,
        SortingStatistics &statistics
        );

    static void merge(
        std::vector<int> &data,
        int left,
        int middle,
        int right,
        std::vector<SortingStep> &steps,
        SortingStatistics &statistics
        );
};

#endif // MERGESORT_H