#include "ros/ros.h"
#include "std_msgs/Empty.h"
#include "std_msgs/String.h"
#include "stdio.h"
#include "stdlib.h"
#include <vector>
#include <sstream>
#include <string>
#include <fstream>

std::vector<std::string> getUSB() {
	std::fstream ports;
	ports.open("~/awailableProts.txt", std::fstream::in);
	std::vector<std::string> result(2);
	getline(ports, result[1]);
	getline(ports, result[2]);
	return result;
}

void MoveTo(const std_msgs::String::ConstPtr& msg) {
	std::vector<std::string> ports = getUSB();
	int current = std::stoi(msg->data.c_str());
	std::string command = "echo -n '1255 1255 1255' " + ports[1];
	sleep(1);
	while (current % 360 != 0) {
		int current = std::stoi(msg->data.c_str());
		std::system(command.c_str());
	}
	command = "echo -n '0000 0000 0000' " + ports[1];
	std::system(command.c_str());
	
	command = "rostopic pub setMove1 std_msgs/String \"data: ''\" --once";
	system(command.c_str());
}

void Move(const std_msgs::String::ConstPtr& msg) {
	ros::NodeHandle n;
	ros::Subscriber position0 = n.subscribe("pos0", 5, MoveTo);
}


int main(int argc, char **argv) {
  ros::init(argc, argv, "move");

  ros::NodeHandle n;

  ros::Subscriber sub = n.subscribe("setMove0", 5, Move);

  ros::spin();

  return 0;
}
