#include "PacketInterpreter.h"
#include "VariableByteInteger.h"
#include "AssignedClientIdentifier.h"
#include "MQTTPubcompMessage.h"
#include "PayloadFormatIndicator.h"
#include "ServerReference.h"
#include "UserProperty.h"


int interpret_connect_packet(MQTTConnectMessage * message, const char * packet)
{
	ConnectFixedHeader temp_fheader = message->get_fHeader();
	ConnectPayload temp_payload = message->get_payload();
		int first_byte_fheader = packet[0];
		packet++;
		int message_type = (first_byte_fheader >> 4) & 0x0f;
		int flags = first_byte_fheader % 16;

		if (message_type != temp_fheader.get_control_packet_type()) return mqttpacket::PACKET_ERROR_PACKET_HEADER;

		temp_fheader.set_flags(flags);
		VariableByteInteger packet_length;
		UTF8String protocol_name;
		int protocol_version;
		int connect_flags;
		TwoByteInteger keep_alive;
		int n_property = 0;
		UTF8String id;
		UTF8String password;

		packet += reverse_data_convert(&packet_length, packet);
		packet += reverse_data_convert(&protocol_name, packet);
		packet += reverse_data_convert(&protocol_version, packet);
		packet += reverse_data_convert(&connect_flags, packet);
		packet += reverse_data_convert(&keep_alive, packet);

		ConnectVariableHeader temp_vHeader(protocol_version, flags, keep_alive.get_data());
		ConnectFixedHeader temp_fHeader(connect_flags);

		packet += reverse_data_convert(&n_property, packet);
		for (int i = n_property; i > 0; )
		{
			int temp_property_id;
			int size;
			packet += reverse_data_convert(&temp_property_id, packet);
			i--;
			switch (temp_property_id)
			{
			case mqttpacket::MQTT_PROPERTY_SESSION_EXPIRY_INTERVAL:
				FourByteInteger value;
				size = reverse_data_convert(&value, packet);
				packet += size;
				std::shared_ptr<SessionExpiryInterval> session(new SessionExpiryInterval(value.get_data()));
				temp_vHeader.add_property(session);
			}
			i -= size;
		}

		packet += reverse_data_convert(&id, packet);
		packet += reverse_data_convert(&password, packet);


		ConnectPayload payload(id.get_data(), password.get_data());

		message->set_fHeader(temp_fHeader);
		message->set_vHeader(temp_vHeader);
		message->set_payload(payload);

		return 0;
}

int interpret_connact_packet(MQTTConnackMessage * message, const char* packet)
{
	ConnackFixedHeader temp_fheader = message->get_fHeader();

	int first_byte_fheader = packet[0];
	packet++;
	int message_type = (first_byte_fheader >> 4 ) & 0x0f;
	int flags = first_byte_fheader % 16;

	if (message_type != temp_fheader.get_control_packet_type()) return mqttpacket::PACKET_ERROR_PACKET_HEADER;

	temp_fheader.set_flags(flags);
	VariableByteInteger packet_length;
	int session_present;
	int reason_code;
	int n_property = 0;
	FourByteInteger session_exp;
	UTF8String identifier;
	UTF8String alt_reference;
	UTF8String server_reference;
	std::shared_ptr<SessionExpiryInterval> session(new SessionExpiryInterval());
	std::shared_ptr<AssignedClientIdentifier> client_identifier(new AssignedClientIdentifier());
	std::shared_ptr<UserProperty> alt_server(new UserProperty());
	std::shared_ptr<ServerReference> server_address(new ServerReference());
	
	packet += reverse_data_convert(&packet_length, packet);
	packet += reverse_data_convert(&session_present, packet);
	packet += reverse_data_convert(&reason_code, packet);
	
	ConnackVariableHeader temp_vHeader(session_present, reason_code);
	ConnackFixedHeader temp_fHeader;
	
	packet += reverse_data_convert(&n_property, packet);
	for (int i = n_property; i > 0; )
	{
		int temp_property_id;
		int size=0;
		packet += reverse_data_convert(&temp_property_id, packet);
		i--;
		switch (temp_property_id)
		{
		case mqttpacket::MQTT_PROPERTY_SESSION_EXPIRY_INTERVAL:
			size = reverse_data_convert(&session_exp, packet);
			packet += size;
			session->set_data(session_exp.get_data());
			temp_vHeader.add_property(session);
			break;
		case mqttpacket::MQTT_PROPERTY_ASSIGNED_CLIENT_IDENTIFIER:
			size = reverse_data_convert(&identifier, packet);
			packet += size;
			client_identifier->set_identifier(identifier.get_data());
			temp_vHeader.add_property(client_identifier);
			break;
		case mqttpacket::MQTT_PROPERTY_USER_PROPERTY:
			size = reverse_data_convert(&alt_reference, packet);
			packet += size;
			alt_server->set_reference(alt_reference.get_data());
			temp_vHeader.add_property(alt_server);
			break;
		case mqttpacket::MQTT_PROPERTY_SERVER_REFERENCE:
			size = reverse_data_convert(&server_reference, packet);
			packet += size;
			server_address->set_reference(server_reference.get_data());
			temp_vHeader.add_property(server_address);
			break;

		default:break;
		}
		i -= size;
	}

	message->set_fHeader(temp_fHeader);
	message->set_vHeader(temp_vHeader);

	return 0;
}

int interpret_publish_packet(MQTTPublishMessage * message, const char* packet)
{
	PublishFixedHeader temp_fheader = message->get_fHeader();
	UTF8String temp_payload = message->get_payload();

	int first_byte_fheader = packet[0];
	packet++;
	int message_type = (first_byte_fheader >> 4 ) & 0x0f;
	int flags = first_byte_fheader % 16;
	int dup = flags & 0x08;
	int qos = flags & 0x03;

	if (message_type != temp_fheader.get_control_packet_type()) return mqttpacket::PACKET_ERROR_PACKET_HEADER;

	temp_fheader.set_flags(flags);
	VariableByteInteger packet_length;
	//int packet_length=0;
	UTF8String topic_name;
	TwoByteInteger packet_identifier;

	UTF8String payload;
	int n_property = 0;
	packet += reverse_data_convert(&packet_length, packet);
	//std::cout << "packet length = " << packet_length << std::endl;
	packet += reverse_data_convert(&topic_name, packet);
	packet += reverse_data_convert(&packet_identifier, packet);

	PublishVariableHeader temp_vHeader(topic_name.get_data(), packet_identifier.get_data());
	PublishFixedHeader temp_fHeader(flags);
	std::shared_ptr<PayloadFormatIndicator> format_ind(new PayloadFormatIndicator(0));
	
	packet += reverse_data_convert(&n_property, packet);
	for (int i = n_property; i > 0; )
	{
		int temp_property_id;
		int size=0;
		packet += reverse_data_convert(&temp_property_id, packet);
		i--;
		switch (temp_property_id)
		{
		case mqttpacket::MQTT_PROPERTY_PAYLOAD_FORMAT_INDICATOR:
			int value;
			size = reverse_data_convert(&value, packet);
			packet += size;
			format_ind->set_format_type(value);
			temp_vHeader.add_property(format_ind);
		}
		i -= size;
	}

	packet += reverse_data_convert(&payload, packet);

	UTF8String publish_payload(payload.get_data());
	//std::cout << "publish_payload:" << publish_payload.get_data() << std::endl;

	message->set_fHeader(temp_fHeader);
	message->set_vHeader(temp_vHeader);
	message->set_payload(publish_payload);

	return 0;
}

int interpret_pubrec_packet(MQTTPubrecMessage * message, const char* packet)
{
	PubrecFixedHeader temp_fheader = message->get_fHeader();

	int first_byte_fheader = packet[0];
	packet++;
	int message_type = (first_byte_fheader >> 4 ) & 0x0f;
	int flags = first_byte_fheader % 16;

	if (message_type != temp_fheader.get_control_packet_type()) return mqttpacket::PACKET_ERROR_PACKET_HEADER;

	temp_fheader.set_flags(flags);
	VariableByteInteger packet_length;
	TwoByteInteger packet_identifier;
	int reason_code;
	int n_property = 0;
	packet += reverse_data_convert(&packet_length, packet);
	packet += reverse_data_convert(&packet_identifier, packet);
	packet += reverse_data_convert(&reason_code, packet);

	PubrecVariableHeader temp_vHeader(packet_identifier.get_data(), reason_code);

	message->set_vHeader(temp_vHeader);
	return 0;
}

int interpret_pubrel_packet(MQTTPubrelMessage * message, const char* packet)
{
	PubrelFixedHeader temp_fheader = message->get_fHeader();

	int first_byte_fheader = packet[0];
	packet++;
	int message_type = (first_byte_fheader >> 4 ) & 0x0f;
	int flags = first_byte_fheader % 16;

	if (message_type != temp_fheader.get_control_packet_type()) return mqttpacket::PACKET_ERROR_PACKET_HEADER;

	temp_fheader.set_flags(flags);
	VariableByteInteger packet_length;
	TwoByteInteger packet_identifier;
	int reason_code;
	int n_property = 0;
	packet += reverse_data_convert(&packet_length, packet);
	packet += reverse_data_convert(&packet_identifier, packet);
	packet += reverse_data_convert(&reason_code, packet);

	PubrelVariableHeader temp_vHeader(packet_identifier.get_data(), reason_code);

	message->set_vHeader(temp_vHeader);
	return 0;
}

int interpret_puback_packet(MQTTPubackMessage * message, const char* packet)
{
	PubackFixedHeader temp_fheader = message->get_fHeader();

	int first_byte_fheader = packet[0];
	packet++;
	int message_type = (first_byte_fheader >> 4 ) & 0x0f;
	int flags = first_byte_fheader % 16;

	if (message_type != temp_fheader.get_control_packet_type()) return mqttpacket::PACKET_ERROR_PACKET_HEADER;

	temp_fheader.set_flags(flags);
	VariableByteInteger packet_length;
	TwoByteInteger packet_identifier;
	int reason_code;
	int n_property = 0;
	packet += reverse_data_convert(&packet_length, packet);
	packet += reverse_data_convert(&packet_identifier, packet);
	packet += reverse_data_convert(&reason_code, packet);

	PubackVariableHeader temp_vHeader(packet_identifier.get_data(), reason_code);

	message->set_vHeader(temp_vHeader);
	return 0;
}

int interpret_pubcomp_packet(MQTTPubcompMessage * message, const char* packet)
{
	PubcompFixedHeader temp_fheader = message->get_fHeader();

	int first_byte_fheader = packet[0];
	packet++;
	int message_type = (first_byte_fheader >> 4 ) & 0x0f;
	int flags = first_byte_fheader % 16;

	if (message_type != temp_fheader.get_control_packet_type()) return mqttpacket::PACKET_ERROR_PACKET_HEADER;

	temp_fheader.set_flags(flags);
	VariableByteInteger packet_length;
	TwoByteInteger packet_identifier;
	int reason_code;
	int n_property = 0;
	packet += reverse_data_convert(&packet_length, packet);
	packet += reverse_data_convert(&packet_identifier, packet);
	packet += reverse_data_convert(&reason_code, packet);

	PubcompVariableHeader temp_vHeader(packet_identifier.get_data(), reason_code);

	message->set_vHeader(temp_vHeader);
	return 0;
}

int interpret_subscribe_packet(MQTTSubscribeMessage * message, const char* packet)
{
	SubscribeFixedHeader temp_fHeader = message->get_fHeader();
	int first_byte_fheader = packet[0];
	packet++;
	int message_type = (first_byte_fheader >> 4) & 0x0f;
	int flags = first_byte_fheader % 16;

	if (message_type != temp_fHeader.get_control_packet_type()) return mqttpacket::PACKET_ERROR_PACKET_HEADER;

	temp_fHeader.set_flags(flags);
	VariableByteInteger packet_length;
	TwoByteInteger packet_identifier;
	
	int n_property = 0;
	packet += reverse_data_convert(&packet_length, packet);
	packet += reverse_data_convert(&packet_identifier, packet);

	SubscribeVariableHeader temp_vHeader(packet_identifier.get_data());
	SubscribePayload temp_payload;
	packet += reverse_data_convert(&n_property, packet);

	for (int i = n_property; i > 0; )
	{
		int temp_property_id;
		int size = 0;
		packet += reverse_data_convert(&temp_property_id, packet);
		i--;
		switch (temp_property_id)
		{
		case mqttpacket::MQTT_PROPERTY_USER_PROPERTY:
			break;
		}
		i -= size;
	}
	//No property is used in the current version of the libray.

	for(int i=packet_length.get_value()-3/*the length of variable header*/; i> 0; )
	{
		UTF8String temp_filter;
		int subscription_option;
		int size = 0;
		size += reverse_data_convert(&temp_filter, packet);
		packet += size;
		i -= size;
		size += reverse_data_convert(&subscription_option, packet);
		packet += size;
		i -= size;
		temp_payload.add_topic_filter(
			temp_filter.get_data(),						//topic filter
			subscription_option && 0x3,					//maximum qos
			(subscription_option && 0x04) >> 2,			//no local
			(subscription_option && 0x08) >> 3,			//retain
			(subscription_option && 0x30) >> 4			//retain_handling
		);
	}
	
	message->set_vHeader(temp_vHeader);
	message->set_payload(temp_payload);
	return 0;
}

int interpret_suback_packet(MQTTSubackMessage* message, const char* packet) 
{
	SubackFixedHeader temp_fHeader = message->get_fHeader();
	int first_byte_fheader = packet[0];
	packet++;
	int message_type = (first_byte_fheader >> 4) & 0x0f;
	int flags = first_byte_fheader % 16;

	if (message_type != temp_fHeader.get_control_packet_type()) return mqttpacket::PACKET_ERROR_PACKET_HEADER;

	temp_fHeader.set_flags(flags);
	VariableByteInteger packet_length;
	TwoByteInteger packet_identifier;

	int n_property = 0;
	packet += reverse_data_convert(&packet_length, packet);
	packet += reverse_data_convert(&packet_identifier, packet);

	SubackVariableHeader temp_vHeader(packet_identifier.get_data());
	SubackPayload temp_payload;
	packet += reverse_data_convert(&n_property, packet);

	for (int i = n_property; i > 0; )
	{
		int temp_property_id;
		int size = 0;
		packet += reverse_data_convert(&temp_property_id, packet);
		i--;
		switch (temp_property_id)
		{
		case mqttpacket::MQTT_PROPERTY_USER_PROPERTY:
			break;
		}
		i -= size;
	}
	//No property is used in the current version of the libray.

	for (int i = packet_length.get_value() - 3/*the length of variable header*/; i > 0;)
	{
		int temp_result;
		int size = 0;
		size = reverse_data_convert(&temp_result, packet);
		packet += size;
		i -= size;
		temp_payload.add_result(temp_result);
	}
	message->set_fHeader(temp_fHeader);
	message->set_vHeader(temp_vHeader);
	message->set_payload(temp_payload);
	return 0;
}
