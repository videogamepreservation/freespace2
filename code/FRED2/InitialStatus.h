/*
 * Copyright (C) Volition, Inc. 1999.  All rights reserved.
 *
 * All source code herein is the property of Volition, Inc. You may not sell 
 * or otherwise commercially exploit the source or things you created based on the 
 * source.
 *
*/

// InitialStatus.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// initial_status dialog

class initial_status : public CDialog
{
// Construction
public:
	void undock(int obj);
	void OnOK();
	int inited;
	void change_subsys();
	initial_status(CWnd* pParent = NULL);   // standard constructor
	void initialize_docker_points();
	void initialize_dockee_points();

	int m_ship;
	int m_docked_with;
	int m_multi_edit;

// Dialog Data
	//{{AFX_DATA(initial_status)
	enum { IDD = IDD_INITIAL_STATUS };
	CSpinButtonCtrl	m_hull_spin;
	CSpinButtonCtrl	m_velocity_spin;
	CSpinButtonCtrl	m_shields_spin;
	CSpinButtonCtrl	m_damage_spin;
	int		m_damage;
	int		m_docked;
	int		m_shields;
	int		m_velocity;
	int		m_hull;
	int		m_dockee_point;
	int		m_docker_point;
	BOOL	m_has_shields;
	int		m_locked;
	CString	m_cargo_name;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(initial_status)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(initial_status)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeSubsys();
	afx_msg void OnSelchangeDocked();
	afx_msg void OnSelchangeDockerPoint();
	afx_msg void OnHasShields();
	afx_msg void OnLocked();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void reset_arrival_to_false( int shipnum );
	int cur_subsys;
	int m_docker_index;
	int m_dockee_index;
};
