#ifndef __DEFINE__H__
#define __DEFINE__H__


#ifdef _WIN32
#include <SDL.h>
#include <SDL_net.h>

#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_net.h>

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

//客户端向服务器发送的消息头   uint16_t类型
#define FLAG_PLAY 0x0011				//下棋
#define FLAG_ASK_REGRET 0x0012	//请求悔棋
#define FLAG_RETURN_REGRET 0x0013  //另一方返回是否同意悔棋
#define FLAG_READY 0x0014   //客户端准备好开始游戏

//服务端向客户端发送的消息头  uint16_t类型
#define FLAG_WAIT 0x0021				//等待另一个玩家
#define FLAG_START 0x0022				//开始游戏
#define FLAG_RUN 0x0023					//等待
#define FLAG_CHANGE 0x0024			//换边
#define FLAG_QUERY_REGRET 0x0025//询问另一个
#define FLAG_REGRETED 0x0026		//悔棋
#define FLAG_FULL 0x0027					//所有房间都满了
#define FLAG_END 0x0028					//游戏结束

typedef uint16_t FlagType;
typedef uint16_t LengthType;
typedef uint8_t* DataType;

/*
消息包格式
*/
typedef struct
{
	GameState gameState;
	CHESS_COLOR side;
	CHESS_COLOR current;
	uint32_t time;
}Messge;

typedef struct
{
	int row;
	int col;
}B_POINT;

//黑白双方   0代表黑房 1代表白方
enum CHESS_COLOR
{
	B = 0,
	W,
	N
};

//游戏状态  房间中的游戏状态
enum GameState
{
	WAIT = 0,
	START,
	RUN,
	REGRET,
	END
};


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
