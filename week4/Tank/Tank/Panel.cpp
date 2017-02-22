// Panel.cpp : implementation file
//

#include "stdafx.h"
#include "Tank.h"
#include "Panel.h"


// CPanel

IMPLEMENT_DYNAMIC(CPanel, CWnd)

CPanel::CPanel()
{
	h = 0;
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
	CRect r;
	GetClientRect(r);
	r.top -= r.top * (double)h/100;;
	dc.FillSolidRect(r,RGB(0,100,255));
	GetClientRect(r);

	r.bottom -= r.bottom * (double)h/100;;
	dc.FillSolidRect(r,RGB(255,255,255));


	// Do not call CWnd::OnPaint() for painting messages
}
