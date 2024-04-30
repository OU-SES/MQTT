#pragma once
#include "FixedHeader.h"
#include "MQTTControlPacketList.h"

class SubscribeFixedHeader : public FixedHeader
{
public:
	SubscribeFixedHeader() : FixedHeader(mqttpacket::MQTT_CONTROL_PACKET_TYPE_SUBSCRIBE, mqttpacket::DEFAULT_FLAGS) {}
};
