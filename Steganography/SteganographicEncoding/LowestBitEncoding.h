#pragma once

#include <collection.h>

using namespace Windows::Foundation::Collections;

namespace SteganographicEncoding
{
	class LowestBitEncoding
    {
    public:
		LowestBitEncoding();
		uint8* DecodeText(uint8* image, uint32 decodedLength);
		uint8* EncodeText(uint8* image, uint32 imageLength, uint8* added, uint32 addedLength, int32 offset);

		void LowestBitEncoding::Blabla(uint8* lala);
	
	/*	byte* DecodeText(byte* image, std::shared_ptr<unsigned int> decodedLength);
		byte* EncodeText(byte* image, unsigned int imageLength, byte* added, unsigned int addedLength, int offset);
		byte* BitConversion(int i);
		char* ConvertUTFToChar(const wchar_t* text, unsigned int length);*/
    };
}