#pragma once
#include "VariableHeader.h"

class PublishVariableHeader : public VariableHeader
{
public:
	PublishVariableHeader(std::string topic_name_, int identifier) : VariableHeader()
	{
		topic_name.set_data(topic_name_);
		packet_identifier.set_data(identifier);
	}

	PublishVariableHeader() : VariableHeader()
	{
		topic_name.set_data("");
		packet_identifier.set_data(0);
	}

	void set_topic_name(std::string topic_name_) { topic_name.set_data(topic_name_); }
	std::string get_topic_name_str() { return topic_name.get_data(); }
	void set_client_identifier(int identifier) { packet_identifier.set_data(identifier); }
	int get_client_identifier_int() { return packet_identifier.get_data(); }
	UTF8String get_topic_name() { return topic_name; }
	TwoByteInteger get_packet_identifier() { return packet_identifier; }
private:
	UTF8String topic_name;
	TwoByteInteger packet_identifier;
};