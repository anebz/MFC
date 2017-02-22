#include "rebote.h"
#include <afxwin.h>
#include <math.h>

#define SPEED 10
#define RADIUS 25

CMiApp miObjeto; //crear un objeto global y empieza

								// mi_clase		clase_heredada
BEGIN_MESSAGE_MAP(CMiVentana, CFrameWnd)
	ON_COMMAND(1001, Salir) // tiene que tener el mismo identificador que el boton
	ON_COMMAND(1002, Start)
	ON_WM_MOUSEMOVE()
	ON_WM_TIMER()
	ON_WM_PAINT()
END_MESSAGE_MAP()

BOOL CMiApp::InitInstance()
{
	CMiVentana *pV = new CMiVentana("Mi Ventana");
	pV->ShowWindow(SW_SHOWNORMAL);//SW_SHOWMAXIMIZED
	pV->UpdateWindow();
	CMiApp::m_pMainWnd = pV; //copiar el objeto
	return true;
}
//constructor
CMiVentana::CMiVentana(char *name)
{
	this->Create(NULL,name); //otras opciones
	miBoton.Create("Salir",WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,
									CRect(0,0,70,30),this,1001);
										 //x1, y1, x2, y2

	tim1.Create("Start",WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,
									CRect(0,35,70,65),this,1002);

	//dc.MoveTo(0,90); 
	//dc.LineTo(r.bottom, 90);
	started = 0;
	CRect r;
	GetClientRect(r);
	x = rand()%(r.right-RADIUS-r.left + 1) + r.left;
	y = rand()%(r.bottom-RADIUS-r.top + 1) + r.top;
	dx = 1;
	dy = 1;
}

void CMiVentana::Salir()
{
	if(MessageBox("Desea Salir?","Mis Mensajes",MB_YESNO) == IDYES){
		this->OnClose(); // cerrar ventana y messagebox
	}
}

void CMiVentana::OnTimer(UINT nID)
{
	Bola();
	started = 1;
	Invalidate(true);
}

void CMiVentana::Start()
{
	CPaintDC dc(this);
	CRect r;
	GetClientRect(r);
	x = rand()%(r.right-RADIUS-r.left + 1) + r.left;
	y = rand()%(r.bottom-RADIUS-r.top + 1) + r.top;
	dc.Ellipse(x, y, x+RADIUS, y+RADIUS);
	started = 1;
	SetTimer(1,200,NULL);
	Invalidate(true);
}

int swap(int a){
	if(a == -1) return 1;
	else return -1;
}

void CMiVentana::Bola()
{
	CRect r;
	GetClientRect(r);
	if(x <= r.left + 70 || x >= r.right - RADIUS){
		dx = swap(dx);
	}
	else if(y <= r.top || y >= r.bottom - RADIUS){
		dy = swap(dy);
	}
	x += dx*SPEED;
	y += dy*SPEED;
}

void CMiVentana::OnMouseMove(UINT nF, CPoint p)
{
	m_p = p;
	Invalidate(false);
}

void CMiVentana::OnPaint()
{
	CPaintDC dc(this); //objeto del dispositivo gráfico
	CRect r;
	GetClientRect(r);

	// diseño
	CPen p1(PS_SOLID,1,RGB(0,0,0));
	dc.SelectObject(&p1);
	dc.MoveTo(70,0); dc.LineTo(70,r.bottom);
	//dc.MoveTo(0,r.bottom/2); dc.LineTo(r.right,r.bottom/2);

	// onHOUSE paint
	CRect r1;
	GetClientRect(r1);
	CString cs; 
	cs.Format(" Ball coordinates: x:%.3d y:%.3d",x,y);
	dc.TextOut(75,r1.top,cs); //escribir

	Bola();
	// pintar la bola
	//DrawCircle(&dc,20,50,250); // may not work
	if(started == 1){
		dc.Ellipse(x, y, x+RADIUS, y+RADIUS);
		started = 0;
	}
	//DrawCircle(CPaintDC,rad,x,y);

}
