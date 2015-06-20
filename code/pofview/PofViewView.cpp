/*
 * Copyright (C) Volition, Inc. 1999.  All rights reserved.
 *
 * All source code herein is the property of Volition, Inc. You may not sell 
 * or otherwise commercially exploit the source or things you created based on the 
 * source.
 *
*/

// PofViewView.cpp : implementation of the CPofViewView class
//

#include "stdafx.h"
#include "PofView.h"

#include "PofViewDoc.h"
#include "PofViewView.h"

#include "2d.h"
#include "3d.h"
#include "model.h"
#include "vecmat.h"
#include "bmpman.h"
#include "floating.h"
#include "key.h"
#include "physics.h"
#include "lighting.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPofViewView

IMPLEMENT_DYNCREATE(CPofViewView, CView)

BEGIN_MESSAGE_MAP(CPofViewView, CView)
	//{{AFX_MSG_MAP(CPofViewView)
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_WM_KILLFOCUS()
	ON_WM_SETFOCUS()
	ON_WM_SIZE()
	ON_COMMAND(ID_POF_OUTLINE, OnPofOutline)
	ON_UPDATE_COMMAND_UI(ID_POF_OUTLINE, OnUpdatePofOutline)
	ON_COMMAND(ID_POF_LIGHTING, OnPofLighting)
	ON_UPDATE_COMMAND_UI(ID_POF_LIGHTING, OnUpdatePofLighting)
	ON_COMMAND(ID_POF_PIVOTS, OnPofPivots)
	ON_UPDATE_COMMAND_UI(ID_POF_PIVOTS, OnUpdatePofPivots)
	ON_UPDATE_COMMAND_UI(ID_DETAIL_1, OnUpdateDetail1)
	ON_COMMAND(ID_DETAIL_1, OnDetail1)
	ON_COMMAND(ID_DETAIL_2, OnDetail2)
	ON_UPDATE_COMMAND_UI(ID_DETAIL_2, OnUpdateDetail2)
	ON_COMMAND(ID_DETAIL_3, OnDetail3)
	ON_UPDATE_COMMAND_UI(ID_DETAIL_3, OnUpdateDetail3)
	ON_COMMAND(ID_DETAIL_4, OnDetail4)
	ON_UPDATE_COMMAND_UI(ID_DETAIL_4, OnUpdateDetail4)
	ON_COMMAND(ID_DETAIL_5, OnDetail5)
	ON_UPDATE_COMMAND_UI(ID_DETAIL_5, OnUpdateDetail5)
	ON_COMMAND(ID_DETAIL_6, OnDetail6)
	ON_UPDATE_COMMAND_UI(ID_DETAIL_6, OnUpdateDetail6)
	ON_COMMAND(ID_SHOW_TREE, OnShowTree)
	ON_UPDATE_COMMAND_UI(ID_SHOW_TREE, OnUpdateShowTree)
	ON_COMMAND(ID_POF_PATHS, OnPofPaths)
	ON_UPDATE_COMMAND_UI(ID_POF_PATHS, OnUpdatePofPaths)
	ON_COMMAND(ID_POF_RADIUS, OnPofRadius)
	ON_UPDATE_COMMAND_UI(ID_POF_RADIUS, OnUpdatePofRadius)
	ON_COMMAND(ID_POF_OVERWRITE, OnPofOverwrite)
	ON_UPDATE_COMMAND_UI(ID_POF_OVERWRITE, OnUpdatePofOverwrite)
	ON_COMMAND(IDC_SHOW_DAMAGED_SUBOBJECTS, OnShowDamagedSubobjects)
	ON_UPDATE_COMMAND_UI(IDC_SHOW_DAMAGED_SUBOBJECTS, OnUpdateShowDamagedSubobjects)
	ON_COMMAND(IDC_SHOW_DEBRIS, OnShowDebris)
	ON_UPDATE_COMMAND_UI(IDC_SHOW_DEBRIS, OnUpdateShowDebris)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_POF_SMOOTHING, OnPofSmoothing)
	ON_UPDATE_COMMAND_UI(ID_POF_SMOOTHING, OnUpdatePofSmoothing)
	ON_COMMAND(ID_POF_TEXTURING, OnPofTexturing)
	ON_UPDATE_COMMAND_UI(ID_POF_TEXTURING, OnUpdatePofTexturing)
	ON_COMMAND(ID_POF_SHIELDS, OnPofShields)
	ON_UPDATE_COMMAND_UI(ID_POF_SHIELDS, OnUpdatePofShields)
	ON_COMMAND(IDC_TOGGLE_LIGHTING, OnToggleLighting)
	ON_UPDATE_COMMAND_UI(IDC_TOGGLE_LIGHTING, OnUpdateToggleLighting)
	ON_COMMAND(ID_INVISIBLEFACES, OnInvisiblefaces)
	ON_UPDATE_COMMAND_UI(ID_INVISIBLEFACES, OnUpdateInvisiblefaces)	
	ON_COMMAND(ID_BAY_PATHS, OnBayPaths)
	ON_UPDATE_COMMAND_UI(ID_BAY_PATHS, OnUpdateBayPaths)
	ON_COMMAND(ID_AUTOCEN, OnAutocenter)
	ON_UPDATE_COMMAND_UI(ID_AUTOCEN, OnUpdateAutocenter)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPofViewView construction/destruction

CPofViewView::CPofViewView()
{
	// TODO: add construction code here
//	m_ViewerPos = 
//	m_ViewerOrient = 

	matrix temp_orient = IDENTITY_MATRIX;
	vector temp_pos = {0.0f, 0.0f, -10.0f};

	m_ViewerZoom = 0.8f;
	m_ViewerPos = temp_pos;
	m_ViewerOrient = temp_orient;
	m_ObjectOrient = vmd_identity_matrix;
	
//	m_ViewerPos.x=f2fl(0xadd3); m_ViewerPos.y = f2fl(0x32cbb); m_ViewerPos.z =f2fl(0x10006e);
//	m_ViewerOrient.rvec.x=f2fl(0xffff40e2); m_ViewerOrient.rvec.y=f2fl(0x2b3); m_ViewerOrient.rvec.z = f2fl(0xffff55b4);
//	m_ViewerOrient.uvec.x=f2fl(0x5cba); m_ViewerOrient.uvec.y=f2fl(0xd859); m_ViewerOrient.uvec.z = f2fl(0xffff9b5d);
//	m_ViewerOrient.fvec.x=f2fl(0x8edd); m_ViewerOrient.fvec.y=f2fl(0xffff772f); m_ViewerOrient.fvec.z=f2fl(0xffff5d80);

	physics_init( &m_ViewerPhysics );
	m_ViewerPhysics.flags |= PF_ACCELERATES | PF_SLIDE_ENABLED;

	memset( &m_Viewer_ci, 0, sizeof(control_info) );

	m_show_outline = 0;
	m_dolighting = 0;
	m_show_pivots = 0;
	m_current_detail_level = 1;		// If 0, show debris
	m_show_paths = 0;
	m_show_radius = 0;
	m_show_overwrite = 0;
	m_show_destroyed_subobjects = 0;
	m_show_shields = 0;
	m_show_invisible_faces = 0;	
	m_show_bay_paths = 0;
	m_autocenter = 0;
	
	m_lights_on = 1;

	m_mouse_inited = 0;
	m_mouse_x = m_mouse_y = 0;
	m_mouse_dx = m_mouse_dy = 0;
	m_mouse_down = 0;
	
	m_texturing = 1;
	m_smoothing = 1;
	
//	CObjectTree m_subobjects;	
}

void CPofViewView::MoveViewer(float FrameTime, BOOL is_active, int key )
{
	control_info * ci = &m_Viewer_ci;
	float kh;
	polymodel *pm = NULL;

	CPofViewDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	int n_detail_levels = 0;
	if ( pDoc->m_model_num > -1 )	{
		pm = model_get(pDoc->m_model_num);
		n_detail_levels = pm->n_detail_levels;
	}
	 
	switch(key)	{
	case KEY_1:
		if ( n_detail_levels >= 1){
			m_current_detail_level = 1;
		}
		break;
	case KEY_2:
		if ( n_detail_levels >= 2){
			m_current_detail_level = 2;
		}
		break;
	case KEY_3:
		if ( n_detail_levels >= 3){ 
			m_current_detail_level = 3;
		}
		break;
	case KEY_4:
		if ( n_detail_levels >= 4){
			m_current_detail_level = 4;
		}
		break;
	case KEY_5:
		if ( n_detail_levels >= 5){
			m_current_detail_level = 5;
		}
		break;
	case KEY_6:
		if ( n_detail_levels >= 6){
			m_current_detail_level = 6;
		}
		break;
	case KEY_MINUS:
		// Scales the engines thrusters by this much
		model_thrust -= 0.1f;
		if ( model_thrust < 0.0f ){
			model_thrust = 0.0f;
		}
		break;
	case KEY_EQUAL:
		// Scales the engines thrusters by this much
		model_thrust += 0.1f;
		if ( model_thrust > 1.0f ){
			model_thrust = 1.0f;
		}
		break;
	}

	float c_scale = 1.0f;

	if((pm != NULL) && (pm->core_radius < 200.0f)){
		c_scale = 1.0f / 6.0f;
	}
	
	// From keyboard...
	if ( is_active )	{
		float temp = ci->heading;
		float temp1 = ci->pitch;
		memset( ci, 0, sizeof(control_info) );
		ci->heading = temp;
		ci->pitch = temp1;

		if ( keyd_pressed[KEY_BACKSP] )	{
			model_afterburner = 1;
		} else {
			model_afterburner = 0;
		}

	
		kh = (key_down_timef(KEY_PAD6) - key_down_timef(KEY_PAD4)) / 32.0f;
		if (kh == 0.0f){
			ci->heading = 0.0f;
		} else if (kh > 0.0f) {
			if (ci->heading < 0.0f){
				ci->heading = 0.0f;
			}
		} else {// kh < 0
			if (ci->heading > 0.0f){
				ci->heading = 0.0f;
			}
		}
		ci->heading += kh;

		kh = (key_down_timef(KEY_PAD8) - key_down_timef(KEY_PAD2)) / 32.0f;
		if (kh == 0.0f){
			ci->pitch = 0.0f;
		} else if (kh > 0.0f) {
			if (ci->pitch < 0.0f){
				ci->pitch = 0.0f;
			}
		} else { // kh < 0
			if (ci->pitch > 0.0f){
				ci->pitch = 0.0f;
			}
		}
		ci->pitch += kh;

		ci->bank = (key_down_timef(KEY_PAD7) - key_down_timef(KEY_PAD9)) / 8.0f;
		ci->forward = (key_down_timef(KEY_A) - key_down_timef(KEY_Z)) * c_scale;
		ci->sideways = (key_down_timef(KEY_PAD3) - key_down_timef(KEY_PAD1)) * c_scale;
		ci->vertical = (key_down_timef(KEY_PADMINUS) - key_down_timef(KEY_PADPLUS)) * c_scale;
	} else {
		memset( ci, 0, sizeof(control_info) );
	}
	physics_read_flying_controls( &m_ViewerOrient, &m_ViewerPhysics, &m_Viewer_ci, FrameTime );

	physics_sim(&m_ViewerPos, &m_ViewerOrient, &m_ViewerPhysics, FrameTime * 6 );		


	// Rotate object:
	if ( m_mouse_down )	{
		matrix tempm, mousem;

		if ( m_mouse_dx || m_mouse_dy )	{
			vm_trackball( -m_mouse_dx, m_mouse_dy, &mousem );
			vm_matrix_x_matrix(&tempm, &m_ObjectOrient, &mousem);
			m_ObjectOrient = tempm;

			m_mouse_dx = m_mouse_dy = 0;
		}
	}

	
}

CPofViewView::~CPofViewView()
{
}



extern int shipp_thruster_glow_bitmap;
extern float shipp_thruster_glow_noise;
extern int	shipp_thruster_bitmap;		// In PofView.cpp				// What frame the current thruster bitmap is at for this ship
extern int Tmap_show_layers;
extern float Ambient_light;


/////////////////////////////////////////////////////////////////////////////
// CPofViewView drawing
void CPofViewView::OnDraw(CDC* pDC)
{
	CPofViewDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	polymodel * pm = NULL;

	// TODO: add draw code for native data here

	if ( pDoc->m_model_num >= 0 ) {
		RECT client;
		int w, h;

		pm = model_get(pDoc->m_model_num);


		GetClientRect(&client);
		w = client.right - client.left + 1;
		h = client.bottom - client.top + 1;
		if (w>= gr_screen.max_w ) w = gr_screen.max_w-1;
		if (h>= gr_screen.max_h ) h = gr_screen.max_h-1;

		gr_reset_clip();
		gr_set_clip(0,0,w,h);


		gr_set_color(0,0,0);
		gr_clear();
		gr_set_color( 127, 127, 127 );

		float saved_Ambient_light = Ambient_light;

		{
			static vector Global_light_world = { -0.208758f, -0.688253f, 0.694782f };
			light_reset();

			if ( m_lights_on )	{
				light_add_directional( &Global_light_world, 1.0f, 1.0f, 1.0f, 1.0f );
			} else {
				Ambient_light = 0.0f;
			}
		}

		g3_start_frame(1);
		
		g3_set_view_matrix(&m_ViewerPos, &m_ViewerOrient, m_ViewerZoom);

		uint render_flags = 0;
		if ( !m_dolighting ) render_flags |= MR_NO_LIGHTING;
		if ( m_show_outline ) {
			render_flags |= MR_SHOW_OUTLINE;
			model_set_outline_color(0,0,0);
		}

		if ( m_show_shields ){
			render_flags |= MR_SHOW_SHIELDS;
		}

		if ( m_show_invisible_faces )	{
			render_flags |= MR_SHOW_INVISIBLE_FACES;
		}
		
		if (m_show_overwrite){
			Tmap_show_layers = 1;
		} else {
			Tmap_show_layers = 0;
		}

		if ( m_show_pivots ) render_flags |= MR_SHOW_PIVOTS;
		if ( m_show_paths ) render_flags |= MR_SHOW_PATHS;
		if ( m_show_radius ) render_flags |= MR_SHOW_RADIUS;
		if ( !m_smoothing ) render_flags |= MR_NO_SMOOTHING;
		if ( !m_texturing ) render_flags |= MR_NO_TEXTURING;
		if ( m_current_detail_level > 0 ) {
			render_flags |= MR_LOCK_DETAIL;
			model_set_detail_level(m_current_detail_level-1);
		}

		if(m_show_bay_paths) render_flags |= MR_BAY_PATHS;		
		
		if(m_autocenter) render_flags |= MR_AUTOCENTER;

		vector temp_pos = {0.0f, 0.0f, 0.0f };

		model_clear_instance( pDoc->m_model_num );

		model_show_damaged(pDoc->m_model_num, m_show_destroyed_subobjects );

		if ( model_afterburner ){
			model_set_thrust( pDoc->m_model_num, 1.0f, shipp_thruster_bitmap, shipp_thruster_glow_bitmap, shipp_thruster_glow_noise );
		} else {
			model_set_thrust( pDoc->m_model_num, model_thrust, shipp_thruster_bitmap, shipp_thruster_glow_bitmap, shipp_thruster_glow_noise );
		}

		render_flags |= MR_SHOW_THRUSTERS;				

		static int whee = -1;		
		if(whee == -1){
			whee = bm_load("helvig.pcx");
		} 
		if(whee != -1){
			model_set_insignia_bitmap(whee);
		}
		
		if ( m_current_detail_level > 0 )	{
			model_render( pDoc->m_model_num, &m_ObjectOrient, &temp_pos, render_flags );
		} else {
			int i;
			for (i=0; i<pm->num_debris_objects; i++ )	{
				vector tmp = {0.0f, 0.0f, 0.0f };		
				vector tmp1 = pm->submodel[pm->debris_objects[i]].offset;
				model_find_world_point(&tmp, &tmp1, pDoc->m_model_num, -1,&m_ObjectOrient, &temp_pos );
				submodel_render( pDoc->m_model_num, pm->debris_objects[i],&m_ObjectOrient, &tmp, render_flags );
			}
		}

#if 0
		vector hitpos;
		vector tmp1;
		vm_vec_scale_add( &tmp1, &m_ViewerPos, &m_ViewerOrient.fvec, 100.0f );
		int hit = model_check_collision(pDoc->m_model_num,&vmd_identity_matrix,&temp_pos, &m_ViewerPos, &tmp1, &hitpos, 0 );

		if ( hit )	{
			vertex pt;
			ubyte flags;

			flags = g3_rotate_vertex(&pt,&hitpos);

			if (flags == 0) {
				g3_project_vertex(&pt);
				if (!(pt.flags & PF_OVERFLOW))	{
					gr_set_color(128,0,0);
					g3_draw_sphere( &pt, 1.0f );
				}
			}
		}
#endif
		g3_end_frame();
		
		gr_flip_window((uint) pDC->m_hDC, 0, 0, w, h );

		Ambient_light = saved_Ambient_light;		
	}
}

/////////////////////////////////////////////////////////////////////////////
// CPofViewView printing

BOOL CPofViewView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CPofViewView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CPofViewView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CPofViewView diagnostics

#ifdef _DEBUG
void CPofViewView::AssertValid() const
{
	CView::AssertValid();
}

void CPofViewView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPofViewDoc* CPofViewView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPofViewDoc)));
	return (CPofViewDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPofViewView message handlers

void CPofViewView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	key_mark( nFlags&0x7F, 1, 0 );
	
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CPofViewView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	key_mark( nFlags&0x7F, 0, 0 );
	
	CView::OnKeyUp(nChar, nRepCnt, nFlags);
}

extern int pofview_focus;

void CPofViewView::OnSetFocus(CWnd* pOldWnd) 
{
	CView::OnSetFocus(pOldWnd);
	
	// TODO: Add your message handler code here
	key_got_focus();

	pofview_focus++;
}

void CPofViewView::OnKillFocus(CWnd* pNewWnd) 
{
	CView::OnKillFocus(pNewWnd);
	
	// TODO: Add your message handler code here
	key_lost_focus();

	pofview_focus--;

}


void CPofViewView::OnPofOutline() 
{
	m_show_outline = !m_show_outline;
}


void CPofViewView::OnUpdatePofOutline(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck( m_show_outline );
}

void CPofViewView::OnPofLighting() 
{
	m_dolighting = !m_dolighting;
}

void CPofViewView::OnUpdatePofLighting(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck( m_dolighting );
}

void CPofViewView::OnPofPivots() 
{
	m_show_pivots = !m_show_pivots;
	
}

void CPofViewView::OnUpdatePofPivots(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck( m_show_pivots );
}

void CPofViewView::OnDetail1() 
{
	m_current_detail_level = 1;
}

void CPofViewView::OnUpdateDetail1(CCmdUI* pCmdUI) 
{
	CPofViewDoc* pDoc = GetDocument();
	if ( pDoc->m_model_num > -1 )	{
		polymodel * pm = model_get(pDoc->m_model_num);
		if ( (pm->n_detail_levels >= 1) && (m_current_detail_level!=1) )
			pCmdUI->Enable(TRUE);
		else
			pCmdUI->Enable(FALSE);
	}
}

void CPofViewView::OnDetail2() 
{
	m_current_detail_level = 2;
}

void CPofViewView::OnUpdateDetail2(CCmdUI* pCmdUI) 
{
	CPofViewDoc* pDoc = GetDocument();
	if ( pDoc->m_model_num > -1 )	{
		polymodel * pm = model_get(pDoc->m_model_num);
		if ( (pm->n_detail_levels >= 2) && (m_current_detail_level!=2) )
			pCmdUI->Enable(TRUE);
		else
			pCmdUI->Enable(FALSE);
	}
}

void CPofViewView::OnDetail3() 
{
	m_current_detail_level = 3;
}

void CPofViewView::OnUpdateDetail3(CCmdUI* pCmdUI) 
{
	CPofViewDoc* pDoc = GetDocument();
	if ( pDoc->m_model_num > -1 )	{
		polymodel * pm = model_get(pDoc->m_model_num);
		if ( (pm->n_detail_levels >= 3) && (m_current_detail_level!=3) )
			pCmdUI->Enable(TRUE);
		else
			pCmdUI->Enable(FALSE);
	}
}

void CPofViewView::OnDetail4() 
{
	m_current_detail_level = 4;
}

void CPofViewView::OnUpdateDetail4(CCmdUI* pCmdUI) 
{
	CPofViewDoc* pDoc = GetDocument();
	if ( pDoc->m_model_num > -1 )	{
		polymodel * pm = model_get(pDoc->m_model_num);
		if ( (pm->n_detail_levels >= 4) && (m_current_detail_level!=4) )
			pCmdUI->Enable(TRUE);
		else
			pCmdUI->Enable(FALSE);
	}
}

void CPofViewView::OnDetail5() 
{
	m_current_detail_level = 5;
}

void CPofViewView::OnUpdateDetail5(CCmdUI* pCmdUI) 
{
	CPofViewDoc* pDoc = GetDocument();
	if ( pDoc->m_model_num > -1 )	{
		polymodel * pm = model_get(pDoc->m_model_num);
		if ( (pm->n_detail_levels >= 5) && (m_current_detail_level!=5) )
			pCmdUI->Enable(TRUE);
		else
			pCmdUI->Enable(FALSE);
	}
}



void CPofViewView::OnDetail6() 
{
	m_current_detail_level = 6;
}

void CPofViewView::OnUpdateDetail6(CCmdUI* pCmdUI) 
{
	CPofViewDoc* pDoc = GetDocument();
	if ( pDoc->m_model_num > -1 )	{
		polymodel * pm = model_get(pDoc->m_model_num);
		if ( (pm->n_detail_levels >= 6) && (m_current_detail_level!=6) )
			pCmdUI->Enable(TRUE);
		else
			pCmdUI->Enable(FALSE);
	}
}

void CPofViewView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
}


void CPofViewView::OnShowTree() 
{
	// TODO: Add your command handler code here
	CPofViewDoc* pDoc = GetDocument();
	if ( pDoc->m_model_num > -1 )	{
		m_TreeDialog.MyCreate(this);
	}
	
}

void CPofViewView::OnUpdateShowTree(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here

}

void CPofViewView::OnPofPaths() 
{
	m_show_paths = !m_show_paths;
}

void CPofViewView::OnUpdatePofPaths(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck( m_show_paths );
}

void CPofViewView::OnPofRadius() 
{
	m_show_radius = !m_show_radius;

}

void CPofViewView::OnUpdatePofRadius(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck( m_show_radius );
}

void CPofViewView::OnPofOverwrite() 
{
	m_show_overwrite = !m_show_overwrite;
	
}

void CPofViewView::OnUpdatePofOverwrite(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(TRUE);
	pCmdUI->SetCheck( m_show_destroyed_subobjects );
}

void CPofViewView::OnShowDamagedSubobjects() 
{
	m_show_destroyed_subobjects = !m_show_destroyed_subobjects;
}

void CPofViewView::OnUpdateShowDamagedSubobjects(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CPofViewView::OnShowDebris() 
{
	m_current_detail_level = 0;
}

void CPofViewView::OnUpdateShowDebris(CCmdUI* pCmdUI) 
{
	CPofViewDoc* pDoc = GetDocument();
	if ( pDoc->m_model_num > -1 )	{
		polymodel * pm = model_get(pDoc->m_model_num);
		if ( (pm->num_debris_objects >= 1) && (m_current_detail_level!=0) )
			pCmdUI->Enable(TRUE);
		else
			pCmdUI->Enable(FALSE);
	}
}

void CPofViewView::OnMouseMove(UINT nFlags, CPoint point) 
{
	if (m_mouse_inited)	{
		m_mouse_dx = point.x - m_mouse_x;
		m_mouse_dy = point.y - m_mouse_y;
	} else {
		m_mouse_inited = 1;
	}

	m_mouse_x = point.x;
	m_mouse_y = point.y;
	
	CView::OnMouseMove(nFlags, point);
}

void CPofViewView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	m_mouse_down = 1;

	CView::OnLButtonDown(nFlags, point);
}

void CPofViewView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	m_mouse_down = 0;
	
	CView::OnLButtonUp(nFlags, point);
}

void CPofViewView::OnPofSmoothing() 
{
	m_smoothing = !m_smoothing;
}

void CPofViewView::OnUpdatePofSmoothing(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck( m_smoothing );
}

void CPofViewView::OnPofTexturing() 
{
	m_texturing = !m_texturing;
}

void CPofViewView::OnUpdatePofTexturing(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck( m_texturing );
}

void CPofViewView::OnPofShields() 
{
	m_show_shields = !m_show_shields;
}

void CPofViewView::OnUpdatePofShields(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck( m_show_shields );
}

void CPofViewView::OnToggleLighting() 
{
	m_lights_on = !m_lights_on;
}

void CPofViewView::OnUpdateToggleLighting(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck( m_lights_on	 );
}


void CPofViewView::OnInvisiblefaces() 
{
	m_show_invisible_faces = !m_show_invisible_faces;
}

void CPofViewView::OnUpdateInvisiblefaces(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck( m_show_invisible_faces );
}

void CPofViewView::OnBayPaths() 
{
	m_show_bay_paths = !m_show_bay_paths;
}

void CPofViewView::OnUpdateBayPaths(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck( m_show_bay_paths );
}

void CPofViewView::OnAutocenter() 
{
	m_autocenter = !m_autocenter;
}

void CPofViewView::OnUpdateAutocenter(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck( m_autocenter );
}

void CPofViewView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	if ((cx > 0) && (cy > 0)) {
		gr_init(GR_640, GR_SOFTWARE, 8, cx, cy);
	}
}