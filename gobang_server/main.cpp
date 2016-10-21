#include "define.h"

#include <iostream>
#include <string.h>
using namespace std;


int main() {
	int err;
	StartSocketLib;

	int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock == -1) {
		cout << "Socket creation error!" << endl;
		return 0;
	}
	cout << "Socket created!" << endl;

	struct sockaddr_in socketaddress;
	socklen_t sa_size = sizeof(struct sockaddr_in);
	socketaddress.sin_family = AF_INET;
	socketaddress.sin_port = htons(6000);
//	socketaddress.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	socketaddress.sin_addr.s_addr = htonl(INADDR_ANY);
	memset(&(socketaddress.sin_zero), 0, 8);

	//bind
	err = bind(sock, (struct sockaddr*)&socketaddress, sa_size);

	err = listen(sock, 16);

	int datasock;
	datasock = accept(sock, (struct sockaddr*)&socketaddress, &sa_size);

	char buffer[128];
	err = recv(datasock, buffer, 128, 0);

	cout << "Data received:" << endl;
	cout << buffer << endl;

	shutdown(datasock, 2);
	CloseSocket(datasock);

	shutdown(sock, 2);

	CloseSocket(sock);

	CloseSocketLib;
	return 0;
}