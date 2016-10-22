#ifndef __DEFINE__H__
#define __DEFINE__H__


#ifdef _WIN32
#include <SDL.h>
#include <SDL_net.h>

#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_net.h>

#endif // __WIN32



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
