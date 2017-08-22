/*  daytimeserver version1 : 
 *  
 *  服务器端可以打印出连接的客户IP和port
 *
 *
 * uage:
 		[root@localhost intro]# ./daytimetcpsrv1
 		// a cli connecetd
		connection from 127.0.0.1, port 54079


 * */
#include	"unp.h"
#include	<time.h>

int
main(int argc, char **argv)
{
	int					listenfd, connfd;
	socklen_t			len;
	struct sockaddr_in	servaddr, cliaddr;
	char				buff[MAXLINE];
	time_t				ticks;

	listenfd = Socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family      = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port        = htons(13);	/* daytime server */

	Bind(listenfd, (SA *) &servaddr, sizeof(servaddr));

	Listen(listenfd, LISTENQ);

	for ( ; ; ) {
		len = sizeof(cliaddr);
		connfd = Accept(listenfd, (SA *) &cliaddr, &len);      /// addd in server1.c  server0.c中都为NULL

        /* 打印出链接的客户IP和端口号 */
		printf("connection from %s, port %d\n",
			   Inet_ntop(AF_INET, &cliaddr.sin_addr, buff, sizeof(buff)),		// 将二进制的IP 地址转为人们易读的形式
			   ntohs(cliaddr.sin_port));		/// 将网络字节序的port转为主机字节序的port

        ticks = time(NULL);
        snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
        Write(connfd, buff, strlen(buff));

		Close(connfd);
	}
}
