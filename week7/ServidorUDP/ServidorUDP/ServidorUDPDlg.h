
// ServidorUDPDlg.h : header file
//

#pragma once
#include "afxwin.h"

#include "SockServidor.h" // para poder hacer CSockServidor *pSock;

// CServidorUDPDlg dialog
class CServidorUDPDlg : public CDialogEx
{
// Construction
public:
	CServidorUDPDlg(CWnd* pParent = NULL);	// standard constructor
	CSockServidor *pSock;

// Dialog Data
	enum { IDD = IDD_SERVIDORUDP_DIALOG };

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
	afx_msg void OnBnClickedInics();
	afx_msg void OnBnClickedLimpiar();
};
