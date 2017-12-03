#include <ros/ros.h>
#include "rosplan_action_interface/RPActionInterface.h"


#ifndef KCL_moveball
#define KCL_moveball


namespace KCL_rosplan {

	class RPMoveBall: public RPActionInterface
	{

	public:
		RPMoveBall(ros::NodeHandle &nh);

		bool concreteCallback(const rosplan_dispatch_msgs::ActionDispatch::ConstPtr& msg);
	};
}
#endif
