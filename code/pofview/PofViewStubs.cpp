/*
 * Copyright (C) Volition, Inc. 1999.  All rights reserved.
 *
 * All source code herein is the property of Volition, Inc. You may not sell 
 * or otherwise commercially exploit the source or things you created based on the 
 * source.
 *
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

#include "OutWnd.h"
#include "key.h"
#include "2d.h"

int game_cd_changed()
{
	return 0;
}

int rtvoice_stream_data(uint, uint, uint )
{
	return 0;
}

int Fred_running = 0;


void demo_set_playback_filter()
{
}


void os_close()
{
}

int game_check_key()
{
	return key_inkey();
}

int game_poll()
{
	return key_inkey();
}

int game_hacked_data()
{
	return 0;
}

int Font1 = -1;

void freespace_menu_background()
{
	gr_reset_clip();
	gr_clear();
}

void game_enter_state(int, int){}
void game_leave_state(int, int){}
void game_do_state(int){}
void game_process_event(int, int){}
char *Game_CDROM_dir;
void game_stop_looped_sounds(){}
int set_cdrom_path(int){return 0;}
int find_freespace_cd(char*){return 0;}
void game_flush(){}
int Game_skill_level;
void game_stop_time(){}
void game_start_time(){}
void game_do_state_common(int, int){}
void game_set_frametime(int){}
void game_increase_skill_level(){}
int Test_begin;
long Game_time_compression;
int Framerate_delay;
char *Game_current_mission_filename;
int Warpout_forced;
float Warpout_time;
int game_start_mission(){return 0;}
void game_level_close(){}
void game_whack_apply(float, float){}
void game_flash(float, float, float){}
int game_do_cd_check(char *){return 0;}
struct fs_builtin_mission *game_find_builtin_mission(char*){return 0;}
int Show_target_weapons;
int Show_target_debug_info;
int Sun_drew;
int Game_subspace_effect;
void game_load_palette(){}
void game_format_time(long, char*){}
int game_get_default_skill_level(){return 0;}
float Freespace_gamma;
void get_version_string(char*){}
int Game_do_state_should_skip;
vector Camera_pos;
vector Dead_player_last_vel;
void game_set_view_clip(){}
float Viewer_zoom;
int Interface_framerate;
int Game_weapons_tbl_valid;
int Game_ships_tbl_valid;
int Debug_octant;
void game_shudder_apply(int, float){}
int game_single_step;
int last_single_step;
void game_tst_mark(struct object*, struct ship*){}
int tst;
int game_do_cd_mission_check(char*){return 0;}
int Player_multi_died_check;
int Nebedit_running = 0;