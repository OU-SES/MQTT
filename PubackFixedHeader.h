#pragma once
#include "FixedHeader.h"
#include "MQTTControlPacketList.h"

class PubackFixedHeader : public FixedHeader
{
public:
	PubackFixedHeader() : FixedHeader(mqttpacket::MQTT_CONTROL_PACKET_TYPE_PUBACK, mqttpacket::DEFAULT_FLAGS) {}
};
