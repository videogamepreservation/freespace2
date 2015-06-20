/*
 * Copyright (C) Volition, Inc. 1999.  All rights reserved.
 *
 * All source code herein is the property of Volition, Inc. You may not sell 
 * or otherwise commercially exploit the source or things you created based on the 
 * source.
 *
*/

/*
 * $Logfile: /Freespace2/code/Fonttool/FontTool.cpp $
 * $Revision: 2 $
 * $Date: 10/24/98 5:15p $
 * $Author: Dave $
 *
 * Tool for creating/kerning fonts
 *
 * $Log: /Freespace2/code/Fonttool/FontTool.cpp $
 * 
 * 2     10/24/98 5:15p Dave
 * 
 * 1     10/24/98 4:58p Dave
 * 
 * 4     10/30/97 4:56p John
 * Fixed up font stuff to build.  Fixed bug where it didn't show the last
 * 3 characters in kerning table.
 * 
 * 3     6/23/97 6:05p Hoffoss
 * Added stubbs to fix linking errors.
 * 
 * 2     6/05/97 4:53p John
 * First rev of new antialiased font stuff.
 * 
 * 1     6/02/97 4:04p John
 *
 * $NoKeywords: $
 */

#include <stdlib.h>
#include <stdlib.h>
#include <stdio.h>
#include <io.h>
#include <conio.h>

#include "PsTypes.h"
#include "OsApi.h"
#include "Cfile.h"
#include "2d.h"
#include "key.h"
#include "mouse.h"
#include "PalMan.h"
#include "timer.h"

#include "FontTool.h"

char Usage[] = "Usage:\n"	\
"\nFontTool x.pcx [y.vf]\n" \
"\n  If you specify a PCX file, then a font will be\n" \
"  created with the same base name.   If you also\n" \
"  specify a font file, then it will use the kerning\n" \
"  data from that font file when it creates the new\n" \
"  font from the PCX file.\n" \
"\nFontTool x.vf\n" \
"\n  If you specify a font file by itself then it will\n" \
"  allow you to interactively kern that font.\n" \
"\nFontTool x.vf y.vf\n" \
"\n  If you specify two font files, then the kerning\n" \
"  data from the first font will be copied into the\n" \
"  second font.\n" \
"\n";

#define NONE 0
#define PCX 1
#define FONT 2

int Font1 = -1;

void demo_set_playback_filter() {}
float flFrametime = 0.0f;

void freespace_menu_background()
{
	gr_reset_clip();
	gr_clear();
}

int main(int argc, char *argv[] )
{
	int t1, t2;

	t1 = NONE;
	t2 = NONE;

	if ( (argc < 1) || (argc>3) )	{
		printf( Usage );
		return 1;
	}

	if ( argc > 1 )	{
		strlwr( argv[1] );

		if ( strstr( argv[1], ".pcx" ) )
			t1 = PCX;
		else if ( strstr( argv[1], ".vf" ) )
			t1 = FONT;
	}

	if ( argc > 2 )	{
		strlwr( argv[2] );

		if ( strstr( argv[2], ".pcx" ) )
			t2 = PCX;
		else if ( strstr( argv[2], ".vf" ) )
			t2 = FONT;
	}

	if ( (t1==PCX) && (t2==NONE) )
		fonttool_create_font( argv[1], NULL );
	else if ( (t1==PCX) && (t2==FONT) )
		fonttool_create_font( argv[1], argv[2] );
	else if ( (t1==FONT) && (t2==NONE) )
		fonttool_edit_kerning( argv[1] );
	else if ( (t1==FONT) && (t2==FONT) )
		fonttool_kerning_copy( argv[1], argv[2] );
	else
		printf( Usage );

	return 0;
}
