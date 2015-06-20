/*
 * Copyright (C) Volition, Inc. 1999.  All rights reserved.
 *
 * All source code herein is the property of Volition, Inc. You may not sell 
 * or otherwise commercially exploit the source or things you created based on the 
 * source.
 *
*/

/*
 * $Logfile: /Freespace2/code/FRED2/FREDDoc.h $
 * $Revision: 2 $
 * $Date: 10/07/98 6:28p $
 * $Author: Dave $
 *
 * FREDDoc.h : interface of the CFREDDoc class
 * Document class for document/view architechure, which we don't really use in
 * Fred, but MFC forces you do use like it or not.  Handles loading/saving
 * mainly.  Most of the MFC related stuff is handled in FredView.
 *
 * $Log: /Freespace2/code/FRED2/FREDDoc.h $
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
 * 15    8/17/97 10:22p Hoffoss
 * Fixed several bugs in Fred with Undo feature.  In the process, recoded
 * a lot of CFile.cpp.
 * 
 * 14    8/13/97 5:49p Hoffoss
 * Fixed bugs, made additions.
 * 
 * 13    8/13/97 12:46p Hoffoss
 * Added campaign error checker, accelerator table, and mission goal data
 * listings to sexp tree right click menu.
 * 
 * 12    6/09/97 4:57p Hoffoss
 * Added autosave and undo to Fred.
 * 
 * 11    6/05/97 6:10p Hoffoss
 * Added features: Autosaving, object hiding.  Also fixed some minor bugs.
 * 
 * 10    5/21/97 5:42p Hoffoss
 * Added features requested on Todo list.
 * 
 * 9     2/20/97 4:03p Hoffoss
 * Several ToDo items: new reinforcement clears arrival cue, reinforcement
 * control from ship and wing dialogs, show grid toggle.
 * 
 * 8     2/17/97 5:28p Hoffoss
 * Checked RCS headers, added them were missing, changing description to
 * something better, etc where needed.
 * 
 * 14    2/12/97 12:25p Hoffoss
 * Expanded on global error checker, added initial orders conflict
 * checking and warning, added waypoint editor dialog and code.
 * 
 * 13    1/30/97 2:24p Hoffoss
 * Added remaining mission file structures and implemented load/save of
 * them.
 *
 * $NoKeywords: $
 */

#ifndef _FREDDOC_H
#define _FREDDOC_H

#include "AiLocal.h"
#include "MissionSave.h"

#define MISSION_BACKUP_NAME	"Backup"

#define	US_WORLD_CHANGED	0x01
#define	US_VIEW_CHANGED		0x02

class CFREDDoc : public CDocument
{
protected: // create from serialization only
	CFREDDoc();
	DECLARE_DYNCREATE(CFREDDoc)

// Attributes
public:
	int check_undo();
	int autoload();
	int load_mission(char *pathname);
	int autosave(char *desc);
	int save_matrix(matrix &m, FILE *fp);
	int save_vector(vector &v, FILE *fp);
	BOOL confirm_deleting;
	BOOL show_capital_ships;
	BOOL show_elevations;
	BOOL show_fighters;
	BOOL show_grid;
	BOOL show_misc_objects;
	BOOL show_planets;
	BOOL show_waypoints;
	BOOL show_starfield;
	char mission_pathname[256];

// Operations
public:
	CString undo_desc[BACKUP_DEPTH + 1];

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFREDDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual void OnEditClearAll();
	virtual void DeleteContents();
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CFREDDoc();
	static void UpdateStatus(int flags = US_WORLD_CHANGED);

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext &dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CFREDDoc)
	afx_msg void OnEditDelete();
	afx_msg void OnDuplicate();
	afx_msg void OnEditCopy();
	afx_msg void OnEditCut();
	afx_msg void OnEditHold();
	afx_msg void OnEditFetch();
	afx_msg void OnEditPaste();
	afx_msg void OnEditUndo();
	afx_msg void OnFilePreferences();
	afx_msg void OnFileSave();
	afx_msg void OnFileNew();
	afx_msg void editor_init_mission();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	int save_waypoint_list(waypoint_list &w, FILE *fp);
	int save_waypoints(FILE *fp);
	int save_goals(FILE *fp);
	int save_wings(FILE *fp);
	int save_objects(FILE *fp);
	int save_players(FILE *fp);
	int save_briefing_info(FILE *fp);
	int save_plot_info(FILE *fp);
	int save_mission_info(FILE *FP);
};

extern int Local_modified;
extern int Undo_available;
extern int Undo_count;
extern CFREDDoc *FREDDoc_ptr;

void set_modified(BOOL arg = TRUE);

/////////////////////////////////////////////////////////////////////////////

#endif