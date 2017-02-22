
// robocopDlg.cpp : implementation file
//

#include "stdafx.h"
#include "robocop.h"
#include "robocopDlg.h"
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


// CrobocopDlg dialog



CrobocopDlg::CrobocopDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CrobocopDlg::IDD, pParent)
	, m_num(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CrobocopDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_NUM, m_num);
	DDX_Control(pDX, IDC_LISTA, m_lista);
}

BEGIN_MESSAGE_MAP(CrobocopDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_EXIT, &CrobocopDlg::OnBnClickedExit)
	ON_BN_CLICKED(IDC_START, &CrobocopDlg::OnBnClickedStart)
	ON_BN_CLICKED(IDC_RESET, &CrobocopDlg::OnBnClickedReset)
END_MESSAGE_MAP()


// CrobocopDlg message handlers

BOOL CrobocopDlg::OnInitDialog()
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

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CrobocopDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CrobocopDlg::OnPaint()
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
HCURSOR CrobocopDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CrobocopDlg::OnBnClickedExit()
{
	CDialog::OnOK();
}

UINT Robot1(LPVOID lp)
{
	CString cs;
	CrobocopDlg *pDlg = (CrobocopDlg*)lp;
	srand(time(NULL)); //cambia semilla
	int wait = rand()%250; //max 250ms
	for (int i=0;i<pDlg->m_num;i++){
		cs.Format("Robot1: task %d",i);
		pDlg->m_lista.AddString(cs);
		Sleep(wait); //duerme
	}
	pDlg->m_lista.AddString("Fin robot1...");
	return 0;
}

UINT Robot2(LPVOID lp)
{
	CString cs;
	CrobocopDlg *pDlg = (CrobocopDlg*)lp;
	int wait = rand()%250;
	for (int i=0;i<pDlg->m_num;i++){
		cs.Format("Robot2: task %d",i);
		pDlg->m_lista.AddString(cs);
		Sleep(wait); //duerme
	}
	pDlg->m_lista.AddString("Fin robot2...");
	return 0;
}

void CrobocopDlg::OnBnClickedStart()
{
	UpdateData(1); //actualizar variables, coger m_num
	CString cs;
	m_lista.ResetContent(); //limpiar lista
	cs.Format("Num Tasks=%d",m_num);
	m_lista.AddString(cs); //Agregar a lista
	//Crear Hilos Robot1 y Robot2
	CWinThread *p1 = AfxBeginThread(Robot1,this);
	CWinThread *p2 = AfxBeginThread(Robot2,this);
}


void CrobocopDlg::OnBnClickedReset()
{
	m_lista.ResetContent(); //limpiar lista
}
