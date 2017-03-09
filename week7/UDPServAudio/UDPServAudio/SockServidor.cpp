// SockServidor.cpp : implementation file
//

#include "stdafx.h"
#include "UDPServAudio.h"
#include "SockServidor.h"

#include "UDPServAudioDlg.h"

// CSockServidor

CSockServidor::CSockServidor(CUDPServAudioDlg* p)
{
	pDlg = p;
	play = false;
}

CSockServidor::~CSockServidor()
{
	// work of the nothing
}


// CSockServidor member functions

void CSockServidor::OnReceive(int nErrorCode)
{
	char buf[50];
	CString addr;
	UINT port;
	//Recibe Mensaje
	int len = ReceiveFrom(buf,50,addr,port);
	//buf[len] = 0;
	if(buf[0] == '1'){ // play
		play = true;
		pDlg->SetTimer(1, 750, NULL); // empezar timer
		pDlg->tim = true;
		SendTo("1", 1, port, addr); //enviar ACK
	}
	else if(buf[0] == '0'){ // stop
		play = false;
		pDlg->KillTimer(1);
		pDlg->tim = false;
		SendTo("0", 1, port, addr); //enviar ACK
	}
}
