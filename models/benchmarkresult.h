#ifndef BENCHMARKRESULT_H
#define BENCHMARKRESULT_H

#include <QString>

struct BenchmarkResult
{
    QString algorithmName;

    std::size_t comparisons = 0;
    std::size_t swaps = 0;
    std::size_t moves = 0;

    double executionTimeMs = 0.0;
};

#endif // BENCHMARKRESULT_H