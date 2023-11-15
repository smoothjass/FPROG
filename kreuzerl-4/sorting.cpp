#include <iostream>
#include <functional>
#include <optional>
#include <string>
#include <numeric>
#include <vector>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

template <typename DestinationType>
auto transformAll = [](const auto &source, auto fn)
{
    DestinationType result;
    result.reserve(source.size());
    transform(source.begin(), source.end(), back_inserter(result), fn);
    return result;
};

auto bucketSort = [] (const std::vector<int>& toSort, const int& numberOfBuckets) -> const std::vector<int>
{
    std::vector<int> bucketIndices = transformAll<std::vector<int>>(toSort, 
        [=](auto const element) -> int {return numberOfBuckets * element / toSort.size();});
    std::vector<std::vector> buckets;
    return toSort;
};

auto insertionSort = []() -> int
{
    return 0;
};

auto bubbleSort = []() -> int
{
    return 0;
};

auto selectionSort = []() -> int
{
    return 0;
};

auto quickSort = []() -> int
{
    return 0;
};

TEST_CASE("bucketsort"){
    std::vector<int> toSort{1,5,3,7,8,9,2,4,6,0};
    std::vector<int> expected{0,1,2,3,4,5,6,7,8,9};
    CHECK_EQ(bucketSort(toSort, 5), expected);
}

TEST_CASE("insertionsort")
{
    CHECK(insertionSort());
}

TEST_CASE("bubblesort")
{
    CHECK(bubbleSort());
}

TEST_CASE("selectionsort")
{
    CHECK(selectionSort());
}

TEST_CASE("quicksort")
{
    CHECK(quickSort());
}