#pragma once

// CSockServidor command target
class CUDPServAudioDlg; // para evitar recursividades de clases

class CSockServidor : public CSocket
{
public:
	CSockServidor(CUDPServAudioDlg* p);
	CUDPServAudioDlg* pDlg;
	bool play;

	virtual ~CSockServidor();
	virtual void OnReceive(int nErrorCode);
};


