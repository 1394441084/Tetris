#pragma once 

#include <stdio.h>
#include <Windows.h>
#include <string>
#include <graphics.h>//EasyX图形库头文件
#include <time.h>
#include <conio.h>//键盘控制,kbhit(按下键盘返回1)

using namespace std;

//定义小矩形的数值
#define XJX_QS_X  30  //游戏区小矩形X轴起始点
#define XJX_QS_Y  15  //游戏区小矩形Y轴起始点
#define XJX_ZZ_X  353 //游戏区小矩形X轴终值点
#define XJX_ZZ_Y  585 //游戏区小矩形Y轴终值点

#define DJX_QS_X  28  //游戏区大矩形X轴起始点
#define DJX_QS_Y  13  //游戏区大矩形Y轴起始点
#define DJX_ZZ_X  355 //游戏区大矩形X轴终值点
#define DJX_ZZ_Y  587 //游戏区大矩形Y轴终值点

#define LANDING_SPEED 2 //1为方块每次下降为1格,2为下降为0.5格
#define STRSIZE 16
#define SQUARE_SPECIES 5  //方块种类
#define SQUARE_CHANGE  4  //方块的变化
#define SQUARE_HIGH    5  //方块高度,行,Y多少格
#define SQUARE_WIDE    5  //方块宽度,列,X多少格
#define UNIT_SIZE   16  //方块单元的大小
#define RIGHT_SQUARE_X     392  //右上角下一块方块区域起始X=392
#define RIGHT_SQUARE_Y      36  //右上角下一块方块区域起始Y=36
#define J_SQUARE_X    143//降落方块的起始X:112,计算方式:
#define J_SQUARE_Y    8//降落方块的起始Y,计算方式:XJX_QS_Y-UNIT_SIZE-9
#define YXQZGZS_X   20//游戏区X轴总格子数,计算方式:(XJX_ZZ_X-XJX_QS_X)/UNIT_SIZE
#define YXQZGZS_Y	35//游戏区Y轴总格子数,计算方式:(XJX_ZZ_Y-XJX_QS_Y)/UNIT_SIZE
int Game_area[YXQZGZS_Y][YXQZGZS_X];//游戏活动区使用二维数组表示

int color0[YXQZGZS_Y][YXQZGZS_X] ;//表示游戏区方块对应的颜色

//UP, DOWN, LEFT, RIGHT, SPACE.
#define KEY_UP      72  //上按键码72
#define KEY_DOWN    80  //下按键码80
#define KEY_LEFT    75	//左按键码75
#define KEY_RIGHT   77	//右按键码77
#define KEY_SPACE   32	//空格按键码32

int score = 0;//总分数
int grade = 0;//等级
int NewSquare = -1;//下一块方块的序号
int J_NewSquare = -1;//当前下降方块的序号
int speed = 500;

typedef long long int_64;

typedef enum _Square_facing _facing;//方块朝向
enum _Square_facing {//方块的朝向,方块的变化
	_KEY_UP,	//上
	_KEY_DOWN,	//下
	_KEY_LEFT,	//左
	_KEY_RIGHT	//右
};
typedef enum {//方块的移动
	_move_DOWN,  //下
	_move_LEFT,	 //左
	_move_RIGHT	 //右
}_move;


//欢迎界面
void Welcome_interface() {//全局作用
	//创建一个黑漆漆的控制台界面(背景画)
	initgraph(500, 600);//默认黑漆漆(背景画)
	
	//设置窗口标题
	HWND windows= GetHWnd();//获得当前窗口,HWND是类型,windows是变量接收窗口句柄的
	SetWindowText(windows, _T("俄罗斯方块   作者:周伟长"));//设置窗口文本标题

	//设置文本字体样式
	settextstyle(40, 0,_T( "微软雅黑"));
	setcolor(GREEN);//设置颜色(绿色)
	outtextxy(90,200,_T("俄罗斯方块 作者:周伟长"));
	outtextxy(90, 300, _T("编程从俄罗斯方块开始"));
	setbkcolor(RGB(153, 217, 234));//设置(背景画)背景色为很蓝色
	Sleep(3000);//休眠(暂停)三秒
}

//初始化游戏场景背景
void Game_background() {
	cleardevice();//清除屏幕,保留背景画
	
	//写入分数,等级,操作说明等文本
	char str[STRSIZE];//转换字符串需用的数组
	settextstyle(42, 0, _T("微软雅黑"));
	setcolor(RGB(62, 72, 204));//设置颜色
	outtextxy(358, 126, _T("分数:"));
	sprintf_s(str, "%d", score);//将整型转换为字符串
	for (int i = 0, j = 0; i < STRSIZE; i++) {//在屏幕输出分数
		if (str[i] == '\0')break;
		if (score > 99999999 && i == 8) {
			outtextxy(358 + i * 17, 166, '\n');
			outtextxy(358 + j * 17, 166 + 40, str[i]);
			j++;
		}
		else {
			outtextxy(358 + i * 17, 166, str[i]);//将分数输入到此处
		}
	}
	outtextxy(358, 251, _T("等级:"));
	sprintf_s(str, "%d", grade);//将整型转换为字符串
	for (int i = 0; i < STRSIZE; i++) {//输出等级
		if (str[i] == '\0')break;
		outtextxy(358 + i * 17, 291, str[i]);//将等级输入到此处
	}
	outtextxy(358, 338, _T("操作说明:"));
	outtextxy(365, 377, _T(" ↑ :旋转"));
	outtextxy(365, 418, _T(" ↓ :快慢"));
	outtextxy(350, 458, _T("  ←:左移"));
	outtextxy(350, 498, _T("  →:右移"));
	outtextxy(355, 538, _T("空格:暂停"));
	
	//画游戏场景的擂台
	setcolor(RGB(250,18,33));//设置颜色(红色)
	rectangle(DJX_QS_X, DJX_QS_Y, DJX_ZZ_X, DJX_ZZ_Y);//画大矩形
	rectangle(XJX_QS_X, XJX_QS_Y, XJX_ZZ_X, XJX_ZZ_Y);//画小矩形
	setfillcolor(RGB(250, 18, 33));//设置填充颜色
	floodfill(XJX_QS_X-1, XJX_QS_Y-1, RGB(250, 18, 33));//从填充区域中任一坐标,遇到RED(自己定义)颜色停止
	
	//画下一块的视图区域
	setcolor(RGB(255, 245, 0));//设置画笔颜色()
	rectangle(373, 16, 483, 118);//画大矩形
	setbkcolor(RGB(255, 255, 255));//设置从现在开始到后面的背景色,除非再次设置
	setfillcolor(RGB(255, 255, 255));//设置填充颜色
	floodfill(386, 47, RGB(255, 245, 0));//从填充区域中任一坐标,遇到(自己定义)颜色停止
	settextstyle(20, 0, _T("微软雅黑"));//设置字体
	setcolor(RGB(250, 18, 33));//设置颜色
	outtextxy(377, 17, _T("下一块:"));//写入文本
	setcolor(RGB(255, 245, 0));//设置画笔颜色
	rectangle(375, 18, 481, 116);//画小矩形
	setfillcolor(RGB(255, 245, 0));//设置填充颜色
	floodfill(374, 17, RGB(255, 245, 0));//从填充区域中任一坐标,遇到RED(自己定义)颜色停止
}

//方块的表示,0-3=I,4-7=L,8-11=T,12-15=N,16-19田
int square[SQUARE_SPECIES * SQUARE_CHANGE][SQUARE_HIGH][SQUARE_WIDE] = {
	//I型方块的四种形态
	{0,0,0,0,0,
	 0,0,1,0,0,
	 0,0,1,0,0,
	 0,0,1,0,0,
	 0,0,1,0,0},

	 {0,0,0,0,0,
	  0,0,0,0,0,
	  1,1,1,1,0,
	  0,0,0,0,0,
	  0,0,0,0,0},

	{0,0,0,0,0,
	 0,0,1,0,0,
	 0,0,1,0,0,
	 0,0,1,0,0,
	 0,0,1,0,0},

	 {0,0,0,0,0,
	  0,0,0,0,0,
	  1,1,1,1,0,
	  0,0,0,0,0,
	  0,0,0,0,0},

	  //L型方块的四种形态
	 {0,0,0,0,0,
	  0,0,1,0,0,
	  0,0,1,0,0,
	  0,0,1,1,0,
	  0,0,0,0,0},

	 {0,0,0,0,0,
	  0,0,0,0,0,
	  0,1,1,1,0,
	  0,1,0,0,0,
	  0,0,0,0,0},

	 {0,0,0,0,0,
	  0,1,1,0,0,
	  0,0,1,0,0,
	  0,0,1,0,0,
	  0,0,0,0,0},

	 {0,0,0,0,0,
	  0,0,0,1,0,
	  0,1,1,1,0,
	  0,0,0,0,0,
	  0,0,0,0,0},

	  //丄型的四种形态
	 {0,0,0,0,0,
	  0,0,1,0,0,
	  0,1,1,1,0,
	  0,0,0,0,0,
	  0,0,0,0,0},

	 {0,0,0,0,0,
	  0,0,1,0,0,
	  0,0,1,1,0,
	  0,0,1,0,0,
	  0,0,0,0,0},

	 {0,0,0,0,0,
	  0,0,1,0,0,
	  0,1,1,0,0,
	  0,0,1,0,0,
	  0,0,0,0,0},

	 {0,0,0,0,0,
	  0,0,0,0,0,
	  0,1,1,1,0,
	  0,0,1,0,0,
	  0,0,0,0,0},

	  //N型的四种形态
	 {0,0,0,0,0,
	  0,0,1,0,0,
	  0,1,1,0,0,
	  0,1,0,0,0,
	  0,0,0,0,0},

	 {0,0,0,0,0,
	  0,1,1,0,0,
	  0,0,1,1,0,
	  0,0,0,0,0,
	  0,0,0,0,0},

	 {0,0,0,0,0,
	  0,1,0,0,0,
	  0,1,1,0,0,
	  0,0,1,0,0,
	  0,0,0,0,0},

	 {0,0,0,0,0,
	  0,0,1,1,0,
	  0,1,1,0,0,
	  0,0,0,0,0,
	  0,0,0,0,0},

  //方形的四种形态
	{ 0,0,0,0,0,
	  0,0,0,0,0,
	  0,1,1,0,0,
	  0,1,1,0,0,
	  0,0,0,0,0 },

	{ 0,0,0,0,0,
	  0,0,0,0,0,
	  0,1,1,0,0,
	  0,1,1,0,0,
	  0,0,0,0,0 },

	{ 0,0,0,0,0,
	  0,0,0,0,0,
	  0,1,1,0,0,
	  0,1,1,0,0,
	  0,0,0,0,0 },

    { 0,0,0,0,0,
      0,0,0,0,0,
      0,1,1,0,0,
	  0,1,1,0,0,
	  0,0,0,0,0 },
	};

	int Color[SQUARE_SPECIES] = {//颜色数组
	GREEN,YELLOW,RED,BLUE,BROWN
	};


	//清除方块//方块起始点:X,Y,方块朝向
	void Clear_square(int_64 X,int_64 Y, _facing facing) {
		int id = J_NewSquare * SQUARE_CHANGE + facing;
		setfillcolor(RGB(153, 217, 234));
		for (int_64 i = 0; i < SQUARE_HIGH; i++) {
			for (int_64 j = 0; j < SQUARE_WIDE; j++) {
				if (square[id][i][j] == 1) {
					int_64 x = X + j * UNIT_SIZE;
					int_64 y = Y + i * UNIT_SIZE;
					bar(x, y,x + UNIT_SIZE, y + UNIT_SIZE);//画一个无边框矩形,有颜色的
				}
			}
		}
	}

//绘制方块
void drawing_box(int_64 X,int_64 Y,int rgb) {
	setbkcolor(RGB(255, 255,255));//设置(背景画)背景色为很蓝色
	setcolor(RGB(255, 245, 0));
	setfillcolor(Color[rgb]);//设置填充颜色,由随机值来定
	for (int_64 i = 0; i < SQUARE_HIGH; i++) {
		for (int_64 j = 0; j < SQUARE_WIDE; j++) {
			if(square[rgb * SQUARE_CHANGE][i][j]==1){
				fillrectangle(X + j * UNIT_SIZE, Y + i * UNIT_SIZE,//画一个有边框矩形,有颜色的
					X + j * UNIT_SIZE + UNIT_SIZE, Y + i * UNIT_SIZE + UNIT_SIZE);

			//setfillcolor(BLACK);//设置填充颜色 NewSquare
			//bar(SQUARE_X + j * UNIT_SIZE, SQUARE_Y + i * UNIT_SIZE,//画一个无边框矩形,有颜色的
				//SQUARE_X + j * UNIT_SIZE + UNIT_SIZE, SQUARE_Y + i * UNIT_SIZE + UNIT_SIZE);
			}
		}
	}
}
void drawing_box(int_64 X, int_64 Y, int rgb, _facing facing) {
	setbkcolor(RGB(255, 255, 255));//设置(背景画)背景色为很蓝色
	setcolor(RGB(255, 245, 0));
	int id = J_NewSquare * SQUARE_CHANGE + facing;
	setfillcolor(Color[rgb]);//设置填充颜色,由随机值来定
	for (int_64 i = 0; i < SQUARE_HIGH; i++) {
		for (int_64 j = 0; j < SQUARE_WIDE; j++) {
			if (square[id][i][j] == 1) {
				fillrectangle(X + j * UNIT_SIZE, Y + i * UNIT_SIZE,//画一个有边框矩形,有颜色的
					X + j * UNIT_SIZE + UNIT_SIZE, Y + i * UNIT_SIZE + UNIT_SIZE);

				//setfillcolor(BLACK);//设置填充颜色 NewSquare
				//bar(SQUARE_X + j * UNIT_SIZE, SQUARE_Y + i * UNIT_SIZE,//画一个无边框矩形,有颜色的
					//SQUARE_X + j * UNIT_SIZE + UNIT_SIZE, SQUARE_Y + i * UNIT_SIZE + UNIT_SIZE);
			}
		}
	}
}


//右上角新方块的产生
void new_square() {
	//清空方块生成,右上角的矩形区域,保留此区域背景色,清除旧方块
	clearrectangle(RIGHT_SQUARE_X, RIGHT_SQUARE_Y, RIGHT_SQUARE_X + UNIT_SIZE * SQUARE_WIDE, RIGHT_SQUARE_Y + UNIT_SIZE * SQUARE_HIGH);

	//随机选择一种方块
	srand(time(NULL));//srand随机数,产生随机种子的;(返回无符号整型时间(time)(什么时候开始))
	NewSquare = rand() % SQUARE_SPECIES;//取余数限定5,rand()取随机数种,0-4的随机值
	drawing_box(RIGHT_SQUARE_X, RIGHT_SQUARE_Y, NewSquare);//画方块
}


//能否移动
int moveable(int x,int y, _move moveb,_facing facing) {
	//计算当前方块在左上角在游戏区中39*23第多少行的,第多少列的位置
	//起始位置的起始格子位置
	int moveX = (x - XJX_QS_X-1) / UNIT_SIZE; //计算方块位于哪一块格子
	//因为降落起始位置是自定义的-1格子,为了不让算术丢失精度,所以:
	int moveY= ((y- J_SQUARE_Y) -(XJX_QS_Y+1)) / UNIT_SIZE;
	int shape = J_NewSquare * SQUARE_CHANGE + facing;//确认方块的位置,计算第几个二维数组
	int ret = 1;//计算

	//如果在指定位置可以移动
	if (moveb == _move_DOWN) {
		//判断是否实心
		for (int i = 0; i < SQUARE_HIGH; i++) {
			for (int j = 0; j < SQUARE_WIDE; j++) {
		//是否实心&&(实心块+i+1没超出游戏区Y轴总格子数||(碰到实心格子==1))
				if (square[shape][i][j] == 1 &&
					(moveY + i + 1 >= YXQZGZS_Y || Game_area[moveY + i + 1][moveX + j] == 1)) {
					ret = 0;
				}
			}
		}
	}
	else if (moveb == _move_LEFT) {
		for (int i = 0; i < SQUARE_HIGH; i++) {
			for (int j = 0; j < SQUARE_WIDE; j++) {
				if (square[shape][i][j] == 1 &&
					(moveX + j  == 0 || Game_area[moveY + i][moveX + j-1] == 1)) {
					ret = 0;
				}
			}
		}
	}
	else if (moveb == _move_RIGHT) {
		for (int i = 0; i < SQUARE_HIGH; i++) {
			for (int j = 0; j < SQUARE_WIDE; j++) {
				if (square[shape][i][j] == 1 &&
					(moveX + j +1 == YXQZGZS_X || Game_area[moveY + i][moveX + j+1] == 1)) {
					ret = 0;
				}
			}
		}
	}
	return ret;
}

//检测游戏是否结束
void Check_whether_the_game_is_over() {
	if (moveable(J_SQUARE_X, J_SQUARE_Y, _move_DOWN, _KEY_UP)==0) {
		setcolor(BLACK);//设置颜色
		settextstyle(42, 0, _T("微软雅黑"));
		outtextxy(120, 275, _T("你失败了."));
		Sleep(1000);//休眠1秒
		system("pause");//暂停
		closegraph();//关闭图形库
		exit(0);//程序结束
	}
}

//能否变形,判断当前方块是否可以转向到未来指定方向
int Can_it_be_deformed(int x,int y, _facing  facing0) {
	int shape= J_NewSquare * SQUARE_CHANGE + facing0;//确认方块的位置

	if (moveable(x, y, _move_DOWN, facing0)==0) {
		return 0;
	}
	else if (moveable(x, y, _move_LEFT, facing0) == 0) {
		return 0;
	}
	else if (moveable(x, y, _move_RIGHT, facing0) == 0) {
		return 0;
	}
	return 1;
}

void wait(int interval) {//睡眠函数,睡一会醒一会
	int count = interval / 10;
	for (int i = 0; i < count; i++) {
		Sleep(10);
		if (_kbhit()) {//哎呀,被叫醒了
			return;
		}
	}
}
//固化方块(X轴,Y轴,颜色,朝向)
void mark(int x, int y, int color1,_facing  facing) {
	int id= color1 * SQUARE_CHANGE + facing;
	int x0 = (x- XJX_QS_X-1)/ UNIT_SIZE;
	int y0 = (y - 24) / UNIT_SIZE;

	for (int i = 0; i < SQUARE_HIGH; i++) {
		for (int j = 0; j < SQUARE_WIDE; j++) {
			if (square[id][i][j] == 1) {
				Game_area[y0+i][x0+j] = 1;
				color0[y0 + i][x0 + j] = Color[color1];
			}
		}
	}
}


//方块移动
void Square_movement() {
	int X = J_SQUARE_X, Y = J_SQUARE_Y; int curSpeed =speed;
	_facing  facing= _KEY_UP;
	int tj = 0;
	//检测游戏是否结束
	Check_whether_the_game_is_over();
	while (1) {//持续向下下降
		
		Clear_square(X,Y,facing);//清除当前方块
		if (_kbhit()) {//UP, DOWN, LEFT, RIGHT, SPACE.//检测键盘键入
			char key = _getch();//读一个字符(ASCII码),字符的排序整数赋值给key
			if (key == KEY_SPACE) {
				_getch();//如果用户没操作就会停在这里
			}else if (key == KEY_UP) {//上
				//方向 facing0=(强转换类型)((facing + 1) % 4);
				_facing  facing0 = (_facing)((facing + 1) % 4);
				if (Can_it_be_deformed(X, Y+ UNIT_SIZE, facing0)) {
					facing = facing0;//可以旋转赋值
				}
			}
			else if (key == KEY_DOWN) {//下
				tj++;
				tj%2 == 1 ? tj = 1,curSpeed = 50 : curSpeed = speed;
			}
			else if (key == KEY_LEFT) {//左
				if (moveable(X, Y+UNIT_SIZE/ LANDING_SPEED, _move_LEFT, facing) == 1) { X -= UNIT_SIZE; }
			}
			else if (key == KEY_RIGHT) {//右
				if (moveable(X, Y+UNIT_SIZE/ LANDING_SPEED, _move_RIGHT, facing) == 1) { X += UNIT_SIZE; }
			}
		}
		Y = UNIT_SIZE/ LANDING_SPEED +Y;
		drawing_box(X, Y, J_NewSquare, facing);
		//方块的"固化"处理
		if (moveable(X, Y, _move_DOWN, facing) == 0) {
			mark(X, Y, J_NewSquare,facing);
			break;
		}
		wait(curSpeed);//Sleep();这样会卡顿
	}
}

//游戏区生成掉落方块,并固定
void Drop_Square() {
	J_NewSquare = NewSquare;//确定下降方块的种类
	drawing_box(J_SQUARE_X, J_SQUARE_Y, J_NewSquare);//画一个刚从顶部下降的方块
	Sleep(100);//让用户看看
	new_square();//右上角产生新方块
	Sleep(1000);
	//方块移动
	Square_movement();
}

//消除满行格子,并下降.i是传过来的空行,a[]是传来需消除的行数
void Eliminate0(int y) {
	for(int i=y;i>0;i--){//将上面的数全往下移
		for (int x = 0; x < YXQZGZS_X; x++) {//把上一行画下来
			if (Game_area[i - 1][x]) {//检测上上一行是否有格子
				Game_area[i][x] = 1;//如果上行有格子,那么格子掉下来
				color0[i][x] = color0[i - 1][x];//把上一行格子颜色赋值到此行
				setfillcolor(color0[i][x]);//设置填充颜色
				//画一个有边框矩形,有颜色的
				fillrectangle((XJX_QS_X + 1) + x * UNIT_SIZE, 24 + i * UNIT_SIZE,
					(XJX_QS_X + 1) + x * UNIT_SIZE + UNIT_SIZE, 24 + i * UNIT_SIZE + UNIT_SIZE);
			}
			else {
				Game_area[i][x] = 0;
				setfillcolor(RGB(153, 217, 234));//设置填充颜色
				//画一个无边框矩形,有颜色的
				bar((XJX_QS_X + 1) + x * UNIT_SIZE, 24 + i * UNIT_SIZE,
					(XJX_QS_X + 1) + x * UNIT_SIZE + UNIT_SIZE, 24 + i * UNIT_SIZE + UNIT_SIZE);
			}
		}
	}
}

//更新分数和等级
void gxfsgxdj(int fs, int dj) {
	//int score = 0;//总分数
	//int grade = 0;//等级
	//写入分数,等级,操作说明等文本
	setbkcolor(RGB(153, 217, 234));//设置(背景画)背景色为很蓝色
	char str[STRSIZE];//转换字符串需用的数组
	settextstyle(42, 0, _T("微软雅黑"));
	setcolor(RGB(62, 72, 204));//设置颜色
	sprintf_s(str, "%d", fs);//将整型转换为字符串
	for (int i = 0, j = 0; i < STRSIZE; i++) {//在屏幕输出分数
		if (str[i] == '\0')break;
		if (fs > 99999999 && i == 8) {
			outtextxy(358 + i * 17, 166, '\n');
			outtextxy(358 + j * 17, 166 + 40, str[i]);
			j++;
		}
		else {
			outtextxy(358 + i * 17, 166, str[i]);//将分数输入到此处
		}
	}
	
	sprintf_s(str, "%d", dj);//将整型转换为字符串
	for (int i = 0; i < STRSIZE; i++) {//输出等级
		if (str[i] == '\0')break;
		outtextxy(358 + i * 17, 291, str[i]);//将等级输入到此处
	}
	// 更新速度, 等级越高，速度越快，speed越小！
	// 最慢：500， 最快是100
	speed = 500 - dj * 100;
	if (speed <= 100) {
		speed = 100;
	}
}

//消除满行格子,并更新分数及等级
void Eliminate() {
	int j=0;
	int i = YXQZGZS_Y-1;
	for (i ;i >= 0; i--) {
		for (j= 0; j < YXQZGZS_X && Game_area[i][j]; j++) {
		/*
		//执行到此处

		//i行满,没有空位,此时j>=YXQZGZS_X,
		//如果j < 15(真) && Game_area[i][j]==1(真),为真就会遍历下去

		//i行没满,有空位,此时j<YXQZGZS_X
		//如果j >= 15(假) || Game_area[i][j]==0(假),循环条件为假,就会break;
		*/
		}
		if (j >= YXQZGZS_X) {
			//下降
			Eliminate0(i);
			score += 10;//满一行,分数就加10
			grade = score / 50;
			i++;
		}
	}
	gxfsgxdj(score, grade);
}

