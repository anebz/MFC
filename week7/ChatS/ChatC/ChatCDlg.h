
// ChatCDlg.h : header file
//

#pragma once
#include "afxwin.h"


// CChatCDlg dialog
class CChatCDlg : public CDialogEx
{
// Construction
public:
	CChatCDlg(CWnd* pParent = NULL);	// standard constructor
	CSocket misoc;

// Dialog Data
	enum { IDD = IDD_CHATC_DIALOG };

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
	CString m_send;
	afx_msg void OnBnClickedConnect();
	afx_msg void OnBnClickedCsend();
	CString m_user;
};
