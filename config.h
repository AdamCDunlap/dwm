/* See LICENSE file for copyright and license details. */

/* appearance */
static const char font[]            = "-*-terminus-medium-r-*-*-16-*-*-*-*-*-*-*";
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const Bool showbar           = True;     /* False means no bar */
static const Bool topbar            = False;     /* False means bottom bar */

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor    hideborder */
	{ "Stopwatch",NULL,       NULL,       0,            True,        -1,        False },
	{ "Chromium" ,NULL,       NULL,       1,            False,       -1,        True },
};

/* layout(s) */
static const float mfact      = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster      = 1;    /* number of clients in master area */
static const Bool resizehints = False; /* True means respect size hints in tiled resizals */

#include "bstack.c"
#include "bstackhoriz.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[M]",      monocle }, /* first entry is default */
	{ "[]=",      tile },    
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      comboview,      {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      combotag,       {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }


static const char *dmenucmd[] = { "dmenu_run", "-fn", font, "-nb", colors[0][2], "-nf", colors[0][1], "-sb", colors[1][2], "-sf", colors[1][1], NULL };
static const char *rootdmenucmd[] = { "dmenu_run_root", "-fn", font, "-nb", "#204a87", "-nf", "#ffffff", "-sb", colors[1][2], "-sf", colors[1][1], NULL };
static const char *termcmd[]  = { "terminal", NULL };
static const char *termcmdNoTransparency[]  = { "terminal", "+tr", NULL };
static const char *internetcmd[]  = { "chromium", NULL };
static const char *calculatecmd[] = { "calculate", NULL };
static const char *changebgcmd[] = {"changebg", NULL };
static const char *changebgrefreshcmd[] = {"changebg", "-r", NULL };
static const char *invertdisplay[] = {"inv", NULL };
static const char *hibernatecmd[] = {"systemctl", "hibernate", NULL };
static const char *suspendcmd[] = {"mysuspend", NULL };
static const char *screenshotscrcmd[] = {"screenshot", "scr", NULL };
static const char *screenshotareacmd[] = {"screenshot", "area", NULL };
static const char *vimcmd[] = {"terminal", "-e", "vim", NULL};
static const char *xkillcmd[] = {"xkill", NULL};
static const char *selectumountcmd[] = {"select-umount", NULL};
static const char *selectmountcmd[] = {"select-mount", NULL};
static const char *askfortaskcmd[] = {"askfortask", NULL};
static const char *mancmd[] = {"askforman", NULL};

static Key keys[] = {
	/* modifier         key        function        argument */
    { 0,                XK_Pause,       spawn,          {.v = suspendcmd } },
    { ControlMask,      XK_Pause,       spawn,          {.v = hibernatecmd } },

    { 0,                XK_Scroll_Lock, spawn,          {.v = invertdisplay } },
    { ShiftMask,        XK_Scroll_Lock, spawn,          {.v = changebgcmd} }, 
    { MODKEY,           XK_Scroll_Lock, spawn,          {.v = changebgrefreshcmd} },
    { MODKEY,           XK_v,           spawn,          {.v = vimcmd} },

    { MODKEY,           XK_x,           spawn,          {.v = xkillcmd} },
    { MODKEY,           XK_u,           spawn,          {.v = selectumountcmd} },
    { MODKEY,           XK_o,           spawn,          {.v = selectmountcmd} },
    { MODKEY,           XK_n,           spawn,          {.v = mancmd} },
    
    { 0,                XK_Print,       spawn,          {.v = screenshotscrcmd} },
    { ShiftMask,        XK_Print,       spawn,          {.v = screenshotareacmd} },

	{ MODKEY,           XK_p,           spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask, XK_p,           spawn,          {.v = rootdmenucmd } },
	{ MODKEY|ShiftMask, XK_Return,      spawn,          {.v = termcmd } },
	{ MODKEY|ControlMask|ShiftMask, XK_Return,      spawn,          {.v = termcmdNoTransparency } },
	{ MODKEY|ShiftMask, XK_i,           spawn,          {.v = internetcmd } },
    { MODKEY,           XK_c,           spawn,          {.v = calculatecmd } },
	{ MODKEY,           XK_b,           togglebar,      {0} },
	{ MODKEY,           XK_j,           focusstack,     {.i = +1 } },
	{ MODKEY,           XK_k,           focusstack,     {.i = -1 } },
	{ MODKEY,           XK_i,           incnmaster,     {.i = +1 } },
	{ MODKEY,           XK_d,           incnmaster,     {.i = -1 } },
	{ MODKEY,           XK_h,           setmfact,       {.f = -0.05} },
	{ MODKEY,           XK_l,           setmfact,       {.f = +0.05} },
	{ MODKEY,           XK_Return,      zoom,           {0} },
	/*{ MODKEY,           XK_Tab,         view,           {0} },*/
	{ MODKEY|ShiftMask, XK_c,           killclient,     {0} },
	{ MODKEY,           XK_m,           setlayout,      {.v = &layouts[0]} },
	{ MODKEY,           XK_t,           setlayout,      {.v = &layouts[1]} },
	{ MODKEY,           XK_f,           setlayout,      {.v = &layouts[2]} },
    { MODKEY,           XK_s,           setlayout,      {.v = &layouts[3]} },
    { MODKEY,           XK_a,           setlayout,      {.v = &layouts[4]} },
/*	{ MODKEY,           XK_space,       setlayout,      {0} },*/
	{ MODKEY|ShiftMask, XK_space,       togglefloating, {0} },
	{ MODKEY,           XK_0,           view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask, XK_0,           tag,            {.ui = ~0 } },
	{ MODKEY,           XK_comma,       focusmon,       {.i = -1 } },
	{ MODKEY,           XK_period,      focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask, XK_comma,       tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask, XK_period,      tagmon,         {.i = +1 } },
	TAGKEYS(            XK_1,                           0)
	TAGKEYS(            XK_2,                           1)
	TAGKEYS(            XK_3,                           2)
	TAGKEYS(            XK_4,                           3)
	TAGKEYS(            XK_5,                           4)
	TAGKEYS(            XK_6,                           5)
	TAGKEYS(            XK_7,                           6)
	TAGKEYS(            XK_8,                           7)
	TAGKEYS(            XK_9,                           8)
	{ MODKEY|ShiftMask, XK_q,           quit,           {0} },
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	/*{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },*/
	/*{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },*/
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = askfortaskcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	/*{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },*/
	{ ClkClientWin,         MODKEY,         Button2,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
