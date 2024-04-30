#pragma once
#include <string>



#include "DataConvertor.h"
#include "MQTTControlPacketList.h"
#include "Property.h"

class UserProperty : public Property
{
public:
	UserProperty(std::string reference_) : Property(mqttpacket::MQTT_PROPERTY_USER_PROPERTY), reference(reference_)
	{}
	UserProperty() : Property(mqttpacket::MQTT_PROPERTY_USER_PROPERTY), reference("N/A")
	{}
	void set_reference(std::string reference_) { reference.set_data(reference_); }
	std::string get_reference() { return reference.get_data(); }

	void get_data(std::vector<char>* data) override
	{
		data_convert(data, identifier);
		data_convert(data, reference);
	}

	void get_reference(std::vector<char>* data) 
	{
		data_convert(data, reference);
	}
private:
	UTF8String reference;
};
