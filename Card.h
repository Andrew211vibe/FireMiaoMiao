#ifndef CARD_H
#define CARD_H

#include <vector>
#include <string>
#include <queue>

#include "Hero.h"
#include "Monster.h"

#define MAX_CARD_NUM 10//最大卡牌数

class MyCharacter;
class BaseMonster;


enum type {
	none, attack, defend, atk_def,
	atk_draw, def_draw, atk_hurt,
	disc_def, aoe, reMP_hurt, 
	reMP, SelfHurt, Draw, Disc
};

/*
卡牌的基类
属性：
	int 卡牌的耗蓝
	int 卡牌的坐标
	int 卡牌模型在素材库中对应的下标
*/
class BaseCard {
public:
	BaseCard(std::string name = "none", int cost = 1, int idx = 0, type t = none);
	/*
	设置卡牌坐标
	参数：
		int x坐标
		int y坐标
	*/
	virtual void set_card_xy(int x, int y) { card_x = x; card_y = y; }

	/*获取卡牌当前的X轴*/
	virtual int get_card_x() { return card_x; }

	/*获取卡牌当前的Y轴*/
	virtual int get_card_y() { return card_y; }

	/*获取卡牌消耗*/
	virtual int get_card_cost() { return card_cost; }

	/*获取卡牌在卡牌库中的下标*/
	virtual int get_card_id();

	/*获取卡牌类型*/
	int get_card_type();

	/*设置卡牌ID*/
	void set_card_id(int id);

	int get_card_source_id();
	
	/*获得卡牌名字*/
	std::string get_card_name();

	//void check() { printf("file=%s,func=%s,line=%d\n", __FILE__, __FUNCTION__, __LINE__); }

	virtual ~BaseCard();

	/*派生类虚方法：供基类指针使用*/
	virtual int get_card_damage() { return 0; }
	virtual void card_atk_func(BaseMonster& m) { return; }
	virtual int get_card_defend() { return 0; }
	virtual void card_def_func(MyCharacter& me) { return; }
	virtual int get_card_restMP() { return 0; }
	virtual void card_restmp_func(MyCharacter & me) { return; }
	virtual int get_card_hurt() { return 0; }
	virtual void card_selfhurt_func(MyCharacter & me) { return; }
	virtual void card_draw_func() { return; }
	virtual void card_disc_func() { return; }

	/*对敌人造成伤害给玩家加盾*/
	virtual void card_atkdef_func(BaseMonster& m, MyCharacter& me) { return; }

	/*对怪物造成伤害并抽一张牌*/
	virtual void card_atk_draw_func(BaseMonster& m) { return; }
	
	/*对玩家加盾并抽取一张卡*/
	virtual void card_def_draw_func(MyCharacter& me) { return; }

	/*对怪物造成伤害并玩家自己也受到伤害*/
	virtual void card_atk_hurt_func(MyCharacter& me, BaseMonster& m) { return; }

	/*先弃一张牌玩家再加盾*/
	virtual void card_disc_def_func(MyCharacter& m, int ch) { return; }

	/*对怪物造成伤害并玩家自己也受到伤害*/
	virtual void diediedie() { return; }

	/*玩家消耗生命值恢复体力*/
	virtual void card_restMp_hurt_func(MyCharacter& me) { return; }

protected:
	/*
	卡牌的类型：
		攻击，防御，攻击且防御，
		攻击且抽卡，防御且抽卡，攻击且自伤，
		弃牌且防御，全体攻击，回蓝且自伤
	*/
	type card_type;//卡牌的类型
	std::string card_name;//卡牌的名字
	int card_cost;//卡牌的耗蓝
	int card_x = 0, card_y = 0;//卡牌的坐标
	int card_id;
	int card_graph_idx;//卡牌模型在素材库中对应的下标
};


//------------------------------------------------中间派生类

/*攻击的类型的卡牌*/
class AttackCard : virtual public BaseCard {
public:
	AttackCard(int dam = 0, std::string name = "none", int cost = 1, int idx = 0, type t = attack);
	/*获取卡牌的伤害值*/
	int get_card_damage() { return card_damage; }
	/*对敌人造成伤害的函数*/
	void card_atk_func(BaseMonster& m);
	virtual ~AttackCard() {}
private:
	int card_damage; //卡牌的伤害
};


/*防御的类型卡牌*/
class DefendCard : virtual public BaseCard {
public:
	DefendCard(int def = 0, std::string name = "none", int cost = 1, int idx = 0, type t = defend);
	/*获取卡牌的盾值*/
	int get_card_defend() { return card_defend; }
	/*给玩家加盾的函数*/
	void card_def_func(MyCharacter& me);
	virtual ~DefendCard() {}
private:
	int card_defend;//卡牌的盾值
};


/*回蓝类型卡牌*/
class RestMPCard : virtual public BaseCard {
public:
	RestMPCard(int re_mp = 2, std::string name = "none", int cost = 0, int idx = 0, type t = reMP);
	/*玩家恢复体力*/
	void card_restMp_func(MyCharacter& me) { me.player_addEnergy(card_restMP); }
	/*获取卡牌恢复的蓝量*/
	int get_card_restMP() { return card_restMP; }
	virtual ~RestMPCard() {}
private:
	int card_restMP;//卡牌恢复的蓝量
};

/*自伤类型卡牌*/
class SelfHurtCard : virtual public BaseCard {
public:
	SelfHurtCard(int hurt = 1, std::string name = "none", int cost = 0, int idx = 0, type t = SelfHurt);
	/*获取卡牌的自伤值*/
	int get_card_hurt() { return card_hurt; }
	/*玩家自伤*/
	void card_selfhurt_func(MyCharacter & me) { me.player_gethurt(card_hurt); }
	virtual ~SelfHurtCard() {}
private:
	int card_hurt;//卡牌的自伤
};

/*抽卡类型卡牌*/
class DrawCard : virtual public BaseCard {
public:
	DrawCard(std::string name = "none", int cost = 0, int idx = 0, type t = Draw) : BaseCard(name, cost, idx, t) {}
	/*抽取一张卡牌*/
	void card_draw_func();
	virtual ~DrawCard() {}
};

/*弃牌类型卡牌*/
class DiscCard : virtual public BaseCard {
public:
	DiscCard(std::string name = "none", int cost = 0, int idx = 0, type t = Disc) : BaseCard(name, cost, idx, t) {}
	void card_disc_func(int ch);
	virtual ~DiscCard() {}
};


//------------------------------------------------------卡牌子类

/*先攻击后加盾类卡牌*/
class AtkDefCard : public AttackCard, public DefendCard {
public:
	AtkDefCard(int dam = 0, int def = 0, std::string name = "none", int cost = 1, int idx = 0, type t = atk_def) : BaseCard(name, cost, idx, t), AttackCard(dam, name, cost, idx, t), DefendCard(def, name, cost, idx, t) {}
	void card_atkdef_func(BaseMonster& m, MyCharacter& me);
};


/*先攻击再抽卡的类型*/
class AtkDrawCard : public AttackCard, public DrawCard {
public:
	AtkDrawCard(int dam = 0, std::string name = "none", int cost = 1, int idx = 0, type t = atk_draw) : BaseCard(name, cost, idx, t), AttackCard(dam, name, cost, idx, t), DrawCard(name, cost, idx, t) {}
	/*对怪物造成伤害并抽一张牌*/
	void card_atk_draw_func(BaseMonster& m);
};


/*先加盾再抽卡的类型*/
class DefDrawCard : public DefendCard, public DrawCard {
public:
	DefDrawCard(int def = 0, std::string name = "none", int cost = 1, int idx = 0, type t = def_draw) : BaseCard(name, cost, idx, t), DefendCard(def, name, cost, idx, t), DrawCard(name, cost, idx, t) {}
	/*对玩家加盾并抽取一张卡*/
	void card_def_draw_func(MyCharacter& me);
};


/*先攻击 玩家再受到反伤的类型*/
class AtkHurtCard : public AttackCard, public SelfHurtCard {
public:
	AtkHurtCard(int self = 0, int dam = 0, std::string name = "none", int cost = 1, int idx = 0, type t = atk_hurt) : BaseCard(name, cost, idx, t), AttackCard(dam, name, cost, idx, t), SelfHurtCard(self, name, cost, idx, t) {}
	/*对怪物造成伤害并玩家自己也受到伤害*/
	void card_atk_hurt_func(MyCharacter& me, BaseMonster& m);
};


/*先弃牌再受到加盾的类型*/
class DiscDefCard : public DefendCard, public DiscCard {
public:
	DiscDefCard(int def = 0, std::string name = "none", int cost = 1, int idx = 0, type t = disc_def) : BaseCard(name, cost, idx, t), DefendCard(def, name, cost, idx, t), DiscCard(name, cost, idx, t) {}
	/*先弃一张牌玩家再加盾*/
	void card_disc_def_func(MyCharacter& m, int ch);
};


/*对全体的怪物造成伤害*/
class AOECard : public AttackCard {
public:
	AOECard(int dam, std::string name, int cost, int idx = 0, type t = aoe) : BaseCard(name, cost, idx, t), AttackCard(dam, name, cost, idx, t) {}
	/*对怪物造成伤害并玩家自己也受到伤害*/
	void diediedie();
};

/*先回蓝再自伤的类型*/
class RestMPHurtCard : public RestMPCard, public SelfHurtCard {
public:
	RestMPHurtCard(int hur = 3, int re_mp = 2, std::string name = "none", int cost = 0, int idx = 0, type t = reMP_hurt) : BaseCard(name, cost, idx, t), RestMPCard(re_mp, name, cost, idx, t), SelfHurtCard(hur, name, cost, idx, t) {}
	/*消耗角色生命值获得体力值*/
	void card_restMp_hurt_func(MyCharacter& me);
};


/*卡牌库*/
extern std::vector<BaseCard*> cards;
/*手牌*/
extern std::vector<BaseCard*> player_cards;
/*弃牌堆*/
extern std::vector<BaseCard*> discards;

void initialize_card();
#endif
