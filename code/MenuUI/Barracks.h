/*
 * Copyright (C) Volition, Inc. 1999.  All rights reserved.
 *
 * All source code herein is the property of Volition, Inc. You may not sell 
 * or otherwise commercially exploit the source or things you created based on the 
 * source.
 *
*/ 

/*
 * $Logfile: /Freespace2/code/MenuUI/Barracks.h $
 * $Revision: 3 $
 * $Date: 2/02/99 11:58a $
 * $Author: Neilk $
 *
 * C source file for implementing barracks
 *
 * $Log: /Freespace2/code/MenuUI/Barracks.h $
 * 
 * 3     2/02/99 11:58a Neilk
 * added vss revision/log comments
 *
 * $NoKeywords: $
 */

#ifndef _BARRACKS_H
#define _BARRACKS_H

// initialize the barracks 
void barracks_init();

// do a frame for the barrracks
void barracks_do_frame(float frametime);

// close the barracks
void barracks_close();

#endif // _BARRACKS_H