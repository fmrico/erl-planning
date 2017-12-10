#include "erl_planning/KMS_Client.h"


KMS_Client::KMS_Client():
	nh_(),
	 ku_client_(nh_.serviceClient<rosplan_knowledge_msgs::KnowledgeUpdateService>
		 ("/kcl_rosplan/update_knowledge_base")),
	 kq_client_(nh_.serviceClient<rosplan_knowledge_msgs::GetAttributeService>
		 ("/kcl_rosplan/get_current_knowledge"))
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
	{
		ROS_INFO("Instance [%s] added", instance_type.c_str());
		return true;
	}

}

KMS_Client::Fact KMS_Client::getFactFromString(std::string predicate, const std::vector<std::string>&ops)
{
	Fact ret;

	size_t pos;
	pos = predicate.find(" ");
	predicate = predicate.substr(pos+1, std::string::npos);

	for(int i=0; i<ops.size(); i++)
	{
		pos = predicate.find(" ");

		ret.push_back(Fact_Values(ops[i], predicate.substr(0, pos)));
		predicate = predicate.substr(pos+1, std::string::npos);
	}

	return ret;
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
	{
		ROS_INFO("Fact [%s] removed", attribute_name.c_str());
		return true;
	}
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
	{
		ROS_INFO("Fact [%s] added", attribute_name.c_str());
		return true;
	}
}

std::list<std::string>
KMS_Client::getFactsWithPredicate(const std::string& predicate,
	const std::vector<std::string>& operators)
{
	std::list<std::string> ret;

	rosplan_knowledge_msgs::GetAttributeService query_fact_instance;
	query_fact_instance.request.predicate_name = predicate;

	if (!kq_client_.call(query_fact_instance)) {
		ROS_ERROR("Could not query for facts with predicate [%s]", predicate.c_str());
		return ret;
	}

	std::vector<rosplan_knowledge_msgs::KnowledgeItem>::iterator it;
	for(it=query_fact_instance.response.attributes.begin(); it!=query_fact_instance.response.attributes.end();++it)
	{
		std::string ret_predicate(predicate);
		std::vector<std::string> ops(operators.size());

		std::vector<diagnostic_msgs::KeyValue>::iterator it2;
		for(it2=it->values.begin(); it2!=it->values.end(); ++it2)
		{
			for(int i=0; i<operators.size(); i++)
				if(operators[i] == it2->key)
				ops[i] = it2->value;
		}

		for(int i=0; i<ops.size(); i++)
			ret_predicate = ret_predicate + " " + ops[i];

		ret.push_back(ret_predicate);
	}

	return ret;
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
