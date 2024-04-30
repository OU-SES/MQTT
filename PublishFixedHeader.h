#pragma once
#include "FixedHeader.h"
#include "MQTTControlPacketList.h"

class PublishFixedHeader : public FixedHeader
{
public:
	PublishFixedHeader() : FixedHeader(mqttpacket::MQTT_CONTROL_PACKET_TYPE_PUBLISH, mqttpacket::DEFAULT_FLAGS) {}
	PublishFixedHeader(int flags) : FixedHeader(mqttpacket::MQTT_CONTROL_PACKET_TYPE_PUBLISH, flags)
	{
		dup = flags & 0x08;
		qos = flags & 0x03;
	}
	PublishFixedHeader(int dup, int qos, int retain) : FixedHeader(mqttpacket::MQTT_CONTROL_PACKET_TYPE_PUBLISH, (dup << 3) | (qos <<1) | retain) {}

	void set_pub_flags(int flags)
	{
		dup = flags & 0x08;
		qos = flags & 0x03;
	}

	int get_dup() 
	{
		return dup;
	}

	int get_qos()
	{
		return qos;
	}

private:
	int dup;
	int qos;
};
