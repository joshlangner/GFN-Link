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

#include "stdafx.h"
#include<string>
#include"HttpClient.h"

using namespace std;

#ifndef H3rdPartyIDMSimulator
#define H3rdPartyIDMSimulator

#define MY_IDM_CIENT_ID 94211609774260224  // Each IDM (Identity Manager) has a unique ID which is recognized by NVIDIA's IDM
#define MY_IDM_DEVICE_ID 5894509482345
#define JARVIS_REDEEM_URL L"http://nvslb01.nvidia.com/api/1/authentication/delegate/redeem"
#define JARVIS_PROFILE_URL L"http://nvslb01.nvidia.com/api/1/profile/user"

#define _LSTR(s) L ## #s
#define LSTR(s) _LSTR(s)

#define KeyVAL(k1,v1,k2,v2) {## k1 ##:## #v1 ##,## k2 ##:## #v2 ##}
#define JSON(clientID,devID) LSTR(KeyVAL("clientId", clientID, "deviceId", devID))
 
enum enIDMSimError
{
	iseNoError,
	iseEmptyToken,
	iseRequestError,
	iseResponseBadJSONFormat,
	iseJsonKeyNotFound,
	iseInvalidSessionToken,
	iseSpecialError,
};
//====================================================================================================
#define MAX_TOKEN_SIZE 500
class C3rdPartyIDMSimulator  // Sample Game-Developer's Identity Manager 
{
private:
	char		session_token[MAX_TOKEN_SIZE];
	wchar_t*	wstr_buf;
	CHttpClient web_client;
	enIDMSimError last_error;

	static const char	err_msg[][100];
	string				special_err_message;

	const wchar_t * ToWideStr(const char *nstr);
		
public:
	C3rdPartyIDMSimulator() { wstr_buf = nullptr; last_error = iseNoError; session_token[0] = 0; }
	~C3rdPartyIDMSimulator() { delete []wstr_buf; }

	const char * ErrorMessage();
	const char * SessionToken() { return session_token; }
	bool	ObtainSessionToken(const char *del_token);
	string	GetUserProfile(const wchar_t * user_id = nullptr);
	string	GetMyProfile() {return GetUserProfile(nullptr);}
	enIDMSimError GetLastError(){ return last_error; }
};

#endif