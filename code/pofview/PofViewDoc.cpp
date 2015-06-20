/*
 * Copyright (C) Volition, Inc. 1999.  All rights reserved.
 *
 * All source code herein is the property of Volition, Inc. You may not sell 
 * or otherwise commercially exploit the source or things you created based on the 
 * source.
 *
*/

// PofViewDoc.cpp : implementation of the CPofViewDoc class
//

#include "stdafx.h"
#include "PofView.h"

#include "PofViewDoc.h"

#include "model.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPofViewDoc

IMPLEMENT_DYNCREATE(CPofViewDoc, CDocument)

BEGIN_MESSAGE_MAP(CPofViewDoc, CDocument)
	//{{AFX_MSG_MAP(CPofViewDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPofViewDoc construction/destruction

CPofViewDoc::CPofViewDoc()
{
	// TODO: add one-time construction code here

}

CPofViewDoc::~CPofViewDoc()
{
}

BOOL CPofViewDoc::OnNewDocument()
{
	m_model_num	= -1;

	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CPofViewDoc serialization

void CPofViewDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
		m_model_num = model_load((char *)LPCTSTR(ar.GetFile()->GetFilePath()), 0, NULL);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CPofViewDoc diagnostics

#ifdef _DEBUG
void CPofViewDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPofViewDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPofViewDoc commands
