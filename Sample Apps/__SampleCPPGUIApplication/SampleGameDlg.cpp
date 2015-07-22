// SampleGameDlg.cpp : implementation file
//

#include "SampleGameDlg.h"
#include "SampleGame.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()




// CSampleGameDlg dialog

CSampleGameDlg::CSampleGameDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSampleGameDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSampleGameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, lv_in_req);
	DDX_Control(pDX, IDC_LIST3, lv_sent_cmd);
	DDX_Control(pDX, IDC_STATIC1, grbxCommands);
	DDX_Control(pDX, IDC_status_logo, picConnectivity);
}

BEGIN_MESSAGE_MAP(CSampleGameDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CSampleGameDlg::OnBnClickedOk)
	ON_BN_CLICKED(btnKB_Open, &CSampleGameDlg::btnKB_OpenClick)
	ON_BN_CLICKED(btnKB_Close, &CSampleGameDlg::btnKB_CloseClick)
	ON_BN_CLICKED(btnToken, &CSampleGameDlg::btnTokenClick)
	ON_BN_CLICKED(btnStorage, &CSampleGameDlg::btnStorageClick)
	ON_BN_CLICKED(btnNotify, &CSampleGameDlg::btnNotifyClick)
	ON_BN_CLICKED(btnClearSent, &CSampleGameDlg::OnBnClickedbtnclearsent)
	ON_BN_CLICKED(btnClearReceived, &CSampleGameDlg::OnBnClickedbtnclearreceived)
	ON_WM_TIMER()
	ON_WM_CLOSE()
END_MESSAGE_MAP()

// CSampleGameDlg message handlers

BOOL CSampleGameDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// Extra initialization ...
	InitListView();

	CString caption;
	GetWindowText(caption);
	if (GFNLinkSDK::Instance()->IsGFNEnabled())
	{
		connectivity_icon.LoadBitmap(IDB_conn);
		caption += " (Connected to GFN)";
	}
	else
	{
		connectivity_icon.LoadBitmap(IDB_not_conn);
		caption += " (NOT connected to GFN)";
	}
	SetWindowText(caption);
	picConnectivity.SetBitmap(connectivity_icon);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

//-----------------------------------------------------------------------------------------------------------------------------------------
void CSampleGameDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

//-----------------------------------------------------------------------------------------------------------------------------------------
void CSampleGameDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//-----------------------------------------------------------------------------------------------------------------------------------------
HCURSOR CSampleGameDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//-----------------------------------------------------------------------------------------------------------------------------------------
void CSampleGameDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
}

//-----------------------------------------------------------------------------------------------------------------------------------------
void AddColumnsToList(CListCtrl * target_list_view, SColumnDescriptor *cols)
{
	LVCOLUMN lvColumn;
	int index = 0;
	for (SColumnDescriptor *col = cols; col->with > 0; col++)
	{
		lvColumn.mask = col->mask;
		lvColumn.fmt = col->fmt;
		lvColumn.cx = col->with;
		lvColumn.pszText = col->caption;
		target_list_view->InsertColumn(index++, &lvColumn);
	}
}

//-----------------------------------------------------------------------------------------------------------------------------------------
void CSampleGameDlg::InitListView()
{
	SColumnDescriptor req_cols[] = {
		{ 22, LVCF_FMT | LVCF_TEXT | LVCF_WIDTH, LVCFMT_LEFT, L"#" },
		{ 90, LVCF_FMT | LVCF_TEXT | LVCF_WIDTH, LVCFMT_LEFT, L"Request" },
		{ 150, LVCF_FMT | LVCF_TEXT | LVCF_WIDTH, LVCFMT_LEFT, L"Response" },
		{ -1 },
	};
	AddColumnsToList(&lv_in_req, req_cols);
	lv_in_req.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GFNLINES);

	SColumnDescriptor cmd_cols[] = {
		{ 22, LVCF_FMT | LVCF_TEXT | LVCF_WIDTH, LVCFMT_LEFT, L"#" },
		{ 120, LVCF_FMT | LVCF_TEXT | LVCF_WIDTH, LVCFMT_LEFT, L"Command" },
		{ 150, LVCF_FMT | LVCF_TEXT | LVCF_WIDTH, LVCFMT_LEFT, L"Result" },
		{ -1 },
	};
	AddColumnsToList(&lv_sent_cmd, cmd_cols);
	lv_sent_cmd.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GFNLINES);
}

//-----------------------------------------------------------------------------------------------------------------------------------------
void CSampleGameDlg::btnKB_OpenClick()
{
	AddToCmdList(L"Open Keyboard", GFNLinkSDK::Instance()->RequestKeyboardOverlayOpen(gspCenter));
}

//-----------------------------------------------------------------------------------------------------------------------------------------
void CSampleGameDlg::btnKB_CloseClick()
{
	AddToCmdList(L"Close Keyboard", GFNLinkSDK::Instance()->RequestKeyboardOverlayClose());
}

//-----------------------------------------------------------------------------------------------------------------------------------------
void CSampleGameDlg::btnTokenClick()
{
	const char *token = "";
	GFNLinkError err = GFNLinkSDK::Instance()->RequestGFNAccessToken(&token);
	AddToCmdList(L"Get Token", err, token);
}

//-----------------------------------------------------------------------------------------------------------------------------------------
void CSampleGameDlg::btnStorageClick()
{
	const char *locaiton = "";
	GFNLinkError err = GFNLinkSDK::Instance()->GetStorageLocation(&locaiton);
	AddToCmdList(L"Get Storage Location", err, locaiton);
}

//-----------------------------------------------------------------------------------------------------------------------------------------
void CSampleGameDlg::btnNotifyClick()
{
	AddToCmdList(L"SC Notification", GFNLinkSDK::Instance()->NotifyStorageChange());
}

//-----------------------------------------------------------------------------------------------------------------------------------------
void CSampleGameDlg::OnBnClickedbtnclearsent()
{
	lv_sent_cmd.DeleteAllItems();
}

//-----------------------------------------------------------------------------------------------------------------------------------------
void CSampleGameDlg::OnBnClickedbtnclearreceived()
{
	lv_in_req.DeleteAllItems();
}

//-----------------------------------------------------------------------------------------------------------------------------------------
void CSampleGameDlg::OnClose()
{
	CDialogEx::OnClose();
}

//-----------------------------------------------------------------------------------------------------------------------------------------
void CSampleGameDlg::AddToCmdList(LPWSTR cmd, GFNLinkError err, const char *result)
{
	wchar_t row_num[20];
	LVITEM lvItem;
	lvItem.mask = LVIF_TEXT;
	lvItem.iItem = lv_sent_cmd.GetItemCount();
	lvItem.iSubItem = 0;
	wsprintf(row_num, L"%d", lvItem.iItem + 1);
	lvItem.pszText = row_num;
	int nItem = lv_sent_cmd.InsertItem(&lvItem);

	lv_sent_cmd.SetItemText(nItem, 1, cmd);
	if (err != gleSuccess || result == NULL)
	{
		wchar_t err_msg[][40] = {
			L"OK",	// gleSuccess = 0,
			L"GFN DLL Not Present !",		 // gleGFNDLLNotPresent,
			L"GFN Com Not Established !",	 // gleGFNComNotEstablished,		// No controller/test application running to connect to.
			L"GFN Com Error !",			 // gleGFNComError,
			L"Error Calling DLL Function !", // gleErrorCallingDLLFunction,		// Generic DLL error - possibly due to incompatible DLL.
			L"Incompatible Version !",		 // gleIncompatibleVersion,
			L"Unable To Allocate Memory !",	 // gleUnableToAllocateMemory,
			L"Invalid Parameter !", // gleInvalidParameter,
			L"Internal Error !",	// gleInternalError
		};

		lv_sent_cmd.SetItemText(nItem, 2, err_msg[err]);
	}
	else
	{
		wchar_t ws_result[500];
		wsprintf(ws_result, L"%S", result);
		lv_sent_cmd.SetItemText(nItem, 2, ws_result);
	}
}

//-----------------------------------------------------------------------------------------------------------------------------------------
void CSampleGameDlg::AddToList(LPWSTR cmd, ApplicationResult res)
{
	wchar_t row_num[20];
	LVITEM lvItem;
	lvItem.mask = LVIF_TEXT;
	lvItem.iItem = lv_in_req.GetItemCount();
	lvItem.iSubItem = 0;
	wsprintf(row_num, L"%d", lvItem.iItem + 1);
	lvItem.pszText = row_num;
	int nItem = lv_in_req.InsertItem(&lvItem);
	lv_in_req.SetItemText(nItem, 1, cmd);

	wchar_t res_txt[][40] = {
		L"Not Implemented", // arNotImplemented = 0,	// Developers did not implement this method
		L"Success",			// arSuccess,				// Operation completed successfully
		L"Failure",			// arFailure				// General failure result 
	};

	lv_in_req.SetItemText(nItem, 2, res_txt[res]);
}