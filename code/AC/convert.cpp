/*
 * Copyright (C) Volition, Inc. 1999.  All rights reserved.
 *
 * All source code herein is the property of Volition, Inc. You may not sell 
 * or otherwise commercially exploit the source or things you created based on the 
 * source.
 *
*/ 

/*
 * $Logfile: /Freespace2/code/AC/convert.cpp $
 * $Revision: 2 $
 * $Date: 10/23/98 6:03p $
 * $Author: Dave $
 *
 * C module for the conversion of standard animation files to our own ANIM format.
 * This is where all the real code for this application is located really.
 *
 * $Log: /Freespace2/code/AC/convert.cpp $
 * 
 * 2     10/23/98 6:03p Dave
 * 
 * 1     10/23/98 5:34p Dave
 * 
 * 3     10/22/98 6:14p Dave
 * Optimized some #includes in Anim folder. Put in the beginnings of
 * parse/localization support for externalized strings and tstrings.tbl
 * 
 * 2     10/07/98 10:52a Dave
 * Initial checkin.
 * 
 * 1     10/07/98 10:48a Dave
 * 
 * 12    6/23/98 2:52p Hoffoss
 * Changed code so AC compiles once again.
 * 
 * 11    7/20/97 6:57p Lawrance
 * supporting new RLE format
 * 
 * 10    6/25/97 11:57a Lawrance
 * forgot linefeed
 * 
 * 9     6/25/97 11:49a Lawrance
 * don't assert if PCX read fails, print warning
 * 
 * 8     5/21/97 2:26p Lawrance
 * bug fix: not using correct header size
 * 
 * 7     5/21/97 11:06a Lawrance
 * enabling a user-defined transparent value
 * 
 * 6     5/19/97 3:21p Lawrance
 * add fps parm, version num to anim header
 * 
 * 5     2/25/97 5:18p Lawrance
 * force_key_frame now numbering from 1 for PCXs as well as AVIs
 * 
 * 4     2/20/97 1:47p Lawrance
 * adding dots when making frames
 * 
 * 3     2/20/97 10:30a Hoffoss
 * Added in support for forcing a key frame.
 * 
 * 2     2/19/97 9:26p Lawrance
 * added force_key_frame global
 * 
 * 1     2/19/97 7:14p Lawrance
 * 
 * 14    2/19/97 4:21p Lawrance
 * took out unnecessary #include BmpMan.h
 * 
 * 13    2/19/97 3:59p Lawrance
 * using pcxutils to load bitmaps, not bmpman
 * 
 * 12    2/17/97 2:59p Lawrance
 * integrating into game
 * 
 * 11    2/17/97 3:02p Hoffoss
 * Added headers to files, and implemented key frame dialog stuff.
 * 
 * 10    2/14/97 10:38p Lawrance
 * fixing bugs
 * 
 * 9     2/14/97 9:47p Hoffoss
 * fixed bugs.
 * 
 * 8     2/14/97 8:44p Lawrance
 * fixed bug with saving header
 * 
 * 7     2/14/97 8:04p Hoffoss
 * Fixed bug.
 * 
 * 6     2/14/97 7:44p Lawrance
 * fixed some bugs in loading an AVI
 * 
 * 5     2/14/97 7:33p Lawrance
 * added convert_avi_to_anim() function
 * 
 * 4     2/14/97 5:38p Hoffoss
 * Changes to get AnimCoverter project to compile and link.
 * 
 * 3     2/14/97 3:28p Hoffoss
 * Wrote functions to save an anim file.
 * 
 * 2     2/13/97 5:55p Lawrance
 * reading AVI / decompressing AVI functions in
 *
 * $NoKeywords: $
 */

#pragma warning(disable: 4201)

#include <wtypes.h>
#include <vfw.h>		/* Video For Windows header file */
#include "PsTypes.h"
#include "convert.h"
#include "pcxutils.h"
#include "AnimPlay.h"
#include "PackUnPack.h"

#define AVI_STREAM_F_USED	( 1 << 0 )

typedef struct AVI_STREAM_TYPE {
	PAVISTREAM	pstream;
	PAVIFILE		pfile; 
	int			num_frames;
	int			current_frame;
	int			w,h,bpp;
	int			min_compressed_buffer_size;
	ubyte			palette[768];
	char			filename[255];
	//ubyte			pal_translation[256];		// palette translation look-up table
	int		flags;
}	AVI_STREAM_TYPE;

// Internal function prototypes
int	AVI_stream_open(char* filename);
void	AVI_stream_close();
int	AVI_stream_get_frame(ubyte* buffer, int frame_number);
void	AVI_decompress_RLE8(ubyte* src, ubyte* dest, int w, int h);

// Global to file
static		AVI_STREAM_TYPE AVI_stream;	
static int	AVI_stream_inited = 0;

// Globals 
char	*anim_save_filename;
ubyte *cur_frame, *last_frame;
ubyte	anim_buffer[ANIM_BUFFER_MAX];
int	key_frame_rate;
int	force_key_frame;
int	total_key_frames;
int	anim_offset;
int	cur_frame_num;
int	Default_fps;
int	Use_custom_xparent_color;
rgb_triple	Xparent_color;

int	Compression_type;		// what kind of RLE compression is going to be used 
int	Key_frame_compression, Regular_frame_compression;

key_frame *first_frame;
FILE *anim_fp = NULL;
anim Anim;

// AVI_stream_init() is called only to clear USED flag of the AVI_stream structure
// and reset the current frame.
//
//	This does not need to be called explicity, since it will be called by AVI_stream_open()
// anyways.
//
void AVI_stream_init()
{
	AVI_stream.flags &= ~AVI_STREAM_F_USED;
	AVI_stream.current_frame = 0;
	AVI_stream_inited = 1;

	AVIFileInit();						// opens AVIFile library 
}

// AVI_stream_open() will open the AVI file and prepare it for reading, but will not 
// store any of the frame data. 
//
//	returns:   0 ==> success
//           !0 ==> could not open the AVI stream
//
// The filename is expected to be an absolute pathname (or file in the current working directory)
//
int AVI_stream_open(char* filename)
{
	if ( !AVI_stream_inited )
		AVI_stream_init();

	int				hr; 
	PAVIFILE			pfile; 
	PAVISTREAM		pstream;
	AVISTREAMINFO	avi_stream_info;

	Assert( !(AVI_stream.flags & AVI_STREAM_F_USED) );

	// Open the AVI file
	hr = AVIFileOpen(&pfile, filename, OF_SHARE_DENY_WRITE, 0); 
	if (hr != 0){ 
//		nprintf(("Warning", "AVI ==> Unable to open %s", filename)); 
		return -1; 
	} 
 
	strcpy(AVI_stream.filename, filename);

	// Get a handle to the video stream within the AVI file	
	hr = AVIFileGetStream(pfile, &pstream, streamtypeVIDEO, 0); 
	if (hr != 0){ 
		//nprintf(("Warning", "AVI ==> Unable to open video stream in %s", filename)); 
		return -1; 
	} 

	// Store the pointer to stream, since we'll need it later to read from disk
	AVI_stream.pstream = pstream;
	AVI_stream.pfile = pfile;

	// Get information on the stream
	hr = AVIStreamInfo( pstream, &avi_stream_info, sizeof(AVISTREAMINFO) );
	if (hr != 0){ 
		//nprintf(("Warning", "AVI ==> Unable to retreive stream info in %s", filename)); 
		return -1; 
	} 


	int buffer_size;
	
	int start_sample = AVIStreamStart(pstream);
	Assert( start_sample == 0 );

	int end_sample = AVIStreamEnd(pstream);
	Assert( end_sample >= start_sample );

	// store the number of frames in the AVI_info[] structure
	AVI_stream.num_frames = end_sample;		// start sample must be 0
	Assert(AVI_stream.num_frames == AVIStreamLength(pstream) );


	// Get information on the stream
	hr = AVIStreamInfo( pstream, &avi_stream_info, sizeof(AVISTREAMINFO) );
	if (hr != 0){ 
		//nprintf(("Warning", "AVI ==> Unable to retreive stream info in %s", filename)); 
		return -1; 
	} 

	buffer_size = avi_stream_info.dwSuggestedBufferSize;
	Assert( buffer_size > 0 );
	AVI_stream.min_compressed_buffer_size = buffer_size;

	// determine the format of the AVI image data
	ubyte* format_buffer;
	long format_buffer_size;
	BITMAPINFO* bitmap_info;

	hr = AVIStreamFormatSize(pstream, 0, &format_buffer_size);
	Assert( format_buffer_size > 0 );

	format_buffer = (ubyte*) malloc(format_buffer_size);
	Assert(format_buffer != NULL);	// format_buffer is free'ed when AVI is free'ed, since memory is used by b_info member in AVI_info[] structure

	hr = AVIStreamReadFormat(pstream, 0, format_buffer, &format_buffer_size);
	bitmap_info = (BITMAPINFO*)format_buffer;


	switch ( bitmap_info->bmiHeader.biCompression ) {
		case BI_RLE8:
			break;

		default:
			Assert(0);
			break;
	}

	AVI_stream.w = bitmap_info->bmiHeader.biWidth;
	AVI_stream.h = bitmap_info->bmiHeader.biHeight;
	AVI_stream.bpp = bitmap_info->bmiHeader.biBitCount;
		
	// create the palette translation look-up table
	//
	// Transparency:  If the palette color is full green, then treat as transparent
	//						
	RGBQUAD* pal;
	pal = (RGBQUAD*)(bitmap_info->bmiColors);

	// Store the palette in the AVI stream structure
	for ( int i = 0; i < 256; i++ ) {
		AVI_stream.palette[i*3]	  = pal[i].rgbRed;
		AVI_stream.palette[i*3+1] = pal[i].rgbGreen;
		AVI_stream.palette[i*3+2] = pal[i].rgbBlue;
	}	


	//	memcpy(AVI_stream.palette, pal, 256*3);
	
/*
	int transparent_found = 0;
	for ( i = 0; i < 256; i++ ) {

		//nprintf(("AVI", "AVI ==> R: %d  G: %d  B: %d\n", pal[i].rgbRed, pal[i].rgbGreen, pal[i].rgbBlue));
		if ( pal[i].rgbRed < 5 && pal[i].rgbGreen > 250 && pal[i].rgbBlue < 5 ) {
			avi_stream->pal_translation[i]	= TRANSPARENT_INDEX;
			break;	// found transparent, continue in j for loop, since don't need check any more
		}
		else
			avi_stream->pal_translation[i] = palette_find(	pal[i].rgbRed, pal[i].rgbGreen, pal[i].rgbBlue ); 
	}	

	for ( j = i+1; j < 256; j++ ) {
		avi_stream->pal_translation[j] = palette_find(	pal[j].rgbRed, pal[j].rgbGreen, pal[j].rgbBlue ); 
	}
*/

	free(format_buffer);

	// set the flag to used, so to make sure we only process one AVI stream at a time
	AVI_stream.flags |= AVI_STREAM_F_USED;	


	return 0;
}


// AVI_stream_close() should be called when you are finished reading all the frames of an AVI
//
void AVI_stream_close()
{	
//	Assert( AVI_stream.flags & AVI_STREAM_F_USED);

   AVIStreamRelease(AVI_stream.pstream);				// closes the video stream
	AVIFileRelease(AVI_stream.pfile);					// closes the file 
	AVI_stream.flags &= ~AVI_STREAM_F_USED;			// clear the used flag

	AVIFileExit();          // releases AVIFile library 
	AVI_stream_inited = 0;

}




// AVI_stream_get_next_frame() will take the next RLE'd AVI frame and return the
// uncompressed data in the buffer pointer supplied as a parameter.  The caller is
// responsible for allocating the memory before-hand (the memory required is easily
// calculated by looking at the w and h members in AVI_stream).
// 
// returns:    0 ==> success
//            !0 ==> error
//
int AVI_stream_get_frame(ubyte* buffer, int frame_number)
{
	if ( frame_number > AVI_stream.num_frames ) {
		buffer = NULL;
		return -1;
	}

	Assert( (frame_number - 1) >= 0 );

	ubyte* compressed_frame = (ubyte*)malloc(AVI_stream.min_compressed_buffer_size);
	Assert( compressed_frame != NULL );

	long num_bytes_used;
	long num_samples_used;

	AVIStreamRead( AVI_stream.pstream, frame_number-1, 1, compressed_frame, AVI_stream.min_compressed_buffer_size, &num_bytes_used, &num_samples_used);
	Assert(num_samples_used == 1);
		
	AVI_decompress_RLE8(compressed_frame, buffer, AVI_stream.w, AVI_stream.h);

	free( compressed_frame );
	return 0;

}



// -------------------------------------------------------------------------------------------------
// AVI_decompress_RLE8() will decompress the data pointed to by src, and store in dest.
//
//	NOTE:  1. memory for dest must be already allocated before calling function
//

void AVI_decompress_RLE8(ubyte* src, ubyte* dest, int w, int h)
{
	int src_index = 0;
	int dest_index = 0;
	int i;

	Assert( src != NULL);
	Assert( dest != NULL);
	Assert( w > 0 );
	Assert( h > 0 );

	ubyte count;
	ubyte run;
	ubyte control_code;

	int size_src = w * h + 1;

	int scan_line = h-1;	
	int height_offset = scan_line * w;

	while ( src_index < size_src ) {
		
		count = src[src_index];
		
		if ( count == 0 ) {	// control code follows
			src_index++;
			control_code = src[src_index];
			if ( control_code == 1 ) {
				src_index++;
//				nprintf(("AVI","AVI ==> Reached end of compressed image\n"));
				break;
			}
			else if ( control_code == 0 ) {
				src_index++;
				scan_line--;
				height_offset = scan_line * w;	// only need to calc once per scanline
				dest_index = 0;
				//nprintf(("AVI","AVI ==> Reached end of line in compressed image\n"));
			}
			else if ( control_code == 2 ) {
				Assert(0);
			}
			else {
				// in absolute mode
				src_index++;
				for ( i = 0; i < control_code; i++ ) {

					dest[height_offset + dest_index] = src[src_index];
					dest_index++;
					src_index++;
				}
				// run must end on a word boundry
				if ( control_code & 1 )
					src_index++;
			}
		}
		else {
			src_index++;
			run = src[src_index];
			// nprintf(("AVI","AVI ==> Got %d pixel run of %d\n", src[src_index], count));
			memset( &dest[height_offset + dest_index], run, count );
			dest_index += count;
			src_index++;
		}
	}	// end while

}

int save_anim_header()
{
	int i, new_format_id = 0;

	Assert(anim_fp);
	fclose(anim_fp);
	anim_fp = fopen(anim_save_filename, "r+b");

	if (!fwrite(&new_format_id, 2, 1, anim_fp))
		return -1;
	if (!fwrite(&Anim.version, 2, 1, anim_fp))
		return -1;
	if (!fwrite(&Anim.fps, 2, 1, anim_fp))
		return -1;
	if (!fwrite(&Anim.xparent_r, 1, 1, anim_fp))
		return -1;
	if (!fwrite(&Anim.xparent_g, 1, 1, anim_fp))
		return -1;
	if (!fwrite(&Anim.xparent_b, 1, 1, anim_fp))
		return -1;
	if (!fwrite(&Anim.width, 2, 1, anim_fp))
		return -1;
	if (!fwrite(&Anim.height, 2, 1, anim_fp))
		return -1;
	if (!fwrite(&Anim.total_frames, 2, 1, anim_fp))
		return -1;
	if (!fwrite(&Anim.packer_code, 1, 1, anim_fp))
		return -1;
	if (fwrite(&Anim.palette, 3, 256, anim_fp) != 256)
		return -1;
	if (!fwrite(&total_key_frames, 2, 1, anim_fp))
		return -1;

	for (i=0; i<Anim.num_keys; i++) {
		if (!fwrite(&Anim.keys[i].frame_num, 2, 1, anim_fp))
			return -1;

		if (!fwrite(&Anim.keys[i].offset, 4, 1, anim_fp))
			return -1;
	}

	if (!fwrite(&anim_offset, 4, 1, anim_fp))
		return -1;

	return 0;
}

// This function allocates a linked list of key frame headers.
// It is responsible for determining which frames in an anim
// should be key frames.
int allocate_key_frames(int total_frames)
{
	int count = 0, frame = 1, rate = key_frame_rate, last_frame;

	if (!rate)
		rate = total_frames;

	while (frame <= total_frames) {
		count++;
		frame += rate;
	}

	if (force_key_frame >= 0)
		count++;

	if (count)
		Anim.keys = (key_frame *) malloc(count * sizeof(key_frame));

	count = 0;
	frame = last_frame = 1;
	while (frame <= total_frames) {
		if ((force_key_frame > last_frame) && (force_key_frame < frame))
			Anim.keys[count++].frame_num = force_key_frame;

		Anim.keys[count++].frame_num = frame;
		frame += rate;
	}

	if (force_key_frame > last_frame)
		Anim.keys[count++].frame_num = force_key_frame;

	Anim.num_keys = count;
	return count;  // number of key frames
}

int anim_save_init(char *file, int width, int height, int frames)
{
	Assert(file);
	anim_save_filename = file;
	anim_fp = fopen(file, "wb");
	if (!anim_fp)
		return -1;

	Anim.version = ANIM_VERSION;
	Anim.fps = Default_fps;
	Anim.width = width;
	Anim.height = height;
	Anim.packer_code = PACKER_CODE;
	Anim.xparent_r = Xparent_color.r;
	Anim.xparent_g = Xparent_color.g;
	Anim.xparent_b = Xparent_color.b;
	Anim.total_frames = frames;
	anim_offset = 0;
	cur_frame_num = 0;
	total_key_frames = allocate_key_frames(frames);
	fseek(anim_fp, ANIM_HEADER_SIZE + total_key_frames * 6, SEEK_SET);

	switch ( Compression_type ) {
		case CUSTOM_DELTA_RLE:
			Key_frame_compression = PACKING_METHOD_RLE_KEY;
			Regular_frame_compression = PACKING_METHOD_RLE;
			break;

		case STD_DELTA_RLE:
			Key_frame_compression = PACKING_METHOD_STD_RLE_KEY;
			Regular_frame_compression = PACKING_METHOD_STD_RLE;
			break;

		default:
			Int3();
			return -1;
			break;
	} // end switch

	return 0;
}

int anim_save_frame()
{
	ubyte *temp;
	int i, size;
	key_frame *keyp = NULL;

	Assert(anim_fp);
	cur_frame_num++;
	Assert(cur_frame_num <= Anim.total_frames);

	for (i=0; i<Anim.num_keys; i++)
		if (Anim.keys[i].frame_num == cur_frame_num) {
			keyp = &Anim.keys[i];
			break;
		}

	if (keyp) {
		fprintf(stdout, "*");
		fflush(stdout);
		keyp->offset = anim_offset;
		size = pack_key_frame(cur_frame, anim_buffer, Anim.width * Anim.height, ANIM_BUFFER_MAX, Key_frame_compression);

	} else {
		fprintf(stdout, ".");
		fflush(stdout);
		size = pack_frame(cur_frame, last_frame, anim_buffer, Anim.width * Anim.height, ANIM_BUFFER_MAX, Regular_frame_compression);
	}

	if (size < 0)
		return -1;

	if ((int) fwrite(anim_buffer, 1, size, anim_fp) != size)
		return -1;

	anim_offset += size;
	temp = cur_frame;
	cur_frame = last_frame;
	last_frame = temp;
	return 0;
}


// converts an avi file to an anim file
//
// returns:   0 ==> success
//	          !0 ==> failure
//
int convert_avi_to_anim(char* filename)
{
	char ani_filename[255];
	int ret = 1;
	int rc, i, xparent_pal_index;
	int avi_stream_opened = 0;

	rc = AVI_stream_open(filename);
	if ( rc != 0 ) {
		// could not open the AVI stream
		goto Finish;
	}
	avi_stream_opened = 1;
	
	Assert(AVI_stream.bpp == 8);
	cur_frame = (ubyte*) malloc(AVI_stream.w * AVI_stream.h);
	last_frame = (ubyte*) malloc(AVI_stream.w * AVI_stream.h);
	Assert(cur_frame && last_frame);

	strcpy(ani_filename, AVI_stream.filename);
	strcpy(ani_filename + strlen(ani_filename) - 3, "ani");

	memcpy(Anim.palette, AVI_stream.palette, 768);

	if (Use_custom_xparent_color) {
		// Need to look at pixel in top-left 
		rc = AVI_stream_get_frame(cur_frame, 1);
		xparent_pal_index = cur_frame[0];
		Xparent_color.r = Anim.palette[xparent_pal_index * 3];
		Xparent_color.g = Anim.palette[xparent_pal_index * 3 + 1];
		Xparent_color.b = Anim.palette[xparent_pal_index * 3 + 2];

	} else {
		Xparent_color.r = 0;
		Xparent_color.g = 255;
		Xparent_color.b = 0;
	}
	
	rc = anim_save_init(ani_filename, AVI_stream.w, AVI_stream.h, AVI_stream.num_frames);
	if (rc == -1)
		goto Finish;

	for ( i=1; i <= AVI_stream.num_frames; i++ ) {
		// get uncompressed frame from the AVI
		rc = AVI_stream_get_frame(cur_frame, i);
		if ( rc != 0 )
			goto Finish;

		// pass to the anim compression
		rc = anim_save_frame();
		if ( rc != 0 )
			goto Finish;
	}

	rc = save_anim_header();
	if ( rc != 0 )
		goto Finish;

	ret = 0;

	Finish:
	// done with the AVI.. close the stream
	if ( avi_stream_opened )
		AVI_stream_close();

	if ( anim_fp )
		fclose(anim_fp);

	free(cur_frame);
	free(last_frame);
	fprintf(stdout,"\n");
	fflush(stdout);
	return ret;
}

int convert_frames_to_anim(char *filename)
{
	int first_frame, frame, pos, width, height, xparent_pal_index, r = -1;
	char ani_filename[255], name[255], temp[8];	
	int rc;
	FILE *fp;

	Assert(strlen(filename) < 254);
	strcpy(name, filename);
	strcpy(ani_filename, filename);
	strcpy(ani_filename + strlen(ani_filename) - 8, ".ani");
	pos = strlen(name) - 8;
	frame = first_frame = atoi(&name[pos]);
	force_key_frame -= frame;

	// first file
	fp = fopen(name, "rb");
	if(fp != NULL){
		do {
			fclose(fp);
			frame++;
			sprintf(temp, "%04.4d", frame);
			strncpy(&name[pos], temp, 4);	

			// next file
			fp = fopen(name, "rb");
		} while(fp != NULL);	
	}

	rc = pcx_read_header(filename, &width, &height, NULL);
	if (rc != PCX_ERROR_NONE) {
		fprintf(stdout, "An error reading the PCX file %s.  It may not exist.\n", filename);
		return -1;
	}

	cur_frame = (ubyte *) malloc(width * height);
	last_frame = (ubyte *) malloc(width * height);

	rc = pcx_read_bitmap_8bpp(filename, cur_frame, Anim.palette);
	if (rc != PCX_ERROR_NONE) {
		fprintf(stdout, "An error reading the PCX file %s.  It may not exist.\n", filename);
		return -1;
	}

	if (Use_custom_xparent_color) {
		// Need to look at pixel in top-left 
		xparent_pal_index = ((ubyte *) cur_frame)[0];
		Xparent_color.r = Anim.palette[xparent_pal_index * 3];
		Xparent_color.g = Anim.palette[xparent_pal_index * 3 + 1];
		Xparent_color.b = Anim.palette[xparent_pal_index * 3 + 2];

	} else {
		Xparent_color.r = 0;
		Xparent_color.g = 255;
		Xparent_color.b = 0;
	}

	if (anim_save_init(ani_filename, width, height, frame - first_frame))
		goto done;

	while (first_frame < frame) {
		sprintf(temp, "%04.4d", first_frame);
		strncpy(&name[pos], temp, 4);
		rc = pcx_read_bitmap_8bpp(name, cur_frame, Anim.palette);
		if (rc != PCX_ERROR_NONE)
			goto done;

		if (anim_save_frame())
			goto done;

		first_frame++;
	}

	if (save_anim_header())
		goto done;

	r = 0;

done:
	fclose(anim_fp);
	free(cur_frame);
	free(last_frame);
	fprintf(stdout, "\n");
	fflush(stdout);
	return r;
}

