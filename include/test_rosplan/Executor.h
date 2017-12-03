#ifndef EXECUTOR_H
#define EXECUTOR_H

#include <ros/ros.h>

#include <test_rosplan/KMS_Client.h>
#include <std_msgs/String.h>
#include <std_srvs/Empty.h>
#include <utility>

class Executor: public KMS_Client
{
public:
	Executor();
	virtual void update() = 0;

protected:


	void system_stateCB(const std_msgs::String::ConstPtr& msg);

	virtual void init_knowledge() = 0;

	ros::NodeHandle nh_;
	ros::ServiceClient planning_server_state_client_;
	ros::Subscriber system_state_sub_;

	std::string system_state_;

};


#endif
