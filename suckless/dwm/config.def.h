/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 0;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const unsigned int barBdr    = 1;        /* 0 means no bar border */
static const int vertmarg           = 10;       /* vertical margin of bar */
static const int sidemarg           = 10;       /* horizontal margin of bar, barpadding patch is just named wrong imo */
static const int barpadding         = 16;       /* bar padding, the actual visual value is half the set value */
static const char *fonts[]          = { "0xProto Nerd Font:size=10" };
static const char dmenufont[]       = "0xProto Nerd Font:size=10";
static const char clr_barBdr[]      = "#e09ece"; 
static const char clr_normBdr[]     = "#444444"; 
static const char clr_selBdr[]      = "#e09ece"; 
/* Normal */
static const char clr_fgNorm[]      = "#e09ece";
static const char clr_bgNorm[]      = "#000000";
/* Selectd */
static const char clr_fgSel[]       = "#000000";
static const char clr_bgSel[]       = "#e09ece";

static const char clr_unused[]      = "#000000";

static const unsigned int transparent   = 0x00;
static const unsigned int alphaNorm     = 0x99;
static const unsigned int alphaSel      = 0xcc;
static const unsigned int bdrAlphaSel   = OPAQUE; // opaque is set in another file, only god knows why
static const unsigned int bdrAlphaNorm  = OPAQUE; // opaque is set in another file, only god knows why

static const char *colors[][3]      = {
	/*                        fg           bg         border   */
	[SchemeNorm]      = { "#ffffff",   clr_unused, clr_normBdr }, // white fg for security
	[SchemeSel]       = { clr_fgNorm,  clr_bgNorm, clr_selBdr  },
	[SchemeStatus]    = { clr_fgNorm,  clr_bgNorm, clr_barBdr  }, 
	[SchemeTagsNorm]  = { clr_fgNorm,  clr_bgNorm, clr_barBdr  }, 
	[SchemeTagsSel]   = { clr_fgSel,   clr_bgSel,  clr_unused  }, 
};
static const unsigned int alphas[][3]      = {
	/*                      fg      bg              border     */
	[SchemeNorm]      = { OPAQUE, transparent,  bdrAlphaNorm },
	[SchemeSel]       = { OPAQUE, OPAQUE,       bdrAlphaSel },
	[SchemeStatus]    = { OPAQUE, alphaNorm,    bdrAlphaNorm  }, 
	[SchemeTagsSel]   = { OPAQUE, alphaSel,     bdrAlphaSel  }, 
	[SchemeTagsNorm]  = { OPAQUE, alphaNorm,    bdrAlphaNorm  }, 
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     iscentered   isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            0,           0,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.65; /* factor of master area size [0.05..0.95] */
static int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

// its not used but i am scared of removing code (i dont know how it works)
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },
#define HOLDKEY 0xffe9 // 'tis the alt key!  

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
// if i am ever smart, i will find a way to remove this
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", clr_bgNorm, "-nf", clr_fgNorm, "-sb", clr_bgSel, "-sf", clr_fgSel, NULL };
static const char *termcmd[]  = { "st", NULL };

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
	{ !ControlMask,                 HOLDKEY,   holdbar,        {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
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
