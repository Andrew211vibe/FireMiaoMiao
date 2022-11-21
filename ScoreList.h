#pragma once
#include <iostream>
#include <graphics.h>
#include <easyx.h>
using namespace std;
class PlayerList
{
public:
	PlayerList();
	//输入楼层和昵称
	PlayerList(int floorGrade, string name);
	//改写楼层
	void changeFloor(int floor);
	//改写排行榜
	bool writeList(string file);
	//读取排行榜给前端
	string listStr(string file);
private:
	//玩家昵称
	string name;
	//获取时间
	string getTime();
	//游戏开始时间
	string startTime{};
	//游戏得分（层数)
	int floorGrade{};
	//读取排行榜
	bool readList(string file, PlayerList* per);
	bool readList(string filem, string& str);
	//处理时间
	void split(string src, string& des, char mark);
	//排序(插排)
	bool listRank(PlayerList* src);
};