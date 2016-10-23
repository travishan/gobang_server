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
	//��ʾ�������Ƿ����еı���
	int running;
	//��һ���ͻ���������ʱ��index
	int next_ind;
	//�����������socket����
	TCPsocket server_socket;
	//�ͻ������飬 clients��socketsһһ��Ӧ
	Client clients[MAX_SOCKETS];
	SDLNet_SocketSet socket_set;
	TCPsocket sockets[MAX_SOCKETS];


private:
	//��ʼ��
	void init();
	//����socket����ʱ����
	int acceptSocket(int index);
	//�ر�����Ϊindex��socket
	void closeSocket(int index);
	//��������
	uint8_t* recvData(int index, uint16_t &length);
	//�ر�����socket
	void close();

};












#endif // ! __SERVER__SOCKET__H__

