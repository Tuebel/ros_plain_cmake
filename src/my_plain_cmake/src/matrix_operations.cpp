#include <plain_cmake/matrix_operations.h>

namespace plain_cmake
{
Eigen::MatrixXd matrix_operations::add(Eigen::Matrix2d A, Eigen::Matrix2d B)
{
  return A + B;
}
}  // namespace my_plain_cmake