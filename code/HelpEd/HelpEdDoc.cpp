/*
 * Copyright (C) Volition, Inc. 1999.  All rights reserved.
 *
 * All source code herein is the property of Volition, Inc. You may not sell 
 * or otherwise commercially exploit the source or things you created based on the 
 * source.
 *
*/

// HelpEdDoc.cpp : implementation of the CHelpEdDoc class
//

#include "stdafx.h"
#include "HelpEd.h"

#include "HelpEdDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHelpEdDoc

IMPLEMENT_DYNCREATE(CHelpEdDoc, CDocument)

BEGIN_MESSAGE_MAP(CHelpEdDoc, CDocument)
	//{{AFX_MSG_MAP(CHelpEdDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHelpEdDoc construction/destruction

CHelpEdDoc::CHelpEdDoc()
{
	// TODO: add one-time construction code here

}

CHelpEdDoc::~CHelpEdDoc()
{
}

BOOL CHelpEdDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CHelpEdDoc serialization

void CHelpEdDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CHelpEdDoc diagnostics

#ifdef _DEBUG
void CHelpEdDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CHelpEdDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CHelpEdDoc commands

HelpEdLine * CHelpEdDoc::AddLine(CPoint pointFrom, CPoint pointTo)
{
	// create a new line
	HelpEdLine *newline = new HelpEdLine(pointFrom, pointTo);
	try {
		// add this line to object array
		line_array.Add(newline);
		// mark document dirty
		SetModifiedFlag();
	}
	// check for memory exception
	catch (CMemoryException* addlineerror) {
		// display error message in pop box
		AfxMessageBox("Out of memory", MB_ICONSTOP | MB_OK);
		// if we created a HelpEdLine object, we should delete it
		if (newline) {
			delete newline;
			newline = NULL;
		}
		// delete the error message
		addlineerror->Delete();
	}
	return newline;
}

int CHelpEdDoc::get_line_count()
{
	// return line_array size
	return line_array.GetSize();
}
