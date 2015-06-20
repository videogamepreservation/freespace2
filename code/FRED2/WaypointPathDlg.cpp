/*
 * Copyright (C) Volition, Inc. 1999.  All rights reserved.
 *
 * All source code herein is the property of Volition, Inc. You may not sell 
 * or otherwise commercially exploit the source or things you created based on the 
 * source.
 *
*/

/*
 * $Logfile: /Freespace2/code/FRED2/WaypointPathDlg.cpp $
 * $Revision: 2 $
 * $Date: 10/07/98 6:28p $
 * $Author: Dave $
 *
 * Waypoint editor
 *
 * $Log: /Freespace2/code/FRED2/WaypointPathDlg.cpp $
 * 
 * 2     10/07/98 6:28p Dave
 * Initial checkin. Renamed all relevant stuff to be Fred2 instead of
 * Fred. Globalized mission and campaign file extensions. Removed Silent
 * Threat specific code.
 * 
 * 1     10/07/98 3:02p Dave
 * 
 * 1     10/07/98 3:00p Dave
 * 
 * 12    3/21/98 7:36p Lawrance
 * Move jump nodes to own lib.
 * 
 * 11    3/10/98 6:11p Hoffoss
 * Added jump node renaming abilities to Fred.
 * 
 * 10    8/12/97 1:55a Hoffoss
 * Made extensive changes to object reference checking and handling for
 * object deletion call.
 * 
 * 9     5/23/97 1:53p Hoffoss
 * Fixed problems with modeless dialog updating.  It won't get caught in
 * an infinate loop anymore, but still gives an error warning 3 times when
 * using cancel and trying to switch window focus to main window.  Don't
 * know if I can fix that, but it's not too critical right now.
 * 
 * 8     5/14/97 4:08p Lawrance
 * removing my_index from game arrays
 * 
 * 7     4/28/97 4:14p Hoffoss
 * Fixed several bugs involving waypoints.
 * 
 * 6     3/13/97 12:09p Hoffoss
 * Waypoint path editor finished (apparently I didn't get around to
 * completing it before).
 * 
 * 5     2/28/97 11:31a Hoffoss
 * Implemented modeless dialog saving and restoring, and changed some
 * variables names.
 * 
 * 4     2/21/97 5:34p Hoffoss
 * Added extensive modification detection and fixed a bug in initial
 * orders editor.
 * 
 * 3     2/12/97 5:50p Hoffoss
 * Expanded on error checking.
 * 
 * 2     2/12/97 12:26p Hoffoss
 * Expanded on global error checker, added initial orders conflict
 * checking and warning, added waypoint editor dialog and code.
 *
 * $NoKeywords: $
 */

#include "stdafx.h"
#include "fred.h"
#include "WaypointPathDlg.h"
#include "Management.h"
#include "MainFrm.h"
#include "Object.h"
#include "LinkList.h"
#include "Ship.h"
#include "AiGoals.h"
#include "Starfield.h"
#include "JumpNode.h"

#define ID_JUMP_NODE_MENU	8000
#define ID_WAYPOINT_MENU	9000

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// waypoint_path_dlg dialog

waypoint_path_dlg::waypoint_path_dlg(CWnd* pParent /*=NULL*/)
	: CDialog(waypoint_path_dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(waypoint_path_dlg)
	m_name = _T("");
	//}}AFX_DATA_INIT
	bypass_errors = 0;
}

void waypoint_path_dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(waypoint_path_dlg)
	DDX_Text(pDX, IDC_NAME, m_name);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(waypoint_path_dlg, CDialog)
	//{{AFX_MSG_MAP(waypoint_path_dlg)
	ON_WM_CLOSE()
	ON_WM_INITMENU()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// waypoint_path_dlg message handlers

BOOL waypoint_path_dlg::Create()
{
	BOOL r;
	r = CDialog::Create(IDD, Fred_main_wnd);
	initialize_data(1);
	return r;
}

void waypoint_path_dlg::OnInitMenu(CMenu* pMenu)
{
	int i;
	CMenu *m;

	m = pMenu->GetSubMenu(0);
	clear_menu(m);
	for (i=0; i<Num_waypoint_lists; i++)
		if (Waypoint_lists[i].count)
			m->AppendMenu(MF_ENABLED | MF_STRING, ID_WAYPOINT_MENU + i, Waypoint_lists[i].name);

	for (i=0; i<Num_jump_nodes; i++)
		m->AppendMenu(MF_ENABLED | MF_STRING, ID_JUMP_NODE_MENU + i, Jump_nodes[i].name);

	m->DeleteMenu(ID_PLACEHOLDER, MF_BYCOMMAND);
	if (cur_waypoint_list != -1)
		m->CheckMenuItem(ID_WAYPOINT_MENU + cur_waypoint_list, MF_BYCOMMAND | MF_CHECKED);

	if (cur_object_index >= 0)
		if (Objects[cur_object_index].type == OBJ_JUMP_NODE)
			m->CheckMenuItem(ID_JUMP_NODE_MENU + Objects[cur_object_index].instance, MF_BYCOMMAND | MF_CHECKED);

	CDialog::OnInitMenu(pMenu);
}

void waypoint_path_dlg::OnOK()
{
}

void waypoint_path_dlg::OnClose() 
{
	if (update_data()) {
		SetWindowPos(&wndTop, 0, 0, 0, 0, SWP_SHOWWINDOW | SWP_NOMOVE | SWP_NOSIZE);
		bypass_errors = 0;
		return;
	}

	SetWindowPos(Fred_main_wnd, 0, 0, 0, 0, SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE | SWP_HIDEWINDOW);
	Fred_main_wnd->SetWindowPos(&wndTop, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
}

void waypoint_path_dlg::initialize_data(int full_update)
{
	int enable = TRUE;

	if (!GetSafeHwnd())
		return;

	if (query_valid_object() && Objects[cur_object_index].type == OBJ_WAYPOINT)
		Assert(cur_waypoint_list == (Objects[cur_object_index].instance / 65536));

	if (cur_waypoint_list >= 0) {
		m_name = _T(Waypoint_lists[cur_waypoint_list].name);

	} else if (Objects[cur_object_index].type == OBJ_JUMP_NODE) {
		m_name = _T(Jump_nodes[Objects[cur_object_index].instance].name);

	} else {
		m_name = _T("");
		enable = FALSE;
	}

	if (full_update)
		UpdateData(FALSE);

	GetDlgItem(IDC_NAME)->EnableWindow(enable);
}

int waypoint_path_dlg::update_data(int redraw)
{
	char *str, old_name[255];
	int i, z, inst;
	object *ptr;

	if (!GetSafeHwnd())
		return 0;

	UpdateData(TRUE);
	UpdateData(TRUE);

	if (query_valid_object() && Objects[cur_object_index].type == OBJ_WAYPOINT)
		Assert(cur_waypoint_list == (Objects[cur_object_index].instance / 65536));

	if (cur_waypoint_list >= 0) {
		if (!strnicmp(m_name, "player ", 7)) {
			if (bypass_errors)
				return 1;

			bypass_errors = 1;
			z = MessageBox("Waypoint path names can't start with the word 'player'\n"
				"Press OK to restore old name", "Error", MB_ICONEXCLAMATION | MB_OKCANCEL);

			if (z == IDCANCEL)
				return -1;

			m_name = _T(Waypoint_lists[cur_waypoint_list].name);
			UpdateData(FALSE);
		}

		for (i=0; i<MAX_WINGS; i++)
			if (!stricmp(Wings[i].name, m_name)) {
				if (bypass_errors)
					return 1;

				bypass_errors = 1;
				z = MessageBox("This waypoint path name is already being used by a wing\n"
					"Press OK to restore old name", "Error", MB_ICONEXCLAMATION | MB_OKCANCEL);

				if (z == IDCANCEL)
					return -1;

				m_name = _T(Waypoint_lists[cur_waypoint_list].name);
				UpdateData(FALSE);
			}

		ptr = GET_FIRST(&obj_used_list);
		while (ptr != END_OF_LIST(&obj_used_list)) {
			if (ptr->type == OBJ_SHIP) {
				if (!stricmp(m_name, Ships[ptr->instance].ship_name)) {
					if (bypass_errors)
						return 1;

					bypass_errors = 1;
					z = MessageBox("This waypoint path name is already being used by a ship\n"
						"Press OK to restore old name", "Error", MB_ICONEXCLAMATION | MB_OKCANCEL);

					if (z == IDCANCEL)
						return -1;

					m_name = _T(Waypoint_lists[cur_waypoint_list].name);
					UpdateData(FALSE);
				}
			}

			ptr = GET_NEXT(ptr);
		}

		for (i=0; i<MAX_WAYPOINT_LISTS; i++)
			if (Waypoint_lists[i].count && !stricmp(Waypoint_lists[i].name, m_name) && (i != cur_waypoint_list)) {
				if (bypass_errors)
					return 1;

				bypass_errors = 1;
				z = MessageBox("This waypoint path name is already being used by another waypoint path\n"
					"Press OK to restore old name", "Error", MB_ICONEXCLAMATION | MB_OKCANCEL);

				if (z == IDCANCEL)
					return -1;

				m_name = _T(Waypoint_lists[cur_waypoint_list].name);
				UpdateData(FALSE);
			}

		for (i=0; i<Num_jump_nodes; i++)
			if (!stricmp(Jump_nodes[i].name, m_name)) {
				if (bypass_errors)
					return 1;

				bypass_errors = 1;
				z = MessageBox("This waypoint path name is already being used by a jump node\n"
					"Press OK to restore old name", "Error", MB_ICONEXCLAMATION | MB_OKCANCEL);

				if (z == IDCANCEL)
					return -1;

				m_name = _T(Waypoint_lists[cur_waypoint_list].name);
				UpdateData(FALSE);
			}

		strcpy(old_name, Waypoint_lists[cur_waypoint_list].name);
		string_copy(Waypoint_lists[cur_waypoint_list].name, m_name, NAME_LENGTH, 1);

		str = (char *) (LPCTSTR) m_name;
		if (stricmp(old_name, str)) {
			update_sexp_references(old_name, str);
			ai_update_goal_references(REF_TYPE_WAYPOINT, old_name, str);
		}

	} else if (Objects[cur_object_index].type == OBJ_JUMP_NODE) {
		inst = Objects[cur_object_index].instance;
		if (!strnicmp(m_name, "player ", 7)) {
			if (bypass_errors)
				return 1;

			bypass_errors = 1;
			z = MessageBox("Jump node names can't start with the word 'player'\n"
				"Press OK to restore old name", "Error", MB_ICONEXCLAMATION | MB_OKCANCEL);

			if (z == IDCANCEL)
				return -1;

			m_name = _T(Jump_nodes[inst].name);
			UpdateData(FALSE);
		}

		for (i=0; i<MAX_WINGS; i++)
			if (!stricmp(Wings[i].name, m_name)) {
				if (bypass_errors)
					return 1;

				bypass_errors = 1;
				z = MessageBox("This jump node name is already being used by a wing\n"
					"Press OK to restore old name", "Error", MB_ICONEXCLAMATION | MB_OKCANCEL);

				if (z == IDCANCEL)
					return -1;

				m_name = _T(Jump_nodes[inst].name);
				UpdateData(FALSE);
			}

		ptr = GET_FIRST(&obj_used_list);
		while (ptr != END_OF_LIST(&obj_used_list)) {
			if (ptr->type == OBJ_SHIP) {
				if (!stricmp(m_name, Ships[ptr->instance].ship_name)) {
					if (bypass_errors)
						return 1;

					bypass_errors = 1;
					z = MessageBox("This jump node name is already being used by a ship\n"
						"Press OK to restore old name", "Error", MB_ICONEXCLAMATION | MB_OKCANCEL);

					if (z == IDCANCEL)
						return -1;

					m_name = _T(Jump_nodes[inst].name);
					UpdateData(FALSE);
				}
			}

			ptr = GET_NEXT(ptr);
		}

		for (i=0; i<MAX_WAYPOINT_LISTS; i++)
			if (Waypoint_lists[i].count && !stricmp(Waypoint_lists[i].name, m_name)) {
				if (bypass_errors)
					return 1;

				bypass_errors = 1;
				z = MessageBox("This jump node name is already being used by a waypoint path\n"
					"Press OK to restore old name", "Error", MB_ICONEXCLAMATION | MB_OKCANCEL);

				if (z == IDCANCEL)
					return -1;

				m_name = _T(Jump_nodes[inst].name);
				UpdateData(FALSE);
			}

		for (i=0; i<Num_jump_nodes; i++)
			if ((i != inst) && !stricmp(Jump_nodes[i].name, m_name)) {
				if (bypass_errors)
					return 1;

				bypass_errors = 1;
				z = MessageBox("This jump node name is already being used by another jump node\n"
					"Press OK to restore old name", "Error", MB_ICONEXCLAMATION | MB_OKCANCEL);

				if (z == IDCANCEL)
					return -1;

				m_name = _T(Jump_nodes[inst].name);
				UpdateData(FALSE);
			}

		strcpy(old_name, Jump_nodes[inst].name);
		string_copy(Jump_nodes[inst].name, m_name, NAME_LENGTH, 1);

		str = (char *) (LPCTSTR) m_name;
		if (stricmp(old_name, str)) {
			update_sexp_references(old_name, str);
		}
	}

	if (redraw)
		update_map_window();

	return 0;
}

BOOL waypoint_path_dlg::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	int id, point;
	object *ptr;

	id = LOWORD(wParam);
	if ((id >= ID_WAYPOINT_MENU) && (id < ID_WAYPOINT_MENU + MAX_WAYPOINT_LISTS)) {
		if (!update_data()) {
			point = id - ID_WAYPOINT_MENU;
			unmark_all();
			ptr = GET_FIRST(&obj_used_list);
			while (ptr != END_OF_LIST(&obj_used_list)) {
				if (ptr->type == OBJ_WAYPOINT)
					if ((ptr->instance / 65536) == point)
						mark_object(OBJ_INDEX(ptr));

				ptr = GET_NEXT(ptr);
			}

			return 1;
		}
	}

	if ((id >= ID_JUMP_NODE_MENU) && (id < ID_JUMP_NODE_MENU + Num_jump_nodes)) {
		if (!update_data()) {
			point = id - ID_JUMP_NODE_MENU;
			unmark_all();
			ptr = GET_FIRST(&obj_used_list);
			while (ptr != END_OF_LIST(&obj_used_list)) {
				if (ptr->type == OBJ_JUMP_NODE)
					if (ptr->instance == point)
						mark_object(OBJ_INDEX(ptr));

				ptr = GET_NEXT(ptr);
			}

			return 1;
		}
	}

	return CDialog::OnCommand(wParam, lParam);
}
