#pragma once
class TwoByteInteger
{
public:
	explicit TwoByteInteger(int data)
		: data(data)
	{
		length = 2;
	}

	explicit TwoByteInteger()
		: data(0)
	{
		length = 2;
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