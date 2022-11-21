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
int floors = 1;//��ǰ�Ĳ���
int cnt_floors = floors;//�����ļ���
/*��־��ǰ�Ƿ�����һغϵ�Ϊtrueʱ ����һغ� ��Ϊfalseʱ Ϊ���˻غ�*/
bool isPlayerTurn = true;
// ����ɫ
MyCharacter hero(80, 3, 7, 0, 0);
string player_name;
const int player_max_HP = 80;//����������ֵ
// ����
/*���ƿ�*/
std::vector<BaseCard*> cards;
/*����*/
std::vector<BaseCard*> player_cards;
/*���ƶ�*/
std::vector<BaseCard*> discards;
/*�����*/
std::vector<BaseMonster*> monster_lib;
/*������*/
std::vector<std::string> monster_name;
//����·��
vector<string>bkMusic(5);

extern int random(int max);
extern vector<IMAGE> bk_sources;
extern vector<IMAGE> card_sources;
extern vector<IMAGE> character_sources;
extern std::vector<IMAGE>button;//���濪ʼ����������ť
extern std::vector<IMAGE>newButton;//�����ͣʱ��ͼƬ

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
 * �����ˣ�
 * ���ܣ���ʼ���������ԣ�10�ֿ���
 * ������void
 * ����ֵ��void
*/
void init_cards()
{
    initialize_card();
}

/**
 * �����ˣ�
 * ���ܣ���ʼ���������ԣ�Ѫ������Ϊģʽ
 * ������void
 * ����ֵ��void
*/
void init_monster()
{
    is_monster_all_died = false;
    initialize_monster();
}

/**
 * �����ˣ�ǰ�� ������
 * ���ܣ���ʼ��ս������
 * ������void
 * ����ֵ��void
*/
void init_battle()
{
    //// TODO��������:���ɹ����ɫ��սҳ��
    BeginBatchDraw();
    char str[5];
    sprintf(str, "%d", floors);
    settextstyle(80, 0, "����");
    outtextxy(500, 100, "�ؿ�");
    outtextxy(700, 100, str);

    /*������ҵ�״̬*/
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

    /*�������*/
    //putimage(hero.get_player_x(), hero.get_player_y(), &character_sources[hero.get_player_source_idx()]);
    drawAlpha(&character_sources[player_Id], hero.get_player_x(), hero.get_player_y());
    /*�����������״̬*/
    char s1[5], s2[5];
    sprintf(s1, "%d", player_Mp);
    sprintf(s2, "%d", player_Df);
    /*drawAlpha(&bk_sources[2], 150, 600);*/
    setfillcolor(RGB(85, 177, 85));
    solidcircle(100, 600, 50);
    settextstyle(50, 0, "����");
    outtextxy(90, 578, s1);

    settextstyle(25, 0, "����");
    transparentimage(NULL, 165, 425, &bk_sources[2]);
    outtextxy(175, 440, s2);

    /*Ѫ��*/
    int exist_hp = (player_Hp * 200 / player_max_HP);
    char health[5];
    sprintf(health, "%d", player_Hp);
    setfillcolor(RED);
    solidrectangle(hero.get_player_x(), hero.get_player_y() + 205, hero.get_player_x() + exist_hp, hero.get_player_y() + 205 + 15);
    outtextxy(hero.get_player_x() + 50, hero.get_player_y() + 205, health);
    outtextxy(hero.get_player_x() + 80, hero.get_player_y() + 205, "/ 80");

    /*���ƹ������*/
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
 * �����ˣ�
 * ���ܣ�����������ѡ�����޸Ľ�ɫ��ֵ����
 *      ��ȡ�û�������ѡ��������ף�����ö�Ӧ����
 *      ѡ������ѡ���޸��û���Ӧ��ֵ
 * ������int
 * ����ֵ��void
*/
//void god_bless_you(int bless) { return; }

/*չʾ����ܵ����˺�*/
void show_player_hurt(int hurt, int x, int y)
{
    char temp[5];
    sprintf(temp, "%d", hurt);
    settextcolor(RED);
    settextstyle(50, 0, "����");
    outtextxy(hero.get_player_x() + x, hero.get_player_y(), "-");
    outtextxy(hero.get_player_x() + y, hero.get_player_y(), temp);
}

/*չʾ������ӵĶ�ֵ*/
void show_player_def(int def, int x, int y)
{
    char temp[5];
    sprintf(temp, "%d", def);
    settextcolor(GREEN);
    settextstyle(50, 0, "����");
    outtextxy(hero.get_player_x() + x, hero.get_player_y(), "+");
    outtextxy(hero.get_player_x() + y, hero.get_player_y(), temp);
}

/*չʾ������ӵ�Ѫ��*/
void show_player_addHp(int x, int y)
{
    settextcolor(GREEN);
    settextstyle(50, 0, "����");
    outtextxy(hero.get_player_x() + x, hero.get_player_y() + y, "+20");
}

/*չʾ������ٵ�Ѫ��*/
void show_monster_hurt(int x, int y, int hurt)
{
    char temp[5];
    sprintf(temp, "%d", hurt);
    settextcolor(RED);
    settextstyle(50, 0, "����");
    outtextxy(x + 180, y, "-");
    outtextxy(x + 200, y, temp);
}

/**
 * ���ܣ���Ϣ��Ϣ��˳��ظ�Ѫ
 *      ���û�Ѫ����power(int)
 * ������void
 * ����ֵ��void
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
 * ���ܣ�����غ���Ϊģʽ
 *      �жϹ�����Ϊ����й���
 * ������void
 * ����ֵ��void
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

        /*�����ƶ��Ķ���*/
        for (int monster_x = c->get_monster_x(); monster_x >= hero.get_player_x(); monster_x--)
        {
            BeginBatchDraw();
            cleardevice();
            putimage(0, 0, &bk_sources[0]);
            settextcolor(BLACK);
            settextstyle(80, 0, "����");
            outtextxy(500, 100, "����غ�");
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
        IMAGE imshow;//��Ҫ��ʾ��ͼƬ
        //0������ͼƬ����
        vector<IMAGE> run;
        //1��ͼƬ˳����������
        TCHAR imgname[20];
        //2������ͼƬ
        for (int i = 0; i < 5; i++)
        {
            _stprintf_s(imgname, _T("sources/test2/%d.png"), i);
            IMAGE im;
            loadimage(&im, imgname, 300, 300);
            run.push_back(im);
        }
        //3�����ͼƬ
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
* ���ܣ����һ�ſ��Ʋ����ÿ��Ʒ���
*		������
*		���Լ��Ӷ�
* ������int
* ����ֵ��void
*/
void choose_card(int i)
{
    /*ѡ����*/
    if (player_cards[i] && hero.get_player_MP() - player_cards[i]->get_card_cost() >= 0)
    {
        //˵������ʹ�����ſ���
        hero.set_player_MP(hero.get_player_MP() - player_cards[i]->get_card_cost());

        /*���ÿ��Ƶķ���*/
        /*�жϵ�ǰ�Ŀ������ĸ����͵�*/
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

        /*���ù������Ʒ������ƶ���*/
        for (int z = 0; z < player_cards.size(); z++)
        {
            // ɾ����Ӧ���ƣ�˵�ľ����������еã�
            if (player_cards[z]->get_card_type() == card_t)
            {
                player_cards[z]->set_card_xy(1300, 1300);
                discards.push_back(player_cards[z]);
                player_cards.erase(player_cards.begin() + z);
                break;
            }
        }

        //�жϹ��Ƿ�����
        for (int y = 0; y < monster_lib.size(); y++)
        {
            if (monster_lib[y]->get_monster_HP() <= 0)
            {
                is_monster_all_died = true;
                // �����������ɾ��
                monster_lib.erase(monster_lib.begin() + y);
                y--;
            }
            else
                is_monster_all_died = false;
        }

        // �жϽ�ɫ�Ƿ�����
        if (hero.get_player_HP() <= 0)
            is_player_died = true;
    }
}

void showHomePage();

/**
 * ���ܣ���һغϽ��п���ѡ�񹥻�
 * ������ExMessage &
 * ����ֵ��void
*/
void playerRound()
{
    hero.reset_player_MP();
    show_map_node();
    //v_me_50();
    /*�����ȡ����*/
    std::cout << "\n¥����: " << floors << std::endl;
    /*���ƶ���û���� �����ƶ���ϴ��*/
    if (cards.size() <= 3)
    {
        for (int i = 0; i < discards.size(); i++)
        {
            cards.push_back(discards[i]);
        }
        discards.clear();
    }
    /*��ʾ���ƶѵ��ƻ�û���
    �ӳ��ƶ��г���*/
    std::cout << "�ӳ鿨���г���\n";
    if (player_cards.size() == 0 && cards.size() > 3)
    {
        for (int j = 0; j < 3 && cards.size() != 0; j++)
        {
            /*�ӵ�һ�����͵��ھ������г���*/
            int rand_card_id = random(cards.size());
            /*Sleep(100);*/
            assert(rand_card_id < 10);
            player_cards.push_back(cards[rand_card_id]);
            player_cards[j]->set_card_id(player_cards[j]->get_card_id());
            cards.erase(cards.begin() + rand_card_id);
            /*ids[j] = rand_card_id;*/
        }
    }
    //std::cout << "���������: " << player_cards.size() << std::endl;
    //for (int i = 0; i < player_cards.size(); i++)
    //{
    //    if (player_cards[i])
    //    {
    //        cout << "�鵽��" << player_cards[i]->get_card_name() << "���ģ�" << player_cards[i]->get_card_cost() << endl;
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
        create_botton("�����غ�", 1100, 500, 125, 50);
        outtextxy(50, 525, "�������ֵ");
        solidcircle(100, 600, 50);

        /*���ƿ���*/
        outtextxy(1000, 700, "���ƶ�ʣ��");
        outtextxy(0, 700, "���ƶ�ʣ��");
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
                    /*��Ұ��¡��غϽ�����*/
                    //printf("��������\n");
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

    /*�غϽ���ȫ����������*/
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
 * �����ˣ�
 * ���ܣ��������׽���
 *      ��ӡ�������ף��
 *      ��ȡ�û�ѡ��
 *      ����god_bless_you()�����û�ѡ��
 * ������void
 * ����ֵ��void
*/
void floor_zero()
{
    return;
}

void win();

/**
 * �����ˣ�
 * ���ܣ���ʼ��������� init_monster();
 *      ��ӡս������(���ö�Ӧ���ɷ���)
 *          ��ӡ���->��ӡ����->��ӡ��ɫ�͹�
 *      ѭ��������״̬������/����
 *          ����->�������
 *          ������������->��ת�����������
 *          ����->����
 *      ѭ������ɫ״̬������/����
 *          ����->��ת�����������
 *          ����->����
 *      ÿ�غϿ�ʼ���û���0����������ֵ����
 *          ��������
 *              ���Գ���
 *                  ���ƺ���ݿ��Ƶ��ú����޸Ķ�����ֵ
 *          �ɲ鿴��ͼ����չ��
 *          �ɲ鿴����
 *          �ɲ鿴���ƶѡ����ƶ�
 *      �غϽ���
 *          ������������
 *      ���ƶ�Ϊ�գ����ƶ�ϴ����ƶ�
 *      ���������󷵻�1��һ��Ϊ�֣�����2��һ��Ϊ����
 * ������void
 * ����ֵ��int
*/
int Battle_floor()
{
    // ����ս������
    static int floor_count = 1;
    // ����غ���
    static int rounds = 0;
    // ��ʼ������
    init_monster();

    /*��ʼ���زĿ�*/
    bk_sources_init();
    card_sources_init();
    character_sources_init();

    //��ʼ�����
    hero.set_player_xy(225, 225);

    // ��ʼ������
    init_monster();
    monster_lib[0]->set_monster_xy(625, 225);
    monster_lib[1]->set_monster_xy(925, 225);

    while (!is_player_died && !is_monster_all_died)
    {
        init_battle();
        if (isPlayerTurn == true)
        {
            // TODO��һغ�
            playerRound();
            if (hero.get_player_HP() <= 0)
                is_player_died = true;
        }
        else
        {
            // ����غ�
            monsterRound();
            isPlayerTurn = true;
            // ���û���
            if (hero.get_player_def() > 0)
                hero.reset_player_def();
            rounds++;
            std::cout << "Round: " << rounds << std::endl;
            // ������״̬
            if (hero.get_player_HP() <= 0)
                is_player_died = true;
        }
    }


    // ս�����������ת��ͼ���棩������һ��ؿ�
    if (is_player_died)
    {
        std::cout << "����" << std::endl;
        return -1;
    }
    else if (floors == 9)
    {
        std::cout << "ţ����" << std::endl;
        return -2;
    }
    else
    {
        std::cout << "��ɱ" << std::endl;
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

/*���ؽ���*/
void win()
{
    isPlayerTurn = true;
    floors++;

    //	initgraph(640, 480, SHOWCONSOLE);    // ������ͼ���ڣ���СΪ 640x480 ����//
    setbkcolor(WHITE);
    cleardevice();
    //���ͼƬ
    IMAGE img;
    //����ͼƬ
    loadimage(&img, ".\\sources\\1.jpg");
    transparentimage(NULL, 500, 200, &img);
    char s0[50] = "��ս��һ��";
    setfillcolor(RGB(204, 189, 255));//���������ɫ
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
                    //д��һ��չʾ���ֵ�Ч�����൱���ǲ���,ʵ��ʹ��ʱ����ɾ��
                //�ڴ˴�д�°�ť���ʱҪִ�еĺ�����ʵ����Ӧ�Ĺ���
                }
            default:
                break;
            }
        }

    }
}


/**
 * ���ܣ�1. ��ɫ�ظ�Ѫ�� 2. �������ƣ���չ��
 *      ��ʼ���������
 *      ˯��->�޸Ľ�ɫѪ��
 *      ��ת��ͼ����ѡ��ڵ㣨��չ��
 *      ��ת��һ��
 *      1. ��ɫ�ظ�Ѫ��
 *          ����sleep()
 *      2. �������ƣ���չ��
 * ������void
 * ����ֵ��void
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
* ʧ�ܽ���
* ���ܣ�ʧ�ܺ���ת��ѡ���ؿ����߻ص��˵�
* ����ֵ��int
* ����: void
*/
int defeated()
{
    /*    initgraph(640, 480, SHOWCONSOLE);  */  // ������ͼ���ڣ���СΪ 640x480 ����
    setbkcolor(WHITE);
    cleardevice();
    //���ͼƬ
    IMAGE img;
    //����ͼƬ
    loadimage(&img, ".\\sources\\shibai(1).jpg");
    transparentimage(NULL, 484, 30, &img);
    setfillcolor(RGB(192, 192, 192));//���������ɫ
    char s0[50] = "������ҳ";
    char s1[50] = "�ٴ���ս";
    char s2[50] = "������սʧ��";
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
                    //д��һ��չʾ���ֵ�Ч�����൱���ǲ���,ʵ��ʹ��ʱ����ɾ��
                //�ڴ˴�д�°�ť���ʱҪִ�еĺ�����ʵ����Ӧ�Ĺ���
                }
                if (msg.x >= 80 && msg.x <= 80 + 170 && msg.y >= 390 && msg.y <= 390 + 50)
                {
                    cout << "1" << endl;
                    floors = 1;
                    return 1;

                    //�ڴ˴�д�°�ť���ʱҪִ�еĺ�����ʵ����Ӧ�Ĺ���  
                }
                if (msg.x >= 200 && msg.x <= 200 + 170 && msg.y >= 320 && msg.y <= 320 + 50)
                {
                    cout << "2" << endl;

                    //�ڴ˴�д�°�ť���ʱҪִ�еĺ�����ʵ����Ӧ�Ĺ���
                }
                if (msg.x >= 300 && msg.x <= 300 + 170 && msg.y >= 320 && msg.y <= 320 + 50)
                {
                    cout << "3" << endl;

                    //�ڴ˴�д�°�ť���ʱҪִ�еĺ�����ʵ����Ӧ�Ĺ���
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
    //	initgraph(640, 480, SHOWCONSOLE);    // ������ͼ���ڣ���СΪ 640x480 ����//
    setbkcolor(WHITE);
    cleardevice();
    //���ͼƬ
    IMAGE img;
    //����ͼƬ
    loadimage(&img, ".\\sources\\1.jpg");
    transparentimage(NULL, 100, 0, &img);
    char s0[50] = "������ҳ";
    char s1[50] = "�ٴ���ս";
    char s2[50] = "���ε÷�";
    char s3[50] = "";
    setfillcolor(RGB(204, 189, 255));//���������ɫ
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
                    //д��һ��չʾ���ֵ�Ч�����൱���ǲ���,ʵ��ʹ��ʱ����ɾ��
                //�ڴ˴�д�°�ť���ʱҪִ�еĺ�����ʵ����Ӧ�Ĺ���
                }
                if (msg.x >= 80 && msg.x <= 80 + 170 && msg.y >= 390 && msg.y <= 390 + 50)
                {
                    cout << "1" << endl;
                    floors = 1;
                    return 1;

                    //�ڴ˴�д�°�ť���ʱҪִ�еĺ�����ʵ����Ӧ�Ĺ���  
                }
                if (msg.x >= 120 && msg.x <= 120 + 170 && msg.y >= 320 && msg.y <= 320 + 50)
                {
                    cout << "2" << endl;
                    break;

                    //�ڴ˴�д�°�ť���ʱҪִ�еĺ�����ʵ����Ӧ�Ĺ���
                }
                if (msg.x >= 300 && msg.x <= 300 + 170 && msg.y >= 320 && msg.y <= 320 + 50)
                {
                    cout << "3" << endl;
                    break;

                    //�ڴ˴�д�°�ť���ʱҪִ�еĺ�����ʵ����Ӧ�Ĺ���
                }
                break;
            default:
                break;
            }
        }

    }
}


/**
 * �����ˣ�
 * ���ܣ����ݲ����ж����ɶ�Ӧ��Ϸ�����Լ���ʼ����ÿ��һ�����+1
 *      0������->��ת����ҳ�� showBottom() ����չ1��
 *      1��ս��->��תս������ showBattle() �����ģ�
 *      2������->��ת������� showBonfire() (����)
 *      3������
 *      4������¼�
 *      5���̵�
 *      -1: �������� ʧ��
 *      -2: �ɹ����� ����һ
 * ������void
 * ����ֵ��void
*/
void showGamePage()
{
    // ѡ�����
    /*initgraph(1280, 720, EW_SHOWCONSOLE);*/

    /*��¼���а�*/
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
            // ʺ����
            res = defeated();
            if (res == 1)
            {
                // ����ؿ����ʼ������
                init_cards();
            }
            break;
        case -2:
            res = final_win();
            if (res == 1)
            {
                // ����ؿ����ʼ������
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
    //����ͼƬ�ļ��������
    IMAGE bkImg;
    loadimage(&bkImg, ".\\sources\\bk2.png", 1280, 720);
    putimage(0, 0, &bkImg);

    //����ͼ��������ͼ�����������µİ�ť
    vector<IMAGE>kind(3);
    int i = 0;
    loadimage(&kind[i++], ".\\sources\\bkInformation.png", 320, 478);
    loadimage(&kind[i++], ".\\sources\\card.png", 320, 478);
    loadimage(&kind[i++], ".\\sources\\monster.png", 320, 478);

    //���������ť
    int width = 100 + 30, height = 149;
    for (i = 0; i < 3; i++)
    {

        drawAlpha(&kind[i], width, height);
        width += 350;
    }

    //���ذ�ť
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
                //������𣬷���������
                closeMusic(bkMusic[3]);
                showHomePage();
            }
            else if (mouse.x >= 130 && mouse.x <= 450 && mouse.y >= 149 && mouse.y <= 627)
            {
                //������𣬽��뱳�����½���
                show_ency_bkStory();

            }
            else if (mouse.x >= 480 && mouse.x <= 800 && mouse.y >= 149 && mouse.y <= 627)
            {
                //������𣬽��뿨��ͼ��
                show_ency_card1();
            }
            else if (mouse.x >= 830 && mouse.x <= 1150 && mouse.y >= 149 && mouse.y <= 627)
            {
                //������𣬽������ͼ��
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
    settextstyle(25, 0, "����");
    settextcolor(WHITE);
    int x, y;
    int flag = 0;
    x = 570; y = 800;
    while (1)
    {
        outtextxy(x, y, " ����������");
        outtextxy(x, y + 30, "�鳤�� ��̩��");
        outtextxy(x, y + 60, "���鳤�� ������");
        outtextxy(x, y + 90, "���鳤�� ��𩳿");
        outtextxy(x, y + 120, "��Ʒ���� ���ַ�");
        outtextxy(x, y + 150, "��Ʒ���� ��Ǭ��");
        outtextxy(x, y + 180, "��Ϣ�٣� ��һ��");
        outtextxy(x, y + 210, "�ල�٣� ����");
        outtextxy(x, y + 240, "��¼�٣� ľ��");
        outtextxy(x, y + 270, "�����٣� ���Ѽ�");
        outtextxy(x, y + 300, "��л�� 01����ѧ��ѧ��");
        outtextxy(x, y + 360, "��л����!");
        y -= 3;
        Sleep(40);
        cleardevice();
        flag++;
        if (flag == 410)
        {
            outtextxy(600, 500, "�������������");
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
    //���ͼƬ
    IMAGE img;
    //����ͼƬ
    loadimage(&img, ".\\sources\\1.jpg");
    transparentimage(NULL, 600, 680, &img);

    //����
    settextstyle(50, 25, "����");//��������߶ȣ���ȣ�����
    setbkmode(TRANSPARENT);//�������屳��͸����Ĭ�ϲ�͸��
    settextcolor(RGB(227, 114, 0));
    outtextxy(480, 50, "ʥ������������������");

    //���а�
    settextstyle(30, 15, "����");//��������߶ȣ���ȣ�����
    setbkmode(TRANSPARENT);//�������屳��͸����Ĭ�ϲ�͸��
    settextcolor(RGB(227, 114, 0));
    outtextxy(280, 200, "��һ��");
    outtextxy(280, 250, "�ڶ���");
    outtextxy(280, 300, "������");
    outtextxy(280, 350, "������");
    outtextxy(280, 400, "������");
    outtextxy(280, 450, "������");
    outtextxy(280, 500, "������");
    outtextxy(280, 550, "�ڰ���");
    outtextxy(280, 600, "�ھ���");
    outtextxy(280, 650, "��ʮ��");

    ////���а�����

    // 
    // settextstyle(30, 15, "����");//��������߶ȣ���ȣ�����
    // setbkmode(TRANSPARENT);//�������屳��͸����Ĭ�ϲ�͸��
    // settextcolor(RGB(227, 114, 0));
    // outtextxy(280, 200, );
    // outtextxy(280, 250, );
    // outtextxy(280, 300, "������");
    // outtextxy(280, 350, "������");
    // outtextxy(280, 400, "������");
    // outtextxy(280, 400, "������");
    // outtextxy(280, 400, "������");
    // outtextxy(280, 400, "�ڰ���");
    // outtextxy(280, 400, "�ھ���");
    // outtextxy(280, 400, "��ʮ��");
    pl.changeFloor(cnt_floors);
    pl.writeList(".\\score.txt");
    pl.listStr(".\\score.txt");

    //��ť
    settextcolor(WHITE);
    char s0[50] = "������ҳ";
    setfillcolor(RGB(227, 114, 0));//���������ɫ
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
                    //д��һ��չʾ���ֵ�Ч�����൱���ǲ���,ʵ��ʹ��ʱ����ɾ��
                //�ڴ˴�д�°�ť���ʱҪִ�еĺ�����ʵ����Ӧ�Ĺ���
                }
                break;
            default:
                break;
            }
        }

    }

}

/**
 * �����ˣ�
 * ���ܣ�չʾ�˵�ҳ���ܣ������û�ѡ���л�ҳ�棬�û����������ѡ�񣨻���w/s, �������·������
 *      ��ʼ��Ϸ->��ת��Ϸ���� showGamePage() �����ģ�
 *      �˳���Ϸ->�˳�����
 *      ���а�->�������а����
 *      �ٿ�ȫ��->����ٿ�ȫ�����
 *      ������Ա->����������Ա����
 * ������void
 * ����ֵ��void
*/
void showHomePage()
{
    /*initgraph(1280, 720, SHOWCONSOLE);*/
    HWND hnd = GetHWnd();
    char _str[] = "ʥ�������´�������";
    SetWindowText(hnd, _str);

    playMusic(bkMusic[0]);

    IMAGE Img;
    loadimage(&Img, ".\\sources\\bk.png", 1280, 720);//���ؿ�ʼ����ı���ͼƬ
    putimage(0, 0, &Img);//�������

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
    for (i = 0; i < 5; i++)//�����������ťͼƬ
    {
        if (i % 2 == 1)
        {
            height = 338;//���ϴ�λ�����ͼƬ
        }
        drawAlpha(&button[i], width, height);//��͸����ͼ�������ťͼƬ
        width += 244;
        height = 448;
    }

    IMAGE title;
    loadimage(&title, ".\\sources\\title.jpg", 908, 162);//���ر���ͼƬ
    drawAlpha(&title, 186, 100);//��͸����ͼ���������

    width = 57; height = 448;
    MOUSEMSG mouse;
    while (true)//����¼����ڲ�ͬ����������������ת����Ӧ����
    {
        mouse = GetMouseMsg();

        if (mouse.x >= 57 && mouse.x <= 244 && mouse.y >= 448 && mouse.y <= 710)
        {
            drawAlpha(&newButton[0], 57, 448);
            if (mouse.uMsg == WM_LBUTTONUP)//������𣬽������а����
            {
                closeMusic(bkMusic[0]);
                show_rank();
                break;
            }
        }
        else if (mouse.x >= 301 && mouse.x <= 488 && mouse.y >= 338 && mouse.y <= 600)
        {
            drawAlpha(&newButton[1], 301, 338);
            //������𣬽��뿪ʼ��Ϸ����
            if (mouse.uMsg == WM_LBUTTONUP)
            {
                closeMusic(bkMusic[0]);
                showGamePage();
                break;
            }
        }
        else if (mouse.x >= 545 && mouse.x <= 732 && mouse.y >= 448 && mouse.y <= 710)
        {
            //������𣬽���ٿ�ȫ�����
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
            //��������˳���Ϸ
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
            //������𣬽���������Ա����
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
            for (int i = 0; i < 5; i++)//�����������ťͼƬ
            {
                if (i % 2 == 1)
                {
                    height = 338;//���ϴ�λ�����ͼƬ
                }
                drawAlpha(&button[i], width, height);//��͸����ͼ�������ťͼƬ
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
    InputBox(str, 20, "��ô�����ߴ��˵������ǣ�");
    player_name = str;
    showHomePage();
    _getch();
    closegraph();
    return 0;
}