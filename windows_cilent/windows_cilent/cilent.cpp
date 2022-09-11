#include "cilent.h"

int main(int argc, char* argv[])
{
	WSADATA wsadata;
	if (WSAStartup(MAKEWORD(2, 2), &wsadata) != 0) {
		std::cout << "ÍøÂç¿â¼ÓÔØÊ§°Ü" << std::endl;
		return 0;
	}
	int cilentfd = socket(AF_INET, SOCK_STREAM, 0);
	char buf[256]{ "0" };
	if (cilentfd == -1)
	{
		std::cerr << "Error cilent socket" << std::endl;
		exit(EXIT_FAILURE);
	}
	sockaddr_in cilent;
	cilent.sin_family = AF_INET;
	cilent.sin_port = htons(port);
	inet_pton(AF_INET, ip, &cilent.sin_addr.S_un.S_addr);
	int ret = connect(cilentfd, (sockaddr*)&cilent, sizeof(cilent));
	if (ret == -1)
	{
		closesocket(cilentfd);
		std::cerr << "Error connect" << std::endl;
		exit(EXIT_FAILURE);
	}
	while (true)
	{
		std::cout << "connect successful!" << buf << std::endl;
		std::cin >> buf;
		send(cilentfd, buf, sizeof(buf), NULL);
		recv(cilentfd, buf, sizeof(buf), NULL);
		std::cout << "server:" << buf << std::endl;
	}
	closesocket(cilentfd);
	return 0;
}
