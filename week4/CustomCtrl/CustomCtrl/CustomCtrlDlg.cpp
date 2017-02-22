
// CustomCtrlDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CustomCtrl.h"
#include "CustomCtrlDlg.h"
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
public:
//	afx_msg void OnColor2();
//	afx_msg void OnColor1();
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
//	ON_COMMAND(IDC_COLOR2, &CAboutDlg::OnColor2)
//	ON_COMMAND(IDC_COLOR1, &CAboutDlg::OnColor1)
END_MESSAGE_MAP()


// CCustomCtrlDlg dialog



CCustomCtrlDlg::CCustomCtrlDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCustomCtrlDlg::IDD, pParent)
	, m_color(0)
	, m_slider(0)
	, m_valor(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCustomCtrlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_COLOR1, m_color);
	DDX_Slider(pDX, IDC_SLIDER1, m_slider);
	DDX_Text(pDX, IDC_VALOR, m_valor);
}

BEGIN_MESSAGE_MAP(CCustomCtrlDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
//	ON_STN_CLICKED(IDC_PANEL1, &CCustomCtrlDlg::OnStnClickedPanel1)
//	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER1, &CCustomCtrlDlg::OnNMReleasedcaptureSlider1)
	ON_BN_CLICKED(IDC_COLOR1, &CCustomCtrlDlg::OnClickedColor1)
	ON_BN_CLICKED(IDC_COLOR2, &CCustomCtrlDlg::OnBnClickedColor2)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, &CCustomCtrlDlg::OnCustomdrawSlider1)
END_MESSAGE_MAP()


// CCustomCtrlDlg message handlers

BOOL CCustomCtrlDlg::OnInitDialog()
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
	p1.SubclassDlgItem(IDC_PANEL1, this);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCustomCtrlDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCustomCtrlDlg::OnPaint()
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
HCURSOR CCustomCtrlDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CCustomCtrlDlg::OnClickedColor1()
{
	// TODO: Add your control notification handler code here
	UpdateData(1);
	p1.color = m_color;
	p1.Invalidate(0);
}


void CCustomCtrlDlg::OnBnClickedColor2()
{
	// TODO: Add your control notification handler code here
	UpdateData(1);
	p1.color = m_color;
	p1.Invalidate(0);
}


void CCustomCtrlDlg::OnCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: Add your control notification handler code here
	UpdateData(1);
	p1.angulo = (m_slider*360)/100;
	p1.Invalidate(0);
	m_valor.Format("%d", p1.angulo);
	UpdateData(0);
	*pResult = 0;
}
