#pragma once


// CLuz

class CLuz : public CWnd
{
	DECLARE_DYNAMIC(CLuz)

public:
	CLuz();
	virtual ~CLuz();
	int color;

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
};


