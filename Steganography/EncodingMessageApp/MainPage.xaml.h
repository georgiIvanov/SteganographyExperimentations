//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"
#include <robuffer.h>
#include <wrl.h>
#include "EncodeInLowestBit.h"


//using namespace Windows::UI::Xaml::Media::Imaging;
//using namespace std;

namespace EncodingMessageApp
{
	/// <summary>
	/// An empty page that can be used on its own or navigated to within a Frame.
	/// </summary>
	public ref class MainPage sealed
	{
	public:
		MainPage();

	private:
		Windows::UI::Xaml::Media::Imaging::BitmapImage^ bitmap;
		std::shared_ptr<EncodeInLowestBit> bitEncoder;
		SteganographicEncoding::LowestBitEncoding^ roEncoder;

		void ChangeColors();
		void Button_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Button_Click_1(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Button_Click_2(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
	};
}
