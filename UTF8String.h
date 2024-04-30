#pragma once
#include <string>
class UTF8String
{
public:
	explicit UTF8String(const std::string& data)
		: data(data)
	{
		size_t length = data.length();
		msb = length / 256;
		lsb = length % 256;
	}

	UTF8String() : msb (0), lsb(0), data("") {}

	int get_msb() { return msb; }
	int get_lsb() { return lsb; }
	std::string get_data() { return data; }

	void set_data(std::string data_)
	{
		size_t length = data_.length();
		msb = length / 256;
		lsb = length % 256;
		data = data_;
	}
	
private:
	int msb=0;
	int lsb=0;
	std::string data;
};