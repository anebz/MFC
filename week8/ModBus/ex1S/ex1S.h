
// ex1S.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// Cex1SApp:
// See ex1S.cpp for the implementation of this class
//

class Cex1SApp : public CWinApp
{
public:
	Cex1SApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern Cex1SApp theApp;