#pragma once
#include <vector>
#include "UTF8String.h"
#include "TwoByteInteger.h"
#include "VariableByteInteger.h"
#include "FourByteInteger.h"

int data_convert(std::vector<char>* packet, UTF8String data);
int data_convert(std::vector<char>* packet, TwoByteInteger data);
int data_convert(std::vector<char>* packet, FourByteInteger data);
int data_convert(std::vector<char> *packet, int data);
int data_convert_front(std::vector<char> *packet, int data);

int reverse_data_convert(int * dst, const char * src);
int reverse_data_convert(UTF8String *dst, const char* src);
int reverse_data_convert(TwoByteInteger* dst, const char* src);
int reverse_data_convert(VariableByteInteger* dst, const char* src);
int reverse_data_convert(FourByteInteger* dst, const char* src);