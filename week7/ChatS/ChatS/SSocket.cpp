// SSocket.cpp : implementation file
//

#include "stdafx.h"
#include "ChatS.h"
#include "SSocket.h"
#include "ChatSDlg.h"

// CSSocket

CSSocket::CSSocket(CChatSDlg* p)
{
	pDlg = p;
}

CSSocket::~CSSocket()
{
}


// CSSocket member functions


void CSSocket::OnAccept(int nErrorCode)
{
	char buf[50];
	static int num = 0;
	CSocket cliente; // create socket, port??
	Accept(cliente); // Accept for TCP
	while(1){ // loop until we stop receiving
		int len = cliente.Receive(buf,50); // receive from alle
		buf[len] = 0;
		if (len == 0 || len == -1) break;
		pDlg->m_lista.AddString(buf);
		CString cs = "received!";
		cliente.Send(cs,strlen(cs)); // send to alle
	}
	pDlg->UpdateData(0);
	cliente.Close();

	CSocket::OnAccept(nErrorCode);
}
