/*
 * Copyright (C) Volition, Inc. 1999.  All rights reserved.
 *
 * All source code herein is the property of Volition, Inc. You may not sell 
 * or otherwise commercially exploit the source or things you created based on the 
 * source.
 *
*/

/*
 * $Logfile: /Freespace2/code/Ship/ShipContrails.h $
 * $Revision: 2 $
 * $Date: 11/14/98 5:33p $
 * $Author: Dave $
 *
 * all sorts of cool stuff about ships
 *
 * $Log: /Freespace2/code/Ship/ShipContrails.h $
 * 
 * 2     11/14/98 5:33p Dave
 * Lots of nebula work. Put in ship contrails.
 * 
 * 1     11/14/98 3:40p Dave
 * 
 * 1     11/13/98 3:28p Dave
 * 
 * 
 * $NoKeywords: $
 */

#ifndef _FREESPACE2_SHIP_CONTRAIL_HEADER_FILE
#define _FREESPACE2_SHIP_CONTRAIL_HEADER_FILE

// ----------------------------------------------------------------------------------------------
// CONTRAIL DEFINES/VARS
//

// prototypes
struct ship;

// ----------------------------------------------------------------------------------------------
// CONTRAIL FUNCTIONS
//

// call during level initialization
void ct_level_init();

// call during level shutdown
void ct_level_close();

// call when a ship is created to initialize its contrail stuff
void ct_ship_create(ship *shipp);

// call when a ship is deleted to free up its contrail stuff
void ct_ship_delete(ship *shipp);

// call each frame for processing a ship's contrails
void ct_ship_process(ship *shipp);

#endif