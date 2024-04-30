#pragma once
#include <vector>

class Property
{
protected:
	int identifier;
public:
	Property(){}
	
	Property(int identifier)
		: identifier(identifier)
	{}
	
	int get_identifier() const
	{
		return identifier;
	}

	void set_identifier(int identifier)
	{
		this->identifier = identifier;
	}

	virtual void get_data(std::vector<char> *data){}
};
