// SSocket.cpp : implementation file
//

#include "stdafx.h"
#include "ex1S.h"
#include "SSocket.h"

#include "ex1SDlg.h"

// CSSocket

CSSocket::CSSocket(Cex1SDlg* p)
{
	pDlg = p;
	id = 0x15;
}

CSSocket::~CSSocket()
{
}


// CSSocket member functions


void CSSocket::OnAccept(int nErrorCode)
{
	unsigned char buf[20];
	static int num = 0;
	CSocket cliente;
	Accept(cliente);
	while(1){ 
		int len = cliente.Receive(buf,20);
		if (len == 0 || len == -1) break;

		short length = buf[4]*256 + buf[5];

		if(length != 6){
			pDlg->MessageBox("Faltan datos"); return;		
		}

		if(buf[6] != id){
			pDlg->MessageBox("ID incorrecto"); return;		
		}

		if(buf[7] != 0x06){ // si no es write
			pDlg->MessageBox("La funcion tiene que ser write"); return;		
		}

		short slider = buf[8]*256 + buf[9];

		if(slider == 300){
			pDlg->m_pr1.SetPos((buf[10]*256 + buf[11])/10);
		}
		else if(slider == 301){
			pDlg->m_pr2.SetPos((buf[10]*256 + buf[11])/10);
		}else{
			pDlg->MessageBox("Direccion de slider/progress_bar incorrecto"); return;	
		}
		
		cliente.Send(buf,20); // reenviar solamente si es write

	}
	pDlg->UpdateData(0);
	cliente.Close();
	CSocket::OnAccept(nErrorCode);
}
