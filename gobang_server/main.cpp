
#include "ServerSocket.h"



int main(int argc, char** argv) {
	ServerSocket server;

	server.run();

	return 0;
}


//typedef struct
//{
//	int in_use;
//	int questing;
//	uint8_t amt_wood;
//	uint32_t timer_wood;
//}Client;
//
//
//int running = 1;
//int next_ind = 0;
//TCPsocket server_socket;
//Client clients[MAX_SOCKETS];
//SDLNet_SocketSet socket_set;
//TCPsocket sockets[MAX_SOCKETS];
//
//
//void CloseSocket(int index) {
//	if (sockets[index] == nullptr) {
//		fprintf(stderr, "ER: Attempted to delete a nullptr socket.\n");
//		return;
//	}
//
//	if (SDLNet_TCP_DelSocket(socket_set, sockets[index]) == -1) {
//		fprintf(stderr, "ER: SDLNet_TCP_DelSocket: %s\n", SDLNet_GetError());
//		exit(-1);
//	}
//
//	memset(&clients[index], 0x00, sizeof(Client));
//	SDLNet_TCP_Close(sockets[index]);
//	sockets[index] = nullptr;
//}
//
//int AcceptSocket(int index) {
//	if (sockets[index]) {
//		fprintf(stderr, "ER: Overriding socket at index %d.\n", index);
//		CloseSocket(index);
//	}
//
//	sockets[index] = SDLNet_TCP_Accept(server_socket);
//	if (sockets[index] == nullptr) return 0;
//
//	clients[index].in_use = 1;
//	if (SDLNet_TCP_AddSocket(socket_set, sockets[index]) == -1) {
//		fprintf(stderr, "ER: SDLNet_TCP_AddSocket: %s\n", SDLNet_GetError());
//		exit(-1);
//	}
//
//	return 1;
//}
//
//
//uint8_t* RecvData(int index, uint16_t* length) {
//	uint8_t temp_data[MAX_PACKET];
//	int num_recv = SDLNet_TCP_Recv(sockets[index], temp_data, MAX_PACKET);
//
//	if (num_recv <= 0) {
//		CloseSocket(index);
//
//		const char* err = SDLNet_GetError();
//		if (strlen(err) == 0) {
//			cout << "DB: client disconnected\n";
//		} else {
//			fprintf(stderr, "ER: SDLNet_TCP_Recv: %s\n", err);
//		}
//		return nullptr;
//	} else {	
//		*length = num_recv;
//
//		uint8_t* data = (uint8_t*)malloc(num_recv * sizeof(uint8_t));
//		memcpy(data, temp_data, num_recv);
//
//		return data;
//	}
//}
//
//void SendData(int index, uint8_t* data, uint16_t length, uint16_t flag) {
//	uint8_t temp_data[MAX_PACKET];
//
//	int offset = 0;
//	memcpy(temp_data + offset, &flag, sizeof(uint16_t));
//	offset += sizeof(uint16_t);
//	memcpy(temp_data + offset, data, length);
//	offset += length;
//
//	int num_sent = SDLNet_TCP_Send(sockets[index], temp_data, offset);
//	if (num_sent < offset) {
//		fprintf(stderr, "ER: SDLNet_TCP_Send: %s\n", SDLNet_GetError());
//		CloseSocket(index);
//	}
//}
//
//
//void ProcessData(int index, uint8_t* data, uint16_t* offset) {
//	if (data == NULL) return;
//
//	uint16_t flag = *(uint16_t*)&data[*offset];
//	*offset += sizeof(uint16_t);
//
//	switch (flag) {
//	case FLAG_WOOD_UPDATE:
//	{
//		uint16_t send_offset = 0;
//		uint8_t send_data[MAX_PACKET];
//
//		memcpy(send_data + send_offset, &clients[index].amt_wood, sizeof(uint8_t));
//		send_offset += sizeof(uint8_t);
//
//		SendData(index, send_data, send_offset, FLAG_WOOD_UPDATE);
//	} break;
//
//	case FLAG_WOOD_GETTIME:
//	{
//		uint16_t send_offset = 0;
//		uint8_t send_data[MAX_PACKET];
//
//		uint32_t time_left;
//		if (clients[index].questing) {
//			time_left = WOOD_WAIT_TIME - (SDL_GetTicks() - clients[index].timer_wood);
//		} else time_left = 0;
//
//		memcpy(send_data + send_offset, &time_left, sizeof(uint32_t));
//		send_offset += sizeof(uint32_t);
//
//		SendData(index, send_data, send_offset, FLAG_WOOD_GETTIME);
//	} break;
//
//	case FLAG_WOOD_QUEST:
//	{
//		if (!clients[index].questing) {
//			clients[index].questing = 1;
//			clients[index].timer_wood = SDL_GetTicks();
//		}
//	} break;
//
//	case FLAG_QUIT:
//	{
//		running = 0;
//		printf("DB: shutdown by client id: %d\n", index);
//	} break;
//	}
//}
//
//
//
//
//
//int main(int argc, char **argv) {
//	
//	if (SDL_Init(SDL_INIT_TIMER | SDL_INIT_EVENTS) != 0) {
//		fprintf(stderr, "ER: SDL_Init: %s \n", SDL_GetError());
//		exit(-1);
//	}
//	if (SDLNet_Init() == -1) {
//		fprintf(stderr, "ER: SDLNet_Init: %s\n", SDLNet_GetError());
//		exit(-1);
//	}
//
//	IPaddress ip;
//	if (SDLNet_ResolveHost(&ip, nullptr, 8099) == -1) {
//		fprintf(stderr, "ER: SDLNet_ResolveHost: %s\n", SDLNet_GetError());
//		exit(-1);
//	}
//	server_socket = SDLNet_TCP_Open(&ip);
//	if (server_socket == nullptr) {
//		fprintf(stderr, "ER: SDLNet_TCP_Open: %s\n", SDLNet_GetError());
//		exit(-1);
//	}
//	socket_set = SDLNet_AllocSocketSet(MAX_SOCKETS + 1);
//	if (socket_set == nullptr) {
//		fprintf(stderr, "ER: SDLNet_AllocSocketSet: %s\n", SDLNet_GetError());
//		exit(-1);
//	}
//	if (SDLNet_TCP_AddSocket(socket_set, server_socket) == -1) {
//		fprintf(stderr, "ER: SDLNet_TCP_AddSocket: %s\n", SDLNet_GetError());
//		exit(-1);
//	}
//
//	
//
//	while (running) {
//		int num_rdy = SDLNet_CheckSockets(socket_set, 50);
//		if (num_rdy <= 0) {
//			int ind;
//			for (ind = 0; ind<MAX_SOCKETS; ++ind) {
//				if (!clients[ind].in_use) continue;
//
//				if (clients[ind].questing && (SDL_GetTicks() - clients[ind].timer_wood) > WOOD_WAIT_TIME) {
//					clients[ind].questing = 0;
//					clients[ind].amt_wood += 4;
//					SendData(ind, NULL, 0, FLAG_WOOD_QUEST);
//
//					uint16_t send_offset = 0;
//					uint8_t send_data[MAX_PACKET];
//
//					memcpy(send_data + send_offset, &clients[ind].amt_wood, sizeof(uint8_t));
//					send_offset += sizeof(uint8_t);
//
//					SendData(ind, send_data, send_offset, FLAG_WOOD_UPDATE);
//				}
//
//				uint16_t send_offset = 0;
//				uint8_t send_data[MAX_PACKET];
//
//				uint32_t time_left;
//				if (clients[ind].questing) {
//					time_left = WOOD_WAIT_TIME - (SDL_GetTicks() - clients[ind].timer_wood);
//				} else time_left = 0;
//
//				memcpy(send_data + send_offset, &time_left, sizeof(uint32_t));
//				send_offset += sizeof(uint32_t);
//
//				SendData(ind, send_data, send_offset, FLAG_WOOD_GETTIME);
//			}
//		} else {
//			//check server_socket whether we have a new client connection
//			if (SDLNet_SocketReady(server_socket)) {
//				int got_socket = AcceptSocket(next_ind);
//				if (!got_socket) {
//					num_rdy--;
//					continue;
//				}
//
//				// NOTE: get a new index
//				int chk_count;
//				for (chk_count = 0; chk_count<MAX_SOCKETS; ++chk_count) {
//					if (sockets[(next_ind + chk_count) % MAX_SOCKETS] == nullptr) break;
//				}
//
//				next_ind = (next_ind + chk_count) % MAX_SOCKETS;
//				printf("DB: new connection (next_ind = %d)\n", next_ind);
//
//				num_rdy--;
//			}
//
//
//			int ind;
//			for (ind = 0; (ind<MAX_SOCKETS) && num_rdy; ++ind) {
//				if (sockets[ind] == nullptr) continue;
//				if (!SDLNet_SocketReady(sockets[ind])) continue;
//
//				uint8_t* data;
//				uint16_t length;
//
//				data = RecvData(ind, &length);
//				if (data == nullptr) {
//					num_rdy--;
//					continue;
//				}
//
//				int num_processed = 0;
//				uint16_t offset = 0;
//				while (offset < length) {
//					num_processed++;
//					ProcessData(ind, data, &offset);
//				}
//				printf("num_processed from ID: %d was %d\n", ind, num_processed);
//				fflush(stdout);
//
//				free(data);
//				num_rdy--;
//			}
//		}
//	}
//
//	if (SDLNet_TCP_DelSocket(socket_set, server_socket) == -1) {
//		fprintf(stderr, "ER: SDLNet_TCP_DelSocket: %s\n", SDLNet_GetError());
//		exit(-1);
//	} SDLNet_TCP_Close(server_socket);
//
//	int i;
//	for (i = 0; i<MAX_SOCKETS; ++i) {
//		if (sockets[i] == nullptr) continue;
//		CloseSocket(i);
//	}
//
//	SDLNet_FreeSocketSet(socket_set);
//	SDLNet_Quit();
//	SDL_Quit();
//
//
//	return 0;
//}



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

//int main() {
//	int err = 0;
//	vector<int> socketList;
//
//	StartSocketLib;
//
//	int lsock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
//	if (lsock == -1) {
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
//	err = bind(lsock, (struct sockaddr*)&socketaddress, sa_size);
//	err = listen(lsock, 16);  
//
//	fd_set rset;     //读集
//	int i;	//通用迭代变量
//
//	struct timeval zerotime;   //值为0的timeval结构
//	zerotime.tv_usec = 0;
//	zerotime.tv_sec = 0;
//
//	char buffer[128];
//	bool done = false;
//	vector<int>::iterator itr;
//
//	while (!done) {
//		//清除集合
//		FD_ZERO(&rset);
//		//添加监听套接字
//		FD_SET(lsock, &rset);
//		//添加所有数据套接字
//		for (itr = socketList.begin(); itr != socketList.end(); ++itr) {
//			FD_SET(*itr, &rset);
//		}
//		i = select(0x7FFFFFFF, &rset, nullptr, nullptr, &zerotime);
//
//		if (i > 0) {
//			if (FD_ISSET(lsock, &rset)) {
//				//流入连接
//				int dsock = accept(lsock, (struct sockaddr*)&socketaddress, &sa_size);
//				socketList.push_back(dsock);
//				cout << "流入连接" << endl;
//			}
//			for (itr = socketList.begin(); itr != socketList.end(); ++itr) {
//				if (FD_ISSET(*itr, &rset)) {
//					//流入数据
//					err = recv(*itr, buffer, 128, 0);
//					if (err == -1) {
//						cout << "Socket receiving error!" << endl;
//						return 0;
//					}
//					//只停止和关闭已经被断开链接的套接字
//					if (err == 0) {
//						shutdown(*itr, 2);
//						CloseSocket(*itr);
//						socketList.erase(itr);
//						--itr;
//					} else {
//						cout << "Data: " << buffer << endl;
//						if (strcmp(buffer, "servquit") == 0) {
//							done = true;
//						}
//					}
//				}
//			}
//		}
//	}
//	shutdown(lsock, 2);
//	CloseSocket(lsock);
//
//	for (i = 0; i < socketList.size(); ++i) {
//		shutdown(socketList[i], 2);
//		CloseSocket(socketList[i]);
//	}
//	CloseSocketLib;
//}

