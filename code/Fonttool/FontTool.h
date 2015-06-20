/*
 * Copyright (C) Volition, Inc. 1999.  All rights reserved.
 *
 * All source code herein is the property of Volition, Inc. You may not sell 
 * or otherwise commercially exploit the source or things you created based on the 
 * source.
 *
*/

/*
 * $Logfile: /Freespace2/code/Fonttool/FontTool.h $
 * $Revision: 2 $
 * $Date: 10/24/98 5:15p $
 * $Author: Dave $
 *
 * Include file for font creating/kerning tools
 *
 * $Log: /Freespace2/code/Fonttool/FontTool.h $
 * 
 * 2     10/24/98 5:15p Dave
 * 
 * 1     10/24/98 4:58p Dave
 * 
 * 2     6/05/97 4:53p John
 * First rev of new antialiased font stuff.
 * 
 * 1     6/02/97 4:04p John
 *
 * $NoKeywords: $
 */

#ifndef _FONTTOOL_H
#define _FONTTOOL_H

#include "2d.h"
#include "font.h"

void fonttool_edit_kerning(char *fname1);
void fonttool_kerning_copy( char *fname1, char *fname2 );
void fonttool_create_font(char *pcx_filename, char *font_filename);

void fonttool_read( char *fname2, font *fnt2 );
void fonttool_copy_kern( font *fnt1, font *fnt2 );
void fonttool_dump( char *fname1, font *fnt1 );
void fonttool_remove_kerning( font *fnt );
void fonttool_resync_kerning(font *fnt);


#endif
