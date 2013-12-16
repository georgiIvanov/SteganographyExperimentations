#pragma once
#include <memory>

namespace SteganographicEncoding
{
	using namespace std;
	public ref class LowestBitEncoding sealed
    {
		Windows::UI::Xaml::Media::Imaging::WriteableBitmap^ bitmap;
		Windows::Storage::StorageStreamTransaction^ stream;

		shared_ptr<byte*> DecodeText(shared_ptr<byte*> image, shared_ptr<unsigned int> decodedLength);
		shared_ptr<byte*> EncodeText(shared_ptr<byte*> image, unsigned int imageLength, shared_ptr<byte*> added, unsigned int addedLength, int offset);
		shared_ptr<byte*> BitConversion(int i);
		char* ConvertUTFToChar(const wchar_t* text, unsigned int length);
		shared_ptr<byte*> GetImageBuffer();
		shared_ptr<byte*> GetStreamBuffer();
		unsigned int MaxBytesInImage();
    public:
		LowestBitEncoding::LowestBitEncoding();

		void EncodeTextInImage(Platform::String^ inputText);
		void EncodeTextInStream(Platform::String^ inputText);
		Platform::String^ DecodeTextInImage();
		void SetBitmapStream(Windows::Storage::Streams::IRandomAccessStreamWithContentType^ stream);
		void SetBitmapStream(Windows::Storage::StorageStreamTransaction^ stream);
		void ClosePreviousStream();

    };
}