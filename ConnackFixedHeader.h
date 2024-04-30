#include "FixedHeader.h"
#include "MQTTControlPacketList.h"
#pragma once
class ConnackFixedHeader : public FixedHeader 
{
public:
	ConnackFixedHeader(): FixedHeader(mqttpacket::MQTT_CONTROL_PACKET_TYPE_CONNACT, mqttpacket::DEFAULT_FLAGS)
	{}
};