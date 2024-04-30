#pragma once
#include "FixedHeader.h"
#include "MQTTControlPacketList.h"

class PubcompFixedHeader : public FixedHeader
{
public:
	PubcompFixedHeader() : FixedHeader(mqttpacket::MQTT_CONTROL_PACKET_TYPE_PUBCOMP, mqttpacket::DEFAULT_FLAGS) {}
};
