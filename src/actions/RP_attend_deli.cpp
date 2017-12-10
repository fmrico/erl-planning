#include "erl_planning/actions/RP_attend_deli.h"

namespace KCL_rosplan {

	RP_attend_deli::RP_attend_deli(ros::NodeHandle &nh)
	: Action("attend_deli", nh)
	{
		counter_=0;
	}

	bool RP_attend_deli::activation(const rosplan_dispatch_msgs::ActionDispatch::ConstPtr& msg)
	{

		ROS_INFO("RP_attend_deli [%d] %s for %fsec in %fsec...",
			msg->action_id, msg->name.c_str(),
			msg->duration, msg->dispatch_time);
	}

	bool RP_attend_deli::deactivation(const rosplan_dispatch_msgs::ActionDispatch::ConstPtr& msg)
	{
			ROS_INFO("RP_attend_deli [%d] Attended", msg->action_id);
	};

	bool RP_attend_deli::step(const rosplan_dispatch_msgs::ActionDispatch::ConstPtr& msg, bool& finished)
	{
		if(counter_ == 5)
		{
			add_fact("doctor_recognized");
			remove_fact("deli_recognized");
		}

		if(counter_ == 10)
		{
			finished = true;
		}
		counter_++;

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
