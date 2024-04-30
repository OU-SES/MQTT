#pragma once
#include "DataConvertor.h"
#include "MQTTControlPacketList.h"
#include "Property.h"

class SubscriptionIdentifierAvailable : public Property
{
public:
	SubscriptionIdentifierAvailable (bool support_) : Property(mqttpacket::MQTT_PROPERTY_SUBSCRIPTION_IDENTIFIER_AVAILABLE), support(support_)
	{}
	bool get_support() { return support; }

	void get_data(std::vector<char>* data) override
	{
		data_convert(data, identifier);
		data_convert(data, support);
	}
private:
	bool support;
};
