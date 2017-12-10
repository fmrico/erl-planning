#include <ros/ros.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <boost/foreach.hpp>

#include "rosplan_action_interface/RPActionInterface.h"

#include "actionlib/client/simple_action_client.h"
#include "move_base_msgs/MoveBaseAction.h"
#include "mongodb_store/message_store.h"
#include "geometry_msgs/PoseStamped.h"
#include "std_srvs/Empty.h"

#ifndef KCL_escort_to
#define KCL_escort_to

/**
 * This file defines the RPMoveBase class.
 * RPMoveBase is used to connect ROSPlan to the MoveBase library.
 * PDDL "goto_waypoint" actions become "move_base_msgs::MoveBase" actions.
 * Waypoint goals are fetched by name from the SceneDB (implemented by mongoDB).
 */
namespace KCL_rosplan {

	class RP_escort_to: public RPActionInterface
	{

	private:

		mongodb_store::MessageStoreProxy message_store;
		actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> action_client;
		ros::ServiceClient clear_costmaps_client;

	public:

		/* constructor */
		RP_escort_to(ros::NodeHandle &nh, std::string &actionserver);

		/* listen to and process action_dispatch topic */
		bool concreteCallback(const rosplan_dispatch_msgs::ActionDispatch::ConstPtr& msg);
	};
}
#endif
