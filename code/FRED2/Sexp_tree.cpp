/*
 * Copyright (C) Volition, Inc. 1999.  All rights reserved.
 *
 * All source code herein is the property of Volition, Inc. You may not sell 
 * or otherwise commercially exploit the source or things you created based on the 
 * source.
 *
*/

/*
 * $Logfile: /Freespace2/code/Fred2/Sexp_tree.cpp $
 * $Revision: 43 $
 * $Date: 9/07/99 9:22p $
 * $Author: Jefff $
 *
 * Sexp tree handler class.  Almost everything is handled by this class.
 *
 * $Log: /Freespace2/code/Fred2/Sexp_tree.cpp $
 * 
 * 43    9/07/99 9:22p Jefff
 * added 2 more assignable medals
 * 
 * 42    9/07/99 1:05a Andsager
 * Added team-score sexp for multi team vs team missions
 * 
 * 41    8/27/99 4:07p Andsager
 * Add is-ship-visible sexp.  Make ship-vanish sexp SINGLE player only
 * 
 * 40    8/24/99 4:25p Andsager
 * Add ship-vanish sexp
 * 
 * 39    8/16/99 10:04p Andsager
 * Add special-warp-dist and special-warpout-name sexp for Knossos device
 * warpout.
 * 
 * 38    8/09/99 2:00p Dave
 * 2 new sexpressions.
 * 
 * 37    8/02/99 4:26p Dave
 * Added 2 new sexpressions.
 * 
 * 36    8/02/99 1:43p Andsager
 * format fix
 * 
 * 35    7/28/99 1:36p Andsager
 * Modify cargo1 to include flag CARGO_NO_DEPLETE.  Add sexp
 * cargo-no-deplete (only for BIG / HUGE).  Modify ship struct to pack
 * better.
 * 
 * 34    7/24/99 4:56p Dave
 * Added 3 new sexpressions.
 * 
 * 33    7/21/99 8:10p Dave
 * First run of supernova effect.
 * 
 * 32    7/20/99 9:19p Andsager
 * Added facing waypoint sexp
 * 
 * 31    7/20/99 9:54a Andsager
 * Add subsys-set-random sexp
 * 
 * 30    7/19/99 12:02p Andsager
 * Allow AWACS on any ship subsystem. Fix sexp_set_subsystem_strength to
 * only blow up subsystem if its strength is > 0
 * 
 * 29    7/13/99 3:37p Andsager
 * Add secondaries-depleted sexp
 * 
 * 28    7/12/99 12:01p Andsager
 * Make message by default come from command.
 * 
 * 27    7/08/99 12:06p Andsager
 * Add turret-tagged-only and turret-tagged-clear sexp.
 * 
 * 26    6/29/99 10:08a Andsager
 * Add guardian sexp
 * 
 * 25    6/23/99 5:51p Andsager
 * Add waypoint-cap-speed.  Checkin stealth ai - inactive.
 * 
 * 24    6/16/99 10:21a Dave
 * Added send-message-list sexpression.
 * 
 * 23    6/01/99 8:35p Dave
 * Finished lockarm weapons. Added proper supercap weapons/damage. Added
 * awacs-set-radius sexpression.
 * 
 * 22    5/24/99 11:28a Dave
 * Sexpression for adding/removing ships from the hud escort list.
 * 
 * 21    5/20/99 1:40p Andsager
 * Fix find_text() to only look at nodes that are used.
 * 
 * 20    5/04/99 5:21p Andsager
 * 
 * 19    4/28/99 9:33a Andsager
 * Add turret-free and turret-lock (and -all) sexp.  Stargger start time
 * of beam weapons beam-free and beam-free-all.
 * 
 * 18    4/26/99 2:14p Andsager
 * Add beam-protect-ship and beam-unprotect-ship sexp.
 * 
 * 17    4/23/99 12:01p Johnson
 * Added SIF_HUGE_SHIP
 * 
 * 16    4/02/99 9:54a Dave
 * Added a few more options in the weapons.tbl for beam weapons. Attempt
 * at putting "pain" packets into multiplayer.
 * 
 * 15    3/20/99 3:46p Dave
 * Added support for model-based background nebulae. Added 3 new
 * sexpressions.
 * 
 * 14    3/04/99 6:09p Dave
 * Added in sexpressions for firing beams and checking for if a ship is
 * tagged.
 * 
 * 13    3/01/99 10:00a Dave
 * Fxied several dogfight related stats bugs.
 * 
 * 12    2/26/99 6:01p Andsager
 * Add sexp has-been-tagged-delay and cap-subsys-cargo-known-delay
 * 
 * 11    1/26/99 10:09a Andsager
 * Better checking for modifying/deleting variables
 * 
 * 10    1/25/99 5:16p Andsager
 * Handle change of variable type on modify-variable
 * 
 * 9     1/25/99 8:10a Andsager
 * Add sexp_modify_variable().  Changed syntax checking to allow, adding
 * operator return type ambiguous
 * 
 * 8     1/24/99 11:37p Dave
 * First full rev of beam weapons. Very customizable. Removed some bogus
 * Int3()'s in low level net code.
 * 
 * 7     1/20/99 9:02a Andsager
 * Fix bug in verify_and_fix_arguments, where list of strings can have
 * NULL strings.
 * 
 * 6     1/19/99 3:57p Andsager
 * Round 2 of variables
 * 
 * 5     12/17/98 2:39p Andsager
 * Added bitmaps for campaign editor.  Changed input into insert() to
 * include bitmaps
 * 
 * 4     12/17/98 2:34p Andsager
 * new bitmap and dialog for campaign editor
 * 
 * 3     10/13/98 9:27a Dave
 * Started neatening up freespace.h
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
 * 179   9/25/98 1:33p Andsager
 * Add color to event editor (root and chain) indicating mission directive
 * 
 * 178   9/15/98 4:26p Allender
 * added sexpression help for some sexpressions
 * 
 * 177   6/09/98 5:15p Lawrance
 * French/German localization
 * 
 * 176   5/21/98 12:58a Hoffoss
 * Fixed warnings optimized build turned up.
 * 
 * 175   5/15/98 6:45p Hoffoss
 * Made some things not appear in the release version of Fred.
 * 
 * 174   5/14/98 10:15a Allender
 * add optional argument to prevous-goal/event operators to specify what
 * sexpression should return when being played as a single mission
 * 
 * 173   5/04/98 10:57a Johnson
 * Fixed bug with labeled roots allowing insert.
 * 
 * 172   4/25/98 7:39p Allender
 * fixd some small hotkey stuff.  Worked on turret orientation being
 * correct for multiplayer.  new sexpression called end-campaign will will
 * end the main campaign
 * 
 * 171   4/23/98 5:49p Hoffoss
 * Added tracking of techroom database list info in pilot files, added
 * sexp to add more to list, made mouse usable on ship listing in tech
 * room.
 * 
 * 170   4/15/98 3:46p Hoffoss
 * Fixed bug with getting a default argument value from an opf listing was
 * utilizing temporary memory that was being destroyed before we were
 * finished with it.
 * 
 * 169   4/14/98 5:46p Hoffoss
 * Added special-check operator.
 * 
 * 168   4/14/98 5:24p Hoffoss
 * Added a custom operator for training handling for Mike K.
 * 
 * 167   4/14/98 4:19p Jim
 * Fixed bug with deleting an argument to an operator that you shouldn't
 * be allowed to.
 * 
 * 166   4/07/98 10:51a Allender
 * remove any allied from message senders.  Make heads for mission
 * specific messages play appropriately
 * 
 * 165   4/03/98 12:17a Allender
 * new sexpression to detect departed or destroyed.  optionally disallow
 * support ships.  Allow docking with escape pods 
 * 
 * 164   3/30/98 2:57p Hoffoss
 * Fixed event listing in campaign editor mode.
 * 
 * 163   3/26/98 3:13p Duncan
 * Fixed bug in goal name listing generation function.  Allender forgot
 * about an assumption being made with them when he used it for
 * invalidate-goal.
 * 
 * 162   3/23/98 2:46p Hoffoss
 * Fixed bug with default argument available for OPF_MESSAGE even when
 * there were no messages, and added "#Command" as a message source to
 * listing.
 * 
 * 161   3/21/98 7:36p Lawrance
 * Move jump nodes to own lib.
 * 
 *
 * $NoKeywords: $
 */

#include "stdafx.h"
#include "Sexp_tree.h"
#include "Fred.h"
#include "FredDoc.h"
#include "Management.h"
#include "Sexp.h"
#include "OperatorArgTypeSelect.h"
#include "LinkList.h"
#include "EventEditor.h"
#include "MissionGoalsDlg.h"
#include "AiGoals.h"
#include "MissionMessage.h"
#include "MissionCampaign.h"
#include "CampaignEditorDlg.h"
#include "HudSquadMsg.h"
#include "IgnoreOrdersDlg.h"
#include "Medals.h"
#include "ControlsConfig.h"
#include "HUDgauges.h"
#include "Starfield.h"
#include "JumpNode.h"
#include "AddVariableDlg.h"
#include "ModifyVariableDlg.h"

#define MAX_OP_MENUS	30

#define ID_VARIABLE_MENU	0xda00
#define ID_ADD_MENU			0xdc00
#define ID_REPLACE_MENU		0xde00
// note: stay below 0xe000 so we don't collide with MFC defines..

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(sexp_tree, CTreeCtrl)
	//{{AFX_MSG_MAP(sexp_tree)
	ON_NOTIFY_REFLECT(TVN_BEGINDRAG, OnBegindrag)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_DESTROY()
	ON_WM_LBUTTONDOWN()
	ON_NOTIFY_REFLECT(TVN_KEYDOWN, OnKeydown)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static int Add_count, Replace_count;
static int Modify_variable;

struct sexp_help_struct {
	int id;
	char *help;

} Sexp_help[] = {
	{ OP_PLUS, "Plus (Arithmetic operator)\r\n"
		"\tAdds numbers and returns results.\r\n\r\n"
		"Returns a number; Takes 2 or more numeric arguments." },

	{ OP_MINUS, "Minus (Arithmetic operator)\r\n"
		"\tSubtracts numbers and returns results.\r\n\r\n"
		"Returns a number; Takes 2 or more numeric arguments." },

	{ OP_MOD, "Mod (Arithmetic operator)\r\n"
		"\tDivides numbers and returns the remainer.\r\n\r\n"
		"Returns a number; Takes 2 or more numeric arguments." },

	{ OP_MUL, "Multiply (Arithmetic operator)\r\n"
		"\tMultiplies numbers and returns results.\r\n\r\n"
		"Returns a number; Takes 2 or more numeric arguments." },

	{ OP_DIV, "Divide (Arithmetic operator)\r\n"
		"\tDivides numbers and returns results.\r\n\r\n"
		"Returns a number; Takes 2 or more numeric arguments." },

	{ OP_RAND, "Random number (Arithmetic operator)\r\n"
		"\tGets a random number and returns result.\r\n\r\n"
		"Returns a number; Takes 2 numeric arguments.\r\n"
		"\t1:\tLow range of random number.\r\n"
		"\t2:\tHigh range of random number." },

	{ OP_TRUE, "True (Boolean operator)\r\n"
		"\tA true boolean state\r\n\r\n"
		"Returns a boolean value." },

	{ OP_FALSE, "False (Boolean operator)\r\n"
		"\tA false boolean state\r\n\r\n"
		"Returns a boolean value." },

	{ OP_AND, "And (Boolean operator)\r\n"
		"\tAnd is true if all of it's arguments are true.\r\n\r\n"
		"Returns a boolean value; Takes 2 or more boolean arguments." },

	{ OP_OR, "Or (Boolean operator)\r\n"
		"\tOr is true if any of it's arguments are true.\r\n\r\n"
		"Returns a boolean value; Takes 2 or more boolean arguments." },

	{ OP_EQUALS, "Equals (Boolean operator)\r\n"
		"\tIs true if all of it's arguments are equal.\r\n\r\n"
		"Returns a boolean value; Takes 2 or more numeric arguments." },

	{ OP_GREATER_THAN, "Greater than (Boolean operator)\r\n"
		"\tTrue if first argument is greater than the second argument.\r\n\r\n"
		"Returns a boolean value; Takes 2 numeric arguments." },

	{ OP_LESS_THAN, "Less than (Boolean operator)\r\n"
		"\tTrue if first argument is less than the second argument.\r\n\r\n"
		"Returns a boolean value; Takes 2 numeric arguments." },

	{ OP_IS_IFF, "Is IFF (Boolean operator)\r\n"
		"\tTrue if ship{s} are all of the specified team.\r\n\r\n"
		"Returns a boolean value; Takes 2 or more arguments:\r\n"
		"/t1:\tTeam (\"friendly\", \"hostile\" or \"unknown\").\r\n"
		"\tRest:\tName of ship to check." },

	{ OP_HAS_TIME_ELAPSED, "Has time elapsed (Boolean operator)\r\n"
		"\tBecomes true when the specified amount of time has elapsed (Mission time "
		"becomes greater than the specified time).\r\n"
		"Returns a boolean value; Takes 1 numeric argument:\r\n"
		"\t1:\tThe amount of time in seconds." },

	{ OP_NOT, "Not (Boolean operator)\r\n"
		"\tReturns opposite boolean value of argument (True becomes false, and "
		"false becomes true).\r\n\r\n"
		"Returns a boolean value; Takes 1 boolean argument." },

	{ OP_PREVIOUS_GOAL_TRUE, "Previous Mission Goal True (Boolean operator)\r\n"
		"\tReturns true if the specified goal in the specified mission is true "
		"(or succeeded).  It returns false otherwise.\r\n\r\n"
		"Returns a boolean value; Takes 2 arguments + 1 optional:\r\n"
		"\t1:\tName of the mission.\r\n"
		"\t2:\tName of the goal in the mission.\r\n"
		"\t3:\t(Optional) True/False which signifies what this sexpession should return when "
		"this mission is played as a single mission." },

	{ OP_PREVIOUS_GOAL_FALSE, "Previous Mission Goal False (Boolean operator)\r\n"
		"\tReturns true if the specified goal in the specified mission "
		"is false (or failed).  It returns false otherwise.\r\n\r\n"
		"Returns a boolean value; Takes 2 arguments + 1 optional:\r\n"
		"\t1:\tName of the mission.\r\n"
		"\t2:\tName of the goal in the mission.\r\n"
		"\t3:\t(Optional) True/False which signifies what this sexpession should return when "
		"this mission is played as a single mission." },

	{ OP_PREVIOUS_GOAL_INCOMPLETE, "Previous Mission Goal Incomplete (Boolean operator)\r\n"
		"\tReturns true if the specified goal in the specified mission "
		"is incomplete (not true or false).  It returns false otherwise.\r\n\r\n"
		"Returns a boolean value; Takes 2 arguments + 1 optional:\r\n"
		"\t1:\tName of the mission.\r\n"
		"\t2:\tName of the goal in the mission.\r\n"
		"\t3:\t(Optional) True/False which signifies what this sexpession should return when "
		"this mission is played as a single mission." },

	{ OP_PREVIOUS_EVENT_TRUE, "Previous Mission Event True (Boolean operator)\r\n"
		"\tReturns true if the specified event in the specified mission is true "
		"(or succeeded).  It returns false otherwise.\r\n\r\n"
		"Returns a boolean value; Takes 2 arguments + 1 optional:\r\n"
		"\t1:\tName of the mission.\r\n"
		"\t2:\tName of the event in the mission.\r\n"
		"\t3:\t(Optional) True/False which signifies what this sexpession should return when "
		"this mission is played as a single mission." },

	{ OP_PREVIOUS_EVENT_FALSE, "Previous Mission Event False (Boolean operator)\r\n"
		"\tReturns true if the specified event in the specified mission "
		"is false (or failed).  It returns false otherwise.\r\n\r\n"
		"Returns a boolean value; Takes 2 arguments + 1 optional:\r\n"
		"\t1:\tName of the mission.\r\n"
		"\t2:\tName of the event in the mission.\r\n"
		"\t3:\t(Optional) True/False which signifies what this sexpession should return when "
		"this mission is played as a single mission." },

	{ OP_PREVIOUS_EVENT_INCOMPLETE, "Previous Mission Event Incomplete (Boolean operator)\r\n"
		"\tReturns true if the specified event in the specified mission "
		"is incomplete (not true or false).  It returns false otherwise.\r\n\r\n"
		"Returns a boolean value; Takes 2 arguments + 1 optional:\r\n"
		"\t1:\tName of the mission.\r\n"
		"\t2:\tName of the event in the mission.\r\n"
		"\t3:\t(Optional) True/False which signifies what this sexpession should return when "
		"this mission is played as a single mission." },

	{ OP_GOAL_TRUE_DELAY, "Mission Goal True (Boolean operator)\r\n"
		"\tReturns true N seconds after the specified goal in the this mission is true "
		"(or succeeded).  It returns false otherwise.\r\n\r\n"
		"Returns a boolean value; Takes 2 arguments:\r\n"
		"\t1:\tName of the event in the mission.\r\n"
		"\t2:\tNumber of seconds to delay before returning true."},

	{ OP_GOAL_FALSE_DELAY, "Mission Goal False (Boolean operator)\r\n"
		"\tReturns true N seconds after the specified goal in the this mission is false "
		"(or failed).  It returns false otherwise.\r\n\r\n"
		"Returns a boolean value; Takes 2 arguments:\r\n"
		"\t1:\tName of the event in the mission.\r\n"
		"\t2:\tNumber of seconds to delay before returning true."},

	{ OP_GOAL_INCOMPLETE, "Mission Goal Incomplete (Boolean operator)\r\n"
		"\tReturns true if the specified goal in the this mission is incomplete.  This "
		"sexpression will only be useful in conjunction with another sexpression like"
		"has-time-elapsed.  Used alone, it will return true upon misison startup."
		"Returns a boolean value; Takes 1 argument:\r\n"
		"\t1:\tName of the event in the mission."},

	{ OP_EVENT_TRUE_DELAY, "Mission Event True (Boolean operator)\r\n"
		"\tReturns true N seconds after the specified event in the this mission is true "
		"(or succeeded).  It returns false otherwise.\r\n\r\n"
		"Returns a boolean value; Takes 2 arguments:\r\n"
		"\t1:\tName of the event in the mission.\r\n"
		"\t2:\tNumber of seconds to delay before returning true."},

	{ OP_EVENT_FALSE_DELAY, "Mission Event False (Boolean operator)\r\n"
		"\tReturns true N seconds after the specified event in the this mission is false "
		"(or failed).  It returns false otherwise.\r\n\r\n"
		"Returns a boolean value; Takes 2 arguments:\r\n"
		"\t1:\tName of the event in the mission.\r\n"
		"\t2:\tNumber of seconds to delay before returning true."},

	{ OP_EVENT_INCOMPLETE, "Mission Event Incomplete (Boolean operator)\r\n"
		"\tReturns true if the specified event in the this mission is incomplete.  This "
		"sexpression will only be useful in conjunction with another sexpression like"
		"has-time-elapsed.  Used alone, it will return true upon misison startup."
		"Returns a boolean value; Takes 1 argument:\r\n"
		"\t1:\tName of the event in the mission."},

	{ OP_IS_DESTROYED_DELAY, "Is destroyed delay (Boolean operator)\r\n"
		"\tBecomes true <delay> seconds after all specified ships have been destroyed.\r\n\r\n"
		"Returns a boolean value; Takes 2 or more arguments:\r\n"
		"\t1:\tTime delay in seconds (see above).\r\n"
		"\tRest:\tName of ship (or wing) to check status of." },

	{ OP_IS_SUBSYSTEM_DESTROYED_DELAY, "Is subsystem destroyed delay (Boolean operator)\r\n"
		"\tBecomes true <delay> seconds after the specified subsystem of the specified "
		"ship is destroyed.\r\n\r\n"
		"Returns a boolean value; Takes 3 arguments:\r\n"
		"\t1:\tName of ship the subsystem we are checking is on.\r\n"
		"\t2:\tThe name of the subsystem we are checking status of.\r\n"
		"\t3:\tTime delay in seconds (see above)." },

	{ OP_IS_DISABLED_DELAY, "Is disabled delay (Boolean operator)\r\n"
		"\tBecomes true <delay> seconds after the specified ship(s) are disabled.  A "
		"ship is disabled when all of it's engine subsystems are destroyed.  All "
		"ships must be diabled for this function to return true.\r\n\r\n"
		"Returns a boolean value; Takes 2 or more arguments:\r\n"
		"\t1:\tTime delay is seconds (see above).\r\n"
		"\tRest:\tNames of ships to check disabled status of." },

	{ OP_IS_DISARMED_DELAY, "Is disarmed delay (Boolean operator)\r\n"
		"\tBecomes true <delay> seconds after the specified ship(s) are disarmed.  A "
		"ship is disarmed when all of it's turret subsystems are destroyed.  All "
		"ships must be disarmed for this function to return true.\r\n\r\n"
		"Returns a boolean value; Takes 2 or more arguments:\r\n"
		"\t1:\tTime delay is seconds (see above).\r\n"
		"\tRest:\tNames of ships to check disarmed status of." },

	{ OP_HAS_DOCKED_DELAY, "Has docked delay (Boolean operator)\r\n"
		"\tBecomes true <delay> seconds after the specified ships have docked the "
		"specified number of times.\r\n\r\n"
		"Returns a boolean value; Takes 4 arguments:\r\n"
		"\t1:\tThe name of the docker ship\r\n"
		"\t2:\tThe name of the dockee ship\r\n"
		"\t3:\tThe number of times they have to have docked\r\n"
		"\t4:\tTime delay in seconds (see above)." },

	{ OP_HAS_UNDOCKED_DELAY, "Has undocked delay (Boolean operator)\r\n"
		"\tBecomes true <delay> seconds after the specified ships have undocked the "
		"specified number of times.\r\n\r\n"
		"Returns a boolean value; Takes 4 arguments:\r\n"
		"\t1:\tThe name of the docker ship\r\n"
		"\t2:\tThe name of the dockee ship\r\n"
		"\t3:\tThe number of times they have to have undocked\r\n"
		"\t4:\tTime delay in seconds (see above)." },

	{ OP_HAS_ARRIVED_DELAY, "Has arrived delay (Boolean operator)\r\n"
		"\tBecomes true <delay> seconds after the specified ship(s) have arrived into the mission\r\n\r\n"
		"Returns a boolean value; Takes 2 or more arguments:\r\n"
		"\t1:\tTime delay in seconds (see above).\r\n"
		"\tRest:\tName of ship (or wing) we want to check has arrived." },

	{ OP_HAS_DEPARTED_DELAY, "Has departed delay (Boolean operator)\r\n"
		"\tBecomes true <delay> seconds after the specified ship(s) or wing(s) have departed "
		"from the mission by warping out.  If any ship was destroyed, this operator will "
		"never be true.\r\n\r\n"
		"Returns a boolean value; Takes 2 or more arguments:\r\n"
		"\t1:\tTime delay in seconds (see above).\r\n"
		"\tRest:\tName of ship (or wing) we want to check has departed." },

	{ OP_WAYPOINTS_DONE_DELAY, "Waypoints done delay (Boolean operator)\r\n"
		"\tBecomes true <delay> seconds after the specified ship has completed flying the "
		"specified waypoint path.\r\n\r\n"
		"Returns a boolean value; Takes 3 arguments:\r\n"
		"\t1:\tName of ship we are checking.\r\n"
		"\t2:\tWaypoint path we want to check if ship has flown.\r\n"
		"\t3:\tTime delay in seconds (see above)." },

	{ OP_SHIP_TYPE_DESTROYED, "Ship Type Destroyed (Boolean operator)\r\n"
		"\tBecomes true when the specified percentage of ship types in this mission "
		"have been destroyed.  The ship type is a generic type such as fighter/bomber, "
		"transport, etc.  Fighters and bombers count as the same type.\r\n\r\n"
		"Returns a boolean value; Takes 2 arguments:\r\n"
		"\t1:\tPercentage of ships that must be destroyed.\r\n"
		"\t2:\tShip type to check for." },

	{ OP_TIME_SHIP_DESTROYED, "Time ship destroyed (Time operator)\r\n"
		"\tReturns the time the specified ship was destroy.\r\n\r\n"
		"Returns a numeric value; Takes 1 argument:\r\n"
		"\t1:\tName of ship we want to check." },

	{ OP_TIME_SHIP_ARRIVED, "Time ship arrived (Time operator)\r\n"
		"\tReturns the time the specified ship arrived into the mission.\r\n\r\n"
		"Returns a numeric value; Takes 1 argument:\r\n"
		"\t1:\tName of ship we want to check." },

	{ OP_TIME_SHIP_DEPARTED, "Time ship departed (Time operator)\r\n"
		"\tReturns the time the specified ship departed the mission by warping out.  Being "
		"destroyed doesn't count departed.\r\n\r\n"
		"Returns a numeric value; Takes 1 argument:\r\n"
		"\t1:\tName of ship we want to check." },

	{ OP_TIME_WING_DESTROYED, "Time wing destroyed (Time operator)\r\n"
		"\tReturns the time the specified wing was destroy.\r\n\r\n"
		"Returns a numeric value; Takes 1 argument:\r\n"
		"\t1:\tName of wing we want to check." },

	{ OP_TIME_WING_ARRIVED, "Time wing arrived (Time operator)\r\n"
		"\tReturns the time the specified wing arrived into the mission.\r\n\r\n"
		"Returns a numeric value; Takes 1 argument:\r\n"
		"\t1:\tName of wing we want to check." },

	{ OP_TIME_WING_DEPARTED, "Time wing departed (Time operator)\r\n"
		"\tReturns the time the specified wing departed the mission by warping out.  All "
		"ships in the wing have to have warped out.  If any are destroyed, the wing can "
		"never be considered departed.\r\n\r\n"
		"Returns a numeric value; Takes 1 argument:\r\n"
		"\t1:\tName of ship we want to check." },

	{ OP_MISSION_TIME, "Mission time (Time operator)\r\n"
		"\tReturns the current time into the mission.\r\n\r\n"
		"Returns a numeric value." },

	{ OP_TIME_DOCKED, "Time docked (Time operator)\r\n"
		"\tReturns the time the specified ships docked.\r\n\r\n"
		"Returns a numeric value; Takes 3 arguments:\r\n"
		"\t1:\tThe name of the docker ship.\r\n"
		"\t2:\tThe name of the dockee ship.\r\n"
		"\t3:\tThe number of times they must have docked to be true." },

	{ OP_TIME_UNDOCKED, "Time undocked (Time operator)\r\n"
		"\tReturns the time the specified ships undocked.\r\n\r\n"
		"Returns a numeric value; Takes 3 arguments:\r\n"
		"\t1:\tThe name of the docker ship.\r\n"
		"\t2:\tThe name of the dockee ship.\r\n"
		"\t3:\tThe number of times they must have undocked to be true." },

	{ OP_SHIELDS_LEFT, "Sheilds left (Status operator)\r\n"
		"\tReturns the current level of the specified ship's shields as a percentage.\r\n\r\n"
		"Returns a numeric value; Takes 1 argument:\r\n"
		"\t1:\tName of ship to check." },

	{ OP_HITS_LEFT, "Hits left (Status operator)\r\n"
		"\tReturns the current level of the specified ship's hull as a percentage.\r\n\r\n"
		"Returns a numeric value; Takes 1 argument:\r\n"
		"\t1:\tName of ship to check." },

	{ OP_HITS_LEFT_SUBSYSTEM, "Hits left subsystem (Status operator)\r\n"
		"\tReturns the current level of the specified ship's subsystem integrity as a percentage.\r\n\r\n"
		"Returns a numeric value; Takes 1 argument:\r\n"
		"\t1:\tName of ship to check.\r\n"
		"\t2:\tName of subsystem on ship to check." },

	{ OP_DISTANCE, "Distance (Misc. Operator)\r\n"
		"\tReturns the distance between 2 objects.  These objects can be either a ship, "
		"a wing, or a waypoint.\r\n\r\n"
		"Returns a numeric value; Takes 2 arguments:\r\n"
		"\t1:\tThe name of one of the objects.\r\n"
		"\t2:\tThe name of the other object." },

	{ OP_LAST_ORDER_TIME, "Last order time (Status operator)\r\n"
		"\tReturns true if <count> seconds have elapsed since one or more ships have received "
		"a meaningful order from the player.  A meaningful order is currently any order that "
		"is not the warp out order.\r\n\r\n"
		"Returns a boolean value; Takes 2 or more arguments:\r\n"
		"\t1:\tTime in seconds that must elapse.\r\n"
		"\tRest:\tName of ship or wing to check for having received orders." },

	{ OP_WHEN, "When (Conditional operator)\r\n"
		"\tPerforms specified actions when a condition becomes true\r\n\r\n"
		"Takes 2 or more arguments:\r\n"
		"\t1:\tBoolean expression that must be true for actions to take place.\r\n"
		"\tRest:\tActions to take when boolean expression becomes true." },

	{ OP_COND, "Blah" },

	{ OP_CHANGE_IFF, "Change IFF (Action operator)\r\n"
		"\tSets the specified ship(s) to the specified team.\r\n"
		"Takes 2 or more arguments:\r\n"
		"\t1:\tTeam to change to (\"friendly\", \"hostile\" or \"unknown\").\r\n"
		"\tRest:\tName of ship to change team status of." },

	{ OP_MODIFY_VARIABLE, "Modify-variable (Misc. operator)\r\n"
		"\tModifies variable to specified value\r\n\r\n"
		"Takes 2 arguments:\r\n"
		"\t1:\tName of Variable.\r\n"
		"\t2:\tValue to be set." },

	{ OP_PROTECT_SHIP, "Protect ship (Action operator)\r\n"
		"\tProtects a ship from being attacked by any enemy ship.  Any ship"
		"that is protected will not come under enemy fire.\r\n\r\n"
		"Takes 1 or more arguments:\r\n"
		"\tAll:\tName of ship(s) to protect." },

	{ OP_UNPROTECT_SHIP, "Unprotect ship (Action operator)\r\n"
		"\tUnprotects a ship from being attacked by any enemy ship.  Any ship"
		"that is not protected can come under enemy fire.  This function is the opposite"
		"of protect-ship.\r\n\r\n"
		"Takes 1 or more arguments:\r\n"
		"\tAll:\tName of ship(s) to protect." },

	{ OP_BEAM_PROTECT_SHIP, "Beam Protect ship (Action operator)\r\n"
		"\tProtects a ship from being attacked with beam weapon.  Any ship"
		"that is beam protected will not come under enemy beam fire.\r\n\r\n"
		"Takes 1 or more arguments:\r\n"
		"\tAll:\tName of ship(s) to protect." },

	{ OP_BEAM_UNPROTECT_SHIP, "Beam Unprotect ship (Action operator)\r\n"
		"\tUnprotects a ship from being attacked with beam weapon.  Any ship"
		"that is not beam protected can come under enemy beam fire.  This function is the opposite"
		"of beam-protect-ship.\r\n\r\n"
		"Takes 1 or more arguments:\r\n"
		"\tAll:\tName of ship(s) to protect." },

	{ OP_SEND_MESSAGE, "Send message (Action operator)\r\n"
		"\tSends a message to the player.  Can be send by a ship, wing, or special "
		"source.  To send it from a special source, make the first character of the first "
		"argument a \"#\".\r\n\r\n"
		"Takes 3 arguments:\r\n"
		"\t1:\tName of who the message is from.\r\n"
		"\t2:\tPriority of message (\"Low\", \"Normal\" or \"High\").\r\n"
		"\t3:\tName of message (from message editor)." },

	{ OP_SELF_DESTRUCT, "Self destruct (Action operator)\r\n"
		"\tCauses the specified ship(s) to self destruct.\r\n\r\n"
		"Takes 1 or more arguments:\r\n"
		"\tAll:\tName of ship to self destruct." },

	{ OP_NEXT_MISSION, "Next Mission (Action operator)\r\n"
		"\tThe next mission operator is used for campaign branching in the campaign editor.  "
		"It specifies which mission should played be next in the campaign.  This operator "
		"generally follows a 'when' or 'cond' statment in the campaign file.\r\n\r\n"
		"Takes 1 argument:\r\n"
		"\t1:\tName of mission (filename) to proceed to." },

	{ OP_CLEAR_GOALS, "Clear goals (Action operator)\r\n"
		"\tClears the goals for the specified ships and/or wings.\r\n\r\n"
		"Takes 1 or more arguments:\r\n"
		"\tAll:\tName of ship or wing." },

	{ OP_ADD_GOAL, "Add goal (Action operator)\r\n"
		"\tAdds a goal to a ship or wing.\r\n\r\n"
		"Takes 2 arguments:\r\n"
		"\t1:\tName of ship or wing to all goal to.\r\n"
		"\t2:\tGoal to add." },

	{ OP_SABOTAGE_SUBSYSTEM, "Sabotage subystem (Action operator)\r\n"
		"\tReduces the specified subsystem integrity by the specified percentage."
		"If the percntage strength of the subsystem (after completion) is less than 0%,"
		"subsystem strength is set to 0%.\r\n\r\n"
		"Takes 3 arguments:\r\n"
		"\t1:\tName of ship subsystem is on.\r\n"
		"\t2:\tName of subsystem to sabotage.\r\n"
		"\t3:\tPercentage to reduce subsystem integrity by." },

	{ OP_REPAIR_SUBSYSTEM, "Repair Subystem (Action operator)\r\n"
		"\tIncreases the specified subsystem integrity by the specified percentage."
		"If the percntage strength of the subsystem (after completion) is greater than 100%,"
		"subsystem strength is set to 100%.\r\n\r\n"
		"Takes 3 arguments:\r\n"
		"\t1:\tName of ship subsystem is on.\r\n"
		"\t2:\tName of subsystem to repair.\r\n"
		"\t3:\tPercentage to increase subsystem integrity by." },

	{ OP_SET_SUBSYSTEM_STRNGTH, "Set Subsystem Strength (Action operator)\r\n"
		"\tSets the specified subsystem to the the specified percentage."
		"If the percentage specified is < 0, strength is set to 0.  If the percentage is "
		"> 100 % the subsystem strength is set to 100%.\r\n\r\n"
		"Takes 3 arguments:\r\n"
		"\t1:\tName of ship subsystem is on.\r\n"
		"\t2:\tName of subsystem to set strength.\r\n"
		"\t3:\tPercentage to set subsystem integrity to." },

	{ OP_INVALIDATE_GOAL, "Invalidate goal (Action operator)\r\n"
		"\tMakes a mission goal invalid, which causes it to now show up on mission goals "
		"screen, or be evaluated.\r\n"
		"Takes 1 or more arguments:\r\n"
		"\tAll:\tName of mission goal to invalidate." },

	{ OP_VALIDATE_GOAL, "Validate goal (Action operator)\r\n"
		"\tMakes a mission goal valid again, so it shows up on mission goals screen.\r\n"
		"Takes 1 or more arguments:\r\n"
		"\tAll:\tName of mission goal to validate." },

	{ OP_SEND_RANDOM_MESSAGE, "Send random message (Action operator)\r\n"
		"\tSends a random message to the player from those supplied.  Can be send by a "
		"ship, wing, or special source.  To send it from a special source, make the first "
		"character of the first argument a \"#\".\r\n\r\n"
		"Takes 3 or more arguments:\r\n"
		"\t1:\tName of who the message is from.\r\n"
		"\t2:\tPriority of message (\"Low\", \"Normal\" or \"High\")."
		"\tRest:\tName of message (from message editor)." },

	{ OP_TRANSFER_CARGO, "Transfer Cargo (Action operator)\r\n"
		"\tTransfers the cargo from one ship to another ship.\r\n\r\n"
		"Takes 2 arguments:\r\n"
		"\t1:\tName of ship that cargo is being transferred from.\r\n"
		"\t2:\tName of ship that cargo is being transferred to." },

	{ OP_EXCHANGE_CARGO, "Exchange Cargo (Action operator)"
		"\tExchanges the cargos of two ships.  If one of the two ships contains no cargo, "
		"the cargo is transferred instead.\r\n"
		"Takes 2 arguments:\r\n"
		"\t1:\tName of one of the ships.\r\n"
		"\t2:\tName of the other ship." },

	{ OP_INT3, "Error (Debug directive)\r\n"
		"Causes the game to halt with an error." },

	{ OP_AI_CHASE, "Ai-chase (Ship goal)\r\n"
		"\tCauses the specified ship to chase and attack the specified target.\r\n\r\n"
		"Takes 2 arguments:\r\n"
		"\t1:\tName of ship to chase.\r\n"
		"\t2:\tGoal priority (number between 0 and 89)." },

	{ OP_AI_DOCK, "Ai-dock (Ship goal)\r\n"
		"\tCauses one ship to dock with another ship.\r\n\r\n"
		"Takes 4 arguments:\r\n"
		"\t1:\tName of dockee ship (The ship that \"docker\" will dock with).\r\n"
		"\t2:\tDocker's docking point - Which dock point docker uses to dock.\r\n"
		"\t3:\tDockee's docking point - Which dock point on dockee docker will move to.\r\n"
		"\t4:\tGoal priority (number between 0 and 89)." },

	{ OP_AI_UNDOCK, "Ai-undock (Ship goal)\r\n"
		"\tCauses the specified ship to undock from who it is currently docked with.\r\n\r\n"
		"Takes 1 arguments:\r\n"
		"\t1:\tGoal priority (number between 0 and 89)." },

	{ OP_AI_WARP_OUT, "Ai-warp-out (Ship/Wing Goal)\r\n"
		"\tCauses the specified ship/wing to warp out of the mission.  Currently, the ship will "
		"warp out at it's current location.  This behavior will change.  Currently, the first "
		"argument means nothing.\r\n\r\n"
		"Takes 2 arguments:\r\n"
		"\t1:\tName of waypoint path to follow to warp out (not used).\r\n"
		"\t2:\tGoal priority (number between 0 and 89)." },

	{ OP_AI_WAYPOINTS, "Ai-waypoints (Ship goal)\r\n"
		"\tCauses the specified ship to fly a waypoint path continuously.\r\n\r\n"
		"Takes 2 arguments:\r\n"
		"\t1:\tName of waypoint path to fly.\r\n"
		"\t2:\tGoal priority (number between 0 and 89)." },

	{ OP_AI_WAYPOINTS_ONCE, "Ai-waypoints once (Ship goal)\r\n"
		"\tCauses the specified ship to fly a waypoint path.\r\n\r\n"
		"Takes 2 arguments:\r\n"
		"\t1:\tName of waypoint path to fly.\r\n"
		"\t2:\tGoal priority (number between 0 and 89)." },

	{ OP_AI_DESTROY_SUBSYS, "Ai-destroy subsys (Ship goal)\r\n"
		"\tCauses the specified ship to attack and try and destroy the specified subsystem "
		"on the specified ship.\r\n\r\n"
		"Takes 3 arguments:\r\n"
		"\t1:\tName of ship subsystem is on.\r\n"
		"\t2:\tName of subsystem on the ship to attack and destroy.\r\n"
		"\t3:\tGoal priority (number between 0 and 89)." },

	{ OP_AI_CHASE_WING, "Ai-chase wing (Ship goal)\r\n"
		"\tCauses the specified ship to chase and attack the specified target.\r\n\r\n"
		"Takes 2 arguments:\r\n"
		"\t1:\tName of wing to chase.\r\n"
		"\t2:\tGoal priority (number between 0 and 89)." },

	{ OP_AI_DISABLE_SHIP, "Ai-disable-ship (Ship/wing goal)\r\n"
		"\tThis AI goal causes a ship/wing to destroy all of the engine subsystems on "
		"the specified ship.  This goal is different than ai-destroy-subsystem since a ship "
		"may have multiple engine subsystems requiring the use of > 1 ai-destroy-subsystem "
		"goals.\r\n\r\n"
		"Takes 2 arguments:\r\n"
		"\t1:\tName of ship whose engine subsystems should be destroyed\r\n"
		"\t2:\tGoal priority (number between 0 and 89)." },

	{ OP_AI_DISARM_SHIP, "Ai-disarm-ship (Ship/wing goal)\r\n"
		"\tThis AI goal causes a ship/wing to destroy all of the turret subsystems on "
		"the specified ship.  This goal is different than ai-destroy-subsystem since a ship "
		"may have multiple turret subsystems requiring the use of > 1 ai-destroy-subsystem "
		"goals.\r\n\r\n"
		"Takes 2 arguments:\r\n"
		"\t1:\tName of ship whose turret subsystems should be destroyed\r\n"
		"\t2:\tGoal priority (number between 0 and 89)." },

	{ OP_AI_GUARD, "Ai-guard (Ship goal)\r\n"
		"\tCauses the specified ship to guard a ship from other ships not on the same team.\r\n\r\n"
		"Takes 2 arguments:\r\n"
		"\t1:\tName of ship to guard.\r\n"
		"\t2:\tGoal priority (number between 0 and 89)." },

	{ OP_AI_CHASE_ANY, "Ai-chase any (Ship goal)\r\n"
		"\tCauses the specified ship to chase and attack any ship on the opposite team.\r\n\r\n"
		"Takes 1 arguments:\r\n"
		"\t1:\tGoal priority (number between 0 and 89)." },

	{ OP_AI_GUARD_WING, "Ai-guard wing (Ship goal)\r\n"
		"\tCauses the specified ship to guard a wing of ships from other ships not on the "
		"same team.\r\n\r\n"
		"Takes 2 arguments:\r\n"
		"\t1:\tName of wing to guard.\r\n"
		"\t2:\tGoal priority (number between 0 and 89)." },

	{ OP_NOP, "Do-nothing (Action operator)\r\n"
		"\tDoes nothing.  This is used as the default for any required action arguments "
		"of an operator." },

	{ OP_KEY_PRESSED, "Key-pressed (Boolean training operator)\r\n"
		"\tBecomes true when the specified default key has been pressed.  Default key "
		"refers to the what the key normally is when not remapped.  FreeSpace will "
		"automatically account for any keys that have been remapped.  If the optional "
		"delay is specified, becomes true that many seconds after the key has been pressed.\r\n\r\n"
		"Returns a boolean value; Takes 1 or 2 arguments:\r\n"
		"\t1:\tDefault key to check for.\r\n"
		"\t2:\tDelay before operator registers as true (optional).\r\n" },

	{ OP_KEY_RESET, "Key-reset (Training operator)\r\n"
		"\tMarks the specified default key as having not been pressed, so key-pressed will be false "
		"until the player presses it again.  See key-pressed help for more information about "
		"what a default key is.\r\n\r\n"
		"Returns a boolean value; Takes 1 argument:\r\n"
		"\t1:\tDefault key to reset." },

	{ OP_TARGETED, "Targeted (Boolean training operator)\r\n"
		"\tIs true as long as the player has the specified ship (or ship's subsystem) targeted, "
		"or has been targeted for the specified amount of time.\r\n\r\n"
		"Returns a boolean value; Takes 1 to 3 arguments (first required, rest optional):\r\n"
		"\t1:\tName of ship to check if targeted by player.\r\n"
		"\t2:\tLength of time target should have been kept for (optional).\r\n"
		"\t3:\tName of subsystem on ship to check if targeted (optional)." },

	{ OP_SPEED, "Speed (Boolean training operator)\r\n"
		"\tBecomes true when the player has been within the specified speed range set by "
		"set-training-context-speed for the specified amount of time.\r\n\r\n"
		"Returns a boolean value; Takes 1 argument:\r\n"
		"\t1:\tTime in seconds." },

	{ OP_FACING, "Facing (Boolean training operator)\r\n"
		"\tIs true as long as the specified ship is within the player's specified "
		"forward cone.  A forward cone is defined as any point that the angle between the "
		"vector of the point and the player, and the forward facing vector is within the "
		"given angle.\r\n\r\n"
		"Returns a boolean value; Takes 2 argument:\r\n"
		"\t1:\tShip to check is withing forward cone.\r\n"
		"\t2:\tAngle in degrees of the forward cone." },

	{ OP_FACING2, "Facing Waypoint(Boolean training operator)\r\n"
		"\tIs true as long as the specified first waypoint is within the player's specified "
		"forward cone.  A forward cone is defined as any point that the angle between the "
		"vector of the point and the player, and the forward facing vector is within the "
		"given angle.\r\n\r\n"
		"Returns a boolean value; Takes 2 argument:\r\n"
		"\t1:\tName of waypoint path whose first point is withing forward cone.\r\n"
		"\t2:\tAngle in degrees of the forward cone." },

	{ OP_ORDER, "Order (Boolean training operator)\r\n"
		"\tBecomes true when the player had given the specified ship or wing the specified order.\r\n\r\n"
		"Returns a boolean value; Takes 2 arguments:\r\n"
		"\t1:\tName of ship or wing to check if given order to.\r\n"
		"\t2:\tName of order to check if player has given." },

	{ OP_WAYPOINT_MISSED, "Waypoint-missed (Boolean training operator)\r\n"
		"\tBecomes true when a waypoint is flown, but the waypoint is ahead of the one "
		"they are supposed to be flying.  The one they are supposed to be flying is the "
		"next one in sequence in the path after the last one they have hit.\r\n\r\n"
		"Returns a boolean value; Takes no arguments." },

	{ OP_PATH_FLOWN, "Path-flown (Boolean training operator)\r\n"
		"\tBecomes true when all the waypoints in the path have been flown, in sequence.\r\n\r\n"
		"Returns a boolean value; Takes no arguments." },

	{ OP_WAYPOINT_TWICE, "Waypoint-twice (Boolean training operator)\r\n"
		"\tBecomes true when a waypoint is hit that is before the last one hit, which "
		"indicates they have flown a waypoint twice.\r\n\r\n"
		"Returns a boolean value; Takes no arguments." },

	{ OP_TRAINING_MSG, "Training-msg (Action training operator)\r\n"
		"\tSends the player a training message.  Uses the same messages as normal messages, "
		"only they get displayed differently using this operator.  If a secondary message "
		"is specified, it is sent the last time, while the primary message is sent all other "
		"times (event should have a repeat count greater than 1).\r\n\r\n"
		"Takes 1-3 arguments:\r\n"
		"\t1:\tName of primary message to send.\r\n"
		"\t2:\tName of secondary message to send (optional).\r\n"
		"\t3:\tDelay (in seconds) to wait before sending message. (optional)\r\n"
		"\t4:\tAmount of Time (in seconds) to display message (optional)." },

	{ OP_SET_TRAINING_CONTEXT_FLY_PATH, "Set-training-context-fly-path (Training context operator)\r\n"
		"\tTells FreeSpace that the player is expected to fly a waypoint path.  This must be "
		"executed before waypoint-missed, waypoint-twice and path-flown operators become valid.\r\n\r\n"
		"Takes 2 arguments:\r\n"
		"\t1:\tName of waypoint path player should fly.\r\n"
		"\t2:\tDistance away a player needs to be from a waypoint for it to be registered as flown." },

	{ OP_SET_TRAINING_CONTEXT_SPEED, "Set-training-context-speed (Training context operator)\r\n"
		"\tTells FreeSpace that the player is expected to fly within a certain speed range.  Once "
		"this operator has been executed, you can measure how long they have been within this "
		"speed range with the speed operator.\r\n\r\n"
		"Takes 2 arguments:\r\n"
		"\t1:\tMinimum speed of range player is to fly between.\r\n"
		"\t2:\tMaximum speed of range player is to fly between." },

	{ OP_GRANT_PROMOTION, "Grant promotion (Action operator)\r\n"
		"\tIn a single player game, this function grants a player an automatic promotion to the "
		"next rank which the player can obtain.  If he is already at the highest rank, this "
		"operator has no effect.  It takes no arguments." },

	{ OP_GRANT_MEDAL, "Grant medal (Action operator)\r\n"
		"\tIn single player missions, this function grants the given medal to the player.  "
		"Currently, only 1 medal will be allowed to be given per mission.\r\n\r\n"
		"Takes 1 argument:\r\n"
		"\t1:\tName of medal to grant to player." },

	{ OP_GOOD_SECONDARY_TIME, "Set prefered secondary weapons\r\n"
		"\tThis sexpression is used to inform the AI about prefered secondary weapons to "
		"fire during combat.  When this expression is evaulated, any AI ships of the given "
		"team prefer to fire the given weapon at the given ship. (Prefered over other "
		"secondary weapons)\r\n\r\n"
		"Takes 4 argument:\r\n"
		"\t1:\tTeam name which will prefer firing given weapon\r\n"
		"\t2:\tMaximum number of this type of weapon above team can fire.\r\n"
		"\t3:\tWeapon name (list includes only the valid weapons for this expression\r\n"
		"\t4:\tShip name at which the above named team should fire the above named weapon." },

	{ OP_AND_IN_SEQUENCE, "And in sequence (Boolean operator)\r\n"
		"\tReturns true if all of it's arguments have become true in the order they are "
		"listed in.\r\n\r\n"
		"Returns a boolean value; Takes 2 or more boolean arguments." },

	{ OP_SKILL_LEVEL_AT_LEAST, "Skill level at least (Boolean operator)\r\n"
		"\tReturns true if the player has selected the given skill level or higher.\r\n\r\n"
		"Returns a boolean value; Takes 1 arguments:\r\n"
		"\t1:\tName of the skill level to check." },

	{ OP_NUM_PLAYERS, "Num players (Status operator)\r\n"
		"\tReturns the current number of players (multiplayer) playing in the current mission.\r\n\r\n"
		"Returns a numeric value; Takes no arguments." },

	{ OP_IS_CARGO_KNOWN, "Is cargo known (Boolean operator)\r\n"
		"\tReturns true if all of the specified objects' cargo is known by the player (i.e. they "
		"have scanned each one.\r\n\r\n"
		"Returns a boolean value; Takes 1 or more arguments:\r\n"
		"\tAll:\tName of ship to check if it's cargo is known." },

	{ OP_HAS_BEEN_TAGGED_DELAY, "Has ship been tagged (delay) (Boolean operator)\r\n"
		"\tReturns true if all of the specified ships have been tagged.\r\n\r\n"
		"Returns a boolean value after <delay> seconds when all ships have been tagged; Takes 2 or more arguments:\r\n"
		"\t1:\tDelay in seconds after which sexpression will return true when all cargo scanned."
		"\tRest:\tNames of ships to check if tagged.." },

	{ OP_CAP_SUBSYS_CARGO_KNOWN_DELAY, "Is capital ship subsystem cargo known (delay) (Boolean operator)\r\n"
		"\tReturns true if all of the specified subsystem cargo is known by the player.\r\n"
		"\tNote: Cargo must be explicitly named.\r\n\r\n"
		"Returns a boolean value after <delay> seconds when all cargo is known; Takes 3 or more arguments:\r\n"
		"\t1:\tDelay in seconds after which sexpression will return true when all cargo scanned.\r\n"
		"\t2:\tName of Captial ship\r\n"
		"\tRest:\tNames of subsystems to check for cargo known.." },

	{ OP_CARGO_KNOWN_DELAY, "Is cargo known (delay) (Boolean operator)\r\n"
		"\tReturns true if all of the specified objects' cargo is known by the player (i.e. they "
		"have scanned each one.\r\n\r\n"
		"Returns a boolean value after <delay> seconds when all cargo is known; Takes 2 or more arguments:\r\n"
		"\t1:\tDelay in seconds after which sexpression will return true when all cargo scanned."
		"\tRest:\tNames of ships/cargo to check for cargo known.." },

	{ OP_WAS_PROMOTION_GRANTED, "Was promotion granted (Boolean operator)\r\n"
		"\tReturns true if a promotion was granted via the 'Grant promotion' operator in the mission.\r\n\r\n"
		"Returns a boolean value; Takes no arguments." },

	{ OP_WAS_MEDAL_GRANTED, "Was medal granted (Boolean operator)\r\n"
		"\tReturns true if a medal was granted via via the 'Grant medal' operator in the mission.  "
		"If you provide the optional argument to this operator, then true is only returned if the "
		"specified medal was granted.\r\n\r\n"
		"Returns a boolean value; Takes 0 or 1 arguments:\r\n"
		"\t1:\tName of medal to specifically check for (optional)." },

	{ OP_GOOD_REARM_TIME, "Good rearm time (Action operator)\r\n"
		"\tInforms the game logic that right now is a good time for a given team to attempt to "
		"rearm their ships.  The time parameter specified how long the \"good time\" will last.\r\n\r\n"
		"Takes 2 arguments:\r\n"
		"\t1:\tTeam Name\r\n"
		"\t2:\tTime in seconds rearm window should last" },

	{ OP_ALLOW_SHIP, "Allow ship (Action operator)\r\n"
		"\tThis operator makes the given ship type available to the Terran team.  Players will be "
		"able to have ships of this type in their starting wings in all future missions of this "
		"campaign.\r\n\r\n"
		"Takes 1 arguments:\r\n"
		"\t1:\tName of ship type (or ship class) to allow." },

	{ OP_ALLOW_WEAPON, "Allow weapon (Action operator)\r\n"
		"\tThis operator makes the given weapon available to the Terran team.  Players will be "
		"able to equip ships with in all future missions of this campaign.\r\n\r\n"
		"Takes 1 arguments:\r\n"
		"\t1:\tName of weapon (primary or secondary) to allow." },

	{ OP_TECH_ADD_SHIP, "Tech add ship (Action operator)\r\n"
		"\tThis operator makes the given ship type available in the techroom database.  Players will "
		"then be able to view this ship's specs there.\r\n\r\n"
		"Takes 1 or more arguments:\r\n"
		"\tAll:\tName of ship type (or ship class) to add." },

	{ OP_TECH_ADD_WEAPON, "Tech add weapon (Action operator)\r\n"
		"\tThis operator makes the given weapon available in the techroom database.  Players will "
		"then be able to view this weapon's specs there.\r\n\r\n"
		"Takes 1 or more arguments:\r\n"
		"\tAll:\tName of weapon (primary or secondary) to add." },

	{ OP_AI_EVADE_SHIP, "Ai-evade ship (Ship goal)\r\n"
		"\tCauses the specified ship to go into evade mode and run away like the weak "
		"sally-boy it is.\r\n\r\n"
		"Takes 2 arguments:\r\n"
		"\t1:\tName of ship to evade from.\r\n"
		"\t2:\tGoal priority (number between 0 and 89)." },

	{ OP_AI_STAY_NEAR_SHIP, "Ai-stay near ship (Ship goal)\r\n"
		"\tCauses the specified ship to keep itself near the given ship and not stray too far "
		"away from it.\r\n\r\n"
		"Takes 2 arguments:\r\n"
		"\t1:\tName of ship to stay near.\r\n"
		"\t2:\tGoal priority (number between 0 and 89)." },

	{ OP_AI_KEEP_SAFE_DISTANCE, "Ai-keep safe distance (Ship goal)\r\n"
		"\tTells the specified ship to stay a safe distance away from any ship that isn't on the "
		"same team as it.\r\n\r\n"
		"Takes 1 argument:\r\n"
		"\t1:\tGoal priority (number between 0 and 89)." },

	{ OP_AI_IGNORE, "Ai-ignore (Ship goal)\r\n"
		"\tTells the specified ship to ignore the given ship and not consider it as a valid "
		"target to attack.\r\n\r\n"
		"Takes 2 arguments:\r\n"
		"\t1:\tName of ship to ignore.\r\n"
		"\t2:\tGoal priority (number between 0 and 89)." },

	{ OP_AI_STAY_STILL, "Ai-stay still (Ship goal)\r\n"
		"\tCauses the specified ship to stay still.  The ship will do nothing until attacked at "
		"which time the ship will come to life and defend itself.\r\n\r\n"
		"Takes 2 arguments:\r\n"
		"\t1:\tShip or waypoint the ship staying still will directly face (currently not implemented)\r\n"
		"\t2:\tGoal priority (number between 0 and 89)." },

	{ OP_AI_PLAY_DEAD, "Ai-play dead (Ship goal)\r\n"
		"\tCauses the specified ship to pretend that it is dead and not do anything.  This "
		"expression should be used to indicate that a ship has no pilot and cannot respond "
		"to any enemy threats.  A ship playing dead will not respond to any attack.  This "
		"should really be named ai-is-dead\r\n\r\n"
		"Takes 1 argument:\r\n"
		"\t1:\tGoal priority (number between 0 and 89)." },

	{ OP_FLASH_HUD_GAUGE, "Ai-flash hud gauge (Training goal)\r\n"
		"\tCauses the specified hud gauge to flash to draw the player's attention to it.\r\n\r\n"
		"Takes 1 argument:\r\n"
		"\t1:\tName of hud gauge to flash." },

	{ OP_SHIP_VISIBLE, "ship-visible\r\n"
		"\tCauses the ships listed in this sexpression to be visible with player sensors.\r\n\r\n"
		"Takes 1 or more arguments:\r\n"
		"\t1+:\tName of ships to make visible to sensors." },

	{ OP_SHIP_INVISIBLE, "ship-invisible\r\n"
		"\tCauses the ships listed in this sexpression to be invisible to player sensors.\r\n\r\n"
		"Takes 1 or more arguments:\r\n"
		"\t1+:\tName of ships to make invisible to sensors." },

	{ OP_SHIP_VULNERABLE, "ship-vulnerable\r\n"
		"\tCauses the ship listed in this sexpression to be vulnerable to weapons.\r\n\r\n"
		"Takes 1 or more arguments:\r\n"
		"\t1+:\tName of ships to make vulnerable to weapons." },

	{ OP_SHIP_INVULNERABLE, "ship-invulnerable\r\n"
		"\tCauses the ships listed in this sexpression to be invulnerable to weapons.  Use with caution!!!!\r\n\r\n"
		"Takes 1 or more arguments:\r\n"
		"\t1+:\tName of ships to make invulnerable to weapons." },

	{ OP_SHIP_GUARDIAN, "ship-guardian\r\n"
		"\tCauses the ships listed in this sexpression to not be killable by weapons.  Use with caution!!!!\r\n\r\n"
		"Takes 1 or more arguments:\r\n"
		"\t1+:\tName of ships to make invulnerable to weapons." },

	{ OP_SHIP_NO_GUARDIAN, "ship-no-guardian\r\n"
		"\tCauses the ships listed in this sexpression to be killable by weapons, if not invulnerable.\r\n\r\n"
		"Takes 1 or more arguments:\r\n"
		"\t1+:\tName of ships to make vulnerable to weapons." },

	{ OP_PERCENT_SHIPS_DEPARTED, "percent-ships-departed\r\n"
		"\tBoolean function which returns true if the percentage of ships in the listed ships and wings "
		"which have departed is greater or equal to the given percentage.  For wings, all ships of all waves "
		"are used for calculation for the total possible ships to depart.\r\n\r\n"
		"Takes 2 or more arguments:\r\n"
		"\t1:\tPercentge of departed ships at which this function will return true.\r\n"
		"\t2+:\tList of ships/wing whose departure status should be determined." },

	{ OP_PERCENT_SHIPS_DESTROYED, "percent-ships-destroyed\r\n"
		"\tBoolean function which returns true if the percentage of ships in the listed ships and wings "
		"which have been destroyed is greater or equal to the given percentage.  For wings, all ships of all waves "
		"are used for calculation for the total possible ships to be destroyed.\r\n\r\n"
		"Takes 2 or more arguments:\r\n"
		"\t1:\tPercentge of destroyed ships at which this function will return true.\r\n"
		"\t2+:\tList of ships/wing whose destroyed status should be determined." },

	{ OP_RED_ALERT, "red-alert\r\n"
		"\tCauses Red Alert status in a mission.  This function ends the current mission, and moves to "
		"the next mission in the campaign under red alert status.  There should only be one branch from "
		"a mission that uses this expression\r\n\r\n"
		"Takes no arguments."},

	{ OP_DEPART_NODE_DELAY, "depart-node-delay\r\n"
		"\tReturns true N seconds after the listed ships depart, if those ships depart within the "
		"radius of the given jump node.  The delay value is given in seconds.\r\n\r\n"
		"Takes 3 or more arguments:r\n"
		"\t1:\tDelay in seconds after the last ship listed departe before this expression can return true.\r\n"
		"\t2:\tName of a jump node\r\n"
		"\t3+:\tList of ships to check for departure within radius of the jump node." },

	{ OP_DESTROYED_DEPARTED_DELAY, "destroyed-or-departed-delay\r\n"
		"\tReturns true N seconds after all the listed ships or wings have been destroyed or have "
		"departed.\r\n\r\n"
		"Takes 2 or more arguments:\r\n"
		"\t1:\tDelay in seconda after the last ship/wing is destroyed or departerd this expression can return true.\r\n"
		"\t2+:\tName of a ship or wing" },

	{ OP_SPECIAL_CHECK, "Special-check\r\n"
		"\tDo some special check in training.  Ask Mike K. about how it works.\r\n\r\n"
		"Returns a boolean value; Takes 1 argument:\r\n"
		"\t1:\tExtra special number (tm)" },

	{ OP_END_CAMPAIGN, "end-campaign\r\n"
		"\tEnds the builtin campaign.  Should only be used by the main FreeSpace campaign\r\n" },

	{ OP_WARP_BROKEN, "break-warp\r\n"
		"\tBreak the warp drive on the specified ship.  A broken warp drive can be repaired by "
		"a repair ship.  Takes 1 or more arguments:\r\n"
		"\t1:\tList of ships to break the warp drive on" },
	{ OP_WARP_NOT_BROKEN, "fix-warp\r\n"
		"\tFixes a broken warp drive instantaneously.  This option applies to warp drives broken with "
		"the break-warp sepxression.  Takes 1 or more arguments:\r\n"
		"\t1:\tList of ships whose warp drive should be fixed"},
	{ OP_WARP_NEVER, "never-warp\r\n"
		"\tNever allows a ship to warp out.  When this sexpression is used, the given ships will "
		"never be able to warp out.  The warp drive cannot be repaired.  Takes 1 or more arguments:\r\n"
		"\t1:\tList of ships whose are not allowed to warp out under any condition"},
	{ OP_WARP_ALLOWED, "allow-warp\r\n"
		"\tAllows a ship which was previously not allowed to warp out to do so.  When this sexpression is "
		"used, the given ships will be able to warp out again.  Takes 1 or more arguments:\r\n"
		"\t1:\tList of ships whose are allowed to warp out"},
	{ OP_JETTISON_CARGO, "jettison-cargo-delay\r\n"
		"\tCauses a cargo carrying ship to jettison its cargo without the undocking procedure. Takes 2 arguments"},
	{ OP_BEAM_FIRE, "beam-fire\r\n"
		"\tFire a beam weapon from a specified subsystem\r\n"
		"\t1:\tShip which will be firing\r\n"
		"\t2:\tTurret which will fire the beam (note, this turret must have at least 1 beam weapon on it)\r\n"
		"\t3:\tShip which will be targeted\r\n"
		"Use add-data to add a specific subsystem to target on the specified target ship"},
	{ OP_IS_TAGGED, "is-tagged\r\n"
		"\tReturns whether a given ship is tagged or not\r\n"},
	{ OP_NUM_KILLS, "num-kills\r\n"
		"\tReturns the # of kills a player has. The ship specified in the first field should be the ship the player is in.\r\n"
		"\tSo, for single player, this would be alpha 1. For multiplayer, it can be any ship with a player in it. If, at any\r\n"
		"\ttime there is no player in a given ship, this sexpression will return 0"},
	{ OP_NUM_TYPE_KILLS, "num-type-kills\r\n"
		"\tReturns the # of kills a player has on a given ship type (fighter, bomber, cruiser, etc).\r\n"
		"The ship specified in the first field should be the ship the player is in.\r\n"
		"\tSo, for single player, this would be alpha 1. For multiplayer, it can be any ship with a player in it. If, at any\r\n"
		"\ttime there is no player in a given ship, this sexpression will return 0"},
	{ OP_NUM_CLASS_KILLS, "num-class-kills\r\n"
		"\tReturns the # of kills a player has on a specific ship class (Ulysses, Hercules, etc).\r\n"
		"The ship specified in the first field should be the ship the player is in.\r\n"
		"\tSo, for single player, this would be alpha 1. For multiplayer, it can be any ship with a player in it. If, at any\r\n"
		"\ttime there is no player in a given ship, this sexpression will return 0"},	
	{ OP_BEAM_FREE, "beam-free\r\n"
		"\tSets one or more beam weapons to allow firing for a given ship\r\n"
		"\t1: Ship to be operated on\r\n"
		"\t2, 3, etc : List of turrets to activate\r\n"},
	{ OP_BEAM_FREE_ALL, "beam-free-all\r\n"
		"\tSets all beam weapons on the specified ship to be active\r\n"},
	{ OP_BEAM_LOCK, "beam-lock\r\n"
		"\tSets one or more beam weapons to NOT allow firing for a given ship\r\n"
		"\t1: Ship to be operated on\r\n"
		"\t2, 3, etc : List of turrets to deactivate\r\n"},
	{ OP_BEAM_LOCK_ALL, "beam-lock-all\r\n"
		"\tSets all beam weapons on the specified ship to be deactivated\r\n"},
	{ OP_TURRET_FREE, "turret-free\r\n"
		"\tSets one or more turret weapons to allow firing for a given ship\r\n"
		"\t1: Ship to be operated on\r\n"
		"\t2, 3, etc : List of turrets to activate\r\n"},
	{ OP_TURRET_FREE_ALL, "turret-free-all\r\n"
		"\tSets all turret weapons on the specified ship to be active\r\n"},
	{ OP_TURRET_LOCK, "turret-lock\r\n"
		"\tSets one or more turret weapons to NOT allow firing for a given ship\r\n"
		"\t1: Ship to be operated on\r\n"
		"\t2, 3, etc : List of turrets to deactivate\r\n"},
	{ OP_TURRET_LOCK_ALL, "turret-lock-all\r\n"
		"\tSets all turret weapons on the specified ship to be deactivated\r\n"},
	{ OP_ADD_REMOVE_ESCORT, "add-remove-escort\r\n"
		"\tAdds or removes a ship from an escort list.\r\n"
		"\t1: Ship to be added or removed\r\n"
		"\t2: 0 to remove from the list, any positive value to add to the list\r\n"
		"NOTE : it _IS_ safe to add a ship which may already be on the list or remove\r\n"
		"a ship which is not on the list\r\n"},
	{ OP_AWACS_SET_RADIUS, "awacs-set-radius\r\n"
		"\tSets the awacs radius for a given ship subsystem. NOTE : does not work properly in multiplayer\r\n"
		"\t1: Ship which has the awacs subsystem\r\n"
		"\t2: Awacs subsystem\r\n"
		"\t3: New radius\r\n"},
	{ OP_SEND_MESSAGE_LIST, "send-message-list\r\n"
		"\tSends a series of delayed messages. All times are accumulated"
		"\t1:\tName of who the message is from.\r\n"
		"\t2:\tPriority of message (\"Low\", \"Normal\" or \"High\").\r\n"
		"\t3:\tName of message (from message editor).\r\n"
		"\t4:\tDelay in ms\r\n"
		"Use Add-Data for multiple messages"
		"IMPORTANT : each additional message in the list MUST HAVE 4 entries\r\n"
		"any message without the 4 proper fields will be ignore, as will any\r\n"
		"successive messages"},
	{ OP_CAP_WAYPOINT_SPEED, "cap-waypoint-speed\r\n"
		"\tSets the maximum speed of a ship while flying waypoints.\r\n"
		"\t1: Ship name\r\n"
		"\t2: Maximum speed while flying waypoints\r\n"
		"\tNOTE: This will only work if the ship is already in the game\r\n"
		"\tNOTE: Set to -1 to reset\r\n"},
	{ OP_TURRET_TAGGED_ONLY_ALL, "turret-tagged-only\r\n"
		"\tMakes turrets target and hence fire strictly at tagged objects\r\n"
		"\t1: Ship name\r\n"
		"\tNOTE: Will not stop a turret already firing at an untagged ship\r\n"},
	{ OP_TURRET_TAGGED_CLEAR_ALL, "turret-tagged-clear\r\n"
		"\tRelaxes restriction on turrets targeting only tagged ships\r\n"
		"\t1: Ship name\r\n"},
	{ OP_SECONDARIES_DEPLETED, "secondaries-depleted\r\n"
		"\tReturns true if ship is out secondary weapons\r\n"
		"\t1: Ship name\r\n"},
	{ OP_SUBSYS_SET_RANDOM, "subsys-set-random\r\n"
		"\tSets ship subsystem strength in a given range\r\n"
		"\t1: Ship name\r\n"
		"\t2: Low range\r\n"
		"\t3: High range\r\n"
		"\t4: List of subsys names not to be randomized\r\n"},
	{ OP_SUPERNOVA_START, "supernova-start\r\n"
		"\t1: Time in seconds until the supernova shockwave hits the player\r\n"},
	{ OP_SHIELD_RECHARGE_PCT, "shield-recharge-pct\r\n"
		"\tReturns a percentage from 0 to 100\r\n"
		"\t1: Ship name\r\n" },
	{ OP_ENGINE_RECHARGE_PCT, "engine-recharge-pct\r\n"
		"\tReturns a percentage from 0 to 100\r\n"
		"\t1: Ship name\r\n" },
	{ OP_WEAPON_RECHARGE_PCT, "weapon-recharge-pct\r\n"
		"\tReturns a percentage from 0 to 100\r\n"
		"\t1: Ship name\r\n" },
	{ OP_CARGO_NO_DEPLETE, "cargo-no-deplete\r\n"
		"\tCauses the named ship to have unlimited cargo.\r\n"
		"\tNote:  only applies to BIG or HUGE ships\r\n"
		"Takes 1 or more arguments:\r\n"
		"\t1:\tName of one of the ships.\r\n"
		"\t2:\toptional: 1 disallow depletion, 0 allow depletion." },
	{ OP_SHIELD_QUAD_LOW, "shield-quad-low\r\n"
		"\tReturns true if the specified ship has a shield quadrant below\r\n"
		"\tthe specified threshold percentage\r\n"
		"\t1: Ship name\r\n"
		"\t2: Percentage\r\n" },
	{ OP_SECONDARY_AMMO_PCT, "secondary-ammo-pct\r\n"
		"\tReturns the percentage of ammo remaining in the specified bank (0 to 100)\r\n"
		"\t1: Ship name\r\n"
		"\t2: Bank to check (0, 1, 2 are legal banks. 3 will return the cumulative average for all banks" },
	{ OP_IS_SECONDARY_SELECTED, "is-secondary-selected\r\n"
		"\tReturns true if the specified bank is selected (0 .. num_banks - 1)\r\n"
		"\t1: Ship name\r\n"
		"\t2: Bank to check (0 .. num_banks - 1)\r\n"},
	{ OP_IS_PRIMARY_SELECTED, "is-primary-selected\r\n"
		"\tReturns true if the specified bank is selected (0 .. num_banks - 1)\r\n"
		"\t1: Ship name\r\n"
		"\t2: Bank to check (0 .. num_banks - 1)\r\n"},
	{ OP_SPECIAL_WARP_DISTANCE, "special-warp-dist\r\n"
		"\tReturns distance to the plane of the knossos device in percent length of ship\r\n"
		"\t(ie, 100 means front of ship is 1 ship length from plane of knossos device)\r\n"
		"\t1: Ship name\r\n"}, 
	{ OP_SET_SPECIAL_WARPOUT_NAME, "special-warpout-name\r\n"
		"\tSets the name of the knossos device to be used for warpout\r\n"
		"\t1: Ship name to exit\r\n"
		"\t2: Name of knossos device\r\n"},
	{ OP_SHIP_VANISH, "ship-vanish\r\n"
		"\tMakes the named ship vanish (no log and vanish)\r\n"
		"\tSingle Player Only!  Warning: This will cause ship exit not to be logged, so 'has-departed', etc. will not work\r\n"
		"\t1: List of ship names to vanish\r\n"},
	{ OP_IS_SHIP_VISIBLE, "is-ship-visible\r\n"
		"\tCheck whether ship is visible on Player's radar\r\n"
		"\tSingle Player Only!  Returns 0 - not visible, 1 - partially visible, 2 - fully visible.\r\n"
		"\t1: Name of ship to check\r\n"},
	{ OP_TEAM_SCORE, "team-score\r\n"
		"\tGet the score of a multi team vs team game.\r\n"
		"\t1: Team index (1 for team 1 and 2 for team 2)\r\n"},

};

struct op_menu_struct {
	char *name;
	int id;

} op_menu[] = {
	{ "Objectives",	OP_CATAGORY_OBJECTIVE },
	{ "Time",			OP_CATAGORY_TIME },
	{ "Logical",		OP_CATAGORY_LOGICAL },
	{ "Arithmetic",	OP_CATAGORY_ARITHMETIC },
	{ "Status",			OP_CATAGORY_STATUS },
	{ "Change",			OP_CATAGORY_CHANGE },
	{ "Conditionals",	OP_CATAGORY_CONDITIONAL },
	{ "Debugging",		OP_CATAGORY_DEBUG },
	{ "Ai goals",		OP_CATAGORY_AI },
	{ "Event/Goals",	OP_CATAGORY_GOAL_EVENT },
	{ "Training",		OP_CATAGORY_TRAINING },
};

int Num_op_menus = sizeof(op_menu) / sizeof(op_menu_struct);

// constructor
sexp_tree::sexp_tree()
{
	select_sexp_node = -1;
	root_item = -1;
	m_mode = 0;
	m_dragging = FALSE;
	m_p_image_list = NULL;
	help_box = NULL;
	clear_tree();
}

// clears out the tree, so all the nodes are unused.
void sexp_tree::clear_tree(char *op)
{
	int i;

	total = flag = 0;
	for (i=0; i<MAX_SEXP_TREE_SIZE; i++)
		nodes[i].type = SEXPT_UNUSED;

	if (op) {
		DeleteAllItems();
		if (strlen(op)) {
			set_node(allocate_node(-1), (SEXPT_OPERATOR | SEXPT_VALID), op);
			build_tree();
		}
	}
}

void sexp_tree::reset_handles()
{
	int i;

	for (i=0; i<MAX_SEXP_TREE_SIZE; i++)
		nodes[i].handle = NULL;
}

// initializes and creates a tree from a given sexp startpoint.
void sexp_tree::load_tree(int index, char *deflt)
{
	int cur;

	clear_tree();
	root_item = 0;
	if (index < 0) {
		cur = allocate_node(-1);
		set_node(cur, (SEXPT_OPERATOR | SEXPT_VALID), deflt);  // setup a default tree if none
		build_tree();
		return;
	}

	if (Sexp_nodes[index].subtype == SEXP_ATOM_NUMBER) {  // handle numbers allender likes to use so much..
		cur = allocate_node(-1);
		if (atoi(Sexp_nodes[index].text))
			set_node(cur, (SEXPT_OPERATOR | SEXPT_VALID), "true");
		else
			set_node(cur, (SEXPT_OPERATOR | SEXPT_VALID), "false");

		build_tree();
		return;
	}

	// assumption: first token is an operator.  I require this because it would cause problems
	// with child/parent relations otherwise, and it should be this way anyway, since the
	// return type of the whole sexp is boolean, and only operators can satisfy this.
	Assert(Sexp_nodes[index].subtype == SEXP_ATOM_OPERATOR);
	load_branch(index, -1);
	build_tree();
}

void get_combined_variable_name(char *combined_name, const char *sexp_var_name)
{
	int sexp_var_index = get_index_sexp_variable_name(sexp_var_name);
	Assert(sexp_var_index > -1);

	sprintf(combined_name, "%s(%s)", Sexp_variables[sexp_var_index].variable_name, Sexp_variables[sexp_var_index].text);
}



// creates a tree from a given Sexp_nodes[] point under a given parent.  Recursive.
void sexp_tree::load_branch(int index, int parent)
{
	int cur = -1;
	char combined_var_name[2*TOKEN_LENGTH + 2];

	while (index != -1) {
		Assert(Sexp_nodes[index].type != SEXP_NOT_USED);
		if (Sexp_nodes[index].subtype == SEXP_ATOM_LIST) {
			load_branch(Sexp_nodes[index].first, parent);  // do the sublist and continue

		} else if (Sexp_nodes[index].subtype == SEXP_ATOM_OPERATOR) {
			cur = allocate_node(parent);
			if ((index == select_sexp_node) && !flag) {  // translate sexp node to our node
				select_sexp_node = cur;
				flag = 1;
			}

			set_node(cur, (SEXPT_OPERATOR | SEXPT_VALID), Sexp_nodes[index].text);
			load_branch(Sexp_nodes[index].rest, cur);  // operator is new parent now
			return;  // 'rest' was just used, so nothing left to use.

		} else if (Sexp_nodes[index].subtype == SEXP_ATOM_NUMBER) {
			cur = allocate_node(parent);
			if (Sexp_nodes[index].type & SEXP_FLAG_VARIABLE) {
				get_combined_variable_name(combined_var_name, Sexp_nodes[index].text);
				set_node(cur, (SEXPT_VARIABLE | SEXPT_NUMBER | SEXPT_VALID), combined_var_name);
			} else {
				set_node(cur, (SEXPT_NUMBER | SEXPT_VALID), Sexp_nodes[index].text);
			}

		} else if (Sexp_nodes[index].subtype == SEXP_ATOM_STRING) {
			cur = allocate_node(parent);
			if (Sexp_nodes[index].type & SEXP_FLAG_VARIABLE) {
				get_combined_variable_name(combined_var_name, Sexp_nodes[index].text);
				set_node(cur, (SEXPT_VARIABLE | SEXPT_STRING | SEXPT_VALID), combined_var_name);
			} else {
				set_node(cur, (SEXPT_STRING | SEXPT_VALID), Sexp_nodes[index].text);
			}

		} else
			Assert(0);  // unknown and/or invalid sexp type

		if ((index == select_sexp_node) && !flag) {  // translate sexp node to our node
			select_sexp_node = cur;
			flag = 1;
		}

		index = Sexp_nodes[index].rest;
		if (index == -1)
			return;
	}
}

int sexp_tree::query_false(int node)
{
	if (node < 0)
		node = root_item;

	Assert(node >= 0);
	Assert(nodes[node].type == (SEXPT_OPERATOR | SEXPT_VALID));
	Assert(nodes[node].next == -1);  // must make this assumption or else it will confuse code!
	if (find_operator(nodes[node].text) == OP_FALSE){
		return TRUE;
	}

	return FALSE;
}

// builds an sexp of the tree and returns the index of it.  This allocates sexp nodes.
int sexp_tree::save_tree(int node)
{
	if (node < 0)
		node = root_item;

	Assert(node >= 0);
	Assert(nodes[node].type == (SEXPT_OPERATOR | SEXPT_VALID));
	Assert(nodes[node].next == -1);  // must make this assumption or else it will confuse code!
	return save_branch(node);
}

// get variable name from sexp_tree node .text
void var_name_from_sexp_tree_text(char *var_name, const char *text)
{
	int var_name_length = strcspn(text, "(");
	Assert(var_name_length < TOKEN_LENGTH - 1);

	strncpy(var_name, text, var_name_length);
	var_name[var_name_length] = '\0';
}

#define NO_PREVIOUS_NODE -9
// called recursively to save a tree branch and everything under it
int sexp_tree::save_branch(int cur, int at_root)
{
	int start, node = -1, last = NO_PREVIOUS_NODE;
	char var_name_text[TOKEN_LENGTH];

	start = -1;
	while (cur != -1) {
		if (nodes[cur].type & SEXPT_OPERATOR) {
			node = alloc_sexp(nodes[cur].text, SEXP_ATOM, SEXP_ATOM_OPERATOR, -1, save_branch(nodes[cur].child));

			if ((nodes[cur].parent >= 0) && !at_root) {
				node = alloc_sexp("", SEXP_LIST, SEXP_ATOM_LIST, node, -1);
			}
		} else if (nodes[cur].type & SEXPT_NUMBER) {
			// allocate number, maybe variable
			if (nodes[cur].type & SEXPT_VARIABLE) {
				var_name_from_sexp_tree_text(var_name_text, nodes[cur].text);
				node = alloc_sexp(var_name_text, (SEXP_ATOM | SEXP_FLAG_VARIABLE), SEXP_ATOM_NUMBER, -1, -1);
			} else {
				node = alloc_sexp(nodes[cur].text, SEXP_ATOM, SEXP_ATOM_NUMBER, -1, -1);
			}
		} else if (nodes[cur].type & SEXPT_STRING) {
			// allocate string, maybe variable
			if (nodes[cur].type & SEXPT_VARIABLE) {
				var_name_from_sexp_tree_text(var_name_text, nodes[cur].text);
				node = alloc_sexp(var_name_text, (SEXP_ATOM | SEXP_FLAG_VARIABLE), SEXP_ATOM_STRING, -1, -1);
			} else {
				node = alloc_sexp(nodes[cur].text, SEXP_ATOM, SEXP_ATOM_STRING, -1, -1);
			}
		} else if (nodes[cur].type & SEXPT_STRING) {
			Assert( !(nodes[cur].type & SEXPT_VARIABLE) );
			Int3();
		} else {
			Assert(0); // unknown and/or invalid type
		}

		if (last == NO_PREVIOUS_NODE){
			start = node;
		} else if (last >= 0){
			Sexp_nodes[last].rest = node;
		}

		last = node;
		Assert(last != NO_PREVIOUS_NODE);  // should be impossible
		cur = nodes[cur].next;
		if (at_root){
			return start;
		}
	}

	return start;
}

// allocate a node.  Remains used until freed.
int sexp_tree::allocate_node()
{
	int i;

	for (i=0; i<MAX_SEXP_TREE_SIZE; i++)
		if (nodes[i].type == SEXPT_UNUSED) {
			nodes[i].type = SEXPT_UNINIT;
			nodes[i].parent = -1;
			nodes[i].child = -1;
			nodes[i].next = -1;
			total++;
			return i;
		}

	Error(LOCATION, "Out of sexp tree nodes!");
	return -1;
}

// allocate a child node under 'parent'.  Appends to end of list.
int sexp_tree::allocate_node(int parent, int after)
{
	int i, index = allocate_node();

	if (parent != -1) {
		i = nodes[parent].child;
		if (i == -1) {
			nodes[parent].child = index;

		} else {
			while ((i != after) && (nodes[i].next != -1))
				i = nodes[i].next;

			nodes[index].next = nodes[i].next;
			nodes[i].next = index;
		}
	}

	nodes[index].parent = parent;
	return index;
}

// free a node and all it's children.  Also clears pointers to it, if any.
//   node = node chain to free
//   cascade =  0: free just this node and children under it. (default)
//             !0: free this node and all siblings after it.
//
void sexp_tree::free_node(int node, int cascade)
{
	int i;

	// clear the pointer to node
	i = nodes[node].parent;
	Assert(i != -1);
	if (nodes[i].child == node)
		nodes[i].child = nodes[node].next;

	else {
		i = nodes[i].child;
		while (nodes[i].next != -1) {
			if (nodes[i].next == node) {
				nodes[i].next = nodes[node].next;
				break;
			}

			i = nodes[i].next;
		}
	}

	if (!cascade)
		nodes[node].next = -1;

	// now free up the node and it's children
	free_node2(node);
}

// more simple node freer, which works recursively.  It frees the given node and all siblings
// that come after it, as well as all children of these.  Doesn't clear any links to any of
// these freed nodes, so make sure all links are broken first. (i.e. use free_node() if you can)
//
void sexp_tree::free_node2(int node)
{
	Assert(node != -1);
	Assert(nodes[node].type != SEXPT_UNUSED);
	Assert(total > 0);
	*modified = 1;
	nodes[node].type = SEXPT_UNUSED;
	total--;
	if (nodes[node].child != -1)
		free_node2(nodes[node].child);

	if (nodes[node].next != -1)
		free_node2(nodes[node].next);
}

// initialize the data for a node.  Should be called right after a new node is allocated.
void sexp_tree::set_node(int node, int type, char *text)
{
	Assert(type != SEXPT_UNUSED);
	Assert(nodes[node].type != SEXPT_UNUSED);
	nodes[node].type = type;
	size_t max_length;
	if (type & SEXPT_VARIABLE) {
		max_length = 2 * TOKEN_LENGTH + 2;
	} else {
		max_length = TOKEN_LENGTH;
	}
	Assert(strlen(text) < max_length);
	strcpy(nodes[node].text, text);
}

void sexp_tree::post_load()
{
	if (!flag)
		select_sexp_node = -1;
}

// build or rebuild a CTreeCtrl object with the current tree data
void sexp_tree::build_tree()
{
	if (!flag)
		select_sexp_node = -1;

	DeleteAllItems();
	add_sub_tree(0, TVI_ROOT);
}

// Create the CTreeCtrl tree from the tree data.  The tree data should already be setup by
// this point.
void sexp_tree::add_sub_tree(int node, HTREEITEM root)
{
//	char str[80];
	int node2;

	Assert(node >= 0 && node < MAX_SEXP_TREE_SIZE);
	node2 = nodes[node].child;

	// check for single argument operator case (prints as one line)
/*	if (node2 != -1 && nodes[node2].child == -1 && nodes[node2].next == -1) {
		sprintf(str, "%s %s", nodes[node].text, nodes[node2].text);
		nodes[node].handle = insert(str, root);
		nodes[node].flags = OPERAND | EDITABLE;
		nodes[node2].flags = COMBINED;
		return;
	}*/

	// bitmap to draw in tree
	int bitmap;

	if (nodes[node].type & SEXPT_OPERATOR) {
		nodes[node].flags = OPERAND;
		bitmap = BITMAP_OPERATOR;
	} else {
		if (nodes[node].type & SEXPT_VARIABLE) {
			nodes[node].flags = NOT_EDITABLE;
			bitmap = BITMAP_VARIABLE;
		} else {
			nodes[node].flags = EDITABLE;
			bitmap = BITMAP_DATA;
		}
	}

	root = nodes[node].handle = insert(nodes[node].text, bitmap, bitmap, root);

	node = node2;
	while (node != -1) {
		Assert(node >= 0 && node < MAX_SEXP_TREE_SIZE);
		Assert(nodes[node].type & SEXPT_VALID);
		if (nodes[node].type & SEXPT_OPERATOR)	{
			add_sub_tree(node, root);

		} else {
			Assert(nodes[node].child == -1);
			if (nodes[node].type & SEXPT_VARIABLE) {
				nodes[node].handle = insert(nodes[node].text, BITMAP_VARIABLE, BITMAP_VARIABLE, root);
				nodes[node].flags = NOT_EDITABLE;
			} else {
				nodes[node].handle = insert(nodes[node].text, BITMAP_DATA, BITMAP_DATA, root);
				nodes[node].flags = EDITABLE;
			}
		}

		node = nodes[node].next;
	}
}

void sexp_tree::setup_selected(HTREEITEM h)
{
	int i;

	item_index = -1;
	item_handle = h;
	if (!h)
		item_handle = GetSelectedItem();

	for (i=0; i<MAX_SEXP_TREE_SIZE; i++)
		if (nodes[i].handle == item_handle) {
			item_index = i;
			break;
		}
}

int sexp_tree::get_ambiguous_type(int parent)
{

	int first_arg_index = get_modify_variable_first_arg_index();
	int sexp_var_index = get_tree_name_to_sexp_variable_index(nodes[first_arg_index].text);
	Assert(sexp_var_index != -1);

	if (Sexp_variables[sexp_var_index].type & SEXP_VARIABLE_NUMBER) {
		return OPF_NUMBER;
	} else {
		return OPF_AMBIGUOUS;
	}
}


int sexp_tree::get_modify_variable_first_arg_index()
{
	int index;

	Assert( item_index >= 0);

	// get parent and check "modify-variable"
	index = nodes[item_index].parent;
	Assert( index != -1 );
	Assert( !(stricmp(nodes[index].text, "modify-variable")) );

	// get first child and verify type variable
	index = nodes[index].child;
	Assert( index != -1 );
	Assert( nodes[index].type & SEXPT_VARIABLE);

	return index;
}

// handler for right mouse button clicks.
void sexp_tree::right_clicked(int mode)
{
	char buf[256];
	int i, j, z, count, op, add_type, replace_type, type;
	sexp_list_item *list;
	UINT _flags;
	HTREEITEM h;
	POINT click_point, mouse;
	CMenu menu, *mptr, *popup_menu, *add_data_menu = NULL, *replace_data_menu = NULL;
	CMenu *add_op_menu, add_op_submenu[MAX_OP_MENUS];
	CMenu *replace_op_menu, replace_op_submenu[MAX_OP_MENUS];
	CMenu *insert_op_menu, insert_op_submenu[MAX_OP_MENUS];
	CMenu *replace_variable_menu = NULL;

	m_mode = mode;
	add_instance = replace_instance = -1;
	Assert(Num_operators <= MAX_OPERATORS);
	Assert(Num_op_menus < MAX_OP_MENUS);
	GetCursorPos(&mouse);
	click_point = mouse;
	ScreenToClient(&click_point);
	h = HitTest(CPoint(click_point), &_flags);  // find out what they clicked on
	if (h && menu.LoadMenu(IDR_MENU_EDIT_SEXP_TREE)) {
		update_help(h);
		popup_menu = menu.GetSubMenu(0);
		ASSERT(popup_menu != NULL);
		SelectDropTarget(h);

		add_op_menu = replace_op_menu = insert_op_menu = NULL;

		// get pointers to several key popup menus we'll need to modify
		i = popup_menu->GetMenuItemCount();
		while (i--) {
			if ( (mptr = popup_menu->GetSubMenu(i)) > 0 ) {
				popup_menu->GetMenuString(i, buf, sizeof(buf), MF_BYPOSITION);

				if (!stricmp(buf, "add operator")) {
					add_op_menu = mptr;

				} else if (!stricmp(buf, "replace operator")) {
					replace_op_menu = mptr;

				} else if (!stricmp(buf, "add data")) {
					add_data_menu = mptr;

				} else if (!stricmp(buf, "replace data")) {
					replace_data_menu = mptr;

				} else if (!stricmp(buf, "insert operator")) {
					insert_op_menu = mptr;

				} else if (!stricmp(buf, "replace variable")) {
					replace_variable_menu = mptr;
				}
			}
		}

		// add popup menus for all the operator catagories
		for (i=0; i<Num_op_menus; i++) {
			add_op_submenu[i].CreatePopupMenu();
			replace_op_submenu[i].CreatePopupMenu();
			insert_op_submenu[i].CreatePopupMenu();
			add_op_menu->AppendMenu(MF_POPUP, (UINT) add_op_submenu[i].m_hMenu, op_menu[i].name);
			replace_op_menu->AppendMenu(MF_POPUP, (UINT) replace_op_submenu[i].m_hMenu, op_menu[i].name);
			insert_op_menu->AppendMenu(MF_POPUP, (UINT) insert_op_submenu[i].m_hMenu, op_menu[i].name);
		}

		// get rid of the placeholders we needed to ensure popup menus stayed popup menus,
		// i.e. MSDEV will convert empty popup menus into normal menu items.
		add_op_menu->DeleteMenu(ID_PLACEHOLDER, MF_BYCOMMAND);
		replace_op_menu->DeleteMenu(ID_PLACEHOLDER, MF_BYCOMMAND);
		insert_op_menu->DeleteMenu(ID_PLACEHOLDER, MF_BYCOMMAND);
		replace_variable_menu->DeleteMenu(ID_PLACEHOLDER, MF_BYCOMMAND);


		// get item_index
		item_index = -1;
		for (i=0; i<MAX_SEXP_TREE_SIZE; i++) {
			if (nodes[i].handle == h) {
				item_index = i;
				break;
			}
		}

		// Do SEXP_VARIABLE stuff here.
		if (m_mode != MODE_EVENTS) {
			// only allow variables in event mode
			menu.EnableMenuItem(ID_SEXP_TREE_ADD_VARIABLE, MF_GRAYED);
			menu.EnableMenuItem(ID_SEXP_TREE_MODIFY_VARIABLE, MF_GRAYED);
		} else {
			menu.EnableMenuItem(ID_SEXP_TREE_ADD_VARIABLE, MF_ENABLED);
			menu.EnableMenuItem(ID_SEXP_TREE_MODIFY_VARIABLE, MF_ENABLED);
			
			// check not root (-1)
			if (item_index >= 0) {
				// get type of sexp_tree item clicked on
				int type = get_type(h);

				int parent = nodes[item_index].parent;
				if (parent >= 0) {
					op = identify_operator(nodes[parent].text);
					Assert(op >= 0);
					int first_arg = nodes[parent].child;

					// get arg count of item to replace
					Replace_count = 0;
					int temp = first_arg;
					while (temp != item_index) {
						Replace_count++;
						temp = nodes[temp].next;

						// DB - added 3/4/99
						if(temp == -1){
							break;
						}
					}

					int op_type = query_operator_argument_type(op, Replace_count); // check argument type at this position

					// special case dont allow replace data for variable names
					if (op_type != OPF_AMBIGUOUS) {

						if ( (type & SEXPT_STRING) || (type & SEXPT_NUMBER) ) {

							int max_sexp_vars = MAX_SEXP_VARIABLES;
							// prevent collisions in id numbers: ID_VARIABLE_MENU + 512 = ID_ADD_MENU
							Assert(max_sexp_vars < 512);

							for (int idx=0; idx<max_sexp_vars; idx++) {
								if (Sexp_variables[idx].type & SEXP_VARIABLE_SET) {
									UINT flag = MF_STRING | MF_GRAYED;
									// maybe gray flag MF_GRAYED

									// get type -- gray "string" or number accordingly
									if ( type & SEXPT_STRING ) {
										if ( Sexp_variables[idx].type & SEXP_VARIABLE_STRING ) {
											flag &= ~MF_GRAYED;
										}
									} else if ( type & SEXPT_NUMBER ) {
										if ( Sexp_variables[idx].type & SEXP_VARIABLE_NUMBER ) {
											flag &= ~MF_GRAYED;
										}
									}

									// if modify-variable and changing variable, enable all variables
									if (op_type == OPF_VARIABLE_NAME) {
										Modify_variable = 1;
										flag &= ~MF_GRAYED;
									} else {
										Modify_variable = 0;
									}

									char buf[128];
									// append list of variable names and values
									// set id as ID_VARIABLE_MENU + idx
									sprintf(buf, "%s(%s)", Sexp_variables[idx].variable_name, Sexp_variables[idx].text);

									replace_variable_menu->AppendMenu(flag, (ID_VARIABLE_MENU + idx), buf);
								}
							}
						}
					}
				}
			}

			// cant modify if no variables
			if (sexp_variable_count() == 0) {
				menu.EnableMenuItem(ID_SEXP_TREE_MODIFY_VARIABLE, MF_GRAYED);
			}
		}

		// add operator menu items to the various catagory submenus they belong in
		for (i=0; i<Num_operators; i++) {
			for (j=0; j<Num_op_menus; j++) {
				if (op_menu[j].id == (Operators[i].value & OP_CATAGORY_MASK)) {

#ifdef NDEBUG
					switch (Operators[i].value) {
						case OP_WAS_PROMOTION_GRANTED:
						case OP_WAS_MEDAL_GRANTED:
						case OP_GRANT_PROMOTION:
						case OP_GRANT_MEDAL:
						case OP_TECH_ADD_SHIP:
						case OP_TECH_ADD_WEAPON:
							j = Num_op_menus;  // don't allow these operators in final release
					}
#endif
					if (j < Num_op_menus) {
						add_op_submenu[j].AppendMenu(MF_STRING | MF_GRAYED, Operators[i].value, Operators[i].text);
						replace_op_submenu[j].AppendMenu(MF_STRING | MF_GRAYED, Operators[i].value | OP_REPLACE_FLAG, Operators[i].text);
						insert_op_submenu[j].AppendMenu(MF_STRING, Operators[i].value | OP_INSERT_FLAG, Operators[i].text);
					}

					break;	// only 1 category valid
				}
			}
		}

		// find local index (i) of current item (from it's handle)
		SelectItem(item_handle = h);
		for (i=0; i<MAX_SEXP_TREE_SIZE; i++) {
			if (nodes[i].handle == h) {
				break;
			}
		}

		// special case: item is a ROOT node, and a label that can be edited (not an item in the sexp tree)
		if ((item_index == -1) && (m_mode & ST_LABELED_ROOT)) {
			if (m_mode & ST_ROOT_EDITABLE) {
				menu.EnableMenuItem(ID_EDIT_TEXT, MF_ENABLED);
			} else {
				menu.EnableMenuItem(ID_EDIT_TEXT, MF_GRAYED);
			}

			// disable copy, insert op
			menu.EnableMenuItem(ID_EDIT_COPY, MF_GRAYED);
			for (j=0; j<Num_operators; j++) {
				menu.EnableMenuItem(Operators[j].value | OP_INSERT_FLAG, MF_GRAYED);
			}

			gray_menu_tree(popup_menu);
			popup_menu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, mouse.x, mouse.y, this);
			return;
		}

		Assert(item_index != -1);  // handle not found, which should be impossible.
		if (!(nodes[item_index].flags & EDITABLE)) {
			menu.EnableMenuItem(ID_EDIT_TEXT, MF_GRAYED);
		}

		if (nodes[item_index].parent == -1) {  // root node
			menu.EnableMenuItem(ID_DELETE, MF_GRAYED);  // can't delete the root item.
		}

/*		if ((nodes[item_index].flags & OPERAND) && (nodes[item_index].flags & EDITABLE))  // expandable?
			menu.EnableMenuItem(ID_SPLIT_LINE, MF_ENABLED);

		z = nodes[item_index].child;
		if (z != -1 && nodes[z].next == -1 && nodes[z].child == -1)
			menu.EnableMenuItem(ID_SPLIT_LINE, MF_ENABLED);

		z = nodes[nodes[item_index].parent].child;
		if (z != -1 && nodes[z].next == -1 && nodes[z].child == -1)
			menu.EnableMenuItem(ID_SPLIT_LINE, MF_ENABLED);*/

		// change enabled status of 'add' type menu options.
		add_type = 0;
		if (nodes[item_index].flags & OPERAND)	{
			add_type = OPR_STRING;
			int child = nodes[item_index].child;
			Add_count = count_args(child);
			op = identify_operator(nodes[item_index].text);
			Assert(op >= 0);

			// get listing of valid argument values and add to menus
			type = query_operator_argument_type(op, Add_count);
			list = get_listing_opf(type, item_index, Add_count);
			if (list) {
				sexp_list_item *ptr;

				int data_idx = 0;
				ptr = list;
				while (ptr) {
					if (ptr->op >= 0) {
						// enable operators with correct return type
						menu.EnableMenuItem(Operators[ptr->op].value, MF_ENABLED);

					} else {
						// add data
						if ( (data_idx + 3) % 30) {
							add_data_menu->AppendMenu(MF_STRING | MF_ENABLED, ID_ADD_MENU + data_idx, ptr->text);
						} else {
							add_data_menu->AppendMenu(MF_MENUBARBREAK | MF_STRING | MF_ENABLED, ID_ADD_MENU + data_idx, ptr->text);
						}
					}

					data_idx++;
					ptr = ptr->next;
				}
			}

			// special handling for the non-string formats
			if (type == OPF_NONE) {  // an argument can't be added
				add_type = 0;

			} else if (type == OPF_NULL) {  // arguments with no return values
				add_type = OPR_NULL;
			
			} else if (type == OPF_NUMBER) {  // takes numbers
				add_type = OPR_NUMBER;
				menu.EnableMenuItem(ID_ADD_NUMBER, MF_ENABLED);

			} else if (type == OPF_POSITIVE) {  // takes non-negative numbers
				add_type = OPR_POSITIVE;
				menu.EnableMenuItem(ID_ADD_NUMBER, MF_ENABLED);

			} else if (type == OPF_BOOL) {  // takes true/false bool values
				add_type = OPR_BOOL;

			} else if (type == OPF_AI_GOAL) {
				add_type = OPR_AI_GOAL;
			}

			// add_type unchanged from above
			if (add_type == OPR_STRING) {
				menu.EnableMenuItem(ID_ADD_STRING, MF_ENABLED);
			}

			list->destroy();
		}

		// disable operators that do not have arguments available
		for (j=0; j<Num_operators; j++) {
			if (!query_default_argument_available(j)) {
				menu.EnableMenuItem(Operators[j].value, MF_GRAYED);
			}
		}


		// change enabled status of 'replace' type menu options.
		replace_type = 0;
		int parent = nodes[item_index].parent;
		if (parent >= 0) {
			replace_type = OPR_STRING;
			op = identify_operator(nodes[parent].text);
			Assert(op >= 0);
			int first_arg = nodes[parent].child;
			count = count_args(nodes[parent].child);

			// already at minimum number of arguments?
			if (count <= Operators[op].min) {
				menu.EnableMenuItem(ID_DELETE, MF_GRAYED);
			}

			// get arg count of item to replace
			Replace_count = 0;
			int temp = first_arg;
			while (temp != item_index) {
				Replace_count++;
				temp = nodes[temp].next;

				// DB - added 3/4/99
				if(temp == -1){
					break;
				}
			}

			// maybe gray delete
			for (i=Replace_count+1; i<count; i++) {
				if (query_operator_argument_type(op, i-1) != query_operator_argument_type(op, i)) {
					menu.EnableMenuItem(ID_DELETE, MF_GRAYED);
					break;
				}
			}

			type = query_operator_argument_type(op, Replace_count); // check argument type at this position

			// special case reset type for ambiguous
			if (type == OPF_AMBIGUOUS) {
				type = get_ambiguous_type(parent);
			}

			list = get_listing_opf(type, parent, Replace_count);

			// special case dont allow replace data for variable names
			if ( (type != OPF_VARIABLE_NAME) && list) {
				sexp_list_item *ptr;

				int data_idx = 0;
				ptr = list;
				while (ptr) {
					if (ptr->op >= 0) {
						menu.EnableMenuItem(Operators[ptr->op].value | OP_REPLACE_FLAG, MF_ENABLED);

					} else {
						if ( (data_idx + 3) % 30)
							replace_data_menu->AppendMenu(MF_STRING | MF_ENABLED, ID_REPLACE_MENU + data_idx, ptr->text);
						else
							replace_data_menu->AppendMenu(MF_MENUBARBREAK | MF_STRING | MF_ENABLED, ID_REPLACE_MENU + data_idx, ptr->text);
					}

					data_idx++;
					ptr = ptr->next;
				}
			}

			if (type == OPF_NONE) {  // takes no arguments
				replace_type = 0;

			} else if (type == OPF_NUMBER) {  // takes numbers
				replace_type = OPR_NUMBER;
				menu.EnableMenuItem(ID_REPLACE_NUMBER, MF_ENABLED);

			} else if (type == OPF_POSITIVE) {  // takes non-negative numbers
				replace_type = OPR_POSITIVE;
				menu.EnableMenuItem(ID_REPLACE_NUMBER, MF_ENABLED);

			} else if (type == OPF_BOOL) {  // takes true/false bool values
				replace_type = OPR_BOOL;

			} else if (type == OPF_NULL) {  // takes operator that doesn't return a value
				replace_type = OPR_NULL;

			} else if (type == OPF_AI_GOAL) {
				replace_type = OPR_AI_GOAL;
			}

			// default to string
			if (replace_type == OPR_STRING) {
				menu.EnableMenuItem(ID_REPLACE_STRING, MF_ENABLED);
			}

			// modify string or number if (modify_variable)
			if ( !stricmp(Operators[op].text, "modify-variable") ) {
				int modify_type = get_modify_variable_type();

				if (modify_type == OPF_NUMBER) {
					menu.EnableMenuItem(ID_REPLACE_NUMBER, MF_ENABLED);
					menu.EnableMenuItem(ID_REPLACE_STRING, MF_GRAYED);
				}
				// no change for string type
			}

			list->destroy();

		} else {  // top node, so should be a Boolean type.
			if (m_mode == MODE_EVENTS) {  // return type should be null
				replace_type = OPR_NULL;
				for (j=0; j<Num_operators; j++)
					if (query_operator_return_type(j) == OPR_NULL)
						menu.EnableMenuItem(Operators[j].value | OP_REPLACE_FLAG, MF_ENABLED);

			} else {
				replace_type = OPR_BOOL;
				for (j=0; j<Num_operators; j++)
					if (query_operator_return_type(j) == OPR_BOOL)
						menu.EnableMenuItem(Operators[j].value | OP_REPLACE_FLAG, MF_ENABLED);
			}
		}

		for (j=0; j<Num_operators; j++)
			if (!query_default_argument_available(j))
				menu.EnableMenuItem(Operators[j].value | OP_REPLACE_FLAG, MF_GRAYED);

		// change enabled status of 'insert' type menu options.
		z = nodes[item_index].parent;
		Assert(z >= -1);
		if (z != -1) {
			op = identify_operator(nodes[z].text);
			Assert(op != -1);
			j = nodes[z].child;
			count = 0;
			while (j != item_index) {
				count++;
				j = nodes[j].next;
			}

			type = query_operator_argument_type(op, count); // check argument type at this position

		} else {
			if (m_mode == MODE_EVENTS)
				type = OPF_NULL;
			else
				type = OPF_BOOL;
		}

		for (j=0; j<Num_operators; j++) {
			z = query_operator_return_type(j);
			if (!sexp_query_type_match(type, z) || (Operators[j].min < 1))
				menu.EnableMenuItem(Operators[j].value | OP_INSERT_FLAG, MF_GRAYED);

			z = query_operator_argument_type(j, 0);
			if ((type == OPF_NUMBER) && (z == OPF_POSITIVE))
				z = OPF_NUMBER;

			if (z != type)
				menu.EnableMenuItem(Operators[j].value | OP_INSERT_FLAG, MF_GRAYED);
		}

		for (j=0; j<Num_operators; j++)
			if (!query_default_argument_available(j))
				menu.EnableMenuItem(Operators[j].value | OP_INSERT_FLAG, MF_GRAYED);

		// disable non campaign operators if in campaign mode
		for (j=0; j<Num_operators; j++) {
			z = 0;
			if (m_mode == MODE_CAMPAIGN) {
				if (Operators[j].value & OP_NONCAMPAIGN_FLAG)
					z = 1;

			} else {
				if (Operators[j].value & OP_CAMPAIGN_ONLY_FLAG)
					z = 1;
			}

			if (z) {
				menu.EnableMenuItem(Operators[j].value, MF_GRAYED);
				menu.EnableMenuItem(Operators[j].value | OP_REPLACE_FLAG, MF_GRAYED);
				menu.EnableMenuItem(Operators[j].value | OP_INSERT_FLAG, MF_GRAYED);
			}
		}

		if ((Sexp_clipboard > -1) && (Sexp_nodes[Sexp_clipboard].type != SEXP_NOT_USED)) {
			Assert(Sexp_nodes[Sexp_clipboard].subtype != SEXP_ATOM_LIST);

			if (Sexp_nodes[Sexp_clipboard].subtype == SEXP_ATOM_OPERATOR) {
				j = find_operator(CTEXT(Sexp_clipboard));
				Assert(j);
				z = query_operator_return_type(j);

				if ((z == OPR_POSITIVE) && (replace_type == OPR_NUMBER))
					z = OPR_NUMBER;

				if (replace_type == z)
					menu.EnableMenuItem(ID_EDIT_PASTE, MF_ENABLED);

				z = query_operator_return_type(j);
				if ((z == OPR_POSITIVE) && (add_type == OPR_NUMBER))
					z = OPR_NUMBER;

				if (add_type == z)
					menu.EnableMenuItem(ID_EDIT_PASTE_SPECIAL, MF_ENABLED);

			} else if (Sexp_nodes[Sexp_clipboard].subtype == SEXP_ATOM_NUMBER) {
				if ((replace_type == OPR_POSITIVE) && (atoi(CTEXT(Sexp_clipboard)) > -1))
					menu.EnableMenuItem(ID_EDIT_PASTE, MF_ENABLED);

				else if (replace_type == OPR_NUMBER)
					menu.EnableMenuItem(ID_EDIT_PASTE, MF_ENABLED);

				if ((add_type == OPR_POSITIVE) && (atoi(CTEXT(Sexp_clipboard)) > -1))
					menu.EnableMenuItem(ID_EDIT_PASTE_SPECIAL, MF_ENABLED);

				else if (add_type == OPR_NUMBER)
					menu.EnableMenuItem(ID_EDIT_PASTE_SPECIAL, MF_ENABLED);

			} else if (Sexp_nodes[Sexp_clipboard].subtype == SEXP_ATOM_STRING) {
				if (replace_type == OPR_STRING)
					menu.EnableMenuItem(ID_EDIT_PASTE, MF_ENABLED);

				if (add_type == OPR_STRING)
					menu.EnableMenuItem(ID_EDIT_PASTE_SPECIAL, MF_ENABLED);

			} else
				Int3();  // unknown and/or invalid sexp type
		}

		if (!(menu.GetMenuState(ID_DELETE, MF_BYCOMMAND) & MF_GRAYED))
			menu.EnableMenuItem(ID_EDIT_CUT, MF_ENABLED);

		gray_menu_tree(popup_menu);
		popup_menu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, mouse.x, mouse.y, this);
	}
}

// counts the number of arguments an operator has.  Call this with the node of the first
// argument of the operator
int sexp_tree::count_args(int node)
{
	int count = 0;

	while (node != -1) {
		count++;
		node = nodes[node].next;
	}

	return count;
}

// identify what type of argument this is.  You call it with the node of the first argument
// of an operator.  It will search through enough of the arguments to determine what type of
// data they are.
int sexp_tree::identify_arg_type(int node)
{
	int type = -1;

	while (node != -1) {
		Assert(nodes[node].type & SEXPT_VALID);
		switch (SEXPT_TYPE(nodes[node].type)) {
			case SEXPT_OPERATOR:
				type = find_operator(nodes[node].text);
				Assert(type);
				return query_operator_return_type(type);

			case SEXPT_NUMBER:
				return OPR_NUMBER;

			case SEXPT_STRING:  // either a ship or a wing
				type = SEXP_ATOM_STRING;
				break;  // don't return, because maybe we can narrow selection down more.
		}

		node = nodes[node].next;
	}

	return type;
}

// determine if an item should be editable.  This doesn't actually edit the label.
int sexp_tree::edit_label(HTREEITEM h)
{
	int i;

	for (i=0; i<MAX_SEXP_TREE_SIZE; i++) {
		if (nodes[i].handle == h) {
			break;
		}
	}

	// Check if tree root
	if (i == MAX_SEXP_TREE_SIZE) {
		if (m_mode & ST_ROOT_EDITABLE) {
			return 1;
		}

		return 0;
	}

	// Operators are editable
	if (nodes[i].type & SEXPT_OPERATOR) {
		return 1;
	}

	// Variables must be edited through dialog box
	if (nodes[i].type & SEXPT_VARIABLE) {
		return 0;
	}

	// Don't edit if not flaged as editable
	if (!(nodes[i].flags & EDITABLE)) {
		return 0;
	}

	// Otherwise, allow editing
	return 1;

/*
	if (nodes[i].flags & OPERAND) {
		data = nodes[i].child;

		SetItemText(h, nodes[i].text);
		nodes[i].flags = OPERAND;
		item_handle = nodes[data].handle = insert(nodes[data].text, nodes[data].type, nodes[data].flags, h);
		nodes[data].flags = EDITABLE;
		Expand(h, TVE_EXPAND);
		SelectItem(item_handle);
		return 2;
	}
*/
}

int sexp_tree::end_label_edit(HTREEITEM h, char *str)
{
	int len, node, r = 1;

	*modified = 1;
	if (!str)
		return 0;

	for (node=0; node<MAX_SEXP_TREE_SIZE; node++)
		if (nodes[node].handle == h)
			break;

	if (node == MAX_SEXP_TREE_SIZE) {
		if (m_mode == MODE_EVENTS) {
			item_index = GetItemData(h);
			Assert(Event_editor_dlg);
			node = Event_editor_dlg->handler(ROOT_RENAMED, item_index, str);
			return 1;

		} else
			Int3();  // root labels shouldn't have been editable!
	}

	Assert(node < MAX_SEXP_TREE_SIZE);
	if (nodes[node].type & SEXPT_OPERATOR) {
		str = match_closest_operator(str, node);
		SetItemText(h, str);
		item_index = node;
		add_or_replace_operator(identify_operator(str), 1);
		r = 0;
	}

	// Error checking would not hurt here
	len = strlen(str);
	if (len >= TOKEN_LENGTH)
		len = TOKEN_LENGTH - 1;

	strncpy(nodes[node].text, str, len);
	nodes[node].text[len] = 0;

/*	node = nodes[node].parent;
	if (node != -1) {
		child = nodes[node].child;
		if (child != -1 && nodes[child].next == -1 && nodes[child].child == -1) {
			merge_operator(child);
			return 0;
		}
	}*/

	return r;
}

// Check if 'op' is a valid operator match for operator format (OPF) 'type'.  Returns true if it
// is, false if not.
//
int sexp_tree::check_operator_validity(int op, int type)
{
	int rtype;

	rtype = query_operator_return_type(op);
	switch (type) {
		case OPF_NUMBER:
			return ( (rtype == OPR_NUMBER) || (rtype == OPR_POSITIVE) );

		case OPF_POSITIVE:
			return (rtype == OPR_POSITIVE);

		case OPF_BOOL:
			return (rtype == OPR_BOOL);

		case OPF_NULL:
			return (rtype == OPR_NULL);

		case OPF_AI_GOAL:
			return (rtype == OPR_AI_GOAL);
	}

	return 0;
}

// Look for the valid operator that is the closest match for 'str' and return the operator
// number of it.  What operators are valid is determined by 'node', and an operator is valid
// if it is allowed to fit at position 'node'
//
char *sexp_tree::match_closest_operator(char *str, int node)
{
	int z, n, i, op, arg_num, type;
	char *sub_best = NULL, *best = NULL;

	z = nodes[node].parent;
	if (z < 0) {
		return str;
	}

	op = identify_operator(nodes[z].text);
	if (op < 0)
		return str;

	// determine which argument we are of the parent
	arg_num = 0;
	n = nodes[z].child;
	while (n != node) {
		Assert(n >= 0);
		arg_num++;
		n = nodes[n].next;
	}

	type = query_operator_argument_type(op, arg_num); // check argument type at this position
	for (i=0; i<Num_operators; i++) {
		if (check_operator_validity(i, type)) {
			if ( (stricmp(str, Operators[i].text) <= 0) && (!best || (stricmp(str, best) < 0)) )
				best = Operators[i].text;
			
			if ( !sub_best || (stricmp(Operators[i].text, sub_best) > 0) )
				sub_best = Operators[i].text;
		}
	}

	if (!best)
		best = sub_best;  // no best found, use our plan #2 best found.

	Assert(best);  // we better have some valid operator at this point.
	return best;

/*	char buf[256];
	int child;

	if (nodes[node].flags == EDITABLE)  // data
		node = nodes[node].parent;

	if (node != -1) {
		child = nodes[node].child;
		if (child != -1 && nodes[child].next == -1 && nodes[child].child == -1) {
			sprintf(buf, "%s %s", nodes[node].text, nodes[child].text);
			SetItemText(nodes[node].handle, buf);
			nodes[node].flags = OPERAND | EDITABLE;
			nodes[child].flags = COMBINED;
			DeleteItem(nodes[child].handle);
			nodes[child].handle = NULL;
			return;
		}
	}*/
}

// this really only handles messages generated by the right click popup menu
BOOL sexp_tree::OnCommand(WPARAM wParam, LPARAM lParam)
{
	int i, z, id, node, op, type;
	sexp_list_item *list, *ptr;
	HTREEITEM h;

	if ((item_index >= 0) && (item_index < total))
		item_handle = nodes[item_index].handle;

	id = LOWORD(wParam);


	// Add variable
	if (id == ID_SEXP_TREE_ADD_VARIABLE) {
		CAddVariableDlg dlg;
		dlg.DoModal();

		if ( dlg.m_create ) {

			// set type
			int type;
			if ( dlg.m_type_number ) {
				type = SEXP_VARIABLE_NUMBER;
			} else {
				type = SEXP_VARIABLE_STRING;
			}

			// add variable
			sexp_add_variable(dlg.m_default_value, dlg.m_variable_name, type);

			// sort variable
			sexp_variable_sort();
		}
		return 1;
	}

	// Modify variable
	if (id == ID_SEXP_TREE_MODIFY_VARIABLE) {
		CModifyVariableDlg dlg;

		// get sexp_variable index for item index
		dlg.m_start_index = get_item_index_to_var_index();

		// get pointer to tree
		dlg.m_p_sexp_tree = this;

		dlg.DoModal();

		Assert( !(dlg.m_deleted && dlg.m_do_modify) );

		if (dlg.m_deleted) {
			// find index in sexp_variable list
			int sexp_var_index = get_index_sexp_variable_name(dlg.m_cur_variable_name);
			Assert(sexp_var_index != -1);

			// delete from list
			sexp_variable_delete(sexp_var_index);

			// sort list
			sexp_variable_sort();

			// delete from sexp_tree, replacing with "number" or "string" as needed
			// further error checking from add_data()
			delete_sexp_tree_variable(dlg.m_cur_variable_name);

			return 1;
		}

		if (dlg.m_do_modify) {
			// check sexp_tree -- warn on type
			// find index and change either (1) name, (2) type, (3) value
			int sexp_var_index = get_index_sexp_variable_name(dlg.m_old_var_name);
			Assert(sexp_var_index != -1);

			// save old name, since name may be modified
			char old_name[TOKEN_LENGTH];
			strcpy(old_name, Sexp_variables[sexp_var_index].variable_name);

			// set type
			int type;
			if (dlg.m_type_number) {
				type = SEXP_VARIABLE_NUMBER;
			} else {
				type = SEXP_VARIABLE_STRING;
			}

			// update sexp_variable
			sexp_fred_modify_variable(dlg.m_default_value, dlg.m_cur_variable_name, sexp_var_index, type);

			// modify sexp_tree
			modify_sexp_tree_variable(old_name, sexp_var_index);

			// Don't sort until after modify, since modify uses index
			if (dlg.m_modified_name) {
				sexp_variable_sort();
			}

			return 1;
		}

		// no change
		return 1;
	}


	// check if REPLACE_VARIABLE_MENU
	if ( (id >= ID_VARIABLE_MENU) && (id < ID_VARIABLE_MENU + 511)) {

		Assert(item_index >= 0);

		// get index into list of type valid variables
		int var_idx = id - ID_VARIABLE_MENU;
		Assert( (var_idx >= 0) && (var_idx < MAX_SEXP_VARIABLES) );

		int type = get_type(item_handle);
		Assert( (type & SEXPT_NUMBER) || (type & SEXPT_STRING) );

		// dont do type check for modify-variable
		if (Modify_variable) {
			if (Sexp_variables[var_idx].type & SEXP_VARIABLE_NUMBER) {
				type = SEXPT_NUMBER;
			} else if (Sexp_variables[var_idx].type & SEXP_VARIABLE_STRING) {
				type = SEXPT_STRING;
			} else {
				Int3();	// unknown type
			}

		} else {
	
			// verify type in tree is same as type in Sexp_variables array
			if (type & SEXPT_NUMBER) {
				Assert(Sexp_variables[var_idx].type & SEXP_VARIABLE_NUMBER);
			}

			if (type & SEXPT_STRING) {
				Assert( (Sexp_variables[var_idx].type & SEXP_VARIABLE_STRING) );
			}
		}

		// Replace data
		replace_variable_data(var_idx, (type | SEXPT_VARIABLE));

		return 1;
	}


	if ((id >= ID_ADD_MENU) && (id < ID_ADD_MENU + 511)) {
		Assert(item_index >= 0);
		op = identify_operator(nodes[item_index].text);
		Assert(op >= 0);

		type = query_operator_argument_type(op, Add_count);
		list = get_listing_opf(type, item_index, Add_count);
		Assert(list);

		id -= ID_ADD_MENU;
		ptr = list;
		while (id) {
			id--;
			ptr = ptr->next;
			Assert(ptr);
		}

		Assert((SEXPT_TYPE(ptr->type) != SEXPT_OPERATOR) && (ptr->op < 0));
		expand_operator(item_index);
		add_data(ptr->text, ptr->type);
		list->destroy();
		return 1;
	}

	if ((id >= ID_REPLACE_MENU) && (id < ID_REPLACE_MENU + 511)) {
		Assert(item_index >= 0);
		Assert(nodes[item_index].parent >= 0);
		op = identify_operator(nodes[nodes[item_index].parent].text);
		Assert(op >= 0);

		type = query_operator_argument_type(op, Replace_count); // check argument type at this position
		list = get_listing_opf(type, nodes[item_index].parent, Replace_count);
		Assert(list);

		id -= ID_REPLACE_MENU;
		ptr = list;
		while (id) {
			id--;
			ptr = ptr->next;
			Assert(ptr);
		}

		Assert((SEXPT_TYPE(ptr->type) != SEXPT_OPERATOR) && (ptr->op < 0));
		expand_operator(item_index);
		replace_data(ptr->text, ptr->type);
		list->destroy();
		return 1;
	}

	for (op=0; op<Num_operators; op++) {
		if (id == Operators[op].value) {
			add_or_replace_operator(op);
			return 1;
		}

		if (id == (Operators[op].value | OP_REPLACE_FLAG)) {
			add_or_replace_operator(op, 1);
			return 1;
		}

		if (id == (Operators[op].value | OP_INSERT_FLAG)) {
			int flags;

			z = nodes[item_index].parent;
			flags = nodes[item_index].flags;
			node = allocate_node(z, item_index);
			set_node(node, (SEXPT_OPERATOR | SEXPT_VALID), Operators[op].text);
			nodes[node].flags = flags;
			if (z >= 0)
				h = nodes[z].handle;

			else {
				h = GetParentItem(nodes[item_index].handle);
				if (m_mode == MODE_GOALS) {
					Assert(Goal_editor_dlg);
					Goal_editor_dlg->insert_handler(item_index, node);
					SetItemData(h, node);

				} else if (m_mode == MODE_EVENTS) {
					Assert(Event_editor_dlg);
					Event_editor_dlg->insert_handler(item_index, node);
					SetItemData(h, node);

				} else if (m_mode == MODE_CAMPAIGN) {
					Campaign_tree_formp->insert_handler(item_index, node);
					SetItemData(h, node);

				} else {
					h = TVI_ROOT;
					root_item = node;
				}
			}

			item_handle = nodes[node].handle = insert(Operators[op].text, BITMAP_OPERATOR, BITMAP_OPERATOR, h, nodes[item_index].handle);
			move_branch(item_index, node);

			item_index = node;
			for (i=1; i<Operators[op].min; i++)
				add_default_operator(op, i);

			Expand(item_handle, TVE_EXPAND);
			*modified = 1;
			return 1;
		}
	}

	switch (id) {
		case ID_EDIT_COPY:
			// If a clipboard already exist, unmark it as persistent and free old clipboard
			if (Sexp_clipboard != -1) {
				sexp_unmark_persistent(Sexp_clipboard);
				free_sexp2(Sexp_clipboard);
			}

			// Allocate new clipboard and mark persistent
			Sexp_clipboard = save_branch(item_index, 1);
			sexp_mark_persistent(Sexp_clipboard);
			return 1;

		case ID_EDIT_PASTE:
			// the following assumptions are made..
			Assert((Sexp_clipboard > -1) && (Sexp_nodes[Sexp_clipboard].type != SEXP_NOT_USED));
			Assert(Sexp_nodes[Sexp_clipboard].subtype != SEXP_ATOM_LIST);

			if (Sexp_nodes[Sexp_clipboard].subtype == SEXP_ATOM_OPERATOR) {
				expand_operator(item_index);
				replace_operator(CTEXT(Sexp_clipboard));
				if (Sexp_nodes[Sexp_clipboard].rest != -1) {
					load_branch(Sexp_nodes[Sexp_clipboard].rest, item_index);
					i = nodes[item_index].child;
					while (i != -1) {
						add_sub_tree(i, nodes[item_index].handle);
						i = nodes[i].next;
					}
				}

			} else if (Sexp_nodes[Sexp_clipboard].subtype == SEXP_ATOM_NUMBER) {
				Assert(Sexp_nodes[Sexp_clipboard].rest == -1);
				expand_operator(item_index);
				replace_data(CTEXT(Sexp_clipboard), (SEXPT_NUMBER | SEXPT_VALID));

			} else if (Sexp_nodes[Sexp_clipboard].subtype == SEXP_ATOM_STRING) {
				Assert(Sexp_nodes[Sexp_clipboard].rest == -1);
				expand_operator(item_index);
				replace_data(CTEXT(Sexp_clipboard), (SEXPT_STRING | SEXPT_VALID));

			} else
				Assert(0);  // unknown and/or invalid sexp type

			return 1;

		case ID_EDIT_PASTE_SPECIAL:  // add paste, instead of replace.
			// the following assumptions are made..
			Assert((Sexp_clipboard > -1) && (Sexp_nodes[Sexp_clipboard].type != SEXP_NOT_USED));
			Assert(Sexp_nodes[Sexp_clipboard].subtype != SEXP_ATOM_LIST);

			if (Sexp_nodes[Sexp_clipboard].subtype == SEXP_ATOM_OPERATOR) {
				expand_operator(item_index);
				add_operator(CTEXT(Sexp_clipboard));
				if (Sexp_nodes[Sexp_clipboard].rest != -1) {
					load_branch(Sexp_nodes[Sexp_clipboard].rest, item_index);
					i = nodes[item_index].child;
					while (i != -1) {
						add_sub_tree(i, nodes[item_index].handle);
						i = nodes[i].next;
					}
				}

			} else if (Sexp_nodes[Sexp_clipboard].subtype == SEXP_ATOM_NUMBER) {
				Assert(Sexp_nodes[Sexp_clipboard].rest == -1);
				expand_operator(item_index);
				add_data(CTEXT(Sexp_clipboard), (SEXPT_NUMBER | SEXPT_VALID));

			} else if (Sexp_nodes[Sexp_clipboard].subtype == SEXP_ATOM_STRING) {
				Assert(Sexp_nodes[Sexp_clipboard].rest == -1);
				expand_operator(item_index);
				add_data(CTEXT(Sexp_clipboard), (SEXPT_STRING | SEXPT_VALID));

			} else
				Assert(0);  // unknown and/or invalid sexp type

			return 1;

/*		case ID_SPLIT_LINE:
			if ((nodes[item_index].flags & OPERAND) && (nodes[item_index].flags & EDITABLE))  // expandable?
				expand_operator(item_index);
			else
				merge_operator(item_index);

			return 1;*/

		case ID_EXPAND_ALL:
			expand_branch(item_handle);
			return 1;

		case ID_EDIT_TEXT:
			if (edit_label(item_handle)) {
				*modified = 1;
				EditLabel(item_handle);
			}

			return 1;

		case ID_ADD_STRING:	{
			int node;
			
			node = add_data("string", (SEXPT_STRING | SEXPT_VALID));
			EditLabel(nodes[node].handle);
			return 1;
		}

		case ID_ADD_NUMBER:	{
			int node;

			node = add_data("number", (SEXPT_NUMBER | SEXPT_VALID));
			EditLabel(nodes[node].handle);
			return 1;
		}

		case ID_EDIT_CUT:
			if (Sexp_clipboard != -1) {
				sexp_unmark_persistent(Sexp_clipboard);
				free_sexp2(Sexp_clipboard);
			}

			Sexp_clipboard = save_branch(item_index, 1);
			sexp_mark_persistent(Sexp_clipboard);
			// fall through to ID_DELETE case.

		case ID_DELETE:	{
			int parent, node;
			HTREEITEM h;

			if ((m_mode & ST_ROOT_DELETABLE) && (item_index == -1)) {
				item_index = GetItemData(item_handle);
				if (m_mode == MODE_GOALS) {
					Assert(Goal_editor_dlg);
					node = Goal_editor_dlg->handler(ROOT_DELETED, item_index);

				} else if (m_mode == MODE_EVENTS) {
					Assert(Event_editor_dlg);
					node = Event_editor_dlg->handler(ROOT_DELETED, item_index);

				} else {
					Assert(m_mode == MODE_CAMPAIGN);
					node = Campaign_tree_formp->handler(ROOT_DELETED, item_index);
				}

				Assert(node >= 0);
				free_node2(node);
				DeleteItem(item_handle);
				*modified = 1;
				return 1;
			}

			Assert(item_index >= 0);
			h = GetParentItem(item_handle);
			parent = nodes[item_index].parent;
			if ((parent == -1) && (m_mode == MODE_EVENTS))
				Int3();  // no longer used, temporary to check if called still.

			Assert(parent != -1 && nodes[parent].handle == h);
			free_node(item_index);
			DeleteItem(item_handle);

			node = nodes[parent].child;
/*			if (node != -1 && nodes[node].next == -1 && nodes[node].child == -1) {
				sprintf(buf, "%s %s", nodes[parent].text, nodes[node].text);
				SetItem(h, TVIF_TEXT, buf, 0, 0, 0, 0, 0);
				nodes[parent].flags = OPERAND | EDITABLE;
				nodes[node].flags = COMBINED;
				DeleteItem(nodes[node].handle);
			}*/

			*modified = 1;
			return 1;
		}
	}
	
	return CTreeCtrl::OnCommand(wParam, lParam);
}

// adds to or replaces (based on passed in flag) the current operator
void sexp_tree::add_or_replace_operator(int op, int replace_flag)
{
	int i, op_index, op2;

	op_index = item_index;
	if (replace_flag) {
		if (nodes[item_index].flags & OPERAND) {  // are both operators?
			op2 = identify_operator(nodes[item_index].text);
			Assert(op2 >= 0);
			i = count_args(nodes[item_index].child);
			if ((i >= Operators[op].min) && (i <= Operators[op].max)) {  // are old num args valid?
				while (i--)
					if (query_operator_argument_type(op2, i) != query_operator_argument_type(op, i))  // does each arg match expected type?
						break;

				if (i < 0) {  // everything is ok, so we can keep old arguments with new operator
					set_node(item_index, (SEXPT_OPERATOR | SEXPT_VALID), Operators[op].text);
					SetItemText(nodes[item_index].handle, Operators[op].text);
					nodes[item_index].flags = OPERAND;
					return;
				}
			}
		}

		replace_operator(Operators[op].text);

	} else
		add_operator(Operators[op].text);

	// fill in all the required (minimum) arguments with default values
	for (i=0; i<Operators[op].min; i++)
		add_default_operator(op, i);

	Expand(item_handle, TVE_EXPAND);
}

// initialize node, type operator
//
void sexp_list_item::set_op(int op_num)
{
	int i;

	if (op_num >= FIRST_OP) {  // do we have an op value instead of an op number (index)?
		for (i=0; i<Num_operators; i++)
			if (op_num == Operators[i].value)
				op_num = i;  // convert op value to op number
	}

	op = op_num;
	text = Operators[op].text;
	type = (SEXPT_OPERATOR | SEXPT_VALID);
}

// initialize node, type data
// Defaults: t = SEXPT_STRING
//
void sexp_list_item::set_data(char *str, int t)
{
	op = -1;
	text = str;
	type = t;
}

// add a node to end of list
//
void sexp_list_item::add_op(int op_num)
{
	sexp_list_item *item, *ptr;

	item = new sexp_list_item;
	ptr = this;
	while (ptr->next)
		ptr = ptr->next;

	ptr->next = item;
	item->set_op(op_num);
}

// add a node to end of list
// Defaults: t = SEXPT_STRING
//
void sexp_list_item::add_data(char *str, int t)
{
	sexp_list_item *item, *ptr;

	item = new sexp_list_item;
	ptr = this;
	while (ptr->next)
		ptr = ptr->next;

	ptr->next = item;
	item->set_data(str, t);
}

// add a node to end of list, allocating memory for the text
// Defaults: t = SEXPT_STRING
//
void sexp_list_item::add_data_dup(char *str, int t)
{
	sexp_list_item *item, *ptr;

	item = new sexp_list_item;
	ptr = this;
	while (ptr->next)
		ptr = ptr->next;

	ptr->next = item;
	item->set_data(strdup(str), t);
	item->flags |= SEXP_ITEM_F_DUP;
}

// add an sexp list to end of another list (join lists)
//
void sexp_list_item::add_list(sexp_list_item *list)
{
	sexp_list_item *ptr;

	ptr = this;
	while (ptr->next)
		ptr = ptr->next;

	ptr->next = list;
}

// free all nodes of list
//
void sexp_list_item::destroy()
{
	sexp_list_item *ptr, *ptr2;

	ptr = this;
	while (ptr) {
		ptr2 = ptr->next;
		if (ptr->flags & SEXP_ITEM_F_DUP)
			free(ptr->text);

		delete ptr;
		ptr = ptr2;
	}
}

int sexp_tree::add_default_operator(int op, int argnum)
{
	char buf[256];
	int index;
	sexp_list_item item;
	HTREEITEM h;

	h = item_handle;
	index = item_index;
	item.text = buf;
	if (get_default_value(&item, op, argnum))
		return -1;

	if (item.type & SEXPT_OPERATOR) {
		Assert((item.op >= 0) && (item.op < Num_operators));
		add_or_replace_operator(item.op);
		item_index = index;
		item_handle = h;

	} else {
		// special case for modify-variable (data added 1st arg is variable)
		if ( !stricmp(Operators[op].text, "modify-variable") ) {
			if (argnum == 0) {

				int sexp_var_index = get_index_sexp_variable_name(item.text);
				Assert(sexp_var_index != -1);
				int type = SEXPT_VALID | SEXPT_VARIABLE;
				if (Sexp_variables[sexp_var_index].type & SEXP_VARIABLE_STRING) {
					type |= SEXPT_STRING;
				} else if (Sexp_variables[sexp_var_index].type & SEXP_VARIABLE_NUMBER) {
					type |= SEXPT_NUMBER;
				} else {
					Int3();
				}

				char node_text[2*TOKEN_LENGTH + 2];
				sprintf(node_text, "%s(%s)", item.text, Sexp_variables[sexp_var_index].text);
				add_variable_data(node_text, type);
			} else {
				// the the variable name
				char buf2[256];
				Assert(argnum == 1);
				sexp_list_item temp_item;
				temp_item.text = buf2;
				get_default_value(&temp_item, op, 0);
				int sexp_var_index = get_index_sexp_variable_name(temp_item.text);
				Assert(sexp_var_index != -1);

				// from name get type
				int temp_type = Sexp_variables[sexp_var_index].type;
				int type;
				if (temp_type & SEXP_VARIABLE_NUMBER) {
					type = SEXPT_VALID | SEXPT_NUMBER;
				} else if (temp_type & SEXP_VARIABLE_STRING) {
					type = SEXPT_VALID | SEXPT_STRING;
				} else {
					Int3();
				}
				add_data(item.text, type);
			}
		} else {
			add_data(item.text, item.type);
		}
	}

	return 0;
}

int sexp_tree::get_default_value(sexp_list_item *item, int op, int i)
{
	char *str = NULL;
	int type, index;
	sexp_list_item *list;
	HTREEITEM h;

	h = item_handle;
	index = item_index;
	type = query_operator_argument_type(op, i);
	switch (type) {
		case OPF_NULL:
			item->set_op(OP_NOP);
			return 0;

		case OPF_BOOL:
			item->set_op(OP_TRUE);
			return 0;

		case OPF_NUMBER:
		case OPF_POSITIVE:
		case OPF_AMBIGUOUS:
			// if the top level operators is an AI goal, and we are adding the last number required,
			// assume that this number is a priority and make it 89 instead of 1.
			if ((query_operator_return_type(op) == OPR_AI_GOAL) && (i == (Operators[op].min - 1)))
				item->set_data("89", (SEXPT_NUMBER | SEXPT_VALID));
			else if (((Operators[op].value == OP_HAS_DOCKED_DELAY) || (Operators[op].value == OP_HAS_UNDOCKED_DELAY)) && (i == 2))
				item->set_data("1", (SEXPT_NUMBER | SEXPT_VALID));
			else if ( (Operators[op].value == OP_SHIP_TYPE_DESTROYED) || (Operators[op].value == OP_GOOD_SECONDARY_TIME) )
				item->set_data("100", (SEXPT_NUMBER | SEXPT_VALID));
			else
				item->set_data("0", (SEXPT_NUMBER | SEXPT_VALID));

			return 0;
	}

	list = get_listing_opf(type, index, i);
	if (list) {
		char *ptr;

		ptr = item->text;
		*item = *list;
		item->text = ptr;
		strcpy(item->text, list->text);

		list->destroy();
		return 0;
	}

	// catch anything that doesn't have a default value.  Just describe what should be here instead
	switch (type) {
		case OPF_SHIP:
		case OPF_SHIP_NOT_PLAYER:
		case OPF_SHIP_WING:
		case OPF_SHIP_POINT:
		case OPF_SHIP_WING_POINT:
			str = "<name of ship here>";
			break;

		case OPF_WING:
			str = "<name of wing here>";
			break;

		case OPF_DOCKER_POINT:
			str = "<docker point>";
			break;

		case OPF_DOCKEE_POINT:
			str = "<dockee point>";
			break;

		case OPF_SUBSYSTEM:
		case OPF_AWACS_SUBSYSTEM:
			str = "<name of subsystem>";
			break;

		case OPF_POINT:
			str = "<waypoint>";
			break;

		case OPF_MESSAGE:
			str = "<Message>";
			break;

		case OPF_WHO_FROM:
			//str = "<any allied>";
			str = "<any wingman>";
			break;
			
		case OPF_WAYPOINT_PATH:
			str = "<waypoint path>";
			break;

		case OPF_MISSION_NAME:
			str = "<mission name>";
			break;

		case OPF_GOAL_NAME:
			str = "<goal name>";
			break;

		case OPF_SHIP_TYPE:
			str = "<ship type here>";
			break;

		case OPF_EVENT_NAME:
			str = "<event name>";
			break;

		case OPF_HUGE_WEAPON:
			str = "<huge weapon type>";
			break;

		case OPF_JUMP_NODE_NAME:
			str = "<Jump node name>";
			break;

		default:
			str = "<new default required!>";
			break;
	}

	item->set_data(str, (SEXPT_STRING | SEXPT_VALID));
	return 0;
}

int sexp_tree::query_default_argument_available(int op)
{
	int i;

	Assert(op >= 0);
	for (i=0; i<Operators[op].min; i++)
		if (!query_default_argument_available(op, i))
			return 0;

	return 1;
}

int sexp_tree::query_default_argument_available(int op, int i)
{	
	int j, type;
	object *ptr;

	type = query_operator_argument_type(op, i);
	switch (type) {
		case OPF_NULL:
		case OPF_BOOL:
		case OPF_NUMBER:
		case OPF_POSITIVE:
		case OPF_IFF:
		case OPF_WHO_FROM:
		case OPF_PRIORITY:
		case OPF_SHIP_TYPE:
		case OPF_SUBSYSTEM:		
		case OPF_AWACS_SUBSYSTEM:
		case OPF_DOCKER_POINT:
		case OPF_DOCKEE_POINT:
		case OPF_AI_GOAL:
		case OPF_KEYPRESS:
		case OPF_AI_ORDER:
		case OPF_SKILL_LEVEL:
		case OPF_MEDAL_NAME:
		case OPF_WEAPON_NAME:
		case OPF_SHIP_CLASS_NAME:
		case OPF_HUD_GAUGE_NAME:
		case OPF_HUGE_WEAPON:
		case OPF_JUMP_NODE_NAME:
		case OPF_AMBIGUOUS:
			return 1;

		case OPF_SHIP:
		case OPF_SHIP_NOT_PLAYER:
		case OPF_SHIP_WING:
		case OPF_SHIP_POINT:
		case OPF_SHIP_WING_POINT:
			ptr = GET_FIRST(&obj_used_list);
			while (ptr != END_OF_LIST(&obj_used_list)) {
				if (ptr->type == OBJ_SHIP)
					return 1;

				ptr = GET_NEXT(ptr);
			}

			return 0;

		case OPF_WING:
			for (j=0; j<MAX_WINGS; j++)
				if (Wings[j].wave_count)
					return 1;

			return 0;

		case OPF_POINT:
		case OPF_WAYPOINT_PATH:
			if (Num_waypoint_lists)
				return 1;

			return 0;

		case OPF_MISSION_NAME:
			if (m_mode != MODE_CAMPAIGN) {
				if (!(*Mission_filename))
					return 0;

				return 1;
			}

			if (Campaign.num_missions > 0)
				return 1;

			return 0;

		case OPF_GOAL_NAME: {
			int value;

			value = Operators[op].value;

			if (m_mode == MODE_CAMPAIGN)
				return 1;

			// need to be sure that previous-goal functions are available.  (i.e. we are providing a default argument for them)
			else if ((value == OP_PREVIOUS_GOAL_TRUE) || (value == OP_PREVIOUS_GOAL_FALSE) || (value == OP_PREVIOUS_GOAL_INCOMPLETE) || Num_goals)
				return 1;

			return 0;
		}

		case OPF_EVENT_NAME: {
			int value;

			value = Operators[op].value;
			if (m_mode == MODE_CAMPAIGN)
				return 1;

			// need to be sure that previous-event functions are available.  (i.e. we are providing a default argument for them)
			else if ((value == OP_PREVIOUS_EVENT_TRUE) || (value == OP_PREVIOUS_EVENT_FALSE) || (value == OP_PREVIOUS_EVENT_INCOMPLETE) || Num_mission_events)
				return 1;

			return 0;
		}

		case OPF_MESSAGE:
			if (m_mode == MODE_EVENTS) {
				Assert(Event_editor_dlg);
				if (Event_editor_dlg->current_message_name(0))
					return 1;

			} else {
				if (Num_messages > Num_builtin_messages)
					return 1;
			}

			return 0;

		case OPF_VARIABLE_NAME:
			if (sexp_variable_count() > 0) {
				return 1;
			} else {
				return 0;
			}

		default:
			Int3();

	}

	return 0;
}

// expand a combined line (one with an operator and it's one argument on the same line) into
// 2 lines.
void sexp_tree::expand_operator(int node)
{
	int data;
	HTREEITEM h;

	if (nodes[node].flags & COMBINED) {
		node = nodes[node].parent;
		Assert((nodes[node].flags & OPERAND) && (nodes[node].flags & EDITABLE));
	}

	if ((nodes[node].flags & OPERAND) && (nodes[node].flags & EDITABLE)) {  // expandable?
		Assert(nodes[node].type & SEXPT_OPERATOR);
		h = nodes[node].handle;
		data = nodes[node].child;
		Assert(data != -1 && nodes[data].next == -1 && nodes[data].child == -1);

		SetItem(h, TVIF_TEXT, nodes[node].text, 0, 0, 0, 0, 0);
		nodes[node].flags = OPERAND;
		nodes[data].handle = insert(nodes[data].text, BITMAP_DATA, BITMAP_DATA, h);
		nodes[data].flags = EDITABLE;
		Expand(h, TVE_EXPAND);
	}
}

// expand a CTreeCtrl branch and all of it's children
void sexp_tree::expand_branch(HTREEITEM h)
{
	Expand(h, TVE_EXPAND);
	h = GetChildItem(h);
	while (h) {
		expand_branch(h);
		h = GetNextSiblingItem(h);
	}
}

void sexp_tree::merge_operator(int node)
{
/*	char buf[256];
	int child;

	if (nodes[node].flags == EDITABLE)  // data
		node = nodes[node].parent;

	if (node != -1) {
		child = nodes[node].child;
		if (child != -1 && nodes[child].next == -1 && nodes[child].child == -1) {
			sprintf(buf, "%s %s", nodes[node].text, nodes[child].text);
			SetItemText(nodes[node].handle, buf);
			nodes[node].flags = OPERAND | EDITABLE;
			nodes[child].flags = COMBINED;
			DeleteItem(nodes[child].handle);
			nodes[child].handle = NULL;
			return;
		}
	}*/
}

// add a data node under operator pointed to by item_index
int sexp_tree::add_data(char *data, int type)
{
	int node;

	expand_operator(item_index);
	node = allocate_node(item_index);
	set_node(node, type, data);
	nodes[node].handle = insert(data, BITMAP_DATA, BITMAP_DATA, nodes[item_index].handle);
	nodes[node].flags = EDITABLE;
	*modified = 1;
	return node;
}

// add a (variable) data node under operator pointed to by item_index
int sexp_tree::add_variable_data(char *data, int type)
{
	int node;

	Assert(type & SEXPT_VARIABLE);

	expand_operator(item_index);
	node = allocate_node(item_index);
	set_node(node, type, data);
	nodes[node].handle = insert(data, BITMAP_VARIABLE, BITMAP_VARIABLE, nodes[item_index].handle);
	nodes[node].flags = NOT_EDITABLE;
	*modified = 1;
	return node;
}

// add an operator under operator pointed to by item_index.  Updates item_index to point
// to this new operator.
void sexp_tree::add_operator(char *op, HTREEITEM h)
{
	int node;
	
	if (item_index == -1) {
		node = allocate_node(-1);
		set_node(node, (SEXPT_OPERATOR | SEXPT_VALID), op);
		item_handle = nodes[node].handle = insert(op, BITMAP_OPERATOR, BITMAP_OPERATOR, h);

	} else {
		expand_operator(item_index);
		node = allocate_node(item_index);
		set_node(node, (SEXPT_OPERATOR | SEXPT_VALID), op);
		item_handle = nodes[node].handle = insert(op, BITMAP_OPERATOR, BITMAP_OPERATOR, nodes[item_index].handle);
	}

	nodes[node].flags = OPERAND;
	item_index = node;
	*modified = 1;
}

// add an operator with one argument under operator pointed to by item_index.  This function
// exists because the one arg case is a special case.  The operator and argument is
// displayed on the same line.
/*void sexp_tree::add_one_arg_operator(char *op, char *data, int type)
{
	char str[80];
	int node1, node2;
	
	expand_operator(item_index);
	node1 = allocate_node(item_index);
	node2 = allocate_node(node1);
	set_node(node1, SEXPT_OPERATOR, op);
	set_node(node2, type, data);
	sprintf(str, "%s %s", op, data);
	nodes[node1].handle = insert(str, nodes[item_index].handle);
	nodes[node1].flags = OPERAND | EDITABLE;
	nodes[node2].flags = COMBINED;
	*modified = 1;
}*/

/*
int sexp_tree::verify_tree(int *bypass)
{
	return verify_tree(0, bypass);
}

// check the sexp tree for errors.  Return -1 if error, or 0 if no errors.  If an error
// is found, item_index = node of error.
int sexp_tree::verify_tree(int node, int *bypass)
{
	int i, type, count, op, type2, op2, argnum = 0;

	if (!total)
		return 0;  // nothing to check

	Assert(node >= 0 && node < MAX_SEXP_TREE_SIZE);
	Assert(nodes[node].type == SEXPT_OPERATOR);

	op = identify_operator(nodes[node].text);
	if (op == -1)
		return node_error(node, "Unknown operator", bypass);

	count = count_args(nodes[node].child);
	if (count < Operators[op].min)
		return node_error(node, "Too few arguments for operator", bypass);
	if (count > Operators[op].max)
		return node_error(node, "Too many arguments for operator", bypass);

	node = nodes[node].child;  // get first argument
	while (node != -1) {
		type = query_operator_argument_type(op, argnum);
		Assert(nodes[node].type & SEXPT_VALID);
		if (nodes[node].type == SEXPT_OPERATOR) {
			if (verify_tree(node) == -1)
				return -1;

			op2 = identify_operator(nodes[node].text);  // no error checking, because it was done in the call above.
			type2 = query_operator_return_type(op2);

		} else if (nodes[node].type == SEXPT_NUMBER) {
			char *ptr;

			type2 = OPR_NUMBER;
			ptr = nodes[node].text;
			while (*ptr)
				if (!isdigit(*ptr++))
					return node_error(node, "Number is invalid", bypass);

		} else if (nodes[node].type == SEXPT_STRING) {
			type2 = SEXP_ATOM_STRING;

		} else
			Assert(0);  // unknown and invalid sexp node type.

		switch (type) {
			case OPF_NUMBER:
				if (type2 != OPR_NUMBER)
					return node_error(node, "Number or number return type expected here", bypass);

				break;

			case OPF_SHIP:
				if (type2 == SEXP_ATOM_STRING)
					if (ship_name_lookup(nodes[node].text) == -1)
						type2 = 0;

				if (type2 != SEXP_ATOM_STRING)
					return node_error(node, "Ship name expected here", bypass);

				break;

			case OPF_WING:
				if (type2 == SEXP_ATOM_STRING)
					if (wing_name_lookup(nodes[node].text) == -1)
						type2 = 0;

				if (type2 != SEXP_ATOM_STRING)
					return node_error(node, "Wing name expected here", bypass);

				break;

			case OPF_SHIP_WING:
				if (type2 == SEXP_ATOM_STRING)
					if (ship_name_lookup(nodes[node].text) == -1)
						if (wing_name_lookup(nodes[node].text) == -1)
							type2 = 0;

				if (type2 != SEXP_ATOM_STRING)
					return node_error(node, "Ship or wing name expected here", bypass);

				break;

			case OPF_BOOL:
				if (type2 != OPR_BOOL)
					return node_error(node, "Boolean return type expected here", bypass);

				break;

			case OPF_NULL:
				if (type2 != OPR_NULL)
					return node_error(node, "No return type operator expected here", bypass);

				break;

			case OPF_POINT:
				if (type2 != SEXP_ATOM_STRING || verify_vector(nodes[node].text))
					return node_error(node, "3d coordinate expected here", bypass);

				break;

			case OPF_SUBSYSTEM:
				if (type2 == SEXP_ATOM_STRING)
					if (ai_get_subsystem_type(nodes[node].text) == SUBSYSTEM_UNKNOWN)
						type2 = 0;

				if (type2 != SEXP_ATOM_STRING)
					return node_error(node, "Subsystem name expected here", bypass);

				break;

			case OPF_IFF:
				if (type2 == SEXP_ATOM_STRING) {
					for (i=0; i<Num_team_names; i++)
						if (!stricmp(Team_names[i], nodes[node].text))
							break;
				}

				if (i == Num_team_names)
					return node_error(node, "Iff team type expected here", bypass);

				break;

			case OPF_AI_GOAL:
				if (type2 != OPR_AI_GOAL)
					return node_error(node, "Ai goal return type expected here", bypass);

				break;

			case OPF_DOCKER_POINT:
				if (type2 != SEXP_ATOM_STRING)
					return node_error(node, "Docker docking point name expected here", bypass);

				break;

			case OPF_DOCKEE_POINT:
				if (type2 != SEXP_ATOM_STRING)
					return node_error(node, "Dockee docking point name expected here", bypass);

				break;
		}

		node = nodes[node].next;
		argnum++;
	}

	return 0;
}
*/

// display an error message and position to point of error (a node)
int sexp_tree::node_error(int node, char *msg, int *bypass)
{
	char text[512];

	if (bypass)
		*bypass = 1;

	item_index = node;
	item_handle = nodes[node].handle;
	if (nodes[node].flags & COMBINED)
		item_handle = nodes[nodes[node].parent].handle;

	ensure_visible(node);
	SelectItem(item_handle);
	sprintf(text, "%s\n\nContinue checking for more errors?", msg);
	if (MessageBox(text, "Sexp error", MB_YESNO | MB_ICONEXCLAMATION) == IDNO)
		return -1;
	else
		return 0;
}

void sexp_tree::hilite_item(int node)
{
	ensure_visible(node);
	SelectItem(nodes[node].handle);
}

// because the MFC function EnsureVisible() doesn't do what it says it does, I wrote this.
void sexp_tree::ensure_visible(int node)
{
	Assert(node != -1);
	if (nodes[node].parent != -1)
		ensure_visible(nodes[node].parent);  // expand all parents first

	if (nodes[node].child != -1)  // expandable?
		Expand(nodes[node].handle, TVE_EXPAND);  // expand this item
}

void sexp_tree::link_modified(int *ptr)
{
	modified = ptr;
}

void get_variable_default_text_from_variable_text(char *text, char *default_text)
{
	int len;
	char *start;

	// find '('
	start = strstr(text, "(");
	Assert(start);
	start++;

	// get length and copy all but last char ")"
	len = strlen(start);
	strncpy(default_text, start, len-1);

	// add null termination
	default_text[len-1] = '\0';
}

void get_variable_name_from_sexp_tree_node_text(const char *text, char *var_name)
{
	int length;
	length = strcspn(text, "(");

	strncpy(var_name, text, length);
	var_name[length] = '\0';
}

int sexp_tree::get_modify_variable_type()
{
	Assert(item_index > -1);
	int sexp_var_index;

	// get arg
	int parent = nodes[item_index].parent;
	Assert(parent != -1);

	if ( !stricmp(nodes[parent].text, "modify-variable") ) {
		Assert(nodes[parent].child != -1);
		sexp_var_index = get_tree_name_to_sexp_variable_index(nodes[nodes[parent].child].text);
		Assert(sexp_var_index != -1);
	} else {
		Int3();  // should not be called otherwise
	}

	if (Sexp_variables[sexp_var_index].type & SEXP_VARIABLE_NUMBER) {
		return OPF_NUMBER;
	} else if (Sexp_variables[sexp_var_index].type & SEXP_VARIABLE_STRING) {
		return OPF_AMBIGUOUS;
	} else {
		Int3();
		return 0;
	}
}


void sexp_tree::verify_and_fix_arguments(int node)
{
	int op, arg_num, type, tmp;
	static int flag = 0;
	sexp_list_item *list, *ptr;

	if (flag)
		return;

	flag++;
	op = identify_operator(nodes[node].text);
	if (op < 0)
		return;

	tmp = item_index;
	item_index = node;

	arg_num = 0;
	item_index = nodes[node].child;
	while (item_index >= 0) {
		// get listing of valid argument values for node item_index
		type = query_operator_argument_type(op, arg_num);
		// special case for modify-variable
		if (type == OPF_AMBIGUOUS) {
			// check if parent variable type is number, returns OPF_NUMBER or OPF_AMBIGUOUS
			type = get_modify_variable_type();
		}
		if (query_restricted_opf_range(type)) {
			list = get_listing_opf(type, node, arg_num);
			if (!list && (arg_num >= Operators[op].min)) {
				free_node(item_index, 1);
				item_index = tmp;
				flag--;
				return;
			}

			if (list) {
				// get a pointer to nodes[item_index].text for normal value
				// or default variable value if variable
				char *text_ptr;
				char default_variable_text[TOKEN_LENGTH];
				if (nodes[item_index].type & SEXPT_VARIABLE) {
					// special case for modify-variable
					if ( !stricmp(Operators[op].text, "modify-variable") ) {
						// make text_ptr to start - before '('
						get_variable_name_from_sexp_tree_node_text(nodes[item_index].text, default_variable_text);
						text_ptr = default_variable_text;
					} else {
						get_variable_default_text_from_variable_text(nodes[item_index].text, default_variable_text);
						text_ptr = default_variable_text;
					}
				} else {
					text_ptr = nodes[item_index].text;
				}

				ptr = list;
				while (ptr) {

					if (ptr->text != NULL) {
						// make sure text is not NULL
						// check that proposed text is valid for operator
						if ( !stricmp(ptr->text, text_ptr) )
							break;

						ptr = ptr->next;
					} else {
						// text is NULL, so set ptr to NULL to end loop
						ptr = NULL;
					}
				}

				if (!ptr) {  // argument isn't in list of valid choices, 
					if (list->op >= 0) {
						replace_operator(list->text);
					} else {
						replace_data(list->text, list->type);
					}
				}

			} else {
				bool invalid = false;
				if (type == OPF_AMBIGUOUS) {
					if (SEXPT_TYPE(nodes[item_index].type) == SEXPT_OPERATOR) {
						invalid = true;
					}
				} else {
					if (SEXPT_TYPE(nodes[item_index].type) != SEXPT_OPERATOR) {
						invalid = true;
					}
				}

				if (invalid) {
					replace_data("<Invalid>", (SEXPT_STRING | SEXPT_VALID));
				}
			}

			if (nodes[item_index].type & SEXPT_OPERATOR)
				verify_and_fix_arguments(item_index);
		}

		item_index = nodes[item_index].next;
		arg_num++;
	}

	item_index = tmp;
	flag--;
}

void sexp_tree::replace_data(char *data, int type)
{
	int node;
	HTREEITEM h;

	node = nodes[item_index].child;
	if (node != -1)
		free_node2(node);

	nodes[item_index].child = -1;
	h = nodes[item_index].handle;
	while (ItemHasChildren(h))
		DeleteItem(GetChildItem(h));

	set_node(item_index, type, data);
	SetItemText(h, data);
	SetItemImage(h, BITMAP_DATA, BITMAP_DATA);
	nodes[item_index].flags = EDITABLE;

	// check remaining data beyond replaced data for validity (in case any of it is dependent on data just replaced)
	verify_and_fix_arguments(nodes[item_index].parent);

	*modified = 1;
	update_help(GetSelectedItem());
}


// Replaces data with sexp_variable type data
void sexp_tree::replace_variable_data(int var_idx, int type)
{
	int node;
	HTREEITEM h;
	char buf[128];

	Assert(type & SEXPT_VARIABLE);

	node = nodes[item_index].child;
	if (node != -1)
		free_node2(node);

	nodes[item_index].child = -1;
	h = nodes[item_index].handle;
	while (ItemHasChildren(h)) {
		DeleteItem(GetChildItem(h));
	}

	// Assemble name
	sprintf(buf, "%s(%s)", Sexp_variables[var_idx].variable_name, Sexp_variables[var_idx].text);

	set_node(item_index, type, buf);
	SetItemText(h, buf);
	SetItemImage(h, BITMAP_VARIABLE, BITMAP_VARIABLE);
	nodes[item_index].flags = NOT_EDITABLE;

	// check remaining data beyond replaced data for validity (in case any of it is dependent on data just replaced)
	verify_and_fix_arguments(nodes[item_index].parent);

	*modified = 1;
	update_help(GetSelectedItem());
}



void sexp_tree::replace_operator(char *op)
{
	int node;
	HTREEITEM h;

	node = nodes[item_index].child;
	if (node != -1)
		free_node2(node);

	nodes[item_index].child = -1;
	h = nodes[item_index].handle;
	while (ItemHasChildren(h))
		DeleteItem(GetChildItem(h));

	set_node(item_index, (SEXPT_OPERATOR | SEXPT_VALID), op);
	SetItemText(h, op);
	nodes[item_index].flags = OPERAND;
	*modified = 1;
	update_help(GetSelectedItem());

	// hack added at Allender's request.  If changing ship in an ai-dock operator, re-default
	// docking point.
}

/*void sexp_tree::replace_one_arg_operator(char *op, char *data, int type)
{
	char str[80];
	int node;
	HTREEITEM h;

	node = nodes[item_index].child;
	if (node != -1)
		free_node2(node);

	nodes[item_index].child = -1;
	h = nodes[item_index].handle;
	while (ItemHasChildren(h))
		DeleteItem(GetChildItem(h));
	
	node = allocate_node(item_index);
	set_node(item_index, SEXPT_OPERATOR, op);
	set_node(node, type, data);
	sprintf(str, "%s %s", op, data);
	SetItemText(h, str);
	nodes[item_index].flags = OPERAND | EDITABLE;
	nodes[node].flags = COMBINED;
	*modified = 1;
	update_help(GetSelectedItem());
}*/

// moves a whole sexp tree branch to a new position under 'parent' and after 'after'.
// The expansion state is preserved, and node handles are updated.
void sexp_tree::move_branch(int source, int parent)
{
	int node;

	// if no source, skip everything
	if (source != -1) {
		node = nodes[source].parent;
		if (node != -1) {
			if (nodes[node].child == source)
				nodes[node].child = nodes[source].next;
			else {
				node = nodes[node].child;
				while (nodes[node].next != source) {
					node = nodes[node].next;
					Assert(node != -1);
				}

				nodes[node].next = nodes[source].next;
			}
		}

		nodes[source].parent = parent;
		nodes[source].next = -1;
		if (parent) {
			if (nodes[parent].child == -1)
				nodes[parent].child = source;
			else {
				node = nodes[parent].child;
				while (nodes[node].next != -1)
					node = nodes[node].next;

				nodes[node].next = source;
			}

			move_branch(nodes[source].handle, nodes[parent].handle);

		} else
			move_branch(nodes[source].handle);
	}
}

HTREEITEM sexp_tree::move_branch(HTREEITEM source, HTREEITEM parent, HTREEITEM after)
{
	int i, image1, image2;
	HTREEITEM h = 0, child, next;

	if (source) {
		for (i=0; i<MAX_SEXP_TREE_SIZE; i++)
			if (nodes[i].handle == source)
				break;

		if (i < MAX_SEXP_TREE_SIZE) {
			GetItemImage(source, image1, image2);
			h = insert(GetItemText(source), image1, image2, parent, after);
			nodes[i].handle = h;

		} else {
			GetItemImage(source, image1, image2);
  			h = insert(GetItemText(source), image1, image2, parent, after);
		}

		SetItemData(h, GetItemData(source));
		child = GetChildItem(source);
		while (child) {
			next = GetNextSiblingItem(child);
			move_branch(child, h);
			child = next;
		}

		if (GetItemState(source, TVIS_EXPANDED) & TVIS_EXPANDED)
			Expand(h, TVE_EXPAND);

		DeleteItem(source);
	}

	return h;
}

void sexp_tree::copy_branch(HTREEITEM source, HTREEITEM parent, HTREEITEM after)
{
	int i, image1, image2;
	HTREEITEM h, child;

	if (source) {
		for (i=0; i<MAX_SEXP_TREE_SIZE; i++)
			if (nodes[i].handle == source)
				break;

		if (i < MAX_SEXP_TREE_SIZE) {
			GetItemImage(source, image1, image2);
			h = insert(GetItemText(source), image1, image2, parent, after);
			nodes[i].handle = h;

		} else {
			GetItemImage(source, image1, image2);
  			h = insert(GetItemText(source), image1, image2, parent, after);
		}

		SetItemData(h, GetItemData(source));
		child = GetChildItem(source);
		while (child) {
			copy_branch(child, h);
			child = GetNextSiblingItem(child);
		}

		if (GetItemState(source, TVIS_EXPANDED) & TVIS_EXPANDED)
			Expand(h, TVE_EXPAND);
	}
}

void sexp_tree::swap_roots(HTREEITEM one, HTREEITEM two)
{
	HTREEITEM h;

	Assert(!GetParentItem(one));
	Assert(!GetParentItem(two));
//	copy_branch(one, TVI_ROOT, two);
//	move_branch(two, TVI_ROOT, one);
//	DeleteItem(one);
	h = move_branch(one, TVI_ROOT, two);
	SelectItem(h);
	SelectItem(h);
	*modified = 1;
}

void sexp_tree::OnBegindrag(NMHDR* pNMHDR, LRESULT* pResult) 
{
	UINT flags;

//	ScreenToClient(&m_pt);
	ASSERT(!m_dragging);
	m_h_drag = HitTest(m_pt, &flags);
	m_h_drop = NULL;

	if (!m_mode || GetParentItem(m_h_drag))
		return;

	ASSERT(m_p_image_list == NULL);
	m_p_image_list = CreateDragImage(m_h_drag);  // get the image list for dragging
	if (!m_p_image_list)
		return;

	m_p_image_list->DragShowNolock(TRUE);
	m_p_image_list->SetDragCursorImage(0, CPoint(0, 0));
	m_p_image_list->BeginDrag(0, CPoint(0,0));
	m_p_image_list->DragMove(m_pt);
	m_p_image_list->DragEnter(this, m_pt);
	SetCapture();
	m_dragging = TRUE;
}

void sexp_tree::OnLButtonDown(UINT nFlags, CPoint point) 
{
	m_pt = point;
	CTreeCtrl::OnLButtonDown(nFlags, point);
}

void sexp_tree::OnMouseMove(UINT nFlags, CPoint point) 
{
	HTREEITEM hitem;
	UINT flags;

	if (m_dragging) {
		ASSERT(m_p_image_list != NULL);
		m_p_image_list->DragMove(point);
		if ((hitem = HitTest(point, &flags)) != NULL)
			if (!GetParentItem(hitem)) {
				m_p_image_list->DragLeave(this);
				SelectDropTarget(hitem);
				m_h_drop = hitem;
				m_p_image_list->DragEnter(this, point);
			}
	}

	CTreeCtrl::OnMouseMove(nFlags, point);
}

void sexp_tree::OnLButtonUp(UINT nFlags, CPoint point) 
{
	int index1, index2;

	if (m_dragging) {
		ASSERT(m_p_image_list != NULL);
		m_p_image_list->DragLeave(this);
		m_p_image_list->EndDrag();
		delete m_p_image_list;
		m_p_image_list = NULL;

		if (m_h_drop && m_h_drag != m_h_drop) {
			Assert(m_h_drag);
			index1 = GetItemData(m_h_drag);
			index2 = GetItemData(m_h_drop);
			swap_roots(m_h_drag, m_h_drop);
			if (m_mode == MODE_GOALS) {
				Assert(Goal_editor_dlg);
				Goal_editor_dlg->swap_handler(index1, index2);

			} else if (m_mode == MODE_EVENTS) {
				Assert(Event_editor_dlg);
				Event_editor_dlg->swap_handler(index1, index2);

			} else if (m_mode == MODE_CAMPAIGN) {
				Campaign_tree_formp->swap_handler(index1, index2);

			} else
				Assert(0);

		} else
			MessageBeep(0);

		ReleaseCapture();
		m_dragging = FALSE;
		SelectDropTarget(NULL);
	}

	CTreeCtrl::OnLButtonUp(nFlags, point);
}

void sexp_tree::setup(CEdit *ptr)
{
	CImageList *pimagelist;
	CBitmap bitmap;

	help_box = ptr;
	if (help_box) {
		int stops[2] = { 10, 30 };

		help_box -> SetTabStops(2, (LPINT) stops);
	}

	pimagelist = GetImageList(TVSIL_NORMAL);
	if (!pimagelist) {
		pimagelist = new CImageList();
		pimagelist->Create(16, 16, TRUE/*bMask*/, 2, 9);

		bitmap.LoadBitmap(IDB_OPERATOR);
		pimagelist->Add(&bitmap, (COLORREF) 0xFFFFFF);
		bitmap.DeleteObject();

		bitmap.LoadBitmap(IDB_DATA);
		pimagelist->Add(&bitmap, (COLORREF) 0xFF00FF);
		bitmap.DeleteObject();

		bitmap.LoadBitmap(IDB_VARIABLE);
		pimagelist->Add(&bitmap, (COLORREF) 0xFF00FF);
		bitmap.DeleteObject();

		bitmap.LoadBitmap(IDB_ROOT);
		pimagelist->Add(&bitmap, (COLORREF) 0xFF00FF);
		bitmap.DeleteObject();

		bitmap.LoadBitmap(IDB_ROOT_DIRECTIVE);
		pimagelist->Add(&bitmap, (COLORREF) 0xFFFFFF);
		bitmap.DeleteObject();

		bitmap.LoadBitmap(IDB_CHAINED);
		pimagelist->Add(&bitmap, (COLORREF) 0xFF00FF);
		bitmap.DeleteObject();

		bitmap.LoadBitmap(IDB_CHAINED_DIRECTIVE);
		pimagelist->Add(&bitmap, (COLORREF) 0xFFFFFF);
		bitmap.DeleteObject();

		bitmap.LoadBitmap(IDB_GREEN_DOT);
		pimagelist->Add(&bitmap, (COLORREF) 0xFFFFFF);
		bitmap.DeleteObject();

		bitmap.LoadBitmap(IDB_BLACK_DOT);
		pimagelist->Add(&bitmap, (COLORREF) 0xFFFFFF);
		bitmap.DeleteObject();

		SetImageList(pimagelist, TVSIL_NORMAL);
	}
}
//#define BITMAP_OPERATOR 0
//#define BITMAP_DATA 1
//#define BITMAP_VARIABLE 2
//#define BITMAP_ROOT 3
//#define BITMAP_ROOT_DIRECTIVE 4
//#define BITMAP_CHAIN 5
//#define BITMAP_CHAIN_DIRECTIVE 6
//#define BITMAP_GREEN_DOT 7
//#define BITMAP_BLACK_DOT 8


HTREEITEM sexp_tree::insert(LPCTSTR lpszItem, int image, int sel_image, HTREEITEM hParent, HTREEITEM hInsertAfter)
{
	return InsertItem(lpszItem, image, sel_image, hParent, hInsertAfter);

}

void sexp_tree::OnDestroy() 
{
	CImageList *pimagelist;

	pimagelist = GetImageList(TVSIL_NORMAL);
	if (pimagelist) {
		pimagelist->DeleteImageList();
		delete pimagelist;
	}

	CTreeCtrl::OnDestroy();
}

HTREEITEM sexp_tree::handle(int node)
{
	return nodes[node].handle;
}

char *sexp_tree::help(int code)
{
	int i;

	i = sizeof(Sexp_help) / sizeof(sexp_help_struct);
	while (i--) {
		if (Sexp_help[i].id == code)
			break;
	}

	if (i >= 0)
		return Sexp_help[i].help;

	return NULL;
}

// get type of item clicked on
int sexp_tree::get_type(HTREEITEM h)
{
	int i;

	// get index into sexp_tree 
	for (i=0; i<MAX_SEXP_TREE_SIZE; i++)
		if (nodes[i].handle == h)
			break;

	if ( (i >= MAX_SEXP_TREE_SIZE) ) {
		// Int3();	// This would be the root of the tree  -- ie, event name
		return -1;
	}

	return nodes[i].type;
}


void sexp_tree::update_help(HTREEITEM h)
{
	char *str;
	int i, j, z, c, code;
	CString text;

	for (i=0; i<Num_operators; i++)
		for (j=0; j<Num_op_menus; j++)
			if ((Operators[i].value & OP_CATAGORY_MASK) == op_menu[j].id) {
				if (!help(Operators[i].value))
					Int3();  // Damn you, Allender!  If you add new sexp operators, add help for them too! :)
			}

	help_box = (CEdit *) GetParent()->GetDlgItem(IDC_HELP_BOX);
	if (!help_box || !::IsWindow(help_box->m_hWnd))
		return;

	for (i=0; i<MAX_SEXP_TREE_SIZE; i++)
		if (nodes[i].handle == h)
			break;

	if ((i >= MAX_SEXP_TREE_SIZE) || !nodes[i].type) {
		help_box->SetWindowText("");
		return;
	}

	if (SEXPT_TYPE(nodes[i].type) != SEXPT_OPERATOR) {
		z = nodes[i].parent;
		if (z < 0) {
			Warning(LOCATION, "Sexp data \"%s\" has no parent!", nodes[i].text);
			return;
		}

		code = identify_operator(nodes[z].text);
		if (code >= 0) {
			c = 0;
			j = nodes[z].child;
			while ((j >= 0) && (j != i)) {
				j = nodes[j].next;
				c++;
			}

			Assert(j >= 0);
			if (query_operator_argument_type(code, c) == OPF_MESSAGE) {
				for (j=0; j<Num_messages; j++)
					if (!stricmp(Messages[j].name, nodes[i].text)) {
						text.Format("Message Text:\r\n%s", Messages[j].message);
						help_box->SetWindowText(text);
						return;
					}
			}
		}

		i = z;
	}

	code = find_operator(nodes[i].text);
	str = help(code);
	if (!str)
		str = "No help available";

	help_box->SetWindowText(str);
}

// find list of sexp_tree nodes with text
// stuff node indices into find[]
int sexp_tree::find_text(char *text, int *find)
{
	int i, find_count;

	// initialize find
	for (i=0; i<MAX_SEARCH_MESSAGE_DEPTH; i++) {
		find[i] = -1;
	}

	find_count = 0;

	for (i=0; i<MAX_SEXP_TREE_SIZE; i++) {
		// only look at used and editable nodes
		if ((nodes[i].flags & EDITABLE && (nodes[i].type != SEXPT_UNUSED))) {
			// find the text
			if ( !stricmp(nodes[i].text, text)  ) {
				find[find_count++] = i;

				// don't exceed max count - array bounds
				if (find_count == MAX_SEARCH_MESSAGE_DEPTH) {
					break;
				}
			}
		}
	}

	return find_count;
}
			

void sexp_tree::OnKeydown(NMHDR *pNMHDR, LRESULT *pResult) 
{
	int key;
	TV_KEYDOWN *pTVKeyDown = (TV_KEYDOWN *) pNMHDR;

	key = pTVKeyDown->wVKey;
	if (key == VK_SPACE)
		EditLabel(GetSelectedItem());

	*pResult = 0;
}

// Determine if a given opf code has a restricted argument range (i.e. has a specific, limited
// set of argument values, or has virtually unlimited possibilities.  For example, boolean values
// only have true or false, so it is restricted, but a number could be anything, so it's not.
//
int sexp_tree::query_restricted_opf_range(int opf)
{
	switch (opf) {
		case OPF_NUMBER:
		case OPF_POSITIVE:
		case OPF_WHO_FROM:
			return 0;
	}

	return 1;
}

// generate listing of valid argument values.
// opf = operator format to generate list for
// parent_node = the parent node we are generating list for
// arg_index = argument number of parent this argument will go at
//
sexp_list_item *sexp_tree::get_listing_opf(int opf, int parent_node, int arg_index)
{
	switch (opf) {
		case OPF_NONE:
			return NULL;

		case OPF_NULL:
			return get_listing_opf_null();

		case OPF_BOOL:
			return get_listing_opf_bool(parent_node);

		case OPF_NUMBER:
			return get_listing_opf_number();

		case OPF_SHIP:
			return get_listing_opf_ship(parent_node);

		case OPF_WING:
			return get_listing_opf_wing();
		
		case OPF_AWACS_SUBSYSTEM:
		case OPF_SUBSYSTEM:
			return get_listing_opf_subsystem(parent_node, arg_index);			

		case OPF_POINT:
			return get_listing_opf_point();

		case OPF_IFF:
			return get_listing_opf_iff();

		case OPF_AI_GOAL:
			return get_listing_opf_ai_goal(parent_node);

		case OPF_DOCKER_POINT:
			return get_listing_opf_docker_point(parent_node);

		case OPF_DOCKEE_POINT:
			return get_listing_opf_dockee_point(parent_node);

		case OPF_MESSAGE:
			return get_listing_opf_message();

		case OPF_WHO_FROM:
			return get_listing_opf_who_from();

		case OPF_PRIORITY:
			return get_listing_opf_priority();

		case OPF_WAYPOINT_PATH:
			return get_listing_opf_waypoint_path();

		case OPF_POSITIVE:
			return get_listing_opf_positive();

		case OPF_MISSION_NAME:
			return get_listing_opf_mission_name();

		case OPF_SHIP_POINT:
			return get_listing_opf_ship_point();

		case OPF_GOAL_NAME:
			return get_listing_opf_goal_name(parent_node);

		case OPF_SHIP_WING:
			return get_listing_opf_ship_wing();

		case OPF_SHIP_WING_POINT:
			return get_listing_opf_ship_wing_point();

		case OPF_SHIP_TYPE:
			return get_listing_opf_ship_type();

		case OPF_KEYPRESS:
			return get_listing_opf_keypress();

		case OPF_EVENT_NAME:
			return get_listing_opf_event_name(parent_node);

		case OPF_AI_ORDER:
			return get_listing_opf_ai_order();

		case OPF_SKILL_LEVEL:
			return get_listing_opf_skill_level();

		case OPF_MEDAL_NAME:
			return get_listing_opf_medal_name();

		case OPF_WEAPON_NAME:
			return get_listing_opf_weapon_name();

		case OPF_SHIP_CLASS_NAME:
			return get_listing_opf_ship_class_name();

		case OPF_HUD_GAUGE_NAME:
			return get_listing_opf_hud_gauge_name();

		case OPF_HUGE_WEAPON:
			return get_listing_opf_huge_weapon();

		case OPF_SHIP_NOT_PLAYER:
			return get_listing_opf_ship_not_player();

		case OPF_JUMP_NODE_NAME:
			return get_listing_opf_jump_nodes();

		case OPF_VARIABLE_NAME:
			return get_listing_opf_variable_names();

		case OPF_AMBIGUOUS:
			return NULL();

		default:
			Int3();  // unknown OPF code
	}

	return NULL;
}

sexp_list_item *sexp_tree::get_listing_opf_null()
{
	int i;
	sexp_list_item head;

	for (i=0; i<Num_operators; i++)
		if (query_operator_return_type(i) == OPR_NULL)
			head.add_op(i);

	return head.next;
}

sexp_list_item *sexp_tree::get_listing_opf_bool(int parent_node)
{
	int i, only_basic;
	sexp_list_item head;

	// search for the previous goal/event operators.  If found, only add the true/false
	// sexpressions to the list
	only_basic = 0;
	if ( parent_node != -1 ) {
		int op;

		op = find_operator(nodes[parent_node].text);
		if ( (op == OP_PREVIOUS_GOAL_TRUE) || (op == OP_PREVIOUS_GOAL_FALSE) || (op == OP_PREVIOUS_EVENT_TRUE) || (op == OP_PREVIOUS_EVENT_FALSE) )
			only_basic = 1;

	}

	for (i=0; i<Num_operators; i++) {
		if (query_operator_return_type(i) == OPR_BOOL) {
			if ( !only_basic || (only_basic && ((Operators[i].value == OP_TRUE) || (Operators[i].value == OP_FALSE))) ) {
				head.add_op(i);
			}
		}
	}

	return head.next;
}

sexp_list_item *sexp_tree::get_listing_opf_positive()
{
	int i;
	sexp_list_item head;

	for (i=0; i<Num_operators; i++)
		if (query_operator_return_type(i) == OPR_POSITIVE)
			head.add_op(i);

	return head.next;
}

sexp_list_item *sexp_tree::get_listing_opf_number()
{
	int i, z;
	sexp_list_item head;

	for (i=0; i<Num_operators; i++) {
		z = query_operator_return_type(i);
		if ((z == OPR_NUMBER) || (z == OPR_POSITIVE))
			head.add_op(i);
	}

	return head.next;
}

sexp_list_item *sexp_tree::get_listing_opf_ship(int parent_node)
{
	object *ptr;
	sexp_list_item head;
	int op = 0, dock_ship = -1, require_cap_ship = 0;

	// look at the parent node and get the operator.  Some ship lists should be filtered based
	// on what the parent operator is
	if ( parent_node >= 0 ) {
		op = find_operator(nodes[parent_node].text);

		// prune out to only capital ships
		if (!stricmp(nodes[parent_node].text, "cap-subsys-cargo-known-delay")) {
			require_cap_ship = 1;
		}

		// get the dock_ship number of if this goal is an ai dock goal.  used to prune out unwanted ships out
		// of the generated ship list
		dock_ship = -1;
		if ( op == OP_AI_DOCK ) {
			int z;

			z = nodes[parent_node].parent;
			Assert(z >= 0);
			Assert(!stricmp(nodes[z].text, "add-ship-goal") || !stricmp(nodes[z].text, "add-wing-goal") || !stricmp(nodes[z].text, "add-goal"));

			z = nodes[z].child;
			Assert(z >= 0);

			dock_ship = ship_name_lookup(nodes[z].text, 1);
			Assert( dock_ship != -1 );
		}
	}

	ptr = GET_FIRST(&obj_used_list);
	while (ptr != END_OF_LIST(&obj_used_list)) {
		if ((ptr->type == OBJ_SHIP) || (ptr->type == OBJ_START)) {
			if ( op == OP_AI_DOCK ) {
				// only include those ships in the list which the given ship can dock with.
				if ( (dock_ship != ptr->instance) && ship_docking_valid(dock_ship , ptr->instance) )
					head.add_data(Ships[ptr->instance].ship_name );

			} else {
				if ( !require_cap_ship || (Ship_info[Ships[ptr->instance].ship_info_index].flags & SIF_HUGE_SHIP) ) {
					head.add_data(Ships[ptr->instance].ship_name);
				}
			}
		}

		ptr = GET_NEXT(ptr);
	}

	return head.next;
}

sexp_list_item *sexp_tree::get_listing_opf_wing()
{
	int i;
	sexp_list_item head;

	for (i=0; i<MAX_WINGS; i++){
		if (Wings[i].wave_count){
			head.add_data(Wings[i].name);
		}
	}

	return head.next;
}

// specific types of subsystems we're looking for
#define OPS_CAP_CARGO		1	
#define OPS_STRENGTH			2
#define OPS_BEAM_TURRET		3
#define OPS_AWACS				4
sexp_list_item *sexp_tree::get_listing_opf_subsystem(int parent_node, int arg_index)
{
	int op, child, sh;
	int special_subsys = 0;
	sexp_list_item head;
	ship_subsys *subsys;

	// determine if the parent is one of the set subsystem strength items.  If so,
	// we want to append the "Hull" name onto the end of the menu
	Assert(parent_node >= 0);	
	
	// get the operator type of the node
	op = find_operator(nodes[parent_node].text);

	// first child node
	child = nodes[parent_node].child;
	Assert(child >= 0);

	switch(op){
	// where we care about hull strength
	case OP_REPAIR_SUBSYSTEM:
	case OP_SABOTAGE_SUBSYSTEM:
	case OP_SET_SUBSYSTEM_STRNGTH:
		special_subsys = OPS_STRENGTH;
		break;

	// awacs subsystems
	case OP_AWACS_SET_RADIUS:
		special_subsys = OPS_AWACS;
		break;

	// where we care about capital ship subsystem cargo
	case OP_CAP_SUBSYS_CARGO_KNOWN_DELAY:
		special_subsys = OPS_CAP_CARGO;
		
		// get the next sibling
		child = nodes[child].next;		
		break;

	// where we care about turrets carrying beam weapons
	case OP_BEAM_FIRE:
		special_subsys = OPS_BEAM_TURRET;

		// if this is arg index 3 (targeted ship)
		if(arg_index == 3){			
			Assert(arg_index == 3);
			child = nodes[child].next;
			Assert(child >= 0);			
			child = nodes[child].next;			
		} else {
			Assert(arg_index == 1);
		}
		break;
	}			

	// now find the ship and add all relevant subsystems
	Assert(child >= 0);
	sh = ship_name_lookup(nodes[child].text, 1);
	if (sh >= 0) {
		subsys = GET_FIRST(&Ships[sh].subsys_list);
		while (subsys != END_OF_LIST(&Ships[sh].subsys_list)) {
			// add stuff
			switch(special_subsys){
			// subsystem cargo
			case OPS_CAP_CARGO:					
				if (valid_cap_subsys_cargo_list(subsys->system_info->subobj_name) ) {
					head.add_data(subsys->system_info->subobj_name);
				}
				break;

			// beam fire
			case OPS_BEAM_TURRET:
				head.add_data(subsys->system_info->subobj_name);
				break;

			// awacs level
			case OPS_AWACS:
				if (subsys->system_info->flags & MSS_FLAG_AWACS) {
					head.add_data(subsys->system_info->subobj_name);
				}
				break;

			// everything else
			default:
				head.add_data(subsys->system_info->subobj_name);
				break;
			}

			// next subsystem
			subsys = GET_NEXT(subsys);
		}
	}
	
	// if one of the subsystem strength operators, append the Hull string
	if(special_subsys == OPS_STRENGTH){
		head.add_data(SEXP_HULL_STRING);
	}

	return head.next;
}

sexp_list_item *sexp_tree::get_listing_opf_point()
{
	char buf[NAME_LENGTH+8];
	int i, j;
	sexp_list_item head;

	for (i=0; i<Num_waypoint_lists; i++)
		for (j=0; j<Waypoint_lists[i].count; j++) {
			sprintf(buf, "%s:%d", Waypoint_lists[i].name, j + 1);
			head.add_data_dup(buf);
		}

	return head.next;
}

sexp_list_item *sexp_tree::get_listing_opf_iff()
{
	int i;
	sexp_list_item head;

	for (i=0; i<Num_team_names; i++)
		head.add_data(Team_names[i]);

	return head.next;
}

sexp_list_item *sexp_tree::get_listing_opf_ai_goal(int parent_node)
{
	int i, n, w, z, child;
	sexp_list_item head;

	Assert(parent_node >= 0);
	child = nodes[parent_node].child;
	Assert(child >= 0);
	n = ship_name_lookup(nodes[child].text, 1);
	if (n >= 0) {
		// add operators if it's an ai-goal and ai-goal is allowed for that ship
		for (i=0; i<Num_operators; i++) {
			if ( (query_operator_return_type(i) == OPR_AI_GOAL) && query_sexp_ai_goal_valid(Operators[i].value, n) )
				head.add_op(i);
		}

	} else {
		z = wing_name_lookup(nodes[child].text);
		if (z >= 0) {
			for (w=0; w<Wings[z].wave_count; w++) {
				n = Wings[z].ship_index[w];
				// add operators if it's an ai-goal and ai-goal is allowed for that ship
				for (i=0; i<Num_operators; i++) {
					if ( (query_operator_return_type(i) == OPR_AI_GOAL) && query_sexp_ai_goal_valid(Operators[i].value, n) )
						head.add_op(i);
				}
			}

		} else
			return NULL;  // no valid ship or wing to check against, make nothing available
	}

	return head.next;
}

sexp_list_item *sexp_tree::get_listing_opf_docker_point(int parent_node)
{
	int i, z, sh;
	sexp_list_item head;

	Assert(parent_node >= 0);
	Assert(!stricmp(nodes[parent_node].text, "ai-dock"));

	z = nodes[parent_node].parent;
	Assert(z >= 0);
	Assert(!stricmp(nodes[z].text, "add-ship-goal") || !stricmp(nodes[z].text, "add-wing-goal") || !stricmp(nodes[z].text, "add-goal"));

	z = nodes[z].child;
	Assert(z >= 0);

	sh = ship_name_lookup(nodes[z].text, 1);
	if (sh >= 0) {
		z = get_docking_list(Ships[sh].modelnum);
		for (i=0; i<z; i++)
			head.add_data(Docking_bay_list[i]);
	}

	return head.next;
}

sexp_list_item *sexp_tree::get_listing_opf_dockee_point(int parent_node)
{
	int i, z, sh;
	sexp_list_item head;

	Assert(parent_node >= 0);
	Assert(!stricmp(nodes[parent_node].text, "ai-dock"));

	z = nodes[parent_node].child;
	Assert(z >= 0);

	sh = ship_name_lookup(nodes[z].text, 1);
	if (sh >= 0) {
		z = get_docking_list(Ships[sh].modelnum);
		for (i=0; i<z; i++)
			head.add_data(Docking_bay_list[i]);
	}

	return head.next;
}

sexp_list_item *sexp_tree::get_listing_opf_message()
{
	char *str;
	int i;
	sexp_list_item head;

	if (m_mode == MODE_EVENTS) {
		Assert(Event_editor_dlg);
		// this for looks a litle strange, but had to do it get rid of a warning.  Conditional
		//uses last statement is sequence, i.e. same as for (i=0, str, i++)
		for (i=0; str = Event_editor_dlg->current_message_name(i), str; i++)
			head.add_data(str);

	} else {
		for (i=Num_builtin_messages; i<Num_messages; i++)
			head.add_data(Messages[i].name);
	}

	return head.next;
}

sexp_list_item *sexp_tree::get_listing_opf_who_from()
{
	object *ptr;
	sexp_list_item head;

	//head.add_data("<any allied>");
	head.add_data("#Command");
	head.add_data("<any wingman>");

	ptr = GET_FIRST(&obj_used_list);
	while (ptr != END_OF_LIST(&obj_used_list)) {
		if ((ptr->type == OBJ_SHIP) || (ptr->type == OBJ_START))
			if (!(Ship_info[Ships[get_ship_from_obj(ptr)].ship_info_index].flags & SIF_NOT_FLYABLE))
				head.add_data(Ships[ptr->instance].ship_name);

		ptr = GET_NEXT(ptr);
	}

	return head.next;
}

sexp_list_item *sexp_tree::get_listing_opf_priority()
{
	sexp_list_item head;

	head.add_data("High");
	head.add_data("Normal");
	head.add_data("Low");
	return head.next;
}

sexp_list_item *sexp_tree::get_listing_opf_waypoint_path()
{
	int i;
	sexp_list_item head;

	for (i=0; i<Num_waypoint_lists; i++)
		head.add_data(Waypoint_lists[i].name);

	return head.next;
}

sexp_list_item *sexp_tree::get_listing_opf_ship_point()
{
	sexp_list_item head;

	head.add_list(get_listing_opf_ship());
	head.add_list(get_listing_opf_point());
	return head.next;
}

sexp_list_item *sexp_tree::get_listing_opf_ship_wing_point()
{
	sexp_list_item head;

	head.add_data("<any friendly>");
	head.add_data("<any hostile>");
	head.add_data("<any neutral>");
	head.add_data("<any unknown>");
	head.add_list(get_listing_opf_ship());
	head.add_list(get_listing_opf_wing());
	head.add_list(get_listing_opf_point());
	return head.next;
}

sexp_list_item *sexp_tree::get_listing_opf_mission_name()
{
	int i;
	sexp_list_item head;

	if ((m_mode == MODE_CAMPAIGN) && (Cur_campaign_mission >= 0)) {
		for (i=0; i<Campaign.num_missions; i++)
			if ( (i == Cur_campaign_mission) || (Campaign.missions[i].level < Campaign.missions[Cur_campaign_mission].level) )
				head.add_data(Campaign.missions[i].name);

	} else
		head.add_data(Mission_filename);

	return head.next;
}

sexp_list_item *sexp_tree::get_listing_opf_goal_name(int parent_node)
{
	int i, m;
	sexp_list_item head;

	if (m_mode == MODE_CAMPAIGN) {
		int child;

		Assert(parent_node >= 0);
		child = nodes[parent_node].child;
		Assert(child >= 0);

		for (m=0; m<Campaign.num_missions; m++)
			if (!stricmp(Campaign.missions[m].name, nodes[child].text))
				break;

		if (m < Campaign.num_missions) {
			if (Campaign.missions[m].num_goals < 0)  // haven't loaded goal names yet.
				read_mission_goal_list(m);

			for (i=0; i<Campaign.missions[m].num_goals; i++)
				head.add_data(Campaign.missions[m].goals[i].name);
		}

	} else {
		for (i=0; i<Num_goals; i++)
			head.add_data(Mission_goals[i].name);
	}

	return head.next;
}

sexp_list_item *sexp_tree::get_listing_opf_ship_wing()
{
	sexp_list_item head;

	head.add_list(get_listing_opf_ship());
	head.add_list(get_listing_opf_wing());
	return head.next;
}

sexp_list_item *sexp_tree::get_listing_opf_ship_type()
{
	int i;
	sexp_list_item head;

	for (i=0; i<MAX_SHIP_TYPE_COUNTS; i++){
		head.add_data(Ship_type_names[i]);
	}

	return head.next;
}

sexp_list_item *sexp_tree::get_listing_opf_keypress()
{
	int i;
	sexp_list_item head;

	for (i=0; i<CCFG_MAX; i++) {
		if (Control_config[i].key_default > 0) {
			head.add_data_dup(textify_scancode(Control_config[i].key_default));
		}
	}

	return head.next;
}

sexp_list_item *sexp_tree::get_listing_opf_event_name(int parent_node)
{
	int i, m;
	sexp_list_item head;


	if (m_mode == MODE_CAMPAIGN) {
		int child;

		Assert(parent_node >= 0);
		child = nodes[parent_node].child;
		Assert(child >= 0);

		for (m=0; m<Campaign.num_missions; m++)
			if (!stricmp(Campaign.missions[m].name, nodes[child].text))
				break;

		if (m < Campaign.num_missions) {
			if (Campaign.missions[m].num_events < 0)  // haven't loaded goal names yet.
				read_mission_goal_list(m);

			for (i=0; i<Campaign.missions[m].num_events; i++)
				head.add_data(Campaign.missions[m].events[i].name);
		}

	} else {
		for (i=0; i<Num_mission_events; i++)
			head.add_data(Mission_events[i].name);
	}

	return head.next;
}

sexp_list_item *sexp_tree::get_listing_opf_ai_order()
{
	int i;
	sexp_list_item head;

	for (i=0; i<Fred_comm_orders_max; i++)
		head.add_data(Fred_comm_orders[i].menu_text);

	return head.next;
}

sexp_list_item *sexp_tree::get_listing_opf_skill_level()
{
	int i;
	sexp_list_item head;

	for (i=0; i<NUM_SKILL_LEVELS; i++)
		head.add_data(Skill_level_names(i, 0));

	return head.next;
}

sexp_list_item *sexp_tree::get_listing_opf_medal_name()
{
	int i;
	sexp_list_item head;

	for (i=0; i<MAX_ASSIGNABLE_MEDALS; i++)
		head.add_data(Medals[i].name);

	// also add SOC crest (index 17) and Wings (index 13)
	head.add_data(Medals[13].name);
	head.add_data(Medals[17].name);

	return head.next;
}

sexp_list_item *sexp_tree::get_listing_opf_weapon_name()
{
	int i;
	sexp_list_item head;

	for (i=0; i<Num_weapon_types; i++)
		head.add_data(Weapon_info[i].name);

	return head.next;
}

sexp_list_item *sexp_tree::get_listing_opf_ship_class_name()
{
	int i;
	sexp_list_item head;

	for (i=0; i<Num_ship_types; i++)
		head.add_data(Ship_info[i].name);

	return head.next;
}

sexp_list_item *sexp_tree::get_listing_opf_hud_gauge_name()
{
	int i;
	sexp_list_item head;

	for (i=0; i<NUM_HUD_GAUGES; i++)
		head.add_data(HUD_gauge_text[i]);

	return head.next;
}

sexp_list_item *sexp_tree::get_listing_opf_huge_weapon()
{
	int i;
	sexp_list_item head;

	for (i=0; i<Num_weapon_types; i++) {
		if (Weapon_info[i].wi_flags & WIF_HUGE)
			head.add_data(Weapon_info[i].name);
	}

	return head.next;
}

sexp_list_item *sexp_tree::get_listing_opf_ship_not_player()
{
	object *ptr;
	sexp_list_item head;

	ptr = GET_FIRST(&obj_used_list);
	while (ptr != END_OF_LIST(&obj_used_list)) {
		if (ptr->type == OBJ_SHIP)
			head.add_data(Ships[ptr->instance].ship_name);

		ptr = GET_NEXT(ptr);
	}

	return head.next;
}

sexp_list_item *sexp_tree::get_listing_opf_jump_nodes()
{
	int i;
	sexp_list_item head;

	for (i = 0; i < Num_jump_nodes; i++ ) 
		head.add_data( Jump_nodes[i].name );

	return head.next;
}

// creates list of Sexp_variables
sexp_list_item *sexp_tree::get_listing_opf_variable_names()
{
	int i;
	sexp_list_item head;

	for (i=0; i<MAX_SEXP_VARIABLES; i++) {
		if (Sexp_variables[i].type & SEXP_VARIABLE_SET) {
			head.add_data( Sexp_variables[i].variable_name );
		}
	}

	return head.next;
}


// Deletes sexp_variable from sexp_tree.
// resets tree to not include given variable, and resets text and type
void sexp_tree::delete_sexp_tree_variable(const char *var_name)
{
	char search_str[64];
	char replace_text[TOKEN_LENGTH];
	
	sprintf(search_str, "%s(", var_name);

	// store old item index
	int old_item_index = item_index;

	for (int idx=0; idx<MAX_SEXP_TREE_SIZE; idx++) {
		if (nodes[idx].type & SEXPT_VARIABLE) {
			if ( strstr(nodes[idx].text, search_str) != NULL ) {

				// check type is number or string
				Assert( (nodes[idx].type & SEXPT_NUMBER) || (nodes[idx].type & SEXPT_STRING) );

				// reset type as not variable
				int type = nodes[idx].type &= ~SEXPT_VARIABLE;

				// reset text
				if (nodes[idx].type & SEXPT_NUMBER) {
					strcpy(replace_text, "number");
				} else {
					strcpy(replace_text, "string");
				}

				// set item_index and replace data
				item_index = idx;
				replace_data(replace_text, type);
			}
		}
	}

	// restore item_index
	item_index = old_item_index;
}


// Modify sexp_tree for a change in sexp_variable (name, type, or default value)
void sexp_tree::modify_sexp_tree_variable(const char *old_name, int sexp_var_index)
{
	char search_str[64];
	int type;

	Assert(Sexp_variables[sexp_var_index].type & SEXP_VARIABLE_SET);
	Assert( (Sexp_variables[sexp_var_index].type & SEXP_VARIABLE_NUMBER) || (Sexp_variables[sexp_var_index].type & SEXP_VARIABLE_STRING) );

	// Get type for sexp_tree node
	if (Sexp_variables[sexp_var_index].type & SEXP_VARIABLE_NUMBER) {
		type = (SEXPT_NUMBER | SEXPT_VALID);
	} else {
		type = (SEXPT_STRING | SEXPT_VALID);
	}
															
	// store item index;
	int old_item_index = item_index;

	// Search string in sexp_tree nodes
	sprintf(search_str, "%s(", old_name);

	for (int idx=0; idx<MAX_SEXP_TREE_SIZE; idx++) {
		if (nodes[idx].type & SEXPT_VARIABLE) {
			if ( strstr(nodes[idx].text, search_str) != NULL ) {
				// temp set item_index
				item_index = idx;

				// replace variable data
				replace_variable_data(sexp_var_index, (type | SEXPT_VARIABLE));
			}
		}
	}

	// restore item_index
	item_index = old_item_index;
}


// convert from item_index to sexp_variable index, -1 if not
int sexp_tree::get_item_index_to_var_index()
{
	// check valid item index and node is a variable
	if ( (item_index > 0) && (nodes[item_index].type & SEXPT_VARIABLE) ) {

		return get_tree_name_to_sexp_variable_index(nodes[item_index].text);
	} else {
		return -1;
	}
}

int sexp_tree::get_tree_name_to_sexp_variable_index(const char *tree_name)
{
	char var_name[TOKEN_LENGTH];

	int chars_to_copy = strcspn(tree_name, "(");
	Assert(chars_to_copy < TOKEN_LENGTH - 1);

	// Copy up to '(' and add null termination
	strncpy(var_name, tree_name, chars_to_copy);
	var_name[chars_to_copy] = '\0';

	// Look up index
	return get_index_sexp_variable_name(var_name);
}

int sexp_tree::get_variable_count(const char *var_name)
{
	int idx;
	int count = 0;
	char compare_name[64];

	// get name to compare
	strcpy(compare_name, var_name);
	strcat(compare_name, "(");

	// look for compare name
	for (idx=0; idx<MAX_SEXP_TREE_SIZE; idx++) {
		if (nodes[idx].type & SEXPT_VARIABLE) {
			if ( strstr(nodes[idx].text, compare_name) ) {
				count++;
			}
		}
	}

	return count;
}