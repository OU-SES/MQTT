#pragma once
#include "MQTTMessage.h"
#include "PubackFixedHeader.h"
#include "PubackVariableHeader.h"

class MQTTPubackMessage : public MQTTMessage
{
public:
	int get_message_type()
	{
		return fHeader.get_control_packet_type();
	}

	void set_fHeader(PubackFixedHeader& fHeader_) { fHeader = fHeader_; }
	void set_vHeader(PubackVariableHeader& vHeader_) { vHeader = vHeader_; }
	PubackFixedHeader get_fHeader() { return fHeader; }
	PubackVariableHeader get_vHeader() { return vHeader; }
	
private:
	PubackFixedHeader fHeader;
	PubackVariableHeader vHeader;
};
