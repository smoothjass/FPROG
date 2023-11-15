// This program calculates the distance d between the circumcenter and the incenter of a triangle.

#include <iostream>
#include <vector>

// no global state in fprog
// Global variables
// double a, b, c;
// double s, area, circumradius, inradius, distance;

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

std::vector<double> calculate_radii(const double& a, const double& b, const double& c) {
    const double s = (a + b + c) / 2;
    const double area = square_root(s * (s - a) * (s - b) * (s - c));
    const double inradius = area / s;
    const double circumradius = (a * b * c) / (4 * area);
    std::vector<double> radii {inradius, circumradius};
    return radii;
}

double calculate_distance(const double& inradius, const double& circumradius) {
    return square_root(circumradius * circumradius - 2 * circumradius * inradius);
}

int main() {
    //a = 3, b = 4, c = 5;
    const double a = 3;
    const double b = 4;
    const double c = 5;
    std::cout << "Triangle sides: a = " << a << ", b = " << b << ", c = " << c << "\n";

    std::vector<double> radii = calculate_radii(a, b, c);
    const double inradius = radii[0];
    const double circumradius = radii[1];
    std::cout << "Inradius: " << inradius << "\n";
    std::cout << "Circumradius: " << circumradius << "\n";

    const double distance = calculate_distance(inradius, circumradius);
    std::cout << "Distance between circumcenter and incenter: " << distance << "\n";

    return 0;
}
