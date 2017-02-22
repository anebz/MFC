
// InasensDlg.h : header file
//

#pragma once
#include "afxwin.h"


// CInasensDlg dialog
class CInasensDlg : public CDialogEx
{
// Construction
public:
	CInasensDlg(CWnd* pParent = NULL);	// standard constructor
	CWinThread* Nodos[99]; // 99:max nodes accepted
	bool msg[99];
	int n_msg;

// Dialog Data
	enum { IDD = IDD_INASENS_DIALOG };

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
	afx_msg LRESULT OnBroadcast(WPARAM wParam, LPARAM lParam); //para mensajes
public:
	afx_msg void OnBnClickedCancel();
	CListBox m_lista;
	int m_numnodes;
	int m_emission_node;
	afx_msg void OnBnClickedSend();
	afx_msg void OnBnClickedClear();
};
