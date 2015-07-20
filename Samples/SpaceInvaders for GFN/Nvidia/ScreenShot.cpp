// by: Mohammad Mottaghi (mamad@cs.duke.edu, mmottaghi@nvidia.com)

#define WIN32_LEAN_AND_MEAN			

#include <windows.h>				

int CaptureAnImage(HWND hWnd, const char * image_file_path)
{
	HDC hdcScreen;
	HDC hdcWindow;

	hdcScreen = GetDC(NULL);
	hdcWindow = GetDC(hWnd);

	HDC hdcMemDC = NULL;
	try
	{
		hdcMemDC = CreateCompatibleDC(hdcWindow);

		if (!hdcMemDC)
			throw 1; // MessageBox(hWnd, "CreateCompatibleDC has failed", "Failed", MB_OK);

		// Get the client area for size calculation
		RECT rcClient;
		GetClientRect(hWnd, &rcClient);

		//This is the best stretch mode
		SetStretchBltMode(hdcWindow, HALFTONE);

		//The source DC is the entire screen and the destination DC is the current window (HWND)
		if (!StretchBlt(hdcWindow, 0, 0, rcClient.right, rcClient.bottom, hdcScreen, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), SRCCOPY))
			throw 2; //  MessageBox(hWnd, "StretchBlt has failed", "Failed", MB_OK);

		HBITMAP hbmScreen = NULL;
		hbmScreen = CreateCompatibleBitmap(hdcWindow, rcClient.right - rcClient.left, rcClient.bottom - rcClient.top);

		if (!hbmScreen)
			throw 3; //  MessageBox(hWnd, "CreateCompatibleBitmap Failed", "Failed", MB_OK);

		SelectObject(hdcMemDC, hbmScreen);

		if (!BitBlt(hdcMemDC, 0, 0, rcClient.right - rcClient.left, rcClient.bottom - rcClient.top, hdcWindow, 0, 0, SRCCOPY))
			throw 4; // MessageBox(hWnd, "BitBlt has failed", "Failed", MB_OK);
	
		BITMAP bmpScreen;
		GetObject(hbmScreen, sizeof(BITMAP), &bmpScreen);	// Get the BITMAP from the HBITMAP

		BITMAPFILEHEADER   bmfHeader;
		BITMAPINFOHEADER   bi;

		bi.biSize = sizeof(BITMAPINFOHEADER);
		bi.biWidth = bmpScreen.bmWidth;
		bi.biHeight = bmpScreen.bmHeight;
		bi.biPlanes = 1;
		bi.biBitCount = 32;
		bi.biCompression = BI_RGB;
		bi.biSizeImage = 0;
		bi.biXPelsPerMeter = 0;
		bi.biYPelsPerMeter = 0;
		bi.biClrUsed = 0;
		bi.biClrImportant = 0;

		DWORD dwBmpSize = ((bmpScreen.bmWidth * bi.biBitCount + 31) / 32) * 4 * bmpScreen.bmHeight;

		// Starting with 32-bit Windows, GlobalAlloc and LocalAlloc are implemented as wrapper functions that 
		// call HeapAlloc using a handle to the process's default heap. Therefore, GlobalAlloc and LocalAlloc 
		// have greater overhead than HeapAlloc.
		HANDLE hDIB = GlobalAlloc(GHND, dwBmpSize);
		char *lpbitmap = (char *)GlobalLock(hDIB);

		// Gets the "bits" from the bitmap and copies them into a buffer 
		// which is pointed to by lpbitmap.
		GetDIBits(hdcWindow, hbmScreen, 0, (UINT)bmpScreen.bmHeight, lpbitmap, (BITMAPINFO *)&bi, DIB_RGB_COLORS);

		DWORD dwSizeofDIB = dwBmpSize + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
		//Offset to where the actual bitmap bits start.
		bmfHeader.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) + (DWORD)sizeof(BITMAPINFOHEADER);
		bmfHeader.bfSize = dwSizeofDIB;
		bmfHeader.bfType = 0x4D42; //BM   

		DWORD dwBytesWritten = 0;
		HANDLE hFile = CreateFile(image_file_path, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		if (hFile != FALSE)
		{
			WriteFile(hFile, (LPSTR)&bmfHeader, sizeof(BITMAPFILEHEADER), &dwBytesWritten, NULL);
			WriteFile(hFile, (LPSTR)&bi, sizeof(BITMAPINFOHEADER), &dwBytesWritten, NULL);
			WriteFile(hFile, (LPSTR)lpbitmap, dwBmpSize, &dwBytesWritten, NULL);
			CloseHandle(hFile);
		}

		GlobalUnlock(hDIB);
		GlobalFree(hDIB);
		DeleteObject(hbmScreen);
	}
	catch (int e)
	{
		char exc_msg[][50] = {
			"",
			"CreateCompatibleDC has failed",
			"StretchBlt has failed",
			"CreateCompatibleBitmap Failed",
			"BitBlt has failed"
		};
		MessageBox(hWnd, exc_msg[e], "Screenshot Failed", MB_OK);
	}

	DeleteObject(hdcMemDC);
	ReleaseDC(NULL, hdcScreen);
	ReleaseDC(hWnd, hdcWindow);

	return 0;
}


