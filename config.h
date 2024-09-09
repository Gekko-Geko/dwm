/* See LICENSE file for copyright and license details. */
// include "/home/geko/.cache/wal/colors-wal-dwm.h"
static const char norm_fg[] = "#d8d3d4";
static const char norm_bg[] = "#121019";
static const char norm_border[] = "#979394";

static const char sel_fg[] = "#121019";
static const char sel_bg[] = "#ff7f50";
static const char sel_border[] = "#ff7f50";

static const char urg_fg[] = "#d8d3d4";
static const char urg_bg[] = "#62867A";
static const char urg_border[] = "#62867A";

static const char *colors[][3]      = {
    /*               fg           bg         border                         */
    [SchemeNorm] = { norm_fg,     norm_bg,   norm_border }, // unfocused wins
    [SchemeSel]  = { sel_fg,      sel_bg,    sel_border },  // the focused win
    [SchemeUrg] =  { urg_fg,      urg_bg,    urg_border },
};
/* appearance */
static const unsigned int gappih = 20; /* horiz inner gap between windows */
static const unsigned int gappiv = 10; /* vert inner gap between windows */
static const unsigned int gappoh =
    12; /* horiz outer gap between windows and screen edge */
static const unsigned int gappov =
    12; /* vert outer gap between windows and screen edge */
static int smartgaps =
    0; /* 1 means no outer gap when there is only one window */
static const int focusonwheel = 0;
static unsigned int borderpx = 4; /* border pixel of windows */
static const int swallowfloating =
    0;                         /* 1 means swallow floating windows by default */
static unsigned int snap = 32; /* snap pixel */
static int showbar = 1;        /* 0 means no bar */
static int topbar = 1;         /* 0 means bottom bar */
static char dmenufont[] = "Hack:size=14";
static const char *fonts[] = {"Hack:size=14:antialias=true:autohint=true",
                              "Noto Color Emoji:size=14"};

/* tagging */
static const char *tags[] = {"", "", "", "", ""};

static const char *tagsel[][2] = {
	{ "#cc231d", "#1d2021" },
	{ "#d79921", "#1d2021" },
	{ "#689d6a", "#1d2021" },
	{ "#98971a", "#1d2021" },
	{ "#d65d0e", "#1d2021" },
};

static const unsigned int ulinepad	= 5;	/* horizontal padding between the underline and tag */
static const unsigned int ulinestroke	= 2;	/* thickness / height of the underline */
static const unsigned int ulinevoffset	= 0;	/* how far above the bottom of the bar the line should appear */
static const int ulineall 		= 0;	/* 1 to show underline on all tags, 0 for just the active ones */

static const Rule rules[] = {
    /* xprop(1):
     *	WM_CLASS(STRING) = instance, class
     *	WM_NAME(STRING) = title
     */
    /* class     instance  title           tags mask  isfloating  isterminal  noswallow  monitor */
    {"st",          NULL,     NULL,           0,            0,        1,          0,        -1},
    {"steam",       NULL,     NULL,           1 << 3,       1,        0,          0,        -1},
    {"firefox",     NULL,     NULL,           1 << 2,       0,        0,          -1,       -1},
    {"discord",     NULL,     NULL,           1 << 1,       0,        0,          0,        -1},
    {"thunderbird", NULL,     NULL,           1 << 1,       0,        0,          0,        -1},
    {NULL,          NULL,     "Event Tester", 0,            0,        0,          1,        -1}, /* xev */
};

/* layout(s) */
static float mfact = 0.60;  /* factor of master area size [0.05..0.95] */
static int nmaster = 1;     /* number of clients in master area */
static int resizehints = 0; /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen =
    1; /* 1 will force focus on the fullscreen window */

#define FORCE_VSPLIT                                                           \
  1 /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
    /* symbol     arrange function */
    {"[]=", tile}, /* first entry is default */
    {"[M]", monocle},
    {"[@]", spiral},
    {"[\\]", dwindle},
    {"H[]", deck},
    {"TTT", bstack},
    {"===", bstackhoriz},
    {"HHH", grid},
    {"###", nrowgrid},
    {"---", horizgrid},
    {":::", gaplessgrid},
    {"|M|", centeredmaster},
    {">M>", centeredfloatingmaster},
    {"><>", NULL}, /* no layout function means floating behavior */
    {NULL, NULL},
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY, TAG)                                                      \
  {MODKEY, KEY, view, {.ui = 1 << TAG}},                                       \
      {MODKEY | ControlMask, KEY, toggleview, {.ui = 1 << TAG}},               \
      {MODKEY | ShiftMask, KEY, tag, {.ui = 1 << TAG}},                        \
      {MODKEY | ControlMask | ShiftMask, KEY, toggletag, {.ui = 1 << TAG}},

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd)                                                             \
  {                                                                            \
    .v = (const char *[]) { "/bin/sh", "-c", cmd, NULL }                       \
  }

/* commands */
static char dmenumon[2] =
    "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = {
    "dmenu_run", "-m",    dmenumon, "-fn",  dmenufont, "-nb",  norm_bg,
    "-nf",       norm_fg, "-sb",    sel_bg, "-sf",     sel_fg, NULL};
static const char *termcmd[] = {"st", NULL};
static const char *browser[] = {"firefox", NULL};
static const char *discord[] = {"discord", NULL};
static const char *shutdown[] = {"prompt", "Do you want to shutdown?",
                                 "/sbin/halt -p", NULL};
static const char *screenshot[] = {"/usr/local/bin/screenshot", NULL};
static const char *upbright[] = {"/sbin/brillo", "-q", "-A", "10", NULL};
static const char *downbright[] = {"/sbin/brillo", "-q", "-U", "10", NULL};
static const char *locking[] = {"/usr/local/bin/slock"};
static const char *vol_up[] = {"/usr/local/bin/volume_up"};
static const char *vol_down[] = {"/usr/local/bin/volume_down"};
static const char *vol_mute[] = {"/usr/local/bin/volume_mute"};
static const char *skippy[] = {"/sbin/skippy-xd"};

#include "movestack.c"

static Key keys[] = {
    /* modifier                     key        function        argument */
    {MODKEY, XK_g, togglebar, {0}},
    {MODKEY, XK_p, spawn, {.v = dmenucmd}},
    {MODKEY, XK_Return, spawn, {.v = termcmd}},
    {MODKEY, XK_b, spawn, {.v = browser}},
    {MODKEY, XK_d, spawn, {.v = discord}},
    {MODKEY, XK_j, focusstack, {.i = +1}},
    {MODKEY, XK_k, focusstack, {.i = -1}},
//{MODKEY, XK_i, incnmaster, {.i = +1}},
//{MODKEY, XK_d, incnmaster, {.i = -1}},
    {MODKEY, XK_h, setmfact, {.f = -0.05}},
    {MODKEY, XK_l, setmfact, {.f = +0.05}},
    {MODKEY | ShiftMask, XK_j, movestack, {.i = +1}},
    {MODKEY | ShiftMask, XK_k, movestack, {.i = -1}},
    {MODKEY, XK_Return, zoom, {0}},
    {MODKEY | Mod1Mask, XK_u, incrgaps, {.i = +1}},
    {MODKEY | Mod1Mask | ShiftMask, XK_u, incrgaps, {.i = -1}},
    {MODKEY | Mod1Mask, XK_i, incrigaps, {.i = +1}},
    {MODKEY | Mod1Mask | ShiftMask, XK_i, incrigaps, {.i = -1}},
    {MODKEY | Mod1Mask, XK_o, incrogaps, {.i = +1}},
    {MODKEY | Mod1Mask | ShiftMask, XK_o, incrogaps, {.i = -1}},
    {MODKEY | Mod1Mask, XK_6, incrihgaps, {.i = +1}},
    {MODKEY | Mod1Mask | ShiftMask, XK_6, incrihgaps, {.i = -1}},
    {MODKEY | Mod1Mask, XK_7, incrivgaps, {.i = +1}},
    {MODKEY | Mod1Mask | ShiftMask, XK_7, incrivgaps, {.i = -1}},
    {MODKEY | Mod1Mask, XK_8, incrohgaps, {.i = +1}},
    {MODKEY | Mod1Mask | ShiftMask, XK_8, incrohgaps, {.i = -1}},
    {MODKEY | Mod1Mask, XK_9, incrovgaps, {.i = +1}},
    {MODKEY | Mod1Mask | ShiftMask, XK_9, incrovgaps, {.i = -1}},
    {MODKEY | Mod1Mask, XK_0, togglegaps, {0}},
    {MODKEY | Mod1Mask | ShiftMask, XK_0, defaultgaps, {0}},
    {Mod1Mask, XK_Tab, view, {0}},
    {MODKEY, XK_q, killclient, {0}},
    {MODKEY, XK_t, setlayout, {.v = &layouts[0]}},
    {MODKEY, XK_f, setlayout, {.v = &layouts[1]}},
    {MODKEY, XK_m, setlayout, {.v = &layouts[2]}},
    {MODKEY, XK_space, setlayout, {0}},
    {MODKEY | ShiftMask, XK_space, togglefloating, {0}},
    {MODKEY, XK_0, view, {.ui = ~0}},
    {MODKEY | ShiftMask, XK_0, tag, {.ui = ~0}},
    {MODKEY, XK_comma, focusmon, {.i = -1}},
    {MODKEY, XK_period, focusmon, {.i = +1}},
    {MODKEY | ShiftMask, XK_comma, tagmon, {.i = -1}},
    {MODKEY | ShiftMask, XK_period, tagmon, {.i = +1}},
    {MODKEY | ShiftMask, XK_q, quit, {0}},
    {MODKEY | ShiftMask, XK_x, spawn, {.v = shutdown}},
    {MODKEY | ShiftMask, XK_p, spawn, {.v = screenshot}},
    {MODKEY | ShiftMask, XK_l, spawn, {.v = locking}},
    {MODKEY, XK_Tab, spawn, {.v = skippy}},
    {0, XF86XK_AudioLowerVolume, spawn, {.v = vol_down}},
    {0, XF86XK_AudioRaiseVolume, spawn, {.v = vol_up}},
    {0, XF86XK_AudioMute, spawn, {.v = vol_mute}},
    {ControlMask, XK_F2, spawn, {.v = vol_down}},
    {ControlMask, XK_F3, spawn, {.v = vol_up}},
    {ControlMask, XK_F1, spawn, {.v = vol_mute}},
    {0, XF86XK_MonBrightnessDown, spawn, {.v = downbright}},
    {0, XF86XK_MonBrightnessUp, spawn, {.v = upbright}},
    TAGKEYS(XK_1, 0) TAGKEYS(XK_2, 1) TAGKEYS(XK_3, 2) TAGKEYS(XK_4, 3)
        TAGKEYS(XK_5, 4)};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle,
 * ClkClientWin, or ClkRootWin */
static Button buttons[] = {
    /* click                event mask      button          function argument */
    {ClkLtSymbol, 0, Button1, setlayout, {0}},
    {ClkLtSymbol, 0, Button3, setlayout, {.v = &layouts[2]}},
    {ClkWinTitle, 0, Button2, zoom, {0}},
    {ClkStatusText, 0, Button2, spawn, {.v = termcmd}},
    {ClkClientWin, MODKEY, Button1, movemouse, {0}},
    {ClkClientWin, MODKEY, Button2, togglefloating, {0}},
    {ClkClientWin, MODKEY, Button3, resizemouse, {0}},
    {ClkTagBar, 0, Button1, view, {0}},
    {ClkTagBar, 0, Button3, toggleview, {0}},
    {ClkTagBar, MODKEY, Button1, tag, {0}},
    {ClkTagBar, MODKEY, Button3, toggletag, {0}},
};
