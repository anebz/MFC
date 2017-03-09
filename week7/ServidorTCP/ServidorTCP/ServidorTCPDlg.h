
// ServidorTCPDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "MySocket.h"

// CServidorTCPDlg dialog
class CServidorTCPDlg : public CDialogEx
{
// Construction
public:
	CServidorTCPDlg(CWnd* pParent = NULL);	// standard constructor
	CMySocket *misoc;

// Dialog Data
	enum { IDD = IDD_SERVIDORTCP_DIALOG };

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
	CListBox m_lista;
};
