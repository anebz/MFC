// Panel.cpp : implementation file
//

#include "stdafx.h"
#include "Depositos.h"
#include "Panel.h"


// CPanel

IMPLEMENT_DYNAMIC(CPanel, CWnd)

CPanel::CPanel()
{
	height = 0;
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
	CRect r;
	GetClientRect(r);

	r.top -= r.top * (double)height/100;;
	dc.FillSolidRect(r,RGB(0,100,255));

	GetClientRect(r);
	r.bottom -= r.bottom * (double)height/100;
	dc.FillSolidRect(r,RGB(255,255,255));

}
