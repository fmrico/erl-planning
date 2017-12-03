#include "erl_planning/KMS_Client.h"


KMS_Client::KMS_Client():
	nh_(),
	 ku_client_(nh_.serviceClient<rosplan_knowledge_msgs::KnowledgeUpdateService>
		 ("/kcl_rosplan/update_knowledge_base"))
{
}

bool
KMS_Client::add_instance(const std::string instance_type, const std::string attribute_name)
{
	rosplan_knowledge_msgs::KnowledgeItem add_instance;
	add_instance.knowledge_type = rosplan_knowledge_msgs::KnowledgeItem::INSTANCE;
	add_instance.instance_type = instance_type;
	add_instance.instance_name = attribute_name;
	rosplan_knowledge_msgs::KnowledgeUpdateService add_instance_instance;
	add_instance_instance.request.update_type = rosplan_knowledge_msgs::
		KnowledgeUpdateService::Request::ADD_KNOWLEDGE;
	add_instance_instance.request.knowledge = add_instance;

	if (!ku_client_.call(add_instance_instance)) {
		ROS_ERROR("Could not add the instance [%s %s]", instance_type.c_str(),
			attribute_name.c_str());
		return false;
	}else
		return true;
}


bool
KMS_Client::remove_fact(std::string attribute_name, const Fact& fact)
{
	rosplan_knowledge_msgs::KnowledgeItem add_fact_v;
	add_fact_v.knowledge_type = rosplan_knowledge_msgs::KnowledgeItem::FACT;
	add_fact_v.attribute_name = attribute_name;
	for(Fact::const_iterator it=fact.begin(); it!=fact.end(); ++it)
	{
		diagnostic_msgs::KeyValue kv;
		kv.key = it->first;
		kv.value = it->second;
		add_fact_v.values.push_back(kv);
	}

	rosplan_knowledge_msgs::KnowledgeUpdateService add_fact_instance;
	add_fact_instance.request.update_type = rosplan_knowledge_msgs::
		KnowledgeUpdateService::Request::REMOVE_KNOWLEDGE;
	add_fact_instance.request.knowledge = add_fact_v;

	if (!ku_client_.call(add_fact_instance)) {
		ROS_ERROR("Could not add the fact [%s]", attribute_name.c_str());
		return false;
	}else
		return true;
}


bool
KMS_Client::add_fact(std::string attribute_name, const Fact& fact)
{
	rosplan_knowledge_msgs::KnowledgeItem add_fact_v;
	add_fact_v.knowledge_type = rosplan_knowledge_msgs::KnowledgeItem::FACT;
	add_fact_v.attribute_name = attribute_name;
	for(Fact::const_iterator it=fact.begin(); it!=fact.end(); ++it)
	{
		diagnostic_msgs::KeyValue kv;
		kv.key = it->first;
		kv.value = it->second;
		add_fact_v.values.push_back(kv);
	}

	rosplan_knowledge_msgs::KnowledgeUpdateService add_fact_instance;
	add_fact_instance.request.update_type = rosplan_knowledge_msgs::
		KnowledgeUpdateService::Request::ADD_KNOWLEDGE;
	add_fact_instance.request.knowledge = add_fact_v;

	if (!ku_client_.call(add_fact_instance)) {
		ROS_ERROR("Could not add the fact [%s]", attribute_name.c_str());
		return false;
	}else
		return true;
}

bool
KMS_Client::add_goal(std::string attribute_name, const Fact& fact)
{
	rosplan_knowledge_msgs::KnowledgeItem add_fact_v;
	add_fact_v.knowledge_type = rosplan_knowledge_msgs::KnowledgeItem::FACT;
	add_fact_v.attribute_name = attribute_name;
	for(Fact::const_iterator it=fact.begin(); it!=fact.end(); ++it)
	{
		diagnostic_msgs::KeyValue kv;
		kv.key = it->first;
		kv.value = it->second;
		add_fact_v.values.push_back(kv);
	}

	rosplan_knowledge_msgs::KnowledgeUpdateService add_goal_instance;
	add_goal_instance.request.update_type = rosplan_knowledge_msgs::
		KnowledgeUpdateService::Request::ADD_GOAL;
	add_goal_instance.request.knowledge = add_fact_v;

	if (!ku_client_.call(add_goal_instance)) {
		ROS_ERROR("Could not add the fact [%s]", attribute_name.c_str());
		return false;
	}else
	{
		ROS_INFO("Fact [%s] added", attribute_name.c_str());
		return true;
	}
}
