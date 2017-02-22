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
		int started;
		int x, y, dx, dy;
		CMiVentana(char *);//constructor

		DECLARE_MESSAGE_MAP() // declarar todos los mensajes

		void OnPaint();
		void Start();
		void Bola();
		void Salir();
		void OnTimer(UINT nID);
		void OnMouseMove(UINT, CPoint);
};
