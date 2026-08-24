#ifndef SORTINGSTATISTICS_H
#define SORTINGSTATISTICS_H

#include <cstddef>

struct SortingStatistics
{
    std::size_t comparisons = 0;
    std::size_t swaps = 0;
    std::size_t moves = 0;
    double executionTimeMs = 0.0;

    void reset()
    {
        comparisons = 0;
        swaps = 0;
        moves = 0;
        executionTimeMs = 0.0;
    }
};

#endif // SORTINGSTATISTICS_H