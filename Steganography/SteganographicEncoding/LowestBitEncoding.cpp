// Class1.cpp
#include "pch.h"
#include "LowestBitEncoding.h"

using namespace SteganographicEncoding;
using namespace Platform;
using namespace Collections;
//using namespace Platform::Collections;

LowestBitEncoding::LowestBitEncoding()
{
}

uint32 LowestBitEncoding::GetEncodedTextLength(VectorUINT8^ image)
{
	int length = 0;
	int offset = 32;

	for (int i = 0; i < 32; i++)
	{
		length = (length << 1) | (image->GetAt(i) & 1);
	}

	return length;
}

VectorUINT8^ LowestBitEncoding::DecodeText(VectorUINT8^ image, uint32 textLength)
{
	Vector<uint32>^ decoded = ref new Vector<uint32>{};
	
	int offset = 32;

	for (int b = 0; b < textLength; b++)
	{
		for (int i = 0; i < 8; i++, ++offset)
		{
			int bit = (int) ((decoded->GetAt(b) << 1) | image->GetAt(offset) & 1);
			decoded->InsertAt(b, bit);
		}
	}

	return decoded;
}

VectorUINT8^ LowestBitEncoding::EncodeText(VectorUINT8^ image, VectorUINT8^ added, int32 offset)
{
	if (added->Size + offset > image->Size)
	{
		throw ref new InvalidArgumentException(L"Image too small");
	}

	for (unsigned i = 0; i < added->Size; i++)
	{
		int add = added->GetAt(i);
		for (int bit = 7; bit >= 0; --bit, ++offset)
		{
			int b = (add >> bit) & 1;

			byte recordedByte = ((image->GetAt(offset) & 0xFE) | b);
			image->SetAt(offset, recordedByte);
		}
	}

	return image;
}

VectorUINT8^ LowestBitEncoding::BitConversion(int i)
{
	byte byte3 = (byte) ((i & 0xFF000000) >> 24);
	byte byte2 = (byte) ((i & 0x00FF0000) >> 16);
	byte byte1 = (byte) ((i & 0x0000FF00) >> 8);
	byte byte0 = (byte) ((i & 0x000000FF));

	Vector<uint32>^ newVec = ref new Vector<uint32>(4);
	newVec->Append(byte3);
	newVec->Append(byte2);
	newVec->Append(byte1);
	newVec->Append(byte0);

	return newVec;

	/*return(new byte[]
	{
		byte3, byte2, byte1, byte0
	});*/
}
