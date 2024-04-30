#pragma once
#include "Property.h"
#include "UTF8String.h"
#include "MQTTControlPacketList.h"
#include "DataConvertor.h"

class ServerReference : public Property
{
public:
	ServerReference(std::string reference_) : Property(mqttpacket::MQTT_PROPERTY_SERVER_REFERENCE), reference(reference_)
	{}

	ServerReference() : Property(mqttpacket::MQTT_PROPERTY_SERVER_REFERENCE), reference("N/A")
	{}
	void set_reference(std::string reference_) { reference.set_data(reference_); }
	std::string get_reference() { return reference.get_data(); }
	
	void get_data(std::vector<char> *data) override
	{
		data_convert(data, identifier);
		data_convert(data, reference);
	}
private:
	UTF8String reference;
};
