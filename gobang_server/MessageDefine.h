#ifndef __MESSAGEDEFINE__H__
#define __MESSAGEDEFINE__H__

#ifdef _WIN32
#include <SDL_net.h>

#else
#include <SDL2/SDL_net.h>

#endif // __WIN32

/*
�ͻ�������������͵���Ϣͷ   uint16_t����
*/
#define FLAG_PLAY 0x0011				//����
#define FLAG_ASK_REGRET 0x0012	//�������
#define FLAG_RETURN_REGRET 0x0013  //��һ�������Ƿ�ͬ�����
#define FLAG_READY 0x0014   //�ͻ���׼���ÿ�ʼ��Ϸ
#define FLAG_RESTART 0x0015 //�ͻ���׼�����ٿ�һ��

///*
//�������ͻ��˷��͵���Ϣͷ  uint16_t����
//*/
//#define FLAG_WAIT 0x0021				//�ȴ���һ�����
//#define FLAG_START 0x0022				//��ʼ��Ϸ
//#define FLAG_RUN 0x0023					//�ȴ�
//#define FLAG_CHANGE 0x0024			//����
//#define FLAG_QUERY_REGRET 0x0025//ѯ����һ��
//#define FLAG_REGRETED 0x0026		//����
//#define FLAG_FULL 0x0027					//���з��䶼����
//#define FLAG_END 0x0028					//��Ϸ����

/*
�µ���Ϣ����  ���������͸��ͻ���
1.������Ϸ״̬
2.���������Ϣ
3.������Ϣ
*/
#define FLAG_GAME_INFO 0x0021			//��Ϸ��Ϣ��Ϣ
#define FLAG_PLAYER_INFO 0x0022		//�����Ϣ��Ϣ
#define FLAG_PLAY_INFO 0x0023			//������Ϣ
#define FLAG_QUERY_REGRET 0x0024	//ѯ����һ���Ƿ�ͬ�����

typedef uint16_t FlagType;
typedef uint16_t LengthType;
typedef uint8_t* DataType;


/*
��Ϸ��Ϣ��Ϣ����ʽ
*/
typedef struct Game_Message_Struct
{
	uint16_t gameState;//��Ϸ״̬
	uint16_t curSide;//��ǰ���巽
	uint16_t playerNum;
	uint16_t time;//��ǰ���巽ʣ��ʱ��
	uint16_t p1Index;
	uint16_t p2Index;
	uint16_t winner;
}Game_Message;

/*
�����Ϣ��Ϣ����ʽ
*/
typedef struct Player_Message_Struct
{
	uint16_t name[16];
	uint16_t color;//�����ɫ
	uint16_t connected;//�Ƿ�����
	uint16_t disconnected;//�Ƿ�Ͽ�
	uint16_t regret;//�Ƿ����
	uint16_t roomIndx;//�����
	uint16_t playerIndex;//��Һ�
	uint16_t yourIndex;//��ĺ�
	uint16_t prepared;//�Ƿ�׼��
}Player_Message;


#endif // !__MESSAGEDEFINE__H__

