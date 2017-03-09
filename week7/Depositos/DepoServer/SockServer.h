#pragma once

// CSockServer command target

class CDepoServerDlg;

class CSockServer : public CSocket
{
public:
	CSockServer(CDepoServerDlg*);
	CDepoServerDlg *pDlg; // objeto del dialogo

	virtual ~CSockServer();
	virtual void OnReceive(int nErrorCode);
};


