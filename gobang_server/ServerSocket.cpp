#include "ServerSocket.h"



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

	memset(&clients[index], 0x00, sizeof(Client));
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

	clients[index].in_use = 1;
	if (SDLNet_TCP_AddSocket(socket_set, sockets[index]) == -1) {
		fprintf(stderr, "ER: SDLNet_TCP_AddSocket: %s\n", SDLNet_GetError());
		exit(-1);
	}
	return 1;
}


uint8_t* ServerSocket::recvData(int index, uint16_t &length) {
	uint8_t tempData[MAX_PACKET];

	int numRecv = SDLNet_TCP_Recv(sockets[index], tempData, MAX_PACKET);
	
	if (numRecv <= 0) {
		closeSocket(index);

		const char* err = SDLNet_GetError();
		if (strlen(err) == 0) {
			cout << "DB: client disconnected\n";
		} else {
			fprintf(stderr, "ER: SDLNet_TCP_Recv: %s\n", err);
		}
		return nullptr;
	} else {
		length = numRecv;

		uint8_t* data = (uint8_t*)malloc(numRecv * sizeof(uint8_t));
		memcpy(data, tempData, numRecv);
		return data;
	}


}

void ServerSocket::run() {

	init();
	while (running) {
		int num_rdy = SDLNet_CheckSockets(socket_set, 50);
		if (num_rdy <= 0) {//没有需要更新的socket，处理逻辑	

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

			int ind;
			for (ind = 0; (ind < MAX_SOCKETS) && num_rdy; ++ind) {
				if (sockets[ind] == nullptr) continue;
				if (!SDLNet_SocketReady(sockets[ind])) continue;

				uint8_t *data;
				uint16_t length;

				data = recvData(ind, length);
				if (data == nullptr) {
					num_rdy--;
					continue;
				}

				/*char *message = new char[length+1];
				memcpy(message,)*/
				char *message = (char*)data;
				cout << "number " << ind << " send a message:  " << message << endl;

				free(message);
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