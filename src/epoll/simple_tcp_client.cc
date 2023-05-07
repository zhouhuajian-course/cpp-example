#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <ctype.h>
#include <arpa/inet.h>
// #define SERV_PORT 9999


// #include <iostream>
#include <csignal>
// #include <unistd.h>
 
using namespace std;
 
void signalHandler(int sigalNumber)
{
    cout << "Interrupt signal (" << sigalNumber << ") received.\n";
 
    // 清理并关闭
    // 终止程序  
   exit(0);  
}


int main()
{
    // 注册信号 SIGINT 和 信号处理程序
    signal(SIGINT, signalHandler);  

    int socketFd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketFd == -1)
    {
        return -1;
    }

    struct sockaddr_in serverSocketAddress;
    serverSocketAddress.sin_family = AF_INET;
    serverSocketAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    serverSocketAddress.sin_port = htons(8080);

    int result = connect(
        socketFd, (struct sockaddr *)&serverSocketAddress, sizeof(serverSocketAddress)
    );
    if (result == -1)
    {
        return -2;
    }
    // write(socketFd, "connect success\n", 20);

    std::string str; 
    for (;;) {
        std::cout << "输入要发送的数据: " << std::endl; // 输入一个数字并按回车
        std::cin >> str; 
        // std::cout << str;
        write(socketFd, str.c_str(), str.length());
    }

    // while (sockfd != -1)
    // {

    // } // 等待

    close(socketFd);
    // return 0;
}