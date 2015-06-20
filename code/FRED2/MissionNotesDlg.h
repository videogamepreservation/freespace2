/*
 * Copyright (C) Volition, Inc. 1999.  All rights reserved.
 *
 * All source code herein is the property of Volition, Inc. You may not sell 
 * or otherwise commercially exploit the source or things you created based on the 
 * source.
 *
*/

/*
 * $Logfile: /Freespace2/code/Fred2/MissionNotesDlg.h $
 * $Revision: 5 $
 * $Date: 8/23/99 6:21p $
 * $Author: Jefff $
 *
 * Mission notes editor dialog box handling code
 *
 * $Log: /Freespace2/code/Fred2/MissionNotesDlg.h $
 * 
 * 5     8/23/99 6:21p Jefff
 * added "no traitor" option to missions (and fred)
 * 
 * 4     8/23/99 5:04p Jefff
 * Added new mission flag to disable built-in messages from playing.
 * Added fred support as well.
 * 
 * 3     3/24/99 4:05p Dave
 * Put in support for assigning the player to a specific squadron with a
 * specific logo. Preliminary work for doing pos/orient checksumming in
 * multiplayer to reduce bandwidth.
 * 
 * 2     10/07/98 6:28p Dave
 * Initial checkin. Renamed all relevant stuff to be Fred2 instead of
 * Fred. Globalized mission and campaign file extensions. Removed Silent
 * Threat specific code.
 * 
 * 1     10/07/98 3:01p Dave
 * 
 * 1     10/07/98 3:00p Dave
 * 
 * 16    6/17/98 2:47p Hoffoss
 * Changed so missions are single, multi or training.  Not supporting
 * combos of the above anymore (in Fred).
 * 
 * 15    5/05/98 11:05p Allender
 * ability to flag mission as "no promotion" where promotions and badges
 * are *not* granted even if they should be.  Slight fix to multiplayer
 * problem where locking_subsys is wrong for players current target
 * 
 * 14    4/03/98 12:17a Allender
 * new sexpression to detect departed or destroyed.  optionally disallow
 * support ships.  Allow docking with escape pods 
 * 
 * 13    3/26/98 5:24p Allender
 * put in respawn edit box into mission notes dialog.  Made loading of
 * missions/campaign happen when first entering the game setup screen.
 * 
 * 12    3/16/98 8:27p Allender
 * Fred support for two new AI flags -- kamikaze and no dynamic goals.
 * 
 * 11    3/09/98 4:30p Allender
 * multiplayer secondary weapon changes.  red-alert and cargo-known-delay
 * sexpressions.  Add time cargo revealed to ship structure
 * 
 * 10    2/04/98 4:32p Allender
 * support for multiple briefings and debriefings.  Changes to mission
 * type (now a bitfield).  Bitfield defs for multiplayer modes
 * 
 * 9     1/02/98 4:55p Hoffoss
 * Added support for Mission_all_attack flag to Fred and loading/saving
 * code.
 * 
 * 8     9/30/97 5:56p Hoffoss
 * Added music selection combo boxes to Fred.
 * 
 * 7     8/11/97 3:19p Hoffoss
 * Implemented mission description.
 * 
 * 6     6/11/97 2:14p Hoffoss
 * Added game type (mission type) selection to Fred.
 * 
 * 5     5/20/97 2:28p Hoffoss
 * Added message box queries for close window operation on all modal
 * dialog boxes.
 * 
 * 4     4/17/97 2:01p Hoffoss
 * All dialog box window states are saved between sessions now.
 * 
 * 3     2/17/97 5:28p Hoffoss
 * Checked RCS headers, added them were missing, changing description to
 * something better, etc where needed.
 *
 * $NoKeywords: $
 */

/////////////////////////////////////////////////////////////////////////////
// CMissionNotesDlg dialog

class CMissionNotesDlg : public CDialog
{
// Construction
public:
	int query_modified();
	void OnCancel();
	void OnOK();
	int update_data();
	int initialize_data();
	CMissionNotesDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMissionNotesDlg)
	enum { IDD = IDD_MISSION_NOTES };
	CSpinButtonCtrl	m_respawn_spin;
	CString	m_created;
	CString	m_modified;
	CString	m_mission_notes;
	CString	m_designer_name;
	CString	m_mission_title;
	CString	m_mission_desc;
	CString	m_squad_filename;
	CString	m_squad_name;
	int		m_music;
	BOOL		m_full_war;
	BOOL		m_red_alert;
	BOOL		m_scramble;
	UINT		m_num_respawns;
	BOOL		m_disallow_support;
	BOOL		m_no_promotion;
	BOOL		m_no_builtin_msgs;
	BOOL		m_no_traitor;
	//}}AFX_DATA

	CString	m_mission_notes_orig;
	CString	m_designer_name_orig;
	CString	m_mission_title_orig;
	CString	m_mission_desc_orig;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMissionNotesDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	int m_type;
	void set_types();

	// Generated message map functions
	//{{AFX_MSG(CMissionNotesDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	afx_msg void OnTraining();
	afx_msg void OnMulti();
	afx_msg void OnSingle();
	afx_msg void OnSquadLogo();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
