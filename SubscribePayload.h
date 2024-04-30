#pragma once
#include <vector>
#include "UTF8String.h"

struct Topic
{
	UTF8String filter;
	int maximum_qos;
	int no_local;
	int retain;
	int retain_handling;
	
	Topic(std::string name, int qos, int no_local_, int retain, int retain_handling_) :
		filter(UTF8String(name)), maximum_qos(qos), no_local(no_local_), retain(retain), retain_handling(retain_handling_)
	{}

	Topic() :
		filter(UTF8String("N/A")), maximum_qos(0), no_local(0), retain(0), retain_handling(0)
	{}

	std::string get_filter_contents(){ return filter.get_data(); }
	UTF8String get_filter() { return filter; }
	int get_maximum_qos() { return maximum_qos; }
	int get_nolocal() { return no_local; }
	int get_retain() { return retain; }
	int get_retain_handling() { return retain_handling; }
};

class SubscribePayload
{
public:
	SubscribePayload(){}

	int add_topic_filter(std::string filter, int m_qos, int no_local, int retain, int retain_handling)
	{
		topic_filter.push_back(Topic(filter, m_qos, no_local, retain, retain_handling));
		return topic_filter.size();
	}

	Topic pop_topic()
	{
		Topic result;
		if (!topic_filter.empty()) result = topic_filter.back();
		topic_filter.pop_back();
		return result;
	}

	std::vector<Topic> get_list() { return topic_filter; }
	
private:
	std::vector<Topic> topic_filter;
};


