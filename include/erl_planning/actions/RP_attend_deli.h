#include <ros/ros.h>
#include "rosplan_action_interface/RPActionInterface.h"
#include <erl_planning/Action.h>


#ifndef KCL_attend_deli
#define KCL_attend_deli


namespace KCL_rosplan {

	class RP_attend_deli: public Action
	{

	public:
		RP_attend_deli(ros::NodeHandle &nh);

	protected:

		bool activation(const rosplan_dispatch_msgs::ActionDispatch::ConstPtr& msg);
		bool deactivation(const rosplan_dispatch_msgs::ActionDispatch::ConstPtr& msg);
		bool step(const rosplan_dispatch_msgs::ActionDispatch::ConstPtr& msg, bool& finished);

	private:
		int counter_;
	};
}
#endif
