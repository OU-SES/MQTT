#pragma once
#include "VariableHeader.h"
#include "UTF8String.h"
#include "TwoByteInteger.h"

class ConnectVariableHeader : public VariableHeader
{
public:

	ConnectVariableHeader(int version_, int flags_, int keep_alive_) : VariableHeader()
	{
		protocol_name.set_data("MQTT");
		protocol_version = version_;
		connect_flags = flags_;
		keep_alive.set_data(keep_alive_);
	}

	ConnectVariableHeader() : VariableHeader()
	{
		protocol_name.set_data("MQTT");
		protocol_version = 0;
		connect_flags = 0;
		keep_alive.set_data(0);
	}

	UTF8String get_protocol_name() { return protocol_name; }

	void set_protocol_name(UTF8String protocol) { protocol_name = protocol; }

	int get_protocol_version() { return protocol_version; }

	void set_protocol_version(int version) { protocol_version = version; }

	int get_connect_flags() { return connect_flags; }

	void set_connect_flags(int flags) { connect_flags = flags; }

	TwoByteInteger get_keep_alive() { return keep_alive; }

	void set_keep_alive(int k_alive) { keep_alive.set_data(k_alive); }

private:
	UTF8String protocol_name;
	int protocol_version;
	int connect_flags;
	TwoByteInteger keep_alive;
};
