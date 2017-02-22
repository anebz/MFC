
// RoboRaceDlg.h : header file
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CRoboRaceDlg dialog
class CRoboRaceDlg : public CDialogEx
{
// Construction
public:
	CRoboRaceDlg(CWnd* pParent = NULL);	// standard constructor

	CWinThread *pS, *pM; //para recibir los objetos de los hilos a crear


// Dialog Data
	enum { IDD = IDD_ROBORACE_DIALOG };

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
	afx_msg LRESULT OnFinHilo(WPARAM wParam, LPARAM lParam); //para mensajes
public:
	int m_vueltas;
	int m_longitud;
	CProgressCtrl m_sandia;
	CProgressCtrl m_marrubi;
	afx_msg void OnBnClickedExit();
	afx_msg void OnBnClickedStart();
	afx_msg void OnBnClickedStop();
	afx_msg void OnBnClickedPausa();
	CButton m_pause;
	CButton m_stop;
	CButton m_play;
	afx_msg void OnNMCustomdrawMarrubi(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedPenalise();
};
