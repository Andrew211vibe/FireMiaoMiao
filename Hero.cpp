#include "Hero.h"

const int player_max_HP = 80;
const int player_max_MP = 8;

MyCharacter::MyCharacter(int hp, int mp, int idx, int atk, int def)
{

	m_HP = hp;

	m_MP = mp;

	m_graph_idx = idx;

	// this->attack = atk;

	defend = def;
}

MyCharacter::MyCharacter()
{
	m_HP = iHp;
	m_MP = iMp;
	defend = iDef;
	m_graph_idx = iIdx;
}

MyCharacter::~MyCharacter() {}


int MyCharacter::get_player_HP()
{
	return this->m_HP;
}

void MyCharacter::set_player_HP(int hp)
{
	this->m_HP = hp;
}


void MyCharacter::reset_player_HP()
{
	this->m_HP = iHp;
}

int MyCharacter::get_player_MP()
{
	return this->m_MP;
}
void MyCharacter::set_player_MP(int mp)
{
	this->m_MP = mp;
}


void MyCharacter::reset_player_MP()
{
	this->m_MP = iMp;
}

int MyCharacter::get_player_source_idx()
{
	return this->m_graph_idx;
}

// int MyCharacter::get_player_coin()
// {
// 	return this->coin;
// }

// void MyCharacter::player_coin_update(int coin)
// {
// 	this->coin = coin;
// }

// int MyCharacter::get_player_atk()
// {
// 	return this->attack;
// }

int MyCharacter::get_player_def()
{
	return defend;
}

void MyCharacter::set_player_xy(int x, int y)
{
	this->m_x = x;
	this->m_y = y;
}

int MyCharacter::get_player_x()
{
	return this->m_x;
}

int MyCharacter::get_player_y()
{
	return this->m_y;
}


void MyCharacter::player_gethurt(int hurt)
{
	if (get_player_def() - hurt >= 0)
	{
		this->defend -= hurt;
	}
	else
	{
		int hp = get_player_HP() + get_player_def() - hurt;
		this->defend = 0;
		if (hp < 0)
		{
			this->m_HP = 0;
		}
		else
		{
			this->m_HP = hp;
		}
	}
}

int MyCharacter::player_add_defend(int defend)
{
	int def = get_player_def() + defend;
	if (def >= 0)
	{
		this->defend = def;
	}
	return get_player_def();
}

int MyCharacter::player_addEnergy(int energy)
{
	int en = get_player_MP() + energy;
	if (en >= 0)
	{
		this->m_MP = en;
	}
	return get_player_MP();
}

void MyCharacter::sleep()
{
	int hp = get_player_HP() + 20;
	if (hp > iHp)
		m_HP = iHp;
	else
		m_HP = hp;
}