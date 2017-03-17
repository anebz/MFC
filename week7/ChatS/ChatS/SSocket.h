#pragma once

// CSSocket command target

class CChatSDlg;

class CSSocket : public CSocket
{
public:
	CSSocket(CChatSDlg*);
	CChatSDlg* pDlg;

	virtual ~CSSocket();
	virtual void OnAccept(int nErrorCode);
};


