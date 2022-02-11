/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel size of windows */
static const unsigned int gappx     = 5;        /* gaps size between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int swallowfloating    = 1;        /* 1 means swallow floating windows by default */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     	/* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=10", "fontawesome:size=10" };	/* Fonts */
static const char dmenufont[]       = "monospace:size=10";	/* background color */
static const char col_gray1[]       = "#222222";		/* inactive window border color */
static const char col_gray2[]       = "#444444";		/* font color */
static const char col_gray3[]       = "#bbbbbb";		/* current tag and current window font color */
static const char col_gray4[]       = "#eeeeee";		/* Top bar second color (blue) and active window border color */
static const char col_cyan[]        = "#BB395B";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "", "", "", "", "", "", "", "", "" };	/* tag names (upper left) */

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class		instance	title		tags mask	isfloating	isterminal	noswallow	monitor */
	{ "Gimp",     		NULL,       	NULL,       	1 << 6,         0,           					-1 },
	{ "firefox",  		NULL,       	NULL,       	2,       	0,           	0,		0,		-1 },
	{ "Brave",    		NULL,       	NULL,       	1 << 1,       	0,           	0,         	0,        	-1 },
	{ "Chromium", 		NULL,	  	NULL,       	1 << 1,       	0,           	0,         	0,        	-1 },
	{ "VirtualBox", 	NULL,	  	NULL,       	1 << 4,       	0,           	0,         	0,        	-1 },
	{ "St",  		NULL,       	NULL,       	0,            	0,           	1,         	0,        	-1 },
	{ "Vivaldi-stable",	NULL,       	NULL,         	1,            	0,           	0,         	0,        	-1 },
	{ "Steam",    		NULL,       	NULL,       	1 << 2,         0,           	0,         	0,        	-1 },
	{ "dissenter",  	NULL,       	NULL,       	1 << 3,         0,           	0,         	0,        	-1 },
	{ "Lutris",  		NULL,       	NULL,       	1 << 3,         0,           	0,         	0,        	-1 },
	{ "heroic",  		NULL,       	NULL,       	1 << 3,         0,           	0,         	0,        	-1 },
	{ NULL,  		NULL,       	"discord",      1 << 8,         0,           	0,         	0,        	-1 },
	{ NULL,  		NULL,       	"Friends List", 1 << 8,         0,           	0,         	0,        	-1 },
	{ NULL,       		NULL,       	"Event Tester", 0,            	0,           	0,         	1,        	-1 },
	{ "Authenticate",       NULL,       	NULL,    	~0,        	True,    					-1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL }; /* launches dmenu */
static const char *termcmd[]  = { "st", NULL };		/* sets st as the default terminal */

#include <X11/XF86keysym.h>
#include "shiftview.c"
#include "movestack.c"
static char *endx[] = { "/bin/sh", "-c", "endx", "externalpipe", NULL };
static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY|ShiftMask,		XK_Escape, spawn,	   SHCMD("xkill") },
	{ MODKEY,			XK_BackSpace,	spawn,	   SHCMD("sysact") },
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY,	                XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,		XK_Return, spawn,	   SHCMD("pcmanfm") },
	{ MODKEY,			XK_w,	   spawn,	   SHCMD("vivaldi-stable --enable-features=OverlayScrollbar,OverlayScrollbarFlasgAfterAnyScrollUpdate,OverlayScrollbarFlashWhenMouseEnter --process-per-site -enable-law-res-tiling") },
	{ MODKEY|ShiftMask,		XK_F11,	   spawn,	   SHCMD("chromium --app=https://discord.com/app --class=ICE-SSB-discord --user-data-dir=/home/mastermind/.config/discordium") },
	{ MODKEY,			XK_e,	   spawn,	   SHCMD("dmenuunicode") },
	{ MODKEY|ShiftMask,		XK_m,	   spawn,	   SHCMD("pamixer -t") },
	{ MODKEY,                       XK_b,      togglebar,      {0} },

	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },

	{ MODKEY|ShiftMask,             XK_j,      movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      movestack,      {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_Right,  movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_Left,   movestack,      {.i = -1 } },

	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_u,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_z,	   zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,			XK_t,	   setlayout,	   {.v = &layouts[0]} }, /* tile */
	{ MODKEY|ShiftMask,		XK_t,	   setlayout,	   {.v = &layouts[1]} }, /* floating */
	{ MODKEY,			XK_f,	   togglefullscr,  {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -1 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 0  } },
	{ MODKEY,              		XK_g,      shiftview,  	   { .i = +1 } },
	{ MODKEY|ShiftMask,             XK_g,      shiftview,      { .i = -1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY,	                XK_q,      killclient,     {0} },
	{ MODKEY|ShiftMask,		XK_q, 	   spawn,	   SHCMD("kill -9 `xdotool getwindowfocus getwindowpid`") },
	{ ShiftMask,			XK_Print,  spawn,	   SHCMD("maimpick") },
	{ MODKEY,			XK_Print,  spawn,	   SHCMD("dmenurecord") },
	{ MODKEY|ShiftMask,		XK_Print,  spawn,	   SHCMD("dmenurecord kill") },


	{ 0, XF86XK_Search,		spawn,			   SHCMD("chromium") },
	{ 0, XF86XK_Explorer,		spawn,			   SHCMD("st -e lf") },
	{ 0, XF86XK_AudioMute,		spawn,			   SHCMD("pamixer -t") },
	{ 0, XF86XK_AudioRaiseVolume,	spawn,	   		   SHCMD("pamixer --allow-boost -i 5") },
	{ 0, XF86XK_AudioLowerVolume,	spawn,			   SHCMD("pamixer --allow-boost -d 5") },
	{ 0, XF86XK_AudioRewind,	spawn,			   SHCMD("mpc seek -10") },
	{ 0, XF86XK_AudioForward,	spawn,			   SHCMD("mpc seek +10") },
	{ 0, XF86XK_AudioMedia,		spawn,		   	   SHCMD("st -e ncmpcpp") },
	{ 0, XF86XK_AudioMicMute,	spawn,			   SHCMD("pactl set-source-mute @DEFAULT_SOURCE@ toggle") },
	{ 0, XF86XK_PowerOff,		spawn,			   SHCMD("sysact") },
	/* { 0, XF86XK_Calculator,		spawn,		SHCMD(TERMINAL " -e bc -l") }, */
	{ 0, XF86XK_Calculator,		spawn,			   SHCMD("pactl set-source-mute @DEFAULT_SOURCE@ toggle") },
	{ 0, XF86XK_Sleep,		spawn,			   SHCMD("sudo -A zzz") },
	{ 0, XF86XK_HomePage,		spawn,			   SHCMD("brave") },
	{ 0, XF86XK_ScreenSaver,	spawn,			   SHCMD("slock & xset dpms force off; mpc pause; pauseallmpv") },
	{ 0, XF86XK_TaskPane,		spawn,			   SHCMD("st -e htop") },
	{ 0, XF86XK_Mail,		spawn,			   SHCMD("dissenter-browser") },
	{ 0, XF86XK_MyComputer,		spawn,			   SHCMD("st -e lf /") },
	/* { 0, XF86XK_Battery,		spawn,			   SHCMD("") }, */
	{ 0, XF86XK_Launch1,		spawn,			   SHCMD("xset dpms force off") },
	{ 0, XF86XK_TouchpadToggle,	spawn,			   SHCMD("(synclient | grep 'TouchpadOff.*1' && synclient TouchpadOff=0) || synclient TouchpadOff=1") },
	{ 0, XF86XK_TouchpadOff,	spawn,			   SHCMD("synclient TouchpadOff=1") },
	{ 0, XF86XK_TouchpadOn,		spawn,		 	   SHCMD("synclient TouchpadOff=0") },
	{ 0, XF86XK_MonBrightnessUp,	spawn,			   SHCMD("xbacklight -inc 15") },
	{ 0, XF86XK_MonBrightnessDown,	spawn,			   SHCMD("xbacklight -dec 15") },
	{ 0, XF86XK_AudioPlay,		spawn,			   SHCMD("playerctl play-pause") },
	{ 0, XF86XK_AudioNext,		spawn,			   SHCMD("playerctl next") },
	{ 0, XF86XK_AudioPrev,		spawn,			   SHCMD("playerctl previous") },
	{ 0, XF86XK_AudioStop,		spawn,			   SHCMD("playerctl stop") },
	{ MODKEY,			XK_F3,	spawn,		   SHCMD("displayselect") },
	{ MODKEY,			XK_F4,	spawn,		   SHCMD("pavucontrol") },
	{ MODKEY,			XK_F5,	spawn,		   SHCMD("td-toggle") },
	{ MODKEY,			XK_F6,	spawn,		   SHCMD("torwrap") },
	{ MODKEY,			XK_F8,	spawn,		   SHCMD("picom-toggle") },
	{ MODKEY,			XK_F9,	spawn,		   SHCMD("dmenumount") },
	{ MODKEY,			XK_F10,	spawn,		   SHCMD("dmenuumount") },

};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

