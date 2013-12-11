//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"
#include <robuffer.h>
#include <wrl.h>
#include <time.h>
#include <windows.h>
#include <string>
#include "EncodeInLowestBit.h"


using namespace SteganographicEncoding;
using namespace EncodingMessageApp;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;

using namespace Microsoft::WRL;
using namespace Windows::UI::Xaml::Media::Imaging;
using namespace Windows::Storage::Streams;
using namespace Windows::Storage;
using namespace Windows::Storage::FileProperties;
using namespace Windows::Storage::Pickers;
using namespace concurrency;
using namespace Windows::UI::Core;
using namespace std;

// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=234238

MainPage::MainPage()
{
	InitializeComponent();
	srand((unsigned) time(NULL));
	bitmap = ref new WriteableBitmap(1, 1);
	bitEncoder = shared_ptr<EncodeInLowestBit>();
	//setlocale(LC_ALL, "");
	TestClass^ test = ref new TestClass();
	auto lol = ref new Platform::Collections::Vector<uint8, uint8>();

	auto ff = test->DecodeText(lol, 32);

	
	unique_ptr<wstring> str;
	
	String^ displayText = ref new String();
	for (int i = 0; i < lol->Size; i ++)
	{
		
		/*wchar_t ch = (wchar_t) lol->GetAt(i).ToString;
		str->append(&ch);*/
		displayText = displayText->Concat(displayText, lol->GetAt(i).ToString());
	}

	
	_text->Text = displayText;
}


void EncodingMessageApp::MainPage::Button_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	FileOpenPicker^ openPicker = ref new FileOpenPicker();
	openPicker->FileTypeFilter->Append(".jpg");
	openPicker->FileTypeFilter->Append(".png");
	openPicker->ViewMode = PickerViewMode::Thumbnail;

	StorageFile^ file;// = openPicker->PickSingleFileAsync();

	auto fileTask = create_task(openPicker->PickSingleFileAsync());
	fileTask.then([this](StorageFile^ file)
	{
		if (file == nullptr)
		{
			cancel_current_task();
		}
		return create_task(file->OpenReadAsync());
	}).then([this](IRandomAccessStreamWithContentType^ stm)
	{
		bitmap->SetSource(stm);
		//ChangeColors();
		_modifiedImage->Source = bitmap;
	});

}

void MainPage::ChangeColors()
{


	byte* temp = this->GetImageBuffer();
	const unsigned int width = bitmap->PixelWidth;
	const unsigned int height = bitmap->PixelHeight;
	for (unsigned int k = 0; k < height; k++)
	{
		for (unsigned int i = 0; i < (width * 4); i += 4)
		{
			int pos = k * (width * 4) + (i);

			temp[pos] = temp[pos + 3];
			temp[pos + 1] = ~temp[pos + 2];
			temp[pos + 2] = ~temp[pos + 1];
			temp[pos + 3] = ~temp[pos];
			/*temp[pos] = rand() & 0xff;
			temp[pos + 1] = rand() & 0xff;
			temp[pos + 2] = rand() & 0xff;
			temp[pos + 3] = rand() & 0xff;*/
			/*temp[pos] = ~temp[pos];
			temp[pos + 1] = ~temp[pos + 1] / 3;
			temp[pos + 2] = ~temp[pos + 2] / 2;
			temp[pos + 3] = ~temp[pos + 3];*/
		}
	}


}

//byte* MainPage::EncodeText(byte* image, unsigned int imageLength, byte* added, unsigned int addedLength, int offset)
//{
//	if (addedLength + offset > imageLength)
//	{
//		throw ref new InvalidArgumentException(L"Image too small");
//	}
//
//	
//	for (unsigned int i = 0; i < addedLength; ++i)
//	{
//		int add = added[i];
//		for (int bit = 7; bit >= 0; --bit, ++offset)
//		{
//			int b = (add >> bit) & 1;
//
//			byte recordedByte = ((image[offset] & 0xFE) | b);
//			
//			image[offset] = recordedByte; // (byte) cast
//		}
//	}
//
//	return image;
//}
//
//byte* MainPage::DecodeText(byte* image, shared_ptr<unsigned int> decodedLength)
//{
//	int length = 0;
//	int offset = 32;
//
//	for (int i = 0; i < 32; i++)
//	{
//		length = (length << 1) | (image[i] & 1);
//	}
//
//	*decodedLength = length;
//
//	byte *result = new byte[length];
//	for (int b = 0; b < length ; ++b)
//	{
//		for (int i = 0; i < 8; ++i, ++offset)
//		{
//			int bit = (int) ((result[b] << 1) | image[offset] & 1);
//			result[b] = bit; // 
//		}
//	}
//
//	return result;
//}
//
//byte* MainPage::BitConversion(int i)
//{
//	//0 to 255
//	//return(new byte []{0, 0, 0, (byte) (i & 0x000000FF)});
//	byte byte3 = (byte) ((i & 0xFF000000) >> 24);
//	byte byte2 = (byte) ((i & 0x00FF0000) >> 16);
//	byte byte1 = (byte) ((i & 0x0000FF00) >> 8);
//	byte byte0 = (byte) ((i & 0x000000FF));
//	
//	return(new byte[]{byte3, byte2, byte1, byte0});
//
//}
//
//char* ConvertUTFToChar(const wchar_t* text, unsigned int length)
//{
//	char* cString = new char[length + 1];
//	cString[length] = 0;
//	for (int y = 0; y < length; y++)
//	{
//		char c = (char) text[y];
//		cString[y] = c;
//	}
//
//	return cString;
//}

byte* MainPage::GetImageBuffer()
{
	ComPtr<IUnknown> buffer((IUnknown*) bitmap->PixelBuffer);
	ComPtr<IBufferByteAccess> byteBuffer;
	buffer.As(&byteBuffer);

	byte* bits;
	byteBuffer->Buffer(&bits);

	return bits;
}



void EncodingMessageApp::MainPage::Button_Click_1(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	unsigned int length = _text->Text->Length();
	const wchar_t* text = _text->Text->Data();

	char* convertedText = bitEncoder->ConvertUTFToChar(text, length);


	byte* image = this->GetImageBuffer();
	unsigned int pixelCount = bitmap->PixelWidth * bitmap->PixelHeight;
	auto byteCount = pixelCount * 4; // bitsPerPixel * pixelCount / 8

	byte* textLength = bitEncoder->BitConversion(length);

	for (size_t i = 0; i < length; i++)
	{
		char a = convertedText[i]; // wchar shows
	}

	auto t = sizeof(wchar_t); // 2 bytes

	bitEncoder->EncodeText(image, byteCount, textLength, 4, 0);
	bitEncoder->EncodeText(image, byteCount, (byte*) convertedText, length, 32);

	bitmap->Invalidate();
}

void EncodingMessageApp::MainPage::Button_Click_2(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	byte* image = this->GetImageBuffer();

	shared_ptr<unsigned int> decodedLength(new unsigned int(0));

	byte* decodedText = bitEncoder->DecodeText(image, decodedLength);



	for (size_t i = 0; i < *decodedLength; i++)
	{
		char a = (char) decodedText[i];
		a = (char) decodedText[i];
	}

	int wchars_num = MultiByteToWideChar(CP_UTF8, 0, (char*) decodedText, -1, NULL, 0);
	wchar_t* wstr = new wchar_t[wchars_num];

	MultiByteToWideChar(CP_UTF8, 0, (char*) decodedText, -1, wstr, wchars_num);

	String^ str = ref new String(wstr, *decodedLength);




	delete[] wstr;

	_foundText->Text = str;
	//delete decodedText;
}




//auto bitmap = ref new WriteableBitmap(600, 600);
//
//_modifiedImage->Source = bitmap;
//
//ComPtr<IUnknown> buffer((IUnknown*) bitmap->PixelBuffer);
//ComPtr<IBufferByteAccess> byteBuffer;
//buffer.As(&byteBuffer);
//byte* bits;
//byteBuffer->Buffer(&bits);
//
//RGBQUAD* bits2 = (RGBQUAD*) bits;
//RGBQUAD color = {
//	rand() & 0xff,
//	rand() & 0xff,
//	rand() & 0xff
//};
//
//for (int y = 500; y < 600; y++)
//{
//	bits2[y] = color;
//}
//
//bitmap->Invalidate();

//shared_ptr<wstring> transformed = shared_ptr<wstring>(new wstring(;

//wstring *wc = new wstring(decodedLength, L'#');
//mbstowcs((wchar_t*)&wc[0], (char*) decodedText, (size_t)decodedLength.get());
//_Check_return_opt_ _CRTIMP errno_t __cdecl mbstowcs_s(size_t * _PtNumOfCharConverted, (_SizeInWords, *_PtNumOfCharConverted) wchar_t * _DstBuf, size_t _SizeInWords, (_MaxCount) const char * _SrcBuf, _In_ size_t _MaxCount);

/*size_t* numOfCharConverted = (size_t*) decodedLength.get();
(*numOfCharConverted)++;
wchar_t* destBuf = (wchar_t*) &wc[0];
size_t sizeInWords = 4;
const char* srcBuf = (const char*) decodedText;
size_t maxCount = (size_t) *decodedLength.get();
MultiByteToWideChar
mbstowcs_s(numOfCharConverted, destBuf, sizeInWords, srcBuf, maxCount);*/