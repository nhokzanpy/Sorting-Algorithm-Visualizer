#include "mergesort.h"

#include <chrono>
#include <string>
#include <vector>


std::vector<SortingStep> MergeSort::sort(
    std::vector<int> data,
    SortingStatistics &statistics
    )
{
    statistics.reset();

    std::vector<SortingStep> steps;

    const auto startTime =
        std::chrono::high_resolution_clock::now();

    if (!data.empty())
    {
        mergeSort(
            data,
            0,
            static_cast<int>(data.size()) - 1,
            steps,
            statistics
            );
    }

    SortingStep completeStep;
    completeStep.type =
        SortingStepType::Complete;
    completeStep.arrayState = data;
    completeStep.description =
        "Sorting complete";

    steps.push_back(
        completeStep
        );

    const auto endTime =
        std::chrono::high_resolution_clock::now();

    statistics.executionTimeMs =
        std::chrono::duration<double, std::milli>(
            endTime - startTime
            ).count();

    return steps;
}


void MergeSort::mergeSort(
    std::vector<int> &data,
    int left,
    int right,
    std::vector<SortingStep> &steps,
    SortingStatistics &statistics
    )
{
    if (left >= right)
    {
        return;
    }

    const int middle =
        left + (right - left) / 2;

    mergeSort(
        data,
        left,
        middle,
        steps,
        statistics
        );

    mergeSort(
        data,
        middle + 1,
        right,
        steps,
        statistics
        );

    merge(
        data,
        left,
        middle,
        right,
        steps,
        statistics
        );
}


void MergeSort::merge(
    std::vector<int> &data,
    int left,
    int middle,
    int right,
    std::vector<SortingStep> &steps,
    SortingStatistics &statistics
    )
{
    std::vector<int> leftPart(
        data.begin() + left,
        data.begin() + middle + 1
        );

    std::vector<int> rightPart(
        data.begin() + middle + 1,
        data.begin() + right + 1
        );

    int i = 0;
    int j = 0;
    int k = left;

    while (
        i < static_cast<int>(leftPart.size()) &&
        j < static_cast<int>(rightPart.size())
        )
    {
        ++statistics.comparisons;

        SortingStep compareStep;
        compareStep.type =
            SortingStepType::Compare;
        compareStep.arrayState = data;
        compareStep.firstIndex = left + i;
        compareStep.secondIndex =
            middle + 1 + j;
        compareStep.description =
            "Comparing " +
            std::to_string(leftPart[i]) +
            " and " +
            std::to_string(rightPart[j]);

        steps.push_back(
            compareStep
            );

        if (leftPart[i] <= rightPart[j])
        {
            data[k] = leftPart[i];

            ++i;
        }
        else
        {
            data[k] = rightPart[j];

            ++j;
        }

        ++statistics.moves;

        SortingStep moveStep;
        moveStep.type =
            SortingStepType::Move;
        moveStep.arrayState = data;
        moveStep.firstIndex = k;
        moveStep.secondIndex = k;
        moveStep.description =
            "Place " +
            std::to_string(data[k]) +
            " at position " +
            std::to_string(k);

        steps.push_back(
            moveStep
            );

        ++k;
    }

    while (
        i < static_cast<int>(leftPart.size())
        )
    {
        data[k] = leftPart[i];

        ++statistics.moves;

        SortingStep moveStep;
        moveStep.type =
            SortingStepType::Move;
        moveStep.arrayState = data;
        moveStep.firstIndex = k;
        moveStep.secondIndex = k;
        moveStep.description =
            "Place " +
            std::to_string(data[k]) +
            " at position " +
            std::to_string(k);

        steps.push_back(
            moveStep
            );

        ++i;
        ++k;
    }

    while (
        j < static_cast<int>(rightPart.size())
        )
    {
        data[k] = rightPart[j];

        ++statistics.moves;

        SortingStep moveStep;
        moveStep.type =
            SortingStepType::Move;
        moveStep.arrayState = data;
        moveStep.firstIndex = k;
        moveStep.secondIndex = k;
        moveStep.description =
            "Place " +
            std::to_string(data[k]) +
            " at position " +
            std::to_string(k);

        steps.push_back(
            moveStep
            );

        ++j;
        ++k;
    }

    SortingStep mergeStep;
    mergeStep.type =
        SortingStepType::Merge;
    mergeStep.arrayState = data;
    mergeStep.firstIndex = left;
    mergeStep.secondIndex = right;
    mergeStep.description =
        "Merged range [" +
        std::to_string(left) +
        ", " +
        std::to_string(right) +
        "]";

    steps.push_back(
        mergeStep
        );
}