#include <iostream>
#include <vector>
#include <string>
#include <optional>

// Define a simple matrix as a 2D vector of doubles
using Matrix = std::vector<std::vector<double>>;

// Define a Result monad to represent the outcome of the matrix inversion
template <typename T>
using Result = std::optional<T>;

// Function to calculate the determinant of a 2x2 matrix
double determinant(const Matrix &mat)
{
    if (mat.size() != 2 || mat[0].size() != 2 || mat[1].size() != 2)
    {
        throw std::runtime_error("Matrix must be 2x2 to calculate determinant.");
    }

    return mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];
}

// Immutable function to invert the matrix and return a Result monad
Result<Matrix> invert_matrix(const Matrix &mat)
{
    try
    {
        // Check if the matrix can be inverted (non-zero determinant)
        double det = determinant(mat);
        if (det == 0.0)
        {
            return Result<Matrix>();
        }

        // Calculate the inverse of a 2x2 matrix
        Matrix inverted_matrix(2, std::vector<double>(2, 0.0));
        inverted_matrix[0][0] = mat[1][1] / det;
        inverted_matrix[1][1] = mat[0][0] / det;
        inverted_matrix[0][1] = -mat[0][1] / det;
        inverted_matrix[1][0] = -mat[1][0] / det;

        return Result<Matrix>(inverted_matrix);
    }
    catch (const std::exception &e)
    {
        return Result<Matrix>();
    }
}

int main()
{
    // Sample 2x2 matrix
    Matrix sample_matrix = {{4, 7}, {2, 6}};

    // Attempt to invert the matrix
    Result<Matrix> result = invert_matrix(sample_matrix);

    // Handle the result
    if (result.has_value())
    {
        std::cout << "Inverted Matrix:\n";
        for (const auto &row : result.value())
        {
            for (double element : row)
            {
                std::cout << element << " ";
            }
            std::cout << "\n";
        }
    }
    else
    {
        std::cout << "Matrix inversion failed or determinant is zero.\n";
    }

    return 0;
}
