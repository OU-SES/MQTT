#pragma once
#include "VariableHeader.h"

class SubscribeVariableHeader : public VariableHeader
{
public:

	SubscribeVariableHeader(int packet_identifier_) : VariableHeader(),
		packet_identifier(packet_identifier_)
	{}

	SubscribeVariableHeader() : VariableHeader()
	{
		packet_identifier.set_data(0);
	}

	TwoByteInteger get_packet_identifier() { return packet_identifier; }

private:
	TwoByteInteger packet_identifier;
	//subscription identifier is not supported yet.
};
