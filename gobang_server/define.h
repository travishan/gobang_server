#ifndef __DEFINE__H__
#define __DEFINE__H__


#ifdef _WIN32
#include <SDL.h>

#else
#include <SDL2/SDL.h>

#endif // __WIN32

#include <vector>
#include <map>
#include <memory>
#include <iostream>
#include <functional>
#include <algorithm>


using namespace std;

#define GRID_MIN 0
#define GRID_NUM 15
#define GRID_COUNT 15*15

typedef struct
{
	int row;
	int col;
}B_POINT;

/*
�ڰ�˫��   0����ڷ� 1����׷�
*/
typedef uint16_t CHESS_COLOR;
#define B 0
#define W 1
#define N 2

/*
��Ϸ״̬  �����е���Ϸ״̬
*/
typedef uint16_t GameState;
#define WAIT 0
#define START 1
#define RUN 2
#define REGRET 3
#define END 4


inline
void fillMatrix(CHESS_COLOR(&a)[15][15], int n) {
	memset(a, n, sizeof(a));
}




//
//#ifdef _WIN32
//	#pragma once
//	#include <WinSock2.h>
//	#include <WS2tcpip.h>
//	//#pragma comment(lib,"ws2_32.lib")
//	#pragma comment(lib,"WS2_32.lib") 
//	
//#else
//	#include <sys/types.h>
//	#include <sys/socket.h>
//	#include <netinet/in.h>
//	#include <unistd.h>
//	#include <netdb.h>
//	#include <arpa/inet.h>
//	
//#endif // WIN32
//
//
//#ifdef _WIN32
//	WSADATA g_wsadata;
//	#define CloseSocket closesocket
//	#define GetSocketError WSAGetLastError
//	#define StartSocketLib WSAStartup( MAKEWORD(2,2), &g_wsadata);
//	#define CloseSocketLib WSACleanup();
//	#ifndef socklen_t
//		typedef int socklen_t;
//	#endif // !socklen_t
//
//#else
//	#define CloseSocket close
//	#define GetSocketError errno
//	#define StartSocketLib {}
//	#define CloseSocketLib {}
//#endif // _WIN32









#endif // !__DEFINE__H__
