
// RoboRaceDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RoboRace.h"
#include "RoboRaceDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

int Fin = 0, Susp = 0; // Variables globales para comunicar
int it1 = 0, it2 = 0;
#define WM_FIN_HILO WM_USER+100

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


// CRoboRaceDlg dialog



CRoboRaceDlg::CRoboRaceDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CRoboRaceDlg::IDD, pParent)
	, m_vueltas(0)
	, m_longitud(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRoboRaceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_VUELTAS, m_vueltas);
	DDX_Text(pDX, IDC_LONGITUD, m_longitud);
	DDX_Control(pDX, IDC_SANDIA, m_sandia);
	DDX_Control(pDX, IDC_MARRUBI, m_marrubi);
	DDX_Control(pDX, IDC_PAUSA, m_pause);
	DDX_Control(pDX, IDC_STOP, m_stop);
	DDX_Control(pDX, IDC_START, m_play);
}

BEGIN_MESSAGE_MAP(CRoboRaceDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_EXIT, &CRoboRaceDlg::OnBnClickedExit)
	ON_MESSAGE (WM_FIN_HILO, OnFinHilo)
	ON_BN_CLICKED(IDC_START, &CRoboRaceDlg::OnBnClickedStart)
	ON_BN_CLICKED(IDC_STOP, &CRoboRaceDlg::OnBnClickedStop)
	ON_BN_CLICKED(IDC_PAUSA, &CRoboRaceDlg::OnBnClickedPausa)
	ON_BN_CLICKED(IDC_PENALISE, &CRoboRaceDlg::OnBnClickedPenalise)
END_MESSAGE_MAP()


// CRoboRaceDlg message handlers

BOOL CRoboRaceDlg::OnInitDialog()
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
	m_pause.EnableWindow(FALSE);
	m_stop.EnableWindow(FALSE);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CRoboRaceDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CRoboRaceDlg::OnPaint()
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
HCURSOR CRoboRaceDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CRoboRaceDlg::OnBnClickedExit()
{
	CRoboRaceDlg::OnOK();
}

LRESULT CRoboRaceDlg::OnFinHilo(WPARAM wParam, LPARAM lParam) //Mensajes
{
	Fin = 1;
	if(wParam == 1)
		MessageBox("Ekipo marrubi txapeldun, ekipo sandia ha muerto");
	
	else if (wParam == 2)
		MessageBox("Ekipo sandia txapeldun, ekipo marrubi ha muerto");
	return 0;
}

UINT SandiatHilo(LPVOID pParam) //Hilo 1 (Ferrari)
{
	srand(time(NULL)); //Cambiar la semilla de inicio
	int t = rand()%25;
	CRoboRaceDlg *pDlg = (CRoboRaceDlg*)pParam;
	int len = pDlg->m_longitud * pDlg->m_vueltas;
	for(it1 = 0; it1<len; it1++){
		pDlg->m_sandia.SetPos(it1*100.0/len);
		Sleep(t);
		if(Fin) break;
	}
	if(!Fin) pDlg->PostMessage(WM_FIN_HILO,1); //Mensaje de Sandia(1)
	return 0;
}

UINT MarrubiHilo(LPVOID pParam) //Hilo 2 (Renault)
{
	//srand(time(NULL)); //Cambiar la semilla de inicio
	int t = rand()%25;
	CRoboRaceDlg *pDlg = (CRoboRaceDlg*)pParam;
	int len = pDlg->m_longitud * pDlg->m_vueltas;
	for(it2 = 0; it2<len; it2++){
		pDlg->m_marrubi.SetPos(it2*100.0/len);
		Sleep(t);
		if(Fin) break;
	}
	if(!Fin) pDlg->PostMessage(WM_FIN_HILO,2); //Mensaje de Marrubi(2)
	return 0;
}

void CRoboRaceDlg::OnBnClickedStart()
{
	UpdateData(1); //actualizar variables
	if(m_vueltas == 0 && m_longitud == 0){
		AfxMessageBox("los parámetros son erróneos");
		return;
	}

	m_pause.EnableWindow(TRUE);
	m_stop.EnableWindow(TRUE);
	if(Susp == 1){
		pS->ResumeThread();
		pM->ResumeThread();
		Susp = 0;
	}else{
		Fin = 0;
		pS = AfxBeginThread(SandiatHilo, this);
		pM = AfxBeginThread(MarrubiHilo, this);
	}
}


void CRoboRaceDlg::OnBnClickedStop()
{
	Fin = 1;
	m_marrubi.SetPos(0);
	m_sandia.SetPos(0);
}


void CRoboRaceDlg::OnBnClickedPausa()
{
	Susp = 1;
	pS->SuspendThread();
	pM->SuspendThread();
}


void CRoboRaceDlg::OnBnClickedPenalise()
{
	int marrubi_pos = m_marrubi.GetPos();
	int sandia_pos = m_sandia.GetPos();
	if(marrubi_pos > sandia_pos) it2 = (sandia_pos - (marrubi_pos - sandia_pos))/(100.0/(m_longitud*m_vueltas));
	if(marrubi_pos < sandia_pos) it1 = (marrubi_pos - (sandia_pos - marrubi_pos))/(100.0/(m_longitud*m_vueltas));
}
