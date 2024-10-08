/* See LICENSE file for copyright and license details. */
/* Default settings; can be overriden by command line. */

static int topbar       = 0;    /* -b  option; if 0, dmenu appears at bottom     */
static int centered     = 1;    /* -c option; centers dmenu on screen */
static int min_width    = 500;  /* minimum width when centered */
static int border       = 1;    /* 1 means a border with the fg Norm color around the menu */
static int inputBorder  = 1;    /* 1 means a border with the fg Norm color around the text input */
/* -fn option overrides fonts[0]; default X11 font or font set */
static const char *fonts[] = {
	"0xProto Nerd Font:size=10"
};
static const char *prompt      = NULL;      /* -p  option; prompt to the left of input field */
static const char *colors[SchemeLast][2] = {
	              /*     fg         bg     */
	[SchemeNorm]  = { "#e09ece", "#000000" },
	[SchemeSel]   = { "#000000", "#e09ece" },
	[SchemeOut]   = { "#e09ece", "#332233" },
};
/* -l option; if nonzero, dmenu uses vertical list with given number of lines */
static unsigned int lines = 5;

/*
 * Characters not considered part of a word while deleting words
 * for example: " /?\"&[]"
 */
static const char worddelimiters[] = " ";
