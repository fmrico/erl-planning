#include <ros/ros.h>
#include "rosplan_action_interface/RPActionInterface.h"
#include <erl_planning/KMS_Client.h>


#ifndef KCL_attend_deli
#define KCL_attend_deli


namespace KCL_rosplan {

	class RP_attend_deli: public RPActionInterface, public KMS_Client
	{

	public:
		RP_attend_deli(ros::NodeHandle &nh);

		bool concreteCallback(const rosplan_dispatch_msgs::ActionDispatch::ConstPtr& msg);
	};
}
#endif
