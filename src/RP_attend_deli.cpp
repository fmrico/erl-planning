#include "erl_planning/RP_attend_deli.h"

namespace KCL_rosplan {

	RP_attend_deli::RP_attend_deli(ros::NodeHandle &nh)
	{
		ROS_INFO("RP_attend_deli Started ======================================================================");
	}

	bool RP_attend_deli::concreteCallback(const rosplan_dispatch_msgs::ActionDispatch::ConstPtr& msg)
	{

		ROS_INFO("RP_attend_deli [%d] %s for %fsec in %fsec...",
			msg->action_id, msg->name.c_str(),
			msg->duration, msg->dispatch_time);

			ros::Duration(5).sleep();
			add_fact("doctor_recognized");
			remove_fact("deli_recognized");
			ros::Duration(15).sleep();

			ROS_INFO("RP_attend_deli Done!!!");
		return true;
	}
}
	int main(int argc, char **argv) {

		ros::init(argc, argv, "rosplan_interface_attend_deli");
		ros::NodeHandle nh("~");

		// create PDDL action subscriber
		KCL_rosplan::RP_attend_deli rpwb(nh);

		// listen for action dispatch
		ros::Subscriber ds = nh.subscribe("/kcl_rosplan/action_dispatch", 1000, &KCL_rosplan::RPActionInterface::dispatchCallback, dynamic_cast<KCL_rosplan::RPActionInterface*>(&rpwb));

		rpwb.runActionInterface();

		return 0;
	}
