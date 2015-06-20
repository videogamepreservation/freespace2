/*
 * Copyright (C) Volition, Inc. 1999.  All rights reserved.
 *
 * All source code herein is the property of Volition, Inc. You may not sell 
 * or otherwise commercially exploit the source or things you created based on the 
 * source.
 *
*/

#ifndef _EDITOR_H
#define _EDITOR_H

/*
#ifdef __cplusplus
extern "C" {
#endif
*/

#include "physics.h"
#include "3d.h"
#include "MissionGrid.h"

#define	MAX_GRID_POINTS		1000

void create_object(int objnum, vector *pos);

//	This stuff properly belongs in editor.h, but I gave up trying to figure out how
//	to add an include file to the project.

extern void test_form_wing(int x);

extern int	select_object(int cx, int cy);
extern void game_init();

extern matrix	Grid_gmatrix;
extern vector	Grid_center;

extern int	Show_stars;
extern void rpd_line(vector *v0, vector *v1);


/*
#ifdef __cplusplus
}
#endif
*/

#endif