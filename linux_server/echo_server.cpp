#include "echo_server.h"

void echo(int connectfd, sockaddr_in* cilentaddr)
{
    int judge = 0;
    while ((judge = read(connectfd, buf, 256)))
    {
        std::cout << inet_ntoa(cilentaddr->sin_addr) << ":" << buf << std::endl;
        write(connectfd, buf, 256);
    }
    if (judge == 0)
    {
        std::cout << "close cilent!" << std::endl;
    }
    else
    {
        std::cerr << "read Error server!" << std::endl;
    }
}

void* thread(void* a)
{
    arg* aa = (arg*)a;
    int connfd = *(aa->vargp);
    pthread_detach(pthread_self());
    delete(aa->vargp);
    echo(connfd, aa->cilentaddr);
    close(connfd);
    return NULL;
}

int main(int argc, char* argv[])
{
    pthread_t pid;
    int* connefd, serverfd, judge;
    sockaddr_in server, * cilent;
    socklen_t len = sizeof(*cilent);
    serverfd = socket(AF_INET, SOCK_STREAM, 0);
    if (serverfd == -1)
    {
        std::cerr << "Error(server socket)" << std::endl;
        //exit(EXIT_FAILURE);
    }
    server.sin_port = htons(port);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(ip);
    judge = bind(serverfd, (sockaddr*)&server, sizeof(server));
    if (judge == -1)
    {
        close(serverfd);
        std::cerr << "Error bind" << std::endl;
        //exit(EXIT_FAILURE);
    }
    judge = listen(serverfd, 1024);
    if (judge == -1)
    {
        close(serverfd);
        std::cerr << "Error listen" << std::endl;
        //exit(EXIT_FAILURE);
    }
    while (true)
    {
        arg* a = new arg;
        connefd = new int;
        cilent = new sockaddr_in;
        *connefd = accept(serverfd, (sockaddr*)cilent, &len);
        a->cilentaddr = cilent;
        a->vargp = connefd;
        pthread_create(&pid, NULL, thread, a);
        if (serverfd == -1)
        {
            std::cerr << "Error accept" << std::endl;
            continue;
        }
        std::cout << "connect successful" << std::endl;
    }
    close(serverfd);
    return 0;
}
