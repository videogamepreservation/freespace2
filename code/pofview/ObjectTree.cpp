/*
 * Copyright (C) Volition, Inc. 1999.  All rights reserved.
 *
 * All source code herein is the property of Volition, Inc. You may not sell 
 * or otherwise commercially exploit the source or things you created based on the 
 * source.
 *
*/

// ObjectTree.cpp : implementation file
//

#include "stdafx.h"
#include "pofview.h"
#include "ObjectTree.h"
#include "PofViewDoc.h"
#include "PofViewView.h"


#include "model.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CObjectTree dialog


CObjectTree::CObjectTree(CWnd* pParent /*=NULL*/)
	: CDialog(CObjectTree::IDD, pParent)
{
	//{{AFX_DATA_INIT(CObjectTree)
	//}}AFX_DATA_INIT

	m_pv = NULL;
}


void CObjectTree::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CObjectTree)
	DDX_Control(pDX, IDC_TXT_POF_INFO, m_txt_pof_info);
	DDX_Control(pDX, IDC_TXT_DETAIL6, m_txt_detail6);
	DDX_Control(pDX, IDC_TXT_DETAIL5, m_txt_detail5);
	DDX_Control(pDX, IDC_TXT_DETAIL4, m_txt_detail4);
	DDX_Control(pDX, IDC_TXT_DETAIL3, m_txt_detail3);
	DDX_Control(pDX, IDC_TXT_DETAIIL1, m_txt_detail1);
	DDX_Control(pDX, IDC_TXT_DETAIL2, m_txt_detail2);
	DDX_Control(pDX, IDC_TXT_BSPGEN_VERSION, m_txt_bspgen_version);
	DDX_Control(pDX, IDC_TXT_MOVEMENT_AXIS, m_txt_movement_axis);
	DDX_Control(pDX, IDC_TXT_MOVEMENT_TYPE, m_txt_movement_type);
	DDX_Control(pDX, IDC_TXT_NAME, m_txt_name);
	DDX_Control(pDX, IDC_TXT_NUMPOLIES, m_txt_num_polies);
	DDX_Control(pDX, IDC_TXT_NUM_VERTICES, m_txt_num_verts);
	DDX_Control(pDX, IDC_TREE1, m_tree);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CObjectTree, CDialog)
	//{{AFX_MSG_MAP(CObjectTree)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE1, OnSelchangedTree1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CObjectTree message handlers


void CObjectTree::add_model(polymodel *pm, int sm, HTREEITEM parent )
{
	int i;
	HTREEITEM citem;

	// check for live debris
	if ( !strnicmp("debris-", pm->submodel[sm].name, strlen("debris-")) ) {
		char debris_name[256];

		// traverse the tree and put live debris with correct submodel
		for (citem = m_tree.GetFirstVisibleItem(); citem != NULL; citem = m_tree.GetNextVisibleItem(citem)) {
			CString item_text = m_tree.GetItemText(citem);
			strcpy(debris_name, "debris-");
			strcat(debris_name, item_text);

			if ( strstr(pm->submodel[sm].name, debris_name) ) {
				citem = m_tree.InsertItem( pm->submodel[sm].name, citem );
				m_tree.SetItemData( citem, sm );
				return;
			}
		}
	}

	if ( parent != NULL )
		citem = m_tree.InsertItem( pm->submodel[sm].name, parent );
	else
		citem = m_tree.InsertItem( pm->submodel[sm].name );

	m_tree.SetItemData( citem, sm );

	for (i=pm->submodel[sm].first_child; i>-1; i = pm->submodel[i].next_sibling )	{
		add_model(pm, i, citem );
	}

}

BOOL CObjectTree::OnInitDialog() 
{
	CDialog::OnInitDialog();

	{	
		CPofViewView * pv = (CPofViewView * )m_pv;
		if ( pv )	{
			CPofViewDoc* pDoc = pv->GetDocument();
			if ( pDoc->m_model_num > -1 )	{
				polymodel * pm = model_get(pDoc->m_model_num);

				int i;

				sprintf( m_title, "%s's subobjects", pDoc->GetTitle() );

				SetWindowText(m_title);
						
				//m_tree.DeleteAllItems();

				// add all base submodels (ie, without parents) except live debris
				for (i=0; i<pm->n_models; i++)	{
					if ( pm->submodel[i].parent < 0) {
						// add if *not* live debris
						if ( strnicmp("debris-", pm->submodel[i].name, strlen("debris-")) ) {
							add_model(pm, i, NULL);
						}
					}
				}

				// Expand to make all tree visible for searching when adding live debris
				ExpandAll();
				// Now add any live debris
				for (i=0; i<pm->n_models; i++)	{
					if ( pm->submodel[i].parent < 0) {
						// add if live debris
						if ( !strnicmp("debris-", pm->submodel[i].name, strlen("debris-")) ) {
							add_model(pm, i, NULL);
						}
					}
				}
				CollapseAll();

			} else {
				sprintf( m_title, "%s's subobjects", pDoc->GetTitle() );

				SetWindowText(m_title);
			}

		}




	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CObjectTree::MyCreate(void * pv)
{
	m_pv = pv;

	if (!GetSafeHwnd())
		Create(CObjectTree::IDD);

	SetWindowPos(&wndTop, 0, 0, 0, 0, SWP_SHOWWINDOW | SWP_NOMOVE | SWP_NOSIZE);
}

void CObjectTree::OnSelchangedTree1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	
	if (pNMTreeView->hdr.code == TVN_SELCHANGED )		{
		CPofViewView * pv = (CPofViewView * )m_pv;
		if ( pv )	{
			CPofViewDoc* pDoc = pv->GetDocument();
			polymodel * pm = model_get(pDoc->m_model_num);
			bsp_info * sm = &pm->submodel[pNMTreeView->itemNew.lParam];

			m_txt_detail1.SetWindowText("");
			m_txt_detail2.SetWindowText("");
			m_txt_detail3.SetWindowText("");
			m_txt_detail4.SetWindowText("");
			m_txt_detail5.SetWindowText("");
			m_txt_detail6.SetWindowText("");

			m_txt_pof_info.SetWindowText("");


			if ( pm )	{
				char tmp[1024];

				sprintf( tmp, "%d.%02d", pm->version/100, pm->version %100 );
				m_txt_bspgen_version.SetWindowText(tmp);

				m_txt_name.SetWindowText(sm->name);

				sprintf( tmp, "%d", submodel_get_num_polys(pDoc->m_model_num,pNMTreeView->itemNew.lParam) );
				m_txt_num_polies.SetWindowText(tmp);

				sprintf( tmp, "%d", submodel_get_num_verts(pDoc->m_model_num,pNMTreeView->itemNew.lParam) );
				m_txt_num_verts.SetWindowText(tmp);

				switch( sm->movement_type )	{
				case -1: m_txt_movement_type.SetWindowText("None");break;
				case 0: m_txt_movement_type.SetWindowText("Positional");break;
				case 1: m_txt_movement_type.SetWindowText("Rotational");break;
				default: m_txt_movement_type.SetWindowText("?Unknown?");break;
				}

				if (sm->movement_type==1)	{
					switch(sm->movement_axis)	{
					case 0:m_txt_movement_axis.SetWindowText("X (Pitch)");break;
					case 1:m_txt_movement_axis.SetWindowText("Y (Bank)");break;
					case 2:m_txt_movement_axis.SetWindowText("Z (Heading)");break;
					default:m_txt_movement_axis.SetWindowText("?Unknown?");break;
					}
				} else {
					m_txt_movement_axis.SetWindowText("");
				}

				if ( sm->num_details > 0 )
					m_txt_detail1.SetWindowText(pm->submodel[sm->details[0]].name);
				if ( sm->num_details > 1 )
					m_txt_detail2.SetWindowText(pm->submodel[sm->details[1]].name);
				if ( sm->num_details > 2 )
					m_txt_detail3.SetWindowText(pm->submodel[sm->details[2]].name);
				if ( sm->num_details > 3 )
					m_txt_detail4.SetWindowText(pm->submodel[sm->details[3]].name);
				if ( sm->num_details > 4 )
					m_txt_detail5.SetWindowText(pm->submodel[sm->details[4]].name);
				if ( sm->num_details > 5 )
					m_txt_detail6.SetWindowText(pm->submodel[sm->details[5]].name);

				if ( sm->i_replace > -1 )	{
					sprintf( tmp, "%s\n[I replace %s]", pm->debug_info, pm->submodel[sm->i_replace].name );
					m_txt_pof_info.SetWindowText(tmp);
				} else if ( sm->my_replacement > -1 ) {
					sprintf( tmp, "%s\n[My replacment %s]", pm->debug_info, pm->submodel[sm->my_replacement].name );
					m_txt_pof_info.SetWindowText(tmp);
				} else {
					m_txt_pof_info.SetWindowText(pm->debug_info);
				}

				
			} else {
				m_txt_name.SetWindowText("");
				m_txt_num_polies.SetWindowText("");
				m_txt_num_verts.SetWindowText("");
				m_txt_movement_axis.SetWindowText("");
				m_txt_movement_type.SetWindowText("");
			}
		}
		
	}
	
	*pResult = 0;
}

// Expand the tree making all first level visible
void CObjectTree::ExpandAll()
{
	HTREEITEM citem;

	for (citem = m_tree.GetFirstVisibleItem(); citem != NULL; citem = m_tree.GetNextVisibleItem(citem)) {
		m_tree.Expand(citem, TVE_EXPAND);
	}

}

// Collapse all first level
void CObjectTree::CollapseAll()
{
	HTREEITEM citem;

	for (citem = m_tree.GetFirstVisibleItem(); citem != NULL; citem = m_tree.GetNextVisibleItem(citem)) {
		m_tree.Expand(citem, TVE_COLLAPSE);
	}

}



