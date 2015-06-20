/*
 * Copyright (C) Volition, Inc. 1999.  All rights reserved.
 *
 * All source code herein is the property of Volition, Inc. You may not sell 
 * or otherwise commercially exploit the source or things you created based on the 
 * source.
 *
*/

/*
 * $Logfile: /Freespace2/code/nebedit/NebEdit.cpp $
 * $Revision: 7 $
 * $Date: 7/15/99 3:07p $
 * $Author: Dave $
 *
 * Program to edit nebulas in 2d
 *
 * $Log: /Freespace2/code/nebedit/NebEdit.cpp $
 * 
 * 7     7/15/99 3:07p Dave
 * 32 bit detection support. Mouse coord commandline.
 * 
 * 6     5/19/99 4:07p Dave
 * Moved versioning code into a nice isolated common place. Fixed up
 * updating code on the pxo screen. Fixed several stub problems.
 * 
 * 5     1/08/99 2:06p Dave
 * Fixed pfoview for software mode.
 * 
 * 4     12/18/98 1:14a Dave
 * Rough 1024x768 support for Direct3D. Proper detection and usage through
 * the launcher.
 * 
 * 3     11/13/98 2:32p Dave
 * Improved commandline parsing for exe pathname.
 * 
 * 2     10/24/98 9:51p Dave
 * 
 * 1     10/24/98 9:39p Dave
 * 
 * 13    4/13/98 10:11a John
 * Made timer functions thread safe.  Made timer_init be called in all
 * projects.
 * 
 * 12    3/23/98 1:35p Sandeep
 * 
 * 11    3/05/98 11:15p Hoffoss
 * Changed non-game key checking to use game_check_key() instead of
 * game_poll().
 * 
 * 10    12/29/97 5:10p Allender
 * fixed problems with speed not being reported properly in multiplayer
 * games.  Made read_flying_controls take frametime as a parameter.  More
 * ship/weapon select stuff
 * 
 * 9     12/04/97 3:47p John
 * Made joystick move mouse cursor
 * 
 * 8     11/21/97 11:32a John
 * Added nebulas.   Fixed some warpout bugs.
 * 
 * 7     11/19/97 10:15p Adam
 * upped maxtris to 200
 * 
 * 6     11/19/97 4:28p Sandeep
 * added poly/vert counter
 * 
 * 5     11/19/97 1:59p Sandeep
 * Added multiple vertex editing mode
 * 
 * 4     11/16/97 2:29p John
 * added versioning to nebulas; put nebula code into freespace.
 * 
 * 3     11/13/97 12:04p Sandeep
 * Added face editing support, deletion support, and a saving and loading
 * stuff.
 * 
 * 2     11/10/97 9:59p John
 * some tweaking
 * 
 * 1     11/10/97 9:42p John
 *
 * $NoKeywords: $
 */


#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <dos.h>

#include "pstypes.h"
#include "2d.h"
#include "3d.h"
#include "key.h"
#include "palman.h"
#include "bmpman.h"
#include "timer.h"
#include "floating.h"
#include "osapi.h"
#include "cfile.h"
#include "LinkList.h"
#include "Lighting.h"
#include "Mouse.h"
#include "vecmat.h"
#include "physics.h"
#include "model.h"
#include "font.h"


#define SCREEN_W	640	
#define SCREEN_H	480

vector ViewerPos;
matrix ViewerOrient;
matrix ModelOrient;
vector ModelPos;
physics_info ViewerPhysics;
float ViewerZoom = 1.0f;

int test_model = -1;
int Fred_running = 0;
int Pofview_running = 0;
float flFrametime = 0.0f;

int Font1 = -1;

color color_green;

vector Global_light_world = { 0.208758f, -0.688253f, -0.694782f };

// nebula stuff

#define NEB_W 6
#define NEB_H 6
#define MAX_TRIS 200
#define MAX_POINTS 300

int neb_w = 0, neb_h = 0;

int nebula_inited = 0;
int num_pts = 0;

int x[MAX_POINTS], y[MAX_POINTS], l[MAX_POINTS];
float scale_factor = 1.0f;

int num_tris = 0;
int tri[MAX_TRIS][3];

color nebula_color;

int Mouse_x, Mouse_y;
int Current_point;
BOOL Selected[MAX_POINTS];
BOOL Sel_mode = 0;   // 0 = 1 point at a time, 1 = select multiple points
int Current_face;

int View_mode = 0;	// 0 = 2d editor, 1 = 3d viewer

int Vert_mode = 0;   // 0 = Move vertices/Add vertices, 2 = Move face/Add face

int Which_vert = 0;  // Current vertex of the faceadd

int Orig_pos_x;
int Orig_pos_y;
int End_pos_x;
int End_pos_y;
BOOL Draw_sel_box = FALSE;

int Neb_created = 0;

int Nebedit_running = 1;

extern int load_nebula_sub(char*);
extern void project_2d_onto_sphere(vector *, float, float);

void create_default_neb()
{
	int i,j;
	neb_w = NEB_W;
	neb_h = NEB_H;
	num_pts = neb_w*neb_h;

	for (j=0; j<neb_h; j++ )	{
		for (i=0; i<neb_w; i++ )	{
			x[i+j*neb_w] = ((i+1)*SCREEN_W)/(neb_w+2);
			y[i+j*neb_w] = ((j+3)*SCREEN_H)/(neb_h+6);
			if ( (j==0) || (j==neb_h-1))	{
				l[i+j*neb_w] = 0;
			} else {
				l[i+j*neb_w] = 31;
			}
		}
	}

	num_tris = 0;

	for (j=0; j<neb_h-1; j++ )	{
		for (i=0; i<neb_w-1; i++ )	{
			tri[num_tris][0] = i+neb_w*j;
			tri[num_tris][1] = i+neb_w*j+1;
			tri[num_tris][2] = i+neb_w*(j+1)+1;
			num_tris++;

			tri[num_tris][0] = i+neb_w*j;
			tri[num_tris][1] = i+neb_w*(j+1)+1;
			tri[num_tris][2] = i+neb_w*(j+1);
			num_tris++;
		}
	}

	Neb_created = 1;
}

#define NEBULA_FILE_ID "NEBU"			
#define NEBULA_MAJOR_VERSION 1		// Can be 1-?
#define NEBULA_MINOR_VERSION 0		// Can be 0-99

void save_nebula_sub(char *filename)
{
	FILE *fp;
	float xf, yf;
	int version;

	fp = fopen(filename, "wb");

	// ID of NEBU
	fwrite( "NEBU", 4, 1, fp );	
	version = NEBULA_MAJOR_VERSION*100+NEBULA_MINOR_VERSION;
	fwrite( &version, sizeof(int), 1, fp );
	fwrite( &num_pts, sizeof(int), 1, fp );
	fwrite( &num_tris, sizeof(int), 1, fp );

	for (int i=0; i<num_pts; i++ )	{
		xf = float(x[i])/640.0f;
		yf = float(y[i])/480.0f;
		fwrite( &xf, sizeof(float), 1, fp );
		fwrite( &yf, sizeof(float), 1, fp );
		fwrite( &l[i], sizeof(int), 1, fp );
	}

	for (i=0; i<num_tris; i++ )	{
		fwrite( &tri[i][0], sizeof(int), 1, fp );
		fwrite( &tri[i][1], sizeof(int), 1, fp );
		fwrite( &tri[i][2], sizeof(int), 1, fp );
	}

	fclose(fp);
}

void nebedit_close()
{
	save_nebula_sub( "autosaved.neb" );
}

void save_nebula()
{
	char filename[255] = "\0";
	//char filter[255] = "Nebula Files\0
	OPENFILENAME o;
	memset(&o,0,sizeof(o));
	o.lStructSize = sizeof(o);
	//o.hwndOwner = GetActiveWindow();
	o.lpstrFilter = "Nebula Files\0*.NEB\0\0";
	o.lpstrFile = filename;
	o.nMaxFile = 256;
	o.Flags = OFN_OVERWRITEPROMPT | OFN_PATHMUSTEXIST;
	o.lpstrDefExt = "*.NEB";
	if (!GetSaveFileName(&o)) return;

	save_nebula_sub(filename);
}

void load_nebula()
{
	char filename[255] = "\0";
	OPENFILENAME o;
	memset(&o,0,sizeof(o));
	o.lStructSize = sizeof(OPENFILENAME);
	//o.hwndOwner = GetActiveWindow();
	o.lpstrFilter = "Nebula Files\0*.NEB\0\0";
	o.lpstrFile = filename;
	o.nMaxFile = 256;
	o.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;
	o.lpstrDefExt = "*.NEB";

	int create_default = 0;
	if (!GetOpenFileName(&o)) {
		create_default = 1;
	} else {
		if ( !load_nebula_sub(filename))	{
			create_default = 1;
		}
	}

	if ( create_default )	{	
		create_default_neb();	
	}

	Neb_created = 1;
}

void nebula_init()
{
	if ( nebula_inited ) return;
	memset(Selected, 0, sizeof(BOOL)*MAX_POINTS);
	nebula_inited++;

	create_default_neb();	
	gr_init_alphacolor( &nebula_color, 0, 255, 0, 255 );

	return;
}

void draw_tri_2d( int i, int j, int k )
{
	int index[3];

	index[0] = i;
	index[1] = j;
	index[2] = k;

	vertex va, vb, vc;
	vertex * verts[3] = { &va, &vb, &vc };
//	gr_zbuffering = 0;
	for (int v=0; v<3; v++ )	{
		verts[v]->sx = i2fl(x[index[v]]);   
		verts[v]->sy = i2fl(y[index[v]]);
		verts[v]->u = 0.0f;
		verts[v]->v = 0.0f;
		verts[v]->sw = 1.0f; 
		verts[v]->r = verts[v]->g = verts[v]->b = (ubyte)(i2fl(l[index[v]])/31.0f);

	}

//	gr_set_color( 0, 0, 0 );
	gr_tmapper(3, verts, TMAP_FLAG_RAMP | TMAP_FLAG_GOURAUD | TMAP_FLAG_NEBULA );

	if ( !keyd_pressed[KEY_LSHIFT] )	{
		gr_set_color(100,100,100);
		gr_line( x[i], y[i], x[j], y[j] );
		gr_line( x[j], y[j], x[k], y[k] );
		gr_line( x[k], y[k], x[i], y[i] );
	}
}

void nebula_draw_2d()
{
	int i;
	
	for (i=0; i<num_tris; i++ )	{
		draw_tri_2d( tri[i][0], tri[i][1], tri[i][2] );
	}		

		gr_set_color(100,0,0);
		for (i=0; i<num_pts; i++ )	{
			gr_circle( x[i], y[i], 4 );
		}
		if ((Sel_mode==1)) { // multiple selection
			if (Draw_sel_box) {
				gr_set_color(200,0,200);
				gr_line(Orig_pos_x, Orig_pos_y, Orig_pos_x, End_pos_y);
				gr_line(Orig_pos_x, End_pos_y, End_pos_x, End_pos_y);
				gr_line(End_pos_x, Orig_pos_y, End_pos_x, End_pos_y);
				gr_line(End_pos_x, Orig_pos_y, Orig_pos_x, Orig_pos_y);
			} else {
				gr_set_color(0,100,0);
				for (int i=0;i<num_pts;i++)
					if (Selected[i]) gr_circle( x[i], y[i], 5);
			}
		} else if ((Vert_mode==0)&&(Current_point>-1)) {
			gr_set_color(0,100,0);
			gr_circle( x[Current_point], y[Current_point], 5);
		} else if (Vert_mode == 1) {
			for (i=0;i<Which_vert;i++) {
				gr_set_color(0,0,100);
				gr_circle( x[tri[num_tris][i]], y[tri[num_tris][i]], 6);
			}
			gr_set_color(200,200,0);
			if (Current_face>-1) {
				gr_line(x[tri[Current_face][0]], y[tri[Current_face][0]], 
						x[tri[Current_face][1]], y[tri[Current_face][1]]);
				gr_line(x[tri[Current_face][1]], y[tri[Current_face][1]], 
						x[tri[Current_face][2]], y[tri[Current_face][2]]);
				gr_line(x[tri[Current_face][2]], y[tri[Current_face][2]], 
						x[tri[Current_face][0]], y[tri[Current_face][0]]);
			}
		}
}


void draw_tri_3d( int i, int j, int k )
{
	int index[3];

	index[2] = k;
	index[1] = j;
	index[0] = i;

	vertex va, vb, vc;
	vertex * verts[3] = { &va, &vb, &vc };
	//gr_zbuffering = 0;
	for (int v=0; v<3; v++ )	{
		vector tmp;
		
		project_2d_onto_sphere( &tmp, 1.0f - i2fl(x[index[v]])/640.0f, i2fl(y[index[v]])/480.0f );
	
		vm_vec_scale( &tmp, 10.0f );

		g3_rotate_faraway_vertex( verts[v], &tmp );
		//g3_rotate_vertex( verts[v], &tmp );
		g3_project_vertex( verts[v] );

		verts[v]->r = verts[v]->g = verts[v]->b = (ubyte)(i2fl(l[index[v]])/31.0f);
	}

	//gr_zbuffering = 0;
	//gr_set_color_fast( &nebula_color );
	//gr_set_color( 0, 0, 0 );
	g3_draw_poly(3, verts, TMAP_FLAG_RAMP | TMAP_FLAG_GOURAUD | TMAP_FLAG_NEBULA );
}

void nebula_draw_3d()
{
	int i;
	for (i=0; i<num_tris; i++ )	{
		draw_tri_3d( tri[i][0], tri[i][1], tri[i][2] );
	}		
}

void render_frame()
{
	gr_reset_clip();

	gr_set_color(0,0,0);		// set color to black
	gr_rect(0,0,SCREEN_W,SCREEN_H);	// clear screen

	light_reset();
	light_add_directional( &Global_light_world, 0.1f, 1.0f, 1.0f, 1.0f );

	g3_start_frame(1);

	g3_set_view_matrix(&ViewerPos, &ViewerOrient,ViewerZoom);

	if ( View_mode == 0 )	{
		nebula_draw_2d();

		gr_set_font(Font1);
		gr_set_color_fast( &color_green );
		gr_printf(10,10,"Nebula Editor. Mode :");
		if (Sel_mode ==1) {
				gr_printf(180, 10, "Multiple Vertex Selection Editing");
		} else if (Vert_mode ==0 ) {
			gr_printf(180,10,"Vertex Editing");
			if(Current_point >= 0){
				gr_printf(180, 20, "Current vertex intensity : %d\n", l[Current_point]);
			}
		} else if (Vert_mode ==1) {
			gr_printf(180,10,"Face Editing");
		}
		char blah[255];
		gr_printf(20,30,"# Points:");
		gr_printf(100,30, itoa(num_pts, blah, 10));
		gr_printf(220,30,"# Polys:");
		gr_printf(300,30, itoa(num_tris, blah, 10));		
	} else {
		nebula_draw_3d();
		model_render( test_model, &ModelOrient, &ModelPos );
	}

	g3_end_frame();

	gr_flip();
}

int get_closest(int mx, int my)
{
	int i, closest = -1, cval = 100000;

	for (i=0; i<num_pts; i++ )	{
		int dist;
		int dx, dy;
		
		dx = x[i] - mx;
		dy = y[i] - my;
		
		dist = fl2i(fl_sqrt( i2fl((dx*dx)+(dy*dy)) ));

		if ( dist < cval )	{
			cval = dist;
			closest = i;
		}
	}

	return closest;
}

int get_closest_face(int mx, int my)
{
	int i, closest = -1, cval = 100000;

	for (i=0; i<num_tris; i++ )	{
		int dist;
		int dx, dy;
		
		dx = x[tri[i][0]] - mx;
		dy = y[tri[i][0]] - my;

		dx += x[tri[i][1]] - mx;
		dy += y[tri[i][1]] - my;
		
		dx += x[tri[i][2]] - mx;
		dy += y[tri[i][2]] - my;

		dist = fl2i(fl_sqrt( i2fl((dx*dx)+(dy*dy)) ));
/*
		dist += fl2i(fl_sqrt( i2fl((dx*dx)+(dy*dy)) ));

		dx = x[tri[i][2]] - mx;
		dy = y[tri[i][2]] - my;
		dist += fl2i(fl_sqrt( i2fl((dx*dx)+(dy*dy)) ));
*/

		if ( dist < cval )	{
			cval = dist;
			closest = i;
		}
	}

	return closest;
}

void delete_face(int i)
{
	for (int j=i;j<num_tris;j++) {
		memcpy(tri[j], tri[j+1], sizeof(int)*3);
	}
	num_tris--;
}

void delete_vert(int i)
{
	for (int j=0;j<num_tris;j++) {
		if ((tri[j][0]==i)||(tri[j][1]==i)||(tri[j][2]==i)) {
			delete_face(j);
			j=0;
		}
	}
	for (j=0;j<num_tris;j++) {
		if (tri[j][0]>i) tri[j][0]--;
		if (tri[j][1]>i) tri[j][1]--;
		if (tri[j][2]>i) tri[j][2]--;
	}
	for (j=i;j<num_pts;j++) {
		x[j] = x[j+1];
		y[j] = y[j+1];
		l[j] = l[j+1];
	}
	num_pts--;
}

int add_vert(int mx, int my)
{
	Assert(num_pts<300);
	x[num_pts] = mx;
	y[num_pts] = my;
	l[num_pts] = 0;
	num_pts++;
	return num_pts-1;
}

void select_by_box(int x1, int y1, int x2, int y2)
{
	if (x1>x2) {
		int temp = x1;
		x1 = x2;
		x2 = temp;
	}
	if (y1>y2) {
		int temp = y1;
		y1 = y2;
		y2 = temp;
	}
	for (int i=0;i<num_pts;i++) {
		if ((x[i]<=x2) && (x[i]>=x1) &&
			 (y[i]<=y2) && (y[i]>=y1)) {
			Selected[i] = TRUE;
		}
	}
}

void sphericalize_nebula()
{
	int idx1, idx2;
	int px = SCREEN_W / (neb_w - 1);
	int py = SCREEN_H / (neb_h - 1);

	// flatten out the nebula so that it covers the entire sphere evenly
	for(idx1=0; idx1<neb_w; idx1++){
		for(idx2=0; idx2<neb_h; idx2++){
			x[idx1+idx2*neb_w] = px * idx1;
			y[idx1+idx2*neb_w] = py * idx2;
		}
	}
}

void controls_read_all(control_info * ci, float sim_time )
{
	float kh;

	{
		float temp = ci->heading;
		float temp1 = ci->pitch;
		memset( ci, 0, sizeof(control_info) );
		ci->heading = temp;
		ci->pitch = temp1;
	}

	// From keyboard...
	kh = (key_down_timef(KEY_PAD6) - key_down_timef(KEY_PAD4))/8.0f;
	if (kh == 0.0f)
		ci->heading = 0.0f;
	else if (kh > 0.0f) {
		if (ci->heading < 0.0f)
			ci->heading = 0.0f;
	} else // kh < 0
		if (ci->heading > 0.0f)
			ci->heading = 0.0f;
	ci->heading += kh;

	kh = (key_down_timef(KEY_PAD8) - key_down_timef(KEY_PAD2))/8.0f;
	if (kh == 0.0f)
		ci->pitch = 0.0f;
	else if (kh > 0.0f) {
		if (ci->pitch < 0.0f)
			ci->pitch = 0.0f;
	} else // kh < 0
		if (ci->pitch > 0.0f)
			ci->pitch = 0.0f;
	ci->pitch += kh;

	ci->bank = (key_down_timef(KEY_PAD7) - key_down_timef(KEY_PAD9))*.75f;
	ci->forward = key_down_timef(KEY_A) - key_down_timef(KEY_Z);
	ci->sideways = key_down_timef(KEY_PAD3) - key_down_timef(KEY_PAD1);
	ci->vertical = key_down_timef(KEY_PADPLUS) - key_down_timef(KEY_PADENTER);
}

int check_keys()
{
	int k;

	while( (k = key_inkey()) != 0 )	{
//mprintf(( "Key = %x\n", k ));
		if ( k == KEY_ESC ) {
			return 1;
		}

		switch( k )	{
		case KEY_ENTER:
			Sel_mode = FALSE;
			Vert_mode = !Vert_mode;
			Which_vert = 0;
			break;

		case KEY_DELETE:
			if (Sel_mode) break;
			if (Vert_mode==1) delete_face(Current_face);
			else if (Vert_mode==0) {
				delete_vert(Current_point);
			}
			break;

		case KEY_MINUS:
			scale_factor -= 0.05f;
			mprintf(( "Scale = %.1f\n", scale_factor ));
			break;


		case KEY_EQUAL:
			scale_factor += 0.05f;
			mprintf(( "Scale = %.1f\n", scale_factor ));
			break;

		case KEY_INSERT:
			Sel_mode = !Sel_mode;
			break;

		case KEY_SPACEBAR:
			View_mode = !View_mode;
			break;

		case KEY_COMMA:
			if (Sel_mode) {
				int i;
				for (i=0;i<num_pts;i++) if (Selected[i]) {
					if ( l[i] > 0 )	{
						l[i]--;
					}
				}
			} else if (Vert_mode==0) {
				if ( Current_point > -1 )	{
					if ( l[Current_point] > 0 )	{
						l[Current_point]--;
					}
				}
			} else if (Vert_mode ==1) {
				if ( l[tri[Current_face][0]] > 0 )	{
						l[tri[Current_face][0]]--;
					}
				if ( l[tri[Current_face][1]] > 0 )	{
						l[tri[Current_face][1]]--;
					}
				if ( l[tri[Current_face][2]] > 0 )	{
						l[tri[Current_face][2]]--;
					}
			}
			break;

		case KEY_PERIOD:	
			if (Sel_mode) {
				int i;
				for (i=0;i<num_pts;i++) if (Selected[i]) {
					if ( l[i] < 31 )	{
						l[i]++;
					}
				}
			} else if (Vert_mode==0) {
				if ( Current_point > -1 )	{
					if ( l[Current_point] < 31 )	{
						l[Current_point]++;
					}
				}
			} else if (Vert_mode ==1) {
				if ( l[tri[Current_face][0]] <31 )	{
						l[tri[Current_face][0]]++;
					}
				if ( l[tri[Current_face][1]] <31)	{
						l[tri[Current_face][1]]++;
					}
				if ( l[tri[Current_face][2]] <31 )	{
						l[tri[Current_face][2]]++;
					}
			}
			
			break;		

		case KEY_F5:
			save_nebula();
			break;
		case KEY_F7:
			load_nebula();
			break;

		case KEY_BACKSP:
			sphericalize_nebula();
			break;
		}
	}
	return 0;
}

void os_close()
{
	exit(1);
}

int newtri[3];

int mdflag = 0;

int PASCAL WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR szCmdLine, int nCmdShow)
{
	int i;
	fix t1, t2;
	control_info ci;
	float speed = 20.0f;		// how fast viewer moves	

	// setup the fred exe directory so CFILE can init properly
	/*
	char *c = GetCommandLine();
	Assert(c != NULL);
	char *tok = strtok(c, " ");
	Assert(tok != NULL);	
	*/

	timer_init();
	// cfile_init(tok);
	cfile_init(__argv[0]);
	os_init( "NebEdit", "NebEdit" );	//SCREEN_W, SCREEN_H );
	palette_load_table( "gamepalette1-01.pcx" );	
	gr_init(GR_640, GR_SOFTWARE, 8);
	key_init();
	mouse_init();
	Font1 = gr_init_font( "font01.vf" );
	gr_init_alphacolor( &color_green, 0,255,0,255 );

	test_model = model_load( "fighter01.pof", 0, NULL );

	physics_init( &ViewerPhysics );
	ViewerPhysics.flags |= PF_ACCELERATES | PF_SLIDE_ENABLED;
	
	ViewerPhysics.max_vel.x = 2.0f*speed;		//sideways
	ViewerPhysics.max_vel.y = 2.0f*speed;		//up/down
	ViewerPhysics.max_vel.z = 2.0f*speed;		//forward
	ViewerPhysics.max_rear_vel = 2.0f*speed;	//backward -- controlled seperately
	
	memset( &ci, 0, sizeof(control_info) );

	ModelOrient = vmd_identity_matrix;
	ModelPos.x=0.0f; ModelPos.y = 0.0f; ModelPos.z = 0.0f;

	ViewerOrient = vmd_identity_matrix;
	ViewerPos.x=0.0f; ViewerPos.y = 0.0f; ViewerPos.z = -50.0f;

	flFrametime = 0.033f;

	t1 = timer_get_fixed_seconds();

	nebula_init();

	int some_selected = 0;

	while(1)	{
		some_selected = FALSE;
		if (Sel_mode==1) {
			for (i=0;i<num_pts;i++) {
				if (Selected[i]) {
					some_selected = TRUE;
					break;
				}
			}
		}

		mouse_get_pos( &Mouse_x, &Mouse_y );

		if (Current_face==-1) {
			Current_face = get_closest_face(Mouse_x, Mouse_y);
		}
		
		if ( check_keys() ){
			break;
		}

		if ( Sel_mode==1 ) {
			// Special mouse handlers for multiple selmode
			if (mouse_down_count(LOWEST_MOUSE_BUTTON)) {
				Orig_pos_x = Mouse_x;
				Orig_pos_y = Mouse_y;
			}
			if (mouse_down(LOWEST_MOUSE_BUTTON)) {
				for (i=0;i<num_pts;i++) {
					if (Selected[i]) {
						x[i]+=Mouse_x - Orig_pos_x;
						y[i]+=Mouse_y - Orig_pos_y;
					}
				}
				Orig_pos_x = Mouse_x;
				Orig_pos_y = Mouse_y;
			}
			if (mouse_down_count(MOUSE_RIGHT_BUTTON)) {
				Orig_pos_x = Mouse_x;
				Orig_pos_y = Mouse_y;
				for (i=0;i<num_pts;i++) {
					Selected[i] = FALSE;
				}
			}
			if (mouse_down(MOUSE_RIGHT_BUTTON)) {
				Draw_sel_box = TRUE;
				End_pos_x = Mouse_x;
				End_pos_y = Mouse_y;
			}
			if (mouse_up_count(MOUSE_RIGHT_BUTTON)) {
				Draw_sel_box = FALSE;
				End_pos_x = Mouse_x;
				End_pos_y = Mouse_y;
				select_by_box(Orig_pos_x, Orig_pos_y, End_pos_x, End_pos_y);
			}

		} else {

		if ( mouse_down(LOWEST_MOUSE_BUTTON) )	{
			if ( mdflag )	{
				if (Vert_mode==0) {
					x[Current_point] = Mouse_x;
					y[Current_point] = Mouse_y;
				} else if (Vert_mode==1) {
					x[tri[Current_face][0]] += Mouse_x - Orig_pos_x;
					y[tri[Current_face][0]] += Mouse_y - Orig_pos_y;
					x[tri[Current_face][1]] += Mouse_x - Orig_pos_x;
					y[tri[Current_face][1]] += Mouse_y - Orig_pos_y;
					x[tri[Current_face][2]] += Mouse_x - Orig_pos_x;
					y[tri[Current_face][2]] += Mouse_y - Orig_pos_y;
					Orig_pos_x = Mouse_x;
					Orig_pos_y = Mouse_y;
				}
			} else {
				if (Vert_mode == 1) {
					Current_face = get_closest_face(Mouse_x, Mouse_y);
					Orig_pos_x = Mouse_x;
					Orig_pos_y = Mouse_y;
				}
				if (Vert_mode==0) {
					Current_point = get_closest(Mouse_x, Mouse_y);
					mouse_set_pos(x[Current_point], y[Current_point]);
				}
				mdflag = TRUE;
			}
		}
		if ( mouse_up_count(LOWEST_MOUSE_BUTTON)) {
			//Current_point = -1;
			//Current_face = -1;
			mdflag = FALSE;
		}

		if ( mouse_up_count(MOUSE_RIGHT_BUTTON) ) {
			if (Vert_mode==0) {
				Current_point = add_vert(Mouse_x, Mouse_y);
			} else if (Vert_mode==1) {
				if ((num_tris<MAX_TRIS-1)) { 
					tri[num_tris][Which_vert] = get_closest(Mouse_x, Mouse_y);
					Which_vert++;
					if (Which_vert>2) {
						Which_vert = 0;
						num_tris++;
					}
				}
			}
		}
		}
		controls_read_all(&ci, flFrametime );
		physics_read_flying_controls( &ViewerOrient, &ViewerPhysics, &ci, flFrametime );
		physics_sim(&ViewerPos, &ViewerOrient, &ViewerPhysics, flFrametime );		

		render_frame();

		t2 = timer_get_fixed_seconds();
		if ( t2 > t1 )	{
			flFrametime = f2fl(t2 - t1);
		}

		t1 = t2;
	}

	nebedit_close();

	return 0;
}

// Stub functions and variables.
// These do nothing but are needed to prevent link errors.
void demo_set_playback_filter() {}

void freespace_menu_background()
{
	gr_reset_clip();
	gr_clear();
}

int game_check_key()
{
	return key_inkey();
}

int game_poll()
{
	return key_inkey();
}

vector Camera_pos;
vector Dead_player_last_vel;
// end stubs
