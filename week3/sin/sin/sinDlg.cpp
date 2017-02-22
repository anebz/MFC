
// sinDlg.cpp : implementation file
//

#include "stdafx.h"
#include "sin.h"
#include "sinDlg.h"
#include "afxdialogex.h"
#include "math.h"

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


// CsinDlg dialog



CsinDlg::CsinDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CsinDlg::IDD, pParent)
	, m_ciclos(0)
	, m_ampl(0)
	, m_ptos(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CsinDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_CICLOS, m_ciclos);
	DDX_Text(pDX, IDC_AMPL, m_ampl);
	DDX_Text(pDX, IDC_PTOS, m_ptos);
	DDX_Control(pDX, IDC_GRAFICA, m_grafica);
}

BEGIN_MESSAGE_MAP(CsinDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_CICLOS, &CsinDlg::OnEnChangeCiclos)
	ON_BN_CLICKED(IDOK, &CsinDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CsinDlg message handlers

BOOL CsinDlg::OnInitDialog()
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

void CsinDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CsinDlg::OnPaint()
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
HCURSOR CsinDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CsinDlg::OnEnChangeCiclos()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void CsinDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CsinDlg::OnOK();
}

void CsinDlg::OnOK(){
	CString cs;
	CRect rc;
	m_grafica.GetClientRect(rc); //obtener el area cliente
	CDC *pDC = m_grafica.GetDC(); //obtener el DC del cliente
	//fondo blanco
	CBrush b1;
	b1.CreateSolidBrush(RGB(255,255,255));
	pDC->FillRect(rc,&b1);
	//eje central color rojo
	CPen p1(PS_SOLID,0,RGB(192,0,0));
	pDC->SelectObject(&p1);
	int h = rc.bottom;
	int w = rc.right;
	int yc = h/2; //el origen del eje y
	pDC->MoveTo(0,yc); pDC->LineTo(rc.right,yc);
	//calculos
	UpdateData(true);
	//cambiar el color a azul
	CPen p2(PS_SOLID,0,RGB(0,0,192));
	pDC->SelectObject(&p2);
	int xt = m_ptos * m_ciclos; //# de puntos a dibujar
	pDC->MoveTo(0,yc); //pto. origen
	for (int i=1;i<=xt;i++) {
		//calculo de fx
		double fx = m_ampl * sin(2*3.14159*i/m_ptos);
		int y = yc - fx * yc /m_ampl ; //conver. escala
		pDC->LineTo(i*w/xt,y);
	}
}