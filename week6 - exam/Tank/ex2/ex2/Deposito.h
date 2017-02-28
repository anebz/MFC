#pragma once


// CDeposito

class CDeposito : public CWnd
{
	DECLARE_DYNAMIC(CDeposito)

public:
	CDeposito();
	virtual ~CDeposito();
	double initial_y;
	int dim_pict;
	int m_litros;
	int m_capmax;
	bool descarga;

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
};


