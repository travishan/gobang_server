#ifndef  __SERVER__SOCKET__H__
#define __SERVER__SOCKET__H__


#include "define.h"
#include "MessageDefine.h"
#include "House.h"

#define MAX_PACKET 1024
#define MAX_SOCKETS 0x10

#define PORT 9088
#define CHECK_INTERVAL 50





class ServerSocket
{
public:
	ServerSocket();

	//运行服务器
	void run();


private:
	//表示服务器是否运行的变量
	uint16_t running;
	//下一个客户端连进来时的index
	uint16_t next_ind;
	//保存服务器的socket变量
	TCPsocket server_socket;
	//客户端数组， clients和sockets一一对应
	//Client clients[MAX_SOCKETS];
	SDLNet_SocketSet socket_set;
	TCPsocket sockets[MAX_SOCKETS];


private:
	//初始化
	void init();
	//当有socket流入时调用
	uint16_t acceptSocket(uint16_t index);
	//关闭索引为index的socket
	void closeSocket(uint16_t index);
	//接收数据
	void recvData(uint16_t index);
	//发送数据
	void sendData(uint16_t index, uint8_t* data, uint16_t length, uint16_t flag);
	//关闭所有socket
	void close();
	//发生异常关闭socket
	void errorClose(uint16_t index);

	//房间管理类
	shared_ptr<House> house;

};












#endif // ! __SERVER__SOCKET__H__

