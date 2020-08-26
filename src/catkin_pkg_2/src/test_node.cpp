#include <ros/ros.h>
#include <std_msgs/String.h>
#include <iostream>
#include <plain_cmake/matrix_operations.h>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "talker");
  ros::NodeHandle n;
  ros::Publisher chatter_pub = n.advertise<std_msgs::String>("chatter", 1000);
  ros::Rate loop_rate(10);

  // use the library
  Eigen::Matrix2d A;
  A << 1, 2, 3, 4;
  Eigen::Matrix2d B;
  B << 4, 3, 2, 1;
  auto C = plain_cmake::matrix_operations::add(A, B);
  std::cout << A << "\n+\n"
            << B << "\n=\n"
            << C << std::endl;

  int count = 0;
  while (ros::ok())
  {
    std_msgs::String msg;
    std::stringstream ss;
    ss << "test node " << count;
    msg.data = ss.str();
    ROS_INFO("%s", msg.data.c_str());
    chatter_pub.publish(msg);
    ros::spinOnce();
    loop_rate.sleep();
    ++count;
  }

  return 0;
}