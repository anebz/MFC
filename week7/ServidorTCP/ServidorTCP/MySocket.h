#pragma once

// Destino del comando de CMySocket

class CServidorTCPDlg; // De esta manera evitamos un error
// por recursividad en las cabeceras

class CMySocket : public CSocket
{
	public:
		CMySocket(CServidorTCPDlg *p);

		CServidorTCPDlg *pDlg;

		virtual ~CMySocket();
	protected:
		// Funcion de recepci�n al aceptar la conexi�n
		virtual void OnAccept(int nError);
};


