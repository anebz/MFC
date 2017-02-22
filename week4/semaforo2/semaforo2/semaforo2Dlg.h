
// semaforo2Dlg.h : header file
//

#pragma once
#include "Luz.h"

// Csemaforo2Dlg dialog
class Csemaforo2Dlg : public CDialogEx
{
// Construction
public:
	Csemaforo2Dlg(CWnd* pParent = NULL);	// standard constructor
	CLuz red, yellow, green; // 3 variables tipo CLuz que van a pintar el color dependiendo de la variable local 'color'
	int mode; // modo en el que estamos, si en modo rojo, verde, ...

// Dialog Data
	enum { IDD = IDD_SEMAFORO2_DIALOG };

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
	afx_msg void OnTimer(UINT_PTR nIDEvent); // funcion de ontimer
	afx_msg void OnBnClickedStart(); // funcion a la que entra cuando se clicka en el boton
};
