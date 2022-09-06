#include <iostream>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

const char* ip = "192.168.160.128";
const int port = 12345;
char buf[256] = {"0"};
