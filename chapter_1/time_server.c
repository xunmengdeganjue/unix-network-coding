#include<stdio.h>
#include<time.h>

#include <sys/socket.h>	 /* basic socket definitions */
#include <netinet/in.h>	         /* sockaddr_in{} and other Internet defns */
#include <arpa/inet.h>           /*for inet_pton*/
#include "new_unp.h"

int main(){
	int listenfd,connfd;
	struct sockaddr_in servaddr;
	char buff[MAXLINE];
	time_t ticks;
	
	listenfd = Socket(AF_INET, SOCK_STREAM, 0);
	
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(13);
	
	Bind(listenfd,(SA *) &servaddr, sizeof(servaddr));
	
	Listen(listenfd, LISTENQ);
	
	for(;;){
		connfd = Accept(listenfd,(SA *) NULL, NULL);
		
		ticks = time(NULL);
		snprintf(buff,sizeof(buff),"%.24s\r\n",ctime(&ticks));
		Writen(connfd,buff,strlen(buff));
		
		Close(connfd);
		
	}
	
	
	
	
	
}






