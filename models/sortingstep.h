#ifndef SORTINGSTEP_H
#define SORTINGSTEP_H

#include <vector>
#include <string>

enum class SortingStepType
{
    Compare,
    Swap,
    Move,
    MarkSorted,
    Merge,
    Complete
};

struct SortingStep
{
    SortingStepType type = SortingStepType::Compare;

    std::vector<int> arrayState;

    int firstIndex = -1;
    int secondIndex = -1;

    std::string description;
};

#endif // SORTINGSTEP_H