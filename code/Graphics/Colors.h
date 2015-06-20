/*
 * Copyright (C) Volition, Inc. 1999.  All rights reserved.
 *
 * All source code herein is the property of Volition, Inc. You may not sell 
 * or otherwise commercially exploit the source or things you created based on the 
 * source.
 *
*/ 

/*
 * $Logfile: /Freespace2/code/Graphics/Colors.h $
 * $Revision: 5 $
 * $Date: 1/14/99 12:48a $
 * $Author: Dave $
 *
 * Functions to deal with colors & alphacolors
 *
 * $Log: /Freespace2/code/Graphics/Colors.h $
 * 
 * 5     1/14/99 12:48a Dave
 * Todo list bug fixes. Made a pass at putting briefing icons back into
 * FRED. Sort of works :(
 * 
 * 4     11/30/98 5:31p Dave
 * Fixed up Fred support for software mode.
 * 
 * 3     11/30/98 1:07p Dave
 * 16 bit conversion, first run.
 * 
 * 2     10/07/98 10:52a Dave
 * Initial checkin.
 * 
 * 1     10/07/98 10:49a Dave
 * 
 * 2     2/07/98 7:50p John
 * Added code so that we can use the old blending type of alphacolors if
 * we want to.  Made the stars use them.
 * 
 * 1     6/17/97 12:01p John
 *
 * $NoKeywords: $
 */

#ifndef _COLORS_H
#define _COLORS_H

struct alphacolor_old;

void grx_init_alphacolors();
void grx_init_color( color *clr, int r, int g, int b );
void grx_init_alphacolor( color *clr, int r, int g, int b, int alpha, int type );
void grx_set_color( int r, int g, int b );
void grx_set_color_fast( color *clr );
void grx_get_color( int *r, int *g, int *b );

void calc_alphacolor_old(alphacolor_old *ac);

#endif
