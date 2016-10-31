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
	Player(uint16_t socket);
	~Player();

	//��¼һ����
	void addStep(const B_POINT &p);

	//��ȡ���Ӽ�¼��غ���
	recordIterator begin() { return record.begin(); }
	recordIterator end() { return record.end(); }
	size_t size() { return size(); }
	void push_back(const B_POINT &b) { record.push_back(b); }
	const B_POINT &front() { return record.front(); }

	//�Ͽ�����
	void disconnect() { disconnected = true; }

	//get set ��غ���
	void setName(string n) { name = n; }
	string getName() { return name; }
	void setSocketIndex(uint16_t s) { socketIndex = s; }
	uint16_t getSocketIndex() { return socketIndex; }
	void setConnected(bool con) { connected = con; }
	bool getConnected() { return connected; }
	void setDisconnected(bool dis) { disconnected = dis; }
	bool isDisconnected() { return disconnected; }
	void setRegret(bool reg) { regret = reg; }
	bool getRegret() { return regret; }
	void setColor(CHESS_COLOR c) { color = c; }
	CHESS_COLOR getColor() { return color; }
	void setRoomIndex(uint16_t index) { roomIndex = index; }
	uint16_t getRoomIndex() { return roomIndex; }
	void setPrepared(bool pre) { prepared = pre; }
	bool getPrepared() { return prepared; }
private:
	/*���id
	*/
	string name;

	/*��ҵ�socket����
	*/
	uint16_t socketIndex;

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
	uint16_t roomIndex;

	/*�Ƿ�׼��
	*/
	bool prepared;
};






#endif // !__PLAYER__H__

