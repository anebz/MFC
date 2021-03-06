
// DepositosDlg.h : header file
//

#pragma once
#include "SockClient.h"
#include "Panel.h"

// CDepositosDlg dialog
class CDepositosDlg : public CDialogEx
{
// Construction
public:
	CDepositosDlg(CWnd* pParent = NULL);	// standard constructor
	CSockClient *pUDP, *sTCP; // objetos de socket
	CPanel p1, p2; // objetos CPanel para los dos PictureControl

// Dialog Data
	enum { IDD = IDD_DEPOSITOS_DIALOG };

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
	CString m_ip, m_dep1, m_dep2, m_msg;
	int m_port;
	afx_msg void OnBnClickedStop();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
