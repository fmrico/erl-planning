#include "erl_planning/RPMoveBall.h"

namespace KCL_rosplan {

	RPMoveBall::RPMoveBall(ros::NodeHandle &nh)
	{
		ROS_INFO("RPMoveBall Started ======================================================================");
	}

	bool RPMoveBall::concreteCallback(const rosplan_dispatch_msgs::ActionDispatch::ConstPtr& msg)
	{

		ROS_INFO("RPMoveBall [%d] %s (%s: %s -> %s) for %fsec in %fsec...",
			msg->action_id, msg->name.c_str(), msg->parameters[0].value.c_str(),
		  msg->parameters[1].value.c_str(),   msg->parameters[2].value.c_str(),
			msg->duration, msg->dispatch_time);

			for(int i=0; i<5; i++)
			{
				checkOverAllConditions(msg);
				ros::Duration(1).sleep();
			}
			ROS_INFO("RPMoveBall Done!!!");
		return true;
	}
}
	int main(int argc, char **argv) {

		ros::init(argc, argv, "rosplan_interface_moveball");
		ros::NodeHandle nh("~");

		// create PDDL action subscriber
		KCL_rosplan::RPMoveBall rpmb(nh);

		// listen for action dispatch
		ros::Subscriber ds = nh.subscribe("/kcl_rosplan/action_dispatch", 1000, &KCL_rosplan::RPActionInterface::dispatchCallback, dynamic_cast<KCL_rosplan::RPActionInterface*>(&rpmb));

		rpmb.runActionInterface();

		return 0;
	}
