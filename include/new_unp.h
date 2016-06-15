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
#define LISTENQ     1024    /* 2nd argument to listen(),该宏表示系统内核允许在监听描述符上排队的最大客户连接数 */

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

/* Define some port number that can be used for client-servers */
#define	SERV_PORT		 9877			/* TCP and UDP client-servers */


/* prototypes for our socket wrapper functions: see {Sec errors} ,the definition is in wrapsock.c*/
int		 Accept(int, SA *, socklen_t *);
void	 Bind(int, const SA *, socklen_t);
void	 Connect(int, const SA *, socklen_t);
void	 Close(int);

void	 Writen(int, void *, size_t);

/* prototypes for our stdio wrapper functions: see {Sec errors} ,the definition is in wrapstdio.c*/
void	 Fclose(FILE *);
FILE	*Fdopen(int, const char *);
char	*Fgets(char *, int, FILE *);
FILE	*Fopen(const char *, const char *);
void	 Fputs(const char *, FILE *);


/* prototypes for our own library wrapper functions,the definition is in wraplib.c*/
const char		*Inet_ntop(int, const void *, char *, size_t);
void			 Inet_pton(int, const char *, void *);
ssize_t	 readline(int, void *, size_t);

#endif



