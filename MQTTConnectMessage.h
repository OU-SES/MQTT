#pragma once
#include "ConnectFixedHeader.h"
#include "ConnectPayload.h"
#include "ConnectVariableHeader.h"
#include "MQTTMessage.h"
class MQTTConnectMessage : public MQTTMessage
{
public:
	MQTTConnectMessage() : payload("","")
	{}

	ConnectFixedHeader get_fHeader() const
	{
		return fHeader;
	}

	void set_fHeader(const ConnectFixedHeader& f_header)
	{
		fHeader = f_header;
	}

	ConnectVariableHeader get_vHeader() const
	{
		return vHeader;
	}

	void set_vHeader(ConnectVariableHeader& v_header)
	{
		//vHeader = v_header;
		vHeader.set_connect_flags(v_header.get_connect_flags());
		vHeader.set_keep_alive(v_header.get_keep_alive().get_data());
		vHeader.set_packet_identifier(v_header.get_packet_identifier());
		vHeader.set_packet_identifier_b(v_header.get_packet_identifier_b());
		auto fucking_protocol = v_header.get_protocol_name();
		auto fucking_stupid = vHeader.get_protocol_name();
		vHeader.set_protocol_name(fucking_protocol);
		vHeader.set_protocol_version(v_header.get_protocol_version());

		auto properties = v_header.get_property_list();
		for (auto property : properties) 
		{
			vHeader.add_property(property);
		}
	}

	int get_message_type()
	{
		return fHeader.get_control_packet_type();
	}

	ConnectPayload get_payload()
	{
		return payload;
	}

	void set_payload( const ConnectPayload& payload_ )
	{
		payload = payload_;
	}
	
private:
	ConnectFixedHeader fHeader;
	ConnectVariableHeader vHeader;
	ConnectPayload payload;
};