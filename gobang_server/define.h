#ifndef __DEFINE__H__
#define __DEFINE__H__

#ifdef _WIN32
	#pragma once
	#include <WinSock2.h>
	#include <WS2tcpip.h>
	//#pragma comment(lib,"ws2_32.lib")
	#pragma comment(lib,"WS2_32.lib") 
#else
	#include <sys/types.h>
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <unistd.h>
	#include <netdb.h>
	#include <arpa/inet.h>
	
#endif // WIN32


#ifdef _WIN32
	WSADATA g_wsadata;
	#define CloseSocket closesocket
	#define GetSocketError WSAGetLastError
	#define StartSocketLib WSAStartup( MAKEWORD(2,2), &g_wsadata);
	#define CloseSocketLib WSACleanup();
	#ifndef socklen_t
		typedef int socklen_t;
	#endif // !socklen_t

#else
	#define CloseSocket close
	#define GetSocketError errno
	#define StartSocketLib {}
	#define CloseSocketLib {}
#endif // _WIN32


#define MAX_PACKET 0xFF
#define MAX_SOCKETS 0x10

#define WOOD_WAIT_TIME 5000

#define FLAG_QUIT 0x0000
#define FLAG_WOOD_UPDATE 0x0010


//-----------------------------------------------------------------------------
#define FLAG_QUIT 0x0000
#define FLAG_WOOD_QUEST 0x0011
#define FLAG_WOOD_UPDATE 0x0010
#define FLAG_WOOD_GETTIME 0x0012








#endif // !__DEFINE__H__
