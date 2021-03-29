/* See LICENSE file for copyright and license details. */

/* appearance */
#include <X11/XF86keysym.h>
static const unsigned int borderpx       = 1;   /* border pixel of windows */
static const unsigned int snap           = 32;  /* snap pixel */
static const unsigned int gappih         = 10;  /* horiz inner gap between windows */
static const unsigned int gappiv         = 10;  /* vert inner gap between windows */
static const unsigned int gappoh         = 10;  /* horiz outer gap between windows and screen edge */
static const unsigned int gappov         = 10;  /* vert outer gap between windows and screen edge */
static const int smartgaps               = 1;   /* 1 means no outer gap when there is only one window */
static const int showbar                 = 1;   /* 0 means no bar */
static const int topbar                  = 1;   /* 0 means bottom bar */
static const unsigned int systrayspacing = 0;   /* systray spacing */
static const int showsystray             = 1;   /* 0 means no systray */
/* Indicators: see patch/bar_indicators.h for options */
static int tagindicatortype              = INDICATOR_BOTTOM_BAR_SLIM;
static int tiledindicatortype            = INDICATOR_NONE;
static int floatindicatortype            = INDICATOR_BOTTOM_BAR_SLIM;
static const char *fonts[]               = { "Sarasa Mono SC Nerd:size=10" };

static char normfgcolor[]                = "#f9b4ab";
static char normbgcolor[]                = "#222222";
static char normbordercolor[]            = "#679186";
static char normfloatcolor[]             = "#db8fd9";

static char selfgcolor[]                 = "#eeeeee";
static char selbgcolor[]                 = "#679186";
static char selbordercolor[]             = "#fdebd3";
static char selfloatcolor[]              = "#005577";

static char titlenormfgcolor[]           = "#eeeeee";
static char titlenormbgcolor[]           = "#679186";
static char titlenormbordercolor[]       = "#222222";
static char titlenormfloatcolor[]        = "#db8fd9";

static char titleselfgcolor[]            = "#222222";
static char titleselbgcolor[]            = "#f9b4ab";
static char titleselbordercolor[]        = "#fdebd3";
static char titleselfloatcolor[]         = "#db8fd9";

static char tagsnormfgcolor[]            = "#aaaaaa";
static char tagsnormbgcolor[]            = "#555555";
static char tagsnormbordercolor[]        = "#444444";
static char tagsnormfloatcolor[]         = "#db8fd9";

static char tagsselfgcolor[]             = "#f9b4ab";
static char tagsselbgcolor[]             = "#222222";
static char tagsselbordercolor[]         = "#fdebd3";
static char tagsselfloatcolor[]          = "#db8fd9";

static char hidfgcolor[]                 = "#679186";
static char hidbgcolor[]                 = "#222222";
static char hidbordercolor[]             = "#005577";
static char hidfloatcolor[]              = "#f76e0c";

static char urgfgcolor[]                 = "#bbbbbb";
static char urgbgcolor[]                 = "#222222";
static char urgbordercolor[]             = "#ff0000";
static char urgfloatcolor[]              = "#db8fd9";


static const unsigned int baralpha = 0xd0;
static const unsigned int borderalpha = OPAQUE;
static const unsigned int alphas[][3] = {
	/*                       fg      bg        border     */
  // [SchemeNorm]         = { OPAQUE, baralpha, borderalpha },
	// [SchemeSel]          = { OPAQUE, baralpha, borderalpha },
  [SchemeTitleNorm]    = { OPAQUE, baralpha, borderalpha },
	// [SchemeTitleSel]     = { OPAQUE, baralpha, borderalpha },
	[SchemeTagsNorm]     = { OPAQUE, baralpha, borderalpha },
	// [SchemeTagsSel]      = { OPAQUE, baralpha, borderalpha },
	[SchemeHid]          = { OPAQUE, baralpha, borderalpha },
	[SchemeUrg]          = { OPAQUE, baralpha, borderalpha },
};

static char *colors[][ColCount] = {
	/*                       fg                bg                border                float */
  [SchemeNorm]         = { normfgcolor,      normbgcolor,      normbordercolor,      normfloatcolor },
  [SchemeSel]          = { selfgcolor,       selbgcolor,       selbordercolor,       selfloatcolor },
	[SchemeTitleNorm]    = { titlenormfgcolor, titlenormbgcolor, titlenormbordercolor, titlenormfloatcolor },
  [SchemeTitleSel]     = { titleselfgcolor,  titleselbgcolor,  titleselbordercolor,  titleselfloatcolor },
	[SchemeTagsNorm]     = { tagsnormfgcolor,  tagsnormbgcolor,  tagsnormbordercolor,  tagsnormfloatcolor },
	[SchemeTagsSel]      = { tagsselfgcolor,   tagsselbgcolor,   tagsselbordercolor,   tagsselfloatcolor },
	[SchemeHid]          = { hidfgcolor,       hidbgcolor,       hidbordercolor,       hidfloatcolor },
	[SchemeUrg]          = { urgfgcolor,       urgbgcolor,       urgbordercolor,       urgfloatcolor },
};

static const char *const autostart[] = {
  "picom", "--experimental-backends", NULL,
  "/bin/bash","-c", "/home/aaron/.local/share/dwm/scripts/dwm-status.sh ", NULL, 
  "/bin/bash","-c","/home/aaron/.local/share/dwm/scripts/tap-to-click.sh ",NULL,
  "/bin/bash","-c"," /home/aaron/.local/share/dwm/scripts/inverse-scroll.sh ",NULL,
  "/bin/bash","-c"," /home/aaron/.local/share/dwm/scripts/wp-autochange.sh ",NULL,
  "/bin/bash","-c"," /home/aaron/.local/share/dwm/scripts/dwm-get-dot.sh ",NULL,
  "/bin/bash","-c"," /home/aaron/.local/share/dwm/scripts/dwm-get-cpu.sh ",NULL,
  "nm-applet",NULL,
  "flameshot ",NULL,
  "dunst",NULL,
  // "udiskie","--smart-tray", "--automount",NULL,
  "xmodmap", "/home/aaron/.Xmodmap",NULL,
  "xcape","-e","'Mode_switch=Escape'",NULL,
	NULL /* terminate */
};



const char *spcmd1[] = {"st", "-n", "spterm", "-g", "120x34", NULL };
static Sp scratchpads[] = {
   /* name          cmd  */
   {"spterm",      spcmd1},
};

/* Tags
 * In a traditional dwm the number of tags in use can be changed simply by changing the number
 * of strings in the tags array. This build does things a bit different which has some added
 * benefits. If you need to change the number of tags here then change the NUMTAGS macro in dwm.c.
 *
 * Examples:
 *
 *  1) static char *tagicons[][NUMTAGS*2] = {
 *         [DEFAULT_TAGS] = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "A", "B", "C", "D", "E", "F", "G", "H", "I" },
 *     }
 *
 *  2) static char *tagicons[][1] = {
 *         [DEFAULT_TAGS] = { "•" },
 *     }
 *
 * The first example would result in the tags on the first monitor to be 1 through 9, while the
 * tags for the second monitor would be named A through I. A third monitor would start again at
 * 1 through 9 while the tags on a fourth monitor would also be named A through I. Note the tags
 * count of NUMTAGS*2 in the array initialiser which defines how many tag text / icon exists in
 * the array. This can be changed to *3 to add separate icons for a third monitor.
 *
 * For the second example each tag would be represented as a bullet point. Both cases work the
 * same from a technical standpoint - the icon index is derived from the tag index and the monitor
 * index. If the icon index is is greater than the number of tag icons then it will wrap around
 * until it an icon matches. Similarly if there are two tag icons then it would alternate between
 * them. This works seamlessly with alternative tags and alttagsdecoration patches.
 */
static char *tagicons[][NUMTAGS] = {
	[DEFAULT_TAGS]        ={ "➊", "➋", "➌", "➍", "➎", "➏", "➐", "➑", "➒" },
  [ALTERNATIVE_TAGS]    = { "①", "②", "③", "④", "⑤", "⑥", "⑦", "⑧", "⑨" },
	// [ALT_TAGS_DECORATION] = { "<1>", "<2>", "<3>", "<4>", "<5>", "<6>", "<7>", "<8>", "<9>" },
};


/* There are two options when it comes to per-client rules:
 *  - a typical struct table or
 *  - using the RULE macro
 *
 * A traditional struct table looks like this:
 *    // class      instance  title  wintype  tags mask  isfloating  monitor
 *    { "Gimp",     NULL,     NULL,  NULL,    1 << 4,    0,          -1 },
 *    { "Firefox",  NULL,     NULL,  NULL,    1 << 7,    0,          -1 },
 *
 * The RULE macro has the default values set for each field allowing you to only
 * specify the values that are relevant for your rule, e.g.
 *
 *    RULE(.class = "Gimp", .tags = 1 << 4)
 *    RULE(.class = "Firefox", .tags = 1 << 7)
 *
 * Refer to the Rule struct definition for the list of available fields depending on
 * the patches you enable.
 */
static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 *	WM_WINDOW_ROLE(STRING) = role
	 *	_NET_WM_WINDOW_TYPE(ATOM) = wintype
	 */
	RULE(.wintype = WTYPE "DIALOG", .isfloating = 1)
	RULE(.wintype = WTYPE "UTILITY", .isfloating = 1)
	RULE(.wintype = WTYPE "TOOLBAR", .isfloating = 1)
	RULE(.wintype = WTYPE "SPLASH", .isfloating = 1)
	RULE(.class = "Gimp", .tags = 1 << 4)
	RULE(.class = "Firefox", .tags = 1 << 7)
	RULE(.instance = "spterm", .tags = SPTAG(0), .isfloating = 1)
};



/* Bar rules allow you to configure what is shown where on the bar, as well as
 * introducing your own bar modules.
 *
 *    monitor:
 *      -1  show on all monitors
 *       0  show on monitor 0
 *      'A' show on active monitor (i.e. focused / selected) (or just -1 for active?)
 *    bar - bar index, 0 is default, 1 is extrabar
 *    alignment - how the module is aligned compared to other modules
 *    widthfunc, drawfunc, clickfunc - providing bar module width, draw and click functions
 *    name - does nothing, intended for visual clue and for logging / debugging
 */
static const BarRule barrules[] = {
	/* monitor  bar    alignment         widthfunc                drawfunc                clickfunc                name */
	{ -1,       0,     BAR_ALIGN_LEFT,   width_tags,              draw_tags,              click_tags,              "tags" },
	{  'A',       0,     BAR_ALIGN_RIGHT,  width_systray,           draw_systray,           click_systray,           "systray" },
	{ -1,       0,     BAR_ALIGN_LEFT,   width_ltsymbol,          draw_ltsymbol,          click_ltsymbol,          "layout" },
	{ 'A',      0,     BAR_ALIGN_RIGHT,  width_status2d,          draw_status2d,          click_status2d,          "status2d" },
	{ -1,       0,     BAR_ALIGN_NONE,   width_awesomebar,        draw_awesomebar,        click_awesomebar,        "awesomebar" },
};

/* layout(s) */
static const float mfact     = 0.62; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */


static const Layout layouts[] = {
	/* symbol     arrange function */
		{ " ",    tile             },    /* first entry is default */
	{ " ",   NULL             },    /* no layout function means floating behavior */
	{ " ", monocle          },
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

static const char *termcmd[]  = { "alacritty", NULL };
static const char *browsercmd[]  = { "vivaldi-stable", NULL };
static const char *codecmd[]  = { "code", NULL };
static const char *terminalcmd[]  = { "st", NULL };
static const char *slockcmd[]  = { "slock", NULL };
static const char *upvolcmd[]       = { "/home/aaron/.local/share/dwm/scripts/vol-up.sh",      NULL };
static const char *downvolcmd[]     = { "/home/aaron/.local/share/dwm/scripts/vol-down.sh",    NULL };
static const char *mutevolcmd[]     = { "/home/aaron/.local/share/dwm/scripts/vol-toggle.sh",  NULL };

static const char *wpchangecmd[]    = { "/home/aaron/.local/share/dwm/scripts/wp-change.sh",   NULL };
static const char *screenshotcmd[]  = { "/home/aaron/.local/share/dwm/scripts/screenshot.sh",  NULL };
static const char *filemanagercmd[]  = { "/home/aaron/.local/share/dwm/scripts/filemanager.sh",  NULL };
static const char *roficmd[] = { "rofi", "-show", NULL };
static const char *rofisearchcmd[] = {"/home/aaron/apps/web-search.sh", NULL};

static Key keys[] = {
	/* modifier                     key            function                argument */
	{ MODKEY,                       XK_Return,     spawn,          {.v = termcmd }       },
	{ MODKEY,                       XK_g,          spawn,          {.v = browsercmd }    },
	{ MODKEY|ControlMask,             XK_grave,       spawn,          {.v = slockcmd }    },
	{ MODKEY|ShiftMask,             XK_w,          spawn,          {.v = upvolcmd }      },
	{ MODKEY|ShiftMask,             XK_s,          spawn,          {.v = downvolcmd }    },
	{ MODKEY|ShiftMask,             XK_e,          spawn,          {.v = mutevolcmd }    },
	{ MODKEY|ShiftMask,             XK_d,          spawn,          {.v = wpchangecmd }   },
	{ MODKEY|ShiftMask,             XK_a,          spawn,          {.v = screenshotcmd } },
	{ MODKEY,                   XK_equal,          spawn,          {.v = filemanagercmd } },
	{ MODKEY,                   XK_backslash,          spawn,          {.v = terminalcmd } },
	{ MODKEY,                       XK_s, spawn,  {.v = rofisearchcmd } },
	{ MODKEY,                       XK_d, spawn,  {.v = roficmd } },
	{ 0,                       XK_F9,         togglescratch,  {.v = spcmd1 } },
 { 0, XF86XK_AudioRaiseVolume, spawn, {.v = upvolcmd }  },
  { 0, XF86XK_AudioLowerVolume, spawn,  {.v = downvolcmd }  },
  {  MODKEY,                      XK_bracketleft,  spawn, SHCMD("xbacklight -dec +5;/home/aaron/.local/share/dwm/scripts/dwm-status-refresh.sh") },
  {  MODKEY,                      XK_bracketright,  spawn, SHCMD("xbacklight -inc +5;/home/aaron/.local/share/dwm/scripts/dwm-status-refresh.sh") },
  { 0, XF86XK_AudioMute, spawn, SHCMD("/usr/bin/amixer set Master toggle;/home/aaron/.local/share/dwm/scripts/dwm-status-refresh.sh") },
  { 0, XF86XK_MonBrightnessUp, spawn, SHCMD("xbacklight -inc +5;/home/aaron/.local/share/dwm/scripts/dwm-status-refresh.sh") },
  { 0, XF86XK_MonBrightnessDown, spawn, SHCMD("xbacklight -dec +5;/home/aaron/.local/share/dwm/scripts/dwm-status-refresh.sh") },
  { 0, XF86XK_Calculator, spawn, SHCMD("rofi -show calc") },

	{ MODKEY,                       XK_b,          togglebar,              {0} },
	{ MODKEY,                       XK_j,          focusstack,             {.i = +1 } },
	{ MODKEY,                       XK_k,          focusstack,             {.i = -1 } },
	{ MODKEY|ShiftMask,              XK_j,          rotatestack,            {.i = +1 } },
	{ MODKEY|ShiftMask,              XK_k,          rotatestack,            {.i = -1 } },
	{ MODKEY,                       XK_o,          incnmaster,             {.i = +1 } },
	{ MODKEY,                       XK_p,          incnmaster,             {.i = -1 } },
	{ MODKEY,                       XK_h,          setmfact,               {.f = -0.05} },
	{ MODKEY,                       XK_l,          setmfact,               {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_h,          setcfact,               {.f = +0.25} },
	{ MODKEY|ShiftMask,             XK_l,          setcfact,               {.f = -0.25} },
	{ MODKEY|ShiftMask,             XK_o,          setcfact,               {0} },


	{ MODKEY|Mod1Mask,              XK_h,          incrgaps,       {.i = +1 }            },
	{ MODKEY|Mod1Mask,              XK_l,          incrgaps,       {.i = -1 }            },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_h,          incrogaps,      {.i = +1 }            },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_l,          incrogaps,      {.i = -1 }            },
	{ MODKEY|Mod1Mask|ControlMask,  XK_h,          incrigaps,      {.i = +1 }            },
	{ MODKEY|Mod1Mask|ControlMask,  XK_l,          incrigaps,      {.i = -1 }            },
	{ MODKEY|Mod1Mask,              XK_0,          togglegaps,     {0}                   },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_0,          defaultgaps,    {0}                   },
	{ MODKEY,                       XK_u,          incrihgaps,     {.i = +1 }            },
	{ MODKEY,                       XK_i,          incrihgaps,     {.i = -1 }            },
	{ MODKEY|ControlMask,           XK_u,          incrivgaps,     {.i = +1 }            },
	{ MODKEY|ControlMask,           XK_i,          incrivgaps,     {.i = -1 }            },
	{ MODKEY|Mod1Mask,              XK_u,          incrohgaps,     {.i = +1 }            },
	{ MODKEY|Mod1Mask,              XK_i,          incrohgaps,     {.i = -1 }            },
	{ MODKEY|ShiftMask,             XK_u,          incrovgaps,     {.i = +1 }            },
	{ MODKEY|ShiftMask,             XK_i,          incrovgaps,     {.i = -1 }            },

	{ MODKEY|ShiftMask,             XK_Return,     zoom,           {0}                   },
	{ MODKEY,                       XK_Tab,        view,           {0}                   },
	{ MODKEY|ControlMask,           XK_q,          killclient,     {0}                   },
	{ MODKEY|ControlMask|ShiftMask, XK_q,          quit,                   {1} },
	{ MODKEY|ShiftMask,             XK_t,          setlayout,      {.v = &layouts[0]}    },
	{ MODKEY|ShiftMask,             XK_f,          setlayout,      {.v = &layouts[1]}    },
	{ MODKEY|ShiftMask,             XK_m,          setlayout,      {.v = &layouts[2]}    },
	{ MODKEY,                       XK_f,          fullscreen,     {0}                   },
	{ MODKEY,                       XK_space,      setlayout,      {0}                   },
	{ MODKEY|ShiftMask,             XK_space,      togglefloating, {0}                   },
	{ MODKEY,                       XK_0,          view,           {.ui = ~0 }           },
	{ MODKEY|ShiftMask,             XK_0,          tag,            {.ui = ~0 }           },
	{ MODKEY,                       XK_comma,      focusmon,       {.i = -1 }            },
	{ MODKEY,                       XK_period,     focusmon,       {.i = +1 }            },
	{ MODKEY|ShiftMask,             XK_comma,      tagmon,         {.i = -1 }            },
	{ MODKEY|ShiftMask,             XK_period,     tagmon,         {.i = +1 }            },

	// { MODKEY,                       XK_grave,      togglescratch,          {.ui = 0 } },
	// { MODKEY|ShiftMask,             XK_grave,      removescratch,          {.ui = 0 } },
	{ MODKEY,             XK_f,          fullscreen,             {0} },
	TAGKEYS(                        XK_1,                                  0)
	TAGKEYS(                        XK_2,                                  1)
	TAGKEYS(                        XK_3,                                  2)
	TAGKEYS(                        XK_4,                                  3)
	TAGKEYS(                        XK_5,                                  4)
	TAGKEYS(                        XK_6,                                  5)
	TAGKEYS(                        XK_7,                                  6)
	TAGKEYS(                        XK_8,                                  7)
	TAGKEYS(                        XK_9,                                  8)
	{ MODKEY|ControlMask|ShiftMask, XK_c,          quit,           {0}                   },
};


/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask           button          function        argument */
	{ ClkLtSymbol,          0,                   Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,                   Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,                   Button1,        togglewin,      {0} },
	{ ClkWinTitle,          0,                   Button3,        showhideclient, {0} },
	{ ClkWinTitle,          0,                   Button2,        zoom,           {0} },
	{ ClkStatusText,        0,                   Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,              Button1,        movemouse,      {0} },
	/* placemouse options, choose which feels more natural:
	 *    0 - tiled position is relative to mouse cursor
	 *    1 - tiled postiion is relative to window center
	 *    2 - mouse pointer warps to window center
	 */
	{ ClkClientWin,         MODKEY|ControlMask,  Button1,        placemouse,     {.i = 1} },
	{ ClkClientWin,         MODKEY,              Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,              Button3,        resizemouse,    {0} },
	{ ClkClientWin,         MODKEY|ShiftMask,    Button3,        dragcfact,      {0} },
	{ ClkTagBar,            0,                   Button1,        view,           {0} },
	{ ClkTagBar,            0,                   Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,              Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,              Button3,        toggletag,      {0} },
};


