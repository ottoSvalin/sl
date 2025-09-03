/* See LICENSE file for copyright and license details. */

#define SESSION_FILE "/tmp/dwm-session"

/* appearance */
static unsigned int borderpx  = 1;        /* border pixel of windows */
static unsigned int snap      = 32;       /* snap pixel */
static int showbar            = 1;        /* 0 means no bar */
static int topbar             = 1;        /* 0 means bottom bar */
static char font[]            = "monospace:size=10";
static char dmenufont[]       = "monospace:size=10";
static const char *fonts[]          = { font };
static char normbgcolor[]           = "#222222";
static char normbordercolor[]       = "#444444";
static char normfgcolor[]           = "#bbbbbb";
static char selfgcolor[]            = "#eeeeee";
static char selbordercolor[]        = "#005577";
static char selbgcolor[]            = "#005577";
static char *colors[][3] = {
       /*               fg           bg           border   */
       [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
       [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	//{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
	{ "discord",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static int nmaster     = 1;    /* number of clients in master area */
static int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

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

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

#define STATUSBAR "dwmblocks"

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbordercolor, "-sf", selfgcolor, NULL };

static const char *termcmd[]  = { "st", NULL };
static const char *restartcmd[] = {"restartdwm", NULL};

static const char *dummy_cmd[] = {"notify-send", "Key not bound...", NULL};
static const char *brightness_inc_cmd[] = {"brightnessctl", "-n192", "set", "+10%", NULL};
static const char *brightness_dec_cmd[] = {"brightnessctl", "-n192", "set", "10%-", NULL};
static const char *volume_max_cmd[] = {"audioctl", "--max", NULL};
static const char *volume_min_cmd[] = {"audioctl", "--min", NULL};
static const char *volume_inc_cmd[] = {"audioctl", "-i", "5", NULL};
static const char *volume_dec_cmd[] = {"audioctl", "-d", "5", NULL};
static const char *volume_i_cmd[] = {"audioctl", "-i", "1", NULL};
static const char *volume_d_cmd[] = {"audioctl", "-d", "1", NULL};
static const char *volume_mute_cmd[] = {"audioctl", "-m", NULL};
static const char *bookmark_paste_cmd[] = {"bookmarker", "-p", NULL};
static const char *bookmark_copy_cmd[] = {"bookmarker", "-c", NULL};
static const char *screenshot_selection_cmd[] = {"prtscr", "-s", "/home/otto/pictures/screenshots", NULL};
static const char *screenshot_full_cmd[] = {"prtscr", "-f", "/home/otto/pictures/screenshots", NULL};
static const char *temp_inc_cmd[] = {"tempctl", "-i", NULL};
static const char *temp_dec_cmd[] = {"tempctl", "-d", NULL};
static const char *temp_reset_cmd[] = {"tempctl", "-r", NULL};
static const char *temp_min_cmd[] = {"tempctl", "-m", NULL};
static const char *tablet_exit_cmd[] = {"tabletctl", "-x", NULL};
static const char *tablet_standing_cmd[] = {"tabletctl", "-s", NULL};
static const char *tablet_landscape_cmd[] = {"tabletctl", "-l", NULL};
static const char *touchscreen_toggle_cmd[] = {"tabletctl", "-t", NULL};
static const char *draw_cmd[] = {"xournalpp", NULL};
static const char *suspend_cmd[] = {"powerctl", "-l", NULL};
static const char *power_cmd[] = {"powerctl", "-m", NULL};
static const char *network_list_cmd[] = {"netwctl", NULL};
static const char *network_manage_cmd[] = {"netwctl", "--manage-current", NULL};
static const char *emoji_cmd[] = {"emojipicker", NULL};
static const char *toggle_theme_cmd[] = {"themectl", "-t", NULL};

/*
 * Xresources preferences to load at startup
 */
ResourcePref resources[] = {
		{ "font",               STRING,  &font },
		{ "dmenufont",          STRING,  &dmenufont },
		{ "normbgcolor",        STRING,  &normbgcolor },
		{ "normbordercolor",    STRING,  &normbordercolor },
		{ "normfgcolor",        STRING,  &normfgcolor },
		{ "selbgcolor",         STRING,  &selbgcolor },
		{ "selbordercolor",     STRING,  &selbordercolor },
		{ "selfgcolor",         STRING,  &selfgcolor },
		{ "borderpx",          	INTEGER, &borderpx },
		{ "snap",          		INTEGER, &snap },
		{ "showbar",          	INTEGER, &showbar },
		{ "topbar",          	INTEGER, &topbar },
		{ "nmaster",          	INTEGER, &nmaster },
		{ "resizehints",       	INTEGER, &resizehints },
		{ "mfact",      	 	FLOAT,   &mfact },
};


static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XF86XK_Back,              spawn,          {.v = tablet_standing_cmd}},
	{ MODKEY,                       XF86XK_Forward,           spawn,          {.v = tablet_landscape_cmd}},
	{ MODKEY|ShiftMask,             XF86XK_Back,              spawn,          {.v = tablet_standing_cmd}},
	{ MODKEY|ShiftMask,             XF86XK_Forward,           spawn,          {.v = tablet_landscape_cmd}},
	{ MODKEY|ShiftMask,             XF86XK_Back,              spawn,          {.v = draw_cmd}},
	{ MODKEY|ShiftMask,             XF86XK_Forward,           spawn,          {.v = draw_cmd}},
	{ MODKEY,                       XF86XK_Reload,            spawn,          {.v = touchscreen_toggle_cmd}},
	{ 0,                            XF86XK_Reload,            spawn,          {.v = tablet_exit_cmd}},
	{ MODKEY,                       XF86XK_LaunchA,           spawn,          {.v = screenshot_selection_cmd}},
	{ MODKEY|ShiftMask,             XF86XK_LaunchA,           spawn,          {.v = screenshot_full_cmd}},
	{ 0,                            XF86XK_MonBrightnessDown, spawn,          {.v = brightness_dec_cmd}},
	{ 0,                            XF86XK_MonBrightnessUp,   spawn,          {.v = brightness_inc_cmd}},
	{ MODKEY,                       XF86XK_MonBrightnessDown, spawn,          {.v = temp_dec_cmd}},
	{ MODKEY,                       XF86XK_MonBrightnessUp,   spawn,          {.v = temp_inc_cmd}},
	{ MODKEY|ShiftMask,             XF86XK_MonBrightnessDown, spawn,          {.v = temp_min_cmd}},
	{ MODKEY|ShiftMask,             XF86XK_MonBrightnessUp,   spawn,          {.v = temp_reset_cmd}},
	{ 0,                            XF86XK_AudioMute,         spawn,          {.v = volume_mute_cmd}},
	{ 0,                            XF86XK_AudioLowerVolume,  spawn,          {.v = volume_dec_cmd}},
	{ 0,                            XF86XK_AudioRaiseVolume,  spawn,          {.v = volume_inc_cmd}},
	{ MODKEY,                       XF86XK_AudioLowerVolume,  spawn,          {.v = volume_d_cmd}},
	{ MODKEY,                       XF86XK_AudioRaiseVolume,  spawn,          {.v = volume_i_cmd}},
	{ MODKEY|ShiftMask,             XF86XK_AudioLowerVolume,  spawn,          {.v = volume_min_cmd}},
	{ MODKEY|ShiftMask,             XF86XK_AudioRaiseVolume,  spawn,          {.v = volume_max_cmd}},
	{ 0,                            XF86XK_Sleep,             spawn,          {.v = suspend_cmd}},
	{ MODKEY,                       XF86XK_Sleep,             spawn,          {.v = power_cmd}},
	{ MODKEY|ShiftMask,             XF86XK_Sleep,             spawn,          {.v = toggle_theme_cmd}},
	{ 0,                            XF86XK_WakeUp,            spawn,          {.v = tablet_exit_cmd}},
	{ MODKEY,                       XK_i,                     spawn,          {.v = emoji_cmd} },
	{ MODKEY,                       XK_o,                     spawn,          {.v = bookmark_paste_cmd} },
	{ MODKEY|ShiftMask,             XK_o,                     spawn,          {.v = bookmark_copy_cmd} },
	{ MODKEY,                       XK_p,                     spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_n,                     spawn,          {.v = network_list_cmd} },
	{ MODKEY|ShiftMask,             XK_n,                     spawn,          {.v = network_manage_cmd} },
	{ MODKEY|ShiftMask,             XK_Return,                spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,                     togglebar,      {0} },
	{ MODKEY,                       XK_j,                     focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,                     focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_j,                     incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,                     incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,                     setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,                     setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return,                zoom,           {0} },
	{ MODKEY,                       XK_Tab,                   view,           {0} },
	{ MODKEY|ShiftMask,             XK_q,                     killclient,     {0} },
	{ MODKEY,                       XK_t,                     setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,                     setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,                     setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,                 setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,                 togglefloating, {0} },
	{ MODKEY,                       XK_0,                     view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,                     tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,                 focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period,                focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,                 tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period,                tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY,                       XK_x,      spawn,          {.v = restartcmd} },
	{ MODKEY|ShiftMask,             XK_x,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask        button          function        argument */
	{ ClkLtSymbol,          0,                Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,                Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,                Button2,        zoom,           {0} },
	{ ClkStatusText,        0,                Button1,        sigstatusbar,   {.i = 1} }, /* left click */
	{ ClkStatusText,        0,                Button2,        sigstatusbar,   {.i = 2} }, /* middle click */
	{ ClkStatusText,        0,                Button3,        sigstatusbar,   {.i = 3} }, /* right click */
	{ ClkStatusText,        0,                Button4,        sigstatusbar,   {.i = 4} }, /* scroll up */
	{ ClkStatusText,        0,                Button5,        sigstatusbar,   {.i = 5} }, /* scroll down */
	{ ClkStatusText,        ShiftMask,        Button1,        sigstatusbar,   {.i = 6} }, 
	{ ClkClientWin,         MODKEY,           Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,           Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,           Button3,        resizemouse,    {0} },
	{ ClkClientWin,         MODKEY|ShiftMask, Button1,        resizemouse,    {0} },
	{ ClkTagBar,            0,                Button1,        view,           {0} },
	{ ClkTagBar,            0,                Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,           Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,           Button3,        toggletag,      {0} },
};

