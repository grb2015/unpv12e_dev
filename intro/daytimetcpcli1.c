/*
	daytimecli version1  更version0 一样。

	uage:
		[root@localhost intro]# ./daytimetcpcli1 127.0.0.1
		Tue Aug 22 09:34:29 2017
		counter = 1
		[root@localhost intro]# 



*/
#include	"unp.h"

int
main(int argc, char **argv)
{
	int					sockfd, n;
    int                 counter = 0;        
	char				recvline[MAXLINE + 1];
	struct sockaddr_in	servaddr;

	if (argc != 2)
		err_quit("usage: a.out <IPaddress>");

	if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		err_sys("socket error");

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port   = htons(13);	/* daytime server */
	if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0)
		err_quit("inet_pton error for %s", argv[1]);

	if (connect(sockfd, (SA *) &servaddr, sizeof(servaddr)) < 0)
		err_sys("connect error");

	while ( (n = read(sockfd, recvline, MAXLINE)) > 0) {
		counter++;      /// what is added in cli1.c     有可能一次读不完，这里统计读了多少次
		recvline[n] = 0;	/* null terminate */
		if (fputs(recvline, stdout) == EOF)
			err_sys("fputs error");
	}
	if (n < 0)
		err_sys("read error");

	printf("counter = %d\n", counter);      /// added in cli1.c 
	exit(0);
}
