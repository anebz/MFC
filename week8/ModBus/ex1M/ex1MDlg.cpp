
// ex1MDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ex1M.h"
#include "ex1MDlg.h"
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


// Cex1MDlg dialog



Cex1MDlg::Cex1MDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Cex1MDlg::IDD, pParent)
	, m_sl1(0)
	, m_sl2(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cex1MDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Slider(pDX, IDC_SL1, m_sl1);
	DDV_MinMaxInt(pDX, m_sl1, 0, 100);
	DDX_Slider(pDX, IDC_SL2, m_sl2);
	DDV_MinMaxInt(pDX, m_sl2, 0, 100);
}

BEGIN_MESSAGE_MAP(Cex1MDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_START, &Cex1MDlg::OnBnClickedStart)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SL1, &Cex1MDlg::OnNMReleasedcaptureSl1)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SL2, &Cex1MDlg::OnNMReleasedcaptureSl2)
END_MESSAGE_MAP()


// Cex1MDlg message handlers

BOOL Cex1MDlg::OnInitDialog()
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
	m_msg = 1;

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void Cex1MDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void Cex1MDlg::OnPaint()
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
HCURSOR Cex1MDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void Cex1MDlg::OnBnClickedStart()
{

}


void Cex1MDlg::OnNMReleasedcaptureSl1(NMHDR *pNMHDR, LRESULT *pResult)
{
	UpdateData(1);
	CSocket misoc;
	if(!misoc.Create()){ 
		MessageBox("Error"); return;
	}
	if(!misoc.Connect("127.0.0.1", 502)){
		MessageBox("No conecta.."); return;
	}	
	unsigned char Bus[20];
	unsigned char rec_buf[20];
	
	// Transaction identifier
	Bus[0] = m_msg >> 8; // MSB
	Bus[1] = m_msg & 0xFF; // LSB

	Bus[2] = 0x00; // Protocol Identifier
	Bus[3] = 0x00;	

	// ID slave
	Bus[6] = 21 & 0XFF; // 21 < 255 --> solo un byte

	// function code (write)
	Bus[7] = 0x06; // = 6 (dec)

	// Data address
	short Trans = 300;
	Bus[8] = Trans >> 8;
	Bus[9] = Trans & 0xFF;

	// value = 0x1F4 == 500
	short value = m_sl1;
	Bus[10] = value*10 >> 8;
	Bus[11] = value*10 & 0xFF;

	// meessage length
	short length = 12;
	Bus[4] = length - 1 - 5 >> 8;
	Bus[5] = length - 1 - 5 & 0xFF;


	misoc.Send(Bus, 20);

	if(Bus[7] == 0x06){ // en caso de write
		int len = misoc.Receive(rec_buf,20); 
		if(memcmp(Bus, rec_buf, 12) != 0){ // si chars received son diferentse a char sent
			MessageBox("Error en la comunicacion"); return;
		}
	}

	misoc.Close(); 
	m_msg++;

	*pResult = 0;
}


void Cex1MDlg::OnNMReleasedcaptureSl2(NMHDR *pNMHDR, LRESULT *pResult)
{
	UpdateData(1);
	CSocket misoc;
	if(!misoc.Create()){ 
		MessageBox("Error"); return;
	}
	if(!misoc.Connect("127.0.0.1", 502)){
		MessageBox("No conecta.."); return;
	}	
	unsigned char Bus[20];
	unsigned char rec_buf[20];
	
	// Transaction identifier
	Bus[0] = m_msg >> 8; // MSB
	Bus[1] = m_msg & 0xFF; // LSB

	Bus[2] = 0x00; // Protocol Identifier
	Bus[3] = 0x00;	

	// ID slave
	Bus[6] = 21 & 0XFF; // 21 < 255 --> solo un byte

	// function code (write)
	Bus[7] = 0x06; // = 6 (dec)

	// Data address
	short Trans = 301;
	Bus[8] = Trans >> 8;
	Bus[9] = Trans & 0xFF;

	// value = 0x1F4 == 500
	short value = m_sl2;
	Bus[10] = value*10 >> 8;
	Bus[11] = value*10 & 0xFF;

	// meessage length
	short length = 12;
	Bus[4] = length - 1 - 5 >> 8;
	Bus[5] = length - 1 - 5 & 0xFF;


	misoc.Send(Bus, 20);

	if(Bus[7] == 0x06){ // en caso de write
		int len = misoc.Receive(rec_buf,20); 
		if(memcmp(Bus, rec_buf, 12) != 0){ // si chars received son diferentse a char sent
			MessageBox("Error en la comunicacion"); return;
		}
	}

	misoc.Close(); 
	m_msg++;

	*pResult = 0;
}
