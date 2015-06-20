/*
 * Copyright (C) Volition, Inc. 1999.  All rights reserved.
 *
 * All source code herein is the property of Volition, Inc. You may not sell 
 * or otherwise commercially exploit the source or things you created based on the 
 * source.
 *
*/

/*
 * $Logfile: /Freespace2/code/Fred2/MissionNotesDlg.cpp $
 * $Revision: 6 $
 * $Date: 8/23/99 6:21p $
 * $Author: Jefff $
 *
 * Mission notes editor dialog box handling code
 *
 * $Log: /Freespace2/code/Fred2/MissionNotesDlg.cpp $
 * 
 * 6     8/23/99 6:21p Jefff
 * added "no traitor" option to missions (and fred)
 * 
 * 5     8/23/99 5:04p Jefff
 * Added new mission flag to disable built-in messages from playing.
 * Added fred support as well.
 * 
 * 4     3/24/99 4:05p Dave
 * Put in support for assigning the player to a specific squadron with a
 * specific logo. Preliminary work for doing pos/orient checksumming in
 * multiplayer to reduce bandwidth.
 * 
 * 3     2/23/99 2:32p Dave
 * First run of oldschool dogfight mode.
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
 * 23    6/17/98 2:47p Hoffoss
 * Changed so missions are single, multi or training.  Not supporting
 * combos of the above anymore (in Fred).
 * 
 * 22    5/25/98 12:16p Hoffoss
 * Removed dogfight option from dialog.  No longer supported.
 * 
 * 21    5/18/98 1:56a Allender
 * respawn limit to 999 max
 * 
 * 20    5/05/98 11:05p Allender
 * ability to flag mission as "no promotion" where promotions and badges
 * are *not* granted even if they should be.  Slight fix to multiplayer
 * problem where locking_subsys is wrong for players current target
 * 
 * 19    4/03/98 12:17a Allender
 * new sexpression to detect departed or destroyed.  optionally disallow
 * support ships.  Allow docking with escape pods 
 * 
 * 18    3/26/98 5:24p Allender
 * put in respawn edit box into mission notes dialog.  Made loading of
 * missions/campaign happen when first entering the game setup screen.
 * 
 * 17    3/18/98 3:17p Allender
 * fix scramble checkbox
 * 
 * 16    3/18/98 10:27a Allender
 * fixed bug with missions always being tagged a single player regardless
 * of checkbox setting
 * 
 * 15    3/16/98 8:27p Allender
 * Fred support for two new AI flags -- kamikaze and no dynamic goals.
 * 
 * 14    3/09/98 4:30p Allender
 * multiplayer secondary weapon changes.  red-alert and cargo-known-delay
 * sexpressions.  Add time cargo revealed to ship structure
 * 
 * 13    2/09/98 9:25p Allender
 * team v team support.  multiple pools and breifings
 * 
 * 12    2/04/98 4:32p Allender
 * support for multiple briefings and debriefings.  Changes to mission
 * type (now a bitfield).  Bitfield defs for multiplayer modes
 * 
 * 11    1/02/98 4:55p Hoffoss
 * Added support for Mission_all_attack flag to Fred and loading/saving
 * code.
 * 
 * 10    9/30/97 5:56p Hoffoss
 * Added music selection combo boxes to Fred.
 * 
 * 9     8/11/97 3:19p Hoffoss
 * Implemented mission description.
 * 
 * 8     6/11/97 2:14p Hoffoss
 * Added game type (mission type) selection to Fred.
 * 
 * 7     5/20/97 2:28p Hoffoss
 * Added message box queries for close window operation on all modal
 * dialog boxes.
 * 
 * 6     5/06/97 2:43p Hoffoss
 * Fixed bug in Mission notes dialog, where window wasn't being destroyed.
 * 
 * 5     4/17/97 2:01p Hoffoss
 * All dialog box window states are saved between sessions now.
 * 
 * 4     2/21/97 5:34p Hoffoss
 * Added extensive modification detection and fixed a bug in initial
 * orders editor.
 * 
 * 3     2/17/97 5:28p Hoffoss
 * Checked RCS headers, added them were missing, changing description to
 * something better, etc where needed.
 *
 * $NoKeywords: $
 */

#include "stdafx.h"
#include "FRED.h"
#include "FredDoc.h"
#include "MissionNotesDlg.h"
#include "Management.h"
#include "EventMusic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define NO_SQUAD				"<none>"

// module globals to hold button information
CButton *coop, *team, *dogfight;

/////////////////////////////////////////////////////////////////////////////
// CMissionNotesDlg dialog

CMissionNotesDlg::CMissionNotesDlg(CWnd* pParent /*=NULL*/) : CDialog(CMissionNotesDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMissionNotesDlg)
	m_created = _T("");
	m_modified = _T("");
	m_mission_notes = _T("");
	m_designer_name = _T("");
	m_mission_title = _T("");
	m_mission_desc = _T("");
	m_squad_filename = _T("");
	m_squad_name = _T(NO_SQUAD);
	m_music = -1;
	m_full_war = FALSE;
	m_red_alert = FALSE;
	m_scramble = FALSE;
	m_num_respawns = 0;
	m_disallow_support = FALSE;
	m_no_promotion = FALSE;
	m_no_builtin_msgs = FALSE;
	m_no_traitor = FALSE;
	//}}AFX_DATA_INIT
}

void CMissionNotesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMissionNotesDlg)
	DDX_Control(pDX, IDC_RESPAWN_SPIN, m_respawn_spin);
	DDX_Text(pDX, IDC_CREATED, m_created);
	DDX_Text(pDX, IDC_MODIFIED, m_modified);
	DDX_Text(pDX, IDC_MISSION_NOTES, m_mission_notes);
	DDX_Text(pDX, IDC_DESIGNER_NAME, m_designer_name);
	DDX_Text(pDX, IDC_MISSION_TITLE, m_mission_title);
	DDX_Text(pDX, IDC_MISSION_DESC, m_mission_desc);
	DDX_Text(pDX, IDC_SQUAD_LOGO, m_squad_filename);
	DDX_Text(pDX, IDC_SQUAD_NAME, m_squad_name);
	DDX_CBIndex(pDX, IDC_MUSIC, m_music);
	DDX_Check(pDX, IDC_FULL_WAR, m_full_war);
	DDX_Check(pDX, IDC_RED_ALERT, m_red_alert);
	DDX_Check(pDX, IDC_SCRAMBLE, m_scramble);
	DDX_Text(pDX, IDC_RESPAWNS, m_num_respawns);
	DDV_MinMaxUInt(pDX, m_num_respawns, 0, 999);
	DDX_Check(pDX, IDC_SUPPORT_ALLOWED, m_disallow_support);
	DDX_Check(pDX, IDC_NO_PROMOTION, m_no_promotion);
	DDX_Check(pDX, IDC_DISABLE_BUILTIN_MSGS, m_no_builtin_msgs);
	DDX_Check(pDX, IDC_NO_TRAITOR, m_no_traitor);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMissionNotesDlg, CDialog)
	//{{AFX_MSG_MAP(CMissionNotesDlg)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_TRAINING, OnTraining)
	ON_BN_CLICKED(IDC_MULTI, OnMulti)
	ON_BN_CLICKED(IDC_SINGLE, OnSingle)
	ON_BN_CLICKED(IDC_SQUAD_LOGO_BUTTON, OnSquadLogo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMissionNotesDlg message handlers

int CMissionNotesDlg::query_modified()
{
	if (m_mission_title != m_mission_title_orig){
		return 1;
	}
	if (m_designer_name != m_designer_name_orig){
		return 1;
	}
	if (m_mission_notes != m_mission_notes_orig){
		return 1;
	}
	if (m_mission_desc != m_mission_desc_orig){
		return 1;
	}
	if (Current_soundtrack_num != m_music - 1){
		return 1;
	}
	if (Mission_all_attack != m_full_war){
		return 1;
	}

	return 0;
}

void CMissionNotesDlg::OnOK()
{
	int new_m_type, flags, is_multi = 0, is_training = 0, is_single = 0;

	UpdateData();
	is_single = (((CButton *) GetDlgItem(IDC_SINGLE))->GetCheck() == 1);
	is_multi = (((CButton *) GetDlgItem(IDC_MULTI))->GetCheck() == 1);
	is_training = (((CButton *) GetDlgItem(IDC_TRAINING))->GetCheck() == 1);

	// deal with changing the mission type.  Code is done this way since training missions
	// just override anything else.
	new_m_type = 0;
	if (is_training) {
		new_m_type = MISSION_TYPE_TRAINING;
	} else {
		if (is_single){
			new_m_type = MISSION_TYPE_SINGLE;
		}

		if (is_multi) {
			new_m_type |= MISSION_TYPE_MULTI;
			if (coop->GetCheck()){
				new_m_type |= MISSION_TYPE_MULTI_COOP;
			} else if (team->GetCheck()){
				new_m_type |= MISSION_TYPE_MULTI_TEAMS;
			} else if(dogfight->GetCheck()){
				new_m_type |= MISSION_TYPE_MULTI_DOGFIGHT;
			} else {
				Int3();			// get allender -- multiplayer mode not set!!!
			}
		}
	}

	if (!new_m_type) {
		MessageBox("You must select the game type: training, single, or multiplayer", "Error");
		return;
	}

	MODIFY(The_mission.game_type, new_m_type );
	MODIFY(The_mission.red_alert, m_red_alert );
	MODIFY(The_mission.scramble, m_scramble );
	MODIFY(The_mission.num_respawns, (int)m_num_respawns );
	MODIFY(The_mission.disallow_support, (int)m_disallow_support);

	// set the flags for no promotion
	flags = The_mission.flags;
	if ( m_no_promotion ) {
		The_mission.flags |= MISSION_FLAG_NO_PROMOTION;
	} else {
		The_mission.flags &= ~MISSION_FLAG_NO_PROMOTION;
	}

	// set flags for no builtin messages
	if ( m_no_builtin_msgs ) {
		The_mission.flags |= MISSION_FLAG_NO_BUILTIN_MSGS;
	} else {
		The_mission.flags &= ~MISSION_FLAG_NO_BUILTIN_MSGS;
	}

	// set no traitor flags
	if ( m_no_traitor ) {
		The_mission.flags |= MISSION_FLAG_NO_TRAITOR;
	} else {
		The_mission.flags &= ~MISSION_FLAG_NO_TRAITOR;
	}

	if ( flags != The_mission.flags ){
		set_modified();
	}

	string_copy(The_mission.name, m_mission_title, NAME_LENGTH, 1);
	string_copy(The_mission.author, m_designer_name, NAME_LENGTH, 1);
	deconvert_multiline_string(The_mission.notes, m_mission_notes, NOTES_LENGTH);
	deconvert_multiline_string(The_mission.mission_desc, m_mission_desc, MISSION_DESC_LENGTH);

	// copy squad stuff
	if(m_squad_name == CString(NO_SQUAD)){
		strcpy(The_mission.squad_name, "");
		strcpy(The_mission.squad_filename, "");
	} else {
		string_copy(The_mission.squad_name, m_squad_name, NAME_LENGTH);
		string_copy(The_mission.squad_filename, m_squad_filename, MAX_FILENAME_LEN);
	}

	MODIFY(Current_soundtrack_num, m_music - 1);
	MODIFY(Mission_all_attack, m_full_war);
	if (query_modified()){
		set_modified();
	}

	theApp.record_window_data(&Mission_notes_wnd_data, this);

	// update the Num_teams variable accoriding to mission types
	Num_teams = 1;
	if ( (The_mission.game_type & MISSION_TYPE_MULTI) && (The_mission.game_type & MISSION_TYPE_MULTI_TEAMS) ){
		Num_teams = 2;
	}

	CDialog::OnOK();
}

void CMissionNotesDlg::OnCancel()
{
	theApp.record_window_data(&Mission_notes_wnd_data, this);
	CDialog::OnCancel();
}

BOOL CMissionNotesDlg::OnInitDialog() 
{
	int i;
	CComboBox *box;

	// set up the radio box states
	coop = (CButton *)GetDlgItem(IDC_COOP);
	team = (CButton *)GetDlgItem(IDC_TEAMVTEAM);
	dogfight = (CButton *)GetDlgItem(IDC_DOGFIGHT);

	m_mission_title_orig = m_mission_title = _T(The_mission.name);
	m_designer_name_orig = m_designer_name = _T(The_mission.author);
	m_created = _T(The_mission.created);
	m_modified = _T(The_mission.modified);
	m_mission_notes_orig = m_mission_notes = convert_multiline_string(The_mission.notes);
	m_mission_desc_orig = m_mission_desc = convert_multiline_string(The_mission.mission_desc);
	m_red_alert = The_mission.red_alert;
	m_scramble = The_mission.scramble;
	m_disallow_support = The_mission.disallow_support;
	m_no_promotion = (The_mission.flags & MISSION_FLAG_NO_PROMOTION) ? 1 : 0;
	m_no_builtin_msgs = (The_mission.flags & MISSION_FLAG_NO_BUILTIN_MSGS) ? 1 : 0;
	m_no_traitor = (The_mission.flags & MISSION_FLAG_NO_TRAITOR) ? 1 : 0;
	CDialog::OnInitDialog();

	box = (CComboBox *) GetDlgItem(IDC_MUSIC);
	box->AddString("None");
	for (i=0; i<Num_soundtracks; i++){
		box->AddString(Soundtracks[i].name);		
	}

	// squad info
	if(strlen(The_mission.squad_name) > 0){
		m_squad_name = _T(The_mission.squad_name);
		m_squad_filename = _T(The_mission.squad_filename);
	} else {
		m_squad_name = _T(NO_SQUAD);
		m_squad_filename = _T("");
	}

	m_type = The_mission.game_type;
	m_music = Current_soundtrack_num + 1;
	m_full_war = Mission_all_attack;

	// set up the game type checkboxes accoring to m_type
	if ( m_type & MISSION_TYPE_SINGLE ){
		((CButton *) GetDlgItem(IDC_SINGLE))->SetCheck(1);
	}

	// for multiplayer -- be sure to assign a default type if not already assigned.
	if ( m_type & MISSION_TYPE_MULTI ){
		((CButton *) GetDlgItem(IDC_MULTI))->SetCheck(1);
	}

	if ( m_type & MISSION_TYPE_TRAINING ){
		((CButton *) GetDlgItem(IDC_TRAINING))->SetCheck(1);
	}

	// we need to set one of these three multiplayer modes so interface looks correct
	if ( !(m_type & (MISSION_TYPE_MULTI_COOP | MISSION_TYPE_MULTI_DOGFIGHT | MISSION_TYPE_MULTI_TEAMS)) ){
		m_type |= MISSION_TYPE_MULTI_COOP;
	}

	if ( m_type & MISSION_TYPE_MULTI_COOP ){
		coop->SetCheck(1);
	} else if ( m_type & MISSION_TYPE_MULTI_TEAMS ){
		team->SetCheck(1);
	} else if ( m_type & MISSION_TYPE_MULTI_DOGFIGHT ){
		dogfight->SetCheck(1);
	} else {
		Int3();			// get allender -- multiplayer mode not set!!!
	}

	m_respawn_spin.SetRange(0, 99);
	m_num_respawns = The_mission.num_respawns;

	set_types();
	UpdateData(FALSE);
	theApp.init_window(&Mission_notes_wnd_data, this);
	return TRUE;
}

void CMissionNotesDlg::OnClose() 
{
	int z;

	if (query_modified()) {
		z = MessageBox("Do you want to keep your changes?", "Close", MB_ICONQUESTION | MB_YESNOCANCEL);
		if (z == IDCANCEL){
			return;
		}

		if (z == IDYES) {
			OnOK();
			return;
		}
	}

	CDialog::OnClose();
}

// when training button is set, we need to disable all other buttons
void CMissionNotesDlg::OnTraining() 
{
	UpdateData(TRUE);
	set_types();
}

void CMissionNotesDlg::OnMulti() 
{
	UpdateData(TRUE);
	set_types();
}

void CMissionNotesDlg::OnSingle() 
{
	UpdateData(TRUE);
	set_types();
}

void CMissionNotesDlg::set_types()
{
	int enable = 0;

	// when training is checked, no other type is active
	if (((CButton *) GetDlgItem(IDC_MULTI))->GetCheck() == 1){
		enable = 1;
	}

	coop->EnableWindow(enable);
	team->EnableWindow(enable);
	dogfight->EnableWindow(enable);
	GetDlgItem(IDC_RESPAWNS)->EnableWindow(enable);
	GetDlgItem(IDC_RESPAWN_SPIN)->EnableWindow(enable);
}

void CMissionNotesDlg::OnSquadLogo()
{	
	CString pcx_filename;
	int z;

	// get list of squad images
	z = cfile_push_chdir(CF_TYPE_SQUAD_IMAGES_MAIN);
	CFileDialog dlg(TRUE, "pcx", pcx_filename, OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR, "Pcx Files (*.pcx)|*.pcx");

	// if we have a result
	if (dlg.DoModal() == IDOK) {
		m_squad_filename = dlg.GetFileName();		
	} else {
		m_squad_filename = _T("");
	}
	UpdateData(FALSE);		

	// restore directory
	if (!z){
		cfile_pop_dir();
	}	
}