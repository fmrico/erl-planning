#ifndef ACTION__H
#define ACTION__H

#include <ros/ros.h>

#include "rosplan_action_interface/RPActionInterface.h"
#include "erl_planning/KMS_Client.h"


namespace KCL_rosplan {

	class Action: public RPActionInterface, public KMS_Client
	{

	public:
		Action(std::string id, ros::NodeHandle &nh, float freq = 1.0)
		: id_(id), freq_(freq)
		{};

		bool concreteCallback(const rosplan_dispatch_msgs::ActionDispatch::ConstPtr& msg);

	protected:

		virtual bool activation(const rosplan_dispatch_msgs::ActionDispatch::ConstPtr& msg){};
		virtual bool deactivation(const rosplan_dispatch_msgs::ActionDispatch::ConstPtr& msg){};
		virtual bool step(const rosplan_dispatch_msgs::ActionDispatch::ConstPtr& msg, bool& finished) = 0;

		std::string id_;
		float freq_;
	};
}

#endif
