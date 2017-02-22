
// oscillatorDlg.h : header file
//

#pragma once
#include "afxwin.h"


// CoscillatorDlg dialog
class CoscillatorDlg : public CDialogEx
{
// Construction
public:
	CoscillatorDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_OSCILLATOR_DIALOG };

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
	bool start;
	int dt;
	int x1, x2, y1, y2;

	int m_ampl;
	int m_freq;
	CString m_width;
	CStatic m_osc;
	afx_msg void OnBnClickedBtn();
	void Paint();
	void EmpezarTimer();
	void AcabarTimer();
	void OnTimer(UINT nID);
};
