#ifndef MULTISIZEBENCHMARKRUNNER_H
#define MULTISIZEBENCHMARKRUNNER_H

#include <vector>

#include "../models/multisizebenchmarkresult.h"

class MultiSizeBenchmarkRunner
{
public:
    static std::vector<MultiSizeBenchmarkResult> run(
        const std::vector<int> &sizes
        );
};

#endif // MULTISIZEBENCHMARKRUNNER_H