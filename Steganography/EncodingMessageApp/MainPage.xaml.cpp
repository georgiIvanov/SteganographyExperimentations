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
	bitmap = ref new BitmapImage();
	bitEncoder = shared_ptr<EncodeInLowestBit>();
	
	roEncoder = ref new LowestBitEncoding();
	
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
		bitmap->SetSource(stm->CloneStream());
		roEncoder->SetBitmapStream(stm);

		_modifiedImage->Source = bitmap;
		
	});

}

void EncodingMessageApp::MainPage::Button_Click_1(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	roEncoder->EncodeTextInImage(_text->Text);
}

void EncodingMessageApp::MainPage::Button_Click_2(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	_foundText->Text = roEncoder->DecodeTextInImage();
}