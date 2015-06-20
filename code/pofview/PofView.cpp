/*
 * Copyright (C) Volition, Inc. 1999.  All rights reserved.
 *
 * All source code herein is the property of Volition, Inc. You may not sell 
 * or otherwise commercially exploit the source or things you created based on the 
 * source.
 *
*/

// PofView.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "PofView.h"

#include "MainFrm.h"
#include "ChildFrm.h"
#include "PofViewDoc.h"
#include "PofViewView.h"

#include "psTypes.h"
#include "cfile.h"
#include "palman.h"
#include "2d.h"
#include "3d.h"
#include "model.h"
#include "vecmat.h"
#include "floating.h"
#include "key.h"
#include "timer.h"
#include "mouse.h"
#include "BmpMan.h"
#include "SystemVars.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

int Pofview_running = 1;

/////////////////////////////////////////////////////////////////////////////
// CPofViewApp

BEGIN_MESSAGE_MAP(CPofViewApp, CWinApp)
	//{{AFX_MSG_MAP(CPofViewApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPofViewApp construction

CPofViewApp::CPofViewApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CPofViewApp object

CPofViewApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CPofViewApp initialization

BOOL CPofViewApp::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(
		IDR_POFTYPE,
		RUNTIME_CLASS(CPofViewDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CPofViewView));
	AddDocTemplate(pDocTemplate);

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;

	// Enable drag/drop open
	m_pMainWnd->DragAcceptFiles();

	// setup the fred exe directory so CFILE can init properly
	/*
	char *c = GetCommandLine();
	Assert(c != NULL);
	char *tok = strtok(c, " ");
	Assert(tok != NULL);	
	*/

	outwnd_init();
	timer_init();
	cfile_init(__argv[0]);
	palette_load_table( "gamepalette1-01" );
	gr_init(GR_640, GR_SOFTWARE, 8, 640, 480);
	gr_set_gamma(2.0f);
	key_init();
	mouse_init();
	gr_init_font( "font01.vf" );
	m_timer = timer_get_milliseconds();
	model_init();

	// Enable DDE Execute open
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// DON'T display a new MDI child window during startup!!!
	if ( cmdInfo.m_nShellCommand == CCommandLineInfo::FileNew )	{
		cmdInfo.m_nShellCommand = CCommandLineInfo::FileNothing;
	}

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The main window has been initialized, so show and update it.
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CPofViewApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CPofViewApp commands


CPofViewView * GetView()
{
  CMDIChildWnd * pChild =
       ((CMDIFrameWnd*)(AfxGetApp()->m_pMainWnd))->MDIGetActive();

  if ( !pChild )
     return NULL;

  CView * pView = pChild->GetActiveView();

  if ( !pView )
     return NULL;

  // Fail if view is of wrong kind
  // (this could occur with splitter windows, or additional
  // views on a single document
  if ( ! pView->IsKindOf( RUNTIME_CLASS(CPofViewView) ) )
     return NULL;

  return (CPofViewView *) pView;
}


// Stuff for showing ship thrusters. 
typedef struct thrust_anim {
	int	num_frames;
	int	first_frame;
	float time;				// in seconds
} thrust_anim;

#define NUM_THRUST_ANIMS					6
#define THRUST_ANIM_NORMAL					0
#define THRUST_ANIM_AFTERBURNER			1
#define THRUST_ANIM_GLOW_NORMAL			2
#define THRUST_ANIM_GLOW_AFTERBURNER	3

static thrust_anim	Thrust_anims[NUM_THRUST_ANIMS];
extern char Thrust_anim_names[NUM_THRUST_ANIMS][MAX_FILENAME_LEN];

static int Thrust_anim_inited = 0;

int	shipp_thruster_bitmap = -1;					// What frame the current thruster bitmap is at for this ship
float	shipp_thruster_frame = 0.0f;					// Used to keep track of which frame the animation should be on.

int	shipp_thruster_glow_bitmap = -1;					// What frame the current thruster bitmap is at for this ship
float	shipp_thruster_glow_frame = 0.0f;					// Used to keep track of which frame the animation should be on.
float	shipp_thruster_glow_noise = 1.0f;

// loads the animations for ship's afterburners
void init_thrusters()
{
	int			fps, i;
	thrust_anim	*ta;

	if ( Thrust_anim_inited == 1 )
		return;

	for ( i = 0; i < NUM_THRUST_ANIMS; i++ ) {
		ta = &Thrust_anims[i];
		//if ( i < 2 )	{
			ta->first_frame = bm_load_animation(Thrust_anim_names[i],  &ta->num_frames, &fps);
			if ( ta->first_frame == -1 ) {
				Error(LOCATION,"Error loading animation file: %s\n",Thrust_anim_names[i]);
				return;
			}
			Assert(fps != 0);
			ta->time = i2fl(ta->num_frames)/fps;
		//} else {
		//	ta->first_frame = bm_load(Thrust_anim_names[i] );
		//	ta->num_frames = NOISE_NUM_FRAMES;
		//	fps = 15;
		//	if ( ta->first_frame == -1 ) {
		//		Error(LOCATION,"Error loading bitmap file: %s\n",Thrust_anim_names[i]);
		//		return;
		//	}
		//	Assert(fps != 0);
		//	ta->time = i2fl(ta->num_frames)/fps;
		//}
	}

	Thrust_anim_inited = 1;
}

	// JAS - figure out which thruster bitmap will get rendered next
	// time around.  ship_render needs to have shipp_thruster_bitmap set to
	// a valid bitmap number, or -1 if we shouldn't render thrusters.
void do_thruster_frame( float thrust, int afterburner, float frametime )
{
	float rate;
	int framenum;
	thrust_anim *the_anim;

	if ( !Thrust_anim_inited )	init_thrusters();

	if ( afterburner )	{
		the_anim = &Thrust_anims[THRUST_ANIM_AFTERBURNER];
		rate = 1.2f;		// go at 1.2x faster when afterburners on
	} else {
		the_anim = &Thrust_anims[THRUST_ANIM_NORMAL];
		// If thrust at 0, go at half as fast, full thrust; full framerate
		// so set rate from 0.5 to 1.0, depending on thrust from 0 to 1
		rate = 0.5f + thrust / 2.0f;
	}

	shipp_thruster_frame += frametime * rate;

	// Sanity checks
	if ( shipp_thruster_frame < 0.0f )	shipp_thruster_frame = 0.0f;
	if ( shipp_thruster_frame > 100.0f ) shipp_thruster_frame = 0.0f;

	if ( shipp_thruster_frame > the_anim->time )	{
		shipp_thruster_frame -= the_anim->time;
	}
	framenum = fl2i( (shipp_thruster_frame*the_anim->num_frames) / the_anim->time );
	if ( framenum < 0 ) framenum = 0;
	if ( framenum >= the_anim->num_frames ) framenum = the_anim->num_frames-1;
	
	// Get the bitmap for this frame
	shipp_thruster_bitmap = the_anim->first_frame + framenum;

//	mprintf(( "TF: %.2f\n", shipp_thruster_frame ));


	// Do for glows

	if ( afterburner )	{
		the_anim = &Thrust_anims[THRUST_ANIM_GLOW_AFTERBURNER];
		rate = 1.2f;		// go at 1.2x faster when afterburners on
	} else {
		the_anim = &Thrust_anims[THRUST_ANIM_GLOW_NORMAL];
		// If thrust at 0, go at half as fast, full thrust; full framerate
		// so set rate from 0.5 to 1.0, depending on thrust from 0 to 1
		rate = 0.5f + thrust / 2.0f;
	}

	shipp_thruster_glow_frame += frametime * rate;

	// Sanity checks
	if ( shipp_thruster_glow_frame < 0.0f )	shipp_thruster_glow_frame = 0.0f;
	if ( shipp_thruster_glow_frame > 100.0f ) shipp_thruster_glow_frame = 0.0f;

	if ( shipp_thruster_glow_frame > the_anim->time )	{
		shipp_thruster_glow_frame -= the_anim->time;
	}
	framenum = fl2i( (shipp_thruster_glow_frame*the_anim->num_frames) / the_anim->time );
	if ( framenum < 0 ) framenum = 0;
	if ( framenum >= the_anim->num_frames ) framenum = the_anim->num_frames-1;
	
	// Get the bitmap for this frame
	shipp_thruster_glow_bitmap = the_anim->first_frame;
	shipp_thruster_glow_noise = Noise[framenum];

//	mprintf(( "TF: %.2f\n", shipp_thruster_frame ));

}


int pofview_focus=0;
float flFrametime;

float model_thrust = 0.0f;
int model_afterburner = 0;

BOOL CPofViewApp::OnIdle(LONG lCount)
{
	CWinApp::OnIdle(lCount);

	CPofViewView* CurrentView;
	CDC* pDC;
	int tmp_time = timer_get_milliseconds();
	float frame_time;
	int k = key_inkey();

	frame_time = ((float)(tmp_time-m_timer)) / 1000.0f;
	flFrametime = frame_time;

	m_timer = tmp_time;

	if (pofview_focus<1) return FALSE;

	CurrentView = GetView();
	if ( !CurrentView ) return TRUE;

	do_thruster_frame( model_thrust, model_afterburner, flFrametime );

	CurrentView->MoveViewer(frame_time,TRUE,k);

	pDC = CurrentView->GetDC();
	if ( !pDC ) return TRUE;

	CurrentView->OnDraw(pDC);

	CurrentView->ReleaseDC(pDC);

	return TRUE;
}

int CPofViewApp::ExitInstance() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CWinApp::ExitInstance();
}
