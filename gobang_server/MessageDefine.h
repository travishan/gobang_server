#ifndef __MESSAGEDEFINE__H__
#define __MESSAGEDEFINE__H__

#ifdef _WIN32
#include <SDL_net.h>

#else
#include <SDL2/SDL_net.h>

#endif // __WIN32

/*
客户端向服务器发送的消息头   uint16_t类型
*/
#define FLAG_PLAY 0x0011				//下棋
#define FLAG_ASK_REGRET 0x0012	//请求悔棋
#define FLAG_RETURN_REGRET 0x0013  //另一方返回是否同意悔棋
#define FLAG_READY 0x0014   //客户端准备好开始游戏
#define FLAG_RESTART 0x0015 //客户端准备好再开一局

///*
//服务端向客户端发送的消息头  uint16_t类型
//*/
//#define FLAG_WAIT 0x0021				//等待另一个玩家
//#define FLAG_START 0x0022				//开始游戏
//#define FLAG_RUN 0x0023					//等待
//#define FLAG_CHANGE 0x0024			//换边
//#define FLAG_QUERY_REGRET 0x0025//询问另一个
//#define FLAG_REGRETED 0x0026		//悔棋
//#define FLAG_FULL 0x0027					//所有房间都满了
//#define FLAG_END 0x0028					//游戏结束

/*
新的消息类型  服务器发送给客户端
1.发送游戏状态
2.发送玩家信息
3.下棋信息
*/
#define FLAG_GAME_INFO 0x0021			//游戏信息消息
#define FLAG_PLAYER_INFO 0x0022		//玩家信息消息
#define FLAG_PLAY_INFO 0x0023			//下棋消息
#define FLAG_QUERY_REGRET 0x0024	//询问另一方是否同意悔棋

typedef uint16_t FlagType;
typedef uint16_t LengthType;
typedef uint8_t* DataType;


/*
游戏信息消息包格式
*/
typedef struct Game_Message_Struct
{
	uint16_t gameState;//游戏状态
	uint16_t curSide;//当前走棋方
	uint16_t playerNum;
	uint16_t time;//当前走棋方剩余时间
	uint16_t p1Index;
	uint16_t p2Index;
	uint16_t winner;
}Game_Message;

/*
玩家信息消息包格式
*/
typedef struct Player_Message_Struct
{
	uint16_t name[16];
	uint16_t color;//玩家颜色
	uint16_t connected;//是否连接
	uint16_t disconnected;//是否断开
	uint16_t regret;//是否悔棋
	uint16_t roomIndx;//房间号
	uint16_t playerIndex;//玩家号
	uint16_t yourIndex;//你的号
	uint16_t prepared;//是否准备
}Player_Message;


#endif // !__MESSAGEDEFINE__H__

