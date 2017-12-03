#include "erl_planning/RP_recognize_person.h"

namespace KCL_rosplan {

	RP_recognize_person::RP_recognize_person(ros::NodeHandle &nh):nh_(nh)
	{
		ROS_INFO("RP_recognize_person Started ======================================================================");
	}

	bool RP_recognize_person::concreteCallback(const rosplan_dispatch_msgs::ActionDispatch::ConstPtr& msg)
	{

		ROS_INFO("RP_recognize_person [%d] %s (%s) for %fsec in %fsec...",
			msg->action_id, msg->name.c_str(), msg->parameters[0].value.c_str(),
			msg->duration, msg->dispatch_time);


			ros::Duration(2).sleep();
			add_fact("deli_recognized");
			ros::Duration(2).sleep();

			ROS_INFO("RP_recognize_person Done!!!");


		return false;
	}
}
	int main(int argc, char **argv) {

		ros::init(argc, argv, "rosplan_interface_recognize_person");
		ros::NodeHandle nh("~");

		// create PDDL action subscriber
		KCL_rosplan::RP_recognize_person rpwb(nh);

		// listen for action dispatch
		ros::Subscriber ds = nh.subscribe("/kcl_rosplan/action_dispatch", 1000, &KCL_rosplan::RPActionInterface::dispatchCallback, dynamic_cast<KCL_rosplan::RPActionInterface*>(&rpwb));

		rpwb.runActionInterface();

		return 0;
	}
