#ifndef MULTISIZEBENCHMARKRESULT_H
#define MULTISIZEBENCHMARKRESULT_H

#include <QString>
#include <cstddef>

struct MultiSizeBenchmarkResult
{
    QString algorithmName;

    int inputSize = 0;

    std::size_t comparisons = 0;
    std::size_t swaps = 0;
    std::size_t moves = 0;

    double executionTimeMs = 0.0;
};

#endif // MULTISIZEBENCHMARKRESULT_H