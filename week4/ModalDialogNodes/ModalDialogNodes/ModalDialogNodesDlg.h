
// ModalDialogNodesDlg.h : header file
//

#pragma once
#include "Node.h"
#include "afxwin.h"

// CModalDialogNodesDlg dialog
class CModalDialogNodesDlg : public CDialogEx
{
// Construction
public:
	CModalDialogNodesDlg(CWnd* pParent = NULL);	// standard constructor
	CNode n1;

// Dialog Data
	enum { IDD = IDD_MODALDIALOGNODES_DIALOG };

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
	afx_msg void OnBnClickedAdd();

	struct Node{
		int id, x, y;
	}data[100];
	int nNodos;
	CStatic m_figura;
};
