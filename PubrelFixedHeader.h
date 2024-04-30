#pragma once
#include "FixedHeader.h"
#include "MQTTControlPacketList.h"

class PubrelFixedHeader : public FixedHeader
{
public:
	PubrelFixedHeader() : FixedHeader(mqttpacket::MQTT_CONTROL_PACKET_TYPE_PUBREL, mqttpacket::DEFAULT_FLAGS) {}
};
