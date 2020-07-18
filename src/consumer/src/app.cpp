#include <iostream>
#include <plain_cmake/matrix_operations.h>

int main()
{
  Eigen::Matrix2d A;
  A << 1, 2, 3, 4;
  Eigen::Matrix2d B;
  B << 4, 3, 2, 1;
  auto C = plain_cmake::matrix_operations::add(A, B);
  std::cout << A << "\n+\n" << B << "\n=\n" << C << std::endl;
  return EXIT_SUCCESS;
}
