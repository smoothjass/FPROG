// Here's a C++ program that calculates the median of a triangle given the lengths of its sides a, b, and c

#include <iostream>
#include <functional>

// no global state in fprog -> no global variables
// double a, b, c;

// Silly square function that is not immutable and not pure
double silly_square(double x)
{
    std::cout << "Calculating the silly square of " << x << "\n";
    double result = 0;
    for (int i = 0; i < x; ++i)
    {
        result += x;
        std::cout << "Iteration " << i + 1 << ": Current result = " << result << "\n";
    }
    return result;
}

// pure immutable square function
auto square = [] (const double &x)
{
    return x * x;
};

// Helper function to calculate square root without using std::sqrt()
/*
// without binding
auto square_root = [](const double &x)
{
    return [x](const double& epsilon)
    {
        return [x, epsilon](const int& max_iterations)
        {
            // std::cout << "Calculating the square root of " << x << "\n";
            if (x < 0)
            {
                return -1.0; // Invalid input
            }
            if (x == 0)
            {
                return 0.0;
            }

            double low = 0, high = x;
            double mid;
            for (int i = 0; i < max_iterations; ++i)
            {
                mid = (low + high) / 2.0;
                double mid_square = mid * mid;
                // std::cout << "Iteration " << i + 1 << ": Midpoint = " << mid << ", Midpoint squared = " << mid_square << "\n";

                if (mid_square > x)
                {
                    high = mid;
                }
                else if (mid_square < x)
                {
                    low = mid;
                }

                if (high - low < epsilon)
                {
                    break;
                }
            }

            return mid;
        };
    };
};
*/

// with binding
auto square_root = [](const double &x, const double &epsilon, const int &max_iterations)
{
    // std::cout << "Calculating the square root of " << x << "\n";
    if (x < 0)
    {
        return -1.0; // Invalid input
    }
    if (x == 0)
    {
        return 0.0;
    }

    double low = 0, high = x;
    double mid;
    for (int i = 0; i < max_iterations; ++i)
    {
        mid = (low + high) / 2.0;
        double mid_square = mid * mid;
        // std::cout << "Iteration " << i + 1 << ": Midpoint = " << mid << ", Midpoint squared = " << mid_square << "\n";

        if (mid_square > x)
        {
            high = mid;
        }
        else if (mid_square < x)
        {
            low = mid;
        }

        if (high - low < epsilon)
        {
            break;
        }
    }

    return mid;
};

auto square_root_bound = bind(square_root, std::placeholders::_1, 1e-10, 1000);

auto calculate_median = [](const double &a)
{
    return [a](const double &b)
    {
        return [a, b](const double &c)
        {
            // double result = 0.5 * square_root(2 * silly_square(b) + 2 * silly_square(c) - silly_square(a));
            //double result = 0.5 * square_root(2 * square(b) + 2 * square(c) - square(a))(1e-10)(1000);

            // this would make more sense with binding for the default values i think
            // i will do that here and only currying without binding in a different exercise,
            // to be able to present both solutions

            double result = 0.5 * square_root_bound(2 * square(b) + 2 * square(c) - square(a));
            return result;
        };
    };
};

int main()
{
    const double a = 3;
    const double b = 4;
    const double c = 5;
    std::cout << "Triangle sides: a = " << a << ", b = " << b << ", c = " << c << "\n";

    std::cout << "Calculating the median of a triangle with sides a = " << a << ", b = " << b << ", c = " << c << "\n";
    double median_a = calculate_median(a)(b)(c);

    // a = 4, b = 3, c = 5;
    std::cout << "Calculating the median of a triangle with sides a = " << b << ", b = " << a << ", c = " << c << "\n";
    double median_b = calculate_median(b)(a)(c);

    // a = 5, b = 3, c = 4;
    std::cout << "Calculating the median of a triangle with sides a = " << c << ", b = " << a << ", c = " << b << "\n";
    double median_c = calculate_median(c)(a)(b);

    std::cout << "Medians:\n";
    std::cout << "Median from vertex A: " << median_a << "\n";
    std::cout << "Median from vertex B: " << median_b << "\n";
    std::cout << "Median from vertex C: " << median_c << "\n";

    return 0;
}
