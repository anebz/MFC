
// ex2Dlg.h : header file
//

#pragma once
#include "Deposito.h"
#include "afxwin.h"

// Cex2Dlg dialog
class Cex2Dlg : public CDialogEx
{
// Construction
public:
	Cex2Dlg(CWnd* pParent = NULL);	// standard constructor
	CDeposito d[2];
	CWinThread *pC, *pD; //para recibir los objetos de los hilos a crear

// Dialog Data
	enum { IDD = IDD_EX2_DIALOG };

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
	int m_cap1;
	int m_cap2;
	int m_cp[2];
	int cap[2];
	int m_carga;
	int m_descarga;
	afx_msg void OnBnClickedCarg();
	afx_msg LRESULT OnFinHilo(WPARAM wParam, LPARAM lParam); //para mensajes
	afx_msg void OnBnClickedDescarg();
//	CStatic m_dep;
	CListBox m_lista;
	afx_msg void OnBnClickedButton1();
	void Actualizar(int litros1, int litros2);
	CString m_dep1;
	CString m_dep2;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
