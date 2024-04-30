#pragma once
#include "MQTTMessage.h"
#include "PubrelFixedHeader.h"
#include "PubrelVariableHeader.h"

class MQTTPubrelMessage : public MQTTMessage
{
public:
	int get_message_type()
	{
		return fHeader.get_control_packet_type();
	}

	void set_fHeader(PubrelFixedHeader& fHeader_) { fHeader = fHeader_; }
	void set_vHeader(PubrelVariableHeader& vHeader_) { vHeader = vHeader_; }
	PubrelFixedHeader get_fHeader() { return fHeader; }
	PubrelVariableHeader get_vHeader() { return vHeader; }

private:
	PubrelFixedHeader fHeader;
	PubrelVariableHeader vHeader;
};