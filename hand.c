
/*
*  Hand
*
*  (C) Copyright 1999 Denis McLaughlin
* 
*/


/* some generic includes */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


/* specific hand includes */
#include "hand.h"
#include "global.h"


/* program main loop */

int main(int argc, char **argv)
{
	debug(GENERAL) fprintf(stderr,"entering main()\n");


	/* read and parse our config file, and then our command line */
	Initialize(argc,argv);


	/* if we've received the -b flag for background operation, we
	 * drop into the background and listen for incoming requests */
	if ( bg )
	{
		log("running hand server");

		if (fork()==0)
		{
			pid=getpid();
			DoServer();
			exit(1);
		}
		else
		{
			exit(1);
		}
	}


	/* otherwise, we're a client:
	*  - if we're running in secure mode, we immediately execute the
	*    request
	*  - otherwise, we check to see if there is a server running
	*  - if no server is running, we spawn a server, wait a second,
	*    and then try again, lather, rinse, repeat
	*  - if/once a server is running, we contact it to process the
	*    request
	*/
	if (secure)
	{
		log("executing in secure environment");
		execvp(execp,execa);
	}
	else
	{
		log("executing in daemon mode");

		while (!OpenConnect())
		{
			log("server not present");
			if (fork()==0)
			{
				pid=getpid();
				log("attempting to start server");
				execl(argv[0],argv[0],"-b",NULL);
			}
			sleep(1);
		}

		log("server running, now executing command");
		execvp(execp,execa);
	}


	Exit();
	return(0);
} 


void Exit(void)
{
	debug(GENERAL) fprintf(stderr,"entering Exit()\n");

	if ( logF != NULL) fclose(logF);
}


void Usage(void)
{
	fprintf(stderr,"\nUsage:\n");
	fprintf(stderr,"hand [-d] [-v <#>] [-p <#>] [-F <cfg>] [-L <log>] [-s] [-b] -- <program> <args>\n");
	fprintf(stderr,"\n");
	fprintf(stderr,"where:\n");
	fprintf(stderr,"\t-d : enables debug mode\n");
	fprintf(stderr,"\t-v : sets the verbosity level to <vl>\n");
	fprintf(stderr,"\t-p : sets the port to <port>\n");
	fprintf(stderr,"\t-F : uses <config> as the configuration file\n");
	fprintf(stderr,"\t-L : uses <log> as the log file\n");
	fprintf(stderr,"\t-s : runs client in secure (standalone) mode\n");
	fprintf(stderr,"\t-b : start in background (internal use)\n");
	fprintf(stderr,"\n");

	exit(1);
}
