// MySocket.cpp : implementation file
//

#include "stdafx.h"
#include "ServidorTCP.h"
#include "MySocket.h"
#include "ServidorTCPDlg.h"


// CMySocket

CMySocket::CMySocket(CServidorTCPDlg *p)
{
	pDlg = p;
}

CMySocket::~CMySocket()
{
}


// CMySocket member functions


void CMySocket::OnAccept(int nErrorCode)
{
	char buf[50];
	static int num = 0;
	CSocket cliente;
	Accept(cliente);
	while(1){
		int len = cliente.Receive(buf,50);
		buf[len] = 0;
		if (len == 0 || len == -1) break;
		pDlg->m_lista.AddString(buf);
		sprintf(buf,"ACK: %d",num++);
		cliente.Send(buf,strlen(buf));
		pDlg->m_lista.AddString(buf);
	}
	pDlg->UpdateData(0);
	cliente.Close();
}
