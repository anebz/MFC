#pragma once


// CPanel

class CPanel : public CWnd
{
	DECLARE_DYNAMIC(CPanel)

public:
	CPanel();
	int h;
	virtual ~CPanel();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
};


