/*
 * Copyright (C) Volition, Inc. 1999.  All rights reserved.
 *
 * All source code herein is the property of Volition, Inc. You may not sell 
 * or otherwise commercially exploit the source or things you created based on the 
 * source.
 *
*/

// HelpEdView.cpp : implementation of the CHelpEdView class
//

#include "stdafx.h"
#include "HelpEd.h"

#include "HelpEdDoc.h"
#include "HelpEdView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHelpEdView

IMPLEMENT_DYNCREATE(CHelpEdView, CView)

BEGIN_MESSAGE_MAP(CHelpEdView, CView)
	//{{AFX_MSG_MAP(CHelpEdView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHelpEdView construction/destruction

CHelpEdView::CHelpEdView()
{
	// TODO: add construction code here

}

CHelpEdView::~CHelpEdView()
{
}

BOOL CHelpEdView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CHelpEdView drawing

void CHelpEdView::OnDraw(CDC* pDC)
{
	pDC;
	CHelpEdDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CHelpEdView diagnostics

#ifdef _DEBUG
void CHelpEdView::AssertValid() const
{
	CView::AssertValid();
}

void CHelpEdView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CHelpEdDoc* CHelpEdView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CHelpEdDoc)));
	return (CHelpEdDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CHelpEdView message handlers

void CHelpEdView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// Capture the mouse, so no other application can
	// grab it if the mouse leaves the window area
	SetCapture();
	// Save the point
	m_ptPrevPos = point;

	// pass mouse event up the chain
	CView::OnLButtonDown(nFlags, point);
}


//DEL void CHelpEdView::blah()
//DEL {
//DEL 
//DEL }
