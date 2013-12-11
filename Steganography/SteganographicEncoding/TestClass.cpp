#include <pch.h>
#include "TestClass.h"

using namespace Platform;
using namespace Windows::Foundation::Collections;
using namespace std;

namespace SteganographicEncoding
{

	/*uint8* TestClass::Lol()
	{
		uint8 a(0);
		return &a;
	}*/

	IVector<uint8>^ TestClass::DecodeText(IVector<uint8>^ image,
		uint32 decodedLength)
	{
		image->Append(4);
		image->Append(5);
		image->Append(6);

		return image;
	}

	String^ TestClass::GetMesssage()
	{
		String^ lol = ref new String(L"FUFUFU");

		return lol;
	}
}