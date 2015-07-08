// Author: Mohammad D. Mottaghi

#include "afxdialogex.h"
#include <string>
#include <Winhttp.h>
#include"DlgHTTPRequest.h"
#include"HttpClient.h"
#include "GRIDLinkSDK_CAPI.hpp"

using namespace GRIDLinkSDK;


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define IDM_SIMULATOR_PATH L"http://localhost:55443/idmSimulator"

using namespace std;

BEGIN_MESSAGE_MAP(CHTTPRequestDlg, CDialogEx)	
	ON_BN_CLICKED(rdCustomIDM, &CHTTPRequestDlg::CustomIDMClick)
	ON_BN_CLICKED(rdSimIDM, &CHTTPRequestDlg::RestoreDefaults)
	ON_BN_CLICKED(btnProfile, &CHTTPRequestDlg::btnProfileClick)
	ON_BN_CLICKED(btnGo, &CHTTPRequestDlg::btnGoClick)
	ON_BN_CLICKED(btnClear, &CHTTPRequestDlg::btnClearClick)
END_MESSAGE_MAP()
//------------------------------------------------------------------------------------------------------------------------
CHTTPRequestDlg::CHTTPRequestDlg() : CDialogEx(CHTTPRequestDlg::IDD)
{
}
//------------------------------------------------------------------------------------------------------------------------
void CHTTPRequestDlg::ShowResponse(const char *rsp, size_t len)
{
	const size_t cSize = len + 1;
	wchar_t* w_resp = new wchar_t[cSize];
	mbstowcs(w_resp, rsp, cSize);
	txtResponse.SetWindowText(w_resp);
	delete[]w_resp;
}
//------------------------------------------------------------------------------------------------------------------------
void CHTTPRequestDlg::ReportError(const char *formatted_msg, int err_code)
{
	const size_t buf_len = 1000;
	char msg[buf_len] = "Failed ! ";
	if (err_code > 0)
		sprintf(msg + strlen(msg), formatted_msg, formatted_msg);
	else
		strcpy(msg + strlen(msg), formatted_msg);
	ShowResponse(msg, strlen(msg));
}
//------------------------------------------------------------------------------------------------------------------------
void CHTTPRequestDlg::btnClearClick()
{
	txtResponse.SetWindowText(L"");
}
//------------------------------------------------------------------------------------------------------------------------
void CHTTPRequestDlg::CustomIDMClick()
{
	GetDlgItem(btnProfile)->EnableWindow(false);
	GetDlgItem(btnGo)->SetWindowText(L"Pos&t Data");
	SetWindowText(L"HTTP-Post Composer");
	txtUrl.SetWindowText(L"http");
	txtHeaders.SetWindowText(L"");
}
//------------------------------------------------------------------------------------------------------------------------
void CHTTPRequestDlg::RestoreDefaults()
{
	GetDlgItem(btnGo)->SetWindowText(L"Get Session &Token");
	GetDlgItem(btnProfile)->EnableWindow(true);
	((CButton*)this->GetDlgItem(rdSimIDM))->SetCheck(true);
	SetWindowText(L"3rd-Party-IDM Simulator");
	
	txtUrl.SetWindowText(IDM_SIMULATOR_PATH);
	txtHeaders.SetWindowText(TEXT("Authorization: Basic b64(<Token>:)"));
	txtBody.SetWindowText(TEXT("")); // 
//	txtUrl.SetWindowText(TEXT("http://nvslb01.nvidia.com/api/1/authentication/user/login"));  
//	txtBody.SetWindowText(TEXT("{\"deviceId\": \"94211609774260224\"}")); // "token=<Token>"
//	txtHeaders.SetWindowText(TEXT("Authorization: Basic dGVzdEBnbWFpbC5jb206MTIzNEhlbGxv\r\ncontent-type:application/json"));
}
//------------------------------------------------------------------------------------------------------------------------
void CHTTPRequestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, txtBody);
	DDX_Control(pDX, IDC_EDIT2, txtUrl);
	DDX_Control(pDX, IDC_EDIT3, txtHeaders);
	DDX_Control(pDX, IDC_EDIT4, txtResponse);
	RestoreDefaults();
}
//------------------------------------------------------------------------------------------------------------------------
void CHTTPRequestDlg::btnProfileClick()
{
	const char *response;
	string user_profile = idm_simulator.GetUserProfile();
	if (user_profile.length() == 0)
		response = idm_simulator.GetLastError() == iseInvalidSessionToken ? "Error: Get a session token first." : idm_simulator.ErrorMessage();
	else
		response = user_profile.c_str();

	ShowResponse(response, strlen(response));
}
//------------------------------------------------------------------------------------------------------------------------
void CHTTPRequestDlg::btnGoClick()
{
	CString given_url;
	txtUrl.GetWindowText(given_url);

	if (given_url.Compare(IDM_SIMULATOR_PATH) == 0)
	{
		string success_results = "";
		const char *simulated_resp, *delegate_token = "";
		GRIDLinkError err = GRIDLinkSDK::Instance()->RequestGRIDAccessToken(&delegate_token);
		if (idm_simulator.ObtainSessionToken(delegate_token))
			simulated_resp = idm_simulator.ErrorMessage();
		else
		{
			success_results = "Session token received successfully:\r\n";
			success_results += idm_simulator.SessionToken();
			simulated_resp = success_results.c_str();
		}

		ShowResponse(simulated_resp, strlen(simulated_resp));
	}
	else
	{
		CString req_body, req_header;
		txtBody.GetWindowText(req_body);
		txtHeaders.GetWindowText(req_header);

		CHttpClient http(L"NVidia Sample Game");
		const char *real_idm_resp = http.Post(given_url.GetBuffer(), req_header.GetBuffer(), req_body.GetBuffer());
		ShowResponse(real_idm_resp, strlen(real_idm_resp));
	}
}
//------------------------------------------------------------------------------------------------------------------------
