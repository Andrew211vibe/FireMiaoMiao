#include "Card.h"
#include "random.h"


BaseCard::BaseCard(std::string name, int cost, int idx, type t)
{
	card_type = t;
	card_name = name;
	card_cost = cost;
	card_graph_idx = idx;
}

BaseCard::~BaseCard() {}

int BaseCard::get_card_type()
{
	return card_type;
}

int BaseCard::get_card_id()
{
	int size = cards.size();
	int i;
	for (i = 0; i < size; i++)
	{
		if ((*cards[i]).card_name == this->card_name)
		{
			return i;
		}
	}
	if (i == size)
	{
		return -1;
	}
	return 0;
}

int BaseCard::get_card_source_id()
{
	return this->card_graph_idx;
}

std::string BaseCard::get_card_name()
{
	return this->card_name;
}

void BaseCard::set_card_id(int id)
{
	this->card_id = id;
}


// ----------------------------------------BaseCard派生

AttackCard::AttackCard(int dam, std::string name, int cost, int idx, type t) : BaseCard(name, cost, idx, t)
{
	card_damage = dam;
}

void AttackCard::card_atk_func(BaseMonster& m)
{
	//check();
	m.set_getDamage(card_damage);
}


DefendCard::DefendCard(int def, std::string name, int cost, int idx, type t) : BaseCard(name, cost, idx, t)
{
	card_defend = def;
}

void DefendCard::card_def_func(MyCharacter& me)
{
	//check();
	me.player_add_defend(card_defend);
}


RestMPCard::RestMPCard(int re_mp, std::string name, int cost, int idx, type t) : BaseCard(name, cost, idx, t)
{
	card_restMP = re_mp;
}


SelfHurtCard::SelfHurtCard(int hurt, std::string name, int cost, int idx, type t) : BaseCard(name, cost, idx, t)
{
	card_hurt = hurt;
}

void DrawCard::card_draw_func()
{
	if (cards.size() == 0)
	{
		cards.swap(discards);
	}
	int val = random(cards.size());
	player_cards.push_back(cards[val]);
	cards.erase(cards.begin() + val);
}

void DiscCard::card_disc_func(int ch)
{
	/*如果手牌数量大于等于2，就弃牌，否则只消除手牌*/
	if (player_cards.size() >= 2)
	{
		int val = random(player_cards.size());
		while (val == ch)
		{
			val = random(player_cards.size());
		}

		set_card_xy(1300, 1300);
		discards.push_back(player_cards[val]);
		player_cards.erase(player_cards.begin() + val);
	}
}

// ---------------------------------------------------次派生

void AtkDefCard::card_atkdef_func(BaseMonster& m, MyCharacter& me)
{
	//check();
	card_atk_func(m);
	card_def_func(me);
}


void AtkDrawCard::card_atk_draw_func(BaseMonster& m)
{
	//check();
	card_atk_func(m);
	card_draw_func();
}


void DefDrawCard::card_def_draw_func(MyCharacter& me)
{
	//check();
	card_def_func(me);
	card_draw_func();
}


void AtkHurtCard::card_atk_hurt_func(MyCharacter& me, BaseMonster& m)
{
	//check();
	card_atk_func(m);
	card_selfhurt_func(me);
}


void DiscDefCard::card_disc_def_func(MyCharacter& m, int ch)
{
	//check();
	card_disc_func(ch);
	card_def_func(m);
}


void AOECard::diediedie()
{
	//check();
	for (auto iter = monster_lib.begin(); iter != monster_lib.end(); iter++)
	{
		(*iter)->set_getDamage(get_card_damage());
	}
}


void RestMPHurtCard::card_restMp_hurt_func(MyCharacter& me)
{
	card_restMp_func(me);
	card_selfhurt_func(me);
}


AttackCard card1(6, "攻击", 1, 0);
DefendCard card2(5, "防御", 1, 1);
AtkDrawCard card3(9, "喵喵拳", 1, 2);
AtkDefCard card4(5, 5, "后空翻", 1, 3);
DefDrawCard card5(8, "傲慢喵喵", 1, 4);
AtkHurtCard card6(2, 15, "御血术", 2, 5);
DiscDefCard card7(13, "有舍有得", 2, 6);
AOECard card8(8, "喵喵爪", 2, 7);
RestMPHurtCard card9(3, 2, "燃烧圣火", 0, 8);
DefendCard card10(30, "爷不想动", 3, 9);


void initialize_card()
{
	cards.push_back(&card1);
	cards.push_back(&card2);
	cards.push_back(&card3);
	cards.push_back(&card4);
	cards.push_back(&card5);
	cards.push_back(&card6);
	cards.push_back(&card7);
	cards.push_back(&card8);
	cards.push_back(&card9);
	cards.push_back(&card10);
}