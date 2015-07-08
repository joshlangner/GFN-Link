// Author: Mohammad D. Mottaghi

#pragma once
#include "stdafx.h"
#include <afxcmn.h>
#include "resource.h"		// main symbols
#include"IDMSimulator.h"


class CHTTPRequestDlg : public CDialogEx
{
public:
	CEdit txtUrl;
	CEdit txtHeaders;
	CEdit txtBody;
	CEdit txtResponse;

	CHTTPRequestDlg();

	// Dialog Data
	enum { IDD = IDD_HTTP_REQ };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	// Implementation
protected:
	DECLARE_MESSAGE_MAP()

private:
	C3rdPartyIDMSimulator idm_simulator;

	void btnGoClick();
	void btnClearClick();
	void btnProfileClick();
	void RestoreDefaults();
	void CustomIDMClick();
	void ReportError(const char *formatted_msg, int err_code);
	void ShowResponse(const char *rsp, size_t len);
};

