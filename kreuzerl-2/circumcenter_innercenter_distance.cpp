// This program calculates the distance d between the circumcenter and the incenter of a triangle.

#include <iostream>
#include <vector>
// #include <functional>

// no global state in fprog
// Global variables
// double a, b, c;
// double s, area, circumradius, inradius, distance;

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

auto calculate_radii = [](const double &a)
{
    return [a](const double &b)
    {
        return [a, b](const double &c)
        {
            // using namespace std::placeholders;
            // auto square_root_bound = bind(square_root, _1)(1e-10)(1000);
            const double s = (a + b + c) / 2;
            const double area = square_root(s * (s - a) * (s - b) * (s - c))(1e-10)(1000);
            // const double area = square_root_bound(s * (s - a) * (s - b) * (s - c));
            // this would make more sense with binding for the default values i think
            // but it does not work this way. I am trying binding in a different exercise (median), because i want to have both solutions
            // to be able to present both ideas.

            const double inradius = area / s;
            const double circumradius = (a * b * c) / (4 * area);
            std::vector<double> radii{inradius, circumradius};
            return radii;
        };
    };
};

auto calculate_distance = [](const double &inradius)
{
    return [inradius](const double &circumradius)
    {
        return square_root(circumradius * circumradius - 2 * circumradius * inradius)(1e-10)(1000);
        // this would make more sense with binding for the default values i think
    };
};

int
main()
{
    // a = 3, b = 4, c = 5;
    const double a = 3;
    const double b = 4;
    const double c = 5;
    std::cout << "Triangle sides: a = " << a << ", b = " << b << ", c = " << c << "\n";

    std::vector<double> radii = calculate_radii(a)(b)(c);
    const double inradius = radii[0];
    const double circumradius = radii[1];
    std::cout << "Inradius: " << inradius << "\n";
    std::cout << "Circumradius: " << circumradius << "\n";

    const double distance = calculate_distance(inradius)(circumradius);
    std::cout << "Distance between circumcenter and incenter: " << distance << "\n";

    return 0;
}
