#pragma once

// CSockServer command target

class CDepoServerDlg;

class CSockServer : public CSocket
{
public:
	CSockServer(CDepoServerDlg*);
	CDepoServerDlg *pDlg;
	CSocket soc;

	virtual ~CSockServer();
	virtual void OnReceive(int nErrorCode);
};


