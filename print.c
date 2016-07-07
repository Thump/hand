
/*
 * (C) Copyright 1999 Denis McLaughlin
 *
 * Printing routines
 *
 */


/* some generic includes */
#include <stdio.h>
#include <stdlib.h>

/* specific hand includes */
#include "hand.h"


void PrintHeader(void)
{
	debug(GENERAL) fprintf(stderr,"entering PrintHeader()\n");
	printf(header);
	printf("\n");
}

	
void PrintConfig(void)
{
	debug(GENERAL) fprintf(stderr,"entering PrintConfig()\n");

	printf("Defaults:\n");
	printf("    base directory: %s\n",base);
	printf("    configuration file: %s\n",config);
	printf("    log file: %s\n",logfile);
	printf("    listen port: %d\n",port);
	printf("    debug flag: %d\n",df);
	printf("    verbosity level: %d\n",vl);
	printf("    background: %d\n",bg);
	printf("    secure: %d\n",secure);
	printf("    executable: %s\n",execp);
	printf("\n");
}
