#include <ros/ros.h>

#include "erl_planning/Executor.h"
#include <std_msgs/Empty.h>

class ERLExecutor: public Executor
{
public:
	ERLExecutor()
	{
		bell_sub = nh_.subscribe("/bell", 1, &ERLExecutor::bellCB, this);

		init_knowledge();
	}

	void bellCB(const std_msgs::Empty::ConstPtr& msg)
	{
		Fact fact_bell_ringed;
		fact_bell_ringed.push_back(Fact_Values("b", "doorbell"));
		add_fact("bell_ringed", fact_bell_ringed);
		remove_fact("mission_accomplished");
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

		add_instance("location", "l_kitchen");
		add_instance("location", "l_start");
		add_instance("location", "l_entrance");
		add_instance("location", "l_bedroom");
		add_instance("visitor", "Apu");
		add_instance("visitor", "Nick");


		Fact fact_robot_at_start;
		fact_robot_at_start.push_back(Fact_Values("l", "l_start"));
		add_fact("robot_at", fact_robot_at_start);

		Fact fact_kitchen;
		fact_kitchen.push_back(Fact_Values("l", "l_kitchen"));
		add_fact("kitchen_location", fact_kitchen);

		Fact fact_bedroom;
		fact_bedroom.push_back(Fact_Values("l", "l_bedroom"));
		add_fact("bedroom_location", fact_bedroom);

		Fact fact_entrance;
		fact_entrance.push_back(Fact_Values("l", "l_entrance"));
		add_fact("entrance_location", fact_entrance);

		Fact fact_start;
		fact_start.push_back(Fact_Values("l", "l_start"));
		add_fact("start_location", fact_start);

		Fact fact_deli;
		fact_deli.push_back(Fact_Values("p", "Apu"));
		add_fact("deli_person", fact_deli);

		Fact fact_doctor;
		fact_doctor.push_back(Fact_Values("p", "Nick"));
		add_fact("doctor_person", fact_doctor);

		Fact fact_person_at;
		fact_person_at.push_back(Fact_Values("p", "Nick"));
		fact_person_at.push_back(Fact_Values("l", "l_entrance"));
		add_fact("person_at", fact_person_at);


		Fact fact_visitor_attended;
		add_goal("mission_accomplished");
	}

private:
		ros::Subscriber bell_sub;
		ros::NodeHandle nh_;

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
