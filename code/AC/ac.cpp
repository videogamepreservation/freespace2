/*
 * Copyright (C) Volition, Inc. 1999.  All rights reserved.
 *
 * All source code herein is the property of Volition, Inc. You may not sell 
 * or otherwise commercially exploit the source or things you created based on the 
 * source.
 *
*/ 

/*
 * $Logfile: /Freespace2/code/AC/ac.cpp $
 * $Revision: 2 $
 * $Date: 10/23/98 6:03p $
 * $Author: Dave $
 *
 * C module for console version of anim converter
 *
 * $Log: /Freespace2/code/AC/ac.cpp $
 * 
 * 2     10/23/98 6:03p Dave
 * 
 * 12    6/24/98 10:43a Hoffoss
 * Changed default to 15 FPS instead of 30 FPS.
 * 
 * 11    6/23/98 4:18p Hoffoss
 * Fixed some bugs with AC release build.
 * 
 * 10    7/20/97 6:59p Lawrance
 * added new -i and -x switches
 * 
 * 9     5/21/97 11:06a Lawrance
 * enabling a user-defined transparent value
 * 
 * 8     5/19/97 3:21p Lawrance
 * add fps parm, version num to anim header
 * 
 * 7     2/25/97 5:18p Lawrance
 * add carriage return after finished, so DOS prompt at a new line
 * 
 * 6     2/20/97 3:03p Lawrance
 * initialize force_key_frame global to -1
 * 
 * 5     2/20/97 1:59p Lawrance
 * sourcesafe sucks
 * 
 * 4     2/20/97 1:58p Adam
 * 
 * 2     2/19/97 9:26p Lawrance
 * console version of converter working
 * 
 * 1     2/19/97 7:26p Lawrance
 *
 * $NoKeywords: $
 */

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "convert.h"
#include "ac.h"
#include "AnimPlay.h"
#include "PackUnpack.h"

#ifdef NDEBUG
char *help_text = "AC ANI Converter Copyright (C) 1998, Volition, Inc.  All Rights Reserved.\n"
						"For exclusive use in FreeSpace missions only.\n\n"
						"Usage: ac [-fps n] [-v] filename\n\n" \
						"-i     => display information and statistics about the ani file\n" \
						"-x     => extract pcx files from ani (named filename0000.pcx etc)\n" \
                  "-fps n => n frames per second (default 15)\n" \
						"-v     => display the version number\n" \
						"filename => a Microsoft RLE AVI || PCX file in form nameXXXX.pcx\n\n" \
						"Examples:\n" \
						"ac test.avi => converts test.avi to test.ani\n" \
						"ac test0000.pcx => converts test0000.pcx up to highest testxxxx.pcx to test.ani\n";

#else
char *help_text = "Usage: ac [-c n] [-k n] [-ke n] [-fps n] [-to] [-v] filename\n\n" \
						"-c   n => which kind of compression to use (default is 1):\n" \
						"     -c 0 => compression using up to 255 count, takes 3 bytes for a run\n" \
						"     -c 1 => compression using up to 127 count, takes 2 bytes for a run\n" \
						"-i     => display information and statistics about the ani file\n" \
						"-x     => extract pcx files from ani (named filename0000.pcx etc)\n" \
						"-k   n => keyframe at frame n\n" \
                  "-ke  n => keyframe every n frames\n" \
                  "-fps n => n frames per second (default 15)\n" \
                  "-to    => transparent override.  Use pixel in top-left corner of first frame as transparent color.  Otherwise RGB value 0.255.0 is used.\n" \
						"-v     => display the version number\n" \
						"filename => a Microsoft RLE AVI || PCX file in form nameXXXX.pcx\n\n" \
						"Examples:\n" \
						"ac test.avi => converts test.avi to test.ani with no keyframes\n" \
						"ac -k 10 test.avi => converts test.avi to test.ani with keyframe at 10th frame\n" \
						"ac -ke 10 test.avi => every 10th frame (frame 1, 10, 20 etc) is a keyframe\n" \
						"ac test0000.pcx => converts test0000.pcx up to highest testxxxx.pcx to test.ani\n"\
						"ac -k 10 test0000.pcx => same as above, but test009.pcx is a keyframe\n" \
						"ac -ke 5 test0000.pcx => makes test0004.pcx, test0009.pcx, etc a keyframe\n";
#endif

// Global to file
static char buffer[255];

// Internal function prototypes
void ac_error(char *msg);
void start_convert_with(char* filename);

int main(int argc, char *argv[])
{
	int i;

	key_frame_rate = 0;		// assume no regular keyframes
	force_key_frame = -1;	// assume no force key frame

	Default_fps = ANIM_DEFAULT_FPS;	// assume default fps value
	Use_custom_xparent_color = 0;		// assume xparent RGB is 0.255.0

	Compression_type = CUSTOM_DELTA_RLE;

	vm_init(16*1024*1024);

	if ( argc <= 1 ) {
		printf(help_text);
		exit(0);
	}

	for ( i = 1; i < argc; i++ ) {
		if ( !stricmp(argv[i], "-h" ) ) {
			printf(help_text);
			exit(0);

#ifndef NDEBUG
		} else if ( !stricmp(argv[i], "-c" ) ) {
			int mode;
			if ( i+1 >= argc ) ac_error("-c switch requires a parameter\n");
			mode = atoi(argv[i+1]);
			i++;
			switch ( mode ) {
				case 0:
					Compression_type = CUSTOM_DELTA_RLE;
					break;
				case 1:
					Compression_type = STD_DELTA_RLE;
					break;
				default:
					ac_error("-c only supports compression types 0 and 1\n");
					break;
			}	// end switch

		} else if ( !stricmp(argv[i], "-k" ) ) {
			if ( i+1 >= argc ) ac_error("-k switch requires a parameter\n");
			force_key_frame = atoi(argv[i+1]);
			i++;

		} else if ( !stricmp(argv[i], "-ke" ) ) {
			if ( i+1 >= argc ) ac_error("-ke switch requires a parameter\n");
			key_frame_rate = atoi(argv[i+1]);
			i++;

		} else if ( !stricmp(argv[i], "-to" ) ) {
			Use_custom_xparent_color = 1;
#endif

		} else if ( !stricmp(argv[i], "-fps" ) ) {
			if ( i+1 >= argc ) ac_error("-fps switch requires a parameter\n");
			Default_fps = atoi(argv[i+1]);
			i++;

		} else if ( !stricmp(argv[i], "-v" ) ) {
			printf("AC version: %.2f\n", float(ANIM_VERSION));

		} else if ( !stricmp(argv[i], "-i" ) ) {
			if ( i+1 >= argc ) ac_error("-i switch requires filename of ani\n");
			anim_display_info(argv[i+1]);
			exit(0);

		} else if ( !stricmp(argv[i], "-x" ) ) {
			if ( i+1 >= argc ) ac_error("-x switch requires filename of ani\n");
			anim_write_frames_out(argv[i+1]);
			exit(0);

		} else {
			start_convert_with(argv[i]);
		}

	}

	return 0;
}

void ac_error(char *msg)
{
	fprintf(stderr, msg);
	exit(1);
}


void start_convert_with(char* filename)
{
	char *extension;
	int rc;

	if (strlen(filename) < 4 || filename[strlen(filename) - 4] != '.')
		ac_error("Extension must be specified for file to convert");

	extension = filename + strlen(filename) - 3;
	if (!stricmp(extension, "avi")) {
		if ( key_frame_rate > 0 )
			key_frame_rate--;
		rc = convert_avi_to_anim(filename);
		if (rc) {
			sprintf(buffer,"Could not convert %s to ani format\n", filename);
			ac_error(buffer);
		}
	}
	else if (!stricmp(extension, "pcx")) {
		rc = convert_frames_to_anim(filename);
		if (rc) {
			sprintf(buffer,"Could not convert %s to ani format\n", filename);
			ac_error(buffer);
		}
	}
	else
		ac_error("Type of file to convert is not supported");
}