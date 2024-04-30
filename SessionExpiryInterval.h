#pragma once
#include "DataConvertor.h"
#include "Property.h"
#include "MQTTControlPacketList.h"
class SessionExpiryInterval : public Property
{
	int data;

public:
	SessionExpiryInterval(int data_) : Property(mqttpacket::MQTT_PROPERTY_SESSION_EXPIRY_INTERVAL), data(data_)
	{}

	SessionExpiryInterval() : Property(mqttpacket::MQTT_PROPERTY_SESSION_EXPIRY_INTERVAL), data(0)
	{}
	
	int get_data_int() const
	{
		return data;
	}

	void set_data(int data)
	{
		this->data = data;
	}
	
	void get_data(std::vector<char>* data_) override
	{
		data_convert(data_, identifier);
		data_convert(data_, FourByteInteger(data));
	}
};
