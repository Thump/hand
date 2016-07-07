
/*
 * Hand utility
 *
 * (C) Copyright 1999 Brad Black
 *
 */


/* some generic includes */
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#include "hand.h"


/* This routine processes the command line and the config file, with 
 * the command line taking precedence over the config.  In spite of this
 * we still process the command line arguments first, in case we've been
 * told to process a config file other than the default.
 */

void Initialize(int argc, char **argv)
{
	int opt;

	debug(GENERAL) fprintf(stderr,"entering Initialize()\n");

	/* We first skim through the command line switches to see if we've
	 * been pointed to a new config file
	 */	
	while ((opt=getopt(argc,argv,"dv:p:F:L:bs")) != EOF)
	{
		if (opt == 'F')
			config=strdup(optarg);
		
		if (opt == '?')
			Usage();

		lomem(config);
	}
	/* reset optind to 1, so we can reprocess the switches later */
	optind=1;


	/* We read and process the config file */
	ReadConfig();

	/* and then we process the command line switches */
	ReadSwitch(argc,argv);

	/* grab our PID */
	pid=getpid();
	
	/* Open the log file */
	OpenLog();
} 


void ReadConfig(void)
{
	int result1=0,result2=0;
	int linecount=0;

	debug(GENERAL) fprintf(stderr,"entering ReadConfig()\n");

	/* attempt to open config file, error and return if we can't */
	configF=fopen(config,"r");
	if (configF==NULL)
	{
		sprintf(scratch1,"Error opening config %s: %s",
			config,sys_errlist[errno]);
		log(scratch1);
		return;
	}


	/* This while loop steps through the lines in the config file,
	 * parsing those it can figure out, ignoring anything containing
	 * only blanks, or text preceded by a #, and declaring (and then
	 * ignoring) crap.
	 * 
	 * Because of our line limit on fgets, we can only read lines of SSIZE
	 * or less.  At time of writing, set to 10240, it shouldn't be too
	 * much of an issue.
	 */
	while (fgets(scratch1,SSIZE,configF) != NULL)
	{
		/* increment a counter for our lines */
		linecount++;


		/* if its of valid form, try and read it, ignore unknown names */
		result1=sscanf(scratch1," %[^#= \t\n] = %[^#\n]",scratch2,scratch3);
		if (result1 == 2)
		{
			if (!strcmp("logfile",scratch2))
				lomem(logfile=strdup(scratch3));
			
			if (!strcmp("port",scratch2))
				port=atoi(scratch3);
			
			if (!strcmp("debug",scratch2))
				df=atoi(scratch3);
			
			if (!strcmp("verbosity",scratch2))
				vl=atoi(scratch3);
			
			if (!strcmp("secure",scratch2))
				secure=1;

			continue;
		}


		/* see if it matches an ignorable line */
		result1=sscanf(scratch1," %[#]",scratch2);
		result2=sscanf(scratch1," %[\n\r]",scratch2);
		if (result1==1 || result2<0)
		{
			continue;
		}

		
		sprintf(scratch1,"unknown syntax error in %s at line %d: ignored"
			,config,linecount);
		log(scratch1);
	}

	/* close our config file */
	fclose(configF);
}


void ReadSwitch(int argc, char **argv)
{
	int opt;

	debug(GENERAL) fprintf(stderr,"entering ReadSwitch()\n");
	
	/* We step through the command line switches */
	while ((opt=getopt(argc,argv,"dv:p:F:L:bs")) != EOF)
	{
		/* having already read the config file, we ignore -F */
		if (opt == 'F');
		
		if (opt == 'd')
			df=1;
		
		if (opt == 'v')
			vl=atoi(optarg);
		
		if (opt == 'p')
			port=atoi(optarg);
		
		if (opt == 'L')
			lomem(logfile=strdup(optarg));
		
		if (opt == 's')
			secure=1;
		
		if (opt == 'b')
			bg=1;
	}


	/* we set our pointers to the argument and executables, but only
    *  if we're not running in daemon mode */

	if ( !bg )
		if (optind < argc)
		{
			execp=argv[optind];
			execa=argv+optind;
		}
		else
		{
			fprintf(stderr,"\n");
			fprintf(stderr,"error: no program specified\n");
			Usage();
			exit(-1);
		}
}
