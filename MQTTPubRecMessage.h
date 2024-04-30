#pragma once
#include "MQTTMessage.h"
#include "PubRecVariableHeader.h"
#include "PubRecFixedHeader.h"

class MQTTPubrecMessage : public MQTTMessage
{
public:
	int get_message_type()
	{
		return fHeader.get_control_packet_type();
	}

	void set_fHeader(PubrecFixedHeader& fHeader_) { fHeader = fHeader_; }
	void set_vHeader(PubrecVariableHeader& vHeader_) { vHeader = vHeader_; }
	PubrecFixedHeader get_fHeader() { return fHeader; }
	PubrecVariableHeader get_vHeader() { return vHeader; }

private:
	PubrecFixedHeader fHeader;
	PubrecVariableHeader vHeader;
};

