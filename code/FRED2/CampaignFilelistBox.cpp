/*
 * Copyright (C) Volition, Inc. 1999.  All rights reserved.
 *
 * All source code herein is the property of Volition, Inc. You may not sell 
 * or otherwise commercially exploit the source or things you created based on the 
 * source.
 *
*/

// CampaignFilelistBox.cpp : implementation file
//

#include "stdafx.h"
#include "fred.h"
#include "freespace.h"
#include "CampaignFilelistBox.h"
#include "CampaignTreeWnd.h"
#include "MissionCampaign.h"
#include "MissionParse.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// campaign_filelist_box

campaign_filelist_box::campaign_filelist_box()
{
}

campaign_filelist_box::~campaign_filelist_box()
{
}


BEGIN_MESSAGE_MAP(campaign_filelist_box, CListBox)
	//{{AFX_MSG_MAP(campaign_filelist_box)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// campaign_filelist_box message handlers

void campaign_filelist_box::initialize()
{
	int i, z;
	char wild_card[256];
	WIN32_FIND_DATA file_data;
	HANDLE h;
	mission a_mission;

	ResetContent();
	memset(wild_card, 0, 256);
	strcpy(wild_card, NOX("*"));
	strcat(wild_card, FS_MISSION_FILE_EXT);
	h = FindFirstFile(wild_card, &file_data);
	if (h != INVALID_HANDLE_VALUE) {
		do {

			// make a call to get the mission info for this mission.  Passing a misison as the second
			// parameter will prevent The_mission from getting overwritten.
			get_mission_info( file_data.cFileName, &a_mission );

			// only add missions of the appropriate type to the file listbox
			if ( (Campaign.type == CAMPAIGN_TYPE_SINGLE) && (a_mission.game_type & (MISSION_TYPE_SINGLE|MISSION_TYPE_TRAINING)) )
				AddString(file_data.cFileName);
			else if ( (Campaign.type == CAMPAIGN_TYPE_MULTI_COOP) && (a_mission.game_type & MISSION_TYPE_MULTI_COOP) )
				AddString(file_data.cFileName);
			else if ( (Campaign.type == CAMPAIGN_TYPE_MULTI_TEAMS) && (a_mission.game_type & MISSION_TYPE_MULTI_TEAMS) )
				AddString(file_data.cFileName);

		} while (FindNextFile(h, &file_data));

		FindClose(h);
	}

	for (i=0; i<Campaign.num_missions; i++) {
		z = FindString(-1, Campaign.missions[i].name);
		if (z != LB_ERR) {
			DeleteString(z);  // take out all missions already in the campaign
			i--;  // recheck for name just in case there are two (should be impossible but can't be sure)
		}
	}
}
