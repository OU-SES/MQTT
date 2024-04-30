#pragma once
#include "FixedHeader.h"
#include "MQTTControlPacketList.h"

class PubrecFixedHeader : public FixedHeader
{
public:
	PubrecFixedHeader() : FixedHeader(mqttpacket::MQTT_CONTROL_PACKET_TYPE_PUBREC, mqttpacket::DEFAULT_FLAGS) {}
};
