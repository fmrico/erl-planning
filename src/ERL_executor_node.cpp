#include <ros/ros.h>

#include "test_rosplan/Executor.h"

class ERLExecutor: public Executor
{
public:
	ERLExecutor()
	{
		init_knowledge();
	}

	void update()
	{
		ROS_INFO("State: [%s]", system_state_.c_str());

		if(system_state_ == "Ready")
		{
			std_srvs::Empty service;
			if (!planning_server_state_client_.call(service))
				ROS_ERROR("Planning responded with an error");
			else
				ROS_INFO("Planning success");
		}
	}


	void init_knowledge()
	{

		add_instance("robot", "pepper");
		add_instance("bell", "doorbell");
		add_instance("doctor", "Jack");
		add_instance("deli", "Raj");


		Fact fact_robot_ready;
		fact_robot_ready.push_back(Fact_Values("r", "pepper"));
		add_fact("robot_ready", fact_robot_ready);

		Fact fact_visitor_attended;
		add_goal("visitor_attended");
	}

};

int main(int argc, char **argv)
{

   ros::init(argc, argv, "ERL");
   ros::NodeHandle n;

   ros::Rate loop_rate(1);
	 ERLExecutor exec;

	 exec.update();

	 ros::spin();

   return 0;

 }
