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
    afx_msg void btnReq3PTokenClick();
    afx_msg void btnSet3PTokenClick();
    afx_msg void btnStorageClick();
	afx_msg void btnNotifyClick();
	afx_msg void OnBnClickedbtnAuth();
	afx_msg void OnBnClickedbtnclearsent();
	afx_msg void OnBnClickedbtnclearreceived();
	afx_msg void OnClose();

	void AddToCmdList(LPWSTR cmd, GFNLinkError err = gleSuccess, const char *result=NULL);
	void AddToList(LPWSTR, ApplicationResult);
};
