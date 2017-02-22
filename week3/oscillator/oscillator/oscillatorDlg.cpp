
// oscillatorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "oscillator.h"
#include "oscillatorDlg.h"
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


// CoscillatorDlg dialog

CoscillatorDlg::CoscillatorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CoscillatorDlg::IDD, pParent)
	, m_ampl(0)
	, m_freq(0)
	, m_width(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CoscillatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_AMPL, m_ampl);
	DDX_Text(pDX, IDC_FREQ, m_freq);
	DDX_Text(pDX, IDC_WIDTH, m_width);
	DDX_Control(pDX, IDC_PICT, m_osc);
	DDV_MinMaxInt(pDX, m_ampl, 0, INT_MAX);
}

BEGIN_MESSAGE_MAP(CoscillatorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN, &CoscillatorDlg::OnBnClickedBtn)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CoscillatorDlg message handlers

BOOL CoscillatorDlg::OnInitDialog()
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
	start = false;
	dt = 0;
	x1 = 0;
	x2 = 0;
	y1 = 0;
	y2 = 0;

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CoscillatorDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CoscillatorDlg::OnPaint()
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
		CString cs;
		CRect rc;
		m_osc.GetClientRect(rc); //obtener el area cliente
		CDC *pDC = m_osc.GetDC(); //obtener el DC del cliente
		CBrush b1;
		//fondo blanco
		b1.CreateSolidBrush(RGB(255,255,255));
		pDC->FillRect(rc,&b1);

		//Dibujo Ejes
		CPen p1(PS_SOLID,1,RGB(255,0,0));
		pDC->SelectObject(&p1);
		pDC->MoveTo(rc.right/2,0); pDC->LineTo(rc.right/2,rc.bottom);
		pDC->MoveTo(0,rc.bottom/2); pDC->LineTo(rc.right,rc.bottom/2);

		// empezar a pintar paint una vez hayamos pulsado el boton
		// si no, sale el rectángulo cuando iniciemos el dialog
		if(start) Paint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CoscillatorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CoscillatorDlg::OnTimer(UINT nID)
{
	dt++; 
	Invalidate(false); // volver a hacer onpaint pero sin resetear todo el dialog
}

void CoscillatorDlg::EmpezarTimer()
{
	double time = 1/(double)m_freq; // en segundos
	SetTimer(1,time*1000,NULL); // 1:ID, tiempo en milisegundos
}

void CoscillatorDlg::AcabarTimer()
{
	KillTimer(1); //1: matar el timer con el ID = 1
	Invalidate(false); // volver a hacer onpaint pero sin resetear todo el dialog
}

void CoscillatorDlg::Paint()
{
	CRect r;
	m_osc.GetClientRect(r); //obtener el area cliente
	CDC *pDC = m_osc.GetDC(); //obtener el DC del cliente
	x1 = (int)(m_ampl)*cos(2*3.14*dt/m_freq) + r.right/2 - 10; // formula del coseno + r.right/2 para centrarlo en el medio
	x2 = x1 + 20;
	y1 = r.bottom/2 - 20; y2 = y1 + 20; // posiciones verticales

	pDC->Rectangle(x1, y1, x2, y2);

	// linea desde x = 0 hasta el rectangulo
	CPen p2(PS_SOLID,1,RGB(0,0,0)); // color negro
	pDC->SelectObject(&p2);
	pDC->MoveTo(0,r.bottom/2 - 10); 
	pDC->LineTo(x1,r.bottom/2 - 10);
	m_width.Format("width = %.3d", x1);

	UpdateData(0); // pasar info a los controles para que aparezca el width en el dialog
}

void CoscillatorDlg::OnBnClickedBtn()
{
	UpdateData(1); // recibir data de controles
	CRect rc;
	m_osc.GetClientRect(rc); //obtener el area cliente
	if(m_freq == 0 || m_ampl == 0){
		AfxMessageBox("Frecuencia o amplitud incorrecta"); 
		return;
	}
	else if (m_ampl >= rc.right/2 - 10){ // 20 por la longitud del rectangulo
		AfxMessageBox("La amplitud supera los limites de la ventana"); 
		return;
	}
	if(!start){ // opcion start
		CString cs;
		CDC *pDC = m_osc.GetDC(); //obtener el DC del cliente
		CBrush b1;

		//fondo blanco
		b1.CreateSolidBrush(RGB(255,255,255));
		pDC->FillRect(rc,&b1);

		//Dibujo Ejes
		CPen p1(PS_SOLID,1,RGB(255,0,0));
		pDC->SelectObject(&p1);
		pDC->MoveTo(rc.right/2,0); pDC->LineTo(rc.right/2,rc.bottom);
		pDC->MoveTo(0,rc.bottom/2); pDC->LineTo(rc.right,rc.bottom/2);

		EmpezarTimer(); // empezar el movimiento del péndulo
		start = true; // variable para decir que ya estamos en modo start
	}
	else{ // opcion stop
		AcabarTimer();
		start = false;
	}
}