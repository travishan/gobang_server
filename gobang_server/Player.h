#ifndef __PLAYER__H__
#define __PLAYER__H__

#include "define.h"

/************************

Player��
������ҵ�Socket
�¹�������
����

************************/
class Player
{
	typedef vector<B_POINT>::iterator recordIterator;
	typedef vector<B_POINT>::size_type size_t;
public:
	Player();
	Player(int socket);
	~Player();

	//��¼һ����
	void addStep(const B_POINT &p);

	//��ȡ���Ӽ�¼��غ���
	recordIterator begin() { return record.begin(); }
	recordIterator end() { return record.end(); }
	size_t size() { return size(); }

	//�Ͽ�����
	void disconnect() { disconnected = true; }

	//get set ��غ���
	void setName(string n) { name = n; }
	string getName() { return name; }
	void setSocketIndex(int s) { socketIndex = s; }
	int getSocketIndex() { return socketIndex; }
	void setConnected(bool con) { connected = con; }
	bool getConnected() { return connected; }
	void setDisconnected(bool dis) { disconnected = dis; }
	bool isDisconnected() { return disconnected; }
	void setRegret(bool reg) { regret = reg; }
	bool getRegret() { return regret; }
	void setColor(CHESS_COLOR c) { color = c; }
	CHESS_COLOR getColor() { return color; }
	void setRoomIndex(int index) { roomIndex = index; }
	int getRoomIndex() { return roomIndex; }
	void setPrepared(bool pre) { prepared = pre; }
	bool getPrepared() { return prepared; }
private:
	/*���id
	*/
	string name;

	/*��ҵ�socket����
	*/
	int socketIndex;

	/*����߹������Ӽ�¼
	*/
	vector<B_POINT> record;

	/*�Ƿ�����
	*/
	bool connected;

	/*�Ƿ�Ͽ�
	*/
	bool disconnected;

	/*�Ƿ����
	*/
	bool regret;

	/*��ɫ
	*/
	CHESS_COLOR color;

	/*�����
	*/
	int roomIndex;

	/*�Ƿ�׼��
	*/
	bool prepared;
};






#endif // !__PLAYER__H__

