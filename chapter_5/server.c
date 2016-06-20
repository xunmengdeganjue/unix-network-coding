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
	int listenfd,connfd;
	pid_t childpid;
	socklen_t clilen;
	struct sockaddr_in cliaddr,servaddr;
	
	listenfd = Socket(AF_INET,SOCK_STREAM, 0);
	
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(SERV_PORT);
	
	Bind(listenfd, (SA *)&servaddr, sizeof(servaddr));
	
	Listen(listenfd, LISTENQ);
	
	Signal(SIGCHLD, sig_chld); /*must call waitpid()*/
	
	for(;;){
		clilen = sizeof(cliaddr);
		if((connfd = accept(listenfd, (SA *) &(cliaddr),&clilen)) < 0){
			if( errno == EINTR)
				continue;
			else
				err_sys("accept error!");
		}
		
		if((childpid = Fork()) == 0){ /*child process*/
			Close(listenfd);		/*close listening socket*/	
			//str_echo(connfd);		/*process the request*/
			str_calc(connfd);
			exit(0);
		}
		Close(connfd);				/*parent closes connectd socket*/
		
	}
}


