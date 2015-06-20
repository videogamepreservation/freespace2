/*
 * Copyright (C) Volition, Inc. 1999.  All rights reserved.
 *
 * All source code herein is the property of Volition, Inc. You may not sell 
 * or otherwise commercially exploit the source or things you created based on the 
 * source.
 *
*/

// ObjectTree.h : header file
//
#ifndef _OBJECTTREE_H
#define _OBJECTTREE_H

#include "model.h"

/////////////////////////////////////////////////////////////////////////////
// CObjectTree dialog

class CObjectTree : public CDialog
{
// Construction
public:
	char m_title[128];

	void MyCreate(void * pv);
	void add_model(polymodel *pm, int submodel, HTREEITEM parent );
	void ExpandAll();
	void CollapseAll();

	CObjectTree(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CObjectTree)
	enum { IDD = IDD_DIALOG1 };
	CStatic	m_txt_pof_info;
	CStatic	m_txt_detail6;
	CStatic	m_txt_detail5;
	CStatic	m_txt_detail4;
	CStatic	m_txt_detail3;
	CStatic	m_txt_detail1;
	CStatic	m_txt_detail2;
	CStatic	m_txt_bspgen_version;
	CStatic	m_txt_movement_axis;
	CStatic	m_txt_movement_type;
	CStatic	m_txt_name;
	CStatic	m_txt_num_polies;
	CStatic	m_txt_num_verts;
	CTreeCtrl	m_tree;
	//}}AFX_DATA


	void * m_pv;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CObjectTree)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CObjectTree)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangedTree1(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif
