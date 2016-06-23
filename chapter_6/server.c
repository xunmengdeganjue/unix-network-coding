#include "new_unp.h"

str_echo(int sockfd){
	ssize_t n;
	char buf[MAXLINE];
again:
	while((n = read(sockfd,buf,MAXLINE)) > 0)
		Writen(sockfd,buf,n);
	if(n<0&& errno == EINTR)
		goto again;
	else if(n < 0)
		err_sys("str_echo:read error");
}

/*
*    Function Name    : str_calc
*    Create Date      : 2016.06.20
*    Author           : 
*    Description      : do the calculation of the data from the client.
*    Param  Input     : sockfd.				
*    Return Code  1   : void
*    revised History  :
*/
void str_calc(int sockfd){
	long arg1,arg2;
	ssize_t n;
	char line[MAXLINE];
	
	for(;;){
		if((n =Readline(sockfd,line,MAXLINE)) == 0)
			return;	/*connection closed by other end */
		if(sscanf(line, "%ld%ld",&arg1,&arg2) == 2)
			snprintf(line,sizeof(line),"%ld\n",arg1+arg2);
		else
			snprintf(line,sizeof(line),"input error\n");
		n = strlen(line);
		Writen(sockfd,line,n);
	}
}
/*
*    Function Name    : sig_chld
*    Create Date      : 2016.06.15
*    Author           : 
*    Description      : just write data which from the client back to the client.
*    Param  Input     : sockfd.				
*    Return Code  1   : void
*    revised History  :
*/
void sig_chld(int signo){
	pid_t pid;
	int stat;
	
	pid = wait(&stat);
	printf("child %d terminated\n",pid);
	return;
}

int main(int argc,char **argv){
	int listenfd,connfd,i,maxi,maxfd,sockfd;
	int nready,client[FD_SETSIZE];
	ssize_t n;
	fd_set rset, allset;
	char buf[MAXLINE];
	socklen_t clilen;
	struct sockaddr_in cliaddr,servaddr;
	
	listenfd = Socket(AF_INET,SOCK_STREAM, 0);
	
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(SERV_PORT);
	
	Bind(listenfd, (SA *)&servaddr, sizeof(servaddr));
	
	Listen(listenfd, LISTENQ);
	
	maxfd = listenfd; /*initialize*/
	maxi = -1;			/*index into clident[] array*/
	//Signal(SIGCHLD, sig_chld); /*must call waitpid()*/
	for(i = 0; i < FD_SETSIZE; i++)
		client[i] = -1;	/*-1 indicates available entry*/
	FD_ZERO(&allset);
	FD_SET(listenfd, &allset);
	
	for(;;){
		rset = allset;	/* structure assignment */
		nready = Select(maxfd+1, &rset, NULL, NULL, NULL);
		if(FD_ISSET(listenfd, &rset)){	/*new client connection*/
			clilen = sizeof(cliaddr);
			connfd = Accept(listenfd, (SA *)&cliaddr, &clilen);
			
			for(i = 0; i < FD_SETSIZE; i++){
				if(client[i] < 0){
					client[i] = connfd;	/*save descriptor*/
					break;
				}
			}	
			if ( i == FD_SETSIZE )
				err_quit("too many clients");
			FD_SET(connfd, &allset); /*add new descriptor to set*/
			if(connfd > maxfd)
				maxfd = connfd;	/*for select*/
			if(i > maxi)
				maxi = i;		/*max index in client[] array */
			if(--nready <= 0)
				continue; 		/*no more readable descriptors*/
		}
		for(i = 0; i <= maxi; i++){/*check all clients for data*/
			if ((sockfd = client[i] ) < 0)
				continue;
			if(FD_ISSET(sockfd, &rset)){
				if((n = Read(sockfd, buf, MAXLINE)) == 0){
					/*connection closed by client*/
					Close(sockfd);
					FD_CLR(sockfd, &allset);
					client[i] = -1;
				}else
					Writen(sockfd, buf, n);
				
				if(--nready <= 0)
					break;	/*no more readable descriptors*/
			}
		}	
		//Close(connfd);				/*parent closes connectd socket*	
	}
}


