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

	//���з�����
	void run();


private:
	//��ʾ�������Ƿ����еı���
	uint16_t running;
	//��һ���ͻ���������ʱ��index
	uint16_t next_ind;
	//�����������socket����
	TCPsocket server_socket;
	//�ͻ������飬 clients��socketsһһ��Ӧ
	//Client clients[MAX_SOCKETS];
	SDLNet_SocketSet socket_set;
	TCPsocket sockets[MAX_SOCKETS];


private:
	//��ʼ��
	void init();
	//����socket����ʱ����
	uint16_t acceptSocket(uint16_t index);
	//�ر�����Ϊindex��socket
	void closeSocket(uint16_t index);
	//��������
	void recvData(uint16_t index);
	//��������
	void sendData(uint16_t index, uint8_t* data, uint16_t length, uint16_t flag);
	//�ر�����socket
	void close();
	//�����쳣�ر�socket
	void errorClose(uint16_t index);

	//���������
	shared_ptr<House> house;

};












#endif // ! __SERVER__SOCKET__H__

