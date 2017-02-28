// Deposito.cpp : implementation file
//

#include "stdafx.h"
#include "ex2.h"
#include "Deposito.h"


// CDeposito

IMPLEMENT_DYNAMIC(CDeposito, CWnd)

CDeposito::CDeposito()
{
	initial_y = 0;
	m_capmax = 0;
	m_litros = 0;
	descarga = false;
}

CDeposito::~CDeposito()
{
}


BEGIN_MESSAGE_MAP(CDeposito, CWnd)
	ON_WM_PAINT()
END_MESSAGE_MAP()



// CDeposito message handlers




void CDeposito::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	CRect r;
	GetClientRect(r); //obtener el area cliente
	CDC *pDC = GetDC(); //obtener el DC del cliente

	dim_pict = r.bottom - r.top;

	initial_y *= (double)(r.bottom - r.top); // ajustar a las dimensiones del Picture Control

	CBrush b1;
	b1.CreateSolidBrush(RGB(0,0,255)); // azul

	if(descarga){
		CBrush b1;
		b1.CreateSolidBrush(RGB(255,255,255)); // blanco
		pDC->FillRect(r,&b1);
	}

	if(initial_y == 0){
		r.top = r.bottom - m_litros;
	}
	else{
		m_litros = initial_y;
		r.top = r.bottom - initial_y;
		initial_y = 0;
	}

	if(r.top > r.bottom){
		return;
	}

	pDC->FillRect(r,&b1);
	// Do not call CWnd::OnPaint() for painting messages
}
