
// ex1Dlg.h : header file
//

#pragma once
#include "afxwin.h"


// Cex1Dlg dialog
class Cex1Dlg : public CDialogEx
{
// Construction
public:
	Cex1Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_EX1_DIALOG };

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
	int m_altura;
	int m_vel;
	double m_ang;
	double dt, x, y;
	double maxy, maxx;
	std::vector<std::pair<double, double>> pos;
	afx_msg void OnBnClickedStart();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CStatic m_panel;
	CListBox m_list;
	afx_msg void OnBnClickedClear();
	CString m_area;
	CString m_bola;
};
