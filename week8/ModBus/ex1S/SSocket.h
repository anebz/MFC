#pragma once

// CSSocket command target
class Cex1SDlg;

class CSSocket : public CSocket
{
public:
	CSSocket(Cex1SDlg*);
	Cex1SDlg* pDlg;
	int id;

	virtual ~CSSocket();
	virtual void OnAccept(int nErrorCode);
};


