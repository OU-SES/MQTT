#pragma once
#include <iterator>
#include <sstream>
#include <vector>

class VariableByteInteger
{
private:
	int value=0;
	std::vector<char> variable_byte_int;
	const int LSB = 128;
	const int MSB = 128;
	const int ONE_BYTE_LENGTH = 1;
	
	void convert_from_int_into_variable_byte()
	{
		int intermediate = value;
		int temp_calc;
		char* variable_data;
		char* end_variable;
		bool first_byte = true;
		do
		{
			temp_calc = intermediate % LSB;
			intermediate /= LSB;
			if (first_byte) 
			{
				first_byte = false;
			}
			else 
			{
				temp_calc += MSB;
			}

			variable_data = reinterpret_cast<char*>(&temp_calc);
			end_variable = variable_data + ONE_BYTE_LENGTH;
			std::copy(variable_data, end_variable, std::back_inserter(variable_byte_int));
		} while (intermediate > 0);
		std::reverse(variable_byte_int.begin(), variable_byte_int.end());
	}
	
	void convert_from_variable_byte_into_int()
	{
		int multiply = pow(MSB, variable_byte_int.size() - 1);
		unsigned int temp_int=0;
		for(char temp_variable : variable_byte_int)
		{
			//temp_int = static_cast<unsigned int>(temp_variable);
			temp_int = 0x000000ff & temp_variable;
			//memcpy(&temp_int, &temp_variable, sizeof(temp_variable));
			if ((temp_int & MSB) == MSB) temp_int -= MSB;
			
			temp_int *= multiply;
			value += temp_int;
			multiply /= 128;
		}
	}
	
public:
	VariableByteInteger() : value(0)
	{
		convert_from_int_into_variable_byte();
	}
	
	VariableByteInteger(int value_) :
		value(value_)
	{
		convert_from_int_into_variable_byte();
	}

	VariableByteInteger(std::vector<char> list) : variable_byte_int(list)
	{
		convert_from_variable_byte_into_int();
	}

	int get_value() { return value; }
	std::vector<char> get_variable_value() { return variable_byte_int; }

	void set_data(int data)
	{
		value = data;
		convert_from_int_into_variable_byte();
	}

	void set_list(std::vector<char> list)
	{
		variable_byte_int = list;
		convert_from_variable_byte_into_int();
	}
};
