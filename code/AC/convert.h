/*
 * Copyright (C) Volition, Inc. 1999.  All rights reserved.
 *
 * All source code herein is the property of Volition, Inc. You may not sell 
 * or otherwise commercially exploit the source or things you created based on the 
 * source.
 *
*/ 

/*
 * $Logfile: /Freespace2/code/AC/convert.h $
 * $Revision: 2 $
 * $Date: 10/23/98 6:03p $
 * $Author: Dave $
 *
 * Header file for the conversion of standard animation files to our own ANIM format
 *
 * $Log: /Freespace2/code/AC/convert.h $
 * 
 * 2     10/23/98 6:03p Dave
 * 
 * 1     10/23/98 5:34p Dave
 * 
 * 2     10/07/98 10:52a Dave
 * Initial checkin.
 * 
 * 1     10/07/98 10:48a Dave
 * 
 * 7     6/24/98 10:43a Hoffoss
 * Changed default to 15 FPS instead of 30 FPS.
 * 
 * 6     4/10/98 5:20p John
 * Changed RGB in lighting structure to be ubytes.  Removed old
 * not-necessary 24 bpp software stuff.
 * 
 * 5     7/20/97 6:58p Lawrance
 * supporting new RLE format
 * 
 * 4     5/21/97 11:06a Lawrance
 * enabling a user-defined transparent value
 * 
 * 3     5/19/97 3:21p Lawrance
 * add fps parm, version num to anim header
 * 
 * 2     2/19/97 9:26p Lawrance
 * added force_key_frame global
 * 
 * 1     2/19/97 7:14p Lawrance
 * 
 * 5     2/17/97 3:02p Hoffoss
 * Added headers to files, and implemented key frame dialog stuff.
 * 
 * 4     2/14/97 7:33p Lawrance
 * added convert_avi_to_anim() function
 * 
 * 3     2/14/97 3:28p Hoffoss
 * Wrote functions to save an anim file.
 * 
 * 2     2/13/97 5:55p Lawrance
 * reading AVI / decompressing AVI functions in
 *
 * $NoKeywords: $
 */

#include "pstypes.h"

#ifndef __CONVERT_H__
#define __CONVERT_H__

// !!IMPORTANT!!
// ANIM_HEADER_SIZE is the size (in bytes) of the header.  If the header format changes, you
// must update this number.
#define ANIM_HEADER_SIZE	790

#define ANIM_BUFFER_MAX 400000
#define ANIM_VERSION		2				// update this when save format changes

#define ANIM_DEFAULT_FPS	15

// specify the different types of compression that can be used (Compression_type is assigned one of these values)
#define	CUSTOM_DELTA_RLE	0
#define	STD_DELTA_RLE		1

int convert_avi_to_anim(char* filename);
int convert_frames_to_anim(char *filename);

typedef struct rgb_triple {
	ubyte	r, g, b;
} rgb_triple;

extern int			key_frame_rate;
extern int			force_key_frame;
extern int			Default_fps;
extern rgb_triple	Xparent_color;
extern int			Use_custom_xparent_color;
extern int			Compression_type;


#endif /* __CONVERT_H__ */