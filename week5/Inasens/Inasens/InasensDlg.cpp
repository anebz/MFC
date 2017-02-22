
// InasensDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Inasens.h"
#include "InasensDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define WM_FIN_HILO WM_USER+100

int maxnumnode = 0;

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


// CInasensDlg dialog



CInasensDlg::CInasensDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CInasensDlg::IDD, pParent)
	, m_numnodes(0)
	, m_emission_node(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CInasensDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LISTA, m_lista);
	DDX_Text(pDX, IDC_NUM, m_numnodes);
	DDX_Text(pDX, IDC_EMIT, m_emission_node);
}

BEGIN_MESSAGE_MAP(CInasensDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDCANCEL, &CInasensDlg::OnBnClickedCancel)
	ON_MESSAGE (WM_FIN_HILO, OnBroadcast)
	ON_BN_CLICKED(IDC_SEND, &CInasensDlg::OnBnClickedSend)
	ON_BN_CLICKED(IDC_CLEAR, &CInasensDlg::OnBnClickedClear)
END_MESSAGE_MAP()


// CInasensDlg message handlers
UINT Thread(LPVOID pParam)
{
	CInasensDlg *pDlg = (CInasensDlg*)pParam;
	CString cs;
	while(1){
		for(size_t i = 0; i<pDlg->m_numnodes; i++){ // recorrer todos los nodos para ver si alguno ha enviado un mensaje
			if(pDlg->msg[i]){ // if message has been sent
				pDlg->PostMessage(WM_FIN_HILO,i);
				break;
			}
		}
	}
	return 0;
}

BOOL CInasensDlg::OnInitDialog()
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

void CInasensDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CInasensDlg::OnPaint()
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
HCURSOR CInasensDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CInasensDlg::OnBnClickedClear()
{
	m_lista.ResetContent();
}

void CInasensDlg::OnBnClickedCancel()
{
	CInasensDlg::OnOK();
}

LRESULT CInasensDlg::OnBroadcast(WPARAM wParam, LPARAM lParam) //Mensajes
{
	n_msg++; // aumenta el # de threads que entra en la funcion
	if(n_msg == m_numnodes){ // todos los threads/nodos han entrado en la función
		
		// obtener los numeros de los nodos ordenados en modo random
		std::vector<int> nodenums(m_numnodes);
		for(size_t i = 0; i < m_numnodes; ++i)
			nodenums[i] = i+1;
		std::random_shuffle(std::begin(nodenums), std::end(nodenums));

		CString cs;
		for(size_t i = 0; i<m_numnodes; i++){
			if(nodenums[i] != wParam + 1){ // que no escriba que "nodo 1 ha recibido mensaje de nodo 1"
				cs.Format("Nodo %d: 'mensaje de nodo %d recibido!'",nodenums[i],wParam+1);
				m_lista.AddString(cs);
			}
		}

		msg[wParam] = false; // la señal mandada se desactiva
		cs.Format(""); // newline
		m_lista.AddString(cs);
	}
	return 0;
}

void CInasensDlg::OnBnClickedSend()
{
	UpdateData(1); // recibir info de variables

	// se ha escrito cuántos nodos existen, creamos los threads ahora.
	// solo se hace al principio o cuando el usuario cambia el # de nodos totales
	if(m_numnodes != 0){ 

		if(m_numnodes < 2 || m_numnodes > 99){
			AfxMessageBox("# nodes must be between [2,99]");
			return;
		}

		std::fill(msg, msg + m_numnodes, false); // inicializar todos los mensajes a 0

		if(m_numnodes > maxnumnode){ // si ahora tenemos más nodos que antes, hay que empezarlos
			for(size_t i = maxnumnode; i<= maxnumnode + (m_numnodes-maxnumnode); i++){ // comenzar threads nuevos
				Nodos[i] = AfxBeginThread(Thread, this);
			}
		}
		else{ // si en cambio tenemos menos nodos que antes, los suspendemos para que no estén corriendo cuando no son necesarios
			for(size_t i = m_numnodes; i<= m_numnodes + (maxnumnode - m_numnodes); i++){
				Nodos[i]->SuspendThread();
			}
		}
		maxnumnode = m_numnodes; // maxnumnode = el # de nodos activos en este momento
	}

	if(m_emission_node > m_numnodes) AfxMessageBox("ERROR: node number can't exceed the number of nodes");

	n_msg = 0; // mensajes recibidos = 0
	msg[m_emission_node-1] = true; // mensaje del nodo m_emission_node ha sido enviado

}