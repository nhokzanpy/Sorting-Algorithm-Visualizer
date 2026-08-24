#include "selectionsort.h"

#include <chrono>
#include <string>
#include <utility>

std::vector<SortingStep> SelectionSort::sort(
    std::vector<int> data,
    SortingStatistics &statistics
    )
{
    statistics.reset();

    std::vector<SortingStep> steps;

    const auto startTime =
        std::chrono::high_resolution_clock::now();

    const int n =
        static_cast<int>(data.size());

    for (int i = 0; i < n - 1; ++i)
    {
        int minIndex = i;

        for (int j = i + 1; j < n; ++j)
        {
            ++statistics.comparisons;

            SortingStep compareStep;
            compareStep.type =
                SortingStepType::Compare;
            compareStep.arrayState = data;
            compareStep.firstIndex = minIndex;
            compareStep.secondIndex = j;
            compareStep.description =
                "Comparing " +
                std::to_string(data[minIndex]) +
                " and " +
                std::to_string(data[j]);

            steps.push_back(compareStep);

            if (data[j] < data[minIndex])
            {
                minIndex = j;
            }
        }

        if (minIndex != i)
        {
            const int leftValue = data[i];
            const int rightValue = data[minIndex];

            std::swap(
                data[i],
                data[minIndex]
                );

            ++statistics.swaps;
            statistics.moves += 3;

            SortingStep swapStep;
            swapStep.type =
                SortingStepType::Swap;
            swapStep.arrayState = data;
            swapStep.firstIndex = i;
            swapStep.secondIndex = minIndex;
            swapStep.description =
                "Swap " +
                std::to_string(leftValue) +
                " and " +
                std::to_string(rightValue);

            steps.push_back(swapStep);
        }

        SortingStep sortedStep;
        sortedStep.type =
            SortingStepType::MarkSorted;
        sortedStep.arrayState = data;
        sortedStep.firstIndex = i;
        sortedStep.description =
            "Position " +
            std::to_string(i) +
            " is sorted";

        steps.push_back(sortedStep);
    }

    if (n > 0)
    {
        SortingStep lastSortedStep;
        lastSortedStep.type =
            SortingStepType::MarkSorted;
        lastSortedStep.arrayState = data;
        lastSortedStep.firstIndex = n - 1;
        lastSortedStep.description =
            "Position " +
            std::to_string(n - 1) +
            " is sorted";

        steps.push_back(lastSortedStep);
    }

    SortingStep completeStep;
    completeStep.type =
        SortingStepType::Complete;
    completeStep.arrayState = data;
    completeStep.description =
        "Sorting complete";

    steps.push_back(completeStep);

    const auto endTime =
        std::chrono::high_resolution_clock::now();

    statistics.executionTimeMs =
        std::chrono::duration<double, std::milli>(
            endTime - startTime
            ).count();

    return steps;
}