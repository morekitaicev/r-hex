#include "ros/ros.h"
#include "std_msgs/String.h"

#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
#include <sstream>
#include <fstream>

#include <iostream>
#include <stdexcept>
#include <stdio.h>
#include <string>

std::vector<std::string> getUSB() {
	std::fstream ports;
	ports.open("~/awailableProts.txt", std::fstream::in);
	std::vector<std::string> result(2);
	getline(ports, result[1]);
	getline(ports, result[2]);
	return result;
}

std::string exec(const std::string& cmd) {
    char buffer[128];
    std::string result = "";
    FILE* pipe = popen(cmd.c_str(), "r");
    if (!pipe) throw std::runtime_error("popen() failed!");
    try {
        while (fgets(buffer, sizeof buffer, pipe) != NULL) {
            result += buffer;
        }
    } catch (...) {
        pclose(pipe);
        throw;
    }
    pclose(pipe);
    return result;
}

std::string getPosMotors(const int& n) {
	std::vector<std::string> pairs = getUSB();
	if (n == 1 || n == 4 || n == 5) {
		std::string command = "sed -n 3p " + pairs[1];
		std::string left_pair = exec(command);
		std::stringstream ss;
		ss << left_pair;
		int one = 0, four = 0, five = 0;
		ss >> one >> four >> five;
		switch(n) {
			case 1:
				return std::to_string(one);
				break;	
			case 4:
				return std::to_string(four);
				break;
			case 5:
				return std::to_string(five);
				break;	
		}
	} else if (n == 2 || n == 3 || n == 6) {
		std::string command = "sed -n 3p " + pairs[2];
		std::string right_pair = exec(command);
		std::stringstream ss;
		ss << right_pair;
		int two = 0, three = 0, six = 0;
		ss >> two >> three >> six;
		switch(n) {
			case 2:
				return std::to_string(two);
				break;	
			case 3:
				return std::to_string(three);
				break;
			case 6:
				return std::to_string(six);
				break;
		}
	}
	return 0;
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "position");
  ros::NodeHandle n;

	ros::Publisher position0_pub = n.advertise<std_msgs::String>("pos0", 5);
  	ros::Publisher position1_pub = n.advertise<std_msgs::String>("pos1", 5);
	ros::Publisher position2_pub = n.advertise<std_msgs::String>("pos2", 5);
	ros::Publisher position3_pub = n.advertise<std_msgs::String>("pos3", 5);
	ros::Publisher position4_pub = n.advertise<std_msgs::String>("pos4", 5);
	ros::Publisher position5_pub = n.advertise<std_msgs::String>("pos5", 5);

  ros::Rate loop_rate(10);

  while (ros::ok())
  {
    std_msgs::String msg0;
	std_msgs::String msg1;
	std_msgs::String msg2;
	std_msgs::String msg3;
	std_msgs::String msg4;
	std_msgs::String msg5;

    std::stringstream ss;
    ss << getPosMotors(1);
    msg0.data = ss.str();

	ss.str("");
	ss << getPosMotors(2);
    msg1.data = ss.str();

	ss.str("");
	ss << getPosMotors(3);
    msg2.data = ss.str();

	ss.str("");
	ss << getPosMotors(4);
    msg3.data = ss.str();

	ss.str("");
	ss << getPosMotors(5);
    msg4.data = ss.str();

	ss.str("");
	ss << getPosMotors(6);
    msg5.data = ss.str();

	position0_pub.publish(msg0);
	position1_pub.publish(msg1);
	position2_pub.publish(msg2);
	position3_pub.publish(msg3);
	position4_pub.publish(msg4);
	position5_pub.publish(msg5);

    ros::spinOnce();

    loop_rate.sleep();
  }


  return 0;
}
