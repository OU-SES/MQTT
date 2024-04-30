#pragma once
#include "FixedHeader.h"
#include "MQTTControlPacketList.h"
#pragma once
class ConnectFixedHeader : public FixedHeader
{
public:
	ConnectFixedHeader() : FixedHeader(mqttpacket::MQTT_CONTROL_PACKET_TYPE_CONNECT, mqttpacket::DEFAULT_FLAGS) {}
	ConnectFixedHeader(int flags) : FixedHeader(mqttpacket::MQTT_CONTROL_PACKET_TYPE_CONNECT, flags) {}
};