/*
 * Copyright (C) Volition, Inc. 1999.  All rights reserved.
 *
 * All source code herein is the property of Volition, Inc. You may not sell 
 * or otherwise commercially exploit the source or things you created based on the 
 * source.
 *
*/

// PofView.h : main header file for the POFVIEW application
//

#ifndef _POFVIEW_H
#define _POFVIEW_H

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CPofViewApp:
// See PofView.cpp for the implementation of this class
//

extern float model_thrust;
extern int model_afterburner;

class CPofViewApp : public CWinApp
{
public:
	virtual BOOL OnIdle(LONG lCount);
	CPofViewApp();


	int m_timer;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPofViewApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CPofViewApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
#endif
