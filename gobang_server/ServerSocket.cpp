#include "ServerSocket.h"

ServerSocket::ServerSocket() : running(1), next_ind(0), server_socket(nullptr), socket_set(nullptr), house(make_shared<House>(House())){
	
	for (int i = 0; i < MAX_SOCKETS; ++i) {
		sockets[i] = nullptr;
	}

	using namespace std::placeholders;
	house->setSendFun(bind(&ServerSocket::sendData, this, _1, _2, _3, _4));
}

void ServerSocket::init() {
	if (SDL_Init(SDL_INIT_TIMER | SDL_INIT_EVENTS) != 0) {
		fprintf(stderr, "ER: SDL_Init: %s \n", SDL_GetError());
		exit(-1);
	}
	if (SDLNet_Init() == -1) {
		fprintf(stderr, "ER: SDLNet_Init: %s\n", SDLNet_GetError());
		exit(-1);
	}

	IPaddress ip;
	if (SDLNet_ResolveHost(&ip, nullptr, PORT) == -1) {
		fprintf(stderr, "ER: SDLNet_ResolveHost: %s\n", SDLNet_GetError());
		exit(-1);
	}

	server_socket = SDLNet_TCP_Open(&ip);
	if (server_socket == nullptr) {
		fprintf(stderr, "ER: SDLNet_TCP_Open: %s\n", SDLNet_GetError());
		exit(-1);
	}

	socket_set = SDLNet_AllocSocketSet(MAX_SOCKETS + 1);
	if (socket_set == nullptr) {
		fprintf(stderr, "ER: SDLNet_AllocSocketSet: %s\n", SDLNet_GetError());
		exit(-1);
	}
	if (SDLNet_TCP_AddSocket(socket_set, server_socket) == -1) {
		fprintf(stderr, "ER: SDLNet_TCP_AddSocket: %s\n", SDLNet_GetError());
		exit(-1);
	}
}

void ServerSocket::closeSocket(int index) {
	if (sockets[index] == nullptr) {
		fprintf(stderr, "ER: Attempted to delete a nullptr socket.\n");
		return;
	}

	if (SDLNet_TCP_DelSocket(socket_set, sockets[index]) == -1) {
		fprintf(stderr, "ER: SDLNet_TCP_DelSocket: %s\n", SDLNet_GetError());
		exit(-1);
	}

	house->disconnectPlayer(index);
	//memset(&clients[index], 0x00, sizeof(Client));
	SDLNet_TCP_Close(sockets[index]);
	sockets[index] = nullptr;
}

int ServerSocket::acceptSocket(int index) {
	if (sockets[index]) {
		fprintf(stderr, "ER: Overriding socket at index %d.\n", index);
		closeSocket(index);
	}

	sockets[index] = SDLNet_TCP_Accept(server_socket);
	if (sockets[index] == nullptr) return 0;

	//clients[index].in_use = 1;
	if (SDLNet_TCP_AddSocket(socket_set, sockets[index]) == -1) {
		fprintf(stderr, "ER: SDLNet_TCP_AddSocket: %s\n", SDLNet_GetError());
		exit(-1);
	}

	house->addPlayer(index);
	return 1;
}


void ServerSocket::errorClose(int index) {
	closeSocket(index);

	const char* err = SDLNet_GetError();
	if (strlen(err) == 0) {
		cout << "DB: client disconnected\n";
	} else {
		fprintf(stderr, "ER: SDLNet_TCP_Recv: %s\n", err);
	}
}

void ServerSocket::recvData(int index) {
	uint16_t flag;
	int numRecv = SDLNet_TCP_Recv(sockets[index], &flag, sizeof(uint16_t));

	if (numRecv <= 0) {//若numRecv小于0  则发生异常 关闭socket
		errorClose(index);
		return;
	} else {//否则，接收剩余消息的长度信息
		uint16_t length;
		numRecv = SDLNet_TCP_Recv(sockets[index], &length, sizeof(uint16_t));
		if (numRecv <= 0) {//若numRecv小于0  则发生异常 关闭socket
			errorClose(index);
			return;
		} else if(length > 0) {//若length大于0 ，则接收剩余信息
			uint8_t *tempData = new uint8_t[length];
			numRecv = SDLNet_TCP_Recv(sockets[index], tempData, length);
			if (numRecv <= 0) {//若numRecv小于0  则发生异常 关闭socket
				errorClose(index);
				return;
			} else {
				house->handleRecieveData(index, flag, tempData, length);
			}
		}
	}
}


void ServerSocket::sendData(int index, uint8_t* data, uint16_t length, uint16_t flag) {
	uint8_t tempData[MAX_PACKET];

	int offset = 0;
	memcpy(tempData + offset, &flag, sizeof(uint16_t));
	offset += sizeof(uint16_t);

	memcpy(tempData + offset, &length, sizeof(uint16_t));
	offset += sizeof(uint16_t);

	memcpy(tempData + offset, data, length);
	offset += length;

	int num_sent = SDLNet_TCP_Send(sockets[index], tempData, offset);
	if (num_sent < length) {
		fprintf(stderr, "ER: SDLNet_TCP_Send: %s\n", SDLNet_GetError());
		closeSocket(index);
	}
}

void ServerSocket::run() {

	init();
	while (running) {
		int num_rdy = SDLNet_CheckSockets(socket_set, 50);
		if (num_rdy <= 0) {//没有需要更新的socket，处理逻辑	
			house->run();
		} else {//有socket流入或有数据流入
				//有socket流入
			if (SDLNet_SocketReady(server_socket)) {
				int got_socket = acceptSocket(next_ind);
				if (!got_socket) {
					num_rdy--;
					continue;
				}

				int chk_count;
				for (chk_count = 0; chk_count < MAX_SOCKETS; ++chk_count) {
					if (sockets[(next_ind + chk_count) % MAX_SOCKETS] == nullptr) break;
				}

				next_ind = (next_ind + chk_count) % MAX_SOCKETS;
				cout << "DB: new connection(next_ind = " << next_ind << ")" << endl;

				--num_rdy;
			}

			//有数据流入
			int ind;
			for (ind = 0; (ind < MAX_SOCKETS) && num_rdy; ++ind) {
				if (sockets[ind] == nullptr) continue;
				if (!SDLNet_SocketReady(sockets[ind])) continue;
				recvData(ind);
				--num_rdy;
			}
		}
	}

	close();
	
}


void ServerSocket::close() {
	if (SDLNet_TCP_DelSocket(socket_set, server_socket) == -1) {
		fprintf(stderr, "ER: SDLNet_TCP_DelSocket: %s\n", SDLNet_GetError());
		exit(-1);
	} SDLNet_TCP_Close(server_socket);

	int i;
	for (i = 0; i<MAX_SOCKETS; ++i) {
		if (sockets[i] == nullptr) continue;
		closeSocket(i);
	}

	SDLNet_FreeSocketSet(socket_set);
	SDLNet_Quit();
	SDL_Quit();
}