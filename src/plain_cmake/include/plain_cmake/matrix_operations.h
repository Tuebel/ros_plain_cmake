#include <eigen3/Eigen/Core>

namespace plain_cmake
{
class matrix_operations
{
private:
public:
  // pure static class
  matrix_operations() = delete;
  ~matrix_operations() = delete;

  /**
   * Add two 2x2 matrices
   * @param A first matrix
   * @param B second matrix
   * @return the sum of the first and second matrix
   */
  static Eigen::MatrixXd add(Eigen::Matrix2d A, Eigen::Matrix2d B);
};
}  // namespace plain_cmake