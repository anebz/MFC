
// TankDlg.h : header file
//

#pragma once
#include "Panel.h"

// CTankDlg dialog
class CTankDlg : public CDialogEx
{
// Construction
public:
	CTankDlg(CWnd* pParent = NULL);	// standard constructor
	CPanel p1;

// Dialog Data
	enum { IDD = IDD_TANK_DIALOG };

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
	afx_msg void OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult);
	int sldr;
	int height;
};
