#ifndef STUDENTSORTRESULT_H
#define STUDENTSORTRESULT_H

#include <QString>
#include <vector>

struct StudentSortResult
{
    QString algorithmName;

    std::vector<int> inputData;
    std::vector<int> sortedData;

    std::size_t comparisons = 0;
    std::size_t swaps = 0;
    std::size_t moves = 0;

    double executionTimeMs = 0.0;

    bool completed = false;
};

#endif // STUDENTSORTRESULT_H