/*
 * Copyright (C) Volition, Inc. 1999.  All rights reserved.
 *
 * All source code herein is the property of Volition, Inc. You may not sell 
 * or otherwise commercially exploit the source or things you created based on the 
 * source.
 *
*/

/*
 * $Logfile: /Freespace2/code/fonttool/FontCreate.cpp $
 * $Revision: 4 $
 * $Date: 1/06/99 2:25p $
 * $Author: Dave $
 *
 * Tool for creating new fonts
 *
 * $Log: /Freespace2/code/fonttool/FontCreate.cpp $
 * 
 * 4     1/06/99 2:25p Dave
 * Stubs and release build fixes.
 * 
 * 3     12/02/98 9:58a Dave
 * Got fonttool working under glide/direct3d.
 * 
 * 2     10/24/98 5:15p Dave
 * 
 * 1     10/24/98 4:58p Dave
 * 
 * 4     10/31/97 10:30a Adam
 * fixed a bug passing wrong pointer to pcx_read trashing memory.
 * 
 * 3     10/30/97 4:56p John
 * Fixed up font stuff to build.  Fixed bug where it didn't show the last
 * 3 characters in kerning table.
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
#include "PcxUtils.h"
#include "Font.h"
#include "BmpMan.h"

#include "FontTool.h"

static bitmap bmp;
static ubyte *data;
static int offset;
static ubyte pal[768];

static ubyte bkg;
static ubyte border;

int num_bad_pixels=0;

static void myexit(int value)
{
//	getch();
	exit(value);
}

ubyte PIX(int x,int y)	
{
	if ( x<0 || x >= bmp.w ) return bkg;
	if ( y<0 || y >= bmp.h ) return bkg;

	return data[x+y*offset];
}

// Attempts to find a box at pixel (x,y) if it can't, then it
// returns 0, else returns 1 and w&h are filled in.
int find_box( int x, int y, int *w, int *h )
{
	int w1, w2, h1, h2;
	int y1,x1,tmp;

	if ( PIX(x,y) != border ) return 0;

	x1 = x;
	y1 = y;

//	printf( "--------- Finding box at %d, %d ----------\n", x1, y1 );

//======================= FIND LEFT EDGE ======================
	y++;
	while ( PIX(x,y)==border )	{
		if ( PIX(x+1,y)==border)	{
			goto LeftSideFound;
		}
		y++;
		if ( y > bmp.h )	{
			printf( "Box at (%d,%d) goes off bottom of screen.\n", x1, y1 );
			myexit(1);
		}
	}
//	printf( "Box at (%d,%d) doesn't have bottom border.\n", x1, y1 );
//	myexit(1);
	return 0;

LeftSideFound:
	h1 = y - y1 - 1;
//	printf( "Has a left height of %d\n", h1 );

//======================= FIND BOTTOM EDGE ======================
	x++;
	while ( PIX(x,y)==border )	{
		if ( PIX(x,y-1)==border)	{
			goto BottomSideFound;
		}
		x++;
		if ( x > bmp.w )	{
			printf( "Box at (%d,%d) goes off left of screen.\n", x1, y1 );
			myexit(1);
		}
	}
	printf( "Box at (%d,%d) doesn't have right border connected to bottom.\n", x1, y1 );
	myexit(1);

BottomSideFound:
	w1 = x - x1 - 1;
//	printf( "Has a bottom width of %d\n", w1 );

//======================= FIND RIGHT EDGE ======================
	tmp = y;
	y--;
	while ( PIX(x,y)==border )	{
		if ( PIX(x-1,y)==border)	{
			goto RightSideFound;
		}
		y--;
		if ( y < 0 )	{
			printf( "Box at (%d,%d) goes off top of screen.\n", x1, y1 );
			myexit(1);
		}
	}
	printf( "Box at (%d,%d) doesn't have top border connected to right border.\n", x1, y1 );
	myexit(1);

RightSideFound:
	h2 = tmp - y - 1;
//	printf( "Has a right height of %d\n", h2 );


//======================= FIND TOP EDGE ======================
	tmp = x;
	x--;
	while ( PIX(x,y)==border )	{
		if ( PIX(x,y+1)==border)	{
			goto TopSideFound;
		}
		x--;
		if ( x < 0 )	{
			printf( "Box at (%d,%d) goes off left of screen.\n", x1, y1 );
			myexit(1);
		}
	}
	printf( "Box at (%d,%d) doesn't have left border connected to top border.\n", x1, y1 );
	myexit(1);

TopSideFound:
	w2 = tmp - x - 1;
//	printf( "Has a top width of %d\n", w2 );

//==================== 
	if ( h1 != h2 )	{
		printf( "Box at (%d,%d) has unequal top/bottom .\n", x1, y1 );
		myexit(1);
	}
	if ( w1 != w2 )	{
		printf( "Box at (%d,%d) has unequal left/right.\n", x1, y1 );
		myexit(1);
	}

	if ( w1 < 1 )	{
		printf( "Box at (%d,%d) is less than 1 pixel wide.\n", x1, y1 );
		myexit(1);
	}
		
	if ( h1 < 1 )	{
		printf( "Box at (%d,%d) is less than 1 pixel tall.\n", x1, y1 );
		myexit(1);
	}

	*w = w1;
	*h = h1;

	return 1;
}



void found_box( font *fnt, int x, int y, int w, int h );

void find_all_boxes(font *fnt)
{
	int x = 0;
	int y = 0;

	data = (ubyte *)bmp.data;
	offset = bmp.w;

	bkg = data[0];
	printf( "Background color = %d\n", bkg );

	for ( y=0; y<bmp.h; y++ )	{
		for ( x=0; x<bmp.w; x++ )	{
			if ( PIX(x,y) != bkg )	{
				border = PIX(x,y);
				goto FoundBorder;
			}
		}
	}
	printf( "Couldn't find anything but background pixels\n" );
	myexit(1);

FoundBorder:
	printf( "Border color = %d, starts at %d,%d\n", border, x, y );

	int w,h;
	int row_height = 0;

	while(1)	{
		if ( find_box( x, y, &w, &h ) )	{
			found_box( fnt, x+1, y+1, w, h );
			x = x + w + 1;
			if ( row_height < 1 )	{
				row_height = h;
			} else {
//		if ( row_height != h )	{
//			printf( "Uneven row height!\n" );
//			myexit(1);
//		}
			}
		} else {
			x++;
			if ( x >= bmp.w )	{
				x = 0;
				if ( row_height )	{
					//printf( "Moving down %d pixels\n", row_height+2);
					y += row_height+2;
					row_height = 0;
				} else {
					y++;
				}
				if ( y >= bmp.h )	{
					break;
				}
			}
		}
	}	
}


void fonttool_create_new( font *fnt )
{
	strncpy( (char *)&fnt->id, "VFNT", 4 );
	fnt->version = FONT_VERSION;
	fnt->num_chars = 0;
	fnt->first_ascii = ' ';
	fnt->w = 0;
	fnt->h = 0;
	fnt->num_kern_pairs = 0;
	fnt->pixel_data = NULL;
	fnt->pixel_data_size = 0;
	fnt->kern_data = NULL;
	fnt->kern_data_size = 0;
	fnt->char_data = NULL;
	fnt->char_data_size = 0;
}
	

void fonttool_add_char( font *fnt, int x1, int y1, int real_w, int h, ubyte *data, int rowsize )
{
	int x, y, n, offset;
	int w;
	
	n = fnt->num_chars;

	w = real_w;
	while ( w & 1)  w++;

	printf( "Adding character %d (%c) from the %dx%d pixels at (%d,%d)\n", n, n + fnt->first_ascii, real_w, h, x1, y1 );

	// add new character data
	font_char * new_char;
	new_char = (font_char *)malloc( fnt->char_data_size + sizeof(font_char) );
	if ( !new_char )	{
		printf( "Not enough memory to create a new character\n" );
		myexit(1);
	}
	if ( fnt->char_data )	{
		memcpy( new_char, fnt->char_data, fnt->char_data_size );
		free(fnt->char_data);
		fnt->char_data = NULL;
	}
	fnt->char_data = new_char;
	fnt->char_data_size += sizeof(font_char);
	new_char = fnt->char_data + fnt->num_chars;
	fnt->num_chars++;

	// add new character pixel data
	ubyte *new_pixel_data = (ubyte *)malloc( fnt->pixel_data_size+w*h );
	if ( !new_pixel_data )	{
		printf( "Not enough memory to create new %dx%d character\n", w, h);
		myexit(1);
	}
	if ( fnt->pixel_data )	{
		memcpy( new_pixel_data, fnt->pixel_data, fnt->pixel_data_size );
		free(fnt->pixel_data);
		fnt->pixel_data = NULL;
	}
	offset = fnt->pixel_data_size;
	fnt->pixel_data_size += w*h;
	fnt->pixel_data = new_pixel_data;
	new_pixel_data = fnt->pixel_data + offset;

	new_char->byte_width = w;
	new_char->spacing = real_w;
	new_char->offset = offset;
	new_char->kerning_entry = -1;
	new_char->user_data = 0;

	for ( y=0; y<h; y++ )	{
		for (x=0; x<w; x++ )	{
			ubyte c;
			if ( x >= real_w)
				c = 0;
			else
				c = data[x+y*rowsize];
			if ( c > 15 ) {
				num_bad_pixels++;
				c = 15;
			}
			*new_pixel_data++ = c;
		}
	}

	if ( fnt->h < 1 )
		fnt->h = h;

	int i, wtotal = 0;

	for (i=0; i<fnt->num_chars; i++ )	{
		wtotal += fnt->char_data[i].spacing;
	}

	fnt->w = wtotal / fnt->num_chars;
	if ( fnt->w < 1 )
		fnt->w = 1;
}


void fonttool_dump( char *filename, font *fnt )
{
	FILE *fp;
	char tmp_name[128], *p;

	strcpy( tmp_name, filename );
	p = strchr( tmp_name, '.' );
	if ( p ) *p = 0;
	strcat( tmp_name, ".vf" );
	
	fp = fopen( tmp_name, "wb" );
	if ( fp == NULL )	{
		printf( "Couldn't open font file '%s' for writing!\n", tmp_name );
		myexit(1);
	}

	fwrite( &fnt->id, 4, 1, fp );
	fwrite( &fnt->version, sizeof(int), 1, fp );
	fwrite( &fnt->num_chars, sizeof(int), 1, fp );
	fwrite( &fnt->first_ascii, sizeof(int), 1, fp );
	fwrite( &fnt->w, sizeof(int), 1, fp );
	fwrite( &fnt->h, sizeof(int), 1, fp );
	fwrite( &fnt->num_kern_pairs, sizeof(int), 1, fp );
	fwrite( &fnt->kern_data_size, sizeof(int), 1, fp );
	fwrite( &fnt->char_data_size, sizeof(int), 1, fp );
	fwrite( &fnt->pixel_data_size, sizeof(int), 1, fp );

	if ( fnt->kern_data_size )	{
		fwrite( fnt->kern_data, fnt->kern_data_size, 1, fp );
	}	
	if ( fnt->char_data_size )	{
		fwrite( fnt->char_data, fnt->char_data_size, 1, fp );
	}	
	if ( fnt->pixel_data_size )	{
		fwrite( fnt->pixel_data, fnt->pixel_data_size, 1, fp );
	}	

	fclose(fp);
}

void fonttool_read( char *filename, font *fnt )
{
	FILE *fp;
	char tmp_name[128], *p;

	strcpy( tmp_name, filename );
	p = strchr( tmp_name, '.' );
	if ( p ) *p = 0;
	strcat( tmp_name, ".vf" );
	
	fp = fopen( tmp_name, "rb" );
	if ( fp == NULL )	{
		printf( "Couldn't open font file '%s' for reading!\n", tmp_name );
		myexit(1);
	}

	fread( &fnt->id, 4, 1, fp );
	fread( &fnt->version, sizeof(int), 1, fp );
	fread( &fnt->num_chars, sizeof(int), 1, fp );
	fread( &fnt->first_ascii, sizeof(int), 1, fp );
	fread( &fnt->w, sizeof(int), 1, fp );
	fread( &fnt->h, sizeof(int), 1, fp );
	fread( &fnt->num_kern_pairs, sizeof(int), 1, fp );
	fread( &fnt->kern_data_size, sizeof(int), 1, fp );
	fread( &fnt->char_data_size, sizeof(int), 1, fp );
	fread( &fnt->pixel_data_size, sizeof(int), 1, fp );

	if ( fnt->kern_data_size )	{
		fnt->kern_data = (font_kernpair *)malloc( fnt->kern_data_size );
		if (!fnt->kern_data)	{
			printf( "Out of memory reading %d bytes of font data from %s\n", tmp_name );
			myexit(1);
		}
		fread( fnt->kern_data, fnt->kern_data_size, 1, fp );
	} else {
		fnt->kern_data = NULL;
	}
	if ( fnt->char_data_size )	{
		fnt->char_data = (font_char *)malloc( fnt->char_data_size );
		if (!fnt->char_data)	{
			printf( "Out of memory reading %d bytes of font data from %s\n", tmp_name );
			myexit(1);
		}
		fread( fnt->char_data, fnt->char_data_size, 1, fp );
	} else {
		fnt->char_data = NULL;
	}
	if ( fnt->pixel_data_size )	{
		fnt->pixel_data = (ubyte *)malloc( fnt->pixel_data_size );
		if (!fnt->pixel_data)	{
			printf( "Out of memory reading %d bytes of font data from %s\n", tmp_name );
			myexit(1);
		}
		fread( fnt->pixel_data, fnt->pixel_data_size, 1, fp );
	} else {
		fnt->pixel_data = NULL;
	}

	fclose(fp);

	// Create a bitmap for hardware cards.
	// JAS:  Try to squeeze this into the smallest square power of two texture.
	// This should probably be done at font generation time, not here.
	int w, h;
	if ( fnt->pixel_data_size < 64*64 )	{
		w = h = 64;
	} else if ( fnt->pixel_data_size < 128*128 )	{
		w = h = 128;
	} else {
		w = h = 256;
	}

	fnt->bm_w = w;
	fnt->bm_h = h;
	fnt->bm_data = (ubyte *)malloc(fnt->bm_w*fnt->bm_h);
	fnt->bm_u = (int *)malloc(sizeof(int)*fnt->num_chars);
	fnt->bm_v = (int *)malloc(sizeof(int)*fnt->num_chars);

	int i,x,y;
	x = y = 0;
	for (i=0; i<fnt->num_chars; i++ )	{
		ubyte * fp;
		int x1, y1;
		fp = &fnt->pixel_data[fnt->char_data[i].offset];
		if ( x + fnt->char_data[i].byte_width >= fnt->bm_w )	{
			x = 0;
			y += fnt->h;
			if ( y+fnt->h > fnt->bm_h ) {
				Error( LOCATION, "Font too big!\n" );
			}
		}
		fnt->bm_u[i] = x;
		fnt->bm_v[i] = y;

		for( y1=0; y1<fnt->h; y1++ )	{
			for (x1=0; x1<fnt->char_data[i].byte_width; x1++ )	{
				uint c = *fp++;
				if ( c > 14 ) c = 14;
				fnt->bm_data[(x+x1)+(y+y1)*fnt->bm_w] = unsigned char(c);	
			}
		}
		x += fnt->char_data[i].byte_width;
	}

	fnt->bitmap_id = bm_create( 8, fnt->bm_w, fnt->bm_h, fnt->bm_data, BMP_AABITMAP );
}

void fonttool_copy_kern( font *src, font *dst )
{
	if ( dst->kern_data )	{
		free( dst->kern_data );
		dst->kern_data = NULL;
	}
	if ( (src->kern_data_size < 1) || (!src->kern_data) )	{
		dst->num_kern_pairs = 0;
		dst->kern_data_size = 0;
		dst->kern_data = NULL;
		fonttool_resync_kerning(dst);
		return;
	}
	dst->kern_data = (font_kernpair *)malloc( src->kern_data_size );
	if (!dst->kern_data)	{
		printf( "Out of memory copying %d bytes of font data.\n" );
		myexit(1);
	}
	memcpy( dst->kern_data, src->kern_data, src->kern_data_size );

	dst->kern_data_size  = src->kern_data_size;
	dst->num_kern_pairs = src->num_kern_pairs;
	fonttool_resync_kerning(dst);
}


void found_box( font *fnt, int x, int y, int w, int h )
{
	fonttool_add_char( fnt, x, y, w, h, &data[x+y*offset], offset );
}


void fonttool_create_font(char *pcx_filename, char *font_filename)
{
	font fnt1, fnt2;
	printf( "Creating font file from '%s' \n", pcx_filename );
	if ( font_filename )	{
	}
		
	int w, h;
	int pcx_error = pcx_read_header( pcx_filename, &w, &h, NULL );
	if ( pcx_error != PCX_ERROR_NONE )	{
		printf( "Error reading PCX file, '%s'\n", pcx_filename );
		myexit(1);
	}	
	
	bmp.w = (short)w;
	bmp.h = (short)h;
	bmp.data = (uint)malloc( w*h + 768 );
	bmp.palette = (ubyte *)(bmp.data +w*h );
	if ( !bmp.data )	{
		printf( "Error mallocing PCX data, '%s'\n", pcx_filename );
		myexit(1);
	}

	pcx_error = pcx_read_bitmap_8bpp( pcx_filename, (ubyte *)bmp.data, pal );
	if ( pcx_error != PCX_ERROR_NONE )	{
		printf( "Error reading PCX file, '%s'\n", pcx_filename );
		myexit(1);
	}	

	fonttool_create_new( &fnt1 );

	find_all_boxes(&fnt1);

	if (font_filename)	{
		printf( "Using kern data from font '%s'\n", font_filename );
		fonttool_read( font_filename, &fnt2 );
		fonttool_copy_kern( &fnt2, &fnt1 );
	}

	printf( "\nFont is, on average, %dx%d and has %d characters, %d kerning pairs.\n", fnt1.w, fnt1.h, fnt1.num_chars, fnt1.num_kern_pairs );
	if ( num_bad_pixels > 0 )
		printf( "It had %d bad pixel(s) in it.\n(Bad means the pixel index was greater than 15).\n" , num_bad_pixels );
	
	fonttool_dump( pcx_filename, &fnt1 );

	myexit(0);
}

