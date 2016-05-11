


#ifndef __NEW_UNP_H__
#define __NEW_UNP_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>                  /*for memset()*/
#include <unistd.h>                 /*for read()*/
#include <errno.h>               /*for errno*/


#include <sys/socket.h>	 /* basic socket definitions */
#include <netinet/in.h>	         /* sockaddr_in{} and other Internet defns */
#include <arpa/inet.h>           /*for inet_pton*/

#define	MAXLINE		4096	/* max text line length */
#define       LISTENQ         1024    /* 2nd argument to listen() */

/* Following shortens all the type casts of pointer arguments */
#define	SA	struct sockaddr

void	 err_dump(const char *, ...);
void	 err_msg(const char *, ...);
void	 err_quit(const char *, ...);
void	 err_ret(const char *, ...);
void	 err_sys(const char *, ...);
#if 0
/* Define bzero() as a macro if it's not in standard C library. */
#ifndef	HAVE_BZERO
#define	bzero(ptr,n)	memset(ptr, 0, n)
/* $$.If bzero$$ */
/* $$.If memset$$ */
#endif
#endif




#endif



