#include "ros/ros.h"
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

void MoveToStart0(const std_msgs::String::ConstPtr& msg) {
	std::vector<std::string> ports = getUSB();
	int current = std::stoi(msg->data.c_str());
	std::string command = "echo -n '1255 0000 0000' " + ports[1];
	while (current % 360 != 0) {
		int current = std::stoi(msg->data.c_str());
		std::system(command.c_str());
	}
	command = "echo -n '0000 0000 0000' " + ports[1];
	std::system(command.c_str());
}

void MoveToStart1(const std_msgs::String::ConstPtr& msg) {
	std::vector<std::string> ports = getUSB();
	int current = std::stoi(msg->data.c_str());
	std::string command = "echo -n '1255 0000 0000' " + ports[2];
	while (current % 360 != 0) {
		int current = std::stoi(msg->data.c_str());
		std::system(command.c_str());
	}
	command = "echo -n '0000 0000 0000' " + ports[2];
	std::system(command.c_str());
}

void MoveToStart2(const std_msgs::String::ConstPtr& msg) {
	std::vector<std::string> ports = getUSB();
	int current = std::stoi(msg->data.c_str());
	std::string command = "echo -n '0000 1255 0000' " + ports[2];
	while (current % 360 != 0) {
		int current = std::stoi(msg->data.c_str());
		std::system(command.c_str());
	}
	command = "echo -n '0000 0000 0000' " + ports[1];
	std::system(command.c_str());
}

void MoveToStart3(const std_msgs::String::ConstPtr& msg) {
	std::vector<std::string> ports = getUSB();
	int current = std::stoi(msg->data.c_str());
	std::string command = "echo -n '0000 0000 1255' " + ports[1];
	while (current % 360 != 0) {
		int current = std::stoi(msg->data.c_str());
		std::system(command.c_str());
	}
	command = "echo -n '0000 0000 0000' " + ports[1];
	std::system(command.c_str());
}

void MoveToStart4(const std_msgs::String::ConstPtr& msg) {
	std::vector<std::string> ports = getUSB();
	int current = std::stoi(msg->data.c_str());
	std::string command = "echo -n '0000 1255 0000' " + ports[1];
	while (current % 360 != 0) {
		int current = std::stoi(msg->data.c_str());
		std::system(command.c_str());
	}
	command = "echo -n '0000 0000 0000' " + ports[2];
	std::system(command.c_str());
}

void MoveToStart5(const std_msgs::String::ConstPtr& msg) {
	std::vector<std::string> ports = getUSB();
	int current = std::stoi(msg->data.c_str());
	std::string command = "echo -n '0000 0000 1255' " + ports[2];
	while (current % 360 != 0) {
		int current = std::stoi(msg->data.c_str());
		std::system(command.c_str());
	}
	command = "echo -n '0000 0000 0000' " + ports[2];
	std::system(command.c_str());
}



void setStartCallback(const std_msgs::String::ConstPtr& msg) {
	ros::NodeHandle n;
	ros::Subscriber position0 = n.subscribe("pos0", 5, MoveToStart0);
  	ros::Subscriber position1 = n.subscribe("pos1", 5, MoveToStart1);
	ros::Subscriber position2 = n.subscribe("pos2", 5, MoveToStart2);
	ros::Subscriber position3 = n.subscribe("pos3", 5, MoveToStart3);
	ros::Subscriber position4 = n.subscribe("pos4", 5, MoveToStart4);
	ros::Subscriber position5 = n.subscribe("pos5", 5, MoveToStart5);
}


void setMove(const std_msgs::String::ConstPtr& msg) {
	std::string command = "rostopic pub setMove0 std_msgs/String \"data: ''\" --once";
	system(command.c_str());
	
}


void setStop(const std_msgs::String::ConstPtr& msg) {
	std::vector<std::string> ports = getUSB();
	std::string left = "echo -n '0000 0000 0000' " + ports[1],
		 right = "echo -n '0000 0000 0000' " + ports[2];
	system(left.c_str());
	system(right.c_str());
}

void Only0(const std_msgs::String::ConstPtr& msg) {
	std::vector<std::string> ports = getUSB();
	std::string command = "echo -n '1255 0000 0000' " + ports[1];
	system(command.c_str());
}

void Only1(const std_msgs::String::ConstPtr& msg) {
	std::vector<std::string> ports = getUSB();
	std::string command = "echo -n '1255 0000 0000' " + ports[2];
	system(command.c_str());
}

void Only2(const std_msgs::String::ConstPtr& msg) {
	std::vector<std::string> ports = getUSB();
	std::string command = "echo -n '0000 1255 0000' " + ports[2];
	system(command.c_str());
}

void Only3(const std_msgs::String::ConstPtr& msg) {
	std::vector<std::string> ports = getUSB();
	std::string command = "echo -n '0000 1255 0000' " + ports[1];
	system(command.c_str());
}

void Only4(const std_msgs::String::ConstPtr& msg) {
	std::vector<std::string> ports = getUSB();
	std::string command = "echo -n '0000 0000 1255' " + ports[1];
	system(command.c_str());
}

void Only5(const std_msgs::String::ConstPtr& msg) {
	std::vector<std::string> ports = getUSB();
	std::string command = "echo -n '0000 0000 1255' " + ports[2];
	system(command.c_str());
}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "listener");
	ros::NodeHandle n;
	ros::Subscriber setStart = n.subscribe("setStart", 5, setStartCallback);
	ros::Subscriber move = n.subscribe("move", 5, setMove);
	ros::Subscriber stop = n.subscribe("stop", 5, setStop);
	
	ros::Subscriber go0 = n.subscribe("go0", 5, Only0);
  	ros::Subscriber go1 = n.subscribe("go1", 5, Only1);
	ros::Subscriber go2 = n.subscribe("go2", 5, Only2);
	ros::Subscriber go3 = n.subscribe("go3", 5, Only3);
	ros::Subscriber go4 = n.subscribe("go4", 5, Only4);
	ros::Subscriber go5 = n.subscribe("go5", 5, Only5);

	ros::spin();
	return 0;
}

