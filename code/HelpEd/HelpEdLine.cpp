/*
 * Copyright (C) Volition, Inc. 1999.  All rights reserved.
 *
 * All source code herein is the property of Volition, Inc. You may not sell 
 * or otherwise commercially exploit the source or things you created based on the 
 * source.
 *
*/

// HelpEdLine.cpp: implementation of the HelpEdLine class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "HelpEd.h"
#include "HelpEdLine.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

HelpEdLine::HelpEdLine()
{

}

HelpEdLine::~HelpEdLine()
{

}

HelpEdLine::HelpEdLine(CPoint point_from, CPoint point_to)
{
	// intiliaze start and ending of a line
	line_start = point_from;
	line_end = point_to;
}

void HelpEdLine::Draw(CDC *pDC)
{
	// draw the line
	pDC->MoveTo(line_start);
	pDC->LineTo(line_end);
}
