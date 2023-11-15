#include <iostream>
#include <utility>
#include <complex>
#include <tuple>

typedef std::complex<double> complex;

double nonPureSquare(double e)
{
  double dummy = e;
  double dummy2 = e;
  for (int i = 1; i < dummy2; i++)
  {
    e = e + dummy;
    std::cout << "i: " << i << " dummy:" << dummy << " e:" << e << std::endl;
  }
  std::cout << "square:" << e << std::endl;
  return e;
}

auto square = [](const double &e)
{ return e * e; };

auto squareroot = [](const float &number)
{
  union Conv
  {
    float f;
    uint32_t i;
  };
  Conv conv;
  conv.f = number;
  conv.i = 0x5f3759df - (conv.i >> 1);
  conv.f *= 1.5F - (number * 0.5F * conv.f * conv.f);
  return 1 / conv.f;
};

auto solve_quadratic_equation = [](const double &a)
{
  return [a](const double &b)
  {
    return [a, b](const double &c)
    {
      const double temp_b = b / a;
      const double temp_c = c / a;
      const double temp_b_squared = square(temp_b);
      const double discriminant = temp_b_squared - 4 * temp_c;
      if (discriminant < 0)
        return std::make_tuple(std::make_pair(complex(-temp_b / 2, squareroot(-discriminant) / 2),
                                              complex(-temp_b / 2, -squareroot(-discriminant) / 2)),
                               temp_b_squared, discriminant);

      const double root = std::sqrt(discriminant);
      const double solution1 = (temp_b > 0) ? (-temp_b - root) / 2
                                            : (-temp_b + root) / 2;

      return std::make_tuple(std::make_pair(complex(solution1, 0), complex(temp_c / solution1, 0)), temp_b_squared, discriminant);
    };
  };
};

int main()
{
  const auto results = solve_quadratic_equation(3)(4)(5);
  std::pair<complex, complex> result = std::get<0>(results);
  std::cout << "square = " << std::get<1>(results) << std::endl
            << "discriminant = " << std::get<2>(results) << std::endl
            << "result = " << result.first << ", " << result.second << std::endl;
}