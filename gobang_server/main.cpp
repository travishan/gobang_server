#include "define.h"

#include <iostream>
#include <string.h>
#include <string>
#include <vector>
using namespace std;


//int main() {
//	int err;
//	StartSocketLib;
//
//	int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
//	if (sock == -1) {
//		cout << "Socket creation error!" << endl;
//		return 0;
//	}
//	cout << "Socket created!" << endl;
//
//	struct sockaddr_in socketaddress;
//	socklen_t sa_size = sizeof(struct sockaddr_in);
//	socketaddress.sin_family = AF_INET;
//	socketaddress.sin_port = htons(6000);
////	socketaddress.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
//	socketaddress.sin_addr.s_addr = htonl(INADDR_ANY);
//	memset(&(socketaddress.sin_zero), 0, 8);
//
//	//bind
//	err = bind(sock, (struct sockaddr*)&socketaddress, sa_size);
//
//	err = listen(sock, 16);  
//
//	int datasock;
//	datasock = accept(sock, (struct sockaddr*)&socketaddress, &sa_size);
//
//	char buffer[128];
//	err = recv(datasock, buffer, 128, 0);
//
//	cout << "Data received:" << endl;
//	cout << buffer << endl;
//
//	shutdown(datasock, 2);
//	CloseSocket(datasock);
//
//	shutdown(sock, 2);
//
//	CloseSocket(sock);
//
//	CloseSocketLib;
//	return 0;
//}

int main() {
	int err = 0;
	vector<int> socketList;

	StartSocketLib;

	int lsock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (lsock == -1) {
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
	err = bind(lsock, (struct sockaddr*)&socketaddress, sa_size);
	err = listen(lsock, 16);  

	fd_set rset;     //读集
	int i;	//通用迭代变量

	struct timeval zerotime;   //值为0的timeval结构
	zerotime.tv_usec = 0;
	zerotime.tv_sec = 0;

	char buffer[128];
	bool done = false;
	vector<int>::iterator itr;

	while (!done) {
		//清除集合
		FD_ZERO(&rset);
		//添加监听套接字
		FD_SET(lsock, &rset);
		//添加所有数据套接字
		for (itr = socketList.begin(); itr != socketList.end(); ++itr) {
			FD_SET(*itr, &rset);
		}
		i = select(0x7FFFFFFF, &rset, nullptr, nullptr, &zerotime);

		if (i > 0) {
			if (FD_ISSET(lsock, &rset)) {
				//流入连接
				int dsock = accept(lsock, (struct sockaddr*)&socketaddress, &sa_size);
				socketList.push_back(dsock);
				cout << "流入连接" << endl;
			}
			for (itr = socketList.begin(); itr != socketList.end(); ++itr) {
				if (FD_ISSET(*itr, &rset)) {
					//流入数据
					err = recv(*itr, buffer, 128, 0);
					if (err == -1) {
						cout << "Socket receiving error!" << endl;
						return 0;
					}
					//只停止和关闭已经被断开链接的套接字
					if (err == 0) {
						shutdown(*itr, 2);
						CloseSocket(*itr);
						socketList.erase(itr);
						--itr;
					} else {
						cout << "Data: " << buffer << endl;
						if (strcmp(buffer, "servquit") == 0) {
							done = true;
						}
					}
				}
			}
		}
	}
	shutdown(lsock, 2);
	CloseSocket(lsock);

	for (i = 0; i < socketList.size(); ++i) {
		shutdown(socketList[i], 2);
		CloseSocket(socketList[i]);
	}
	CloseSocketLib;
}