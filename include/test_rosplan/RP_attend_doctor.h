#include <ros/ros.h>
#include "rosplan_action_interface/RPActionInterface.h"


#ifndef KCL_attend_doctor
#define KCL_attend_doctor


namespace KCL_rosplan {

	class RP_attend_doctor: public RPActionInterface
	{

	public:
		RP_attend_doctor(ros::NodeHandle &nh);

		bool concreteCallback(const rosplan_dispatch_msgs::ActionDispatch::ConstPtr& msg);
	};
}
#endif
