#pragma once
#include "Property.h"
#include <vector>
#include <iterator>
#include "SessionExpiryInterval.h"

class VariableHeader 
{
private:
	bool packet_identifier_b;
	int packet_identifier;
	size_t property_length;
	std::vector <std::shared_ptr<Property>> properties;
public:
	VariableHeader(int packet_identifier_)
		: packet_identifier_b(true), packet_identifier(packet_identifier_), property_length(0)
	{

	}

	VariableHeader()
		: packet_identifier_b(false), packet_identifier(0), property_length(0)
	{

	}

	size_t get_property_length() const
	{
		return property_length;
	}

	void set_property_length(size_t property_length)
	{
		this->property_length = property_length;
	}

	bool get_packet_identifier_b() const
	{
		return packet_identifier_b;
	}

	void set_packet_identifier_b(const bool packet_identifier_b)
	{
		this->packet_identifier_b = packet_identifier_b;
	}

	int get_packet_identifier() const
	{
		return packet_identifier;
	}

	void set_packet_identifier(const int packet_identifier)
	{
		this->packet_identifier = packet_identifier;
	}

	void add_property(std::shared_ptr<Property> property_)
	{
		properties.push_back(property_);
		set_property_length(properties.size());
	}

	std::vector<std::shared_ptr<Property>> get_property_list()
	{
		return properties;
	}
};

