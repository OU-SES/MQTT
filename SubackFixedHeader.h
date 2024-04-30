#pragma once
#include "FixedHeader.h"
#include "MQTTControlPacketList.h"

class SubackFixedHeader : public FixedHeader
{
public:
	SubackFixedHeader() : FixedHeader(mqttpacket::MQTT_CONTROL_PACKET_TYPE_SUBACK, mqttpacket::DEFAULT_FLAGS) {}
};
