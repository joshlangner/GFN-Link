// Author: Mohammad D. Mottaghi

#include"IDMSimulator.h"
#include "base64.h"

const char C3rdPartyIDMSimulator::err_msg[][100] = {
	"No Error",  //iseNoError,
	"No delegate token provided !",  //iseEmptyToken,
	"Error in communication with Jarvis (Code: %d)",  //iseRequestError
	"Bad JSON format encountered in response !",  //iseResponseBadJSONFormat,
	"JSON key not found !",  //iseJsonKeyNotFound,
	"Session token is invalid.",   //iseInvalidSessionToken
	"Special error: message not available",  //	iseSpecialError,
};
//--------------------------------------------------------------------------------------------------------------
enIDMSimError ExtractFromJSON(char *value_buf, const char *key, const char *source_json)
{// returns true if error
	int key_len = strlen(key);

	for (const char * key_pos, *rest_of_json = source_json;; rest_of_json = key_pos + 1)
		if ((key_pos = strstr(rest_of_json, key)))
		{
			if (key_pos[key_len+1] == ':')
			{
				if (const char * val_pos = strchr(key_pos + key_len + 1, '"'))
				{
					sscanf(val_pos + 1, "%[^\"]", value_buf);
					break;
				}
				else
					return iseResponseBadJSONFormat; // json-format error: expected " but not found
			}
		}
		else
			return iseJsonKeyNotFound;

	return iseNoError;
}
//--------------------------------------------------------------------------------------------------------------
string	C3rdPartyIDMSimulator::GetUserProfile(const wchar_t * user_id)
{
	last_error = iseNoError; // reset error
	string user_profile = "";

	int ssn_token_len = strlen(session_token);
	if (ssn_token_len <= 0) // empty session token
	{
		last_error = iseInvalidSessionToken;
		return user_profile;
	}

	string ssn_token_with_colon = session_token;
	ssn_token_with_colon.append(":");
	string b64_token = base64_encode((const unsigned char *)ssn_token_with_colon.c_str(), ssn_token_len + 1);

	CString auth_header = L"Authorization: Basic ";
	auth_header += ToWideStr(b64_token.c_str()); // Authorization: Basic b64(<session_token>:)

	wstring api_url = JARVIS_PROFILE_URL;
	if (user_id != nullptr)
	{
		api_url.append(L"/");
		api_url.append(user_id);
	}

	const char * resp_json = web_client.Get(api_url.c_str(), auth_header.GetBuffer());

	if (resp_json == nullptr)
		last_error = iseRequestError;
	else
		user_profile = resp_json;

	return user_profile;
}
//--------------------------------------------------------------------------------------------------------------
bool C3rdPartyIDMSimulator::ObtainSessionToken(const char *del_token)
{// returns true if any error occurs
	last_error = iseNoError; // reset error
	session_token[0] = 0;

	int token_len = strlen(del_token);
	if (token_len <= 0)
	{
		last_error = iseEmptyToken;
		return true;
	}

	string del_token_with_colon = del_token;
	del_token_with_colon.append(":");
	string b64_token = base64_encode((const unsigned char *)del_token_with_colon.c_str(), token_len+1);

	CString auth_header = L"Content-Type: application/json\n";
	auth_header += L"Authorization: Basic ";
	auth_header += ToWideStr(b64_token.c_str()); // Authorization: Basic b64(<del_token>:)

	const char * resp_json = web_client.Post(
		JARVIS_REDEEM_URL,
		auth_header.GetBuffer(),
		JSON(MY_IDM_CIENT_ID, MY_IDM_DEVICE_ID));

	if (resp_json == nullptr)
		last_error = iseRequestError;
	else if (ExtractFromJSON(session_token, "sessionToken", resp_json) != iseNoError)
	{
		last_error = iseSpecialError;
		special_err_message = resp_json;
	}

	return last_error != iseNoError;
}
//--------------------------------------------------------------------------------------------------------------
const wchar_t * C3rdPartyIDMSimulator::ToWideStr(const char *nstr)
{
	const size_t cSize = strlen(nstr) + 1;
	if (wstr_buf)
		delete[]wstr_buf;			
	wstr_buf = new wchar_t[cSize];
	mbstowcs(wstr_buf, nstr, cSize);
	return wstr_buf;
}
//--------------------------------------------------------------------------------------------------------------
const char * C3rdPartyIDMSimulator::ErrorMessage()
{	
	if (last_error == iseSpecialError)
		return special_err_message.c_str();
	return err_msg[last_error];
}

