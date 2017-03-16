
// ex1MDlg.h : header file
//

#pragma once


// Cex1MDlg dialog
class Cex1MDlg : public CDialogEx
{
// Construction
public:
	Cex1MDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_EX1M_DIALOG };

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
	afx_msg void OnBnClickedStart();
	int m_sl1;
	int m_sl2;
	int m_msg;
	afx_msg void OnNMReleasedcaptureSl1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMReleasedcaptureSl2(NMHDR *pNMHDR, LRESULT *pResult);
};
