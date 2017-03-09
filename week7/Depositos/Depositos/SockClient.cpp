// SockClient.cpp : implementation file
//

#include "stdafx.h"
#include "Depositos.h"
#include "SockClient.h"

#include "DepositosDlg.h"

// CSockClient

CSockClient::CSockClient(CDepositosDlg* p)
{
	pDlg = p;
}

CSockClient::~CSockClient()
{
}


// SockClient member functions


void CSockClient::OnReceive(int nErrorCode)
{
	char buf[50];
	CString addr,cs;
	UINT port;

	//Recibe Mensaje
	int len = ReceiveFrom(buf,50,addr,port);
	// receivefrom: info, length, IP, PORT
	buf[len] = 0; // a partir de la posicion len, todo el array esta a 0

	pDlg->m_dep1 = (CString)buf;
	pDlg->p1.height = atof(buf); // CString to double
	pDlg->p1.Invalidate(1);

	pDlg->m_msg.Format("deposito1: " +  pDlg->m_dep1 + ", deposito2: " + pDlg->m_dep2);

	pDlg->UpdateData(0);
}


void CSockClient::OnAccept(int nErrorCode)
{
	char buf[50];
	static int num = 0;
	CSocket cliente; 
	Accept(cliente); // Accept for TCP
	int len = cliente.Receive(buf,50); 
	buf[len] = 0;

	pDlg->m_dep2 = (CString)buf;
	pDlg->p2.height = atof(buf);
	pDlg->p2.Invalidate(1);
	cliente.Close();

	pDlg->m_msg.Format("deposito1: " +  pDlg->m_dep1 + ", deposito2: " + pDlg->m_dep2);

	pDlg->UpdateData(0);
	CSocket::OnAccept(nErrorCode);
}
