// Here's a C++ program that calculates the circumradius of a triangle using global variables and is not pure nor immutable.

#include <iostream>

// we don't want a global state or global variables in fprog
// Global variables
// double a, b, c;
// double s, area, circumradius;

// Helper function to calculate square root without using std::sqrt()
auto square_root = [](const double &x)
{
    return [x](const double &epsilon)
    {
        return [x, epsilon](const int &max_iterations)
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

auto calculate_circumradius = [](const double &a)
{
    return [a](const double &b)
    {
        return [a, b](const double &c)
        {
            const double s = (a + b + c) / 2;
            const double area = square_root(s * (s - a) * (s - b) * (s - c))(1e-10)(1000);
            // this would make more sense with binding for the default values i think
            // but it does not work this way. I am trying binding in a different exercise (median), because i want to have both solutions
            // to be able to present both ideas.
            return (a * b * c) / (4 * area);
        };
    };
};

int
main()
{
    const double a = 3;
    const double b = 4;
    const double c = 5;
    // a = 3, b = 4, c = 5;
    std::cout << "Triangle sides: a = " << a << ", b = " << b << ", c = " << c << "\n";

    const double circumradius = calculate_circumradius(a)(b)(c);

    std::cout << "Circumradius: " << circumradius << "\n";

    return 0;
}
