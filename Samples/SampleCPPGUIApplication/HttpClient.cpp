// Author: Mohammad D. Mottaghi

/* Copyright (c) 2015, NVIDIA CORPORATION. All rights reserved.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions
  are met:
   * Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   * Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in the
     documentation and/or other materials provided with the distribution.
   * Neither the name of NVIDIA CORPORATION nor the names of its
     contributors may be used to endorse or promote products derived
     from this software without specific prior written permission.
 
  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS "AS IS" AND ANY
  EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
  PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
  PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
  OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. */

#include"HttpClient.h"


CHttpClient::CHttpClient(const wchar_t *app_name)
{
	ResetError();
	hSession = WinHttpOpen(app_name? app_name:L"NVIDIA HTTP Client", WINHTTP_ACCESS_TYPE_DEFAULT_PROXY, WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0);
}
//------------------------------------------------------------------------------------------------------------------------
CHttpClient::~CHttpClient()
{
	if (hSession)
		WinHttpCloseHandle(hSession);
}
//------------------------------------------------------------------------------------------------------------------------
const char *CHttpClient::Post(const wchar_t * target_url, const wchar_t * headers, const wchar_t * body)
{
	return SendRequest(L"POST", target_url, headers, body);
}
//------------------------------------------------------------------------------------------------------------------------
const char *CHttpClient::Get(const wchar_t * target_url, const wchar_t * headers)
{
	return SendRequest(L"GET", target_url, headers, nullptr);
}
//------------------------------------------------------------------------------------------------------------------------
const char *CHttpClient::SendRequest(const wchar_t * verb, const wchar_t * target_url, const wchar_t * headers, const wchar_t * body)
{
	CParsedURL<wchar_t> url;
	url.Parse(target_url);

	HINTERNET  hConnect = NULL, hRequest = NULL;
	if (hSession) // Specify an HTTP server.
		hConnect = WinHttpConnect(hSession, url.Base(), url.is_https ? INTERNET_DEFAULT_HTTPS_PORT : INTERNET_DEFAULT_HTTP_PORT, 0);

	if (hConnect) // Create an HTTP request handle.
		hRequest = WinHttpOpenRequest(hConnect, verb, url.Route(), NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, 0);

	BOOL  bResults = FALSE;
	if (hRequest) // Send a request.
	{
		if (body==nullptr) // indicates a GET request
			bResults = WinHttpSendRequest(hRequest, headers, wcslen(headers), WINHTTP_NO_REQUEST_DATA, 0, 0, NULL);
		else
			bResults = WinHttpSendRequest(hRequest, headers, wcslen(headers), (LPVOID)body, (DWORD)wcslen(body) * 2, (DWORD)wcslen(body) * 2, NULL);
	}

	if (bResults)// End the request.
		bResults = WinHttpReceiveResponse(hRequest, NULL);

	response.clear();
	// Keep checking for data until there is nothing left.
	if (bResults)
		for (DWORD dwSize = 1; dwSize > 0;)
		{
			if (!WinHttpQueryDataAvailable(hRequest, &dwSize)) // Check for available data.
				StoreErrorCode();

			LPSTR pszOutBuffer = new char[dwSize + 1]; // Allocate space for the buffer.
			if (!pszOutBuffer)
			{
				//ReportError("Out of memory\n", -1);
				dwSize = 0;
			}
			else
			{
				ZeroMemory(pszOutBuffer, dwSize + 1);

				DWORD dwDownloaded = 0;
				if (WinHttpReadData(hRequest, (LPVOID)pszOutBuffer, dwSize, &dwDownloaded)) // Read the data.
					response.append(pszOutBuffer);
				else
					StoreErrorCode();

				delete[] pszOutBuffer;// Free the memory allocated to the buffer.
			}
		}
	else // !bResults
		StoreErrorCode();

	// Close any open handles.
	if (hRequest) WinHttpCloseHandle(hRequest);
	if (hConnect) WinHttpCloseHandle(hConnect);

	return last_err_code? nullptr : response.c_str();
}
//===================================================================================================================================================
template<class T>
void CParsedURL<T>::Parse(const char * raw_url)
{
	const char *url_start = raw_url;
	while (*url_start == ' ')
		url_start++;
	is_https = strstr(url_start, "https:") || strstr(url_start, "HTTPS:");

	const char *base_start = strstr(raw_url, "://");
	if (base_start == NULL)
		for (base_start = raw_url; *base_start == ' '; base_start++); // skipping leading spaces		
	else
		base_start += 3; // 3 ---> strlen("://")

	const char *base_end = strstr(base_start, "/");
	if (base_end == NULL)
		base_end = base_start + strlen(base_start);
	ReadBase(base_start, base_end - base_start);
	ReadRoute(base_end, strlen(base_end));
}
//------------------------------------------------------------------------------------------------------------------------
template <class T>
void CParsedURL<T>::Parse(const wchar_t * raw_url)
{
	int copied_chars = 0, url_length = wcslen(raw_url);
	char *ascii_url = new char[url_length + 1];
	for (char *d = ascii_url, *s = (char *)raw_url; copied_chars < url_length; d++, s += 2, copied_chars++)
		*d = *s;
	ascii_url[url_length] = 0;
	Parse(ascii_url);
}
