#include <ros/ros.h>

#include "test_rosplan/Executor.h"

class BoxesExecutor: public Executor
{
public:
	BoxesExecutor()
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

		add_instance("ball", "red");
		add_instance("ball", "blue");
		add_instance("box", "A");
		add_instance("box", "B");
		add_instance("box", "C");


		Fact fact_red_at_box_A;
		fact_red_at_box_A.push_back(Fact_Values("bl", "red"));
		fact_red_at_box_A.push_back(Fact_Values("bx", "A"));
		add_fact("ball_at_box", fact_red_at_box_A);

		Fact fact_blue_at_box_B;
		fact_blue_at_box_B.push_back(Fact_Values("bl", "blue"));
		fact_blue_at_box_B.push_back(Fact_Values("bx", "B"));
		add_fact("ball_at_box", fact_blue_at_box_B);

		Fact fact_free_box_C;
		fact_free_box_C.push_back(Fact_Values("bx", "C"));
		add_fact("free", fact_free_box_C);

		Fact fact_red_at_box_B;
		fact_red_at_box_B.push_back(Fact_Values("bl", "red"));
		fact_red_at_box_B.push_back(Fact_Values("bx", "B"));
		add_goal("ball_at_box", fact_red_at_box_B);

		Fact fact_blue_at_box_C;
		fact_blue_at_box_C.push_back(Fact_Values("bl", "blue"));
		fact_blue_at_box_C.push_back(Fact_Values("bx", "B"));
		add_goal("ball_at_box", fact_blue_at_box_C);

	}

};

int main(int argc, char **argv)
{

   ros::init(argc, argv, "ball_boxes");
   ros::NodeHandle n;

   ros::Rate loop_rate(1);
	 BoxesExecutor exec;

   while (ros::ok())
   {
		 exec.update();

     ros::spinOnce();
     loop_rate.sleep();
   }

   return 0;

 }
