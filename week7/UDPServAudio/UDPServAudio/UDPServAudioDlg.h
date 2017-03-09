
// UDPServAudioDlg.h : header file
//

#pragma once
#include "afxcmn.h"

#include "SockServidor.h"

// CUDPServAudioDlg dialog
class CUDPServAudioDlg : public CDialogEx
{
// Construction
public:
	CUDPServAudioDlg(CWnd* pParent = NULL);	// standard constructor
	CSockServidor *pSock;
	bool tim;

// Dialog Data
	enum { IDD = IDD_UDPSERVAUDIO_DIALOG };

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
	CProgressCtrl m_music;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedToggle();
	int m_port;
};
