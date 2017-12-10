#include "erl_planning/actions/RP_attend_doctor.h"

namespace KCL_rosplan {

	RP_attend_doctor::RP_attend_doctor(ros::NodeHandle &nh)
	{
		ROS_INFO("RP_attend_doctor Started ======================================================================");
	}

	bool RP_attend_doctor::concreteCallback(const rosplan_dispatch_msgs::ActionDispatch::ConstPtr& msg)
	{

		if(!checkAtStartConditions(msg))
		{
			ROS_ERROR("AT Start not meet: cancelling");
			return false;
		}

		ROS_INFO("RP_attend_doctor [%d] %s for %fsec in %fsec...",
			msg->action_id, msg->name.c_str(),
			msg->duration, msg->dispatch_time);

			bool finished = false;
			ros::Rate rate(1);

			int counter=0;

			while(ros::ok() && !finished)
			{
				if(!checkOverAllConditions(msg))
				{
					ROS_ERROR("ALL OVER not meet: cancelling");
					return false;
				}

				ROS_INFO("Attending Doctor: OK");

				if(counter == 5)
				{
					finished = true;
				}

				counter++;
				ros::spinOnce();
				rate.sleep();
			}

			if(!checkAtEndConditions(msg))
			{
				ROS_ERROR("AT END not meet: cancelling");
				return false;
			}

			ROS_INFO("RP_attend_doctor Done!!!");
		return true;
	}
}
	int main(int argc, char **argv) {

		ros::init(argc, argv, "rosplan_interface_attend_doctor");
		ros::NodeHandle nh("~");

		// create PDDL action subscriber
		KCL_rosplan::RP_attend_doctor rpwb(nh);

		// listen for action dispatch
		ros::Subscriber ds = nh.subscribe("/kcl_rosplan/action_dispatch", 1000, &KCL_rosplan::RPActionInterface::dispatchCallback, dynamic_cast<KCL_rosplan::RPActionInterface*>(&rpwb));

		rpwb.runActionInterface();

		return 0;
	}
