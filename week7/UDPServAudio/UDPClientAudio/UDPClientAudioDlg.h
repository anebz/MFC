
// UDPClientAudioDlg.h : header file
//

#pragma once


// CUDPClientAudioDlg dialog
class CUDPClientAudioDlg : public CDialogEx
{
// Construction
public:
	CUDPClientAudioDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_UDPCLIENTAUDIO_DIALOG };

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
	CString m_ip;
	int m_port;
	afx_msg void OnBnClickedPlay();
	afx_msg void OnBnClickedPausea();
};
