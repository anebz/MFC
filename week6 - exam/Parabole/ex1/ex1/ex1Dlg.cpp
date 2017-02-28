
// ex1Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "ex1.h"
#include "ex1Dlg.h"
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


// Cex1Dlg dialog



Cex1Dlg::Cex1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Cex1Dlg::IDD, pParent)
	, m_altura(0)
	, m_vel(0)
	, m_ang(0)
	, m_area(_T(""))
	, m_bola(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cex1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ALTURA, m_altura);
	DDX_Text(pDX, IDC_VEL, m_vel);
	DDX_Text(pDX, IDC_ANG, m_ang);
	DDX_Control(pDX, IDC_PANEL, m_panel);
	DDX_Control(pDX, IDC_LISTA, m_list);
	DDX_Text(pDX, IDC_WIDTH, m_area);
	DDX_Text(pDX, IDC_BOLA, m_bola);
}

BEGIN_MESSAGE_MAP(Cex1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_START, &Cex1Dlg::OnBnClickedStart)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_CLEAR, &Cex1Dlg::OnBnClickedClear)
END_MESSAGE_MAP()


// Cex1Dlg message handlers

BOOL Cex1Dlg::OnInitDialog()
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
	dt = 0; // al principio tiempo=0
	x = 0; y = 0;
	maxy = 0; maxx = 0;

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void Cex1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void Cex1Dlg::OnPaint()
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

		// mi código
		CRect rc;
		m_panel.GetClientRect(rc); //obtener el area cliente
		CDC *pDC = m_panel.GetDC(); //obtener el DC del cliente
		CBrush b1;
		//fondo blanco
		b1.CreateSolidBrush(RGB(255,255,255));
		pDC->FillRect(rc,&b1);

		CPen p1(PS_SOLID,1,RGB(0,0,0));
		pDC->SelectObject(&p1);
		for(std::pair<double, double>& it: pos)
			if(it.second > rc.top && it.first < rc.right){
				pDC->Ellipse(it.first-5, it.second-5, it.first+5, it.second+5); // pintar bola
				m_bola.Format("");
			}
			else{
				m_bola.Format("La bola sigue su curso pero ha excedido las dimensiones del Picture Control");
			}
			UpdateData(0);
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR Cex1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void Cex1Dlg::OnBnClickedStart()
{
	UpdateData(1); // obtener valores en las variables
	m_list.ResetContent();

	if(m_vel == 0 || m_ang == 0){
		AfxMessageBox("Valores de vel/ang incorrectos, inserte valores diferentes a 0");
		return;
	}	
	CString cs;
	cs.Format("t=%.2f x=%.2f y=%.2f", 0.00,0.00,(double)m_altura); // f for double
	m_list.AddString(cs);

	SetTimer(1,100,NULL); // empezar timer 100ms
}


void Cex1Dlg::OnTimer(UINT_PTR nIDEvent)
{
	dt += 0.1;
	CRect r;
	m_panel.GetClientRect(r);
	x = -m_vel*cos(m_ang*(double)(180/3.1415))*dt;
	y = m_altura + m_vel*sin(m_ang*(double)(180/3.1415))*dt - 0.5*9.8*pow(dt,2);

	CString cs;
	cs.Format("t=%.2f x=%.2f y=%.2f", dt,x,y); // f for double
	m_list.AddString(cs);
	
	if(y < 0){ // fin del programa
		KillTimer(1);
		if(x > r.right - 5 && x < r.right + 5) cs.Format("Acertado!");
		else cs.Format("La bola ha llegado hasta la posición %d", (int)x);
		AfxMessageBox(cs);
		return;
	}

	if(x > maxx) maxx = x;
	if(y > maxy) maxy = y;
	m_area.Format("Area: W=%d H=%d", (int)maxx, (int)maxy);
	UpdateData(0);

	y = r.bottom - y; // para que aparezca el 0 en el fondo
	pos.push_back(std::make_pair(x,y)); // guardar posiciones

	Invalidate(false); // volver a hacer onpaint pero sin resetear todo el dialog

	CDialogEx::OnTimer(nIDEvent);
}


void Cex1Dlg::OnBnClickedClear()
{
	m_list.ResetContent();
}
