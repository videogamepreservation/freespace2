/*
 * Copyright (C) Volition, Inc. 1999.  All rights reserved.
 *
 * All source code herein is the property of Volition, Inc. You may not sell 
 * or otherwise commercially exploit the source or things you created based on the 
 * source.
 *
*/

/*
 * $Logfile: /Freespace2/code/nebedit/Nebstubs.cpp $
 * $Revision: 5 $
 * $Date: 5/19/99 4:07p $
 * $Author: Dave $
 *
 * $Log: /Freespace2/code/nebedit/Nebstubs.cpp $ 
 * 
 * 5     5/19/99 4:07p Dave
 * Moved versioning code into a nice isolated common place. Fixed up
 * updating code on the pxo screen. Fixed several stub problems.
 * 
 * 4     4/07/99 6:22p Dave
 * Fred and Freespace support for multiple background bitmaps and suns.
 * Fixed link errors on all subprojects. Moved encrypt_init() to
 * cfile_init() and lcl_init(), since its safe to call twice.
 * 
 * 3     1/06/99 2:26p Dave
 * Stubs and release build fixes.
 * 
 * 2     10/24/98 11:46p Dave
 * 
 * 1     10/24/98 11:45p Dave
 * 
 * 2     10/24/98 9:51p Dave
 * 
 *
 * $NoKeywords: $
 */

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
int game_start_mission(void){return 0;}
void game_level_close(){}
void game_flash(float, float, float){}
void game_whack_apply(float, float){}
int game_do_cd_check(char*){return 0;}
struct fs_builtin_mission *game_find_builtin_mission(char*){return 0;}
int Game_do_state_should_skip;
int Show_target_weapons;
int Show_target_debug_info;
int Sun_drew;
int Game_subspace_effect;
void game_load_palette(){}
void game_format_time(long, char*){}
float Freespace_gamma;
void get_version_string(char*){}
int game_get_default_skill_level(){return 0;}
int game_cd_changed(){return 0;}
void game_set_view_clip(){}
float Viewer_zoom;
int Interface_framerate;
int Game_weapons_tbl_valid;
int Game_ships_tbl_valid;
void game_shudder_apply(int, float){}
int Debug_octant;
int game_hacked_data(){return 0;}
int game_do_cd_mission_check(char*){return 0;}
int Player_multi_died_check;
void game_tst_mark(struct object*, struct ship*){}
int tst;
int game_single_step;
int last_single_step;