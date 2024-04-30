#pragma once
#include <vector>

class SubackPayload
{
public:
	SubackPayload(){}
	void add_result(int result) { result_subscription.push_back(result); }
	std::vector<int> get_result_list() { return result_subscription; }
private:
	std::vector<int> result_subscription;
};
