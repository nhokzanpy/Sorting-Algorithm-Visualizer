#ifndef BENCHMARKRUNNER_H
#define BENCHMARKRUNNER_H

#include <vector>

#include "../models/benchmarkresult.h"

class BenchmarkRunner
{
public:
    static std::vector<BenchmarkResult> run(
        const std::vector<int> &data
        );
};

#endif // BENCHMARKRUNNER_H