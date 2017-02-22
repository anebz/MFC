#include <afxwin.h>
#include "Simple.h"
#include <math.h>

CMiApp miObjeto; //crear un objeto global y empieza

								// mi_clase		clase_heredada
BEGIN_MESSAGE_MAP(CMiVentana, CFrameWnd)
	ON_COMMAND(1001, Salir) // tiene que tener el mismo identificador que el boton
	ON_COMMAND(1002, EmpezarTimer)
	ON_COMMAND(1003, AcabarTimer)
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
									CRect(20,20,120,50),this,1001);
										 //x1, y1, x2, y2

	tim1.Create("Empezar timer",WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,
									CRect(140,20,240,50),this,1002);

	tim2.Create("Matar timer",WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,
								CRect(260,20,360,50),this,1003);
	firstpos = 0;
}

void CMiVentana::Salir()
{
	if(MessageBox("Desea Salir?","Mis Mensajes",MB_YESNO) == IDYES){
		this->OnClose(); // cerrar ventana y messagebox
	}
}

void CMiVentana::OnMouseMove(UINT nF, CPoint p)
{
	m_p = p;
	Invalidate(false);
}

void CMiVentana::OnTimer(UINT nID)
{
	firstpos++;
	Invalidate(true);
}

void CMiVentana::EmpezarTimer()
{
	SetTimer(1,50,NULL); // 1:ID, 100 son ms
				//   cada cuanto se incrementa el timer
}

void CMiVentana::AcabarTimer()
{
	KillTimer(1); //1:ID
	firstpos = 0;
	Invalidate(false);
}

void CMiVentana::OnPaint()
{
	CPaintDC dc(this); //objeto del dispositivo gráfico
	static int cont2 = 0;
	CRect r;
	GetClientRect(r);
	CString cs; 
	cs.Format("ContOnPaint=%.3d",cont2++);
	// se incrementa cada vez que minimizamos o cambiamos de ventana
	dc.TextOut(10,r.top,cs);
	//Dibujo Ejes
	CPen p1(PS_SOLID,1,RGB(255,0,0));
	dc.SelectObject(&p1);
	dc.MoveTo(r.right/2,0); dc.LineTo(r.right/2,r.bottom);
	dc.MoveTo(0,r.bottom/2); dc.LineTo(r.right,r.bottom/2);

	// onHOUSE paint
	CRect r1;
	//obtener las dimen. del area cliente
	GetClientRect(r1);
	cs.Format("x:%.3d y:%.3d",m_p.x,m_p.y);
	dc.TextOut(10,r1.bottom-20,cs); //escribir

	// timer
	CRect r2;
	GetClientRect(r);
	cs.Format("Timer = %.3d",firstpos);
	CPen p2(PS_SOLID,1,RGB(0,0,0));
	dc.SelectObject(&p2);

	dc.TextOut(10,r2.top+140,cs);
						// x, y, string
	x1 = (int)r.right/2*cos(2*3.14*firstpos/10) + r.right/2;
	x2 = x1 + 20;
	y1 = r.bottom/2 - 20; y2 = y1 + 20;
	dc.Rectangle(x1, y1, x2, y2);

	dc.MoveTo(0,r.bottom/2 - 10); 
	dc.LineTo(x1,r.bottom/2 - 10);
}
