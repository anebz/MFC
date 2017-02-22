
// sinDlg.h : header file
//

#pragma once
#include "afxwin.h"


// CsinDlg dialog
class CsinDlg : public CDialogEx
{
// Construction
public:
	CsinDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_SIN_DIALOG };

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
	int m_ciclos;
	afx_msg void OnEnChangeCiclos();
	int m_ampl;
	int m_ptos;
	CStatic m_grafica;
	afx_msg void OnBnClickedOk();
	void OnOK();
};
