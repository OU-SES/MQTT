#pragma once
#include "VariableHeader.h"

class ConnackVariableHeader : public VariableHeader
{
public:
	//This constructure should be used in general cases
	ConnackVariableHeader(int session_present_, int connect_reason_) : VariableHeader()
	{
		session_present = session_present_;
		connect_reason = connect_reason_;
	}

	//This constructure is used only when test or generate temporary variable of ConnackVariableHeader
	ConnackVariableHeader() : VariableHeader()
	{
		session_present = 0;
		connect_reason = mqttpacket::REASON_CODE_SUCCESS;
	}

	int get_session_present() { return session_present; }
	int get_connect_reason() { return connect_reason; }

private:
	int session_present;
	int connect_reason;
};
