// Panel.cpp : implementation file
//

#include "stdafx.h"
#include "CustomCtrl.h"
#include "Panel.h"
#include <math.h>


// CPanel

IMPLEMENT_DYNAMIC(CPanel, CWnd)

CPanel::CPanel()
{
	color = 0;
	angulo = 0;
}

CPanel::~CPanel()
{
}


BEGIN_MESSAGE_MAP(CPanel, CWnd)
	ON_WM_PAINT()
END_MESSAGE_MAP()



// CPanel message handlers




void CPanel::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	int x, y, rd;
	CRect r;
	GetClientRect(r);
	CBrush b1;
	if(!color) b1.CreateSolidBrush(RGB(255,255,0)); // yellow
	else b1.CreateSolidBrush(RGB(50,150,255)); // blue
	dc.SelectObject(&b1);
	dc.Ellipse(r);
	CPoint pt = r.CenterPoint(); // punto medio
	dc.MoveTo(pt.x, pt.y); // centro

	// calcular punto con angulo
	rd = pt.x < pt.y ? pt.x : pt.y; // devuelve el menor num
	x = (int)(rd*sin(angulo*3.141592/180));
	y = (int)(rd*cos(angulo*3.141592/180));
	dc.LineTo(pt.x + x, pt.y - y);

	// Do not call CWnd::OnPaint() for painting messages
}
