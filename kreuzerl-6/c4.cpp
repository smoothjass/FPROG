#include <vector>
#include <algorithm>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <ranges>

// Function to perform a single step of bubblesort and return a new range
auto bubble_step = [](auto elements)
{
    auto new_elements = elements | std::views::transform([](auto a, auto b)
                                                         { return std::minmax(a, b); }) |
                        std::views::join;
    return new_elements;
};

// Bubblesort using functional style and persistent ranges
auto bubblesort = [](auto elements)
{
    auto sorted = elements;
    for (size_t i = 0; i < elements.size(); ++i)
    {
        sorted = bubble_step(sorted);
    }
    return sorted;
};

// Function to insert an element into a sorted range and return a new range
auto insert_sorted = [](auto sorted, auto element)
{
    auto it = std::upper_bound(sorted.begin(), sorted.end(), element);
    return sorted | std::views::take(it - sorted.begin()) |
           std::views::concat(element) |
           std::views::concat(sorted | std::views::drop(it - sorted.begin()));
};

// Insertionsort using functional style and persistent ranges
auto insertionsort = [](auto elements)
{
    auto sorted = elements | std::views::take(1); // Initialize with the first element
    auto remaining = elements | std::views::drop(1);
    return std::accumulate(remaining.begin(), remaining.end(), sorted, insert_sorted);
};

// Selectionsort using functional style and persistent ranges
auto selectionsort = [](auto elements)
{
    auto sorted = elements | std::views::take(1); // Initialize with the first element
    auto remaining = elements | std::views::drop(1);

    auto select_min = [](auto acc, auto remaining)
    {
        auto min_it = std::min_element(remaining.begin(), remaining.end());
        return std::make_pair(
            acc | std::views::concat(*min_it),
            remaining | std::views::take(min_it - remaining.begin()) |
                std::views::concat(remaining | std::views::drop(min_it - remaining.begin() + 1)));
    };

    auto result = std::accumulate(remaining.begin(), remaining.end(),
                                  std::make_pair(sorted, remaining), select_min);

    return result.first;
};

// Quicksort using functional style and persistent ranges
auto quicksort = [](auto elements) -> decltype(elements)
{
    if (elements.size() <= 1)
    {
        return elements;
    }

    auto pivot = elements.front();
    auto less = elements | std::views::filter([&pivot](auto x)
                                              { return x < pivot; });
    auto equal = elements | std::views::filter([&pivot](auto x)
                                               { return x == pivot; });
    auto greater = elements | std::views::filter([&pivot](auto x)
                                                 { return x > pivot; });

    return quicksort(less) | std::views::concat(equal) | quicksort(greater);
};

TEST_CASE("Sorting Algorithms")
{
    SUBCASE("Insertion Sort")
    {
        vector<int> input = {38, 27, 43, 3, 9, 82, 10};
        auto sorted = insertionSort(input);
        CHECK(sorted == vector<int>{3, 9, 10, 27, 38, 43, 82});
    }

    SUBCASE("Bubble Sort")
    {
        vector<int> input = {38, 27, 43, 3, 9, 82, 10};
        auto sorted = bubbleSort(input);
        CHECK(sorted == vector<int>{3, 9, 10, 27, 38, 43, 82});
    }

    SUBCASE("Selection Sort")
    {
        vector<int> input = {38, 27, 43, 3, 9, 82, 10};
        auto sorted = selectionSort(input);
        CHECK(sorted == vector<int>{3, 9, 10, 27, 38, 43, 82});
    }

    SUBCASE("Quick Sort")
    {
        vector<int> input = {38, 27, 43, 3, 9, 82, 10};
        auto sorted = quickSort(input);
        CHECK(sorted == vector<int>{3, 9, 10, 27, 38, 43, 82});
    }
}