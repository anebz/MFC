#pragma once

// SockClient command target

class CDepositosDlg;

class CSockClient : public CSocket
{
public:
	CSockClient(CDepositosDlg*);
	CDepositosDlg* pDlg; // objeto del dialogo

	virtual ~CSockClient();
	virtual void OnReceive(int nErrorCode);
	virtual void OnAccept(int nErrorCode);
};


