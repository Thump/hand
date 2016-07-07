
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
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>


/* specific hand includes */
#include "hand.h"


int OpenListen()
{
	struct sockaddr_in saddr;
	char hostname[256];
	struct hostent *hp;
	int s;

	debug(GENERAL) fprintf(stderr,"entering OpenListen()\n");

	memset(&saddr, 0, sizeof(saddr));
	saddr.sin_family=AF_INET;
	if ((gethostname(hostname,sizeof(hostname))) != 0) die ("gethostname: ");
	if ((hp=gethostbyname(hostname)) == NULL) die ("gethostbyname(): ");
	memcpy(&saddr.sin_addr,hp->h_addr,hp->h_length);
	saddr.sin_port=htons(port);

	if ((s=socket(AF_INET,SOCK_STREAM,0)) == -1) die("socket(): ");
	if (bind(s,&saddr,sizeof(saddr)) != 0) die("bind(): ");

	return(s);
}


int OpenConnect()
{
	struct sockaddr_in saddr;
	char hostname[256];
	struct hostent *hp;
	int s, result;

	debug(GENERAL) fprintf(stderr,"entering OpenConnect()\n");

	memset(&saddr, 0, sizeof(saddr));
	saddr.sin_family=AF_INET;
	if ((gethostname(hostname,sizeof(hostname))) != 0) die ("gethostname: ");
	if ((hp=gethostbyname(hostname)) == NULL) die ("gethostbyname(): ");
	memcpy(&saddr.sin_addr,hp->h_addr,hp->h_length);
	saddr.sin_port=htons(port);

	if ((s=socket(AF_INET,SOCK_STREAM,0)) == -1) die("socket(): ");

	result=(connect(s,&saddr,sizeof(saddr)))==0;
	close(s);
	return(result);
}


void DoServer(void)
{
	int listenp;
	int temp;
	struct sockaddr_in client;
	int len=sizeof(client);

	listenp=OpenListen();

	if (listen(listenp,5) != 0) die("listen(): ");

	for (;;)
	{
		temp=accept(listenp,(struct sockaddr *)&client,&len);
		sprintf(scratch1,"hand server: receiving connection from: %s\n",
			inet_ntoa(client.sin_addr));
		log(scratch1);
		close(temp);
	}
}
