/*
 * Copyright (C) Volition, Inc. 1999.  All rights reserved.
 *
 * All source code herein is the property of Volition, Inc. You may not sell 
 * or otherwise commercially exploit the source or things you created based on the 
 * source.
 *
*/

// HelpEdView.h : interface of the CHelpEdView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_HELPEDVIEW_H__159085CC_C1B5_11D2_9904_00A0CC39C0BE__INCLUDED_)
#define AFX_HELPEDVIEW_H__159085CC_C1B5_11D2_9904_00A0CC39C0BE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CHelpEdView : public CView
{
protected: // create from serialization only
	CHelpEdView();
	DECLARE_DYNCREATE(CHelpEdView)
	CPoint m_ptPrevPos;
// Attributes
public:
	CHelpEdDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHelpEdView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	void OnLButtonDown(UINT nFlags, CPoint point);
	virtual ~CHelpEdView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CHelpEdView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in HelpEdView.cpp
inline CHelpEdDoc* CHelpEdView::GetDocument()
   { return (CHelpEdDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HELPEDVIEW_H__159085CC_C1B5_11D2_9904_00A0CC39C0BE__INCLUDED_)
