#pragma once
#include "MQTTMessage.h"
#include "SubackFixedHeader.h"
#include "SubackPayload.h"
#include "SubackVariableHeader.h"

class MQTTSubackMessage : public MQTTMessage
{
public:
	int get_message_type()
	{
		return fHeader.get_control_packet_type();
	}

	void set_fHeader(SubackFixedHeader& fHeader_) { fHeader = fHeader_; }
	void set_vHeader(SubackVariableHeader& vHeader_) { vHeader = vHeader_; }
	void set_payload(SubackPayload& payload_) { payload = payload_; }
	SubackFixedHeader get_fHeader() { return fHeader; }
	SubackVariableHeader get_vHeader() { return vHeader; }
	SubackPayload get_payload() { return payload; }
	
private:
	SubackFixedHeader fHeader;
	SubackVariableHeader vHeader;
	SubackPayload payload;
};
