#pragma once
// Destino del comando de CSockServidor

class CServidorUDPDlg; // De esta manera evitamos un error por recursividad en las cabeceras

class CSockServidor : public CSocket
{
	public:
		CSockServidor(CServidorUDPDlg *p);
		CServidorUDPDlg *pDlg;
		virtual ~CSockServidor();
	protected:
		// Funcion de recepcion
		void OnReceive(int nError);
};


