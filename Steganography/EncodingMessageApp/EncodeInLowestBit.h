
#pragma once

#include <pch.h>
#include <robuffer.h>
#include <wrl.h>

using namespace std;

class EncodeInLowestBit
{
public:
	byte* DecodeText(byte* image, shared_ptr<unsigned int> decodedLength);
	byte* EncodeText(byte* image, unsigned int imageLength, byte* added, unsigned int addedLength, int offset);
	byte* BitConversion(int i);
	char* ConvertUTFToChar(const wchar_t* text, unsigned int length);
};