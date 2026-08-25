#include "benchmarkrunner.h"

#include "../algorithms/bubblesort.h"
#include "../algorithms/selectionsort.h"
#include "../algorithms/insertionsort.h"
#include "../algorithms/mergesort.h"

#include "../models/sortingstatistics.h"


std::vector<BenchmarkResult> BenchmarkRunner::run(
    const std::vector<int> &data
    )
{
    std::vector<BenchmarkResult> results;

    // =====================================================
    // Bubble Sort
    // =====================================================

    {
        SortingStatistics statistics;

        BubbleSort::sort(
            data,
            statistics
            );

        BenchmarkResult result;

        result.algorithmName =
            "Bubble Sort";

        result.comparisons =
            statistics.comparisons;

        result.swaps =
            statistics.swaps;

        result.moves =
            statistics.moves;

        result.executionTimeMs =
            statistics.executionTimeMs;

        results.push_back(
            result
            );
    }


    // =====================================================
    // Selection Sort
    // =====================================================

    {
        SortingStatistics statistics;

        SelectionSort::sort(
            data,
            statistics
            );

        BenchmarkResult result;

        result.algorithmName =
            "Selection Sort";

        result.comparisons =
            statistics.comparisons;

        result.swaps =
            statistics.swaps;

        result.moves =
            statistics.moves;

        result.executionTimeMs =
            statistics.executionTimeMs;

        results.push_back(
            result
            );
    }


    // =====================================================
    // Insertion Sort
    // =====================================================

    {
        SortingStatistics statistics;

        InsertionSort::sort(
            data,
            statistics
            );

        BenchmarkResult result;

        result.algorithmName =
            "Insertion Sort";

        result.comparisons =
            statistics.comparisons;

        result.swaps =
            statistics.swaps;

        result.moves =
            statistics.moves;

        result.executionTimeMs =
            statistics.executionTimeMs;

        results.push_back(
            result
            );
    }


    // =====================================================
    // Merge Sort
    // =====================================================

    {
        SortingStatistics statistics;

        MergeSort::sort(
            data,
            statistics
            );

        BenchmarkResult result;

        result.algorithmName =
            "Merge Sort";

        result.comparisons =
            statistics.comparisons;

        result.swaps =
            statistics.swaps;

        result.moves =
            statistics.moves;

        result.executionTimeMs =
            statistics.executionTimeMs;

        results.push_back(
            result
            );
    }


    return results;
}