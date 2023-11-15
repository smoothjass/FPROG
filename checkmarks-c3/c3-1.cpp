#include <iostream>
#include <fstream>
#include <vector>
#include <functional>
#include <optional>

// Define the Maybe monad
template <typename T>
using Maybe = std::optional<T>;

// Lambda function to read integers from a file
auto readIntegersFromFile = [](const std::string &filename) -> Maybe<std::vector<int>>
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        return Maybe<std::vector<int>>(); // Return empty Maybe if file cannot be opened
    }

    std::vector<int> integers;
    int num;
    while (file >> num)
    {
        integers.push_back(num);
    }

    return Maybe<std::vector<int>>(integers);
};

// Immutable function to read integers from the file
Maybe<std::vector<int>> readIntegersImmutable(const std::string &filename)
{
    return readIntegersFromFile(filename);
}

// Lambda function to sum the integers in the file
auto sumIntegersFromFile = [](const std::string &filename) -> Maybe<int>
{
    Maybe<std::vector<int>> maybeIntegers = readIntegersFromFile(filename);

    if (maybeIntegers.has_value())
    {
        int sum = 0;
        for (int num : maybeIntegers.value())
        {
            sum += num;
        }
        return Maybe<int>(sum);
    }
    else
    {
        return Maybe<int>(); // Return empty Maybe if reading integers failed
    }
};

int main()
{
    const std::string filename = "integers.txt";

    Maybe<std::vector<int>> maybeIntegers = readIntegersFromFile(filename);
    if (maybeIntegers.has_value())
    {
        std::cout << "Integers read from file: ";
        for (int num : maybeIntegers.value())
        {
            std::cout << num << " ";
        }
        std::cout << "\n";
    }
    else
    {
        std::cout << "Failed to read integers from file.\n";
    }

    Maybe<std::vector<int>> maybeIntegersImmutable = readIntegersImmutable(filename);
    if (maybeIntegersImmutable.has_value())
    {
        std::cout << "Integers read (immutable function): ";
        for (int num : maybeIntegersImmutable.value())
        {
            std::cout << num << " ";
        }
        std::cout << "\n";
    }
    else
    {
        std::cout << "Failed to read integers (immutable function) from file.\n";
    }

    Maybe<int> maybeSum = sumIntegersFromFile(filename);
    if (maybeSum.has_value())
    {
        std::cout << "Sum of integers: " << maybeSum.value() << "\n";
    }
    else
    {
        std::cout << "Failed to sum integers from file.\n";
    }

    return 0;
}
