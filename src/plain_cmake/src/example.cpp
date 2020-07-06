#include <iostream>
#include <plain_cmake/matrix_operations.h>

int main(int argc, char const* argv[])
{
  Eigen::Matrix2d A;
  A << 1, 2, 3, 4;
  Eigen::Matrix2d B;
  B << 4, 3, 2, 1;
  std::cout << plain_cmake::matrix_operations::add(A, B) << std::endl;
  return EXIT_SUCCESS;
}
