//Modify this file to change what commands output to your statusbar, and recompile using the make command.
static const Block blocks[] = {
	/*Icon*/	/*Command*/	/*Update Interval*/	/*Update Signal*/
	{"Dsk:", "status-disk",                 30,             1},
	{"Mem:", "status-memory",      		5,		2},
	{"Net:", "status-network",              10,         	12},
	{"Bat:", "status-battery",              5,		4},
	{"Vol:", "status-audio",                0,		10},
	{"", "date '+%b %d (%a) %H:%M'",	5,		5},
	{"", "status-tablet",			0,		11},
};

//sets delimiter between status commands. NULL character ('\0') means no delimiter.
static char delim[] = " | ";
static unsigned int delimLen = 5;
