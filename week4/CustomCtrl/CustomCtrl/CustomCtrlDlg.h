
// CustomCtrlDlg.h : header file
//

#pragma once
#include "Panel.h"

// CCustomCtrlDlg dialog
class CCustomCtrlDlg : public CDialogEx
{
// Construction
public:
	CCustomCtrlDlg(CWnd* pParent = NULL);	// standard constructor
	CPanel p1;

// Dialog Data
	enum { IDD = IDD_CUSTOMCTRL_DIALOG };

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
//	afx_msg void OnStnClickedPanel1();
	int m_color;
	int m_slider;
	CString m_valor;
//	afx_msg void OnNMReleasedcaptureSlider1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnClickedColor1();
	afx_msg void OnBnClickedColor2();
	afx_msg void OnCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult);
};
