
// LinkNodesDlg.cpp : implementation file
//

#include "stdafx.h"
#include "LinkNodes.h"
#include "LinkNodesDlg.h"
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


// CLinkNodesDlg dialog



CLinkNodesDlg::CLinkNodesDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLinkNodesDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLinkNodesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PIC, m_graph);
}

BEGIN_MESSAGE_MAP(CLinkNodesDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_ADD, &CLinkNodesDlg::OnBnClickedAdd)
END_MESSAGE_MAP()


// CLinkNodesDlg message handlers

BOOL CLinkNodesDlg::OnInitDialog()
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
	nNodes = 0;

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CLinkNodesDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CLinkNodesDlg::OnPaint()
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

		CDC *p = m_graph.GetDC();
		CRect r;
		m_graph.GetClientRect(r);
		p->FillSolidRect(r,RGB(255,255,255));
		for(size_t i = 0; i<nNodes; i++){
			if(nodes[0][i] >= r.left && nodes[0][i] <= r.right && nodes[1][i] >= r.top && nodes[1][i] <= r.bottom)
				p->Ellipse(nodes[0][i]-10, nodes[1][i]-10, nodes[0][i]+10,nodes[1][i]+10);
			else AfxMessageBox("Dimensions have been exceeded");
			
		}
		for(size_t i=0; i<nNodes; i++){
			std::fill_n(dist, MAXNODES, 0); // initialize to zero
			double mindist = 999;
			std::vector<unsigned int> mindposs;
			for(int j=0; j<nNodes; j++){
				if(i != j) dist[j] = sqrt(pow(nodes[0][i] - nodes[0][j],2) + pow(nodes[1][i] - nodes[1][j],2)); // square distance
				else dist[j] = 999;// random value
				if(dist[j] <= mindist){
					if(dist[j] < mindist) mindposs.clear(); // clear all values because now we have a new minimum
					mindist = dist[j];
					mindposs.push_back(j);
				}
			}
			for(unsigned int &k: mindposs){
				if(nodes[0][i] >= r.left + 10 && nodes[0][i] <= r.right - 10 && nodes[1][i] >= r.top + 10 && nodes[1][i] <= r.bottom - 10
				&& nodes[0][k] >= r.left + 10 && nodes[0][k] <= r.right - 10 && nodes[1][k] >= r.top + 10 && nodes[1][k] <= r.bottom - 10){
					int dx = -1, dy = -1;
					if(nodes[0][i] < nodes[0][k]) dx = 1;
					if(nodes[1][i] < nodes[1][k]) dy = 1;
					if(nodes[0][i] == nodes[0][k]) dx = 0;
					if(nodes[1][i] == nodes[1][k]) dy = 0;
					p->MoveTo(nodes[0][i] + dx*8,nodes[1][i] + dy*8);  // draw lines to link nodes
					p->LineTo(nodes[0][k] - dx*8,nodes[1][k] - dy*8);
				}
			}
		}
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CLinkNodesDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CLinkNodesDlg::OnBnClickedAdd()
{
	CNode node;
	if(node.DoModal()==IDOK){
		int diff = 0;
		for(size_t i = 0; i<nNodes; i++){
			if(node.m_x != nodes[0][i] || node.m_y != nodes[1][i]){
				diff++;
			}
		}
		if(diff == nNodes){
			nodes[0][nNodes] = node.m_x;
			nodes[1][nNodes] = node.m_y;
			nNodes++;
			this->Invalidate();
		}
	}
}
