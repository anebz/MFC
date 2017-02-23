
// LinkNodesDlg.h : header file
//

#pragma once
#include "Node.h"
#include "afxwin.h"

#define MAXNODES 100

// CLinkNodesDlg dialog
class CLinkNodesDlg : public CDialogEx
{
// Construction
public:
	CLinkNodesDlg(CWnd* pParent = NULL);	// standard constructor

	int nodes[2][MAXNODES];
	int nNodes;
	double dist[MAXNODES];

// Dialog Data
	enum { IDD = IDD_LINKNODES_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedAdd();
	CStatic m_graph;
};
