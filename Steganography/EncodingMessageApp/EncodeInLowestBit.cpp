#include "pch.h"
#include "EncodeInLowestBit.h"

using namespace Platform;
using namespace std;

byte* EncodeInLowestBit::BitConversion(int i)
{
	byte byte3 = (byte) ((i & 0xFF000000) >> 24);
	byte byte2 = (byte) ((i & 0x00FF0000) >> 16);
	byte byte1 = (byte) ((i & 0x0000FF00) >> 8);
	byte byte0 = (byte) ((i & 0x000000FF));

	return(new byte[]
	{
		byte3, byte2, byte1, byte0
	});
}

char* EncodeInLowestBit::ConvertUTFToChar(const wchar_t* text, unsigned int length)
{
	char* cString = new char[length + 1];
	cString[length] = 0;
	for (int y = 0; y < length; y++)
	{
		char c = (char) text[y];
		cString[y] = c;
	}

	return cString;
}

byte* EncodeInLowestBit::EncodeText(byte* image, unsigned int imageLength, byte* added, unsigned int addedLength, int offset)
{
	if (addedLength + offset > imageLength)
	{
		throw ref new InvalidArgumentException(L"Image too small");
	}


	for (unsigned int i = 0; i < addedLength; ++i)
	{
		int add = added[i];
		for (int bit = 7; bit >= 0; --bit, ++offset)
		{
			int b = (add >> bit) & 1;

			byte recordedByte = ((image[offset] & 0xFE) | b);

			image[offset] = recordedByte; // (byte) cast
		}
	}

	return image;
}

byte* EncodeInLowestBit::DecodeText(byte* image, shared_ptr<unsigned int> decodedLength)
{
	int length = 0;
	int offset = 32;

	for (int i = 0; i < 32; i++)
	{
		length = (length << 1) | (image[i] & 1);
	}

	*decodedLength = length;

	byte *result = new byte[length];
	for (int b = 0; b < length; ++b)
	{
		for (int i = 0; i < 8; ++i, ++offset)
		{
			int bit = (int) ((result[b] << 1) | image[offset] & 1);
			result[b] = bit; // 
		}
	}

	return result;
}