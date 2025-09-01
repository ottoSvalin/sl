/* user and group to drop privileges to */
static const char *user  = "otto";
static const char *group = "otto";


// ALT #001C1C

static const char *colorname[NUMCOLS] = {
	[INIT] =   "#000000",     /* after initialization */
	[INPUT] =  "#00051C",   /* during input */
        [INPUT_ALT] = "#00051F", /* during input, second color */
	[FAILED] = "#1C0000",   /* wrong password */
};

/* treat a cleared input like a wrong password (color) */
static const int failonclear = 1;

/* default message */
static const char * message = ":^)";

/* text color */
static const char * text_color = "#777777";

/* text size (must be a valid size) */
static const char * font_name = "6x10";
