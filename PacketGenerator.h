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
#include "MQTTPubcompMessage.h"
#include "MQTTPubRelMessage.h"
#include "MQTTPubRecMessage.h"
#include "MQTTSubscribeMessage.h"
#include "MQTTSubackMessage.h"

extern "C" MQTT_API int convert_connect_into_packet(MQTTConnectMessage * message, std::vector<char> *packet);
extern "C" MQTT_API int convert_connact_into_packet(MQTTConnackMessage * message, std::vector<char> *packet);
extern "C" MQTT_API int convert_publish_into_packet(MQTTPublishMessage * message, std::vector<char> *packet);
extern "C" MQTT_API int convert_pubrec_into_packet(MQTTPubrecMessage * message, std::vector<char> *packet);
extern "C" MQTT_API int convert_pubrel_into_packet(MQTTPubrelMessage * message, std::vector<char> *packet);
extern "C" MQTT_API int convert_puback_into_packet(MQTTPubackMessage * message, std::vector<char> *packet);
extern "C" MQTT_API int convert_pubcomp_into_packet(MQTTPubcompMessage * message, std::vector<char> * packet);
extern "C" MQTT_API int convert_subscribe_into_packet(MQTTSubscribeMessage * message, std::vector<char> *packet);
extern "C" MQTT_API int convert_suback_into_packet(MQTTSubackMessage * message, std::vector<char> *packet);

void connect_variable_to_string(MQTTConnectMessage* message, std::vector<char> *output_packet);
void connact_variable_to_vector(MQTTConnackMessage* message, std::vector<char> *output_packet);
void publish_variable_to_vector(MQTTPublishMessage* message, std::vector<char> *output_packet);
void pubrec_variable_to_vector(MQTTPubrecMessage* message, std::vector<char> *output_packet);
void pubrel_variable_to_vector(MQTTPubrelMessage* message, std::vector<char> *output_packet);
void puback_variable_to_vector(MQTTPubackMessage* message, std::vector<char> *output_packet);
void pubcomp_variable_to_vector(MQTTPubcompMessage* message, std::vector<char>* output_packet);
void subscribe_variable_to_vector(MQTTSubscribeMessage* message, std::vector<char> *output_packet);
void suback_variable_to_vector(MQTTSubackMessage* message, std::vector<char> *output_packet);

int get_first_byte_in_fheader(int packet_type, int flags);
void property_to_packet(VariableHeader* fHeader, std::vector<char>* container);
void fixed_header_to_packet(FixedHeader* fHeader, std::vector<char>* container);