#pragma once

#include <iostream>
#include <fstream>
#include <Windows.h>
#include <Shobjidl.h>

std::ifstream* LoadFile()
{

	std::ifstream file;
	HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED |
		COINIT_DISABLE_OLE1DDE);
	PWSTR pszFilePath = NULL;
	LPOPENFILENAME filename = NULL;
	IFileOpenDialog *pFile;
	hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL,
		IID_IFileOpenDialog, reinterpret_cast<void**>(&pFile));

	if (SUCCEEDED(hr))
	{
		// Show the Open dialog box.
		hr = pFile->Show(NULL);
	}

	if (SUCCEEDED(hr))
	{
		IShellItem *pItem;
		hr = pFile->GetResult(&pItem);
		if (SUCCEEDED(hr))
		{

			hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);

			pItem->Release();
		}
	}
	file.open(pszFilePath);



	pFile->Release();
	CoUninitialize();

	return &file;
}