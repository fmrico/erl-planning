#include <erl_planning/Action.h>


namespace KCL_rosplan {

bool
Action::concreteCallback(const rosplan_dispatch_msgs::ActionDispatch::ConstPtr& msg)
{
	bool ret = true;

	if(!checkAtStartConditions(msg))
	{
		ROS_ERROR("[%s] AT Start not meet: cancelling", id_.c_str());
		return false;
	}

	if(!activation(msg))
	{
		ROS_ERROR("[%s] ERROR at activation: cancelling", id_.c_str());
		return false;
	}

	bool finished=false;
	ros::Rate rate(freq_);
	while(ros::ok() && !finished && !ret)
	{
		if(!checkOverAllConditions(msg))
		{
			ROS_ERROR("ALL OVER not meet: cancelling");
			ret = false;
		}else
		{
			ret = step(msg, finished);
			if(!ret)
					ROS_ERROR("[%s] ERROR while executing: cleaning and cancelling", id_.c_str());
		}

		ros::spinOnce();
		rate.sleep();
	}


	if(!deactivation(msg))
	{
		ROS_ERROR("[%s] ERROR at deactivation: cancelling", id_.c_str());
		return false;
	}

		if(ret && !checkAtEndConditions(msg))
		{
			ROS_ERROR("[%s] AT End not meet: cancelling", id_.c_str());
			return false;
		}

		return ret;
}

};
