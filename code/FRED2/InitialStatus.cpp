/*
 * Copyright (C) Volition, Inc. 1999.  All rights reserved.
 *
 * All source code herein is the property of Volition, Inc. You may not sell 
 * or otherwise commercially exploit the source or things you created based on the 
 * source.
 *
*/

// InitialStatus.cpp : implementation file
//

#include "stdafx.h"
#include "Fred.h"
#include "FredDoc.h"
#include "InitialStatus.h"
#include "Management.h"
#include "LinkList.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// initial_status dialog

initial_status::initial_status(CWnd* pParent /*=NULL*/)
	: CDialog(initial_status::IDD, pParent)
{
	//{{AFX_DATA_INIT(initial_status)
	m_damage = 0;
	m_docked = -1;
	m_shields = 0;
	m_velocity = 0;
	m_hull = 0;
	m_dockee_point = -1;
	m_docker_point = -1;
	m_has_shields = FALSE;
	m_locked = FALSE;
	m_cargo_name = _T("");
	//}}AFX_DATA_INIT
	inited = 0;
	cur_subsys = LB_ERR;
	m_multi_edit = 0;
}

void initial_status::DoDataExchange(CDataExchange* pDX)
{
	CString str;

	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(initial_status)
	DDX_Control(pDX, IDC_HULL_SPIN, m_hull_spin);
	DDX_Control(pDX, IDC_VELOCITY_SPIN, m_velocity_spin);
	DDX_Control(pDX, IDC_SHIELDS_SPIN, m_shields_spin);
	DDX_Control(pDX, IDC_DAMAGE_SPIN, m_damage_spin);
	DDX_Text(pDX, IDC_DAMAGE, m_damage);
	DDV_MinMaxInt(pDX, m_damage, 0, 100);
	DDX_CBIndex(pDX, IDC_DOCKED, m_docked);
	DDX_CBIndex(pDX, IDC_DOCKEE_POINT, m_dockee_point);
	DDX_CBIndex(pDX, IDC_DOCKER_POINT, m_docker_point);
	DDX_Check(pDX, IDC_HAS_SHIELDS, m_has_shields);
	DDX_Check(pDX, IDC_LOCKED, m_locked);
	DDX_Text(pDX, IDC_CARGO_NAME, m_cargo_name);
	DDV_MaxChars(pDX, m_cargo_name, 20);
	//}}AFX_DATA_MAP

	if (pDX->m_bSaveAndValidate) {
		GetDlgItem(IDC_VELOCITY)->GetWindowText(str);
		m_velocity = atoi(str);
		if (m_velocity < 0)
			m_velocity = 0;
		if (m_velocity > 100)
			m_velocity = 100;

		GetDlgItem(IDC_SHIELDS)->GetWindowText(str);
		m_shields = atoi(str);
		if (m_shields < 0)
			m_shields = 0;
		if (m_shields > 100)
			m_shields = 100;

		GetDlgItem(IDC_HULL)->GetWindowText(str);
		m_hull = atoi(str);
		if (m_hull < 0)
			m_hull = 0;
		if (m_hull > 100)
			m_hull = 100;
	}
}

BEGIN_MESSAGE_MAP(initial_status, CDialog)
	//{{AFX_MSG_MAP(initial_status)
	ON_LBN_SELCHANGE(IDC_SUBSYS, OnSelchangeSubsys)
	ON_CBN_SELCHANGE(IDC_DOCKED, OnSelchangeDocked)
	ON_CBN_SELCHANGE(IDC_DOCKER_POINT, OnSelchangeDockerPoint)
	ON_BN_CLICKED(IDC_HAS_SHIELDS, OnHasShields)
	ON_BN_CLICKED(IDC_LOCKED, OnLocked)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// initial_status message handlers

BOOL initial_status::OnInitDialog() 
{
	int z, vflag, sflag, hflag, ship, type;
	ship_subsys *ptr;
	CComboBox *box;
	CString str;
	object *objp;

	m_ship = cur_ship;
	if (m_ship == -1) {
		Assert((Objects[cur_object_index].type == OBJ_SHIP) || (Objects[cur_object_index].type == OBJ_START));
		m_ship = get_ship_from_obj(cur_object_index);
		Assert(m_ship >= 0);
	}

	vflag = sflag = hflag = 0;
	m_velocity = (int) Objects[cur_object_index].phys_info.speed;
	m_shields = (int) Objects[cur_object_index].shields[0];
	m_hull = (int) Objects[cur_object_index].hull_strength;
	if (Objects[cur_object_index].flags & OF_NO_SHIELDS)
		m_has_shields = 0;
	else
		m_has_shields = 1;

	if (Ships[m_ship].flags & SF_LOCKED)
		m_locked = 1;
	else
		m_locked = 0;

	if (m_multi_edit) {
		objp = GET_FIRST(&obj_used_list);
		while (objp != END_OF_LIST(&obj_used_list)) {
			if (((objp->type == OBJ_SHIP) || (objp->type == OBJ_START)) && (objp->flags & OF_MARKED)) {
				if (objp->phys_info.speed != m_velocity)
					vflag = 1;
				if ((int) objp->shields[0] != m_shields)
					sflag = 1;
				if ((int) objp->hull_strength != m_hull)
					hflag = 1;
				if (objp->flags & OF_NO_SHIELDS) {
					if (m_has_shields)
						m_has_shields = 2;

				} else {
					if (!m_has_shields)
						m_has_shields = 2;
				}

				Assert((objp->type == OBJ_SHIP) || (objp->type == OBJ_START));
				if (Ships[get_ship_from_obj(objp)].flags & SF_LOCKED) {
					if (!m_locked)
						m_locked = 2;

				} else {
					if (m_locked)
						m_locked = 2;
				}
			}

			objp = GET_NEXT(objp);
		}
	}

	CDialog::OnInitDialog();
	str.Format("%d", m_velocity);
	GetDlgItem(IDC_VELOCITY)->SetWindowText(str);
	str.Format("%d", m_shields);
	GetDlgItem(IDC_SHIELDS)->SetWindowText(str);
	str.Format("%d", m_hull);
	GetDlgItem(IDC_HULL)->SetWindowText(str);

	inited = 1;
	box = (CComboBox *) GetDlgItem(IDC_DOCKED);
	box->ResetContent();
	if (!m_multi_edit) {
		z = box->AddString("Nothing");
		m_docked = 0;

		type = model_get_dock_types(Ships[m_ship].modelnum);
		objp = GET_FIRST(&obj_used_list);
		while (objp != END_OF_LIST(&obj_used_list)) {
			if ((objp->type == OBJ_SHIP) || (objp->type == OBJ_START)) {
				ship = get_ship_from_obj(objp);
				if ((ship != m_ship) && (ship_docking_valid(m_ship, ship) || ship_docking_valid(ship, m_ship))) {
					if (model_get_dock_types(Ships[ship].modelnum) & type) {
						z = box->AddString(Ships[ship].ship_name);
						box->SetItemData(z, ship);
					}
				}
			}

			objp = GET_NEXT(objp);
		}

		m_docked_with = -1;
		z  = Ai_info[Ships[m_ship].ai_index].dock_objnum;
		if (z >= 0) {
			Assert(Objects[z].type == OBJ_SHIP);
			z = m_docked_with = get_ship_from_obj(z);
			m_docked = box->FindStringExact(-1, Ships[z].ship_name);

			m_docker_index = Ai_info[Ships[m_ship].ai_index].dock_index;
			m_dockee_index = Ai_info[Ships[m_ship].ai_index].dockee_index;
			initialize_docker_points();
			initialize_dockee_points();

		} else {
			m_docker_index = m_dockee_index = m_docker_point = m_dockee_point = -1;
			GetDlgItem(IDC_DOCKER_POINT)->EnableWindow(FALSE);
			GetDlgItem(IDC_DOCKEE_POINT)->EnableWindow(FALSE);
		}

		ptr = GET_FIRST(&Ships[m_ship].subsys_list);
		while (ptr != END_OF_LIST(&Ships[m_ship].subsys_list)) {
			((CListBox *) GetDlgItem(IDC_SUBSYS)) -> AddString(ptr->system_info->subobj_name);
			ptr = GET_NEXT(ptr);
		}

	} else {
		GetDlgItem(IDC_DOCKED)->EnableWindow(FALSE);
		GetDlgItem(IDC_DOCKER_POINT)->EnableWindow(FALSE);
		GetDlgItem(IDC_DOCKEE_POINT)->EnableWindow(FALSE);
		GetDlgItem(IDC_SUBSYS)->EnableWindow(FALSE);
		GetDlgItem(IDC_DAMAGE)->EnableWindow(FALSE);
	}

	GetDlgItem(IDC_SHIELDS)->EnableWindow(m_has_shields ? TRUE : FALSE);
	GetDlgItem(IDC_SHIELDS_SPIN)->EnableWindow(m_has_shields ? TRUE : FALSE);

	m_velocity_spin.SetRange(0, 100);
	m_hull_spin.SetRange(0, 100);
	m_shields_spin.SetRange(0, 100);
	m_damage_spin.SetRange(0, 100);
	change_subsys();
	UpdateData(FALSE);
	if (vflag)
		GetDlgItem(IDC_VELOCITY)->SetWindowText("");
	if (sflag)
		GetDlgItem(IDC_SHIELDS)->SetWindowText("");
	if (hflag)
		GetDlgItem(IDC_HULL)->SetWindowText("");

	return TRUE;
}

void initial_status::initialize_docker_points()
{
	int i, type;
	CComboBox *box;

	box = (CComboBox *) GetDlgItem(IDC_DOCKER_POINT);
	box->ResetContent();
	if (m_docked_with < 0) {
		m_docker_index = m_docker_point = -1;
		return;
	}

	type = model_get_dock_types(Ships[m_docked_with].modelnum);
	set_valid_dock_points(m_ship, type, box);
	i = box->GetCount();
	Assert(i);  // this shouldn't happen.
	while (i--)
		if ((int) box->GetItemData(i) == m_docker_index)
			break;

	m_docker_point = i;
	if (i < 0) {
		m_docker_point = 0;
		m_docker_index = box->GetItemData(0);
	}
}

void initial_status::initialize_dockee_points()
{
	int i, type;
	CComboBox *box;

	box = (CComboBox *) GetDlgItem(IDC_DOCKEE_POINT);
	box->ResetContent();
	if ((m_docked_with < 0) || (m_docker_index < 0)) {
		m_dockee_index = m_dockee_point = -1;
		return;
	}

	type = model_get_dock_index_type(Ships[m_ship].modelnum, m_docker_index);
	set_valid_dock_points(m_docked_with, type, box);
	i = box->GetCount();
	Assert(i);  // this shouldn't happen.
	while (i--)
		if ((int) box->GetItemData(i) == m_dockee_index)
			break;

	m_dockee_point = i;
	if (i < 0) {
		m_dockee_point = 0;
		m_dockee_index = box->GetItemData(0);
	}
}

void initial_status::change_subsys()
{
	int z, cargo_index, enable = FALSE, enable_cargo_name = FALSE;
	ship_subsys *ptr;

	if (cur_subsys != LB_ERR) {
		ptr = GET_FIRST(&Ships[m_ship].subsys_list);
		while (cur_subsys--) {
			Assert(ptr != END_OF_LIST(&Ships[m_ship].subsys_list));
			ptr = GET_NEXT(ptr);
		}

		MODIFY(ptr -> current_hits, 100.0f - (float) m_damage);

		// update cargo name
		if (strlen(m_cargo_name) > 0) {
			cargo_index = string_lookup(m_cargo_name, Cargo_names, Num_cargo);
			if (cargo_index == -1) {
				if (Num_cargo < MAX_CARGO);
				cargo_index = Num_cargo++;
				strcpy(Cargo_names[cargo_index], m_cargo_name);
				ptr->subsys_cargo_name = cargo_index;
			} else {
				ptr->subsys_cargo_name = cargo_index;
			}
		} else {
			ptr->subsys_cargo_name = -1;
		}
		set_modified();
	}

	cur_subsys = z = ((CListBox *) GetDlgItem(IDC_SUBSYS)) -> GetCurSel();
	if (z == LB_ERR) {
		m_damage = 100;

	} else {
		ptr = GET_FIRST(&Ships[m_ship].subsys_list);
		while (z--) {
			Assert(ptr != END_OF_LIST(&Ships[m_ship].subsys_list));
			ptr = GET_NEXT(ptr);
		}

		m_damage = 100 - (int) ptr -> current_hits;
		if ( (Ship_info[Ships[m_ship].ship_info_index].flags & SIF_HUGE_SHIP) && valid_cap_subsys_cargo_list(ptr->system_info->subobj_name) ) {
			enable_cargo_name = TRUE;
			if (ptr->subsys_cargo_name != -1) {
				m_cargo_name = Cargo_names[ptr->subsys_cargo_name];
			} else {
				m_cargo_name = _T("");
			}
		} else {
			m_cargo_name = _T("");
		}
		enable = TRUE;
	}

	GetDlgItem(IDC_DAMAGE) -> EnableWindow(enable);
	GetDlgItem(IDC_DAMAGE_SPIN) -> EnableWindow(enable);
	GetDlgItem(IDC_CARGO_NAME)->EnableWindow(enable && enable_cargo_name);
	UpdateData(FALSE);
}

void initial_status::OnOK()
{
	char buf[256];
	int z, obj, vflag = 0, sflag = 0, hflag = 0;
	object *o1, *o2, *objp;

	if (GetDlgItem(IDC_VELOCITY)->GetWindowText(buf, 255))
		vflag = 1;
	if (GetDlgItem(IDC_SHIELDS)->GetWindowText(buf, 255))
		sflag = 1;
	if (GetDlgItem(IDC_HULL)->GetWindowText(buf, 255))
		hflag = 1;

	UpdateData(TRUE);
	UpdateData(TRUE);
	change_subsys();
	if (m_multi_edit) {
		objp = GET_FIRST(&obj_used_list);
		while (objp != END_OF_LIST(&obj_used_list)) {
			if (((objp->type == OBJ_SHIP) || (objp->type == OBJ_START)) && (objp->flags & OF_MARKED)) {
				if (vflag)
					MODIFY(objp->phys_info.speed, (float) m_velocity);

				if (sflag)
					MODIFY(objp->shields[0], (float) m_shields);

				if (hflag)
					MODIFY(objp->hull_strength, (float) m_hull);

				if (m_has_shields == 1)
					objp->flags &= ~OF_NO_SHIELDS;
				else if (!m_has_shields)
					objp->flags |= OF_NO_SHIELDS;

				if (m_locked == 1)
					Ships[get_ship_from_obj(objp)].flags |= SF_LOCKED;
				else if (!m_has_shields)
					Ships[get_ship_from_obj(objp)].flags &= ~SF_LOCKED;
			}

			objp = GET_NEXT(objp);
		}

	} else {
		MODIFY(Objects[cur_object_index].phys_info.speed, (float) m_velocity);
		MODIFY(Objects[cur_object_index].shields[0], (float) m_shields);
		MODIFY(Objects[cur_object_index].hull_strength, (float) m_hull);
		if (m_has_shields)
			Objects[cur_object_index].flags &= ~OF_NO_SHIELDS;
		else
			Objects[cur_object_index].flags |= OF_NO_SHIELDS;

		if (m_locked == 1)
			Ships[m_ship].flags |= SF_LOCKED;
		else if (!m_locked)
			Ships[m_ship].flags &= ~SF_LOCKED;

		obj = -1;
		if (m_docked_with >= 0)
			obj = Ships[m_docked_with].objnum;

		z = Ai_info[Ships[m_ship].ai_index].dock_objnum;
		if (z >= 0) {
			int o;

			if (obj >= 0) {
				o = Ai_info[Ships[get_ship_from_obj(obj)].ai_index].dock_objnum;
				if (o >= 0)
					undock(o);
			}

			undock(Ships[m_ship].objnum);
			Update_window = 1;
		}
		
		MODIFY(Ai_info[Ships[m_ship].ai_index].dock_objnum, obj);
		if (obj >= 0) {
			int s1type, s2type;

			// sets up the actual docking on the Fred screen.  After docking is done, use a loose
			// set of rules to possibly set an arrival cue to false
			o1 = &Objects[Ships[m_ship].objnum];
			o2 = &Objects[Ships[m_docked_with].objnum];
			m_docker_index = ((CComboBox *) GetDlgItem(IDC_DOCKER_POINT)) -> GetItemData(m_docker_point);
			MODIFY(Ai_info[Ships[m_ship].ai_index].dock_index, m_docker_index);
			m_dockee_index = ((CComboBox *) GetDlgItem(IDC_DOCKEE_POINT)) -> GetItemData(m_dockee_point);
			MODIFY(Ai_info[Ships[m_ship].ai_index].dockee_index, m_dockee_index);

			// based on the types of the two ships docked, set the arrival cue of the "smaller" ship
			// to false.
			s1type = Ship_info[Ships[m_ship].ship_info_index].flags;
			s2type = Ship_info[Ships[m_docked_with].ship_info_index].flags;

			if (ship_docking_valid(m_ship, m_docked_with)) {
				ai_dock_with_object(o1, o2, 89, AIDO_DOCK_NOW, m_docker_index, m_dockee_index);
			} else {
				ai_dock_with_object(o2, o1, 89, AIDO_DOCK_NOW, m_dockee_index, m_docker_index);
			}

			// based on the rules already defined for docking (see ship_docking_valid()), we can make
			// assumptions about what are "small" and "large" ships in this process.  Set the arrival
			// cue of the small ships to false so that they can properly arrive in the mission when
			// their parent does
			if ( (s2type & SIF_CARGO) || (s1type & SIF_BIG_SHIP) ) {
				reset_arrival_to_false( m_docked_with );
			} else if ( (s1type & SIF_CARGO) || (s2type & SIF_BIG_SHIP) ) {
				reset_arrival_to_false( m_ship );
			} else {
				// default rule -- pick one!
				reset_arrival_to_false( m_ship );
			}

			Assert ( (Ships[m_ship].flags & SF_INITIALLY_DOCKED) || (Ships[m_docked_with].flags & SF_INITIALLY_DOCKED) );

			Update_window = 1;
		}

		if (Update_window)
			update_map_window();
	}

	CDialog::OnOK();
}

void initial_status::undock(int obj)
{
	int o2;
	vector v;
	int ship_num, other_ship_num;

	o2 = Ai_info[Ships[get_ship_from_obj(obj)].ai_index].dock_objnum;
	if (o2 < 0)
		return;

	vm_vec_sub(&v, &Objects[obj].pos, &Objects[o2].pos);
	vm_vec_normalize(&v);
	ship_num = get_ship_from_obj(obj);
	other_ship_num = get_ship_from_obj(o2);

	if (ship_docking_valid(ship_num, other_ship_num) )
		vm_vec_scale_add2(&Objects[obj].pos, &v, Objects[obj].radius * 2.0f);
	else
		vm_vec_scale_add2(&Objects[o2].pos, &v, Objects[o2].radius * -2.0f);

	Ai_info[Ships[ship_num].ai_index].dock_objnum = -1;
	Ai_info[Ships[other_ship_num].ai_index].dock_objnum = -1;

	// check to see if one of these ships has an arrival cue of false.  If so, then
	// reset it back to default value of true.  be sure to correctly update before
	// and after setting data.
	Ship_editor_dialog.update_data(1);
	if ( Ships[ship_num].arrival_cue == Locked_sexp_false ) {
		Ships[ship_num].arrival_cue = Locked_sexp_true;
	} else if ( Ships[other_ship_num].arrival_cue == Locked_sexp_false ) {
		Ships[other_ship_num].arrival_cue = Locked_sexp_true;
	}

	// reset the initially docked flags on both ships (only one will be set, but this s
	// just for safety!)
	Ships[ship_num].flags &= ~(SF_INITIALLY_DOCKED);
	Ships[other_ship_num].flags &= ~(SF_INITIALLY_DOCKED);
	Ship_editor_dialog.initialize_data(1);

}

void initial_status::OnSelchangeSubsys() 
{
	UpdateData(TRUE);
	UpdateData(TRUE);
	change_subsys();
}

void initial_status::OnSelchangeDocked() 
{
	UpdateData(TRUE);
	UpdateData(TRUE);
	if (m_docked) {
		GetDlgItem(IDC_DOCKER_POINT)->EnableWindow(TRUE);
		GetDlgItem(IDC_DOCKEE_POINT)->EnableWindow(TRUE);

		m_docked_with = ((CComboBox *) GetDlgItem(IDC_DOCKED)) -> GetItemData(m_docked);
		initialize_docker_points();
		initialize_dockee_points();

	} else {  // selected 'nothing' as being docked with
		m_docked_with = m_docker_index = m_dockee_index = m_docker_point = m_dockee_point = -1;
		GetDlgItem(IDC_DOCKER_POINT)->EnableWindow(FALSE);
		GetDlgItem(IDC_DOCKEE_POINT)->EnableWindow(FALSE);
	}

	UpdateData(FALSE);
}

void initial_status::OnSelchangeDockerPoint() 
{
	UpdateData(TRUE);
	UpdateData(TRUE);
	initialize_dockee_points();
	UpdateData(FALSE);
}

void initial_status::OnHasShields() 
{
	if (m_has_shields == 1)
		m_has_shields = 0;
	else
		m_has_shields = 1;

	((CButton *) GetDlgItem(IDC_HAS_SHIELDS))->SetCheck(m_has_shields);
	GetDlgItem(IDC_SHIELDS)->EnableWindow(m_has_shields);
	GetDlgItem(IDC_SHIELDS_SPIN)->EnableWindow(m_has_shields);
}

// function to set the arrival cue of a ship to false
void initial_status::reset_arrival_to_false( int shipnum )
{
	char buf[256];

	// if the cue is not false, make it false.  Be sure to all ship editor dialog functions
	// to update date before and after we modify the cue.
	if ( Ships[shipnum].arrival_cue != Locked_sexp_false ) {
		Ship_editor_dialog.update_data(1);
		free_sexp2(Ships[shipnum].arrival_cue);
		Ships[shipnum].arrival_cue = Locked_sexp_false;
		Ship_editor_dialog.initialize_data(1);
		sprintf(buf, "Setting arrival cue of ship %s\nto false for initial docking purposes.", Ships[shipnum].ship_name);
		MessageBox(buf, "", MB_OK | MB_ICONEXCLAMATION);
	}

	Ships[shipnum].flags |= SF_INITIALLY_DOCKED;
}

void initial_status::OnLocked() 
{
	if (m_locked == 1)
		m_locked = 0;
	else
		m_locked = 1;

	((CButton *) GetDlgItem(IDC_LOCKED))->SetCheck(m_locked);
}
