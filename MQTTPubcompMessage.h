#pragma once
#include "MQTTMessage.h"
#include "PubcompFixedHeader.h"
#include "PubcompVariableHeader.h"

class MQTTPubcompMessage : public MQTTMessage
{
public:
	int get_message_type()
	{
		return fHeader.get_control_packet_type();
	}

	void set_fHeader(PubcompFixedHeader& fHeader_) { fHeader = fHeader_; }
	void set_vHeader(PubcompVariableHeader& vHeader_) { vHeader = vHeader_; }
	PubcompFixedHeader get_fHeader() { return fHeader; }
	PubcompVariableHeader get_vHeader() { return vHeader; }

private:
	PubcompFixedHeader fHeader;
	PubcompVariableHeader vHeader;
};
