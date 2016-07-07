
/*
 * (C) Copyright 1999 Denis McLaughlin
 *
 * Include file for global variables, used to set default run time
 * values: all of these can be overridden in either the config file
 * or the command line
 *
 */


/* header string */
char *header="
Hand
version "VERSION"
compiled "__DATE__" at "__TIME__"

(C) Copyright 1999
brad@playground.net
denism@cyberus.ca
";

/* base directory name, only really used for informational purposes */
char *base=BASE;

/* config file name and file pointer */
char *config=CONFIG;
FILE *configF;

/* log file name and file pointer */
char *logfile=LOGFILE;
FILE *logF=NULL;

/* default listen port */
int port=PORT;

/* default debug flag */
int df=0;

/* default verbosity: 0 */
int vl=VL;

/* general scratch space */
char scratch1[SSIZE];
char scratch2[SSIZE];
char scratch3[SSIZE];

/* secure mode flag */
int secure=0;

/* background flag, internal use */
int bg=0;

/* pointer to executable name */
char *execp;

/* pointer to array of argument strings */
char **execa;


/* process id, global so we only have to do it once */
int pid;
