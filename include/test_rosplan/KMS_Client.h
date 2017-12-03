#ifndef KMS_CLIENT_H
#define KMS_CLIENT_H

#include <ros/ros.h>

#include <rosplan_knowledge_msgs/KnowledgeUpdateService.h>
#include <rosplan_knowledge_msgs/KnowledgeItem.h>
#include <std_msgs/String.h>
#include <std_srvs/Empty.h>
#include <utility>

class KMS_Client
{
public:
	KMS_Client();

protected:

	typedef std::pair <std::string,std::string> Fact_Values;
	typedef std::list< Fact_Values> Fact;


	bool add_instance(const std::string instance_type, const std::string attribute_name);

	bool remove_fact(std::string attribute_name, const Fact& fact=Fact());
	bool add_fact(std::string attribute_name, const Fact& fact=Fact());
	bool add_goal(std::string attribute_name, const Fact& fact=Fact());

	ros::NodeHandle nh_;
	ros::ServiceClient ku_client_;

};


#endif
