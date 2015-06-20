/*
 * Copyright (C) Volition, Inc. 1999.  All rights reserved.
 *
 * All source code herein is the property of Volition, Inc. You may not sell 
 * or otherwise commercially exploit the source or things you created based on the 
 * source.
 *
*/

/*
 * $Logfile: /Freespace2/code/FRED2/MissionSave.h $
 * $Revision: 4 $
 * $Date: 1/19/99 3:57p $
 * $Author: Andsager $
 *
 * Mission saving in Fred.
 *
 * $Log: /Freespace2/code/FRED2/MissionSave.h $
 * 
 * 4     1/19/99 3:57p Andsager
 * Round 2 of variables
 * 
 * 3     10/29/98 6:49p Dave
 * Finished up Fred support for externalizing mission and campaign files.
 * 
 * 2     10/07/98 6:28p Dave
 * Initial checkin. Renamed all relevant stuff to be Fred2 instead of
 * Fred. Globalized mission and campaign file extensions. Removed Silent
 * Threat specific code.
 * 
 * 1     10/07/98 3:00p Dave
 * 
 * 21    9/10/98 1:17p Dave
 * Put in code to flag missions and campaigns as being MD or not in Fred
 * and Freespace. Put in multiplayer support for filtering out MD
 * missions. Put in multiplayer popups for warning of non-valid missions.
 * 
 * 20    4/14/98 11:55a Allender
 * add end-of-campaign sexpression to allow for mission replay at the end
 * of campaigns
 * 
 * 19    3/05/98 3:59p Hoffoss
 * Added a bunch of new command brief stuff, and asteroid initialization
 * to Fred.
 * 
 * 18    9/30/97 5:56p Hoffoss
 * Added music selection combo boxes to Fred.
 * 
 * 17    8/25/97 5:56p Hoffoss
 * Added multiple asteroid field support, loading and saving of asteroid
 * fields, and ship score field to Fred.
 * 
 * 16    8/17/97 10:22p Hoffoss
 * Fixed several bugs in Fred with Undo feature.  In the process, recoded
 * a lot of CFile.cpp.
 * 
 * 15    6/17/97 3:01p Lawrance
 * allow FRED to save new briefing format
 * 
 * 14    6/09/97 4:57p Hoffoss
 * Added autosave and undo to Fred.
 * 
 * 13    6/05/97 6:10p Hoffoss
 * Added features: Autosaving, object hiding.  Also fixed some minor bugs.
 * 
 * 12    5/13/97 10:52a Hoffoss
 * Added campaign saving code.
 * 
 * 11    4/21/97 5:02p Hoffoss
 * Player/player status editing supported, and both saved and loaded from
 * Mission files.
 * 
 * 10    4/16/97 2:05p Hoffoss
 * Mission saving and loading of turret info now implemented.
 * 
 * 9     3/10/97 6:43p Hoffoss
 * Standardized docking goal usage by fred to use names instead of
 * indexes.
 * 
 * 8     2/05/97 2:57p Hoffoss
 * Added support for wing goals (initial orders) in Fred.
 * 
 * 7     1/30/97 2:24p Hoffoss
 * Added remaining mission file structures and implemented load/save of
 * them.
 *
 * $NoKeywords: $
 */

#ifndef __MISSION_SAVE_CPP__
#define __MISSION_SAVE_CPP__

#include <stdio.h>
#include "MissionParse.h"
#include "ParseLo.h"
#include "AiLocal.h"
#include "Ai.h"

#define BACKUP_DEPTH	9

class CFred_mission_save {
private:
	char *raw_ptr;
	int err;
	CFILE *fp;

	int save_mission_info();
	int save_plot_info();
	int save_variables();
//	int save_briefing_info();
	int save_cmd_brief();
	int save_cmd_briefs();
	int save_briefing();
	int save_debriefing();
	int save_players();
	int save_objects();
	int save_common_object_data(object *objp, ship *shipp);
	int save_wings();
	int save_goals();
	int save_waypoints();
	int save_waypoint_list(waypoint_list &w);
	int save_vector(vector &v);
	int save_matrix(matrix &m);
	int save_messages();
	int save_events();
	int save_asteroid_fields();
	int save_music();
	void save_campaign_sexp(int node, int link);

public:
	void save_turret_info(ship_subsys *ptr, int ship);
	int save_bitmaps();
	int save_reinforcements();
	void save_ai_goals(ai_goals *goalp, int ship);
	int fout(char *format, ...);
	int fout_ext(char *format, ...);
	void parse_comments(int = 1);
	CFred_mission_save() : err(0), raw_ptr(Mission_text_raw) { }
	int save_mission_file(char *pathname);
	int autosave_mission_file(char *pathname);
	int save_campaign_file(char *pathname);		
};

#endif