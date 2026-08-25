#include "multisizebenchmarkrunner.h"

#include <algorithm>
#include <chrono>
#include <random>
#include <vector>


namespace
{

// =========================================================
// Random Data
// =========================================================

std::vector<int> generateRandomData(
    int size
    )
{
    std::vector<int> data;

    data.reserve(
        static_cast<std::size_t>(size)
        );


    static std::mt19937 generator(
        std::random_device{}()
        );

    std::uniform_int_distribution<int> distribution(
        1,
        10000
        );


    for (int i = 0; i < size; ++i)
    {
        data.push_back(
            distribution(generator)
            );
    }


    return data;
}


// =========================================================
// Bubble Sort Benchmark
// =========================================================

MultiSizeBenchmarkResult benchmarkBubbleSort(
    const std::vector<int> &source
    )
{
    std::vector<int> data =
        source;


    MultiSizeBenchmarkResult result;

    result.algorithmName =
        "Bubble Sort";

    result.inputSize =
        static_cast<int>(
            data.size()
            );


    const auto start =
        std::chrono::high_resolution_clock::now();


    const int n =
        static_cast<int>(
            data.size()
            );


    for (int i = 0; i < n - 1; ++i)
    {
        bool swapped =
            false;


        for (
            int j = 0;
            j < n - i - 1;
            ++j
            )
        {
            ++result.comparisons;


            if (
                data[j] >
                data[j + 1]
                )
            {
                std::swap(
                    data[j],
                    data[j + 1]
                    );

                ++result.swaps;

                // One swap is treated as
                // three data movements.
                result.moves += 3;

                swapped =
                    true;
            }
        }


        if (!swapped)
        {
            break;
        }
    }


    const auto end =
        std::chrono::high_resolution_clock::now();


    result.executionTimeMs =
        std::chrono::duration<double, std::milli>(
            end - start
            ).count();


    return result;
}


// =========================================================
// Selection Sort Benchmark
// =========================================================

MultiSizeBenchmarkResult benchmarkSelectionSort(
    const std::vector<int> &source
    )
{
    std::vector<int> data =
        source;


    MultiSizeBenchmarkResult result;

    result.algorithmName =
        "Selection Sort";

    result.inputSize =
        static_cast<int>(
            data.size()
            );


    const auto start =
        std::chrono::high_resolution_clock::now();


    const int n =
        static_cast<int>(
            data.size()
            );


    for (int i = 0; i < n - 1; ++i)
    {
        int minIndex =
            i;


        for (
            int j = i + 1;
            j < n;
            ++j
            )
        {
            ++result.comparisons;


            if (
                data[j] <
                data[minIndex]
                )
            {
                minIndex =
                    j;
            }
        }


        if (
            minIndex !=
            i
            )
        {
            std::swap(
                data[i],
                data[minIndex]
                );

            ++result.swaps;

            result.moves += 3;
        }
    }


    const auto end =
        std::chrono::high_resolution_clock::now();


    result.executionTimeMs =
        std::chrono::duration<double, std::milli>(
            end - start
            ).count();


    return result;
}


// =========================================================
// Insertion Sort Benchmark
// =========================================================

MultiSizeBenchmarkResult benchmarkInsertionSort(
    const std::vector<int> &source
    )
{
    std::vector<int> data =
        source;


    MultiSizeBenchmarkResult result;

    result.algorithmName =
        "Insertion Sort";

    result.inputSize =
        static_cast<int>(
            data.size()
            );


    const auto start =
        std::chrono::high_resolution_clock::now();


    const int n =
        static_cast<int>(
            data.size()
            );


    for (int i = 1; i < n; ++i)
    {
        const int key =
            data[i];

        int j =
            i - 1;


        while (j >= 0)
        {
            ++result.comparisons;


            if (
                data[j] <=
                key
                )
            {
                break;
            }


            data[j + 1] =
                data[j];

            ++result.moves;

            --j;
        }


        data[j + 1] =
            key;

        ++result.moves;
    }


    const auto end =
        std::chrono::high_resolution_clock::now();


    result.executionTimeMs =
        std::chrono::duration<double, std::milli>(
            end - start
            ).count();


    return result;
}


// =========================================================
// Merge Sort Helpers
// =========================================================

void mergeRanges(
    std::vector<int> &data,
    int left,
    int middle,
    int right,
    MultiSizeBenchmarkResult &result
    )
{
    const int leftSize =
        middle - left + 1;

    const int rightSize =
        right - middle;


    std::vector<int> leftData(
        leftSize
        );

    std::vector<int> rightData(
        rightSize
        );


    for (int i = 0; i < leftSize; ++i)
    {
        leftData[i] =
            data[left + i];

        ++result.moves;
    }


    for (int i = 0; i < rightSize; ++i)
    {
        rightData[i] =
            data[middle + 1 + i];

        ++result.moves;
    }


    int leftIndex =
        0;

    int rightIndex =
        0;

    int dataIndex =
        left;


    while (
        leftIndex < leftSize &&
        rightIndex < rightSize
        )
    {
        ++result.comparisons;


        if (
            leftData[leftIndex] <=
            rightData[rightIndex]
            )
        {
            data[dataIndex] =
                leftData[leftIndex];

            ++leftIndex;
        }
        else
        {
            data[dataIndex] =
                rightData[rightIndex];

            ++rightIndex;
        }


        ++result.moves;

        ++dataIndex;
    }


    while (
        leftIndex <
        leftSize
        )
    {
        data[dataIndex] =
            leftData[leftIndex];

        ++result.moves;

        ++leftIndex;
        ++dataIndex;
    }


    while (
        rightIndex <
        rightSize
        )
    {
        data[dataIndex] =
            rightData[rightIndex];

        ++result.moves;

        ++rightIndex;
        ++dataIndex;
    }
}


void mergeSortRecursive(
    std::vector<int> &data,
    int left,
    int right,
    MultiSizeBenchmarkResult &result
    )
{
    if (
        left >=
        right
        )
    {
        return;
    }


    const int middle =
        left +
        (
            right - left
            ) /
            2;


    mergeSortRecursive(
        data,
        left,
        middle,
        result
        );


    mergeSortRecursive(
        data,
        middle + 1,
        right,
        result
        );


    mergeRanges(
        data,
        left,
        middle,
        right,
        result
        );
}


// =========================================================
// Merge Sort Benchmark
// =========================================================

MultiSizeBenchmarkResult benchmarkMergeSort(
    const std::vector<int> &source
    )
{
    std::vector<int> data =
        source;


    MultiSizeBenchmarkResult result;

    result.algorithmName =
        "Merge Sort";

    result.inputSize =
        static_cast<int>(
            data.size()
            );


    const auto start =
        std::chrono::high_resolution_clock::now();


    if (!data.empty())
    {
        mergeSortRecursive(
            data,
            0,
            static_cast<int>(
                data.size()
                ) -
                1,
            result
            );
    }


    const auto end =
        std::chrono::high_resolution_clock::now();


    result.executionTimeMs =
        std::chrono::duration<double, std::milli>(
            end - start
            ).count();


    return result;
}

}


// =========================================================
// Multi-size Runner
// =========================================================

std::vector<MultiSizeBenchmarkResult>
MultiSizeBenchmarkRunner::run(
    const std::vector<int> &sizes
    )
{
    std::vector<MultiSizeBenchmarkResult> results;


    results.reserve(
        sizes.size() * 4
        );


    for (int size : sizes)
    {
        if (
            size <= 0
            )
        {
            continue;
        }


        // Same input for all four algorithms
        // at this size.
        const std::vector<int> data =
            generateRandomData(
                size
                );


        results.push_back(
            benchmarkBubbleSort(
                data
                )
            );


        results.push_back(
            benchmarkSelectionSort(
                data
                )
            );


        results.push_back(
            benchmarkInsertionSort(
                data
                )
            );


        results.push_back(
            benchmarkMergeSort(
                data
                )
            );
    }


    return results;
}