
// DepositosDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Depositos.h"
#include "DepositosDlg.h"
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


// CDepositosDlg dialog



CDepositosDlg::CDepositosDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDepositosDlg::IDD, pParent)
	, m_ip(_T(""))
	, m_port(0)
	, m_dep1(_T(""))
	, m_dep2(_T(""))
	, m_msg(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDepositosDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_IP, m_ip);
	DDX_Text(pDX, IDC_PORT, m_port);
	DDX_Text(pDX, IDC_DEP1, m_dep1);
	DDX_Text(pDX, IDC_DEP2, m_dep2);
	DDX_Text(pDX, IDC_MSG, m_msg);
}

BEGIN_MESSAGE_MAP(CDepositosDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_START, &CDepositosDlg::OnBnClickedStart)
	ON_BN_CLICKED(IDC_STOP, &CDepositosDlg::OnBnClickedStop)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CDepositosDlg message handlers

BOOL CDepositosDlg::OnInitDialog()
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

	// TODO: Add extra initialization here

	p1.SubclassDlgItem(IDC_D1, this);
	p2.SubclassDlgItem(IDC_D2, this);

	sTCP = new CSockClient(this);
	sTCP->Create(502,SOCK_STREAM); // create socket TCP
	sTCP->Listen(); // listening 

	m_ip = "127.0.0.1";
	m_port = 502;
	UpdateData(0);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDepositosDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDepositosDlg::OnPaint()
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

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDepositosDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CDepositosDlg::OnBnClickedStart()
{
	UpdateData(1);
	// UDP
	pUDP = new CSockClient(this); // create socket
	if(!pUDP->Create(0,SOCK_DGRAM)){ // puerto 0 --> both sockets in port 502 doesn't work
		MessageBox("Error al crear client..."); return;
	}
	pUDP->SendTo("1", 1, m_port, m_ip);

	SetTimer(1,5000,NULL);

}


void CDepositosDlg::OnBnClickedStop()
{
	UpdateData(1);
	pUDP->SendTo("0", 1, m_port, m_ip);
	KillTimer(1);

	m_dep1 = "0";
	UpdateData(0);
	p1.height = 0;
	p1.Invalidate(1);
}


void CDepositosDlg::OnTimer(UINT_PTR nIDEvent)
{
	pUDP->SendTo("1", 1, m_port, m_ip);
	CDialogEx::OnTimer(nIDEvent);
}
