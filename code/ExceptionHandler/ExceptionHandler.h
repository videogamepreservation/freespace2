/*
 * Copyright (C) Volition, Inc. 1999.  All rights reserved.
 *
 * All source code herein is the property of Volition, Inc. You may not sell 
 * or otherwise commercially exploit the source or things you created based on the 
 * source.
 *
*/

/*
 * $Logfile: /Freespace2/code/ExceptionHandler/ExceptionHandler.h $
 * $Revision: 1 $
 * $Date: 6/29/99 7:42p $
 * $Author: Dave $
 *
 * Header file for program exception handling
 *
 * $Log: /Freespace2/code/ExceptionHandler/ExceptionHandler.h $
 * 
 * 1     6/29/99 7:42p Dave
 * 
 * 2     1/18/99 4:34p Allender
 * added the exception handler routines from Game Developer for structured
 * exception handling in vsdk code
 *
 * $NoKeywords: $
 */

#pragma once		// Include this file only once

#ifndef __EXCEPTION_HANDLER_H
#define __EXCEPTION_HANDLER_H

// --------------------
//
// Defines
//
// --------------------


// --------------------
//
// Enumerated types
//
// --------------------


// --------------------
//
// Structures
//
// --------------------

// this is a forward declaration so we don't need to include windows.h

typedef struct _EXCEPTION_POINTERS EXCEPTION_POINTERS, *PEXCEPTION_POINTERS;

// --------------------
//
// Classes
//
// --------------------


// --------------------
//
// Variables
//
// --------------------


// --------------------
//
// Prototypes
//
// --------------------

int __cdecl RecordExceptionInfo(PEXCEPTION_POINTERS data, const char *Message);

// --------------------
//
// Helper Macros
//
// --------------------


#endif // __EXCEPTION_HANDLER_H
