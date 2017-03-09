// SockServer.cpp : implementation file
//

#include "stdafx.h"
#include "DepoServer.h"
#include "SockServer.h"
#include "DepoServerDlg.h" // INCLUDEEEE


// CSockServer

CSockServer::CSockServer(CDepoServerDlg* p)
{
	pDlg = p;
}

CSockServer::~CSockServer()
{
}


// CSockServer member functions

// UDP
void CSockServer::OnReceive(int nErrorCode)
{
	char buf[1];
	CString addr,cs;
	UINT port;

	//Recibe Mensaje
	int len = ReceiveFrom(buf,1,addr,port);
	// receivefrom: info, length, IP, PORT
	pDlg->m_port = port;
	
	pDlg->UpdateData(1);
	
	if(buf[0] == '1') pDlg->m_tim.Format("ON");
	else if(buf[0] == '0') pDlg->m_tim.Format("OFF");

	pDlg->m_msg.Format("deposito1: %d, deposito2: %d", pDlg->m_sl1, pDlg->m_sl2);
	pDlg->UpdateData(0);

	CString ip;
	cs.Format("%d", pDlg->m_sl1);
	ip.Format("127.0.0.1");
	SendTo(cs, cs.GetLength(), pDlg->m_port, ip); 
}
