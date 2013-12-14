﻿// Class1.cpp
#include "pch.h"
#include <robuffer.h>

#include "LowestBitEncoding.h"


using namespace SteganographicEncoding;
using namespace Platform;
using namespace Collections;
using namespace Windows::Storage::Streams;
using namespace Windows::UI::Xaml::Media::Imaging;
using namespace std;

LowestBitEncoding::LowestBitEncoding()
{
	bitmap = ref new WriteableBitmap(1, 1);
}

shared_ptr<byte*> LowestBitEncoding::BitConversion(int i)
{
	byte byte3 = (byte) ((i & 0xFF000000) >> 24);
	byte byte2 = (byte) ((i & 0x00FF0000) >> 16);
	byte byte1 = (byte) ((i & 0x0000FF00) >> 8);
	byte byte0 = (byte) ((i & 0x000000FF));

	return make_shared<byte*>(new byte[]
	{
		byte3, byte2, byte1, byte0
	});
}

char* LowestBitEncoding::ConvertUTFToChar(const wchar_t* text, unsigned int length)
{
	char* cString = new char[length + 1];
	cString[length] = 0;
	for (unsigned y = 0; y < length; y++)
	{
		char c = (char) text[y];
		cString[y] = c;
	}

	return cString;
}

shared_ptr<byte*> LowestBitEncoding::EncodeText(shared_ptr<byte*> image, unsigned int imageLength, shared_ptr<byte*> added, unsigned int addedLength, int offset)
{
	if (addedLength + offset > imageLength)
	{
		throw ref new InvalidArgumentException(L"Image too small");
	}


	for (unsigned int i = 0; i < addedLength; ++i)
	{
		int add = (*added)[i];
		for (int bit = 7; bit >= 0; --bit, ++offset)
		{
			int b = (add >> bit) & 1;

			byte recordedByte = (((*image)[offset] & 0xFE) | b);

			(*image)[offset] = recordedByte;
		}
	}

	return image;
}

shared_ptr<byte*> LowestBitEncoding::DecodeText(shared_ptr<byte*> image, shared_ptr<unsigned int> decodedLength)
{
	int length = 0;
	int offset = 32;

	for (int i = 0; i < 32; i++)
	{
		length = (length << 1) | ((*image)[i] & 1);
	}

	*decodedLength = length;

	shared_ptr<byte*>result = make_shared<byte*>(new byte[length]);
	for (int b = 0; b < length; ++b)
	{
		for (int i = 0; i < 8; ++i, ++offset)
		{
			int bit = (int) (((*result)[b] << 1) | (*image)[offset] & 1);
			(*result)[b] = bit;
		}
	}

	return result;
}

shared_ptr<byte*> LowestBitEncoding::GetImageBuffer()
{
	
	Microsoft::WRL::ComPtr<IUnknown> buffer((IUnknown*) bitmap->PixelBuffer);
	Microsoft::WRL::ComPtr<IBufferByteAccess> byteBuffer;
	buffer.As(&byteBuffer);

	//byte* bits;
	auto bits = make_shared<byte*>();
	byteBuffer->Buffer(&(*bits));

	return bits;
}

void LowestBitEncoding::SetBitmapStream(IRandomAccessStreamWithContentType^ stream)
{
	bitmap->SetSource(stream);
}

void LowestBitEncoding::EncodeTextInImage(String^ inputText)
{
	unsigned int length = inputText->Length();
	const wchar_t* text = inputText->Data();

	shared_ptr<byte*> convertedText = make_shared<byte*>((byte*)this->ConvertUTFToChar(text, length));


	shared_ptr<byte*> image = GetImageBuffer();
	unsigned int pixelCount = bitmap->PixelWidth * bitmap->PixelHeight;
	auto byteCount = pixelCount * 4; // bitsPerPixel * pixelCount / 8

	shared_ptr<byte*> textLength = this->BitConversion(length);

	this->EncodeText(image, byteCount, textLength, 4, 0);
	this->EncodeText(image, byteCount, convertedText, length, 32);
}

String^ LowestBitEncoding::DecodeTextInImage()
{
	shared_ptr<byte*> image = this->GetImageBuffer();

	shared_ptr<unsigned int> decodedLength(new unsigned int(0));

	shared_ptr<byte*> decodedText = this->DecodeText(image, decodedLength);



	int wchars_num = MultiByteToWideChar(CP_UTF8, 0, (char*) (*decodedText), -1, NULL, 0);
	wchar_t* wstr = new wchar_t[wchars_num];

	MultiByteToWideChar(CP_UTF8, 0, (char*) *decodedText, -1, wstr, wchars_num);

	String^ str = ref new String(wstr, *decodedLength);
	return str;
}
