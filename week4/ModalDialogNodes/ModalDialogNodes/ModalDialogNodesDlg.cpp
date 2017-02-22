
// ModalDialogNodesDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ModalDialogNodes.h"
#include "ModalDialogNodesDlg.h"
#include "afxdialogex.h"
#include <algorithm> // for std::find
#include <iterator> // for std::begin, std::end

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


// CModalDialogNodesDlg dialog



CModalDialogNodesDlg::CModalDialogNodesDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CModalDialogNodesDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CModalDialogNodesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PANEL, m_figura);
}

BEGIN_MESSAGE_MAP(CModalDialogNodesDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_ADD, &CModalDialogNodesDlg::OnBnClickedAdd)
END_MESSAGE_MAP()


// CModalDialogNodesDlg message handlers

BOOL CModalDialogNodesDlg::OnInitDialog()
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
	nNodos = 0;

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CModalDialogNodesDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CModalDialogNodesDlg::OnPaint()
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

		// new code
		CDC *p = m_figura.GetDC();
		CRect r;
		m_figura.GetClientRect(r);
		p->FillSolidRect(r, RGB(255,255,255));

		// paint all nodes, not just the new ones
		for(size_t i = 0; i<nNodos; i++){
			if(data[i].x >= r.left && data[i].x <= r.right && data[i].y >= r.top && data[i].y <= r.bottom)
				p->Ellipse(data[i].x-5, data[i].y-5, data[i].x+5, data[i].y+5);
			else AfxMessageBox("Dimensions have been exceeded");
		}
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CModalDialogNodesDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CModalDialogNodesDlg::OnBnClickedAdd()
{
	CNode n1;
	if(n1.DoModal() == IDOK){
		data[nNodos].id = n1.m_id; // store the node numbers in a local array
		data[nNodos].x = n1.m_x;
		data[nNodos].y = n1.m_y;
		nNodos++;
		this->Invalidate(1); // go to onpaint
	}
}
