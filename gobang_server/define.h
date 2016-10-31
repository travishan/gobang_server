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
	uint16_t row;
	uint16_t col;
}B_POINT;

/*
黑白双方   0代表黑房 1代表白方
*/
typedef uint16_t CHESS_COLOR;
const uint16_t B = 0;
const uint16_t W = 1;
const uint16_t N = 2;

/*
游戏状态  房间中的游戏状态
*/
typedef uint16_t GameState;
#define WAIT 0
#define START 1
#define RUN 2
#define REGRET 3
#define END 4


inline
void fillMatrix(CHESS_COLOR(&a)[15][15], uint16_t n) {
	//memset(a, n, sizeof(a));
	for (int i = 0; i < 15; ++i) {
		for (int j = 0; j < 15; ++j) {
			a[i][j] = n;
		}
	}
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
