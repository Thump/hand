
/*
 * Hand
 *
 * (C) Copyright 1999 Denis McLaughlin
 *
 */


/* some generic includes */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>

/* specific hand includes */
#include "hand.h"


/* This routine opens the log file, setting logF to the file is the open
 * succeeds.  If the open does not succeed, logF is set to stderr
 */

void OpenLog(void)
{
	debug(GENERAL) fprintf(stderr,"entering OpenLog()\n");

	/* attempt to open (char *)log */
	logF = fopen(logfile,"w");
	
	if ( logF == NULL)
	{
		sprintf(scratch1,"Error opening log file %s: %s",
			logfile,sys_errlist[errno]);
		log(scratch1);
	}
	else
	{
		sprintf(scratch1,"Log file %s opened",logfile);
		log(scratch1);
	}
}


/* This routine logs messages: if the log file was not successfully opened,
 * the message is sent to stderr.  If the log file was successfully opened,
 * and the debug flag is not set, messages are sent to the log file.  If
 * the log was successfully opened, and the debug flag is set, messages
 * sent to both the log file and stderr.
 * 
 * It is expected that the message text passed to log() will not have a
 * new line appended, to allow log() to have flexibility in post-processing
 * the results.
 */

void log(char *msgtext)
{
	time_t t;
	struct tm *now;
	char timetext[1024];
	
	debug(GENERAL) fprintf(stderr,"entering log()\n");

	t=time(NULL);
	now=localtime(&t);
	sprintf(timetext,"%d-%02d-%02d %02d:%02d:%02d",now->tm_year+1900,
		now->tm_mon+1,now->tm_mday, now->tm_hour,now->tm_min,now->tm_sec);

	/* not valid log file : message to stderr */
	if ( logF==NULL)
		fprintf(stderr,"%s : %s\n",timetext,msgtext);
	/* valid log file, not debug : message to the log file */
	else if ( logF!=NULL && df==0 )
		fprintf(logF,"%s : %s\n",timetext,msgtext);
	/* valid log file, debug : message to stderr and log file */
	else if ( logF!=NULL && df==1)
	{
		fprintf(logF,"%s (%d) : %s\n",timetext,pid,msgtext);
		fprintf(stderr,"%s (%d) : %s\n",timetext,pid,msgtext);
	}
}
