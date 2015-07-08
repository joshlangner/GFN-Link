// Author: Mohammad D. Mottaghi

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