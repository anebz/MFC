
// ClienteUDPDlg.h : header file
//

#pragma once


// CClienteUDPDlg dialog
class CClienteUDPDlg : public CDialogEx
{
// Construction
public:
	CClienteUDPDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_CLIENTEUDP_DIALOG };

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
	int m_port;
	CString m_ip;
	CString m_tx;
	CString m_rx;
	afx_msg void OnBnClickedEnviar();
};
