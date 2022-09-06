#include "echo_server.h"

int main(int argc,char *argv[])
{
    int serverfd = socket(AF_INET,SOCK_STREAM,0),connectfd;
    if(serverfd == -1)
    {
        std::cerr << "Error(server socket)" << std::endl;
        //exit(EXIT_FAILURE);
    }
    sockaddr_in serveraddr,cilentaddr;
    socklen_t len = sizeof(cilentaddr);
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(port);
    serveraddr.sin_addr.s_addr = inet_addr(ip);
    int judge = bind(serverfd,(sockaddr*)&serveraddr,sizeof(serveraddr));
    if(judge == -1)
    {
        close(serverfd);
        std::cerr << "Error bind" << std::endl;
        //exit(EXIT_FAILURE);
    }
    judge = listen(serverfd,1024);
    if(judge == -1)
    {
        close(serverfd);
        std::cerr << "Error listen" << std::endl;
        //exit(EXIT_FAILURE);
    }
    while(true)
    {
        connectfd = accept(serverfd,(sockaddr*)&cilentaddr,&len);
        if(serverfd == -1 )
        {
            std::cerr << "Error accept" << std::endl;
            continue;
        }
        std::cout << "connect successful" << std::endl;
        while((judge = read(connectfd,buf,256)))
        {
            std::cout << inet_ntoa(cilentaddr.sin_addr) << ":" << buf << std::endl;
            write(connectfd,buf,256);
        }
        if(judge == 0)
        {
            std::cout << "close cilent!" << std::endl;
        }
        else
        {
            std::cerr << "read Error server!" << std::endl;
        }
        close(connectfd);
    }
    close(serverfd);
    return 0;
}