#pragma once
class FixedHeader {
private:
	int control_packet_type;
	int flags;
	unsigned int length;
public:
	FixedHeader(int control_type, int flags_) : control_packet_type(control_type), flags(flags_), length(0){}
	FixedHeader() : control_packet_type(0), flags(0), length(0) {}
	void set_flags(int flags_) { flags = flags_; }
	void set_control_packet_type(int type_) { control_packet_type = type_; }
	void set_length(unsigned int length_) { length = length_; }
	int get_control_packet_type() { return control_packet_type; }
	int get_flags() { return flags; }
	unsigned int get_length() { return length; }
};