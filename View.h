#ifndef VIEW_H
#define VIEW_H
#include <iostream>
#include <easyx.h>
#include <graphics.h>
#include <conio.h>

//隐藏命令行
/*ShowWindow(GetConsoleWindow(), SW_HIDE);*/

/*窗口大小1280^800*/

using namespace std;


void playMusic(string name);//打开、播放音乐
void closeMusic(string name);//关闭音乐


/*素材初始化*/

void card_sources_init();

void bk_sources_init();

void character_sources_init();

/*半透明贴图函数*/
void drawAlpha(IMAGE* picture, int  picture_x, int picture_y);

/*展示菜单界面*/
void show_menu();

/*展示百科界面*/
void show_ency();
void show_ency_card1();
void show_ency_card2();
void show_ency_monster1();
void show_ency_bkStory();

/*展示制作人名单*/
void show_credits();

/*绘制关卡*/
void show_map_node();

/*绘制地图(选关界面)*/
int show_map();

/*生成一个按钮*/
void create_botton(const char* text, int x, int y, int w, int h);

/*生成一个文字框*/
void create_textbox(int x, int y, int w, int h);

/*在指定的两点生成一条线段*/
void create_line(int a, int b);

/*返回主界面*/
void return_main();

/*转换图片*/
void transparentimage(IMAGE* dstimg, int x, int y, IMAGE* srcimg);

/*按钮样式*/
void button_create(int x, int y, int w, int h, char* text);

/*排行榜界面*/
//void show_rank();

/*成功界面*/
//void show_win();


/*设置界面*/
//void show_option();

/*攻击动画*/
// 传入起始位置和文件名
void AOEanimate(int x, int y, const char *s);
// 传入怪物坐标
void Atkanimate(int x, int y);
/*受到自伤时的效果*/
void getHurtAnimate(int x, int y);
/*玩家吃盾时的效果*/
void defAnimate(int x, int y);
/*玩家回血时的效果*/
void restHpAnimate(int x, int y);
#endif
