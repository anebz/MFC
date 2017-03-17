
// ChatSDlg.h : header file
//

#pragma once
#include "SSocket.h"
#include "afxwin.h"

// CChatSDlg dialog
class CChatSDlg : public CDialogEx
{
// Construction
public:
	CChatSDlg(CWnd* pParent = NULL);	// standard constructor
	CSSocket* misoc;

// Dialog Data
	enum { IDD = IDD_CHATS_DIALOG };

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
	afx_msg void OnBnClickedSstart();
	afx_msg void OnBnClickedSstop();
	afx_msg void OnBnClickedSsend();
	CListBox m_lista;
	CString m_data;
};
