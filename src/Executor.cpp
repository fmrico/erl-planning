#include "test_rosplan/Executor.h"


Executor::Executor():
	nh_(),
	planning_server_state_client_(nh_.serviceClient<std_srvs::Empty>
			 ("/kcl_rosplan/planning_server")),
	 system_state_("Ready")
{
	system_state_sub_ = nh_.subscribe("/kcl_rosplan/system_state", 10, &Executor::system_stateCB, this);

}

void
Executor::update()
{
		ROS_INFO("State: [%s]", system_state_.c_str());

		if(system_state_ == "Ready")
		{
			std_srvs::Empty service;
			if (!planning_server_state_client_.call(service))
				ROS_ERROR("Planning responded with an error");
			else
				ROS_INFO("Planning success");
		}
	}

void
Executor::system_stateCB(const std_msgs::String::ConstPtr& msg)
{
	system_state_ = msg->data;
}
