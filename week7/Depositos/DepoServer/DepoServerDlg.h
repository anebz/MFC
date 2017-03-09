
// DepoServerDlg.h : header file
//

#pragma once
#include "SockServer.h" // clase derivada de CSocket

// CDepoServerDlg dialog
class CDepoServerDlg : public CDialogEx
{
// Construction
public:
	CDepoServerDlg(CWnd* pParent = NULL);	// standard constructor
	CSockServer *sUDP, *sTCP; // objetos socket


// Dialog Data
	enum { IDD = IDD_DEPOSERVER_DIALOG };

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
	int m_sl1, m_sl2;
	afx_msg void OnNMReleasedcaptureSl2(NMHDR *pNMHDR, LRESULT *pResult);
	CString m_tim;
	CString m_msg;	
	UINT m_port;
};
