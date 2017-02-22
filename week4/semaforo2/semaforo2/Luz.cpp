// Luz.cpp : implementation file
//

#include "stdafx.h"
#include "semaforo2.h"
#include "Luz.h"


// CLuz

IMPLEMENT_DYNAMIC(CLuz, CWnd)

CLuz::CLuz()
{
}

CLuz::~CLuz()
{
}


BEGIN_MESSAGE_MAP(CLuz, CWnd)
	ON_WM_PAINT()
END_MESSAGE_MAP()



// CLuz message handlers

void CLuz::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	CRect r;
	GetClientRect(r);
	CBrush b1;

	if(color == 0) b1.CreateSolidBrush(RGB(0,0,0)); // black
	else if(color == 1) b1.CreateSolidBrush(RGB(255,0,0)); // red
	else if(color == 2) b1.CreateSolidBrush(RGB(255,255,0)); // yellow
	else if(color == 3) b1.CreateSolidBrush(RGB(0,255,0)); // green

	dc.SelectObject(&b1);
	dc.Ellipse(r);
	// Do not call CWnd::OnPaint() for painting messages
}
