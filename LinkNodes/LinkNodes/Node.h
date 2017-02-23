#pragma once


// CNode dialog

class CNode : public CDialogEx
{
	DECLARE_DYNAMIC(CNode)

public:
	CNode(CWnd* pParent = NULL);   // standard constructor
	virtual ~CNode();

// Dialog Data
	enum { IDD = IDD_NODE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	int m_x;
	int m_y;
	afx_msg void OnBnClickedOk();
};
