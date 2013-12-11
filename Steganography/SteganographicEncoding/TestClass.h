#pragma once

#include <collection.h>
#include <pch.h>

namespace SteganographicEncoding
{
	namespace Collections = Windows::Foundation::Collections;

	public ref class TestClass sealed
	{
	public:
		Platform::String^ GetMesssage();
		Collections::IVector<uint8>^ DecodeText(Collections::IVector<uint8>^ image,
			uint32 decodedLength);
//		uint8* Lol();
	};
}