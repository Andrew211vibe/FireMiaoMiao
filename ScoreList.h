#pragma once
#include <iostream>
#include <graphics.h>
#include <easyx.h>
using namespace std;
class PlayerList
{
public:
	PlayerList();
	//����¥����ǳ�
	PlayerList(int floorGrade, string name);
	//��д¥��
	void changeFloor(int floor);
	//��д���а�
	bool writeList(string file);
	//��ȡ���а��ǰ��
	string listStr(string file);
private:
	//����ǳ�
	string name;
	//��ȡʱ��
	string getTime();
	//��Ϸ��ʼʱ��
	string startTime{};
	//��Ϸ�÷֣�����)
	int floorGrade{};
	//��ȡ���а�
	bool readList(string file, PlayerList* per);
	bool readList(string filem, string& str);
	//����ʱ��
	void split(string src, string& des, char mark);
	//����(����)
	bool listRank(PlayerList* src);
};