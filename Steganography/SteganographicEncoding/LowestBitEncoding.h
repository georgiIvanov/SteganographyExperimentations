#pragma once

namespace SteganographicEncoding
{
	public ref class LowestBitEncoding sealed
    {
		Windows::UI::Xaml::Media::Imaging::WriteableBitmap^ bitmap;

		byte* DecodeText(byte* image, std::shared_ptr<unsigned int> decodedLength);
		byte* EncodeText(byte* image, unsigned int imageLength, byte* added, unsigned int addedLength, int offset);
		byte* BitConversion(int i);
		char* ConvertUTFToChar(const wchar_t* text, unsigned int length);
		byte* GetImageBuffer();

    public:
		LowestBitEncoding::LowestBitEncoding();

		void EncodeTextInImage(Platform::String^ inputText);
		Platform::String^ DecodeTextInImage();
		void SetBitmapStream(Windows::Storage::Streams::IRandomAccessStreamWithContentType^ stream);
    };
}