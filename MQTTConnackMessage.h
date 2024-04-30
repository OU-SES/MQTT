#pragma once
#include "ConnackFixedHeader.h"
#include "ConnackVariableHeader.h"
#include "MQTTMessage.h"

class MQTTConnackMessage : public MQTTMessage
{
public:
	MQTTConnackMessage()
	{}

	ConnackFixedHeader get_fHeader() const
	{
		return fHeader;
	}

	void set_fHeader(const ConnackFixedHeader& f_header)
	{
		fHeader = f_header;
	}

	ConnackVariableHeader get_vHeader() const
	{
		return vHeader;
	}

	void set_vHeader(const ConnackVariableHeader& v_header)
	{
		vHeader = v_header;
	}

	int get_message_type()
	{
		return fHeader.get_control_packet_type();
	}

private:
	ConnackFixedHeader fHeader;
	ConnackVariableHeader vHeader;
};
