#ifndef VIEW_H
#define VIEW_H
#include <iostream>
#include <easyx.h>
#include <graphics.h>
#include <conio.h>

//����������
/*ShowWindow(GetConsoleWindow(), SW_HIDE);*/

/*���ڴ�С1280^800*/

using namespace std;


void playMusic(string name);//�򿪡���������
void closeMusic(string name);//�ر�����


/*�زĳ�ʼ��*/

void card_sources_init();

void bk_sources_init();

void character_sources_init();

/*��͸����ͼ����*/
void drawAlpha(IMAGE* picture, int  picture_x, int picture_y);

/*չʾ�˵�����*/
void show_menu();

/*չʾ�ٿƽ���*/
void show_ency();
void show_ency_card1();
void show_ency_card2();
void show_ency_monster1();
void show_ency_bkStory();

/*չʾ����������*/
void show_credits();

/*���ƹؿ�*/
void show_map_node();

/*���Ƶ�ͼ(ѡ�ؽ���)*/
int show_map();

/*����һ����ť*/
void create_botton(const char* text, int x, int y, int w, int h);

/*����һ�����ֿ�*/
void create_textbox(int x, int y, int w, int h);

/*��ָ������������һ���߶�*/
void create_line(int a, int b);

/*����������*/
void return_main();

/*ת��ͼƬ*/
void transparentimage(IMAGE* dstimg, int x, int y, IMAGE* srcimg);

/*��ť��ʽ*/
void button_create(int x, int y, int w, int h, char* text);

/*���а����*/
//void show_rank();

/*�ɹ�����*/
//void show_win();


/*���ý���*/
//void show_option();

/*��������*/
// ������ʼλ�ú��ļ���
void AOEanimate(int x, int y, const char *s);
// �����������
void Atkanimate(int x, int y);
/*�ܵ�����ʱ��Ч��*/
void getHurtAnimate(int x, int y);
/*��ҳԶ�ʱ��Ч��*/
void defAnimate(int x, int y);
/*��һ�Ѫʱ��Ч��*/
void restHpAnimate(int x, int y);
#endif
