#include "studentsortrunner.h"

#include "../algorithms/bubblesort.h"
#include "../algorithms/selectionsort.h"
#include "../algorithms/insertionsort.h"
#include "../algorithms/mergesort.h"

#include "../models/sortingstatistics.h"


StudentSortResult StudentSortRunner::run(
    const std::vector<int> &data,
    const QString &algorithmName
    )
{
    StudentSortResult result;

    result.algorithmName =
        algorithmName;

    result.inputData =
        data;


    SortingStatistics statistics;

    std::vector<SortingStep> steps;


    if (algorithmName == "Bubble Sort")
    {
        steps =
            BubbleSort::sort(
                data,
                statistics
                );
    }
    else if (
        algorithmName ==
        "Selection Sort"
        )
    {
        steps =
            SelectionSort::sort(
                data,
                statistics
                );
    }
    else if (
        algorithmName ==
        "Insertion Sort"
        )
    {
        steps =
            InsertionSort::sort(
                data,
                statistics
                );
    }
    else if (
        algorithmName ==
        "Merge Sort"
        )
    {
        steps =
            MergeSort::sort(
                data,
                statistics
                );
    }
    else
    {
        result.completed =
            false;

        return result;
    }


    if (!steps.empty())
    {
        result.sortedData =
            steps.back().arrayState;

        result.completed =
            true;
    }


    result.comparisons =
        statistics.comparisons;

    result.swaps =
        statistics.swaps;

    result.moves =
        statistics.moves;

    result.executionTimeMs =
        statistics.executionTimeMs;


    return result;
}