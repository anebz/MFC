
// ClienteTCPDlg.h : header file
//

#pragma once
#include "afxwin.h"


// CClienteTCPDlg dialog
class CClienteTCPDlg : public CDialogEx
{
// Construction
public:
	CClienteTCPDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_CLIENTETCP_DIALOG };

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
	CString m_ip;
	int m_port;
	CListBox m_lista;
	afx_msg void OnBnClickedSend();
	CString m_cmd;
};
