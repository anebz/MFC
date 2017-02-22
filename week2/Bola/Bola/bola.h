#include <afxwin.h>

class CMiApp :public CWinApp
{
	public: //sobrecargar InitInstance
		BOOL InitInstance();
};

class CMiVentana :public CFrameWnd
{
private:
	CPoint m_p;
public:
		CButton miBoton, tim1, tim2, obj;
		int firstpos;
		int x1, x2, y1, y2;
		CMiVentana(char *);//constructor

		DECLARE_MESSAGE_MAP() // declarar todos los mensajes

		void EmpezarTimer();
		void AcabarTimer();
		void OnPaint();
		void OnTimer(UINT nID);
		void Salir();
		void OnMouseMove(UINT, CPoint);
};