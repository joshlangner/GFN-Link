#pragma once

class CSampleGameApp : public CWinApp
{
public:
	CSampleGameApp();

// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

	DECLARE_MESSAGE_MAP()
};

extern CSampleGameApp theApp;