/* 
 * version3 :
 *    服务器没变，客户端引入了getsockname 
 *   [root@localhost intro]# ./daytimetcpcli3 127.0.0.1
	 local addr: 127.0.0.1.33081
	 Tue Aug 22 10:23:21 2017
     [root@localhost intro]#
 *
 * */
#include	"unp.h"

int
main(int argc, char **argv)
{
	int					sockfd, n;
	socklen_t			len;
	char				recvline[MAXLINE + 1];
	struct sockaddr_in	servaddr, cliaddr;

	if (argc != 2)
		err_quit("usage: a.out <IPaddress>");

	if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		err_sys("socket error");

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port   = htons(9999);	/* daytime server */
	if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0)
		err_quit("inet_pton error for %s", argv[1]);

	if (connect(sockfd, (SA *) &servaddr, sizeof(servaddr)) < 0)
		err_sys("connect error");

	len = sizeof(cliaddr);

	Getsockname(sockfd, (SA *) &cliaddr, &len); /* 与verison2 不同之处 */
	printf("local addr: %s\n",
		   Sock_ntop((SA *) &cliaddr, sizeof(cliaddr)));

	while ( (n = read(sockfd, recvline, MAXLINE)) > 0) {
		recvline[n] = 0;	/* null terminate */
		if (fputs(recvline, stdout) == EOF)
			err_sys("fputs error");
	}
	if (n < 0)
		err_sys("read error");

	exit(0);
}
