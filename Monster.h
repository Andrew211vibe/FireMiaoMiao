#ifndef MONSTER_H
#define MONSTER_H
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>

class state
{
public:
	int getStrength()const { return strength; }
	int getWeekness()const { return weekness; }
	int getDelicate()const { return delicate; }
	int getShieldBroken()const { return shieldBroken; }
	void setStrength(int tmp) { strength = tmp; }
	void setWeekness(int tmp) { weekness = tmp; }
	void setDelicate(int tmp) { delicate = tmp; }
	void setShieldBroken(int tmp) { shieldBroken = tmp; }
	void stateTurn();
private:
	int strength = 0;
	int weekness = 0;
	int delicate = 0;
	int shieldBroken = 0;
};

class BaseMonster:public state
{
public:
	BaseMonster(int hp, int dam, int idx, std::string name) :m_HP(hp), monster_max_HP(hp), m_damage(dam), m_name(name), m_source_idx(idx)
	{
		m_source_idx = get_monster_id();
	}
	//BaseMonster() {}
	virtual ~BaseMonster() {}

	virtual int find_monster(std::string name);

	virtual int get_monster_id();

	virtual void set_monster_xy(int x, int y);

	virtual int get_monster_x();

	virtual int get_monster_y();

	//virtual void monster_graph_init();
	//virtual void monster_grahp_draw(int x, int y, int w, int h);

	int get_monster_damage();

	void set_monster_damage(int dm);

	void set_monster_id(int id);

	void set_getDamage(int dm);

	int get_monster_HP() { return m_HP; }

	int get_monster_max_HP() { return monster_max_HP; }

	void set_monster_max_HP(int h);

	virtual void s_turn() { return; };
	virtual void ct_turn() { return; };
	virtual void wm_turn() { return; };
	virtual void Bwm_turn() { return; };
	virtual void sK_turn() { return; };
	virtual void mxk_turn() { return; }

	virtual std::string get_name();
protected:
	int m_HP;
	int monster_max_HP;
	int m_damage;
	int m_source_idx;
	std::string m_name;
	int m_x, m_y;
};


class AtkDefmonster : public BaseMonster {
public:
	AtkDefmonster(int hp, int dam, int idx, std::string name);

	//void monster_atk_def_func();


	int get_monster_damage();


	int get_monster_defend();


	void set_def(int def);

	void s_turn() { return; };
	void ct_turn() { return; };
	void wm_turn() { return; };

private:
	int monster_def;
};

/*
class AtkRestHpMonster : public BaseMonster {
public:

	void monster_atk_restMP_func();

	int get_monster_damage();

	int get_monster_damage();

	void monster_HP_update();

private:
	int monster_restHp;
	AtkDefmonster::type monster_type = rest_hp;
};*/



class slimiao :public AtkDefmonster
{
public:
	slimiao(int hp = 20, int dam = 0, int idx = 0, std::string name = "slimiao") :AtkDefmonster(hp, dam, idx, name) {}
	void s_attack();
	void s_defend();
	void s_turn();
private:
	int a[2] = { 1,0 };
	int p = 1;
};


class cat_trader :public AtkDefmonster
{
public:
	cat_trader(int hp = 40, int dam = 13, int idx = 2, std::string name = "cat_trader") :AtkDefmonster(hp, dam, idx, name) {}
	void ct_attack();
	void ct_defend();
	void ct_turn();
private:
	int a[3] = { 1,2,0 };
	int p = 2;
};

class wormiao :public AtkDefmonster
{
public:
	wormiao(int hp = 15, int dam = 0, int idx = 3, std::string name = "mormiao") :AtkDefmonster(hp, dam, idx, name) {}
	void wm_attack();
	void wm_recover();
	void wm_turn();
private:
	int a[2] = { 1,0 };
	int p = 1;
};


class BIGwormiao :public AtkDefmonster
{
public:BIGwormiao(int hp = 80, int dam = 20, int idx = 4, std::string name = "BIGmormiao") :AtkDefmonster(hp, dam, idx, name) {}
	  void Bwm_attack();
	  void Bwm_defend();
	  void Bwm_turn();
private:
	int a[3] = { 1 , 2 , 0 };
	int p = 2;
	int t = 0;
};



class slimiaoKING :public AtkDefmonster
{
public:slimiaoKING(int hp = 130, int dam = 0, int idx = 4, std::string name = "slimiaoKING") :AtkDefmonster(hp, dam, idx, name) {}
	  void sK_turn();
private:
	int a[3] = { 1,2,0 };
	int p = 2;
};

class miaoxk :public AtkDefmonster
{
public:
	miaoxk(int hp = 25, int dam = 0, int idx = 4, std::string name = "miaoxk") :AtkDefmonster(hp, dam, idx, name) {}
	void mxk_turn();
private:
	int a[3] = { 1,2,0 };
	int p = 2;
};

extern std::vector<BaseMonster*> monster_lib;
extern std::vector<std::string> monster_name;

void initialize_monster(int floor,int num = 2);

#endif