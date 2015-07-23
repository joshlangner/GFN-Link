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


#include "afxdialogex.h"
#include <Winhttp.h>
#include<string>

using namespace std;

#ifndef HHttpClient
#define HHttpClient

class CHttpClient
{
private:
	int last_err_code;
	HINTERNET  hSession = NULL;
	string response;

	void StoreErrorCode() { last_err_code = GetLastError(); }
	const char *SendRequest(const wchar_t * verb, const wchar_t * target_url, const wchar_t * headers, const wchar_t * body);

public:
	CHttpClient(const wchar_t *app_name = nullptr);
	~CHttpClient();
	int LastErr() { return last_err_code; }
	void ResetError() { last_err_code = 0; }
	const char *Post(const wchar_t * target_url, const wchar_t * headers, const wchar_t * body);
	const char *Get(const wchar_t * target_url, const wchar_t * headers);
};
//==================================================================================================================================
template <class TSrcCell>
class CParsedURL
{
private:
	wchar_t *base;
	wchar_t *route;

	void CopyContents(wchar_t *dest, const char * src, int len) 	{ mbstowcs(dest, src, len); }
	void CopyContents(wchar_t *dest, const wchar_t * src, int len) 	{ memcpy(dest, src, len * sizeof(wchar_t)); }
	void LoadString(TSrcCell *&dest, const char *src, int len)
	{
		if (dest)
			delete[]dest;
		dest = new wchar_t[len + 1];
		CopyContents(dest, src, len);
		dest[len] = 0;
	}
	void ReadBase(const char *src, size_t len) { LoadString(base, src, len); }
	void ReadRoute(const char *src, size_t len) { LoadString(route, src, len); }

public:
	bool is_https;
	const wchar_t *Base()	{ return base; }
	const wchar_t *Route() { return route; }

	CParsedURL() { base = route = NULL; }
	~CParsedURL() { delete[]base; delete[]route; }
	void Parse(const char * raw_url);
	void Parse(const wchar_t * raw_url);
};
//------------------------------------------------------------------------------------------------------------------------
#endif