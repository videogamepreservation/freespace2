/*
 * Copyright (C) Volition, Inc. 1999.  All rights reserved.
 *
 * All source code herein is the property of Volition, Inc. You may not sell 
 * or otherwise commercially exploit the source or things you created based on the 
 * source.
 *
*/ 

/*
 * $Logfile: /Freespace2/code/ac/ac_stubs.cpp $
 * $Revision: 7 $
 * $Date: 6/21/99 10:24a $
 * $Author: Andsager $
 *
 * Stubs to allow compiling of AC project
 *
 * $Log: /Freespace2/code/ac/ac_stubs.cpp $
 * 
 * 7     6/21/99 10:24a Andsager
 * Fix stubs.
 * 
 * 6     3/19/99 9:52a Dave
 * Checkin to repair massive source safe crash. Also added support for
 * pof-style nebulae, and some new weapons code.
 * 
 * 5     2/17/99 2:17p Dave
 * a few new stubs
 * 
 * 4     1/08/99 2:08p Dave
 * Fixed software mode for pofview.
 * 
 * 3     1/06/99 2:24p Dave
 * Stub fixes.
 * 
 * 2     10/23/98 6:03p Dave
 * 
 * 1     10/23/98 5:04p Dave
 * 
 * 1     10/23/98 4:32p Dave
 * 
 * 6     6/23/98 2:52p Hoffoss
 * Changed code so AC compiles once again.
 * 
 * 5     7/20/97 6:59p Lawrance
 * added new -i and -x switches
 * 
 * 4     5/19/97 3:21p Lawrance
 * add fps parm, version num to anim header
 * 
 * 3     4/18/97 9:20a Lawrance
 * added os_force_windowed() stub
 * 
 * 2     2/19/97 9:26p Lawrance
 * console version of converter working
 *
 * $NoKeywords: $
 */

#include "pstypes.h"

struct bitmap;

void gr_palette_load(unsigned char*)
{
}

void os_force_windowed()
{
}

void gr_set_palette(char *, unsigned char *)
{
}

int tga_read_bitmap( char *, bitmap *) { return 0; };
int tga_read_header(char *, bitmap *, unsigned char *) { return 0; }
long	fixdiv(long, long) { return 0; }
int game_cd_changed() { return 0; }
int Font1;
void freespace_menu_background() {}
int Fred_running;
int Pofview_running = 0;
char *Game_CDROM_dir;
void game_stop_looped_sounds() {}
void game_enter_state(int, int){}
void game_leave_state(int, int){}
void game_do_state(int){}
int set_cdrom_path(int){return 0;}
int find_freespace_cd(char*){return 0;}
void game_flush(){}
void game_process_event(int, int);
int Game_skill_level;
float flFrametime;
int game_check_key(){return 0;}
void game_stop_time(){}
void game_do_state_common(int, int){}
void game_start_time(){}
void game_set_frametime(int){}
int Test_begin;
long Game_time_compression;
int Framerate_delay;
int game_poll() {return 0;}
char *Game_current_mission_filename;
void game_process_event(int, int){}
void game_increase_skill_level(){}
int Warpout_forced;
float Warpout_time;
int game_start_mission(){return 0;}
void game_level_close(){}
void game_whack_apply(float, float){}
void game_flash(float, float, float){}
int game_do_cd_check(char*){return 0;}
struct fs_builtin_mission *game_find_builtin_mission(char*){return 0;}
int Game_do_state_should_skip;
int Show_target_weapons;
int Show_target_debug_info;
int Game_subspace_effect;
void game_load_palette(){}
void game_format_time(long, char*){}
int game_get_default_skill_level(){return 0;}
float Freespace_gamma;
void get_version_string(char*){}
int Sun_drew;
int Interface_framerate;
void game_set_view_clip(){}
float Viewer_zoom;
int Game_weapons_tbl_valid;
int Game_ships_tbl_valid;
vector Camera_pos;
vector Dead_player_last_vel;
int Debug_octant;
void game_shudder_apply(int, float){}
int game_hacked_data() {return 0;}
int game_single_step;
int last_single_step;
int Nebedit_running;
void game_tst_mark(struct object*, struct ship*){}
int game_do_cd_mission_check(char*){return 0;}
int Player_multi_died_check;
int tst;