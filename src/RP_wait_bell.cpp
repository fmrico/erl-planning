#include "test_rosplan/RP_wait_bell.h"

namespace KCL_rosplan {

	RP_wait_bell::RP_wait_bell(ros::NodeHandle &nh)
	{
		ROS_INFO("RP_wait_bell Started ======================================================================");
	}

	bool RP_wait_bell::concreteCallback(const rosplan_dispatch_msgs::ActionDispatch::ConstPtr& msg)
	{


		ROS_INFO("RP_wait_bell [%d] %s (%s: %s) for %fsec in %fsec...",
			msg->action_id, msg->name.c_str(), msg->parameters[0].value.c_str(),
		  msg->parameters[1].value.c_str(),
			msg->duration, msg->dispatch_time);

			ros::Duration(5).sleep();

			ROS_INFO("RP_wait_bell Done!!!");
		return true;
	}
}
	int main(int argc, char **argv) {

		ros::init(argc, argv, "rosplan_interface_wait_bell");
		ros::NodeHandle nh("~");

		// create PDDL action subscriber
		KCL_rosplan::RP_wait_bell rpwb(nh);

		// listen for action dispatch
		ros::Subscriber ds = nh.subscribe("/kcl_rosplan/action_dispatch", 1000, &KCL_rosplan::RPActionInterface::dispatchCallback, dynamic_cast<KCL_rosplan::RPActionInterface*>(&rpwb));

		rpwb.runActionInterface();

		return 0;
	}
