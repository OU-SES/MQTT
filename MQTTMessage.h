#pragma once
#include "FixedHeader.h"
#include "VariableHeader.h"
#include <iostream>
class MQTTMessage 
{
public:
	virtual int get_packet_identifier() { return vHeader.get_packet_identifier(); }
	int get_packet_() { return fHeader.get_control_packet_type(); }
private:
	FixedHeader fHeader;
	VariableHeader vHeader;
};