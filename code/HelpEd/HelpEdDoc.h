/*
 * Copyright (C) Volition, Inc. 1999.  All rights reserved.
 *
 * All source code herein is the property of Volition, Inc. You may not sell 
 * or otherwise commercially exploit the source or things you created based on the 
 * source.
 *
*/

// HelpEdDoc.h : interface of the CHelpEdDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_HELPEDDOC_H__159085CA_C1B5_11D2_9904_00A0CC39C0BE__INCLUDED_)
#define AFX_HELPEDDOC_H__159085CA_C1B5_11D2_9904_00A0CC39C0BE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "HelpEdLine.h"

class CHelpEdDoc : public CDocument
{
protected: // create from serialization only
	CHelpEdDoc();
	DECLARE_DYNCREATE(CHelpEdDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHelpEdDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	int get_line_count();
	HelpEdLine * AddLine(CPoint pointFrom, CPoint pointTo);
	virtual ~CHelpEdDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CHelpEdDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CObArray line_array;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HELPEDDOC_H__159085CA_C1B5_11D2_9904_00A0CC39C0BE__INCLUDED_)
