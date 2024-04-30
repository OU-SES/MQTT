#pragma once
#include "MQTTMessage.h"
#include "SubscribeFixedHeader.h"
#include "SubscribePayload.h"
#include "SubscribeVariableHeader.h"

class MQTTSubscribeMessage : public MQTTMessage
{
public:
	int get_message_type()
	{
		return fHeader.get_control_packet_type();
	}

	void set_fHeader(SubscribeFixedHeader& fHeader_) { fHeader = fHeader_; }
	void set_vHeader(SubscribeVariableHeader& vHeader_) { vHeader = vHeader_; }
	void set_payload(SubscribePayload& payload_) { payload = payload_; }
	SubscribeFixedHeader get_fHeader() { return fHeader; }
	SubscribeVariableHeader get_vHeader() { return vHeader; }
	SubscribePayload get_payload() { return payload; }
private:
	SubscribeFixedHeader fHeader;
	SubscribeVariableHeader vHeader;
	SubscribePayload payload;
};
