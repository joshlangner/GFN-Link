// SampleGameDlg.h : header file
//

#pragma once
#include "stdafx.h"
#include <afxcmn.h>
#include "resource.h"		// main symbols
#include "GFNLinkSDK_CAPI.hpp"

using namespace GFNLinkSDK;

struct SColumnDescriptor
{
	int with;
	UINT mask;
	int fmt;
	LPWSTR caption;
};

// CSampleGameDlg dialog
class CSampleGameDlg : public CDialogEx
{
// Construction
public:
	CSampleGameDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_SAMPLEGAME_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

private:
	CBitmap connectivity_icon;

	void InitListView();

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedOk();
	afx_msg void btnKB_OpenClick();
	afx_msg void btnKB_CloseClick();

	CListCtrl lv_in_req;
	CListCtrl lv_sent_cmd;
	CStatic grbxCommands;
	CStatic picConnectivity;
	afx_msg void btnTokenClick();
	afx_msg void btnStorageClick();
	afx_msg void btnNotifyClick();
	afx_msg void OnBnClickedbtnclearsent();
	afx_msg void OnBnClickedbtnclearreceived();
	afx_msg void OnClose();

	void AddToCmdList(LPWSTR cmd, GFNLinkError err = gleSuccess, const char *result=NULL);
	void AddToList(LPWSTR, ApplicationResult);
};
