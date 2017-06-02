#include "ros/ros.h"
#include "std_msgs/String.h"
#include "sensor_msgs/LaserScan.h"
#include "geometry_msgs/Twist.h"

ros::Publisher pub;

void teleopCallback(const sensor_msgs::LaserScan::ConstPtr& msg)
{
   ROS_INFO("Angle-z: %f", msg->ranges[0]);
}

void joystickCallback(const geometry_msgs::Twist::ConstPtr& joy){
  //ROS_INFO("It works");
  pub.publish(joy);
}

int main(int argc, char **argv)
{

  ros::init(argc, argv, "listener");
  ros::NodeHandle n;
  pub = n.advertise<geometry_msgs::Twist>("/robot/cmd_vel", 1000);
  ros::Subscriber sub = n.subscribe("/base_scan", 1000, teleopCallback);
  ros::Subscriber joystick = n.subscribe("/cmd_vel", 1000, joystickCallback);

  ros::spin();

  return 0;
}
