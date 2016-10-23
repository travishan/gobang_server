#ifndef  __SERVER__SOCKET__H__
#define __SERVER__SOCKET__H__


#include "define.h"
#include <iostream>

using namespace std;


#define MAX_PACKET 1024
#define MAX_SOCKETS 0x10

#define PORT 9088
#define CHECK_INTERVAL 50


typedef struct
{
	int in_use;
	int questing;
	uint8_t amt_wood;
	uint32_t timer_wood;
}Client;

class ServerSocket
{
public:
	ServerSocket() : running(1), next_ind(0), server_socket(nullptr), socket_set(nullptr) {
		for (int i = 0; i < MAX_SOCKETS; ++i) {
			clients[i] = Client();
			sockets[i] = nullptr;
		}
	}


	void run();

	

private:
	//表示服务器是否运行的变量
	int running;
	//下一个客户端连进来时的index
	int next_ind;
	//保存服务器的socket变量
	TCPsocket server_socket;
	//客户端数组， clients和sockets一一对应
	Client clients[MAX_SOCKETS];
	SDLNet_SocketSet socket_set;
	TCPsocket sockets[MAX_SOCKETS];


private:
	//初始化
	void init();
	//当有socket流入时调用
	int acceptSocket(int index);
	//关闭索引为index的socket
	void closeSocket(int index);
	//接收数据
	uint8_t* recvData(int index, uint16_t &length);
	//关闭所有socket
	void close();

};












#endif // ! __SERVER__SOCKET__H__

