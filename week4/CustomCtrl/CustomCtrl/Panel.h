#pragma once


// CPanel

class CPanel : public CWnd
{
	DECLARE_DYNAMIC(CPanel)

public:
	CPanel();
	virtual ~CPanel();

	int color, angulo;

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
};


