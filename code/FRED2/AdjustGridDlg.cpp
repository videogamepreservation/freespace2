/*
 * Copyright (C) Volition, Inc. 1999.  All rights reserved.
 *
 * All source code herein is the property of Volition, Inc. You may not sell 
 * or otherwise commercially exploit the source or things you created based on the 
 * source.
 *
*/

/*
 * $Logfile: /Freespace2/code/FRED2/AdjustGridDlg.cpp $
 * $Revision: 2 $
 * $Date: 10/07/98 6:28p $
 * $Author: Dave $
 *
 * Editor to allow one to change Fred's grid orientation and position.
 *
 * $Log: /Freespace2/code/FRED2/AdjustGridDlg.cpp $
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
 * 3     8/18/97 10:01p Hoffoss
 * Improved dialog by graying out fields that don't have any effect on
 * current plane setting.
 * 
 * 2     8/18/97 9:31p Hoffoss
 * Added grid adjustment dialog and shield system editor dialog.
 *
 * $NoKeywords: $
 */

#include "stdafx.h"
#include "fred.h"
#include "AdjustGridDlg.h"
#include "MissionGrid.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// adjust_grid_dlg dialog

adjust_grid_dlg::adjust_grid_dlg(CWnd* pParent /*=NULL*/)
	: CDialog(adjust_grid_dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(adjust_grid_dlg)
	m_x = 0;
	m_y = 0;
	m_z = 0;
	//}}AFX_DATA_INIT
}

void adjust_grid_dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(adjust_grid_dlg)
	DDX_Control(pDX, IDC_SPIN_Z, m_spinz);
	DDX_Control(pDX, IDC_SPIN_Y, m_spiny);
	DDX_Control(pDX, IDC_SPIN_X, m_spinx);
	DDX_Text(pDX, IDC_EDIT_X, m_x);
	DDX_Text(pDX, IDC_EDIT_Y, m_y);
	DDX_Text(pDX, IDC_EDIT_Z, m_z);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(adjust_grid_dlg, CDialog)
	//{{AFX_MSG_MAP(adjust_grid_dlg)
	ON_BN_CLICKED(IDC_XY_PLANE, OnXyPlane)
	ON_BN_CLICKED(IDC_XZ_PLANE, OnXzPlane)
	ON_BN_CLICKED(IDC_YZ_PLANE, OnYzPlane)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// adjust_grid_dlg message handlers

BOOL adjust_grid_dlg::OnInitDialog() 
{
	m_x = (int) The_grid->center.x;
	m_y = (int) The_grid->center.y;
	m_z = (int) The_grid->center.z;
	CDialog::OnInitDialog();
	if (The_grid->gmatrix.uvec.y) {
		((CButton *) GetDlgItem(IDC_XZ_PLANE))->SetCheck(TRUE);
		GetDlgItem(IDC_EDIT_X)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_Z)->EnableWindow(FALSE);

	} else if (The_grid->gmatrix.uvec.z) {
		((CButton *) GetDlgItem(IDC_XY_PLANE))->SetCheck(TRUE);
		GetDlgItem(IDC_EDIT_X)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_Y)->EnableWindow(FALSE);

	} else {
		((CButton *) GetDlgItem(IDC_YZ_PLANE))->SetCheck(TRUE);
		GetDlgItem(IDC_EDIT_Y)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_Z)->EnableWindow(FALSE);
	}

	m_spinx.SetRange(99999, -99999);
	m_spiny.SetRange(99999, -99999);
	m_spinz.SetRange(99999, -99999);
	return TRUE;
}

void adjust_grid_dlg::OnOK()
{
	UpdateData(TRUE);
	The_grid->center.x = (float) m_x;
	The_grid->center.y = (float) m_y;
	The_grid->center.z = (float) m_z;

	if (((CButton *) GetDlgItem(IDC_XY_PLANE)) -> GetCheck()) {
		The_grid->gmatrix.fvec = vmd_x_vector;
		The_grid->gmatrix.rvec = vmd_y_vector;

	} else if (((CButton *) GetDlgItem(IDC_YZ_PLANE)) -> GetCheck()) {
		The_grid->gmatrix.fvec = vmd_y_vector;
		The_grid->gmatrix.rvec = vmd_z_vector;

	} else {  // XZ plane
		The_grid->gmatrix.fvec = vmd_x_vector;
		The_grid->gmatrix.rvec = vmd_z_vector;
	}

	modify_grid(The_grid);
	CDialog::OnOK();
}

void adjust_grid_dlg::OnXyPlane() 
{
	GetDlgItem(IDC_EDIT_X)->EnableWindow(FALSE);
	GetDlgItem(IDC_SPIN_X)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_Y)->EnableWindow(FALSE);
	GetDlgItem(IDC_SPIN_Y)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_Z)->EnableWindow(TRUE);
	GetDlgItem(IDC_SPIN_Z)->EnableWindow(TRUE);
}

void adjust_grid_dlg::OnXzPlane() 
{
	GetDlgItem(IDC_EDIT_X)->EnableWindow(FALSE);
	GetDlgItem(IDC_SPIN_X)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_Y)->EnableWindow(TRUE);
	GetDlgItem(IDC_SPIN_Y)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_Z)->EnableWindow(FALSE);
	GetDlgItem(IDC_SPIN_Z)->EnableWindow(FALSE);
}

void adjust_grid_dlg::OnYzPlane() 
{
	GetDlgItem(IDC_EDIT_X)->EnableWindow(TRUE);
	GetDlgItem(IDC_SPIN_X)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_Y)->EnableWindow(FALSE);
	GetDlgItem(IDC_SPIN_Y)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_Z)->EnableWindow(FALSE);
	GetDlgItem(IDC_SPIN_Z)->EnableWindow(FALSE);
}
