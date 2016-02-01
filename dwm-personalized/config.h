/* See LICENSE file for copyright and license details. */
#include <X11/XF86keysym.h>

/* appearance */
static const char *fonts[] = {
	"inconsolata:size=8"
};
static const char dmenufont[]       = "inconsolata:size=8";
static const char normbordercolor[] = "#444444";
static const char normbgcolor[]     = "#222222";
static const char normfgcolor[]     = "#bbbbbb";
static const char selbordercolor[]  = "#005577";
static const char selbgcolor[]      = "#005577";
static const char selfgcolor[]      = "#eeeeee";
static const unsigned int borderpx  = 0;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */

/* tagging */
static const char *tags[] = { "cmd", "www", "irc", "etc" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class       instance       title       tags mask     isfloating   monitor */
	//cmd
	{ "st-256color", "st-256color", NULL,       1,            False,       -1 },
	//www
	{ "chromium",    NULL,          NULL,       1 << 1,       False,       -1 },
	{ "Firefox",     NULL,          NULL,       1 << 1,       False,       -1 },
	{ "qutebrowser", "qutebrowser", NULL,       1 << 1,       False,       -1 },
	//irc
	{ "ircterm",     NULL,          NULL,       1 << 2,       False,       -1 },
	//etc
	{ "Client.pyw",  NULL,          NULL,       1 << 3,       False,       -1 },
	{ "steam",       "steam",       NULL,       1 << 3,       False,       -1 }, // Big Picture Mode
	{ "Steam",       "Steam",       NULL,       1 << 3,       False,       -1 },
	{ "Steam",       "Steam",       "Friends",  1 << 3,       False,       -1 },
	{ "xfreerdp",    "xfreerdp",    NULL,       1 << 3,       False,       -1 },
	{ "Okular",      "okular",      NULL,       1 << 3,       False,       -1 },
	//all
	{ "mpv",         NULL,          NULL,      ~0,            True,        -1 },
	{ "Sxiv",        NULL,          NULL,      ~0,            True,        -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

#include "column.c"
#include "deck.c"
#include "gaplessgrid.c"
#include "horizgrid.c"
#include "htile.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[M]",      monocle }, /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[]=",      tile },    
	{ "TTT",      htile },
	{ "HHH",      horizgrid },
	{ "###",      gaplessgrid },
	{ "[]_",      deck },
	{ "||=",      col },
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
static const char *clipmenu[] = { "clipmenu", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *clipsync[] = { "clipsync.sh", NULL };
static const char *dmenucmd[] = { "run-recent", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *lightdown[]= { "bright_adjust.sh", "dec", NULL };
static const char *lightup[]  = { "bright_adjust.sh", "inc", NULL };
static const char *mute[]     = { "amixer", "-q", "sset", "Master", "toggle", NULL };
static const char *newbg[]    = { "systemctl", "--user", "start", "feh-wallpaper.service", NULL };
static const char *openurl[]  = { "browser.sh", NULL };
static const char *rotate[]   = { "rotate.sh", NULL };
static const char *scrot[]    = { "scrot", NULL };
static const char *termcmd[]  = { "st", "-c", "st-256color", "-e", "dvtm", "-M", NULL };
static const char *trans[]    = { "trans-exempt.sh", NULL };
static const char *voldown[]  = { "vol_adjust.sh", "-", NULL };
static const char *volup[]    = { "vol_adjust.sh", "+", NULL };

static Key keys[] = {
	/* modifier           key                       function        argument */
	{ 0,                  XF86XK_AudioMute,         spawn,          {.v = mute } },
	{ 0,                  XF86XK_AudioLowerVolume,  spawn,          {.v = voldown } },
	{ 0,                  XF86XK_AudioRaiseVolume,  spawn,          {.v = volup } },
	{ 0,                  XF86XK_Display,           spawn,          {.v = rotate } },
	{ 0,                  XF86XK_MonBrightnessDown, spawn,          {.v = lightdown } },
	{ 0,                  XF86XK_MonBrightnessUp,   spawn,          {.v = lightup } },
	{ ControlMask,        XK_Insert,                spawn,          {.v = clipsync } },
	{ ControlMask,        XK_grave,                 spawn,          {.v = clipmenu } },
	{ MODKEY,             XK_Insert,                spawn,          {.v = scrot } },
	{ MODKEY,             XK_e,                     spawn,          {.v = trans } },
	{ MODKEY,             XK_p,                     spawn,          {.v = dmenucmd } },
	{ MODKEY,             XK_u,                     spawn,          {.v = openurl } },
	{ MODKEY|ControlMask, XK_r,                     spawn,          {.v = newbg } },
	{ MODKEY|ShiftMask,   XK_Return,                spawn,          {.v = termcmd } },
	{ MODKEY,             XK_space,                 setlayout,      {0} },
	{ MODKEY,             XK_m,                     setlayout,      {.v = &layouts[0]} },
	{ MODKEY,             XK_f,                     setlayout,      {.v = &layouts[1]} },
	{ MODKEY,             XK_t,                     setlayout,      {.v = &layouts[2]} },
        { MODKEY,             XK_b,                     setlayout,      {.v = &layouts[3]} },
        { MODKEY,             XK_g,                     setlayout,      {.v = &layouts[4]} },
        { MODKEY|ShiftMask,   XK_g,                     setlayout,      {.v = &layouts[5]} },
        { MODKEY|ShiftMask,   XK_d,                     setlayout,      {.v = &layouts[6]} },
        { MODKEY,             XK_c,                     setlayout,      {.v = &layouts[7]} },
	{ MODKEY,             XK_Tab,                   view,           {0} },
	{ MODKEY,             XK_0,                     view,           {.ui = ~0 } },
	{ MODKEY,             XK_Return,                zoom,           {0} },
	{ MODKEY,             XK_k,                     focusstack,     {.i = -1 } },
	{ MODKEY,             XK_j,                     focusstack,     {.i = +1 } },
	{ MODKEY,             XK_comma,                 focusmon,       {.i = -1 } },
	{ MODKEY,             XK_period,                focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,   XK_comma,                 tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,   XK_period,                tagmon,         {.i = +1 } },
	{ MODKEY,             XK_h,                     setmfact,       {.f = -0.05} },
	{ MODKEY,             XK_l,                     setmfact,       {.f = +0.05} },
	{ MODKEY,             XK_d,                     incnmaster,     {.i = -1 } },
	{ MODKEY,             XK_i,                     incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,   XK_0,                     tag,            {.ui = ~0 } },
	{ MODKEY,             XK_slash,                 togglebar,      {0} },
	{ MODKEY|ShiftMask,   XK_space,                 togglefloating, {0} },
	{ MODKEY|ShiftMask,   XK_c,                     killclient,     {0} },
	{ MODKEY|ShiftMask,   XK_q,                     quit,           {0} },
	TAGKEYS(              XK_1,                      0)
	TAGKEYS(              XK_2,                      1)
	TAGKEYS(              XK_3,                      2)
	TAGKEYS(              XK_4,                      3)
	TAGKEYS(              XK_5,                      4)
	TAGKEYS(              XK_6,                      5)
	TAGKEYS(              XK_7,                      6)
	TAGKEYS(              XK_8,                      7)
	TAGKEYS(              XK_9,                      8)
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
//	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

