#pragma once

#ifndef MQTTPACKET_EXPORTS
#define MQTT_API __declspec(dllexport)
#else
#define MQTT_API __declspec(dllimport)
#define MQTT_H
#endif

#include "MQTTConnectMessage.h"
#include "MQTTConnackMessage.h"
#include "MQTTMessage.h"
#include "MQTTPublishMessage.h"
#include "MQTTPubackMessage.h"
#include "MQTTPubRelMessage.h"
#include "MQTTPubRecMessage.h"
#include "MQTTSubscribeMessage.h"
#include "MQTTSubackMessage.h"
#include "SubscribePayload.h"
#include "MQTTPubcompMessage.h"

extern "C" MQTT_API void generate_default_connect(MQTTConnectMessage & message, std::string id, std::string password);
extern "C" MQTT_API void generate_connect(MQTTConnectMessage & message, int version, int flags, int keep_alive, int session_expiry_, std::string id, std::string password);

extern "C" MQTT_API void generate_default_connack(MQTTConnackMessage & message, std::string client_identifier, std::string reference, std::string alt_reference);
extern "C" MQTT_API void generate_connack(MQTTConnackMessage & message, int session_present, bool subscription_id_availability, std::string client_identifier, std::string reference, std::string alt_reference);

extern "C" MQTT_API void generate_default_publish(MQTTPublishMessage & message, int packet_identifier, std::string topic_name, std::string data, int qos);
extern "C" MQTT_API void generate_publish(MQTTPublishMessage & message, int packet_identifier, std::string topic_name, std::string data, int dup, int qos, int retain);

extern "C" MQTT_API void generate_default_pubrec(MQTTPubrecMessage & message, int identifier);
extern "C" MQTT_API void generate_pubrec(MQTTPubrecMessage & message, int identifier, int reason_code);

extern "C" MQTT_API void generate_default_pubrel(MQTTPubrelMessage & message, int identifier);
extern "C" MQTT_API void generate_pubrel(MQTTPubrelMessage & message, int identifier, int reason_code);

extern "C" MQTT_API void generate_default_puback(MQTTPubackMessage & message, int identifier);
extern "C" MQTT_API void generate_puback(MQTTPubackMessage & message, int identifier, int reason_code);

extern "C" MQTT_API void generate_default_pubcomp(MQTTPubcompMessage & message, int identifier);
extern "C" MQTT_API void generate_pubcomp(MQTTPubcompMessage & message, int identifier, int reason_code);

extern "C" MQTT_API void generate_default_subscribe(MQTTSubscribeMessage & message, int identifier, std::string topic_filter, int m_qos);
//extern "C" MQTT_API void generate_subscribe(MQTTSubscribeMessage * message, int identifier, std::vector<Topic> topic_filter_list);

extern "C" MQTT_API void generate_default_suback(MQTTSubackMessage & message, int identifier, int result);
extern "C" MQTT_API void generate_suback(MQTTSubackMessage & message, int identifier, const int n_item, const int result_list[]);
