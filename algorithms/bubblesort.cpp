#include "bubblesort.h"

#include <chrono>
#include <string>
#include <utility>

std::vector<SortingStep> BubbleSort::sort(
    std::vector<int> data,
    SortingStatistics &statistics
    )
{
    statistics.reset();

    std::vector<SortingStep> steps;

    const auto startTime = std::chrono::high_resolution_clock::now();

    const int n = static_cast<int>(data.size());

    for (int i = 0; i < n - 1; ++i)
    {
        bool swapped = false;

        for (int j = 0; j < n - i - 1; ++j)
        {
            ++statistics.comparisons;

            SortingStep compareStep;
            compareStep.type = SortingStepType::Compare;
            compareStep.arrayState = data;
            compareStep.firstIndex = j;
            compareStep.secondIndex = j + 1;
            compareStep.description =
                "Comparing " +
                std::to_string(data[j]) +
                " and " +
                std::to_string(data[j + 1]);

            steps.push_back(compareStep);

            if (data[j] > data[j + 1])
            {
                const int leftValue = data[j];
                const int rightValue = data[j + 1];

                std::swap(data[j], data[j + 1]);

                ++statistics.swaps;
                statistics.moves += 3;

                swapped = true;

                SortingStep swapStep;
                swapStep.type = SortingStepType::Swap;
                swapStep.arrayState = data;
                swapStep.firstIndex = j;
                swapStep.secondIndex = j + 1;
                swapStep.description =
                    "Swap " +
                    std::to_string(leftValue) +
                    " and " +
                    std::to_string(rightValue);

                steps.push_back(swapStep);
            }
        }

        SortingStep sortedStep;
        sortedStep.type = SortingStepType::MarkSorted;
        sortedStep.arrayState = data;
        sortedStep.firstIndex = n - i - 1;
        sortedStep.description =
            "Position " +
            std::to_string(n - i - 1) +
            " is sorted";

        steps.push_back(sortedStep);

        if (!swapped)
        {
            break;
        }
    }

    SortingStep completeStep;
    completeStep.type = SortingStepType::Complete;
    completeStep.arrayState = data;
    completeStep.description = "Sorting complete";

    steps.push_back(completeStep);

    const auto endTime = std::chrono::high_resolution_clock::now();

    statistics.executionTimeMs =
        std::chrono::duration<double, std::milli>(
            endTime - startTime
            ).count();

    return steps;
}