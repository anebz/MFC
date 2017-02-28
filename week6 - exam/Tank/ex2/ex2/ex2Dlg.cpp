
// ex2Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "ex2.h"
#include "ex2Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#define WM_FIN_HILO WM_USER+100
#endif

bool stop = false;
bool carga = true;
bool descarga = true;
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


// Cex2Dlg dialog



Cex2Dlg::Cex2Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Cex2Dlg::IDD, pParent)
	, m_cap1(0)
	, m_cap2(0)
	, m_carga(0)
	, m_descarga(0)
	, m_dep1(_T(""))
	, m_dep2(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cex2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_CAP1, m_cap1);
	DDX_Text(pDX, IDC_CAP2, m_cap2);
	DDX_Text(pDX, IDC_CARGA, m_carga);
	DDX_Text(pDX, IDC_DESCARGA, m_descarga);
	//  DDX_Control(pDX, IDC_D1, m_dep);
	DDX_Control(pDX, IDC_LIST1, m_lista);
	DDX_Text(pDX, IDC_DEP1, m_dep1);
	DDX_Text(pDX, IDC_DEP2, m_dep2);
}

BEGIN_MESSAGE_MAP(Cex2Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CARG, &Cex2Dlg::OnBnClickedCarg)
	ON_MESSAGE (WM_FIN_HILO, OnFinHilo)
	ON_BN_CLICKED(IDC_DESCARG, &Cex2Dlg::OnBnClickedDescarg)
	ON_BN_CLICKED(IDC_BUTTON1, &Cex2Dlg::OnBnClickedButton1)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// Cex2Dlg message handlers

BOOL Cex2Dlg::OnInitDialog()
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
	d[0].SubclassDlgItem(IDC_D1,this);
	d[1].SubclassDlgItem(IDC_D2,this);
	CRect r;
	GetClientRect(r); //obtener el area cliente
	d[0].initial_y = 0.1;// el 10% del deposito lleno
	d[1].initial_y = 0.05; // el 5% del deposito lleno

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void Cex2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void Cex2Dlg::OnPaint()
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
HCURSOR Cex2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

LRESULT Cex2Dlg::OnFinHilo(WPARAM wParam, LPARAM lParam) //Mensajes
{
	if(wParam == 1) m_lista.AddString("El deposito1 ha acabado primero");
	else if (wParam == 2) m_lista.AddString("El deposito2 ha acabado primero");
	stop = true;
	return 0;
}

UINT CargaHilo(LPVOID pParam) 
{
	Cex2Dlg *pDlg = (Cex2Dlg*)pParam;
	while(!stop){
		for(size_t i = 0; i<2; i++){
			pDlg->d[i].m_litros += pDlg->m_carga*pDlg->d[i].dim_pict/pDlg->cap[i]; // ir cargando
			pDlg->d[i].Invalidate(0);
			if(pDlg->d[i].m_litros >= pDlg->m_cp[i]){ // cap maxima alcanzada
				pDlg->PostMessage(WM_FIN_HILO,1); 
				break;
			}
		}
		Sleep(1000);
	}
	return 0;
}

UINT DescargaHilo(LPVOID pParam) 
{
	Cex2Dlg *pDlg = (Cex2Dlg*)pParam;
	while(!stop){
		for(size_t i = 0; i<2; i++){
			pDlg->d[i].descarga = true;
			pDlg->d[i].m_litros -= pDlg->m_descarga*pDlg->d[i].dim_pict/pDlg->cap[i]; // ir cargando
			pDlg->d[i].Invalidate(0);
			if(pDlg->d[i].m_litros < 0){ // cap maxima alcanzada
				pDlg->PostMessage(WM_FIN_HILO,2); 
				break;
			}
		}
		Sleep(1000);
	}
	return 0;
}

void Cex2Dlg::OnBnClickedCarg()
{

	if(carga == false){
		m_lista.AddString("Carga detenida");
		pC->SuspendThread();
		carga = true;
		return;
	}
	UpdateData(1);

	if(m_carga <= 0){
		AfxMessageBox("Velocidad de carga incorecta, por favor inserte otro valor");
		return;
	}

	m_lista.AddString("Carga comenzada");

	if(m_cap1 > m_cap2){
		m_cp[0] = d[0].dim_pict; // maximum size in picture control
		m_cp[1] = m_cap2*d[0].dim_pict/m_cap1;
	}
	else if(m_cap2 > m_cap1){
		m_cp[1] = d[0].dim_pict;
		m_cp[0] = m_cap1*d[0].dim_pict/m_cap2;
	}
	else{
		m_cp[0] = d[0].dim_pict; 
		m_cp[1] = d[0].dim_pict;
	}

	cap[0] = m_cap1;
	cap[1] = m_cap2;

	d[0].m_capmax = m_cap1;
	d[1].m_capmax = m_cap2;
	pC = AfxBeginThread(CargaHilo, this);

	carga = false;
	SetTimer(1,500,NULL);
	return;
}


void Cex2Dlg::OnBnClickedDescarg()
{
	if(descarga == false){
		m_lista.AddString("Descarga detenida");
		pD->SuspendThread();
		descarga = true;
		return;
	}
	
	if(m_descarga <= 0){
		AfxMessageBox("Velocidad de descarga incorecta, por favor inserte otro valor");
		return;
	}

	UpdateData(1);
	m_lista.AddString("Descarga comenzada");
	d[0].descarga = true;
	d[1].descarga = true;

	if(m_cap1 > m_cap2){
		m_cp[0] = d[0].dim_pict; // maximum size in picture control
		m_cp[1] = m_cap2*d[0].dim_pict/m_cap1;
	}
	else if(m_cap2 > m_cap1){
		m_cp[1] = d[0].dim_pict;
		m_cp[0] = m_cap1*d[0].dim_pict/m_cap2;
	}
	else{
		m_cp[0] = d[0].dim_pict; 
		m_cp[1] = d[0].dim_pict;
	}

	cap[0] = m_cap1;
	cap[1] = m_cap2;

	d[0].m_capmax = m_cap1;
	d[1].m_capmax = m_cap2;
	pD = AfxBeginThread(DescargaHilo, this);

	descarga = false;
	SetTimer(1,500,NULL);
	return;
}


void Cex2Dlg::OnBnClickedButton1()
{
	m_lista.ResetContent();
}


void Cex2Dlg::OnTimer(UINT_PTR nIDEvent)
{
	m_dep1.Format("%d",d[0].m_litros);
	m_dep2.Format("%d",d[1].m_litros);
	UpdateData(0);
	d[0].Invalidate();
	d[1].Invalidate();
	CDialogEx::OnTimer(nIDEvent);
}
