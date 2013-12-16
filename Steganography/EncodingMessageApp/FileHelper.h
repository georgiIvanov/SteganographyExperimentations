#pragma once

using namespace Platform;


namespace RoClasses
{


	public ref class FileInfo sealed
	{
	public:
		property ULONG64 Size
		{
			ULONG64 get();
		}
		property String^ Name
		{
			String^ get();
		}
	internal:
		FileInfo(String^ name, ULONG64 ulSize);
	private:
		ULONG64 _ulSize;
		String^ _name;
	};
	public ref class FolderInfo sealed
	{
	public:
		//static Windows::Foundation::Collections::IVector<FileInfo^>^ GetEntries(Windows::Storage::StorageFolder^ folder);
	private:
		FolderInfo();
	};
}