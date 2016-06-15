


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

/* prototypes for our socket wrapper functions: see {Sec errors} */
int		 Accept(int, SA *, socklen_t *);
void	 Bind(int, const SA *, socklen_t);
void	 Connect(int, const SA *, socklen_t);
void	 Close(int);



#endif



