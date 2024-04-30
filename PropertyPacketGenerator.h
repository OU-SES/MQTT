#pragma once
#include <memory>
#include <vector>
#include "MQTTControlPacketList.h"
#include "Property.h"
#include "ServerReference.h"

typedef std::vector <std::shared_ptr<Property>> property_list;
typedef std::vector <char> * packet_data;
namespace property
{
	void convert_property(property_list property_list_, packet_data data) 
	{
		int property_type;
		for (std::shared_ptr<Property> temp_p : property_list_)
		{
			//length_of_properties = property_convert(property_container, temp_p);
			property_type = temp_p->get_identifier();
			switch(property_type)
			{
			case mqttpacket::MQTT_PROPERTY_SERVER_REFERENCE:
				ServerReference* reference = temp_p.get();
				break;
			case mqttpacket::MQTT_PROPERTY_SESSION_EXPIRY_INTERVAL:
				break;
			case mqttpacket::MQTT_PROPERTY_SUBSCRIPTION_IDENTIFIER_AVAILABLE:
				break;
			}
		}
	}
	
}
