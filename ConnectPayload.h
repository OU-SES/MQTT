#pragma once
#include <string>

#include "UTF8String.h"

class ConnectPayload
{
private:
	UTF8String id;
	UTF8String password;
public:
	ConnectPayload( std::string id_, std::string password_)
	{
		id = UTF8String(id_);
		password = UTF8String(password_);
	}
	UTF8String get_id() { return id; }
	UTF8String get_password() { return password; }
	void set_id(std::string id_) { id.set_data(id_); }
	void set_password(std::string password_) { password.set_data(password_); }
};
