#include<iostream>
#include<assert.h>
#include <conio.h>
#include "View.h"
#include "Card.h"
#include "ScoreList.h"
#include <random>
//#include "random.h"

#pragma comment( lib, "MSIMG32.LIB")

#define PI 3.14159265359


//-------------------------------------------------------global-------------------------------------------------------//
int floors = 1;//当前的层数
int cnt_floors = floors;//层数的计数
/*标志当前是否是玩家回合当为true时 是玩家回合 当为false时 为敌人回合*/
bool isPlayerTurn = true;
// 主角色
MyCharacter hero(80, 3, 7, 0, 0);
string player_name;
const int player_max_HP = 80;//玩家最大生命值
// 卡牌
/*卡牌库*/
std::vector<BaseCard*> cards;
/*手牌*/
std::vector<BaseCard*> player_cards;
/*弃牌堆*/
std::vector<BaseCard*> discards;
/*怪物堆*/
std::vector<BaseMonster*> monster_lib;
/*怪物名*/
std::vector<std::string> monster_name;
//音乐路径
vector<string>bkMusic(5);

extern int random(int max);
extern vector<IMAGE> bk_sources;
extern vector<IMAGE> card_sources;
extern vector<IMAGE> character_sources;
extern std::vector<IMAGE>button;//储存开始界面的五个按钮
extern std::vector<IMAGE>newButton;//鼠标悬停时的图片

bool is_player_died = false;
bool is_monster_all_died = false;

//---------------------------------------------------------dao---------------------------------------------------------//




//-------------------------------------------------------service-------------------------------------------------------//

void initMusic()
{
    int i = 0;
    bkMusic[i++] = ".\\sources\\bkStart.mp3";
    bkMusic[i++] = ".\\sources\\bkGame.mp3";
    bkMusic[i++] = ".\\sources\\bkRank.mp3";
    bkMusic[i++] = ".\\sources\\bkEncy.mp3";
    bkMusic[i++] = ".\\sources\\bkMem.mp3";
}

/**
 * 负责人：
 * 功能：初始化卡牌属性：10种卡牌
 * 参数：void
 * 返回值：void
*/
void init_cards()
{
    initialize_card();
}

/**
 * 负责人：
 * 功能：初始化怪物属性：血量、行为模式
 * 参数：void
 * 返回值：void
*/
void init_monster()
{
    is_monster_all_died = false;
    initialize_monster();
}

/**
 * 负责人：前端 技术官
 * 功能：初始化战斗界面
 * 参数：void
 * 返回值：void
*/
void init_battle()
{
    //// TODO界面生成:生成怪物角色对战页面
    BeginBatchDraw();
    char str[5];
    sprintf(str, "%d", floors);
    settextstyle(80, 0, "黑体");
    outtextxy(500, 100, "关卡");
    outtextxy(700, 100, str);

    /*绘制玩家的状态*/
    int player_Hp = hero.get_player_HP();
    int player_Mp = hero.get_player_MP();
    int player_Df = hero.get_player_def();
    static int player_Id = 6;
    if (player_Hp < 60 && player_Hp >= 30)
    {
        player_Id = 7;
    }
    else if (player_Hp > 0 && player_Hp < 30)
    {
        player_Id = 8;
    }
    else if (player_Hp > 60)
    {
        player_Id = 6;
    }
    if (player_Hp == 0)
    {
        is_player_died = true;
    }

    /*绘制玩家*/
    //putimage(hero.get_player_x(), hero.get_player_y(), &character_sources[hero.get_player_source_idx()]);
    drawAlpha(&character_sources[player_Id], hero.get_player_x(), hero.get_player_y());
    /*绘制玩家体力状态*/
    char s1[5], s2[5];
    sprintf(s1, "%d", player_Mp);
    sprintf(s2, "%d", player_Df);
    /*drawAlpha(&bk_sources[2], 150, 600);*/
    setfillcolor(RGB(85, 177, 85));
    solidcircle(100, 600, 50);
    settextstyle(50, 0, "黑体");
    outtextxy(90, 578, s1);

    settextstyle(25, 0, "黑体");
    transparentimage(NULL, 165, 425, &bk_sources[2]);
    outtextxy(175, 440, s2);

    /*血条*/
    int exist_hp = (player_Hp * 200 / player_max_HP);
    char health[5];
    sprintf(health, "%d", player_Hp);
    setfillcolor(RED);
    solidrectangle(hero.get_player_x(), hero.get_player_y() + 205, hero.get_player_x() + exist_hp, hero.get_player_y() + 205 + 15);
    outtextxy(hero.get_player_x() + 50, hero.get_player_y() + 205, health);
    outtextxy(hero.get_player_x() + 80, hero.get_player_y() + 205, "/ 80");

    /*绘制怪物队列*/
    for (int i = 0; i < monster_lib.size(); i++)
    {
        int monster_x = (monster_lib[i])->get_monster_x();
        int monster_y = (monster_lib[i])->get_monster_y();
        int monster_HP = (monster_lib[i])->get_monster_HP();
        int monster_atk = (monster_lib[i])->get_monster_damage();
        int monster_id = (monster_lib[i])->get_monster_id();
        int monster_mHp = (monster_lib[i])->get_monster_max_HP();
        char m_max_hp[4], m_hp[4], m_atk[4];
        sprintf(m_max_hp, "%d", monster_mHp);
        sprintf(m_hp, "%d", monster_HP);
        sprintf(m_atk, "%d", monster_atk);
        if ((monster_lib[i])->get_monster_HP() >= 0)
        {
            setfillcolor(RED);
            int monster_exist_Hp = (monster_lib[i])->get_monster_HP() * 200 / (monster_lib[i])->get_monster_max_HP();
            solidrectangle(monster_x, monster_y + 205, monster_x + monster_exist_Hp, monster_y + 205 + 15);
            outtextxy(monster_x + 50, monster_y + 205, m_hp);
            outtextxy(monster_x + 80, monster_y + 205, "/");
            outtextxy(monster_x + 90, monster_y + 205, m_max_hp);
            /*putimage(monster_x, monster_y, &character_sources[1]);*/
            //drawAlpha(&character_sources[monster_lib[i]->get_monster_id()], monster_x, monster_y);
            transparentimage(NULL, monster_x + 200, monster_y, &bk_sources[3]);
            transparentimage(NULL, monster_x, monster_y, &character_sources[monster_id]);
            outtextxy(monster_x + 215, monster_y + 10, m_atk);
        }
    }
    EndBatchDraw();
    int hp = hero.get_player_HP();
    int mp = hero.get_player_MP();
    if (hp == 0)
    {
        is_player_died = true;
    }
    //printf("player's hp = %d\n", hp);
    //printf("player's mp = %d\n", mp);

    //for (int i = 0; i < monster_lib.size(); i++)
    //{
    //    printf("monster %d 's hp = %d \n", i, monster_lib[i]->get_monster_HP());
    //}
}

/**
 * 负责人：
 * 功能：根据喵喵神选择来修改角色数值属性
 *      读取用户输入来选择喵喵神祝福调用对应方法
 *      选择后根据选择修改用户对应数值
 * 参数：int
 * 返回值：void
*/
//void god_bless_you(int bless) { return; }

/*展示玩家受到的伤害*/
void show_player_hurt(int hurt, int x, int y)
{
    char temp[5];
    sprintf(temp, "%d", hurt);
    settextcolor(RED);
    settextstyle(50, 0, "黑体");
    outtextxy(hero.get_player_x() + x, hero.get_player_y(), "-");
    outtextxy(hero.get_player_x() + y, hero.get_player_y(), temp);
}

/*展示玩家增加的盾值*/
void show_player_def(int def, int x, int y)
{
    char temp[5];
    sprintf(temp, "%d", def);
    settextcolor(GREEN);
    settextstyle(50, 0, "黑体");
    outtextxy(hero.get_player_x() + x, hero.get_player_y(), "+");
    outtextxy(hero.get_player_x() + y, hero.get_player_y(), temp);
}

/*展示玩家增加的血量*/
void show_player_addHp(int x, int y)
{
    settextcolor(GREEN);
    settextstyle(50, 0, "黑体");
    outtextxy(hero.get_player_x() + x, hero.get_player_y() + y, "+20");
}

/*展示怪物减少的血量*/
void show_monster_hurt(int x, int y, int hurt)
{
    char temp[5];
    sprintf(temp, "%d", hurt);
    settextcolor(RED);
    settextstyle(50, 0, "黑体");
    outtextxy(x + 180, y, "-");
    outtextxy(x + 200, y, temp);
}

/**
 * 功能：休息休息，顺便回个血
 *      调用回血方法power(int)
 * 参数：void
 * 返回值：void
*/
void v_me_50()
{
    hero.sleep();
    show_map_node();
    restHpAnimate(235, 200);
    show_player_addHp(180, 190);
    Sleep(400);
}

/**
 * 功能：怪物回合行为模式
 *      判断怪物行为后进行攻击
 * 参数：void
 * 返回值：void
*/
void monsterRound()
{

    for (auto& c : monster_lib)
    {
        if (c->get_name() == "slimiao")
        {
            c->s_turn();
        }
        else if (c->get_name() == "cat_trader")
        {
            c->ct_turn();
        }
        else
        {
            c->wm_turn();
        }
        hero.player_gethurt(c->get_monster_damage());

        /*怪物移动的动画*/
        for (int monster_x = c->get_monster_x(); monster_x >= hero.get_player_x(); monster_x--)
        {
            BeginBatchDraw();
            cleardevice();
            putimage(0, 0, &bk_sources[0]);
            settextcolor(BLACK);
            settextstyle(80, 0, "黑体");
            outtextxy(500, 100, "怪物回合");
            drawAlpha(&character_sources[9], hero.get_player_x(), hero.get_player_y());
            transparentimage(NULL, monster_x, 225, &character_sources[c->get_monster_id()]);
            if (monster_x - hero.get_player_x() <= 50)
            {
                IMAGE A;
                loadimage(&A, ".\\sources\\aaa.png", 200, 200);
                drawAlpha(&A, hero.get_player_x() + 100, hero.get_player_y() - 100);
                show_player_hurt(c->get_monster_damage(), 180, 190);
                Sleep(1);
            }
            EndBatchDraw();
        }
        IMAGE imshow;//需要显示的图片
        //0、创建图片向量
        vector<IMAGE> run;
        //1、图片顺序名称数组
        TCHAR imgname[20];
        //2、载入图片
        for (int i = 0; i < 5; i++)
        {
            _stprintf_s(imgname, _T("sources/test2/%d.png"), i);
            IMAGE im;
            loadimage(&im, imgname, 300, 300);
            run.push_back(im);
        }
        //3、输出图片
        int i = 0;
        BeginBatchDraw();
        while (i < run.size())
        {
            imshow = run[i];
            transparentimage(NULL, hero.get_player_x(), hero.get_player_y(), &imshow);
            FlushBatchDraw();
            i++;
            Sleep(100);
        }
        EndBatchDraw();
    }
}


/*
* 功能：抽出一张卡牌并调用卡牌方法
*		攻击怪
*		给自己加盾
* 参数：int
* 返回值：void
*/
void choose_card(int i)
{
    /*选择卡牌*/
    if (player_cards[i] && hero.get_player_MP() - player_cards[i]->get_card_cost() >= 0)
    {
        //说明可以使用这张卡牌
        hero.set_player_MP(hero.get_player_MP() - player_cards[i]->get_card_cost());

        /*调用卡牌的方法*/
        /*判断当前的卡牌是哪个类型的*/
        int card_t = player_cards[i]->get_card_type();
        //std::cout << id << std::endl;
        int j = 0;
        if (monster_lib[j]->get_monster_HP() <= 0)
        {
            if (monster_lib[1]->get_monster_HP() > 0)
            {
                j = 1;
            }
            else
            {
                return;
            }
        }
        switch (card_t)
        {
        case 1:
            cleardevice();
            show_map_node();
            Atkanimate(monster_lib[j]->get_monster_x(), monster_lib[j]->get_monster_y());
            show_monster_hurt(monster_lib[j]->get_monster_x(), monster_lib[j]->get_monster_y(), player_cards[i]->get_card_damage());
            Sleep(400);
            player_cards[i]->card_atk_func(*monster_lib[j]);
            break;
        case 2:
            cleardevice();
            show_map_node();
            defAnimate(180, 255);
            show_player_def(player_cards[i]->get_card_defend(), 180, 200);
            Sleep(400);
            player_cards[i]->card_def_func(hero); break;
        case 3:
            cleardevice();
            show_map_node();
            Atkanimate(monster_lib[j]->get_monster_x(), monster_lib[j]->get_monster_y());
            show_monster_hurt(monster_lib[j]->get_monster_x(), monster_lib[j]->get_monster_y(), player_cards[i]->get_card_damage());
            Sleep(400);
            cleardevice();
            show_map_node();
            defAnimate(180, 255);
            show_player_def(player_cards[i]->get_card_defend(), 180, 200);
            Sleep(400);
            player_cards[i]->card_atkdef_func(*monster_lib[j], hero); break;
        case 4:
            cleardevice();
            show_map_node();
            Atkanimate(monster_lib[j]->get_monster_x(), monster_lib[j]->get_monster_y());
            show_monster_hurt(monster_lib[j]->get_monster_x(), monster_lib[j]->get_monster_y(), player_cards[i]->get_card_damage());
            Sleep(400);
            player_cards[i]->card_atk_draw_func(*monster_lib[j]); break;
        case 5:
            cleardevice();
            show_map_node();
            defAnimate(180, 255);
            show_player_def(player_cards[i]->get_card_defend(), 180, 200);
            Sleep(400);
            player_cards[i]->card_def_draw_func(hero); break;
        case 6:
            cleardevice();
            show_map_node();
            Atkanimate(monster_lib[j]->get_monster_x(), monster_lib[j]->get_monster_y());
            show_monster_hurt(monster_lib[j]->get_monster_x(), monster_lib[j]->get_monster_y(), player_cards[i]->get_card_damage());
            Sleep(400);
            cleardevice();
            show_map_node();
            getHurtAnimate(160, 80);
            show_player_hurt(player_cards[i]->get_card_hurt(), 180, 190);
            Sleep(400);
            player_cards[i]->card_atk_hurt_func(hero, *monster_lib[j]); break;
        case 7:
            cleardevice();
            show_map_node();
            defAnimate(180, 255);
            show_player_def(player_cards[i]->get_card_defend(), 180, 200);
            Sleep(400);
            player_cards[i]->card_disc_def_func(hero, i); break;
        case 8:
            cleardevice();
            show_map_node();
            AOEanimate(280, 280, "test1");
            show_monster_hurt(monster_lib[j]->get_monster_x(), monster_lib[j]->get_monster_y(), player_cards[i]->get_card_damage());
            Sleep(400);
            player_cards[i]->diediedie(); break;
        case 9:
            cleardevice();
            show_map_node();
            Atkanimate(monster_lib[j]->get_monster_x(), monster_lib[j]->get_monster_y());
            show_monster_hurt(monster_lib[j]->get_monster_x(), monster_lib[j]->get_monster_y(), player_cards[i]->get_card_damage());
            Sleep(400);
            cleardevice();
            show_map_node();
            getHurtAnimate(160, 80);
            show_player_hurt(player_cards[i]->get_card_hurt(), 180, 190);
            Sleep(400);
            player_cards[i]->card_restMp_hurt_func(hero); break;
        default:
            break;
        }

        /*将用过的手牌放入弃牌堆中*/
        for (int z = 0; z < player_cards.size(); z++)
        {
            // 删除对应卡牌（说的就是你有舍有得）
            if (player_cards[z]->get_card_type() == card_t)
            {
                player_cards[z]->set_card_xy(1300, 1300);
                discards.push_back(player_cards[z]);
                player_cards.erase(player_cards.begin() + z);
                break;
            }
        }

        //判断怪是否死亡
        for (int y = 0; y < monster_lib.size(); y++)
        {
            if (monster_lib[y]->get_monster_HP() <= 0)
            {
                is_monster_all_died = true;
                // 如果怪死亡就删除
                monster_lib.erase(monster_lib.begin() + y);
                y--;
            }
            else
                is_monster_all_died = false;
        }

        // 判断角色是否死亡
        if (hero.get_player_HP() <= 0)
            is_player_died = true;
    }
}

void showHomePage();

/**
 * 功能：玩家回合进行卡牌选择攻击
 * 参数：ExMessage &
 * 返回值：void
*/
void playerRound()
{
    hero.reset_player_MP();
    show_map_node();
    //v_me_50();
    /*随机抽取手牌*/
    std::cout << "\n楼层数: " << floors << std::endl;
    /*抽牌堆中没牌了 从弃牌堆中洗入*/
    if (cards.size() <= 3)
    {
        for (int i = 0; i < discards.size(); i++)
        {
            cards.push_back(discards[i]);
        }
        discards.clear();
    }
    /*表示抽牌堆的牌还没抽空
    从抽牌堆中抽牌*/
    std::cout << "从抽卡堆中抽牌\n";
    if (player_cards.size() == 0 && cards.size() > 3)
    {
        for (int j = 0; j < 3 && cards.size() != 0; j++)
        {
            /*从第一中类型到第九类型中抽牌*/
            int rand_card_id = random(cards.size());
            /*Sleep(100);*/
            assert(rand_card_id < 10);
            player_cards.push_back(cards[rand_card_id]);
            player_cards[j]->set_card_id(player_cards[j]->get_card_id());
            cards.erase(cards.begin() + rand_card_id);
            /*ids[j] = rand_card_id;*/
        }
    }
    //std::cout << "玩家手牌数: " << player_cards.size() << std::endl;
    //for (int i = 0; i < player_cards.size(); i++)
    //{
    //    if (player_cards[i])
    //    {
    //        cout << "抽到：" << player_cards[i]->get_card_name() << "消耗：" << player_cards[i]->get_card_cost() << endl;
    //    }
    //}
    IMAGE cs;
    loadimage(&cs, ".\\sources\\card.png", 100, 167);
    while (isPlayerTurn)
    {
        BeginBatchDraw();
        putimage(0, 0, &bk_sources[0]);
        settextcolor(BLACK);
        setfillcolor(GREEN);
        create_botton("结束回合", 1100, 500, 125, 50);
        outtextxy(50, 525, "玩家体力值");
        solidcircle(100, 600, 50);

        /*绘制卡牌*/
        outtextxy(1000, 700, "抽牌堆剩余");
        outtextxy(0, 700, "弃牌堆剩余");
        for (int j = 0; j < cards.size(); j++)
        {
            cards[j]->set_card_xy(1100 + (j * 15), 570);
            transparentimage(NULL, cards[j]->get_card_x(), cards[j]->get_card_y(), &cs);
        }
        int a[3] = { 0 }, b[3] = { 0 };
        if (player_cards.size() == 0 || hero.get_player_MP() == 0)
        {
            isPlayerTurn = false;
            break;
        }
        for (int i = 0; i < player_cards.size(); i++)
        {
            player_cards[i]->set_card_xy(350 + (i * 220), 475);
            /*putimage(player_cards[i]->get_card_x(), player_cards[i]->get_card_y(), &card_sources[player_cards[i]->get_card_source_id()]);*/
            transparentimage(NULL, player_cards[i]->get_card_x(), player_cards[i]->get_card_y(), &card_sources[player_cards[i]->get_card_source_id()]);
            a[i] = player_cards[i]->get_card_x();
            b[i] = player_cards[i]->get_card_y();

        }
        if (!discards.empty())
        {
            for (int j = 0; j < discards.size(); j++)
            {
                discards[j]->set_card_xy(150 + (j * 15), 570);
                transparentimage(NULL, discards[j]->get_card_x(), discards[j]->get_card_y(), &card_sources[discards[j]->get_card_source_id() + 10]);
            }
        }
        ExMessage msg;
        if (peekmessage(&msg, EM_MOUSE))
        {
            if (monster_lib.size() == 0 || is_monster_all_died || player_cards.size() == 0 || hero.get_player_MP() == 0)
            {
                isPlayerTurn = false;
                break;
            }
            switch (msg.message)
            {
            case WM_LBUTTONDOWN:
                if (msg.x >= 1100 && msg.x <= 1100 + 125 && msg.y >= 500 && msg.y <= 500 + 50)
                {
                    /*玩家按下“回合结束”*/
                    //printf("按键按下\n");
                    isPlayerTurn = false;
                    break;
                }
                if (a[0] && b[0])
                {
                    if (msg.x >= a[0] && msg.x <= a[0] + 187 && msg.y >= b[0] && msg.y <= b[0] + 262)
                    {
                        choose_card(0);
                        break;
                    }
                }
                if (a[1] && b[1])
                {
                    if (msg.x >= a[1] && msg.x <= a[1] + 187 && msg.y >= b[1] && msg.y <= b[1] + 262)
                    {
                        choose_card(1);
                        break;
                    }
                }
                if (a[2] && b[2])
                {
                    if (msg.x >= a[2] && msg.x <= a[2] + 187 && msg.y >= b[2] && msg.y <= b[2] + 262)
                    {
                        choose_card(2);
                        break;
                    }
                }
            default:
                break;
            }
        }
        init_battle();
    }
    EndBatchDraw();

    /*回合结束全部手牌弃掉*/
    if (player_cards.size() > 0)
    {
        for (int i = 0; i < player_cards.size(); i++)
        {
            discards.push_back(player_cards[i]);
        }
        player_cards.clear();
    }
}



//-------------------------------------------------------view-------------------------------------------------------//

/**
 * 负责人：
 * 功能：生成塔底界面
 *      打印喵喵神的祝福
 *      读取用户选择
 *      调用god_bless_you()传入用户选择
 * 参数：void
 * 返回值：void
*/
void floor_zero()
{
    return;
}

void win();

/**
 * 负责人：
 * 功能：初始化怪物参数 init_monster();
 *      打印战斗界面(调用对应生成方法)
 *          打印框架->打印卡牌->打印角色和怪
 *      循环检查怪物状态：死亡/活着
 *          死亡->清除怪物
 *          怪物数量清零->跳转奖励结算界面
 *          活着->继续
 *      循环检查角色状态：死亡/活着
 *          死亡->跳转死亡结算界面
 *          活着->继续
 *      每回合开始重置护盾0，重置体力值满：
 *          有体力：
 *              可以出牌
 *                  出牌后根据卡牌调用函数修改对象数值
 *          可查看地图（拓展）
 *          可查看设置
 *          可查看弃牌堆、抽牌堆
 *      回合结束
 *          丢弃所有手牌
 *      抽牌堆为空，弃牌堆洗入抽牌堆
 *      层数结束后返回1下一层为怪，返回2下一层为篝火
 * 参数：void
 * 返回值：int
*/
int Battle_floor()
{
    // 计算战斗层数
    static int floor_count = 1;
    // 计算回合数
    static int rounds = 0;
    // 初始化怪物
    init_monster();

    /*初始化素材库*/
    bk_sources_init();
    card_sources_init();
    character_sources_init();

    //初始化玩家
    hero.set_player_xy(225, 225);

    // 初始化怪物
    init_monster();
    monster_lib[0]->set_monster_xy(625, 225);
    monster_lib[1]->set_monster_xy(925, 225);

    while (!is_player_died && !is_monster_all_died)
    {
        init_battle();
        if (isPlayerTurn == true)
        {
            // TODO玩家回合
            playerRound();
            if (hero.get_player_HP() <= 0)
                is_player_died = true;
        }
        else
        {
            // 怪物回合
            monsterRound();
            isPlayerTurn = true;
            // 重置护盾
            if (hero.get_player_def() > 0)
                hero.reset_player_def();
            rounds++;
            std::cout << "Round: " << rounds << std::endl;
            // 检查玩家状态
            if (hero.get_player_HP() <= 0)
                is_player_died = true;
        }
    }


    // 战斗层结束后（跳转地图界面）返回下一层关卡
    if (is_player_died)
    {
        std::cout << "无了" << std::endl;
        return -1;
    }
    else if (floors == 9)
    {
        std::cout << "牛的嘛" << std::endl;
        return -2;
    }
    else
    {
        std::cout << "乱杀" << std::endl;
        hero.reset_player_def();
        cnt_floors = floors;
        win();
    }


    int next = 1;
    /* pl.changeFloor(9);*/
    switch (floor_count)
    {
    case 1:
    case 2:
        floor_count++; break;
    case 3:
        floor_count = 1; next = 2; break;
    default:
        break;
    }
    return next;
}

/*过关界面*/
void win()
{
    isPlayerTurn = true;
    floors++;

    //	initgraph(640, 480, SHOWCONSOLE);    // 创建绘图窗口，大小为 640x480 像素//
    setbkcolor(WHITE);
    cleardevice();
    //输出图片
    IMAGE img;
    //加载图片
    loadimage(&img, ".\\sources\\1.jpg");
    transparentimage(NULL, 500, 200, &img);
    char s0[50] = "挑战下一关";
    setfillcolor(RGB(204, 189, 255));//设置填充颜色
    button_create(600, 500, 170, 50, s0);
    setbkmode(TRANSPARENT);
    ExMessage msg;
    while (true) {
        if (peekmessage(&msg, EM_MOUSE)) {

            switch (msg.message)
            {
            case WM_LBUTTONDOWN:
                if (msg.x >= 600 && msg.x <= 600 + 170 && msg.y >= 500 && msg.y <= 500 + 50)
                {
                    cout << "0" << endl;
                    return;
                    //写了一个展示文字的效果，相当于是测试,实际使用时可以删除
                //在此处写下按钮点击时要执行的函数，实现相应的功能
                }
            default:
                break;
            }
        }

    }
}


/**
 * 功能：1. 角色回复血量 2. 升级卡牌（拓展）
 *      初始化篝火界面
 *      睡觉->修改角色血量
 *      跳转地图界面选择节点（拓展）
 *      跳转下一层
 *      1. 角色回复血量
 *          调用sleep()
 *      2. 升级卡牌（拓展）
 * 参数：void
 * 返回值：void
*/
int Bonfire_floor()
{
    v_me_50();
    return 1;
}

void showGamePage();

void player_reset()
{
    floors = 1;
    hero.reset_player_def();
    hero.reset_player_HP();
    hero.reset_player_MP();
    isPlayerTurn = true;
    is_player_died = false;

    is_monster_all_died = false;

    cards.clear();
    player_cards.clear();
    discards.clear();
}


/**
* 失败界面
* 功能：失败后跳转，选择重开或者回到菜单
* 返回值：int
* 参数: void
*/
int defeated()
{
    /*    initgraph(640, 480, SHOWCONSOLE);  */  // 创建绘图窗口，大小为 640x480 像素
    setbkcolor(WHITE);
    cleardevice();
    //输出图片
    IMAGE img;
    //加载图片
    loadimage(&img, ".\\sources\\shibai(1).jpg");
    transparentimage(NULL, 484, 30, &img);
    setfillcolor(RGB(192, 192, 192));//设置填充颜色
    char s0[50] = "返回首页";
    char s1[50] = "再次挑战";
    char s2[50] = "本次挑战失败";
    char s3[50] = "";
    button_create(1030, 390, 170, 50, s0);
    button_create(80, 390, 170, 50, s1);
    button_create(550, 320, 190, 50, s2);
    setbkmode(TRANSPARENT);
    player_reset();
    ExMessage msg;
    while (true) {
        if (peekmessage(&msg, EM_MOUSE)) {

            switch (msg.message)
            {
            case WM_LBUTTONDOWN:
                if (msg.x >= 1030 && msg.x <= 1030 + 170 && msg.y >= 390 && msg.y <= 390 + 50)
                {
                    cout << "0" << endl;
                    floors = 1;
                    closeMusic(bkMusic[1]);
                    showHomePage();
                    break;
                    //写了一个展示文字的效果，相当于是测试,实际使用时可以删除
                //在此处写下按钮点击时要执行的函数，实现相应的功能
                }
                if (msg.x >= 80 && msg.x <= 80 + 170 && msg.y >= 390 && msg.y <= 390 + 50)
                {
                    cout << "1" << endl;
                    floors = 1;
                    return 1;

                    //在此处写下按钮点击时要执行的函数，实现相应的功能  
                }
                if (msg.x >= 200 && msg.x <= 200 + 170 && msg.y >= 320 && msg.y <= 320 + 50)
                {
                    cout << "2" << endl;

                    //在此处写下按钮点击时要执行的函数，实现相应的功能
                }
                if (msg.x >= 300 && msg.x <= 300 + 170 && msg.y >= 320 && msg.y <= 320 + 50)
                {
                    cout << "3" << endl;

                    //在此处写下按钮点击时要执行的函数，实现相应的功能
                }
                break;
            default:
                break;
            }
        }
    }
}


int final_win()
{
    //	initgraph(640, 480, SHOWCONSOLE);    // 创建绘图窗口，大小为 640x480 像素//
    setbkcolor(WHITE);
    cleardevice();
    //输出图片
    IMAGE img;
    //加载图片
    loadimage(&img, ".\\sources\\1.jpg");
    transparentimage(NULL, 100, 0, &img);
    char s0[50] = "返回首页";
    char s1[50] = "再次挑战";
    char s2[50] = "本次得分";
    char s3[50] = "";
    setfillcolor(RGB(204, 189, 255));//设置填充颜色
    button_create(1030, 390, 170, 50, s0);
    button_create(80, 390, 170, 50, s1);
    button_create(120, 320, 170, 50, s2);
    button_create(300, 320, 170, 50, s3);
    setbkmode(TRANSPARENT);
    player_reset();
    ExMessage msg;
    while (true) {
        if (peekmessage(&msg, EM_MOUSE)) {

            switch (msg.message)
            {
            case WM_LBUTTONDOWN:
                if (msg.x >= 1030 && msg.x <= 1030 + 170 && msg.y >= 390 && msg.y <= 390 + 50)
                {
                    cout << "0" << endl;
                    floors = 1;
                    closeMusic(bkMusic[1]);
                    showHomePage();
                    break;
                    //写了一个展示文字的效果，相当于是测试,实际使用时可以删除
                //在此处写下按钮点击时要执行的函数，实现相应的功能
                }
                if (msg.x >= 80 && msg.x <= 80 + 170 && msg.y >= 390 && msg.y <= 390 + 50)
                {
                    cout << "1" << endl;
                    floors = 1;
                    return 1;

                    //在此处写下按钮点击时要执行的函数，实现相应的功能  
                }
                if (msg.x >= 120 && msg.x <= 120 + 170 && msg.y >= 320 && msg.y <= 320 + 50)
                {
                    cout << "2" << endl;
                    break;

                    //在此处写下按钮点击时要执行的函数，实现相应的功能
                }
                if (msg.x >= 300 && msg.x <= 300 + 170 && msg.y >= 320 && msg.y <= 320 + 50)
                {
                    cout << "3" << endl;
                    break;

                    //在此处写下按钮点击时要执行的函数，实现相应的功能
                }
                break;
            default:
                break;
            }
        }

    }
}


/**
 * 负责人：
 * 功能：根据参数判断生成对应游戏界面以及初始化，每过一层层数+1
 *      0：塔底->跳转塔底页面 showBottom() （拓展1）
 *      1：战斗->跳转战斗界面 showBattle() （核心）
 *      2：篝火->跳转篝火界面 showBonfire() (核心)
 *      3：宝箱
 *      4：随机事件
 *      5：商店
 *      -1: 死亡界面 失败
 *      -2: 成功界面 卡酷一
 * 参数：void
 * 返回值：void
*/
void showGamePage()
{
    // 选择界面
    /*initgraph(1280, 720, EW_SHOWCONSOLE);*/

    /*记录排行榜*/
    PlayerList pl(0, player_name);

    playMusic(bkMusic[1]);

    static int res = floors;

    if (floors == 1)
        init_cards();
    while (res)
    {
        switch (res)
        {
        case 0:
            floor_zero();
            break;
        case 1:
            res = Battle_floor();
            break;
        case 2:
            res = Bonfire_floor();
            break;
        case -1:
            // 屎掉力
            res = defeated();
            if (res == 1)
            {
                // 如果重开则初始化卡牌
                init_cards();
            }
            break;
        case -2:
            res = final_win();
            if (res == 1)
            {
                // 如果重开则初始化卡牌
                init_cards();
            }
            break;
        default:
            break;
        }
    }

    //if (floors <= 9)
    //    showGamePage();
}

void show_ency()
{
    playMusic(bkMusic[3]);
    //背景图片的加载与输出
    IMAGE bkImg;
    loadimage(&bkImg, ".\\sources\\bk2.png", 1280, 720);
    putimage(0, 0, &bkImg);

    //卡牌图鉴、怪物图鉴、背景故事的按钮
    vector<IMAGE>kind(3);
    int i = 0;
    loadimage(&kind[i++], ".\\sources\\bkInformation.png", 320, 478);
    loadimage(&kind[i++], ".\\sources\\card.png", 320, 478);
    loadimage(&kind[i++], ".\\sources\\monster.png", 320, 478);

    //输出三个按钮
    int width = 100 + 30, height = 149;
    for (i = 0; i < 3; i++)
    {

        drawAlpha(&kind[i], width, height);
        width += 350;
    }

    //返回按钮
    IMAGE back;
    loadimage(&back, ".\\sources\\return.png", 90, 40);
    drawAlpha(&back, 0, 20);

    MOUSEMSG mouse;
    while (true)
    {
        mouse = GetMouseMsg();
        if (mouse.uMsg == WM_LBUTTONUP)
        {
            if (mouse.x >= 0 && mouse.x <= 90 && mouse.y >= 20 && mouse.y <= 60)
            {
                //左键弹起，返回主界面
                closeMusic(bkMusic[3]);
                showHomePage();
            }
            else if (mouse.x >= 130 && mouse.x <= 450 && mouse.y >= 149 && mouse.y <= 627)
            {
                //左键弹起，进入背景故事界面
                show_ency_bkStory();

            }
            else if (mouse.x >= 480 && mouse.x <= 800 && mouse.y >= 149 && mouse.y <= 627)
            {
                //左键弹起，进入卡牌图鉴
                show_ency_card1();
            }
            else if (mouse.x >= 830 && mouse.x <= 1150 && mouse.y >= 149 && mouse.y <= 627)
            {
                //左键弹起，进入怪物图鉴
                show_ency_monster1();
            }
        }

    }
}

void show_credits()
{
    playMusic(bkMusic[4]);
    /*initgraph(1280, 720);*/
    setbkcolor(BLACK);
    cleardevice();
    settextstyle(25, 0, "宋体");
    settextcolor(WHITE);
    int x, y;
    int flag = 0;
    x = 570; y = 800;
    while (1)
    {
        outtextxy(x, y, " 制作人名单");
        outtextxy(x, y + 30, "组长： 文泰龙");
        outtextxy(x, y + 60, "副组长： 刘锦斌");
        outtextxy(x, y + 90, "副组长： 李皓晨");
        outtextxy(x, y + 120, "产品经理： 乐林风");
        outtextxy(x, y + 150, "产品经理： 蔡乾枫");
        outtextxy(x, y + 180, "信息官： 杨一凡");
        outtextxy(x, y + 210, "监督官： 高阳");
        outtextxy(x, y + 240, "记录官： 木辛");
        outtextxy(x, y + 270, "技术官： 王佳吉");
        outtextxy(x, y + 300, "鸣谢： 01星球学长学姐");
        outtextxy(x, y + 360, "感谢游玩!");
        y -= 3;
        Sleep(40);
        cleardevice();
        flag++;
        if (flag == 410)
        {
            outtextxy(600, 500, "按任意键继续。");
            _getch();
            closeMusic(bkMusic[4]);
            showHomePage();
            return;
        }
    }
}
void show_rank()
{
    PlayerList pl(0, player_name);
    playMusic(bkMusic[2]);
    //initgraph(1280, 720, SHOWCONSOLE);
    setbkcolor(WHITE);
    cleardevice();
    //输出图片
    IMAGE img;
    //加载图片
    loadimage(&img, ".\\sources\\1.jpg");
    transparentimage(NULL, 600, 680, &img);

    //标题
    settextstyle(50, 25, "黑体");//设置字体高度，宽度，字型
    setbkmode(TRANSPARENT);//设置字体背景透明，默认不透明
    settextcolor(RGB(227, 114, 0));
    outtextxy(480, 50, "圣火永不灭，喵喵永流传");

    //排行榜
    settextstyle(30, 15, "黑体");//设置字体高度，宽度，字型
    setbkmode(TRANSPARENT);//设置字体背景透明，默认不透明
    settextcolor(RGB(227, 114, 0));
    outtextxy(280, 200, "第一名");
    outtextxy(280, 250, "第二名");
    outtextxy(280, 300, "第三名");
    outtextxy(280, 350, "第四名");
    outtextxy(280, 400, "第五名");
    outtextxy(280, 450, "第六名");
    outtextxy(280, 500, "第七名");
    outtextxy(280, 550, "第八名");
    outtextxy(280, 600, "第九名");
    outtextxy(280, 650, "第十名");

    ////排行榜名字

    // 
    // settextstyle(30, 15, "黑体");//设置字体高度，宽度，字型
    // setbkmode(TRANSPARENT);//设置字体背景透明，默认不透明
    // settextcolor(RGB(227, 114, 0));
    // outtextxy(280, 200, );
    // outtextxy(280, 250, );
    // outtextxy(280, 300, "第三名");
    // outtextxy(280, 350, "第四名");
    // outtextxy(280, 400, "第五名");
    // outtextxy(280, 400, "第六名");
    // outtextxy(280, 400, "第七名");
    // outtextxy(280, 400, "第八名");
    // outtextxy(280, 400, "第九名");
    // outtextxy(280, 400, "第十名");
    pl.changeFloor(cnt_floors);
    pl.writeList(".\\score.txt");
    pl.listStr(".\\score.txt");

    //按钮
    settextcolor(WHITE);
    char s0[50] = "返回首页";
    setfillcolor(RGB(227, 114, 0));//设置填充颜色
    button_create(0, 0, 170, 50, s0);
    setbkmode(TRANSPARENT);
    ExMessage msg;
    while (true) {
        if (peekmessage(&msg, EM_MOUSE)) {

            switch (msg.message)
            {
            case WM_LBUTTONDOWN:
                if (msg.x >= 0 && msg.x <= 0 + 170 && msg.y >= 0 && msg.y <= 0 + 50)
                {
                    cout << "0" << endl;
                    closeMusic(bkMusic[2]);
                    showHomePage();
                    //写了一个展示文字的效果，相当于是测试,实际使用时可以删除
                //在此处写下按钮点击时要执行的函数，实现相应的功能
                }
                break;
            default:
                break;
            }
        }

    }

}

/**
 * 负责人：
 * 功能：展示菜单页功能，根据用户选择切换页面，用户可以用鼠标选择（或者w/s, 或者上下方向键）
 *      开始游戏->跳转游戏界面 showGamePage() （核心）
 *      退出游戏->退出程序
 *      排行榜->进入排行榜界面
 *      百科全书->进入百科全书界面
 *      制作人员->进入制作人员界面
 * 参数：void
 * 返回值：void
*/
void showHomePage()
{
    /*initgraph(1280, 720, SHOWCONSOLE);*/
    HWND hnd = GetHWnd();
    char _str[] = "圣火喵喵勇闯喵喵塔";
    SetWindowText(hnd, _str);

    playMusic(bkMusic[0]);

    IMAGE Img;
    loadimage(&Img, ".\\sources\\bk.png", 1280, 720);//加载开始界面的背景图片
    putimage(0, 0, &Img);//输出背景

    int i = 0;
    loadimage(&button[i++], ".\\sources\\rank.png", 187, 262);
    loadimage(&button[i++], ".\\sources\\kaishi.png", 187, 262);
    loadimage(&button[i++], ".\\sources\\book.png", 187, 262);
    loadimage(&button[i++], ".\\sources\\tuichu.png", 187, 262);
    loadimage(&button[i++], ".\\sources\\producer.png", 187, 262);

    i = 0;
    loadimage(&newButton[i++], ".\\sources\\newrank.png", 187, 262);
    loadimage(&newButton[i++], ".\\sources\\newkaishi.png", 187, 262);
    loadimage(&newButton[i++], ".\\sources\\newbook.png", 187, 262);
    loadimage(&newButton[i++], ".\\sources\\newtuichu.png", 187, 262);
    loadimage(&newButton[i++], ".\\sources\\newproducer.png", 187, 262);

    int width = 57, height = 448;
    for (i = 0; i < 5; i++)//间隔输出五个按钮图片
    {
        if (i % 2 == 1)
        {
            height = 338;//向上错开位置输出图片
        }
        drawAlpha(&button[i], width, height);//半透明贴图，输出按钮图片
        width += 244;
        height = 448;
    }

    IMAGE title;
    loadimage(&title, ".\\sources\\title.jpg", 908, 162);//加载标题图片
    drawAlpha(&title, 186, 100);//半透明贴图，输出标题

    width = 57; height = 448;
    MOUSEMSG mouse;
    while (true)//鼠标事件，在不同区域按下左键弹起后，跳转到相应界面
    {
        mouse = GetMouseMsg();

        if (mouse.x >= 57 && mouse.x <= 244 && mouse.y >= 448 && mouse.y <= 710)
        {
            drawAlpha(&newButton[0], 57, 448);
            if (mouse.uMsg == WM_LBUTTONUP)//左键弹起，进入排行榜界面
            {
                closeMusic(bkMusic[0]);
                show_rank();
                break;
            }
        }
        else if (mouse.x >= 301 && mouse.x <= 488 && mouse.y >= 338 && mouse.y <= 600)
        {
            drawAlpha(&newButton[1], 301, 338);
            //左键弹起，进入开始游戏界面
            if (mouse.uMsg == WM_LBUTTONUP)
            {
                closeMusic(bkMusic[0]);
                showGamePage();
                break;
            }
        }
        else if (mouse.x >= 545 && mouse.x <= 732 && mouse.y >= 448 && mouse.y <= 710)
        {
            //左键弹起，进入百科全书界面
            drawAlpha(&newButton[2], 545, 448);
            if (mouse.uMsg == WM_LBUTTONUP)
            {
                closeMusic(bkMusic[0]);
                show_ency();
                break;
            }
        }
        else if (mouse.x >= 789 && mouse.x <= 976 && mouse.y >= 338 && mouse.y <= 600)
        {
            drawAlpha(&newButton[3], 789, 338);
            //左键弹起，退出游戏
            if (mouse.uMsg == WM_LBUTTONUP)
            {
                closeMusic(bkMusic[0]);
                exit(0);
                break;
            }

        }
        else if (mouse.x >= 1033 && mouse.x <= 1220 && mouse.y >= 448 && mouse.y <= 710)
        {
            drawAlpha(&newButton[4], 1033, 448);
            //左键弹起，进入制作人员界面
            if (mouse.uMsg == WM_LBUTTONUP)
            {
                closeMusic(bkMusic[0]);
                show_credits();
                break;
            }
        }
        else
        {
            width = 57, height = 448;
            for (int i = 0; i < 5; i++)//间隔输出五个按钮图片
            {
                if (i % 2 == 1)
                {
                    height = 338;//向上错开位置输出图片
                }
                drawAlpha(&button[i], width, height);//半透明贴图，输出按钮图片
                width += 244;
                height = 448;
            }
        }
    }
    return;
}

int main()
{
    //initgraph(1280, 720, SHOWCONSOLE);
    initgraph(1280, 720);
    initMusic();
    char str[20];
    InputBox(str, 20, "那么，勇者大人的名字是？");
    player_name = str;
    showHomePage();
    _getch();
    closegraph();
    return 0;
}