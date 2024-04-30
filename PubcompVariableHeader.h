#pragma once
#include "VariableHeader.h"

class PubcompVariableHeader : public VariableHeader
{
public:

	PubcompVariableHeader(int packet_identifier_, int reason_code_) : VariableHeader(),
		packet_identifier(packet_identifier_), reason_code(reason_code_)
	{}

	PubcompVariableHeader() : VariableHeader()
	{
		packet_identifier.set_data(0);
		reason_code = 0;
	}

	TwoByteInteger get_packet_identifier() { return packet_identifier; }
	int get_reason_code() { return reason_code; }

private:
	TwoByteInteger packet_identifier;
	int reason_code;
};
