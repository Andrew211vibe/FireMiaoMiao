#include"Monster.h"

void state::stateTurn()
{
	if (shieldBroken > 0)shieldBroken--;
	if (delicate > 0)delicate--;
	if (weekness > 0)weekness--;
}


void push_monster_lib(BaseMonster monster)
{
	monster_lib.push_back(&monster);
}


void clear_monster_lib()
{
	for (auto& c : monster_lib)
		delete c;
	monster_lib.clear();
	monster_name.clear();
}


int BaseMonster::find_monster(std::string name)
{
	int p = 0;
	for (auto& c : monster_lib) {
		if (name == c->m_name)
			return p;
		p++;
	}
	//m_source_idx = p;
	return -1;
}


int BaseMonster::get_monster_id()
{
	return m_source_idx;
}

void BaseMonster::set_monster_id(int id)
{
	this->m_source_idx = id;
}



void BaseMonster::set_monster_xy(int x, int y)
{
	m_x = x; m_y = y;
}


int BaseMonster::get_monster_x()
{
	return m_x;
}

int BaseMonster::get_monster_y()
{
	return m_y;
}


int BaseMonster::get_monster_damage()
{
	return m_damage;
}

void BaseMonster::set_monster_damage(int dm)
{
	m_damage = dm;
}
void BaseMonster::set_getDamage(int dm)
{
	m_HP -= dm;
}

std::string BaseMonster::get_name() {
	return m_name;
}

AtkDefmonster::AtkDefmonster(int hp, int dam, int idx, std::string name) :BaseMonster(hp, dam, idx, name), monster_def(0) {}

int AtkDefmonster::get_monster_damage() { return m_damage; }

int AtkDefmonster::get_monster_defend() { return monster_def; }

void AtkDefmonster::set_def(int def) { monster_def = def; }

void BaseMonster::set_monster_max_HP(int h) { monster_max_HP = h; }

void slimiao::s_attack()
{
	set_monster_damage(get_monster_damage());
}

void slimiao::s_defend()
{
	set_def(get_monster_damage());
}

void slimiao::s_turn()
{
	set_def(0);
	p = a[p];
	switch (p) {
	case 0:
	{
		s_attack();
		break;
	}
	case 1:
	{
		s_defend();
		break;
	}
	}
	set_monster_damage(get_monster_damage() + 3);
	stateTurn();
}

void cat_trader::ct_attack()
{
	set_monster_damage(get_monster_damage());
}

void cat_trader::ct_defend()
{
	set_def(5);
}

void cat_trader::ct_turn()
{
	set_def(0);
	p = a[p];
	switch (p) {
	case 0:
	{
		set_monster_damage(13);
		ct_attack();
		break;
	}
	case 1:
	{
		set_monster_damage(15);
		ct_defend();
		break;
	}
	case 2:
	{
		ct_defend();
		set_monster_damage(0);
		break;
	}
	}
	stateTurn();
}

void wormiao::wm_attack()
{
	set_monster_damage(get_monster_damage());
}

void wormiao::wm_recover()
{
	if (m_HP + 2 <= 15)
		m_HP += 2;
	else m_HP = 15;
}

void wormiao::wm_turn()
{
	set_def(0);
	p = a[p];
	switch (p) {
	case 0:
	{
		wm_attack();
		break;
	}
	case 1:
	{
		wm_recover();
		break;
	}
	}
	set_monster_damage(get_monster_damage() + 3);
	stateTurn();
}

void BIGwormiao::Bwm_attack()
{
	set_monster_damage(get_monster_damage());
}

void BIGwormiao::Bwm_defend()
{
	set_def(10);
	set_monster_damage(0);
}

void BIGwormiao::Bwm_turn()
{
	set_def(0);
	p = a[p];
	t++;
	if (t <= 3) {
		set_def(20);
		return;
	}
	switch (p)
	{
	case 0:
	{
		Bwm_attack();
		break;
	}
	case 1:
	{
		Bwm_attack();
		break;
	}
	case 2:
	{
		Bwm_defend();
		break;
	}
	}
	stateTurn();
}

void slimiaoKING::sK_turn()
{
	if (m_HP <= monster_max_HP / 2)
	{
		monster_lib.erase(monster_lib.begin() + find_monster(m_name));
		monster_name.erase(monster_name.begin() + find_monster(m_name));
		slimiao* a = new slimiao;
		a->set_monster_max_HP(m_HP);
		slimiao* b = new slimiao;
		b->set_monster_max_HP(m_HP);
		monster_lib.push_back(a);
		monster_name.push_back(a->get_name());
		monster_lib.push_back(b);
		monster_name.push_back(b->get_name());
		return;
	}
	set_def(0);
	p = a[p];
	switch (p)
	{
	case 0: {
		set_def(10);
		set_monster_damage(0);
		break;
	}
	case 1:
	{
		;
		break;
	}
	case 2:
	{
		set_monster_damage(35);
		break;
	}
	}
	stateTurn();
}

void initialize_monster(int floor,int num)
{
	clear_monster_lib();
	srand((unsigned)time(NULL));
	if(floor < 5)
		for (int i = 0; i < num; i++)
	{

		int n = rand() % 10 + 1;
		switch (n)
		{
		case 1:
		{
			if(floor > 3)
			{
				cat_trader* b = new cat_trader;
				b->set_monster_id(2);
				monster_name.push_back("cat_trader");
				monster_lib.push_back(b);
				break;
			}
		}
		case 2:
		case 3:
		case 4:
		{
			slimiao* a = new slimiao;
			a->set_monster_id(0);
			monster_name.push_back("slimiao");
			monster_lib.push_back(a);
			break;
		}
		case 5:
		case 6:
		{
			cat_trader* b = new cat_trader;
			b->set_monster_id(2);
			monster_name.push_back("cat_trader");
			monster_lib.push_back(b);
			break;
		}
		case 7:
		case 8:
		case 9:
		case 10:
		{
			wormiao* c = new wormiao;
			monster_name.push_back("wormiao");
			monster_lib.push_back(c);
			break;
		}
		}

		/*
		slimiaoKING* a = new slimiaoKING;
		//a->set_monster_id(0);
		monster_name.push_back("slimiaoKING");
		monster_lib.push_back(a);
		*/
	}
	else if(floor == 5)
	{
		BIGwormiao* b = new BIGwormiao;
		b->set_monster_id(2);
		monster_name.push_back("BIGwormiao");
		monster_lib.push_back(b);
		BIGwormiao* c = new BIGwormiao;
		c->set_monster_id(2);
		monster_name.push_back("BIGwormiao");
		monster_lib.push_back(c);
	}
}
