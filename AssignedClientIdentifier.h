#pragma once
#include "DataConvertor.h"
#include "MQTTControlPacketList.h"
#include "Property.h"
#include "UTF8String.h"

class AssignedClientIdentifier : public Property
{
public:
	AssignedClientIdentifier(std::string reference_) : Property(mqttpacket::MQTT_PROPERTY_ASSIGNED_CLIENT_IDENTIFIER)
	{
		server_identifier.set_data(reference_);
	}

	AssignedClientIdentifier() : Property(mqttpacket::MQTT_PROPERTY_ASSIGNED_CLIENT_IDENTIFIER)
	{
		server_identifier.set_data("");
	}
	
	void set_identifier(std::string identifier_) { server_identifier.set_data(identifier_); }
	std::string get_identifier() { return server_identifier.get_data(); }

	void get_data(std::vector<char>* data) override
	{
		data_convert(data, identifier);
		data_convert(data, server_identifier);
	}
private:
	UTF8String server_identifier;
};
