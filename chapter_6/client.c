#include "new_unp.h"

void str_cli(FILE *fp, int sockfd){
 	char sendline[MAXLINE], recvline[MAXLINE];
 	
 	while(Fgets(sendline, MAXLINE, fp) != NULL){
 		Writen(sockfd, sendline, strlen(sendline));
 		if(Readline(sockfd,recvline,MAXLINE) == 0)
 			err_quit("str_cli:server terminated prematurely");
 		Fputs(recvline, stdout);
 	}
 }
 
/*
*    Function Name    : str_cli_twice
*    Create Date      : 2016.06.15
*    Author           : 
*    Description      : 
*    Param  Input     :			
*    Return Code  1   : void
*    revised History  :
*/ 
void str_cli_twice(FILE *fp, int sockfd){
	
	char sendline[MAXLINE], recvline[MAXLINE];
	
	while(Fgets(sendline, MAXLINE, fp) != NULL){
		Writen(sockfd, sendline, strlen(sendline));
		sleep(1);
		Writen(sockfd, sendline, strlen(sendline)-1 );
		if(Readline(sockfd,recvline,MAXLINE) == 0)
			err_quit("str_cli:server terminated prematurely");
		Fputs(recvline, stdout);
	}
	
}

/*
*    Function Name    : str_cli_select
*    Create Date      : 2016.06.22
*    Author           : 
*    Description      : This function used the select() function to show the I/O
		multiplexing function of the unix network.
*    Param  Input     :			
*    Return Code  1   : void
*    revised History  :
*/
void str_cli_select( FILE *fp, int sockfd){

	int maxfdpl;
	fd_set rset; /* Declare a descriptor set used to check the readability */
	char sendline[MAXLINE], recvline[MAXLINE];
	
	FD_ZERO(&rset);
	
	for(;;){
			FD_SET(fileno(fp), &rset);
			FD_SET(sockfd, &rset);
			maxfdpl = max(fileno(fp), sockfd) +1;
			
			Select(maxfdpl, &rset, NULL, NULL, NULL);
			
			if(FD_ISSET(sockfd, &rset)){ /*socket is readable*/
				if(Readline(sockfd,recvline,MAXLINE) == 0 )
					err_quit("str_cli:server terminated prematurely");
				Fputs(recvline, stdout);
			}
			if(FD_ISSET(fileno(fp), &rset)){/*input is readable*/
				if(Fgets(sendline, MAXLINE, fp) == NULL)
					return ; 	/*all done*/
				Writen(sockfd,sendline,strlen(sendline));			
			}
	}
}

int main(int argc, char *argv[]){
	int sockfd;
	struct sockaddr_in servaddr;
	
	if(argc != 2)
		err_quit("usage: tcpcli <IPaddress>");
	
	sockfd = Socket(AF_INET, SOCK_STREAM, 0);
	
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);
	Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
	/*create the connection with the server.*/
	Connect(sockfd, (SA *)&servaddr, sizeof(servaddr));
	
	str_cli_select(stdin,sockfd);
	
	exit(0);
}
