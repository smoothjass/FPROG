#include <iostream>
#include <optional>

// Define the Maybe monad
template <typename T>
using Maybe = std::optional<T>;

// Lambda function to perform integer division
auto divide_integers = [](int numerator, int denominator) -> Maybe<int>
{
    if (denominator == 0)
    {
        return Maybe<int>(); // Return empty Maybe for division by zero
    }

    return Maybe<int>(numerator / denominator);
};

// Lambda function to print the result of the division
void print_result(const Maybe<int> &result)
{
    if (result.has_value())
    {
        std::cout << "Result of the division: " << result.value() << "\n";
    }
    else
    {
        std::cout << "Error: Division by zero.\n";
    }
}

int main()
{
    int numerator, denominator;

    std::cout << "Enter the numerator: ";
    std::cin >> numerator;

    std::cout << "Enter the denominator: ";
    std::cin >> denominator;

    Maybe<int> result = divide_integers(numerator, denominator);

    print_result(result);

    return 0;
}
