#include "PacketGenerator.h"
#include "MQTTControlPacketList.h"
#include "ConnectVariableHeader.h"
#include "DataConvertor.h"
#include "VariableByteInteger.h"

int convert_connect_into_packet(MQTTConnectMessage * message, std::vector<char> * packet)
{
	const int message_type = message->get_message_type();
	if (message_type != mqttpacket::MQTT_CONTROL_PACKET_TYPE_CONNECT) return mqttpacket::PACKET_ERROR_PACKET_HEADER;
	connect_variable_to_string(message, packet);
	return mqttpacket::COMPLETE_WITH_NO_ERROR;
}

int convert_connact_into_packet(MQTTConnackMessage* message, std::vector<char> *packet)
{
	int message_type = message->get_message_type();
	if (message_type != mqttpacket::MQTT_CONTROL_PACKET_TYPE_CONNACT) return mqttpacket::PACKET_ERROR_PACKET_HEADER;
	connact_variable_to_vector(message, packet);
	return mqttpacket::COMPLETE_WITH_NO_ERROR;
}

int convert_publish_into_packet(MQTTPublishMessage* message, std::vector<char>* packet)
{
	int message_type = message->get_message_type();
	if (message_type != mqttpacket::MQTT_CONTROL_PACKET_TYPE_PUBLISH) return mqttpacket::PACKET_ERROR_PACKET_HEADER;
	publish_variable_to_vector(message, packet);
	return mqttpacket::COMPLETE_WITH_NO_ERROR;
}

int convert_pubrec_into_packet(MQTTPubrecMessage* message, std::vector<char>* packet)
{
	int message_type = message->get_message_type();
	std::vector<const char*> output_packet;
	if (message_type != mqttpacket::MQTT_CONTROL_PACKET_TYPE_PUBREC) return mqttpacket::PACKET_ERROR_PACKET_HEADER;
	pubrec_variable_to_vector(message, packet);
}

int convert_pubrel_into_packet(MQTTPubrelMessage* message, std::vector<char>* packet)
{
	int message_type = message->get_message_type();
	std::vector<const char*> output_packet;
	if (message_type != mqttpacket::MQTT_CONTROL_PACKET_TYPE_PUBREL) return mqttpacket::PACKET_ERROR_PACKET_HEADER;
	pubrel_variable_to_vector(message, packet);
}

int convert_puback_into_packet(MQTTPubackMessage* message, std::vector<char>* packet)
{
	int message_type = message->get_message_type();
	std::vector<const char*> output_packet;
	if (message_type != mqttpacket::MQTT_CONTROL_PACKET_TYPE_PUBACK) return mqttpacket::PACKET_ERROR_PACKET_HEADER;
	puback_variable_to_vector(message, packet);
}

int convert_subscribe_into_packet(MQTTSubscribeMessage* message, std::vector<char>* packet)
{
	int message_type = message->get_message_type();
	std::vector<const char*> output_packet;
	if (message_type != mqttpacket::MQTT_CONTROL_PACKET_TYPE_SUBSCRIBE) return mqttpacket::PACKET_ERROR_PACKET_HEADER;
	subscribe_variable_to_vector(message, packet);
}

int convert_suback_into_packet(MQTTSubackMessage* message, std::vector<char>* packet)
{
	int message_type = message->get_message_type();
	std::vector<const char*> output_packet;
	if (message_type != mqttpacket::MQTT_CONTROL_PACKET_TYPE_SUBACK) return mqttpacket::PACKET_ERROR_PACKET_HEADER;
	suback_variable_to_vector(message, packet);
}

int convert_pubcomp_into_packet(MQTTPubcompMessage* message, std::vector<char>* packet)
{
	int message_type = message->get_message_type();
	std::vector<const char*> output_packet;
	if (message_type != mqttpacket::MQTT_CONTROL_PACKET_TYPE_PUBCOMP) return mqttpacket::PACKET_ERROR_PACKET_HEADER;
	pubcomp_variable_to_vector(message, packet);
}

void connect_variable_to_string(MQTTConnectMessage* message, std::vector<char>*container)
{
	ConnectVariableHeader temp_vHeader(0, 0, 0);
	ConnectFixedHeader temp_fheader = message->get_fHeader();
	ConnectPayload temp_payload = message->get_payload();
	temp_vHeader = message->get_vHeader();

	data_convert(container, temp_vHeader.get_protocol_name());
	data_convert(container, temp_vHeader.get_protocol_version());
	data_convert(container, temp_vHeader.get_connect_flags());
	data_convert(container, temp_vHeader.get_keep_alive());

	property_to_packet(&temp_vHeader, container);
	
	data_convert(container, temp_payload.get_id());
	data_convert(container, temp_payload.get_password());
	
	fixed_header_to_packet(&temp_fheader, container);
}

void connact_variable_to_vector(MQTTConnackMessage * message, std::vector<char>* container)
{
	ConnackVariableHeader temp_vHeader(0, 0);
	ConnackFixedHeader temp_fheader = message->get_fHeader();
	temp_vHeader = message->get_vHeader();
	
	//convert data from variable header into packet.
	data_convert(container, temp_vHeader.get_session_present() << 7);
	data_convert(container, temp_vHeader.get_connect_reason());

	property_to_packet(&temp_vHeader, container);
	
	fixed_header_to_packet(&temp_fheader, container);
}

void publish_variable_to_vector(MQTTPublishMessage* message, std::vector<char>* packet)
{
	PublishFixedHeader temp_fHeader = message->get_fHeader();
	PublishVariableHeader temp_vHeader = message->get_vHeader();
	UTF8String temp_payload = message->get_payload();
	int qos = temp_fHeader.get_flags() & 0x06;

	//convert data from variable header into packet.
	data_convert(packet, temp_vHeader.get_topic_name());
	data_convert(packet, temp_vHeader.get_packet_identifier());
	property_to_packet(&temp_vHeader, packet);

	//convert data from payload into packet
	data_convert(packet, temp_payload);

	//convert data from fixed header into packet
	fixed_header_to_packet(&temp_fHeader, packet);
}

void pubrec_variable_to_vector(MQTTPubrecMessage* message, std::vector<char>*  packet)
{
	PubrecFixedHeader temp_fHeader = message->get_fHeader();
	PubrecVariableHeader temp_vHeader = message->get_vHeader();
	
	// convert data from variable header into packet.
	data_convert(packet, temp_vHeader.get_packet_identifier());
	data_convert(packet, temp_vHeader.get_reason_code());
	property_to_packet(&temp_vHeader, packet);

	//convert data from fixed header into packet
	fixed_header_to_packet(&temp_fHeader, packet);
}

void pubrel_variable_to_vector(MQTTPubrelMessage* message, std::vector<char>* packet)
{
	PubrelFixedHeader temp_fHeader = message->get_fHeader();
	PubrelVariableHeader temp_vHeader = message->get_vHeader();

	// convert data from variable header into packet.
	data_convert(packet, temp_vHeader.get_packet_identifier());
	data_convert(packet, temp_vHeader.get_reason_code());
	property_to_packet(&temp_vHeader, packet);

	//convert data from fixed header into packet
	fixed_header_to_packet(&temp_fHeader, packet);
}

void puback_variable_to_vector(MQTTPubackMessage* message, std::vector<char>* packet)
{
	PubackFixedHeader temp_fHeader = message->get_fHeader();
	PubackVariableHeader temp_vHeader = message->get_vHeader();
	// convert data from variable header into packet.
	data_convert(packet, temp_vHeader.get_packet_identifier());
	data_convert(packet, temp_vHeader.get_reason_code());
	property_to_packet(&temp_vHeader, packet);

	//convert data from fixed header into packet
	fixed_header_to_packet(&temp_fHeader, packet);
}

void pubcomp_variable_to_vector(MQTTPubcompMessage* message, std::vector<char>* packet)
{
	PubcompFixedHeader temp_fHeader = message->get_fHeader();
	PubcompVariableHeader temp_vHeader = message->get_vHeader();

	// convert data from variable header into packet.
	data_convert(packet, temp_vHeader.get_packet_identifier());
	data_convert(packet, temp_vHeader.get_reason_code());
	property_to_packet(&temp_vHeader, packet);

	//convert data from fixed header into packet
	fixed_header_to_packet(&temp_fHeader, packet);
}

void subscribe_variable_to_vector(MQTTSubscribeMessage* message, std::vector<char>* packet)
{
	SubscribeFixedHeader temp_fHeader = message->get_fHeader();
	SubscribeVariableHeader temp_vHeader = message->get_vHeader();
	SubscribePayload temp_payload = message->get_payload();

	//convert data from variable header into packet.
	data_convert(packet, temp_vHeader.get_packet_identifier());
	property_to_packet(&temp_vHeader, packet);
	
	//convert data from payload into packet.
	for(Topic temp_t: temp_payload.get_list())
	{
		data_convert(packet, temp_t.get_filter());
		data_convert(packet,
			temp_t.get_retain_handling() << 4 |
			temp_t.get_retain() << 3 |
			temp_t.get_nolocal() << 2 |
			temp_t.get_maximum_qos()
		);
	}

	//convert data from fixed header into packet.
	fixed_header_to_packet(&temp_fHeader, packet);
}

void suback_variable_to_vector(MQTTSubackMessage* message, std::vector<char>* packet)
{
	SubackFixedHeader temp_fHeader = message->get_fHeader();
	SubackVariableHeader temp_vHeader = message->get_vHeader();
	SubackPayload temp_payload = message->get_payload();

	//convert data from variable header into packet.
	data_convert(packet, temp_vHeader.get_packet_identifier());
	property_to_packet(&temp_vHeader, packet);

	//convert data from payload into packet.
	for (int temp_result : temp_payload.get_result_list())
	{
		data_convert(packet, temp_result);
	}

	//convert data from fixed header into packet.
	fixed_header_to_packet(&temp_fHeader, packet);
}

int get_first_byte_in_fheader(int packet_type, int flags)
{
	return (packet_type << 4) | (flags);
}

void property_to_packet(VariableHeader * vHeader, std::vector<char>* container)
{
	std::vector<char> property_vector;
	for (std::shared_ptr<Property> temp_p : vHeader->get_property_list()) temp_p->get_data(&property_vector);
	data_convert_front(&property_vector, property_vector.size());
	container->insert(std::end(*container), std::begin(property_vector), std::end(property_vector));
}

void fixed_header_to_packet(FixedHeader * fHeader, std::vector<char>* container)
{
	
	VariableByteInteger remaining_length(container->size());
	std::vector<char> remaining = remaining_length.get_variable_value();
	container->insert(container->begin(), remaining.begin(), remaining.end());
	
	//int remaining_length = container->size();
	//std::vector<char> remaining;
	//data_convert(&remaining, remaining_length);
	//container->insert(container->begin(), remaining.begin(), remaining.end());
	const int first_packet_data = get_first_byte_in_fheader(fHeader->get_control_packet_type(), fHeader->get_flags());
	data_convert_front(container, first_packet_data);
}