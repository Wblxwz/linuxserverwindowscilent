#include <iostream>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <pthread.h>

struct arg
{
    int *vargp;
    sockaddr_in* cilentaddr;
};

const char* ip = "192.168.160.128";
const int port = 12345;
char buf[256] = {"0"};

void* thread(void* a);
void echo(int connectfd,sockaddr_in* cilentaddr);
