// Here's a C++ program that calculates the circumradius of a triangle using global variables and is not pure nor immutable.

#include <iostream>

// we don't want a global state or global variables in fprog
// Global variables
// double a, b, c;
// double s, area, circumradius;

// Helper function to calculate square root without using std::sqrt()

// i don't know why to not use sqrt() but it explicitly says it here so it must be part of the instructions
// that is maybe a nice spot to mention that the instructions could be clearer

// made arguments const references, removed cout
// the structural loops are not functional, but i really don't know how ot change them. i'd honestly just use sqrt
double square_root(const double& x, const double epsilon = 1e-10, const int max_iterations = 1000) {
    // std::cout << "Calculating square root of " << x << "\n";
    if (x < 0) {
        return -1; // Invalid input
    }
    if (x == 0) {
        return 0;
    }

    double low = 0, high = x;
    double mid;
    for (int i = 0; i < max_iterations; ++i) {
        mid = (low + high) / 2.0;
        double mid_square = mid * mid;

        // std::cout << "Iteration: " << i + 1 << ", mid: " << mid << ", mid_square: " << mid_square << "\n";

        if (mid_square > x) {
            high = mid;
        } else if (mid_square < x) {
            low = mid;
        }

        if (high - low < epsilon) {
            break;
        }
    }

    return mid;
}

double calculate_circumradius(const double& a, const double& b, const double& c) {
    const double s = (a + b + c) / 2;
    const double area = square_root(s * (s - a) * (s - b) * (s - c));
    return (a * b * c) / (4 * area);
}

int main() {
    const double a = 3;
    const double b = 4;
    const double c = 5;
    //a = 3, b = 4, c = 5;
    std::cout << "Triangle sides: a = " << a << ", b = " << b << ", c = " << c << "\n";

    const double circumradius = calculate_circumradius(a, b, c);

    std::cout << "Circumradius: " << circumradius << "\n";

    return 0;
}
