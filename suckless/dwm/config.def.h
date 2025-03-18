/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 0;        /* 0 means no bar */
static int topbar                   = 1;        /* 0 means bottom bar */
static int rightbar                 = 1;        /* 0 means bar aligned to the left */
static const unsigned int barBdr    = 1;        /* 0 means no bar border */
static const int vertmarg           = 10;       /* vertical margin of bar */
static const int sidemarg           = 10;       /* horizontal margin of bar, barpadding patch is just named wrong imo */
static const int barpadding         = 16;       /* bar padding, the actual visual value is half the set value */
static const char *fonts[]          = { "0xProto Nerd Font:size=10" };
static const char dmenufont[]       = "0xProto Nerd Font:size=10";
static char clr_barBdr[]      = "#e09ece"; 
static char clr_normBdr[]     = "#444444"; 
static char clr_selBdr[]      = "#e09ece"; 
/* Normal */
static char clr_fgNorm[]      = "#e09ece";
static char clr_bgNorm[]      = "#000000";
/* Selectd */
static char clr_fgSel[]       = "#000000";
static char clr_bgSel[]       = "#e09ece";

static char clr_unused[]      = "#000000";

static const unsigned int transparent   = 0x00;
static const unsigned int alphaNorm     = 0x99;
static const unsigned int alphaSel      = 0xcc;
static const unsigned int bdrAlphaSel   = OPAQUE; // opaque is set in another file, only god knows why
static const unsigned int bdrAlphaNorm  = OPAQUE; // opaque is set in another file, only god knows why

static char *colors[][3]      = {
	/*                        fg           bg         border   */
	[SchemeNorm]      = { "#ffffff",  clr_unused, clr_normBdr }, // white fg for security
	[SchemeSel]       = { clr_fgNorm,   clr_bgNorm, clr_selBdr  },
	[SchemeStatus]    = { clr_fgNorm,   clr_bgNorm, clr_barBdr  }, 
	[SchemeTagsNorm]  = { clr_fgNorm,   clr_bgNorm, clr_barBdr  }, 
	[SchemeTagsSel]   = { clr_fgSel,    clr_bgSel,  clr_unused  }, 
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
static const char *tags[] = { "1", "2", "3", "4", "5", "6" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     iscentered   isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            0,           0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.65; /* factor of master area size [0.05..0.95] */
static int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 0; /* 1 will force focus on the fullscreen window */

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

/*
 * Xresources preferences to load at startup
 */
ResourcePref resources[] = {
    { "barbordercolor",     STRING,  &clr_barBdr }, 
    { "normbgcolor",        STRING,  &clr_bgNorm },
		{ "normbordercolor",    STRING,  &clr_normBdr },
		{ "normfgcolor",        STRING,  &clr_fgNorm },
		{ "selbgcolor",         STRING,  &clr_bgSel },
		{ "selbordercolor",     STRING,  &clr_selBdr },
		{ "selfgcolor",         STRING,  &clr_fgSel },
};

#include "selfrestart.c"

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ ControlMask|ShiftMask,  XK_Return,  spawn,          SHCMD("dmenu_run") },
	{ ControlMask|ShiftMask,  XK_t,       spawn,          SHCMD("cd ~ && st") },

	{ MODKEY,                 XK_b,       togglebar,      {0} },
	{ MODKEY,                 XK_j,       focusstack,     {.i = +1 } },
	{ MODKEY,                 XK_k,       focusstack,     {.i = -1 } },
	{ MODKEY,                 XK_i,       incnmaster,     {.i = +1 } },
	{ MODKEY,                 XK_d,       incnmaster,     {.i = -1 } },
  { MODKEY,                 XK_Right,   togglerightbar, {.i = 1} },
  { MODKEY,                 XK_Left,    togglerightbar, {.i = 0} },
  { MODKEY,                 XK_Up,      toggletopbar,   {.i = 1} },
  { MODKEY,                 XK_Down,    toggletopbar,   {.i = 0} },
	{ MODKEY,                 XK_h,       setmfact,       {.f = -0.05} },
	{ MODKEY,                 XK_l,       setmfact,       {.f = +0.05} },
	{ MODKEY,                 XK_Return,  zoom,           {0} },
	{ MODKEY,                 XK_Tab,     view,           {0} },
	{ MODKEY|ShiftMask,       XK_c,       killclient,     {0} },
	{ MODKEY,                 XK_t,       setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                 XK_f,       setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                 XK_m,       setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                 XK_space,   setlayout,      {0} },
	{ MODKEY|ShiftMask,       XK_space,   togglefloating, {0} },
	{ MODKEY,                 XK_0,       view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,       XK_0,       tag,            {.ui = ~0 } },
	{ MODKEY,                 XK_comma,   focusmon,       {.i = -1 } },
	{ MODKEY,                 XK_period,  focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,       XK_comma,   tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,       XK_period,  tagmon,         {.i = +1 } },
	TAGKEYS(                  XK_1,                      0)
	TAGKEYS(                  XK_2,                      1)
	TAGKEYS(                  XK_3,                      2)
	TAGKEYS(                  XK_4,                      3)
	TAGKEYS(                  XK_5,                      4)
	TAGKEYS(                  XK_6,                      5)
  { MODKEY|ShiftMask,       XK_r,       self_restart,   {0} },
	{ MODKEY|ShiftMask,       XK_q,       quit,           {0} },
	{ !ControlMask,           HOLDKEY,    holdbar,        {0} },

  // mpd binds
	{ Mod4Mask, XK_Up,        spawn, SHCMD("mpc volume +5") },
	{ Mod4Mask, XK_Down,      spawn, SHCMD("mpc volume -5") },
	{ Mod4Mask, XK_Left,      spawn, SHCMD("mpc seek -5") },
	{ Mod4Mask, XK_Right,     spawn, SHCMD("mpc seek +5") },
	{ Mod4Mask, XK_BackSpace, spawn, SHCMD("mpc seek 0") },
    // page up is on the left and down is on the right, and i prefer right for next and left for prev
	{ Mod4Mask, XK_Next,      spawn, SHCMD("mpc next") },
	{ Mod4Mask, XK_Prior,     spawn, SHCMD("mpc prev") },
	{ Mod4Mask, XK_space,     spawn, SHCMD("mpc toggle") },
	{ Mod4Mask, XK_Return,    spawn, SHCMD("mpc toggle") },

  // volume binds
	{ 0,  XF86XK_AudioLowerVolume,  spawn, SHCMD("pactl set-sink-volume @DEFAULT_SINK@ -5% && ~/Scripts/volBind.sh") },
	{ 0,  XF86XK_AudioRaiseVolume,  spawn, SHCMD("pactl set-sink-volume @DEFAULT_SINK@ +5% && ~/Scripts/volBind.sh") },
	{ 0,  XF86XK_AudioMute,         spawn, SHCMD("pactl set-sink-mute @DEFAULT_SINK@ toggle && ~/Scripts/volBind.sh") },

  // scripts binds
	{ ControlMask|ShiftMask,  XK_w,   spawn, SHCMD("bash ~/Scripts/wallBind.sh") },
	{ ControlMask|ShiftMask,  XK_k,   spawn, SHCMD("bash ~/Scripts/setPlaylist.sh") },
	{ ControlMask|ShiftMask,  XK_m,   spawn, SHCMD("bash ~/Scripts/setSong.sh") },
	{ ControlMask|ShiftMask,  XK_s,   spawn, SHCMD("bash ~/Scripts/powerBind.sh") },
	{ ControlMask|ShiftMask,  XK_F2,  spawn, SHCMD("bash ~/Scripts/record.sh") },
	{ ControlMask|ShiftMask,  XK_n,   spawn, SHCMD("xclip -selection clipboard -o | xvkbd -xsendevent -file -") },
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

void
viewex(const Arg *arg)
{
	view(&((Arg) { .ui = 1 << arg->ui }));
}

void reload_xresources(const Arg *arg)
{
  load_xresources();
  // tho i only need it for xresources this could reload any change to xresources
  // if you do things right
  setup();
}

/* signal definitions */
static Signal signals[] = {
	/* signum       function */
	{ "viewex",     viewex },
	{ "restart",    self_restart },
	{ "xresources", reload_xresources },
};
