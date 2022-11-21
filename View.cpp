#include"View.h"
#include <vector>
#pragma comment(lib,"Winmm.lib")
/*
* 负责人：
* 描述：
*	存储背景图片的素材库；
* 参数：最大素材存储数量
* 返回值：无
*/
vector<IMAGE> bk_sources(10);

//打开，播放音乐，需要传入音乐文件路径
void playMusic(string name)
{
	string open = "open ";
	string play = "play ";
	string repeat = " repeat";
	open = open.append(name);
	play = play.append(name);
	play = play.append(repeat);
	char* orderOpen = (char*)open.c_str();
	char* orderPlay = (char*)play.c_str();
	mciSendString(orderOpen, NULL, 0, NULL);
	mciSendString(orderPlay, NULL, 0, NULL);
}
//关闭音乐，需要传入音乐文件路径
void closeMusic(string name)
{
	string close = "close ";
	close = close.append(name);
	char* orderClose = (char*)close.c_str();
	mciSendString(orderClose, NULL, 0, NULL);
}

void bk_sources_init()
{
	int i = 0;
	loadimage(&bk_sources[i++], ".\\sources\\bk.png", 1280, 720);
	loadimage(&bk_sources[i++], ".\\sources\\bk2.png", 1280, 720);
	loadimage(&bk_sources[i++], ".\\sources\\fire.png", 50, 50);
	loadimage(&bk_sources[i++], ".\\sources\\monatk.png", 50, 50);
}

/*
* 负责人：
* 描述：
*	存储角色（包括英雄、怪物）图片的素材库；
* 参数：最大素材存储数量
* 返回值：无
*/
vector<IMAGE> character_sources(20);
void character_sources_init()
{
	int i = 0;
	loadimage(&character_sources[i++], (".\\sources\\shilaimiao.png"), 200, 200);
	loadimage(&character_sources[i++], (".\\sources\\shilaiwang.png"), 200, 200);
	loadimage(&character_sources[i++], (".\\sources\\fanzi.png"), 200, 200);
	loadimage(&character_sources[i++], (".\\sources\\chong.png"), 200, 200);
	loadimage(&character_sources[i++], (".\\sources\\bigchong.png"), 200, 200);
	loadimage(&character_sources[i++], (".\\sources\\KING.png"), 200, 200);
	loadimage(&character_sources[i++], (".\\sources\\kb1.png"), 200, 200);
	loadimage(&character_sources[i++], (".\\sources\\kb2.png"), 200, 200);
	loadimage(&character_sources[i++], (".\\sources\\kb3.png"), 200, 200);
	loadimage(&character_sources[i++], (".\\sources\\kb4.png"), 200, 200);
}

/*
* 负责人：
* 描述：
*	存储卡牌图片的素材库；
* 参数：最大素材存储数量
* 返回值：无
*/
vector<IMAGE> card_sources(30);
void card_sources_init()
{
	int i = 0;
	loadimage(&card_sources[i++], (".\\sources\\gongji.png"), 187, 262);
	loadimage(&card_sources[i++], (".\\sources\\fangyu.png"), 187, 262);
	loadimage(&card_sources[i++], (".\\sources\\quan.png"), 187, 262);
	loadimage(&card_sources[i++], (".\\sources\\fangun.png"), 187, 262);
	loadimage(&card_sources[i++], (".\\sources\\aoman.png"), 187, 262);
	loadimage(&card_sources[i++], (".\\sources\\yuxue.png"), 187, 262);
	loadimage(&card_sources[i++], (".\\sources\\cnm.png"), 187, 262);
	loadimage(&card_sources[i++], (".\\sources\\zhua.png"), 187, 262);
	loadimage(&card_sources[i++], (".\\sources\\ranshao.png"), 187, 262);
	loadimage(&card_sources[i++], (".\\sources\\budong.png"), 187, 262);

	loadimage(&card_sources[i++], (".\\sources\\gongji.png"), 84, 148);
	loadimage(&card_sources[i++], (".\\sources\\fangyu.png"), 84, 148);
	loadimage(&card_sources[i++], (".\\sources\\quan.png"), 84, 148);
	loadimage(&card_sources[i++], (".\\sources\\fangun.png"), 84, 148);
	loadimage(&card_sources[i++], (".\\sources\\aoman.png"), 84, 148);
	loadimage(&card_sources[i++], (".\\sources\\yuxue.png"), 84, 148);
	loadimage(&card_sources[i++], (".\\sources\\cnm.png"), 84, 148);
	loadimage(&card_sources[i++], (".\\sources\\zhua.png"), 84, 148);
	loadimage(&card_sources[i++], (".\\sources\\ranshao.png"), 84, 148);
	loadimage(&card_sources[i++], (".\\sources\\budong.png"), 84, 148);
}

/*生成一个按钮*/
void create_botton(const char* text, int x, int y, int w, int h)
{
	setbkmode(TRANSPARENT);
	setfillcolor(RGB(245, 245, 245));
	fillroundrect(x, y, x + w, y + h, 10, 10);
	settextstyle(20, 0, "宋体");
	int width = x + (w - textwidth(text)) / 2;
	int height = y + (h - textheight(text)) / 2;
	outtextxy(width, height, text);
}

vector<IMAGE>button(5);//储存开始界面的五个按钮
vector<IMAGE>newButton(5);//鼠标悬停时的图片

void drawAlpha(IMAGE* picture, int  picture_x, int picture_y) //x为载入图片的X坐标，y为Y坐标
{
	// 变量初始化
	DWORD* dst = GetImageBuffer();    // GetImageBuffer()函数，用于获取绘图设备的显存指针，EASYX自带
	DWORD* draw = GetImageBuffer();
	DWORD* src = GetImageBuffer(picture); //获取picture的显存指针
	int picture_width = picture->getwidth(); //获取picture的宽度，EASYX自带
	int picture_height = picture->getheight(); //获取picture的高度，EASYX自带
	int graphWidth = getwidth();       //获取绘图区的宽度，EASYX自带
	int graphHeight = getheight();     //获取绘图区的高度，EASYX自带
	int dstX = 0;    //在显存里像素的角标

	// 实现透明贴图 公式： Cp=αp*FP+(1-αp)*BP ， 贝叶斯定理来进行点颜色的概率计算
	for (int iy = 0; iy < picture_height; iy++)
	{
		for (int ix = 0; ix < picture_width; ix++)
		{
			int srcX = ix + iy * picture_width; //在显存里像素的角标
			int sa = ((src[srcX] & 0xff000000) >> 24); //0xAArrggbb;AA是透明度
			int sr = ((src[srcX] & 0xff0000) >> 16); //获取RGB里的R
			int sg = ((src[srcX] & 0xff00) >> 8);   //G
			int sb = src[srcX] & 0xff;              //B
			if (ix >= 0 && ix <= graphWidth && iy >= 0 && iy <= graphHeight && dstX <= graphWidth * graphHeight)
			{
				dstX = (ix + picture_x) + (iy + picture_y) * graphWidth; //在显存里像素的角标
				int dr = ((dst[dstX] & 0xff0000) >> 16);
				int dg = ((dst[dstX] & 0xff00) >> 8);
				int db = dst[dstX] & 0xff;
				draw[dstX] = ((sr * sa / 255 + dr * (255 - sa) / 255) << 16)  //公式： Cp=αp*FP+(1-αp)*BP  ； αp=sa/255 , FP=sr , BP=dr
					| ((sg * sa / 255 + dg * (255 - sa) / 255) << 8)         //αp=sa/255 , FP=sg , BP=dg
					| (sb * sa / 255 + db * (255 - sa) / 255);              //αp=sa/255 , FP=sb , BP=db
			}
		}
	}
}

/*按钮样式*/
void button_create(int x, int y, int w, int h, char* text)
{
	setbkmode(TRANSPARENT);//设置字体背景透明
	fillroundrect(x, y, x + w, y + h, 10, 10);//设置按钮
	// 输出字符串（MBCS 字符集）
	char s1[] = "黑体";
	settextstyle(30, 0, s1);
	int tx = x + (w - textwidth(text)) / 2;
	int ty = y + (h - textheight(text)) / 2;

	outtextxy(tx, ty, text);
}

void show_map_node()
{
	BeginBatchDraw();
	putimage(0, 0, &bk_sources[0]);
	settextcolor(BLACK);
	setfillcolor(GREEN);
	create_botton("结束回合", 1100, 500, 125, 50);
	outtextxy(90, 525, "玩家体力值");
	solidcircle(100, 600, 50);
	EndBatchDraw();
}

void show_ency_card1()
{

	IMAGE Img;
	loadimage(&Img, ".\\sources\\card1.png", 1280, 720);
	putimage(0, 0, &Img);

	//返回按钮
	IMAGE back;
	loadimage(&back, ".\\sources\\return.png", 90, 40);
	drawAlpha(&back, 0, 20);

	IMAGE nextPage;
	loadimage(&nextPage, ".\\sources\\go.png", 100, 50);
	drawAlpha(&nextPage, 1180, 640);


	MOUSEMSG mouse;
	while (true)
	{
		mouse = GetMouseMsg();
		if (mouse.uMsg == WM_LBUTTONUP)
		{
			if (mouse.x >= 0 && mouse.x <= 90 && mouse.y >= 20 && mouse.y <= 60)
			{
				show_ency();
			}
			else if (mouse.x >= 1180 && mouse.x <= 1280 && mouse.y >= 640 && mouse.y <= 690)
			{
				show_ency_card2();
			}
		}

	}

}


void show_ency_card2()
{

	IMAGE Img;
	loadimage(&Img, ".\\sources\\card2.png", 1280, 720);
	putimage(0, 0, &Img);

	//返回按钮
	IMAGE back;
	loadimage(&back, ".\\sources\\return.png", 90, 40);
	drawAlpha(&back, 0, 20);
	IMAGE goback;
	loadimage(&goback, ".\\sources\\goback.png", 100, 50);
	drawAlpha(&goback, 0, 640);

	MOUSEMSG mouse;
	while (true)
	{
		mouse = GetMouseMsg();
		if (mouse.uMsg == WM_LBUTTONUP)
		{
			if (mouse.x >= 0 && mouse.x <= 90 && mouse.y >= 20 && mouse.y <= 60)
			{
				show_ency();
			}
			if (mouse.x >= 0 && mouse.x <= 100 && mouse.y >= 640 && mouse.y <= 690)
			{
				show_ency_card1();
			}
		}

	}

}

void show_ency_monster1()
{
	//怪物图鉴的背景图片的加载
	IMAGE Img;
	loadimage(&Img, ".\\sources\\monster1.png", 1280, 720);
	putimage(0, 0, &Img);

	//返回按钮
	IMAGE back;
	loadimage(&back, ".\\sources\\return.png", 90, 40);
	drawAlpha(&back, 0, 20);

	//鼠标事件
	MOUSEMSG mouse;
	while (true)
	{
		mouse = GetMouseMsg();
		if (mouse.uMsg == WM_LBUTTONUP)
		{
			if (mouse.x >= 0 && mouse.x <= 90 && mouse.y >= 20 && mouse.y <= 60)
			{
				//按下返回按钮，返回百科全书界面
				show_ency();
			}
		}
	}
}

void show_ency_bkStory()
{
	//背景故事界面的背景图片加载
	IMAGE Img;
	loadimage(&Img, ".\\sources\\bkStory.png", 1280, 720);
	putimage(0, 0, &Img);

	//返回按钮
	IMAGE back;
	loadimage(&back, ".\\sources\\return.png", 90, 40);
	drawAlpha(&back, 0, 20);

	//鼠标事件
	MOUSEMSG mouse;
	while (true)
	{
		mouse = GetMouseMsg();
		if (mouse.uMsg == WM_LBUTTONUP)
		{
			if (mouse.x >= 0 && mouse.x <= 90 && mouse.y >= 20 && mouse.y <= 60)
			{
				//点击可返回百科全书页面
				show_ency();
			}
		}
	}
}

void transparentimage(IMAGE* dstimg, int x, int y, IMAGE* srcimg)
{
	HDC dstDC = GetImageHDC(dstimg);
	HDC srcDC = GetImageHDC(srcimg);
	int w = srcimg->getwidth();
	int h = srcimg->getheight();
	// 结构体的第三个成员表示额外的透明度，0 表示全透明，255 表示不透明。
	BLENDFUNCTION bf = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };
	// 使用 Windows GDI 函数实现半透明位图
	AlphaBlend(dstDC, x, y, w, h, srcDC, 0, 0, w, h, bf);
}

/*玩家使用AOE卡牌时的效果*/
void AOEanimate(int x, int y, const char *s)
{
	extern void init_battle();
	init_battle();
	IMAGE imshow;//需要显示的图片
	//0、创建图片向量
	vector<IMAGE> run;
	//1、图片顺序名称数组
	TCHAR imgname[20];
	//2、载入图片
	for (int i = 0; i < 8; i++)
	{
		_stprintf_s(imgname, _T("sources/%s/%d.png"), s, i);
		IMAGE im;
		loadimage(&im, imgname, 800, 200);
		run.push_back(im);
	}
	//3、输出图片
	int i = 0;
	BeginBatchDraw();
	while (i < run.size())
	{
		imshow = run[i];
		transparentimage(NULL, x, y, &imshow);
		FlushBatchDraw();
		i++;
		Sleep(100);
	}
	EndBatchDraw();
}

/*玩家出牌时的效果*/
void Atkanimate(int x, int y)
{
	extern void init_battle();
	init_battle();
	IMAGE imshow;//需要显示的图片
	//0、创建图片向量
	vector<IMAGE> run;
	//1、图片顺序名称数组
	TCHAR imgname[20];
	//2、载入图片
	for (int i = 1; i <= 4; i++)
	{
		_stprintf_s(imgname, _T("sources/test/%d.png"), i);
		IMAGE im;
		loadimage(&im, imgname, 100, 300);
		run.push_back(im);
	}
	//3、输出图片
	int i = 0;
	BeginBatchDraw();
	for (int i = 0; i < 4; i++)
	{
		while (i < run.size())
		{
			imshow = run[i];
			transparentimage(NULL, x, y, &imshow);
			FlushBatchDraw();
			i++;
			Sleep(100);
		}
	}
	EndBatchDraw();
	//show_map_node();
}

/*受到自伤时的效果*/
void getHurtAnimate(int x, int y)
{
	extern void init_battle();
	init_battle();
	IMAGE imshow;//需要显示的图片
	//0、创建图片向量
	vector<IMAGE> run;
	//1、图片顺序名称数组
	TCHAR imgname[25];
	//2、载入图片
	for (int i = 1; i <= 18; i++)
	{
		_stprintf_s(imgname, _T("sources/test8/%d.png"), i);
		IMAGE im;
		loadimage(&im, imgname, 360, 390);
		run.push_back(im);
	}
	//3、输出图片
	int i = 0;
	BeginBatchDraw();
	for (int i = 0; i < 3; i++)
	{
		while (i < run.size())
		{
			imshow = run[i];
			transparentimage(NULL, x, y, &imshow);
			FlushBatchDraw();
			i++;
			Sleep(100);
		}
	}
	EndBatchDraw();
}

/*玩家吃盾时的效果*/
void defAnimate(int x, int y)
{
	extern void init_battle();
	init_battle();
	IMAGE imshow;//需要显示的图片
	//0、创建图片向量
	vector<IMAGE> run;
	//1、图片顺序名称数组
	TCHAR imgname[20];
	//2、载入图片
	for (int i = 1; i <= 9; i++)
	{
		_stprintf_s(imgname, _T("sources/test5/%d.png"), i);
		IMAGE im;
		loadimage(&im, imgname, 300, 267);
		run.push_back(im);
	}
	//3、输出图片
	int i = 0;
	BeginBatchDraw();
	for (int i = 0; i < 3; i++)
	{
		while (i < run.size())
		{
			imshow = run[i];
			transparentimage(NULL, x, y, &imshow);
			FlushBatchDraw();
			i++;
			Sleep(100);
		}
	}
	EndBatchDraw();
}

/*玩家回血时的效果*/
void restHpAnimate(int x, int y)
{
	extern void init_battle();
	init_battle();
	IMAGE imshow;//需要显示的图片
	//0、创建图片向量
	vector<IMAGE> run;
	//1、图片顺序名称数组
	TCHAR imgname[20];
	//2、载入图片
	for (int i = 1; i <= 8; i++)
	{
		_stprintf_s(imgname, _T("sources/test7/%d.png"), i);
		IMAGE im;
		loadimage(&im, imgname, 182, 260);
		run.push_back(im);
	}
	//3、输出图片
	int i = 0;
	BeginBatchDraw();
	for (int i = 0; i < 8; i++)
	{
		while (i < run.size())
		{
			imshow = run[i];
			transparentimage(NULL, x, y, &imshow);
			FlushBatchDraw();
			i++;
			Sleep(100);
		}
	}
	EndBatchDraw();
}

