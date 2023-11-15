#include <iostream>

// lambdas in global scope don't make a lot of sense, but for this exercise it doesn't matter much
// currying makes sense for intermediate calculations

/*
// no globally used namespaces, no global variables in fprog
using namespace std;

int x = 0;
int y = 0;
int z = 0;  // double ?
*/

auto square = [](const int &e)
{ return e * e; };

auto squareroot = [](const double &x) { // computes the square root of x
  if (x == 0)
    return 0.;

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
  // cout << "guess:" << guess << endl;
  ;
  return guess;
};

// no void function in fprog
// no cout within functions
// lambda takes one argument, returns lambda which captures the arguments and has its own argument and returns the result of pythagoras
auto pythagoras = [](const int &x)
{
  return [x](const int &y)
  { return squareroot(square(x) + square(y)); };
  // cout << "euklid:" << z << endl;
};

int main(int argc, char *argv[])
{
  const int x = 3;
  const int y = 4;
  const double z = pythagoras(x)(y);
  std::cout << z << std::endl;
  return 0;
}
