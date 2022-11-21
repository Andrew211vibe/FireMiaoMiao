#include <fstream>
#include <time.h>
#include <sstream>
#include <iomanip>
#include "ScoreList.h"
using namespace std;

PlayerList::PlayerList()
{
	this->floorGrade = 0;
	this->startTime = " ";
}

PlayerList::PlayerList(int floorGrade, string name)
{
	this->name = name;
	this->floorGrade = floorGrade;
	split(getTime(), this->startTime, ' ');
}


void PlayerList::changeFloor(int floor)
{
	this->floorGrade = floor;
}

void PlayerList::split(string src, string &des, char mark)
{
	for (int i = 0; i < src.length(); i++)
	{
		if (src[i] != mark)
		{
			des += src[i];
		}
	}
}

string PlayerList::getTime()
{
	string t;
	time_t rawtime;
	struct tm* info;
	time(&rawtime);
	info = localtime(&rawtime);
	if (asctime(info) != 0)
	{
		t = asctime(info);
	}
	t.erase(t.end() - 1);
	return t;
}

bool PlayerList::listRank(PlayerList* src)
{
	int pGrade = this->floorGrade;
	//С��ԭ����С���˳�
	if (pGrade <= src[9].floorGrade)
	{
		return true;
	}
	else
	{
		int i = 8;
		while (i >= 0)
		{
			if (pGrade > src[i].floorGrade)
			{
				src[i + 1] = src[i];
				i--;
			}
			else
			{
				src[i + 1].name = this->name;
				src[i + 1].floorGrade = pGrade;
				src[i + 1].startTime = startTime;
				break;
			}
		}
		if (i <= 0)
		{
			src[0].floorGrade = pGrade;
			src[0].startTime = this->startTime;
		}
	}
	return false;
}

//��ȡ���а�
bool PlayerList::readList(string file,PlayerList* per)
{
	ifstream read(file);
	if (read.is_open())
	{
		string line;
		for (int i = 0; i < 10; i++)
		{
			getline(read, line);
			istringstream in(line);
			in >> per[i].name;
			//XXXXX
			in.seekg(19) >> per[i].startTime;

			in.seekg(40) >> per[i].floorGrade;
			in.clear();
		}
	}
	else
	{
		read.close();
		//��ʧ��
		return false;
	}
	//��ȡ���
	read.close();
	return true;
}
bool PlayerList::readList(string file,string& str)
{
	string line;
	ifstream read(file);
	if (read.is_open())
	{
		int i;
		for (i = 0; i < 10; i++)
		{
			getline(read, line);
			//istringstream in(line);
			str += line;
			str += '\n';
			settextstyle(25, 0, "����");
			outtextxy(370, 205 + i * 50, line.c_str());
		}
	}
	else
	{
		read.close();
		//��ʧ��
		return false;
	}
	//��ȡ���
	read.close();
	return true;
}

//�ı����а�
bool PlayerList::writeList(string file)
{
	//��ʼ��ʮ����
	PlayerList players[10];
	readList(file, players);
	//����
	if (listRank(players))
	{
		//û�ı�
		return false;
	}
	else
	{
		//�ı������а�����д��
		ofstream wList(file);
		for (int i = 0; i < 10; i++)
		{
			wList <<setw(20) << left << players[i].name << setw(40) << left << players[i].startTime << players[i].floorGrade << endl;
		}
		return true;
	}
}

string PlayerList::listStr(string file)
{
	string des;
	readList(file, des);
	return des;
}