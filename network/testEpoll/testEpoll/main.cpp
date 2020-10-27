#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>

#define OPEN_MAX 100

using namespace std;

int main()
{
	struct epoll_event event;
	struct epoll_event wait_event;

	//监听套接字创建
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in my_addr;
	bzero(&my_addr, sizeof(my_addr));
	my_addr.sin_family = AF_INET;
	my_addr.sin_port = htons(8001);
	my_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	bind(sockfd, (struct sockaddr *)&my_addr, sizeof(my_addr));

	listen(sockfd, 10);

	int fd[OPEN_MAX];
	int i = 0, maxi = 0;
	memset(fd, -1, sizeof(fd));
	fd[0] = sockfd;

	//epoll_create
	int epfd = epoll_create(10);
	if (-1 == epfd)
	{
		perror("epoll_create");
		return -1;
	}

	//epoll_ctl 注册监听套接字
	event.data.fd = sockfd;
	event.events = EPOLLIN;
	int ret = epoll_ctl(epfd, EPOLL_CTL_ADD, sockfd, &event);
	if (-1 == ret)
	{
		perror("epoll_ctl");
	}

	//epoll_wait
	//1.检测监听套接字
	//	1.1保存客户端连接
	//	1.2客户端连接加入epoll监测
	//2.检测客户端套接字
	//	2.1recv客户端发来的数据
	//	2.2数据原样send回客户端
	while (true)
	{
		ret = epoll_wait(epfd, &wait_event, maxi + 1, -1);
		cout << "epoll_wait ready" << endl;
	
		//1.检测监听套接字
		if (sockfd == wait_event.data.fd && (EPOLLIN == wait_event.events & EPOLLIN))
		{
			struct sockaddr_in client_addr;
			socklen_t clientLen = sizeof(client_addr);

			int connfd = accept(sockfd, (struct sockaddr*)&client_addr, &clientLen);

			for (i = 1; i < OPEN_MAX; i++)
			{
				if (fd[i] < 0)
				{
					//1.1保存客户端连接
					fd[i] = connfd;
					event.data.fd = connfd;
					event.events = EPOLLIN;

					//1.2客户端连接加入epoll监测
					ret = epoll_ctl(epfd, EPOLL_CTL_ADD, connfd, &event);
					if (-1 == ret)
					{
						perror("epoll_ctl");
					}
					break;
				}
			}

			if (i > maxi)
				maxi = i;
		}

		//2.检测客户端套接字
		for (i = 1; i <= maxi; i++)
		{
			if (fd[i] < 0)
				continue;

			if (fd[i] == wait_event.data.fd && (EPOLLIN == wait_event.events & (EPOLLIN | EPOLLERR) ))
			{
				int len = 0;
				char buf[128] = "";

				//2.1recv客户端发来的数据
				len = recv(fd[i], buf, sizeof(buf), 0);
				if (len < 0)
				{
					if (errno == ECONNRESET)
					{
						close(fd[i]);
						fd[i] = -1;
					}
					else
						perror("read error:");
				}
				else if (len == 0)
				{
					close(fd[i]);
					fd[i] = -1;
				}
				else
				{//2.2数据原样send回客户端
					send(fd[i], buf, len, 0);
				}
			}
		}

		sleep(1);
	}

	return 0;
}