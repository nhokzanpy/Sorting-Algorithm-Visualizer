#include "insertionsort.h"

#include <chrono>
#include <string>

std::vector<SortingStep> InsertionSort::sort(
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

    for (int i = 1; i < n; ++i)
    {
        const int key = data[i];

        int j = i - 1;

        while (j >= 0)
        {
            ++statistics.comparisons;

            SortingStep compareStep;
            compareStep.type =
                SortingStepType::Compare;
            compareStep.arrayState = data;
            compareStep.firstIndex = j;
            compareStep.secondIndex = j + 1;
            compareStep.description =
                "Comparing " +
                std::to_string(data[j]) +
                " and " +
                std::to_string(key);

            steps.push_back(compareStep);

            if (data[j] <= key)
            {
                break;
            }

            data[j + 1] = data[j];

            ++statistics.moves;

            SortingStep moveStep;
            moveStep.type =
                SortingStepType::Move;
            moveStep.arrayState = data;
            moveStep.firstIndex = j;
            moveStep.secondIndex = j + 1;
            moveStep.description =
                "Move " +
                std::to_string(data[j]) +
                " to the right";

            steps.push_back(moveStep);

            --j;
        }

        data[j + 1] = key;

        ++statistics.moves;

        SortingStep insertStep;
        insertStep.type =
            SortingStepType::Move;
        insertStep.arrayState = data;
        insertStep.firstIndex = j + 1;
        insertStep.secondIndex = i;
        insertStep.description =
            "Insert " +
            std::to_string(key) +
            " at position " +
            std::to_string(j + 1);

        steps.push_back(insertStep);

        SortingStep sortedStep;
        sortedStep.type =
            SortingStepType::MarkSorted;
        sortedStep.arrayState = data;
        sortedStep.firstIndex = i;
        sortedStep.description =
            "First " +
            std::to_string(i + 1) +
            " elements are sorted";

        steps.push_back(sortedStep);
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