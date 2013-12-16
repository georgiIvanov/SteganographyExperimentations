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
#include "FileHelper.h"

using namespace SteganographicEncoding;
using namespace EncodingMessageApp;
using namespace RoClasses;

using namespace Platform;
using namespace Platform::Collections;
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
FileInfo^ GetFile(StorageFolder^ folder);

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

void EncodingMessageApp::MainPage::Button_Click_3(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	StorageFolder^ localFolder = ApplicationData::Current->LocalFolder;
	fileInfo = GetFile(localFolder);

	auto openFileTask = create_task(localFolder->GetFileAsync(fileInfo->Name));
	openFileTask.then([this](StorageFile^ file){

		return create_task(file->OpenReadAsync());
	}).then([this](IRandomAccessStreamWithContentType^ stream){
		
		bitmap->SetSource(stream->CloneStream());
		roEncoder->SetBitmapStream(stream);
		_modifiedImage->Source = bitmap;
		_foundText->Text = roEncoder->DecodeTextInImage();
	});

}

void EncodingMessageApp::MainPage::Button_Click_4(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	if (!fileInfo)
	{
		return;
	}

	if (_stream != nullptr)
	{
		_stream->CommitAsync();
		for (size_t i = 0; i < 200000000; i++)
		{

		}
		
	}
	StorageFolder^ localFolder = ApplicationData::Current->LocalFolder;

	auto openFileTask = create_task(localFolder->GetFileAsync(fileInfo->Name));
	openFileTask.then([this](StorageFile^ file){
		
		return create_task(file->OpenTransactedWriteAsync());
	}).then([this](StorageStreamTransaction^ stream){
		roEncoder->ClosePreviousStream();
		roEncoder->SetBitmapStream(stream);
		_stream = stream;
		roEncoder->EncodeTextInStream(_text->Text);

	});
}


FileInfo^ GetFile(StorageFolder^ folder)
{
	

	String^ path(folder->Path + "\\*");
	WIN32_FIND_DATA findData;
	bool bContinue(true);
	Vector<FileInfo^>^ vector = ref new Vector<FileInfo^>();

	ZeroMemory(&findData, sizeof(findData));

	HANDLE hSearchHandle = ::FindFirstFileExW(
		path->Data(),
		FINDEX_INFO_LEVELS::FindExInfoBasic,
		&findData,
		FINDEX_SEARCH_OPS::FindExSearchNameMatch,
		nullptr,
		0);

	if (hSearchHandle == INVALID_HANDLE_VALUE)
	{
		DWORD dwError = ::GetLastError();
		throw ref new COMException(dwError);
	}
	while (bContinue)
	{
		if (!(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
		{
			ULONG64 size = findData.nFileSizeHigh * ((ULONG64) MAXDWORD + 1);
			size += findData.nFileSizeLow;

			FileInfo^ fileInfo = ref new FileInfo(
				ref new String(findData.cFileName),
				size);

			vector->Append(fileInfo);
		}
		bContinue = static_cast<bool>(::FindNextFile(hSearchHandle, &findData));
	}


	return vector->First()->Current;
}

