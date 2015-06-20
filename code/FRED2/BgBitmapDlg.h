/*
 * Copyright (C) Volition, Inc. 1999.  All rights reserved.
 *
 * All source code herein is the property of Volition, Inc. You may not sell 
 * or otherwise commercially exploit the source or things you created based on the 
 * source.
 *
*/

/*
 * $Logfile: /Freespace2/code/Fred2/BgBitmapDlg.h $
 * $Revision: 8 $
 * $Date: 7/02/99 4:30p $
 * $Author: Dave $
 *
 * Background space images manager dialog
 *
 * $Log: /Freespace2/code/Fred2/BgBitmapDlg.h $
 * 
 * 8     7/02/99 4:30p Dave
 * Much more sophisticated lightning support.
 * 
 * 7     6/03/99 6:37p Dave
 * More TNT fun. Made perspective bitmaps more flexible.
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
 * 1     10/07/98 3:01p Dave
 * 
 * 1     10/07/98 2:59p Dave
 * 
 * 12    4/13/98 10:25p Hoffoss
 * Added a flag for subspace missions, and for aboard the Galatea or
 * Bastion.
 * 
 * 11    12/08/97 4:48p Hoffoss
 * Moved starfield editor controls to background editor.
 * 
 * 10    11/25/97 11:40a Hoffoss
 * Added support for nebula placement editing.
 * 
 * 9     11/21/97 2:55p Hoffoss
 * Added Nebula support to Fred.  Implemented loading and saving nebula
 * info to/from mission files.
 * 
 * 8     3/31/97 6:07p Hoffoss
 * Fixed several errors, including BG editor not graying fields, BG editor
 * not updating image when changed, Removed obsolete data from Weapon
 * editor, priority not being saved when missions saved, priority not
 * editable in initial orders editor.
 * 
 * 7     3/27/97 2:24p Hoffoss
 * Fixed bug in image not updating when new image selected from listbox of
 * combo box.
 * 
 * 6     3/21/97 4:24p Hoffoss
 * Fixed bug in changing image to an external image file.
 * 
 * 5     3/17/97 1:54p Hoffoss
 * fixed bugs in BG editor, and added delete button functionality.
 * 
 * 4     3/12/97 4:33p Hoffoss
 * added spin controls to orient editor, light intensity level can be
 * specified in BG editor.
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

#ifndef _BG_BITMAP_DLG_H
#define _BG_BITMAP_DLG_H

/////////////////////////////////////////////////////////////////////////////
// bg_bitmap_dlg dialog

class bg_bitmap_dlg : public CDialog
{
// Construction
public:
	void update_data(int update = 1);
	void create();

	// sun data functions
	void sun_data_init();
	void sun_data_close();
	void sun_data_save_current();

	// bitmap data functions
	void bitmap_data_init();
	void bitmap_data_close();
	void bitmap_data_save_current();

	bg_bitmap_dlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(bg_bitmap_dlg)
	enum { IDD = IDD_BG_BITMAP };	
	CString	m_neb_intensity;	
	int		m_nebula_color;
	int		m_nebula_index;
	int		m_bank;
	int		m_heading;
	int		m_pitch;
	CSliderCtrl			m_slider;
	int		m_neb2_texture;
	BOOL		m_subspace;
	BOOL		m_fullneb;
	int		m_poof[6];	

	// lightning storm data
	CString	m_storm_name;

	// sun data
	CString s_name;
	int s_pitch, s_bank, s_heading;
	float s_scale;
	int s_index;

	// bitmap data
	CString b_name;
	int b_pitch, b_bank, b_heading;
	float b_scale_x, b_scale_y;
	int b_div_x, b_div_y;
	int b_index;

	//}}AFX_DATA	

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(bg_bitmap_dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// clear and build the nebula filename list appropriately
	void build_nebfile_list();

	// Generated message map functions
	//{{AFX_MSG(bg_bitmap_dlg)
	afx_msg void OnClose();	
	afx_msg void OnSelchangeNebcolor();
	afx_msg void OnSelchangeNebpattern();
	afx_msg void OnFullNeb();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);

	// handlers for sun stuff
	afx_msg void OnSunChange();
	afx_msg void OnAddSun();
	afx_msg void OnDelSun();
	afx_msg void OnSunDropdownChange();

	// handlers for bitmap stuff
	afx_msg void OnBitmapChange();
	afx_msg void OnAddBitmap();
	afx_msg void OnDelBitmap();
	afx_msg void OnBitmapDropdownChange();

	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:	
};

#endif