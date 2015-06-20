/*
 * Copyright (C) Volition, Inc. 1999.  All rights reserved.
 *
 * All source code herein is the property of Volition, Inc. You may not sell 
 * or otherwise commercially exploit the source or things you created based on the 
 * source.
 *
*/

/*
 * $Logfile: /Freespace2/code/Fonttool/FontKernCopy.cpp $
 * $Revision: 2 $
 * $Date: 10/24/98 5:15p $
 * $Author: Dave $
 *
 * Tool for copying font kerning info
 *
 * $Log: /Freespace2/code/Fonttool/FontKernCopy.cpp $
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

font fnt1, fnt2;

void fonttool_kerning_copy( char *fname1, char *fname2 )
{
	printf( "Copying kerning data from %s to %s\n", fname1, fname2 );

	fonttool_read( fname1, &fnt1 );
	fonttool_read( fname2, &fnt2 );
	fonttool_copy_kern( &fnt1, &fnt2 );

	fonttool_dump( fname2, &fnt2 );

	exit(0);
}

