#pragma once
#include "MQTTMessage.h"
#include "PublishFixedHeader.h"
#include "PublishVariableHeader.h"

class MQTTPublishMessage : public MQTTMessage
{
public:
	MQTTPublishMessage()
	{
		payload = UTF8String();
	}

	PublishFixedHeader get_fHeader() const
	{
		return fHeader;
	}

	void set_fHeader(const PublishFixedHeader& f_header)
	{
		fHeader = f_header;
	}

	PublishVariableHeader get_vHeader() const
	{
		return vHeader;
	}

	void set_vHeader(const PublishVariableHeader& v_header)
	{
		vHeader = v_header;
	}

	int get_message_type()
	{
		return fHeader.get_control_packet_type();
	}

	UTF8String get_payload()
	{
		return payload;
	}

	void set_payload(const UTF8String &data_)
	{
		payload = data_;
	}

private:
	PublishFixedHeader fHeader;
	PublishVariableHeader vHeader;
	UTF8String payload;
};
