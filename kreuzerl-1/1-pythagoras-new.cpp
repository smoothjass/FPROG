#include <iostream>
#include <tuple>
#include <string>
#include <sstream>
#include <cmath>

/*
using namespace std;

// i just don't really like using namespaces, i wanna know where all the stuff comes from
// don't use global states in functional programming -> don't use global variables

int x = 0;
int y = 0;
int z = 0;  // double ?
*/

// i don't know if we are supposed to produce the exact same output as in the original
// if so, here's a function that returns the square and a string in a tuple
std::tuple<int,std::string> squareWithText(const int& e) {
  std::stringstream text;
  int dummy = e;
  int dummy2 = e;
  int dummy3 = e;
  for (int i = 1; i < dummy2; i++)
  {
    dummy3 = dummy3 + dummy;
    text << "i: " << i << " dummy:" << dummy << " e:" << dummy3 << std::endl;
  }
  text << "square:" << dummy3 << std::endl;
  return std::make_tuple(dummy3, text.str());
}

// if we don't have to preserve the output, i'd prefer to do this, because it doesn't require a loop
// and is generally doing less stuff, which is what we want
// this function might not be reusable for other programs, because it doesn't work correctly with non-integers (return value)
// but i am trying to stick as much as possible to the original
int square(const int& e) {
  return e*e;
}

double squareroot(const double& x) { /* computes the square root of x */

  if (x == 0)
    return 0;

  /* the sqrt must be between xhi and xlo */
  double xhi = x;
  double xlo = 0;
  double guess = x / 2;

  /* We stop when guess*guess-x is very small */

  while (std::abs(guess * guess - x) > 0.00001)
  {
    if (guess * guess > x)
    {
      xhi = guess;
    }

    else
    {
      xlo = guess;
    }

    guess = (xhi + xlo) / 2;
  }
  // std::cout << "guess:" << guess << std::endl;
  ;
  return guess;
}

// no void functions in functional programming
std::tuple<int, int, double> pythagoras(const int&x, const int& y)
{
  // z = squareroot(square(x) + square(y));
  // says here that cmath sqrt() is pure. so why not use it?
  // https://www.tutorialspoint.com/pure-function-in-cplusplus
  int square_x = square(x);
  int square_y = square(y);
  return std::make_tuple(square_x, square_y, std::sqrt(square_x + square_y));

  // no couts in pure functions.
  // cout << "euklid:" << z << std::endl;
}

int main(int argc, char *argv[])
{
  const int x = 3;
  const int y = 4;
  const auto result = pythagoras(x, y);
  std::cout << "x = " << x << std::endl
            << "square = " << std::get<0>(result) << std::endl
            << "y = " << y << std::endl
            << "square = " << std::get<1>(result) << std::endl
            << "z = " << std::get<2>(result) << std::endl;
  return 0;
}
