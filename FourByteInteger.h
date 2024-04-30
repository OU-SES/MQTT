#pragma once
class FourByteInteger
{
public:
	explicit FourByteInteger(int data)
		: data(data)
	{
		length = 4;
	}

	explicit FourByteInteger()
		: data(0)
	{
		length = 4;
	}

	int get_length() const
	{
		return length;
	}

	int get_data() const
	{
		return data;
	}

	void set_data(int data_) { data = data_; }
private:
	int length;
	int data;
};