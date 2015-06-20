/*
 * Copyright (C) Volition, Inc. 1999.  All rights reserved.
 *
 * All source code herein is the property of Volition, Inc. You may not sell 
 * or otherwise commercially exploit the source or things you created based on the 
 * source.
 *
*/

/*
 * $Logfile: /Freespace2/code/Fred2/BgBitmapDlg.cpp $
 * $Revision: 11 $
 * $Date: 7/02/99 4:30p $
 * $Author: Dave $
 *
 * Background space images manager dialog
 *
 * $Log: /Freespace2/code/Fred2/BgBitmapDlg.cpp $
 * 
 * 11    7/02/99 4:30p Dave
 * Much more sophisticated lightning support.
 * 
 * 10    6/08/99 5:42p Dave
 * Fixed background bitmap division stuff.
 * 
 * 9     6/03/99 6:42p Dave
 * 
 * 8     6/03/99 6:37p Dave
 * More TNT fun. Made perspective bitmaps more flexible.
 * 
 * 7     5/09/99 6:00p Dave
 * Lots of cool new effects. E3 build tweaks.
 * 
 * 6     4/26/99 8:47p Dave
 * Made all pof related nebula stuff customizable through Fred.
 * 
 * 5     4/07/99 6:21p Dave
 * Fred and Freespace support for multiple background bitmaps and suns.
 * Fixed link errors on all subprojects. Moved encrypt_init() to
 * cfile_init() and lcl_init(), since its safe to call twice.
 * 
 * 4     1/25/99 5:03a Dave
 * First run of stealth, AWACS and TAG missile support. New mission type
 * :)
 * 
 * 3     11/14/98 5:37p Dave
 * Put in support for full nebulas.
 * 
 * 2     10/07/98 6:28p Dave
 * Initial checkin. Renamed all relevant stuff to be Fred2 instead of
 * Fred. Globalized mission and campaign file extensions. Removed Silent
 * Threat specific code.
 *   
 * 18    4/13/98 10:25p Hoffoss
 * Added a flag for subspace missions, and for aboard the Galatea or
 * Bastion.
 * 
 * 17    1/14/98 8:56a John
 * Removed old nebula palette code that didn't matter what HUD colors were
 * loaded.
 * 
 * 16    12/08/97 4:48p Hoffoss
 * Moved starfield editor controls to background editor.
 * 
 * 15    11/25/97 4:48p Johnson
 * Fixed bug with nebula selection.
 * 
 * 14    11/25/97 11:40a Hoffoss
 * Added support for nebula placement editing.
 * 
 * 13    11/23/97 6:06p Hoffoss
 * Renamed background bitmap editor to just background editor.
 * 
 * 12    11/21/97 2:55p Hoffoss
 * Added Nebula support to Fred.  Implemented loading and saving nebula
 * info to/from mission files.
 * 
 * 11    6/11/97 3:26p Hoffoss
 * Added better verification of bitmap filename to BG editor.
 * 
 * 10    4/17/97 2:01p Hoffoss
 * All dialog box window states are saved between sessions now.
 * 
 * 9     3/31/97 6:07p Hoffoss
 * Fixed several errors, including BG editor not graying fields, BG editor
 * not updating image when changed, Removed obsolete data from Weapon
 * editor, priority not being saved when missions saved, priority not
 * editable in initial orders editor.
 * 
 * 8     3/27/97 2:24p Hoffoss
 * Fixed bug in image not updating when new image selected from listbox of
 * combo box.
 * 
 * 7     3/21/97 4:24p Hoffoss
 * Fixed bug in changing image to an external image file.
 * 
 * 6     3/17/97 1:54p Hoffoss
 * fixed bugs in BG editor, and added delete button functionality.
 * 
 * 5     3/12/97 4:33p Hoffoss
 * added spin controls to orient editor, light intensity level can be
 * specified in BG editor.
 * 
 * 4     2/21/97 5:34p Hoffoss
 * Added extensive modification detection and fixed a bug in initial
 * orders editor.
 * 
 * 3     2/04/97 3:09p Hoffoss
 * Background bitmap editor implemented fully.
 * 
 * 2     1/30/97 2:24p Hoffoss
 * Added remaining mission file structures and implemented load/save of
 * them.
 *
 * $NoKeywords: $
 */

#include "stdafx.h"
#include "fred.h"
#include "BgBitmapDlg.h"
#include "Starfield.h"
#include "BmpMan.h"
#include "FredView.h"
#include "FredDoc.h"
#include "PalMan.h"
#include "Nebula.h"
#include "Neb.h"
#include "NebLightning.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// bg_bitmap_dlg dialog

bg_bitmap_dlg::bg_bitmap_dlg(CWnd* pParent) : CDialog(bg_bitmap_dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(bg_bitmap_dlg)		
	m_neb_intensity = _T("");	
	m_nebula_color = -1;
	m_nebula_index = -1;
	m_bank = 0;
	m_heading = 0;
	m_pitch = 0;
	m_subspace = FALSE;
	m_fullneb = FALSE;

	m_neb2_texture = 0;
	
	for(int idx=0; idx<MAX_NEB2_POOFS; idx++){
		m_poof[idx] = Neb2_poof_flags & (1<<idx) ? 1 : 0;
	}

	s_pitch = 0;
	s_bank = 0;
	s_heading = 0;
	s_scale = 1.0f;	
	s_index = -1;

	b_pitch = 0;
	b_bank = 0;
	b_heading = 0;
	b_scale_x = 1.0f; b_scale_y = 1.0f;
	b_div_x = 1; b_div_y = 1;
	b_index = -1;
	//}}AFX_DATA_INIT	
}

void bg_bitmap_dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(bg_bitmap_dlg)			
	DDX_CBIndex(pDX, IDC_NEBCOLOR, m_nebula_color);
	DDX_CBIndex(pDX, IDC_NEBPATTERN, m_nebula_index);
	DDX_Text(pDX, IDC_BANK, m_bank);
	DDX_Text(pDX, IDC_HEADING, m_heading);
	DDX_Text(pDX, IDC_PITCH, m_pitch);
	DDX_Text(pDX, IDC_NEB2_INTENSITY, m_neb_intensity);
	DDX_Control(pDX, IDC_SLIDER1, m_slider);
	DDX_Check(pDX, IDC_SUBSPACE, m_subspace);
	DDX_Check(pDX, IDC_FULLNEB, m_fullneb);

	DDX_CBIndex(pDX, IDC_NEB2_TEXTURE, m_neb2_texture);

	DDX_Text(pDX, IDC_SUN1, s_name);
	DDX_Text(pDX, IDC_SUN1_P, s_pitch);
	DDV_MinMaxInt(pDX, s_pitch, 0, 359);
	DDX_Text(pDX, IDC_SUN1_B, s_bank);
	DDV_MinMaxInt(pDX, s_bank, 0, 359);
	DDX_Text(pDX, IDC_SUN1_H, s_heading);
	DDV_MinMaxInt(pDX, s_heading, 0, 359);
	DDX_Text(pDX, IDC_SUN1_SCALE, s_scale);
	DDV_MinMaxFloat(pDX, s_scale, 0.1f, 50.0f);

	DDX_Text(pDX, IDC_SBITMAP, b_name);
	DDX_Text(pDX, IDC_SBITMAP_P, b_pitch);
	DDV_MinMaxInt(pDX, b_pitch, 0, 359);
	DDX_Text(pDX, IDC_SBITMAP_B, b_bank);
	DDV_MinMaxInt(pDX, b_bank, 0, 359);
	DDX_Text(pDX, IDC_SBITMAP_H, b_heading);
	DDV_MinMaxInt(pDX, b_heading, 0, 359);
	DDX_Text(pDX, IDC_SBITMAP_SCALE_X, b_scale_x);
	DDV_MinMaxFloat(pDX, b_scale_x, 0.001f, 18.0f);
	DDX_Text(pDX, IDC_SBITMAP_SCALE_Y, b_scale_y);
	DDV_MinMaxFloat(pDX, b_scale_y, 0.001f, 18.0f);
	DDX_Text(pDX, IDC_SBITMAP_DIV_X, b_div_x);
	DDV_MinMaxInt(pDX, b_div_x, 1, 5);
	DDX_Text(pDX, IDC_SBITMAP_DIV_Y, b_div_y);
	DDV_MinMaxInt(pDX, b_div_y, 1, 5);

	DDX_Check(pDX, IDC_POOF0, m_poof[0]);
	DDX_Check(pDX, IDC_POOF1, m_poof[1]);
	DDX_Check(pDX, IDC_POOF2, m_poof[2]);
	DDX_Check(pDX, IDC_POOF3, m_poof[3]);
	DDX_Check(pDX, IDC_POOF4, m_poof[4]);
	DDX_Check(pDX, IDC_POOF5, m_poof[5]);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(bg_bitmap_dlg, CDialog)
	//{{AFX_MSG_MAP(bg_bitmap_dlg)
	ON_WM_CLOSE()	
	ON_CBN_SELCHANGE(IDC_NEBCOLOR, OnSelchangeNebcolor)
	ON_CBN_SELCHANGE(IDC_NEBPATTERN, OnSelchangeNebpattern)
	ON_BN_CLICKED(IDC_FULLNEB, OnFullNeb)
	ON_WM_HSCROLL()

	ON_LBN_SELCHANGE(IDC_SUN1_LIST, OnSunChange)
	ON_CBN_SELCHANGE(IDC_SUN1, OnSunDropdownChange)
	ON_BN_CLICKED(IDC_ADD_SUN, OnAddSun)
	ON_BN_CLICKED(IDC_DEL_SUN, OnDelSun)

	ON_LBN_SELCHANGE(IDC_SBITMAP_LIST, OnBitmapChange)
	ON_CBN_SELCHANGE(IDC_SBITMAP, OnBitmapDropdownChange)
	ON_BN_CLICKED(IDC_ADD_SBITMAP, OnAddBitmap)
	ON_BN_CLICKED(IDC_DEL_SBITMAP, OnDelBitmap)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// bg_bitmap_dlg message handlers

void bg_bitmap_dlg::create()
{
	char buf[40];
	int i;
	CComboBox *box;

	CDialog::Create(bg_bitmap_dlg::IDD);
	theApp.init_window(&Bg_wnd_data, this);
	
	box = (CComboBox *) GetDlgItem(IDC_NEBCOLOR);
	for (i=0; i<NUM_NEBULA_COLORS; i++){
		box->AddString(Nebula_colors[i]);
	}	

	m_slider.SetRange(100, MAX_STARS);
	m_slider.SetPos(Num_stars);
	sprintf(buf, "%d", Num_stars);
	GetDlgItem(IDC_TOTAL)->SetWindowText(buf);

	build_nebfile_list();	

	// setup neb poof names
	GetDlgItem(IDC_POOF0)->SetWindowText(Neb2_poof_filenames[0]);	
	GetDlgItem(IDC_POOF1)->SetWindowText(Neb2_poof_filenames[1]);
	GetDlgItem(IDC_POOF2)->SetWindowText(Neb2_poof_filenames[2]);
	GetDlgItem(IDC_POOF3)->SetWindowText(Neb2_poof_filenames[3]);
	GetDlgItem(IDC_POOF4)->SetWindowText(Neb2_poof_filenames[4]);
	GetDlgItem(IDC_POOF5)->SetWindowText(Neb2_poof_filenames[5]);
	for(i=0; i<MAX_NEB2_BITMAPS; i++){
		if(strlen(Neb2_bitmap_filenames[i]) > 0){
			((CComboBox*)GetDlgItem(IDC_NEB2_TEXTURE))->AddString(Neb2_bitmap_filenames[i]);
		}
	}
	// if we have a texture selected already
	if(strlen(Neb2_texture_name) > 0){
		m_neb2_texture = ((CComboBox*)GetDlgItem(IDC_NEB2_TEXTURE))->SelectString(-1, Neb2_texture_name);
		if(m_neb2_texture == CB_ERR){
			((CComboBox*)GetDlgItem(IDC_NEB2_TEXTURE))->SetCurSel(0);
			m_neb2_texture = 0;
		}
	} else {
		((CComboBox*)GetDlgItem(IDC_NEB2_TEXTURE))->SetCurSel(0);
	}

	// setup lightning storm names
	((CComboBox*)GetDlgItem(IDC_NEB2_LIGHTNING))->ResetContent();
	((CComboBox*)GetDlgItem(IDC_NEB2_LIGHTNING))->AddString(CString("none"));
	for(i=0; i<Num_storm_types; i++){
		((CComboBox*)GetDlgItem(IDC_NEB2_LIGHTNING))->AddString(CString(Storm_types[i].name));
	}
	((CComboBox*)GetDlgItem(IDC_NEB2_LIGHTNING))->SelectString(-1, Mission_parse_storm_name);
		
	// if the nebula intensity wasn't set before - set it now
	if(Neb2_awacs < 0.0f){
		m_neb_intensity = CString("3000");
	} else {
		char whee[255] = "";
		m_neb_intensity = CString(itoa((int)Neb2_awacs, whee, 10));
	}
		
	// determine if a full Neb2 is active - load in the full nebula filenames or the partial neb
	// filenames
	m_fullneb = (The_mission.flags & MISSION_FLAG_FULLNEB) ? 1 : 0;
	if(m_fullneb){
		((CButton*)GetDlgItem(IDC_FULLNEB))->SetCheck(1);					
	} else {
		// since there is no "none" option for the full nebulas
		m_nebula_index = Nebula_index + 1;		
	
		m_nebula_color = Mission_palette;
		if (Nebula_index < 0){
			GetDlgItem(IDC_NEBCOLOR)->EnableWindow(FALSE);
		}

		m_pitch = Nebula_pitch;
		m_bank = Nebula_bank;
		m_heading = Nebula_heading;
	}

	// setup sun and sunglow controls
	sun_data_init();	

	// setup bitmap info
	bitmap_data_init();
	
	// determine if subspace is active
	m_subspace = (The_mission.flags & MISSION_FLAG_SUBSPACE) ? 1 : 0;	

	UpdateData(FALSE);
	OnFullNeb();
	update_data();
	update_map_window();
	set_modified();
}

void bg_bitmap_dlg::OnClose() 
{
	UpdateData(TRUE);
	Mission_palette = m_nebula_color;
	
	if(m_fullneb){		
		The_mission.flags |= MISSION_FLAG_FULLNEB;
		Neb2_awacs = (float)atoi((LPCSTR)m_neb_intensity);

		// override dumb values with reasonable ones
		if(Neb2_awacs <= 0.00000001f){
			Neb2_awacs = 3000.0f;
		}

		// store poof flags
		Neb2_poof_flags = 0;
		for(int idx=0; idx<MAX_NEB2_POOFS; idx++){
			if(m_poof[idx]){
				Neb2_poof_flags |= (1<<idx);
			}
		}

		// get the bitmap name
		strcpy(Neb2_texture_name, Neb2_bitmap_filenames[m_neb2_texture]);

		// init the nebula
		neb2_level_init();
	} else {
		The_mission.flags &= ~MISSION_FLAG_FULLNEB;
		Nebula_index = m_nebula_index - 1;
		Neb2_awacs = -1.0f;
		strcpy(Neb2_texture_name, "");
	}

	// get selected storm
	((CComboBox*)GetDlgItem(IDC_NEB2_LIGHTNING))->GetLBText(((CComboBox*)GetDlgItem(IDC_NEB2_LIGHTNING))->GetCurSel(), Mission_parse_storm_name);

	Nebula_pitch = m_pitch;
	Nebula_bank = m_bank;
	Nebula_heading = m_heading;
	if (Nebula_index >= 0){
		nebula_init(Nebula_filenames[Nebula_index], m_pitch, m_bank, m_heading);
	} else {
		nebula_close();
	}

	if (m_subspace){
		The_mission.flags |= MISSION_FLAG_SUBSPACE;				
	} else {
		The_mission.flags &= ~MISSION_FLAG_SUBSPACE;		
	}

	// close sun data
	sun_data_close();

	// close bitmap data
	bitmap_data_close();

	theApp.record_window_data(&Bg_wnd_data, this);
	delete Bg_bitmap_dialog;
	Bg_bitmap_dialog = NULL;
}

void bg_bitmap_dlg::update_data(int update)
{
	if (update){
		UpdateData(TRUE);
	}

	UpdateData(FALSE);	
}

void bg_bitmap_dlg::OnSelchangeNebcolor() 
{
	CWaitCursor wait;

	UpdateData(TRUE);
	Mission_palette = m_nebula_color;


	char palette_filename[1024];

	Assert( Mission_palette >= 0 );
	Assert( Mission_palette <= 98 );

	sprintf( palette_filename, "gamepalette%d-%02d", 1, Mission_palette+1 );

	mprintf(( "Loading palette %s\n", palette_filename ));

	palette_load_table(palette_filename);
	
	Update_window = 1;
}

void bg_bitmap_dlg::OnSelchangeNebpattern() 
{
	CWaitCursor wait;

	UpdateData(TRUE);

	// fullneb indexes differently	
	Nebula_index = m_nebula_index - 1;			

	GetDlgItem(IDC_NEBCOLOR)->EnableWindow(m_nebula_index ? TRUE : FALSE);
	if (Nebula_index >= 0){		
		nebula_init(Nebula_filenames[Nebula_index], m_pitch, m_bank, m_heading);		
	} else {
		nebula_close();
	}

	Update_window = 1;
}

void bg_bitmap_dlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar) 
{
	char buf[40];

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);

	MODIFY(Num_stars, m_slider.GetPos());
	sprintf(buf, "%d", Num_stars);
	GetDlgItem(IDC_TOTAL)->SetWindowText(buf);
}

// when the user toggled the "Full Nebula" button
void bg_bitmap_dlg::OnFullNeb()
{		
	// determine what state we're in	
	UpdateData(TRUE);
	if(m_fullneb){
		// enable all fullneb controls
		GetDlgItem(IDC_NEB2_INTENSITY)->EnableWindow(TRUE);
		GetDlgItem(IDC_NEB2_TEXTURE)->EnableWindow(TRUE);
		GetDlgItem(IDC_NEB2_LIGHTNING)->EnableWindow(TRUE);
		GetDlgItem(IDC_POOF0)->EnableWindow(TRUE);
		GetDlgItem(IDC_POOF1)->EnableWindow(TRUE);
		GetDlgItem(IDC_POOF2)->EnableWindow(TRUE);
		GetDlgItem(IDC_POOF3)->EnableWindow(TRUE);
		GetDlgItem(IDC_POOF4)->EnableWindow(TRUE);
		GetDlgItem(IDC_POOF5)->EnableWindow(TRUE);						

		// disable non-fullneb controls
		GetDlgItem(IDC_NEBPATTERN)->EnableWindow(FALSE);
		GetDlgItem(IDC_NEBCOLOR)->EnableWindow(FALSE);
		GetDlgItem(IDC_PITCH)->EnableWindow(FALSE);
		GetDlgItem(IDC_BANK)->EnableWindow(FALSE);
		GetDlgItem(IDC_HEADING)->EnableWindow(FALSE);

		// check all relevant poofs		
		((CButton*)GetDlgItem(IDC_POOF0))->SetCheck(FALSE);
		if(m_poof[0]){
			((CButton*)GetDlgItem(IDC_POOF0))->SetCheck(TRUE);
		}
		((CButton*)GetDlgItem(IDC_POOF1))->SetCheck(FALSE);
		if(m_poof[1]){
			((CButton*)GetDlgItem(IDC_POOF1))->SetCheck(TRUE);
		}
		((CButton*)GetDlgItem(IDC_POOF2))->SetCheck(FALSE);
		if(m_poof[2]){
			((CButton*)GetDlgItem(IDC_POOF2))->SetCheck(TRUE);
		}
		((CButton*)GetDlgItem(IDC_POOF3))->SetCheck(FALSE);
		if(m_poof[3]){
			((CButton*)GetDlgItem(IDC_POOF3))->SetCheck(TRUE);
		}
		((CButton*)GetDlgItem(IDC_POOF4))->SetCheck(FALSE);
		if(m_poof[4]){
			((CButton*)GetDlgItem(IDC_POOF4))->SetCheck(TRUE);
		}
		((CButton*)GetDlgItem(IDC_POOF5))->SetCheck(FALSE);
		if(m_poof[5]){
			((CButton*)GetDlgItem(IDC_POOF5))->SetCheck(TRUE);
		}
	} else {
		// enable all non-fullneb controls
		GetDlgItem(IDC_NEBPATTERN)->EnableWindow(TRUE);
		GetDlgItem(IDC_NEBCOLOR)->EnableWindow(TRUE);
		GetDlgItem(IDC_PITCH)->EnableWindow(TRUE);
		GetDlgItem(IDC_BANK)->EnableWindow(TRUE);
		GetDlgItem(IDC_HEADING)->EnableWindow(TRUE);		

		// disable all fullneb controls
		GetDlgItem(IDC_NEB2_INTENSITY)->EnableWindow(FALSE);
		GetDlgItem(IDC_NEB2_TEXTURE)->EnableWindow(FALSE);
		GetDlgItem(IDC_NEB2_LIGHTNING)->EnableWindow(FALSE);
		GetDlgItem(IDC_POOF0)->EnableWindow(FALSE);
		GetDlgItem(IDC_POOF1)->EnableWindow(FALSE);
		GetDlgItem(IDC_POOF2)->EnableWindow(FALSE);
		GetDlgItem(IDC_POOF3)->EnableWindow(FALSE);
		GetDlgItem(IDC_POOF4)->EnableWindow(FALSE);
		GetDlgItem(IDC_POOF5)->EnableWindow(FALSE);		
	}		
}

// clear and build the nebula filename list appropriately
void bg_bitmap_dlg::build_nebfile_list()
{
	int i;
	CComboBox *box = (CComboBox *) GetDlgItem(IDC_NEBPATTERN);

	// wacky
	Assert(box != NULL);
	if(box == NULL){
		return;
	}
	
	// clear the box
	box->ResetContent();

	// add all necessary strings		
	box->AddString("None");
	for (i=0; i<NUM_NEBULAS; i++){
		box->AddString(Nebula_filenames[i]);
	}	

	// select the first elementccombobox
	box->SetCurSel(0);
	OnSelchangeNebpattern();
}

void bg_bitmap_dlg::sun_data_init()
{
	int idx;

	// force the range for pitch bank and heading
	((CSpinButtonCtrl *)GetDlgItem(IDC_SUN1_P_SPIN))->SetRange(0, 359);
	((CSpinButtonCtrl *)GetDlgItem(IDC_SUN1_B_SPIN))->SetRange(0, 359);
	((CSpinButtonCtrl *)GetDlgItem(IDC_SUN1_H_SPIN))->SetRange(0, 359);	

	// add all suns to the drop down
	idx=0;
	while((idx < MAX_STARFIELD_BITMAPS) && (Sun_bitmaps[idx].bitmap != -1)){
		((CComboBox*)GetDlgItem(IDC_SUN1))->AddString(Sun_bitmaps[idx].filename);
		
		// next
		idx++;
	}
	
	// add all suns by bitmap filename to the list
	for(idx=0; idx<Num_suns; idx++){	
		((CListBox*)GetDlgItem(IDC_SUN1_LIST))->AddString(Suns[idx].filename);
	}		

	// if we have at least one item, select it
	if(Num_suns > 0){
		((CListBox*)GetDlgItem(IDC_SUN1_LIST))->SetCurSel(0);
		OnSunChange();
	}
}

void bg_bitmap_dlg::sun_data_close()
{	
	// if there is an active sun, save it
	sun_data_save_current();	
}

void bg_bitmap_dlg::sun_data_save_current()
{	
	// if we have an active item
	if(s_index >= 0){
		// read out of the controls
		UpdateData(TRUE);

		// store the data
		strcpy(Suns[s_index].filename, (const char*)s_name);
		Suns[s_index].scale_x = (float)s_scale;
		Suns[s_index].scale_y = 1.0f;
		Suns[s_index].div_x = 1;
		Suns[s_index].div_y = 1;
		Suns[s_index].ang.p = (float)fl_radian(s_pitch);
		Suns[s_index].ang.b = (float)fl_radian(s_bank);
		Suns[s_index].ang.h = (float)fl_radian(s_heading);		
	}
}

void bg_bitmap_dlg::OnSunChange()
{	
	int drop_index;

	// save the current sun
	sun_data_save_current();

	// select the new one
	s_index = ((CListBox*)GetDlgItem(IDC_SUN1_LIST))->GetCurSel();

	// setup data	
	if(s_index >= 0){				
		s_pitch = (int)fl_degrees(Suns[s_index].ang.p);
		s_bank = (int)fl_degrees(Suns[s_index].ang.b);
		s_heading = (int)fl_degrees(Suns[s_index].ang.h);
		s_scale = Suns[s_index].scale_x;		
		s_name = CString(Suns[s_index].filename);

		// stuff back into the controls
		UpdateData(FALSE);

		// select the proper item from the dropdown
		drop_index = ((CComboBox*)GetDlgItem(IDC_SUN1))->FindString( -1, Suns[s_index].filename );
		Assert(drop_index != CB_ERR);
		if(drop_index != CB_ERR){
			((CComboBox*)GetDlgItem(IDC_SUN1))->SetCurSel(drop_index);
		}
	}
}

void bg_bitmap_dlg::OnAddSun()
{
	starfield_bitmap_instance *b;

	// if we've already reached max suns
	if(Num_suns >= MAX_STARFIELD_BITMAPS){
		MessageBox("Max suns reached!");
		return;
	}

	// save any current
	sun_data_save_current();
	
	// select the first sun by default
	b = &Suns[Num_suns++];
	strcpy(b->filename, Sun_bitmaps[0].filename);
	b->scale_x = 1.0f;
	b->scale_y = 1.0f;
	b->div_x = 1;
	b->div_y = 1;
	b->ang.p = 0;
	b->ang.b = 0;
	b->ang.h = 0;

	// add to the listbox and select it
	int add_index = ((CListBox*)GetDlgItem(IDC_SUN1_LIST))->AddString(b->filename);
	((CListBox*)GetDlgItem(IDC_SUN1_LIST))->SetCurSel(add_index);
	
	// call the OnSunChange function to setup all relvant data in the class
	OnSunChange();
}

void bg_bitmap_dlg::OnDelSun()
{
	int idx;

	// if we don't have an active item
	if(s_index < 0){
		return;
	}
	
	// remove the item from the list
	((CListBox*)GetDlgItem(IDC_SUN1_LIST))->DeleteString(s_index);

	// remove it from the list
	for(idx=s_index; idx<Num_suns-1; idx++){
		Suns[idx] = Suns[idx+1];
		strcpy(Suns[idx].filename, Suns[idx+1].filename);
	}

	// decrement the count
	Num_suns--;

	// no item selected, let the message handler assign a new one
	s_index = -1;
}

void bg_bitmap_dlg::OnSunDropdownChange()
{	
	// if we have no active sun, do nothing
	if(s_index < 0){
		return;
	}

	int new_index = ((CComboBox*)GetDlgItem(IDC_SUN1))->GetCurSel();
	Assert(new_index != CB_ERR);

	// get the new string
	if(new_index != CB_ERR){
		((CComboBox*)GetDlgItem(IDC_SUN1))->GetLBText(new_index, s_name);

		// change the name of the string in the listbox
		((CListBox*)GetDlgItem(IDC_SUN1_LIST))->DeleteString(s_index);
		((CListBox*)GetDlgItem(IDC_SUN1_LIST))->InsertString(s_index, (const char*)s_name);
	}	
}

void bg_bitmap_dlg::bitmap_data_init()
{
	int idx;

	// force the range for pitch bank and heading
	((CSpinButtonCtrl *)GetDlgItem(IDC_SBITMAP_P_SPIN))->SetRange(0, 359);
	((CSpinButtonCtrl *)GetDlgItem(IDC_SBITMAP_B_SPIN))->SetRange(0, 359);
	((CSpinButtonCtrl *)GetDlgItem(IDC_SBITMAP_H_SPIN))->SetRange(0, 359);	

	// add all suns to the drop down
	idx=0;
	while((idx < MAX_STARFIELD_BITMAPS) && (Starfield_bitmaps[idx].bitmap != -1)){
		((CComboBox*)GetDlgItem(IDC_SBITMAP))->AddString(Starfield_bitmaps[idx].filename);
		
		// next
		idx++;
	}
	
	// add all suns by bitmap filename to the list
	for(idx=0; idx<Num_starfield_bitmaps; idx++){	
		((CListBox*)GetDlgItem(IDC_SBITMAP_LIST))->AddString(Starfield_bitmap_instance[idx].filename);
	}		

	// if we have at least one item, select it
	if(Num_starfield_bitmaps > 0){
		((CListBox*)GetDlgItem(IDC_SBITMAP_LIST))->SetCurSel(0);
		OnBitmapChange();
	}
}

void bg_bitmap_dlg::bitmap_data_close()
{
	// if there is an active sun, save it
	bitmap_data_save_current();	
}

void bg_bitmap_dlg::bitmap_data_save_current()
{
	// if we have an active item
	if(b_index >= 0){
		// read out of the controls
		UpdateData(TRUE);

		// store the data
		strcpy(Starfield_bitmap_instance[b_index].filename, (const char*)b_name);
		Starfield_bitmap_instance[b_index].scale_x = (float)b_scale_x;
		Starfield_bitmap_instance[b_index].scale_y = (float)b_scale_y;
		Starfield_bitmap_instance[b_index].div_x = b_div_x;
		Starfield_bitmap_instance[b_index].div_y = b_div_y;
		Starfield_bitmap_instance[b_index].ang.p = (float)fl_radian(b_pitch);
		Starfield_bitmap_instance[b_index].ang.b = (float)fl_radian(b_bank);
		Starfield_bitmap_instance[b_index].ang.h = (float)fl_radian(b_heading);
	}
}

void bg_bitmap_dlg::OnBitmapChange()
{
	int drop_index;

	// save the current bitmap
	bitmap_data_save_current();

	// select the new one
	b_index = ((CListBox*)GetDlgItem(IDC_SBITMAP_LIST))->GetCurSel();

	// setup data	
	if(b_index >= 0){		
		b_pitch = (int)fl_degrees(Starfield_bitmap_instance[b_index].ang.p);
		b_bank = (int)fl_degrees(Starfield_bitmap_instance[b_index].ang.b);
		b_heading = (int)fl_degrees(Starfield_bitmap_instance[b_index].ang.h);
		b_scale_x = Starfield_bitmap_instance[b_index].scale_x;
		b_scale_y = Starfield_bitmap_instance[b_index].scale_y;
		b_div_x = Starfield_bitmap_instance[b_index].div_x;
		b_div_y = Starfield_bitmap_instance[b_index].div_y;
		b_name = CString(Starfield_bitmap_instance[b_index].filename);

		// stuff back into the controls
		UpdateData(FALSE);

		// select the proper item from the dropdown
		drop_index = ((CComboBox*)GetDlgItem(IDC_SBITMAP))->FindString( -1, Starfield_bitmap_instance[b_index].filename );
		Assert(drop_index != CB_ERR);
		if(drop_index != CB_ERR){
			((CComboBox*)GetDlgItem(IDC_SBITMAP))->SetCurSel(drop_index);
		}
	}
}

void bg_bitmap_dlg::OnAddBitmap()
{
	starfield_bitmap_instance *b;

	// if we've already reached max bitmaps
	if(Num_starfield_bitmaps >= MAX_STARFIELD_BITMAPS){
		MessageBox("Max starfield bitmaps reached!");
		return;
	}

	// save any current
	bitmap_data_save_current();
	
	// select the first sun by default
	b = &Starfield_bitmap_instance[Num_starfield_bitmaps++];
	strcpy(b->filename, Starfield_bitmaps[0].filename);
	b->scale_x = 1.0f;
	b->scale_y = 1.0f;
	b->div_x = 1;
	b->div_y = 1;
	b->ang.p = 0;
	b->ang.b = 0;
	b->ang.h = 0;

	// add to the listbox and select it
	int add_index = ((CListBox*)GetDlgItem(IDC_SBITMAP_LIST))->AddString(b->filename);
	((CListBox*)GetDlgItem(IDC_SBITMAP_LIST))->SetCurSel(add_index);
	
	// call the OnBitmapChange function to setup all relvant data in the class
	OnBitmapChange();
}

void bg_bitmap_dlg::OnDelBitmap()
{
	int idx;

	// if we don't have an active item
	if(b_index < 0){
		return;
	}
	
	// remove the item from the list
	((CListBox*)GetDlgItem(IDC_SBITMAP_LIST))->DeleteString(b_index);

	// remove it from the list
	for(idx=b_index; idx<Num_starfield_bitmaps-1; idx++){
		Starfield_bitmap_instance[idx] = Starfield_bitmap_instance[idx+1];
		strcpy(Starfield_bitmap_instance[idx].filename, Starfield_bitmap_instance[idx+1].filename);
	}

	// decrement the count
	Num_starfield_bitmaps--;

	// no item selected, let the message handler assign a new one
	b_index = -1;
}

void bg_bitmap_dlg::OnBitmapDropdownChange()
{
	// if we have no active bitmap, do nothing
	if(b_index < 0){
		return;
	}

	int new_index = ((CComboBox*)GetDlgItem(IDC_SBITMAP))->GetCurSel();
	Assert(new_index != CB_ERR);

	// get the new string
	if(new_index != CB_ERR){
		((CComboBox*)GetDlgItem(IDC_SBITMAP))->GetLBText(new_index, b_name);

		// change the name of the string in the listbox
		((CListBox*)GetDlgItem(IDC_SBITMAP_LIST))->DeleteString(b_index);
		((CListBox*)GetDlgItem(IDC_SBITMAP_LIST))->InsertString(b_index, (const char*)b_name);
	}
}
