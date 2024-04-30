#pragma once
namespace mqttpacket {
	//Protocol Version
	const int MQTT_CURRENT_VERSION = 5;
	
	//List of MQTT Control Packet Type
	const int MQTT_CONTROL_PACKET_TYPE_CONNECT = 0x01;
	const int MQTT_CONTROL_PACKET_TYPE_CONNACT = 0x02;
	const int MQTT_CONTROL_PACKET_TYPE_PUBLISH = 0x03;
	const int MQTT_CONTROL_PACKET_TYPE_PUBACK = 0x04;
	const int MQTT_CONTROL_PACKET_TYPE_PUBREC = 0x05;
	const int MQTT_CONTROL_PACKET_TYPE_PUBREL = 0x06;
	const int MQTT_CONTROL_PACKET_TYPE_PUBCOMP = 0x07;
	const int MQTT_CONTROL_PACKET_TYPE_SUBSCRIBE = 0x08;
	const int MQTT_CONTROL_PACKET_TYPE_SUBACK = 0x09;
	//0x10 = unsubscribe
	//0x11 = unsuback
	//....

	//List of flags
	//CONNECT, CONNACK, PUBACK, PUBREC, PUBCOMP, SUBACK, UNSUBACK, PINGREQ, PINGRESP, DISCONNECT, AUTH
	const int DEFAULT_FLAGS = 0x00;

	//PUBREL, SUBSCRIBE, UNSUBSCRIBE
	const int TWO_BITS_FLAGS = 0x02;
	//flags for publish can not be const

	//List of MQTT Properties
	const int MQTT_PAYLOAD_FORMAT_INDICATOR = 0x01;
	const int MQTT_SESSION_EXPIRY_INTERVAL = 0x11;

	//Reason Code
	const int REASON_CODE_SUCCESS = 0x00;
	const int NORMAL_DISCONNECTION = 0x01;
	const int GRANTED_QOS_0 = 0x00;
	const int GRANTED_QOS_1 = 0x01;
	const int GRANTED_QOS_2 = 0x02;
	const int DISCONNECT_WITH_WILL_MESSAGE = 0x04;
	const int PROTOCOL_ERROR = 0x82;
	const int IMPLEMENTATION_SPECIFIC_ERROR = 0x83;
	const int UNSUPPORTED_PROTOCOL_VERSION = 0x84;
	const int CLIENT_IDENTIFIER_NOT_VALID = 0x85;
	const int BAD_USER_NAME_OR_PASSWORD = 0x86;
	const int USE_ANOTHER_SERVER = 0x9C;

	//Connect Flags
	const int MQTT_DEFAULT_CONNECT_OPTION = 196;
		//User Name Flag = true
		//Password Flag = true
		//Will Retain = false;
		//Will QoS = false;
		//Will Flag = false;
		//Clean Start = true;

	const int MQTT_DEFAULT_KEEP_ALIVE = 10;	// 10 second

	//Properties
	const int MQTT_PROPERTY_SESSION_EXPIRY_INTERVAL = 0x11;
	const int MQTT_PROPERTY_ASSIGNED_CLIENT_IDENTIFIER = 0x12;
	const int MQTT_PROPERTY_SUBSCRIPTION_IDENTIFIER_AVAILABLE = 0x29;
	const int MQTT_PROPERTY_SERVER_REFERENCE = 0x1C;
	const int MQTT_PROPERTY_PAYLOAD_FORMAT_INDICATOR = 0x01;
	const int MQTT_PROPERTY_USER_PROPERTY = 0x26;

	//errorList
	const int COMPLETE_WITH_NO_ERROR = 0x00;
	const int PACKET_ERROR_PACKET_HEADER = 0x01;
	const int PACKET_IDENTIFIER_NOT_FOUND = 0x92;

	//const data
	const int MQTT_FORMAT_UTF8 = 0x01;
	const int MQTT_FORMAT_UNSPECIFIED = 0x00;
}