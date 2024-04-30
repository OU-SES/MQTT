#include "pch.h"
#include "MQTTMessageFactory.h"

#include "AssignedClientIdentifier.h"
#include "MQTTControlPacketList.h"
#include "SessionExpiryInterval.h"
#include "ConnectVariableHeader.h"
#include "MQTTConnectMessage.h"
#include "MQTTPubcompMessage.h"
#include "PayloadFormatIndicator.h"
#include "PubcompVariableHeader.h"
#include "ServerReference.h"
#include "SubscribeVariableHeader.h"
#include "SubscriptionIdentifiersAvailable.h"
#include "UserProperty.h"

void generate_default_connect(MQTTConnectMessage & message, std::string id, std::string password)
{
	ConnectVariableHeader connect_variable_header(mqttpacket::MQTT_CURRENT_VERSION, mqttpacket::MQTT_DEFAULT_CONNECT_OPTION, mqttpacket::MQTT_DEFAULT_KEEP_ALIVE);
	//std::shared_ptr<SessionExpiryInterval> session_expiry(new SessionExpiryInterval(0));
	SessionExpiryInterval session_expiry(0);
	std::shared_ptr<SessionExpiryInterval> session_expiry_ = std::make_shared<SessionExpiryInterval>(session_expiry);
	ConnectPayload payload(id, password);
	connect_variable_header.add_property(session_expiry_);
	message.set_vHeader(connect_variable_header);
	message.set_payload(payload);
}

void generate_connect(MQTTConnectMessage & message, int version, int flags, int keep_alive, int session_expiry_, std::string id, std::string password)
{
	ConnectVariableHeader connect_variable_header(version, flags, keep_alive);
	std::shared_ptr<SessionExpiryInterval> session_expiry(new SessionExpiryInterval(session_expiry_));
	ConnectPayload payload(id, password);
	connect_variable_header.add_property(session_expiry);
	message.set_vHeader(connect_variable_header);
	message.set_payload(payload);
}

void generate_default_connack(MQTTConnackMessage & message, std::string client_identifier, std::string reference, std::string alt_reference)
{
	ConnackVariableHeader connack_variable_header(0, mqttpacket::REASON_CODE_SUCCESS);
	std::shared_ptr<ServerReference> sReference(new ServerReference(reference));
	std::shared_ptr<AssignedClientIdentifier> cIdentifier(new AssignedClientIdentifier(client_identifier));
	std::shared_ptr<UserProperty> aReference(new UserProperty(alt_reference));
	connack_variable_header.add_property(sReference);
	connack_variable_header.add_property(cIdentifier);
	connack_variable_header.add_property(aReference);
	message.set_vHeader(connack_variable_header);
}

void generate_connack(MQTTConnackMessage & message, int session_present, bool subscription_id_availability, std::string client_identifier, std::string reference, std::string alt_reference)
{
	ConnackVariableHeader connack_variable_header(session_present, mqttpacket::REASON_CODE_SUCCESS);
	std::shared_ptr<SubscriptionIdentifierAvailable> s_identifier_av(new SubscriptionIdentifierAvailable(subscription_id_availability));
	std::shared_ptr<ServerReference> sReference(new ServerReference(reference));
	std::shared_ptr<AssignedClientIdentifier> cIdentifier(new AssignedClientIdentifier(client_identifier));
	std::shared_ptr<UserProperty> aReference(new UserProperty(alt_reference));
	connack_variable_header.add_property(s_identifier_av);
	connack_variable_header.add_property(sReference);
	connack_variable_header.add_property(cIdentifier);
	connack_variable_header.add_property(aReference);
	message.set_vHeader(connack_variable_header);
}

void generate_default_publish(MQTTPublishMessage & message, int packet_identifier, std::string topic_name, std::string data, int qos)
{
	PublishVariableHeader publish_variable_header(topic_name, packet_identifier);
	PublishFixedHeader publish_fix_header(qos);
	std::shared_ptr<PayloadFormatIndicator> format(new PayloadFormatIndicator(mqttpacket::MQTT_FORMAT_UTF8));
	UTF8String payload(data);
	publish_variable_header.add_property(format);
	message.set_vHeader(publish_variable_header);
	message.set_fHeader(publish_fix_header);
	message.set_payload(payload);
}

void generate_publish(MQTTPublishMessage & message, int packet_identifier, std::string topic_name, std::string data, int dup, int qos, int retain)
{
	PublishVariableHeader publish_variable_header(topic_name, packet_identifier);
	std::shared_ptr<PayloadFormatIndicator> format(new PayloadFormatIndicator(mqttpacket::MQTT_FORMAT_UTF8));
	UTF8String payload(data);
	publish_variable_header.add_property(format);
	message.set_vHeader(publish_variable_header);
	message.set_payload(payload);
}

void generate_default_puback(MQTTPubackMessage & message, int identifier)
{
	PubackVariableHeader puback_variable_header(identifier, mqttpacket::REASON_CODE_SUCCESS);
	message.set_vHeader(puback_variable_header);
}

void generate_puback(MQTTPubackMessage & message, int identifier, int reason_code)
{
	PubackVariableHeader puback_variable_header(identifier, reason_code);
	message.set_vHeader(puback_variable_header);
}

void generate_default_pubrec(MQTTPubrecMessage & message, int identifier)
{
	PubrecVariableHeader pubrec_variable_header(identifier, mqttpacket::REASON_CODE_SUCCESS);
	message.set_vHeader(pubrec_variable_header);
}

void generate_pubrec(MQTTPubrecMessage & message, int identifier, int reason_code)
{
	PubrecVariableHeader pubrec_variable_header(identifier, reason_code);
	message.set_vHeader(pubrec_variable_header);
}

void generate_default_pubrel(MQTTPubrelMessage & message, int identifier)
{
	PubrelVariableHeader pubrel_variable_header(identifier, mqttpacket::REASON_CODE_SUCCESS);
	message.set_vHeader(pubrel_variable_header);
}

void generate_pubrel(MQTTPubrelMessage & message, int identifier, int reason_code)
{
	PubrelVariableHeader pubrel_variable_header(identifier, reason_code);
	message.set_vHeader(pubrel_variable_header);
}

void generate_default_pubcomp(MQTTPubcompMessage &message, int identifier)
{
	PubcompVariableHeader pubcomp_variable_header(identifier, mqttpacket::REASON_CODE_SUCCESS);
	message.set_vHeader(pubcomp_variable_header);
}

void generate_pubcomp(MQTTPubcompMessage & message, int identifier, int reason_code)
{
	PubcompVariableHeader pubcomp_variable_header(identifier, reason_code);
	message.set_vHeader(pubcomp_variable_header);
}

void generate_default_subscribe(MQTTSubscribeMessage & message, int identifier, std::string topic_filter, int m_qos)
{
	SubscribeVariableHeader subscribe_variable_header(identifier);
	SubscribePayload subscribe_payload;
	subscribe_payload.add_topic_filter(topic_filter, m_qos, 0, 0, 0);
	message.set_vHeader(subscribe_variable_header);
	message.set_payload(subscribe_payload);
}

void generate_subscribe(MQTTSubscribeMessage & message, int identifier, std::vector<Topic> topic_filter_list);

void generate_default_suback(MQTTSubackMessage & message, int identifier, int result)
{
	SubackVariableHeader suback_variable_header(identifier);
	SubackPayload subac_payload;
	subac_payload.add_result(result);
	message.set_vHeader(suback_variable_header);
	message.set_payload(subac_payload);
}

void generate_suback(MQTTSubackMessage & message, int identifier, const int n_item, const int result_list[]) 
{
	SubackVariableHeader suback_variable_header(identifier);
	SubackPayload subac_payload;
	for (int i = 0; i < n_item; i++) { subac_payload.add_result(result_list[i]); }
	message.set_vHeader(suback_variable_header);
	message.set_payload(subac_payload);
}
