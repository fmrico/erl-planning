#include <ros/ros.h>
#include "rosplan_action_interface/RPActionInterface.h"


#ifndef KCL_wait_bell
#define KCL_wait_bell


namespace KCL_rosplan {

	class RP_wait_bell: public RPActionInterface
	{

	public:
		RP_wait_bell(ros::NodeHandle &nh);

		bool concreteCallback(const rosplan_dispatch_msgs::ActionDispatch::ConstPtr& msg);
	};
}
#endif
