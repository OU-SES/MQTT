#pragma once
#include <string>

#include "DataConvertor.h"
#include "MQTTControlPacketList.h"
#include "Property.h"

class PayloadFormatIndicator : public Property
{
public:
	PayloadFormatIndicator(int format) : Property(mqttpacket::MQTT_PROPERTY_PAYLOAD_FORMAT_INDICATOR)
	{
		format_type = format;
	}

	PayloadFormatIndicator() : Property(mqttpacket::MQTT_PROPERTY_PAYLOAD_FORMAT_INDICATOR)
	{
		format_type = mqttpacket::MQTT_FORMAT_UTF8;
	}

	void set_format_type(int format) { format_type = format; }
	int get_format_type() { return format_type; }

	void get_data(std::vector<char>* data) override
	{
		data_convert(data, identifier);
		data_convert(data, format_type);
	}
private:
	int format_type;
};
