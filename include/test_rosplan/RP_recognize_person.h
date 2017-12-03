#include <ros/ros.h>
#include "rosplan_action_interface/RPActionInterface.h"
#include <test_rosplan/KMS_Client.h>

#ifndef KCL_recognize_person
#define KCL_recognize_person


namespace KCL_rosplan {

	class RP_recognize_person: public RPActionInterface, public KMS_Client
	{

	public:
		RP_recognize_person(ros::NodeHandle &nh);

		bool concreteCallback(const rosplan_dispatch_msgs::ActionDispatch::ConstPtr& msg);
	private:

		ros::NodeHandle nh_;
	};
}
#endif
