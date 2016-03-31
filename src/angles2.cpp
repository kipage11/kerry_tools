//Will convert robot localization ekf orientation to rpy
//

#include <ros/ros.h>
#include <std_msgs/String.h>
#include <tf/transform_broadcaster.h>
#include <nav_msgs/Odometry.h>
#include <tf/transform_datatypes.h>
	
void backCallback(const nav_msgs::Odometry::ConstPtr& msg)
{
  tf::Quaternion q(msg->pose.pose.orientation.x, msg->pose.pose.orientation.y, msg->pose.pose.orientation.z, msg->pose.pose.orientation.w);
  tf::Matrix3x3 m(q);
  double roll, pitch, yaw;
  m.getRPY(roll, pitch, yaw);
  std::cout << msg->header.frame_id << ", " << roll << ", " << pitch << ", " << yaw << std::endl;
  
}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "angles");
	ros::NodeHandle nh;
	ros::Subscriber sub_back = nh.subscribe("back", 1000, backCallback);
	ros::Subscriber sub_uparm = nh.subscribe("uparm", 1000, backCallback);
	ros::Subscriber sub_4arm = nh.subscribe("4arm", 1000, backCallback);
	ros::Subscriber sub_hand = nh.subscribe("hand", 1000, backCallback);

	ros::spin();
}
