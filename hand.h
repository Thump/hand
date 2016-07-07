
/*
 * (C) Copyright 1999 Denis McLaughlin
 *
 * General include file for hand, specifies a number of
 * extern'd global environment variables, some data structures,
 * function prototypes.
 *
 */


/****************************************************************************/

/* Some high level includes */
 
#include "debug.h"
#include "proto.h"


/****************************************************************************/

/* Global macros and defines */

/* this line implements the groovy debugging routines: see debug.h for the
 * valid values of a
 */
#define debug(a) if (df && (vl&a))

/* this is an easy post-malloc check for out of memory conditions: typical
 * usage would be: foo=(char *)malloc(1024); lomem(foo);
 */
#define lomem(a) if ((a)==NULL) {int lomemjunk=__LINE__; fprintf(logF,"Eek!  Out of memory at line %d in "__FILE__" : aborting\n",lomemjunk); exit(255);}

/* a small routine for critical errors */
#define die(a) { perror(a); exit(-1); }

/* used for scratch space sizing */
#define SSIZE 10240


/****************************************************************************/

/* Global variables, expected to be accessed and modified from everywhere */

/* base directory, only really used for information purposes */
extern char *base;

/* a short header to print for help screens 'n such */
extern char *header;

/* config file name and file pointer */
extern char *config;
extern FILE *configF;

/* log file name and file pointer */
extern char *logfile;
extern FILE *logF;

/* debug flag */
extern int df;

/* verbosity level  */
extern int vl;

/* port to listen for incoming clients on */
extern int port;

/* listen socket, and c1, c2, c3, c4 sockets */
extern int s;
extern int c1;
extern int c2;
extern int c3;
extern int c4;

/* general scratch space */
extern char scratch1[];
extern char scratch2[];
extern char scratch3[];

/* secure mode flag */
extern int secure;

/* background flag, internal use */
extern int bg;

/* pointer to executable name */
extern char *execp;

/* pointer to array of argument strings */
extern char **execa;

/* process id */
extern int pid;
