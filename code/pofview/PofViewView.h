/*
 * Copyright (C) Volition, Inc. 1999.  All rights reserved.
 *
 * All source code herein is the property of Volition, Inc. You may not sell 
 * or otherwise commercially exploit the source or things you created based on the 
 * source.
 *
*/

// PofViewView.h : interface of the CPofViewView class
//
/////////////////////////////////////////////////////////////////////////////

#include "VecMat.h"
#include "Physics.h"
#include "ObjectTree.h"

class CPofViewView : public CView
{
protected: // create from serialization only
	CPofViewView();
	DECLARE_DYNCREATE(CPofViewView)

// Attributes
public:
	int m_dolighting;
	CPofViewDoc* GetDocument();

	void MoveViewer(float FrameTime, BOOL is_active, int key);

	vector m_ViewerPos;
	matrix m_ViewerOrient;
	matrix m_ObjectOrient;
	float m_ViewerZoom;
	physics_info m_ViewerPhysics;
	control_info m_Viewer_ci;
	int m_show_outline;
	int m_show_pivots;
	int m_current_detail_level;
	int m_show_paths;
	int m_show_radius;
	int m_show_overwrite;
	int m_show_destroyed_subobjects;
	int m_show_shields;
	int m_show_invisible_faces;	
	int m_show_bay_paths;
	int m_autocenter;
	int m_mouse_x, m_mouse_y;
	int m_mouse_dx, m_mouse_dy;
	int m_mouse_down;
	int m_mouse_inited;
	
	int m_texturing;
	int m_smoothing;
	int m_lights_on;

	CObjectTree m_TreeDialog;	

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPofViewView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual void OnInitialUpdate();
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPofViewView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CPofViewView)
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPofOutline();
	afx_msg void OnUpdatePofOutline(CCmdUI* pCmdUI);
	afx_msg void OnPofLighting();
	afx_msg void OnUpdatePofLighting(CCmdUI* pCmdUI);
	afx_msg void OnPofPivots();
	afx_msg void OnUpdatePofPivots(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDetail1(CCmdUI* pCmdUI);
	afx_msg void OnDetail1();
	afx_msg void OnDetail2();
	afx_msg void OnUpdateDetail2(CCmdUI* pCmdUI);
	afx_msg void OnDetail3();
	afx_msg void OnUpdateDetail3(CCmdUI* pCmdUI);
	afx_msg void OnDetail4();
	afx_msg void OnUpdateDetail4(CCmdUI* pCmdUI);
	afx_msg void OnDetail5();
	afx_msg void OnUpdateDetail5(CCmdUI* pCmdUI);
	afx_msg void OnDetail6();
	afx_msg void OnUpdateDetail6(CCmdUI* pCmdUI);
	afx_msg void OnShowTree();
	afx_msg void OnUpdateShowTree(CCmdUI* pCmdUI);
	afx_msg void OnPofPaths();
	afx_msg void OnUpdatePofPaths(CCmdUI* pCmdUI);
	afx_msg void OnPofRadius();
	afx_msg void OnUpdatePofRadius(CCmdUI* pCmdUI);
	afx_msg void OnPofOverwrite();
	afx_msg void OnUpdatePofOverwrite(CCmdUI* pCmdUI);
	afx_msg void OnShowDamagedSubobjects();
	afx_msg void OnUpdateShowDamagedSubobjects(CCmdUI* pCmdUI);
	afx_msg void OnShowDebris();
	afx_msg void OnUpdateShowDebris(CCmdUI* pCmdUI);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnPofSmoothing();
	afx_msg void OnUpdatePofSmoothing(CCmdUI* pCmdUI);
	afx_msg void OnPofTexturing();
	afx_msg void OnUpdatePofTexturing(CCmdUI* pCmdUI);
	afx_msg void OnPofShields();
	afx_msg void OnUpdatePofShields(CCmdUI* pCmdUI);
	afx_msg void OnToggleLighting();
	afx_msg void OnUpdateToggleLighting(CCmdUI* pCmdUI);
	afx_msg void OnInvisiblefaces();
	afx_msg void OnUpdateInvisiblefaces(CCmdUI* pCmdUI);	
	afx_msg void OnBayPaths();
	afx_msg void OnUpdateBayPaths(CCmdUI* pCmdUI);
	afx_msg void OnAutocenter();
	afx_msg void OnUpdateAutocenter(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in PofViewView.cpp
inline CPofViewDoc* CPofViewView::GetDocument()
   { return (CPofViewDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
