/*
 * Copyright (C) Volition, Inc. 1999.  All rights reserved.
 *
 * All source code herein is the property of Volition, Inc. You may not sell 
 * or otherwise commercially exploit the source or things you created based on the 
 * source.
 *
*/ 

/*
 * $Logfile: /Freespace2/code/Graphics/GrDirectDraw.h $
 * $Revision: 2 $
 * $Date: 10/07/98 10:52a $
 * $Author: Dave $
 *
 * Include file for software 8-bpp rendering using DirectDraw
 *
 * $Log: /Freespace2/code/Graphics/GrDirectDraw.h $
 * 
 * 2     10/07/98 10:52a Dave
 * Initial checkin.
 * 
 * 1     10/07/98 10:49a Dave
 * 
 * 1     3/25/98 8:07p John
 * Split software renderer into Win32 and DirectX
 *
 * $NoKeywords: $
 */


#ifndef _GRDIRECTDRAW_H
#define _GRDIRECTDRAW_H

void gr_directdraw_init();
void gr_directdraw_cleanup();

#endif //_GRDIRECTDRAW_H
