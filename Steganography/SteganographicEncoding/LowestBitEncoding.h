#pragma once

#include <collection.h>

//using namespace ;

namespace SteganographicEncoding
{
	using VectorUINT8 = Windows::Foundation::Collections::IVector<uint8>;

	public ref class LowestBitEncoding sealed
    {
    public:
		LowestBitEncoding();

		VectorUINT8^ DecodeText(VectorUINT8^ image, uint32 textLength); //, uint32 decodedLength
		VectorUINT8^ EncodeText(VectorUINT8^ image, VectorUINT8^ added, int32 offset); // uint32 imageLength, uint32 addedLength, 
		uint32 GetEncodedTextLength(VectorUINT8^ image);
		
	
	/*	byte* DecodeText(byte* image, std::shared_ptr<unsigned int> decodedLength);
		byte* EncodeText(byte* image, unsigned int imageLength, byte* added, unsigned int addedLength, int offset);
		byte* BitConversion(int i);
		char* ConvertUTFToChar(const wchar_t* text, unsigned int length);*/
    };
}