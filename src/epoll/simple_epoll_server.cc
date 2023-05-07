#include <iostream>
#include <vector>   
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/epoll.h>

using namespace std;

// #define MAX_NUM 1024
// #define SERV_PORT 9999
// #define BUFF_LENGTH 320

class SimpleEpollServer
{
private:
    int serverPort;
    int serverSocketFd;

    int epollEventMaxNum;
    int epollFd;                  // 一个 epoll 实例 对应的 ID
    struct epoll_event * events;  // 发生事件的集合

public:
    SimpleEpollServer();
    int start();
    int createEpoll();
    int epollAdd(int socketFd);
    // int epoll_del(int listenfd);
    // int epoll_mod(int listenfd);
    // int myepoll_wait();
    // struct epoll_event *getEvent();
    ~SimpleEpollServer();
};

SimpleEpollServer::SimpleEpollServer()
{
    this->serverSocketFd = -1;
    this->serverPort = 8080;
    this->epollEventMaxNum = 1024;
}

int SimpleEpollServer::start() 
{
    // 创建 socket 
    serverSocketFd = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocketFd == -1)
    {
        return -1;
    }

    // socket地址
    struct sockaddr_in serverSocketAddress;
    struct sockaddr_in clientSocketAddress;
    socklen_t clientSocketLen;
    // 服务端socket 监听IP和端口
    serverSocketAddress.sin_family = AF_INET;
    serverSocketAddress.sin_addr.s_addr = htonl(INADDR_ANY); 
    serverSocketAddress.sin_port = htons(serverPort);

    // 服务端socket 绑定 IP和端口
    int result = bind(
        serverSocketFd, (struct sockaddr *)&serverSocketAddress, sizeof(serverSocketAddress)
    );
    if (result == -1)
    {
        return -2;
    }

    // listen(sockfd, MAX_LINK_NUM);
    // 开始监听 端口 提供backlog长度
    listen(serverSocketFd, 1024);
    // 创建Epoll多路复用管理器 创建Epoll实例
    createEpoll();
    // epoll 维护两个集合，所有事件集合和有事件发生的集合
    // 把 服务端 socket 加入 epoll
    epollAdd(serverSocketFd);
    printf("Server Started!\n");
    // 死循环
    for (;;)
    { 
        // 等待事件发生 返回发生事件数量 -1一直阻塞，也可设置超时事件
        int number = epoll_wait(epollFd, events, epollEventMaxNum, -1);
        if (number == -1)
        {
            return -5;
        }
        printf("number: %d\n", number);
        // 处理所有事件
        for (int i = 0; i < number; ++i)
        {
            int socketFd = events[i].data.fd;
            // 如果fd是服务端fd，那么是客户端连接事件
            if (socketFd == serverSocketFd)
            {
                // accept接受客户端 (客户端已进入 tcp accept queue)
                int newSocketFd = accept(
                    serverSocketFd, (struct sockaddr *)&clientSocketAddress, &clientSocketLen);
                if (newSocketFd == -1)
                {
                    return -6;
                }
                // 把 fd 注册到 epoll
                epollAdd(newSocketFd);
                printf("accept client: %s\n", inet_ntoa(clientSocketAddress.sin_addr));
            }
            // 其他情况，客户端可读 客户端可写 等 这里只简单处理读
            else
            {
                // 缓冲区 内存
                char inputBuffer[1024];
                // char outputBuffer[1024];
                int result = read(socketFd, inputBuffer, sizeof(inputBuffer));
                // string inputStr = string(inputBuffer);
                // for (int i = 0; i < inputBuffer.size(); i++)
		        //     outputBuffer[i] = toupper(input[i]);
                // write(socketFd, inputBuffer, sizeof(inputBuffer));
                printf("读取数据：%s\n", inputBuffer); 
                // printf("响应数据：%s\n", outputBuffer);
            }
        }
    }
}


int SimpleEpollServer::createEpoll()
{
    epollFd = epoll_create(1);
    if (epollFd == -1)
    {
        return -1;
    }
    if (events != NULL)
    {
        // delete[] events;
    }
    events = new epoll_event[epollEventMaxNum];
    return 0;
}

int SimpleEpollServer::epollAdd(int socketFd)
{
    // 创建一个 epoll event 实例
    struct epoll_event event;
    event.events = EPOLLIN;  // EPOLLIN 读事件感兴趣
    event.data.fd = socketFd;
    return epoll_ctl(epollFd, EPOLL_CTL_ADD, socketFd, &event);
}

// int SimpleEpollServer::epoll_del(int listenfd)
// {
//     struct epoll_event ev;
//     ev.events = EPOLLIN;
//     ev.data.fd = listenfd;
//     return epoll_ctl(epfd, EPOLL_CTL_DEL, listenfd, &ev);
// }

// int SimpleEpollServer::epoll_mod(int listenfd)
// {
//     struct epoll_event ev;
//     ev.events = EPOLLIN;
//     ev.data.fd = listenfd;

//     return epoll_ctl(epfd, EPOLL_CTL_MOD, listenfd, &ev);
// }


// struct epoll_event *SimpleEpollServer::getEvent()
// {
//     return events;
// }


SimpleEpollServer::~SimpleEpollServer()
{
    if (epollFd > 0)
    {
        close(epollFd);
    }

    if (events != NULL)
    {
        delete[] this->events;
        this->events = NULL;
    }
}

int main()
{
    SimpleEpollServer server;
    server.start();
    
}
