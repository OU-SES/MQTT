#include "DataConvertor.h"

#include <iterator>
#include <sstream>

/*
 * convert UTF8String into list of char
 * It consist of 1 byte (MSB), 1 byte (LSB), and n bytes (String)
 * Converted output will be stored at argument vector
 */
int data_convert(std::vector<char> * packet, UTF8String data)
{
	int msb = data.get_msb();
	int lsb = data.get_lsb();
	std::string contents = data.get_data();
	char* contents_c = const_cast<char*>(contents.c_str());
	char* end_contents = contents_c + contents.length();
	char* msb_c = reinterpret_cast<char*>(&msb);
	char* end_msb = msb_c + 1;
	char* lsb_c = reinterpret_cast<char*>(&lsb);
	char* end_lsb = lsb_c + 1;
	std::copy(msb_c, end_msb, std::back_inserter(*packet));
	std::copy(lsb_c, end_lsb, std::back_inserter(*packet));
	std::copy(contents_c,end_contents, std::back_inserter(*packet));
	return 0;
}

/*
 * convert int into list of char
 * It consist of 1 byte (data) and 1 byte (data)
 * Converted output will be stored at argument vector
 */
int data_convert(std::vector<char> *packet, TwoByteInteger data)
{
	std::stringstream convert;
	int first_int = (data.get_data() / 256) & 0xFF;
	int second_int = (data.get_data() % 256) & 0xFF;
	char* first_int_c = reinterpret_cast<char*>(&first_int);
	char* end_first = first_int_c + 1;
	char* second_int_c = reinterpret_cast<char*>(&second_int);
	char* end_second = second_int_c + 1;
	std::copy(first_int_c,end_first, std::back_inserter(*packet));
	std::copy(second_int_c, end_second, std::back_inserter(*packet));
	return 0;
}

/*
 * convert int into list of char
 * It consist of 4 byte (data) 
 * Converted output will be stored at argument vector
 */
int data_convert(std::vector<char>* packet, FourByteInteger data)
{
	std::stringstream convert;
	int value = data.get_data();
	int first_int = (value	& 0xff000000) >> 24;
	int second_int = (value	& 0x00ff0000) >> 16;
	int third_int = (value	& 0x0000ff00) >> 8;
	int fourth_int = value	& 0x000000ff;
	char* first_int_c = reinterpret_cast<char*>(&first_int);
	char* end_first = first_int_c + 1;
	char* second_int_c = reinterpret_cast<char*>(&second_int);
	char* end_second = second_int_c + 1;
	char* third_int_c = reinterpret_cast<char*>(&third_int);
	char* end_third = third_int_c + 1;
	char* fourth_int_c = reinterpret_cast<char*>(&fourth_int);
	char* end_fourth = fourth_int_c + 1;

	std::copy(first_int_c, end_first, std::back_inserter(*packet));
	std::copy(second_int_c, end_second, std::back_inserter(*packet));
	std::copy(third_int_c, end_third, std::back_inserter(*packet));
	std::copy(fourth_int_c, end_fourth, std::back_inserter(*packet));
	return 0;
}

/*
 * convert int into list of char
 * The string consist of 1 byte (data)
 * Converted output will be stored at argument vector
 */
int data_convert(std::vector<char> *packet, int data)
{
	char* result = reinterpret_cast<char*>(&data);
	char* end = result + 1;
	std::copy(result, end, std::back_inserter(*packet));
	return 0;
}

int data_convert_front(std::vector<char>* packet, int data)
{
	char* result = reinterpret_cast<char*>(&data);
	packet->insert(packet->begin(),*result);
	return 0;
}

int reverse_data_convert(int* dst, const char * src)
{
	*dst = *src;
	return 1;
}

int reverse_data_convert(UTF8String* dst, const char* src)
{
	unsigned int msb = src[0];
	msb = 0x000000ff & src[0];
	unsigned int lsb = src[1];
	lsb = 0x000000ff & src[1];
	int string_range = msb * 256 + lsb;
	std::string value(&src[2],&src[2 + string_range]);
	dst->set_data(value);
	return string_range + 2;
}

int reverse_data_convert(TwoByteInteger* dst, const char* src)
{
	int msb = src[0] & 0xFF;
	int lsb = src[1] & 0xFF;
	int value = msb * 256 + lsb;
	dst->set_data(value);
	return 2;
}

int reverse_data_convert(FourByteInteger* dst, const char* src)
{
	int first_byte = src[0];
	int second_byte = src[1];
	int third_byte = src[2];
	int fourth_byte = src[3];
	int value = 
		first_byte *	0x01000000 +
		second_byte *	0x00010000 +
		third_byte *	0x00000100 +
		fourth_byte;
	dst->set_data(value);
	return 4;
}

int reverse_data_convert(VariableByteInteger *dst, const char* src)
{
	std::vector<char> vInteger;
	int counter = 0;
	char temp = src[0];
	int index = 0;
	for(; (temp & 128) == 128; counter++)
	{
		temp = src[index];
		vInteger.push_back(temp);
		index++;
	}
	if (index == 0)
	{
		counter++;
		vInteger.push_back(temp);
	}
	dst->set_list(vInteger);
	return counter;
}
