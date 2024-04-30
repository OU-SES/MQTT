#pragma once

#ifndef MQTTPACKET_EXPORTS
#define MQTT_API __declspec(dllexport)
#else
#define MQTT_API __declspec(dllimport)
#define MQTT_H
#endif

#include "MQTTConnectMessage.h"
#include "MQTTConnackMessage.h"
#include "MQTTPublishMessage.h"
#include "MQTTPubackMessage.h"
#include "MQTTPubRelMessage.h"
#include "MQTTPubRecMessage.h"
#include "MQTTPubcompMessage.h"
#include "MQTTSubscribeMessage.h"
#include "MQTTSubackMessage.h"

extern "C" MQTT_API	int interpret_connect_packet(MQTTConnectMessage* message, const char* packet);
extern "C" MQTT_API int interpret_connact_packet(MQTTConnackMessage* message, const char* packet);
extern "C" MQTT_API	int interpret_publish_packet(MQTTPublishMessage* message, const char* packet);
extern "C" MQTT_API int interpret_pubrec_packet(MQTTPubrecMessage* message, const char* packet);
extern "C" MQTT_API int interpret_pubrel_packet(MQTTPubrelMessage* message, const char* packet);
extern "C" MQTT_API int interpret_puback_packet(MQTTPubackMessage* message, const char* packet);
extern "C" MQTT_API int interpret_pubcomp_packet(MQTTPubcompMessage * message, const char* packet);
extern "C" MQTT_API int interpret_subscribe_packet(MQTTSubscribeMessage* message, const char* packet);
extern "C" MQTT_API int interpret_suback_packet(MQTTSubackMessage* message, const char* packet);

