#include "ros/ros.h"
#include "std_msgs/String.h"

#include <sstream>


float getCurrentTime() {
	return ros::Time::now().toSec();
}

float start = getCurrentTime();

void setTime(const std_msgs::String::ConstPtr& msg) {
	start = getCurrentTime();
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "start_time");
  ros::NodeHandle n;

  ros::Publisher start_time_pub = n.advertise<std_msgs::String>("start_time", 5);

  ros::Rate loop_rate(10);

  while (ros::ok())
  {
    std_msgs::String msg;
    std::stringstream ss;
    ss << start;
    msg.data = ss.str();

    start_time_pub.publish(msg);
	ros::Subscriber setStartTime = n.subscribe("setStartTime", 5, setTime);

    ros::spinOnce();

    loop_rate.sleep();
  }
  return 0;
}

