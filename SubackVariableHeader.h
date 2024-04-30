#pragma once
#include "VariableHeader.h"

class SubackVariableHeader : public VariableHeader
{
public:

	SubackVariableHeader(int packet_identifier_) : VariableHeader(),
		packet_identifier(packet_identifier_)
	{}

	SubackVariableHeader() : VariableHeader()
	{
		packet_identifier.set_data(0);
	}

	TwoByteInteger get_packet_identifier() { return packet_identifier; }

private:
	TwoByteInteger packet_identifier;
};
