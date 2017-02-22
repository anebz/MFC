
// robocopDlg.h : header file
//

#pragma once
#include "afxwin.h"


// CrobocopDlg dialog
class CrobocopDlg : public CDialogEx
{
// Construction
public:
	CrobocopDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_ROBOCOP_DIALOG };

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
	afx_msg void OnLbnSelchangeList1();
	afx_msg void OnBnClickedExit();
	int m_num;
	CListBox m_lista;
	afx_msg void OnBnClickedStart();
	afx_msg void OnBnClickedReset();
};
