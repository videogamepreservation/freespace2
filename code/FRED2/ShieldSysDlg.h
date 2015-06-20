/*
 * Copyright (C) Volition, Inc. 1999.  All rights reserved.
 *
 * All source code herein is the property of Volition, Inc. You may not sell 
 * or otherwise commercially exploit the source or things you created based on the 
 * source.
 *
*/

/*
 * $Logfile: /Freespace2/code/FRED2/ShieldSysDlg.h $
 * $Revision: 2 $
 * $Date: 10/07/98 6:28p $
 * $Author: Dave $
 *
 * Shield generator system editor.  This dialog allows one to indicate whether all ships
 * (on a certain team or of a certain type) have a shield system or not.
 *
 * $Log: /Freespace2/code/FRED2/ShieldSysDlg.h $
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
 * 2     8/18/97 9:31p Hoffoss
 * Added grid adjustment dialog and shield system editor dialog.
 *
 * $NoKeywords: $
 */

extern int Shield_sys_teams[MAX_TEAM_NAMES];
extern int Shield_sys_types[MAX_SHIP_TYPES];

/////////////////////////////////////////////////////////////////////////////
// shield_sys_dlg dialog

class shield_sys_dlg : public CDialog
{
// Construction
public:
	void set_team();
	void set_type();
	shield_sys_dlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(shield_sys_dlg)
	enum { IDD = IDD_SHIELD_SYS };
	int		m_team;
	int		m_type;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(shield_sys_dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(shield_sys_dlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeTeam();
	afx_msg void OnSelchangeType();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
