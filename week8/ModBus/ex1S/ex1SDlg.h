
// ex1SDlg.h : header file
//

#pragma once
#include "SSocket.h"
#include "afxcmn.h"

// Cex1SDlg dialog
class Cex1SDlg : public CDialogEx
{
// Construction
public:
	Cex1SDlg(CWnd* pParent = NULL);	// standard constructor

	CSSocket *pSock;

// Dialog Data
	enum { IDD = IDD_EX1S_DIALOG };

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
	afx_msg void OnBnClickedStart();
	CProgressCtrl m_pr1;
	CProgressCtrl m_pr2;
};
