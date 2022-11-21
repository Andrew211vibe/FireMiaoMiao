#ifndef HERO_H
#define	HERO_H
#include <vector>
#include <string>

class MyCharacter
{
public:

	MyCharacter();
	MyCharacter(int hp, int mp, int idx, int atk, int def);
	~MyCharacter();

	void character_grahp_init();

	void character_grahp_draw(int x, int y, int w, int h);


	void show_player_HP();


	void show_player_MP();

	void set_player_xy(int x, int y);


	int get_player_x();


	int get_player_y();

	int get_player_source_idx();

	int get_player_HP();

	void set_player_HP(int hp);

	void reset_player_HP();

	int get_player_MP();

	void set_player_MP(int mp);

	void reset_player_MP();

	void player_gethurt(int hurt);

	int player_add_defend(int defend);

	int player_addEnergy(int energy);

	void sleep();


	//int get_player_coin();

	void player_coin_update(int coin);

	int get_player_atk();


	int get_player_def();

	void reset_player_def() { defend = 0; }

private:
	// 最大值
	const int iHp = 80;
	const int iMp = 3;
	const int iIdx = 0;
	// const int iAtk = 3;
	const int iDef = 0;

	int m_HP;
	int m_MP;
	int m_x = 0, m_y = 0;
	int m_graph_idx = 6;
	// std::string name;
	// int coin;
	// int attack;
	int defend;

};
#endif