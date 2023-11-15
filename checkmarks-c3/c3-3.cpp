#include <iostream>
#include <cmath>
#include <optional>

// Define a simple QuadraticSolution struct to represent the solutions
struct QuadraticSolution
{
    std::optional<double> x1;
    std::optional<double> x2;
};

// Lambda function to solve the quadratic equation and return a QuadraticSolution
auto solve_quadratic = [](double a, double b, double c) -> std::optional<QuadraticSolution>
{
    if (a == 0.0)
    {
        return std::nullopt; // Not a quadratic equation
    }

    double discriminant = b * b - 4 * a * c;

    if (discriminant > 0)
    {
        // Two real solutions
        QuadraticSolution solution;
        solution.x1 = (-b + sqrt(discriminant)) / (2 * a);
        solution.x2 = (-b - sqrt(discriminant)) / (2 * a);
        return solution;
    }
    else if (discriminant == 0)
    {
        // One real solution
        QuadraticSolution solution;
        solution.x1 = -b / (2 * a);
        return solution;
    }
    else
    {
        // Complex solutions
        QuadraticSolution solution;
        return solution; // Empty solution for complex roots
    }
};

int main()
{
    double a, b, c;

    std::cout << "Enter coefficients a, b, and c for the quadratic equation (ax^2 + bx + c = 0):\n";
    std::cout << "a: ";
    std::cin >> a;
    std::cout << "b: ";
    std::cin >> b;
    std::cout << "c: ";
    std::cin >> c;

    // Attempt to solve the quadratic equation
    std::optional<QuadraticSolution> result = solve_quadratic(a, b, c);

    // Handle the result
    if (result.has_value())
    {
        if (result->x1.has_value())
        {
            std::cout << "Solution 1: " << result->x1.value() << "\n";
        }
        if (result->x2.has_value())
        {
            std::cout << "Solution 2: " << result->x2.value() << "\n";
        }
        if (!result->x1.has_value() && !result->x2.has_value())
        {
            std::cout << "Complex solutions.\n";
        }
    }
    else
    {
        std::cout << "Not a quadratic equation.\n";
    }

    return 0;
}
