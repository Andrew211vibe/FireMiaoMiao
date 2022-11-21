#include"View.h"
#include <vector>
#pragma comment(lib,"Winmm.lib")
/*
* �����ˣ�
* ������
*	�洢����ͼƬ���زĿ⣻
* ����������زĴ洢����
* ����ֵ����
*/
vector<IMAGE> bk_sources(10);

//�򿪣��������֣���Ҫ���������ļ�·��
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
//�ر����֣���Ҫ���������ļ�·��
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
* �����ˣ�
* ������
*	�洢��ɫ������Ӣ�ۡ����ͼƬ���زĿ⣻
* ����������زĴ洢����
* ����ֵ����
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
* �����ˣ�
* ������
*	�洢����ͼƬ���زĿ⣻
* ����������زĴ洢����
* ����ֵ����
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

/*����һ����ť*/
void create_botton(const char* text, int x, int y, int w, int h)
{
	setbkmode(TRANSPARENT);
	setfillcolor(RGB(245, 245, 245));
	fillroundrect(x, y, x + w, y + h, 10, 10);
	settextstyle(20, 0, "����");
	int width = x + (w - textwidth(text)) / 2;
	int height = y + (h - textheight(text)) / 2;
	outtextxy(width, height, text);
}

vector<IMAGE>button(5);//���濪ʼ����������ť
vector<IMAGE>newButton(5);//�����ͣʱ��ͼƬ

void drawAlpha(IMAGE* picture, int  picture_x, int picture_y) //xΪ����ͼƬ��X���꣬yΪY����
{
	// ������ʼ��
	DWORD* dst = GetImageBuffer();    // GetImageBuffer()���������ڻ�ȡ��ͼ�豸���Դ�ָ�룬EASYX�Դ�
	DWORD* draw = GetImageBuffer();
	DWORD* src = GetImageBuffer(picture); //��ȡpicture���Դ�ָ��
	int picture_width = picture->getwidth(); //��ȡpicture�Ŀ�ȣ�EASYX�Դ�
	int picture_height = picture->getheight(); //��ȡpicture�ĸ߶ȣ�EASYX�Դ�
	int graphWidth = getwidth();       //��ȡ��ͼ���Ŀ�ȣ�EASYX�Դ�
	int graphHeight = getheight();     //��ȡ��ͼ���ĸ߶ȣ�EASYX�Դ�
	int dstX = 0;    //���Դ������صĽǱ�

	// ʵ��͸����ͼ ��ʽ�� Cp=��p*FP+(1-��p)*BP �� ��Ҷ˹���������е���ɫ�ĸ��ʼ���
	for (int iy = 0; iy < picture_height; iy++)
	{
		for (int ix = 0; ix < picture_width; ix++)
		{
			int srcX = ix + iy * picture_width; //���Դ������صĽǱ�
			int sa = ((src[srcX] & 0xff000000) >> 24); //0xAArrggbb;AA��͸����
			int sr = ((src[srcX] & 0xff0000) >> 16); //��ȡRGB���R
			int sg = ((src[srcX] & 0xff00) >> 8);   //G
			int sb = src[srcX] & 0xff;              //B
			if (ix >= 0 && ix <= graphWidth && iy >= 0 && iy <= graphHeight && dstX <= graphWidth * graphHeight)
			{
				dstX = (ix + picture_x) + (iy + picture_y) * graphWidth; //���Դ������صĽǱ�
				int dr = ((dst[dstX] & 0xff0000) >> 16);
				int dg = ((dst[dstX] & 0xff00) >> 8);
				int db = dst[dstX] & 0xff;
				draw[dstX] = ((sr * sa / 255 + dr * (255 - sa) / 255) << 16)  //��ʽ�� Cp=��p*FP+(1-��p)*BP  �� ��p=sa/255 , FP=sr , BP=dr
					| ((sg * sa / 255 + dg * (255 - sa) / 255) << 8)         //��p=sa/255 , FP=sg , BP=dg
					| (sb * sa / 255 + db * (255 - sa) / 255);              //��p=sa/255 , FP=sb , BP=db
			}
		}
	}
}

/*��ť��ʽ*/
void button_create(int x, int y, int w, int h, char* text)
{
	setbkmode(TRANSPARENT);//�������屳��͸��
	fillroundrect(x, y, x + w, y + h, 10, 10);//���ð�ť
	// ����ַ�����MBCS �ַ�����
	char s1[] = "����";
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
	create_botton("�����غ�", 1100, 500, 125, 50);
	outtextxy(90, 525, "�������ֵ");
	solidcircle(100, 600, 50);
	EndBatchDraw();
}

void show_ency_card1()
{

	IMAGE Img;
	loadimage(&Img, ".\\sources\\card1.png", 1280, 720);
	putimage(0, 0, &Img);

	//���ذ�ť
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

	//���ذ�ť
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
	//����ͼ���ı���ͼƬ�ļ���
	IMAGE Img;
	loadimage(&Img, ".\\sources\\monster1.png", 1280, 720);
	putimage(0, 0, &Img);

	//���ذ�ť
	IMAGE back;
	loadimage(&back, ".\\sources\\return.png", 90, 40);
	drawAlpha(&back, 0, 20);

	//����¼�
	MOUSEMSG mouse;
	while (true)
	{
		mouse = GetMouseMsg();
		if (mouse.uMsg == WM_LBUTTONUP)
		{
			if (mouse.x >= 0 && mouse.x <= 90 && mouse.y >= 20 && mouse.y <= 60)
			{
				//���·��ذ�ť�����ذٿ�ȫ�����
				show_ency();
			}
		}
	}
}

void show_ency_bkStory()
{
	//�������½���ı���ͼƬ����
	IMAGE Img;
	loadimage(&Img, ".\\sources\\bkStory.png", 1280, 720);
	putimage(0, 0, &Img);

	//���ذ�ť
	IMAGE back;
	loadimage(&back, ".\\sources\\return.png", 90, 40);
	drawAlpha(&back, 0, 20);

	//����¼�
	MOUSEMSG mouse;
	while (true)
	{
		mouse = GetMouseMsg();
		if (mouse.uMsg == WM_LBUTTONUP)
		{
			if (mouse.x >= 0 && mouse.x <= 90 && mouse.y >= 20 && mouse.y <= 60)
			{
				//����ɷ��ذٿ�ȫ��ҳ��
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
	// �ṹ��ĵ�������Ա��ʾ�����͸���ȣ�0 ��ʾȫ͸����255 ��ʾ��͸����
	BLENDFUNCTION bf = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };
	// ʹ�� Windows GDI ����ʵ�ְ�͸��λͼ
	AlphaBlend(dstDC, x, y, w, h, srcDC, 0, 0, w, h, bf);
}

/*���ʹ��AOE����ʱ��Ч��*/
void AOEanimate(int x, int y, const char *s)
{
	extern void init_battle();
	init_battle();
	IMAGE imshow;//��Ҫ��ʾ��ͼƬ
	//0������ͼƬ����
	vector<IMAGE> run;
	//1��ͼƬ˳����������
	TCHAR imgname[20];
	//2������ͼƬ
	for (int i = 0; i < 8; i++)
	{
		_stprintf_s(imgname, _T("sources/%s/%d.png"), s, i);
		IMAGE im;
		loadimage(&im, imgname, 800, 200);
		run.push_back(im);
	}
	//3�����ͼƬ
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

/*��ҳ���ʱ��Ч��*/
void Atkanimate(int x, int y)
{
	extern void init_battle();
	init_battle();
	IMAGE imshow;//��Ҫ��ʾ��ͼƬ
	//0������ͼƬ����
	vector<IMAGE> run;
	//1��ͼƬ˳����������
	TCHAR imgname[20];
	//2������ͼƬ
	for (int i = 1; i <= 4; i++)
	{
		_stprintf_s(imgname, _T("sources/test/%d.png"), i);
		IMAGE im;
		loadimage(&im, imgname, 100, 300);
		run.push_back(im);
	}
	//3�����ͼƬ
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

/*�ܵ�����ʱ��Ч��*/
void getHurtAnimate(int x, int y)
{
	extern void init_battle();
	init_battle();
	IMAGE imshow;//��Ҫ��ʾ��ͼƬ
	//0������ͼƬ����
	vector<IMAGE> run;
	//1��ͼƬ˳����������
	TCHAR imgname[25];
	//2������ͼƬ
	for (int i = 1; i <= 18; i++)
	{
		_stprintf_s(imgname, _T("sources/test8/%d.png"), i);
		IMAGE im;
		loadimage(&im, imgname, 360, 390);
		run.push_back(im);
	}
	//3�����ͼƬ
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

/*��ҳԶ�ʱ��Ч��*/
void defAnimate(int x, int y)
{
	extern void init_battle();
	init_battle();
	IMAGE imshow;//��Ҫ��ʾ��ͼƬ
	//0������ͼƬ����
	vector<IMAGE> run;
	//1��ͼƬ˳����������
	TCHAR imgname[20];
	//2������ͼƬ
	for (int i = 1; i <= 9; i++)
	{
		_stprintf_s(imgname, _T("sources/test5/%d.png"), i);
		IMAGE im;
		loadimage(&im, imgname, 300, 267);
		run.push_back(im);
	}
	//3�����ͼƬ
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

/*��һ�Ѫʱ��Ч��*/
void restHpAnimate(int x, int y)
{
	extern void init_battle();
	init_battle();
	IMAGE imshow;//��Ҫ��ʾ��ͼƬ
	//0������ͼƬ����
	vector<IMAGE> run;
	//1��ͼƬ˳����������
	TCHAR imgname[20];
	//2������ͼƬ
	for (int i = 1; i <= 8; i++)
	{
		_stprintf_s(imgname, _T("sources/test7/%d.png"), i);
		IMAGE im;
		loadimage(&im, imgname, 182, 260);
		run.push_back(im);
	}
	//3�����ͼƬ
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

