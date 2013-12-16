#include <pch.h>
#include "FileHelper.h"
#include <wrl.h>

using namespace RoClasses;
using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::Foundation::Collections;
using namespace Windows::Storage;

FileInfo::FileInfo(String^ name, ULONG64 ulSize) :
_name(name), _ulSize(ulSize)
{
}

ULONG64 FileInfo::Size::get()
{
	return(_ulSize);
}

String^ FileInfo::Name::get()
{
	return(_name);
}

FolderInfo::FolderInfo()
{
}

//IVector<FileInfo^>^ FolderInfo::GetEntries(StorageFolder^ folder)
//{
//	String^ path(folder->Path + "\\*");
//	WIN32_FIND_DATA findData;
//	bool bContinue(true);
//	Vector<FileInfo^>^ vector = ref new Vector<FileInfo^>();
//
//	ZeroMemory(&findData, sizeof(findData));
//
//	HANDLE hSearchHandle = ::FindFirstFileExW(
//		path->Data(),
//		FINDEX_INFO_LEVELS::FindExInfoBasic,
//		&findData,
//		FINDEX_SEARCH_OPS::FindExSearchNameMatch,
//		nullptr,
//		0);
//
//	if (hSearchHandle == INVALID_HANDLE_VALUE)
//	{
//		DWORD dwError = ::GetLastError();
//		throw ref new COMException(dwError);
//	}
//	while (bContinue)
//	{
//		if (!(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
//		{
//			ULONG64 size = findData.nFileSizeHigh * ((ULONG64) MAXDWORD + 1);
//			size += findData.nFileSizeLow;
//
//			FileInfo^ fileInfo = ref new FileInfo(
//				ref new String(findData.cFileName),
//				size);
//
//			vector->Append(fileInfo);
//		}
//		bContinue = ::FindNextFile(hSearchHandle, &findData);
//	}
//	return(vector);
//}