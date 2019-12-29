#pragma once 

#include <stdio.h>
#include <Windows.h>
#include <string>
#include <graphics.h>//EasyXͼ�ο�ͷ�ļ�
#include <time.h>
#include <conio.h>//���̿���,kbhit(���¼��̷���1)

using namespace std;

//����С���ε���ֵ
#define XJX_QS_X  30  //��Ϸ��С����X����ʼ��
#define XJX_QS_Y  15  //��Ϸ��С����Y����ʼ��
#define XJX_ZZ_X  353 //��Ϸ��С����X����ֵ��
#define XJX_ZZ_Y  585 //��Ϸ��С����Y����ֵ��

#define DJX_QS_X  28  //��Ϸ�������X����ʼ��
#define DJX_QS_Y  13  //��Ϸ�������Y����ʼ��
#define DJX_ZZ_X  355 //��Ϸ�������X����ֵ��
#define DJX_ZZ_Y  587 //��Ϸ�������Y����ֵ��

#define LANDING_SPEED 2 //1Ϊ����ÿ���½�Ϊ1��,2Ϊ�½�Ϊ0.5��
#define STRSIZE 16
#define SQUARE_SPECIES 5  //��������
#define SQUARE_CHANGE  4  //����ı仯
#define SQUARE_HIGH    5  //����߶�,��,Y���ٸ�
#define SQUARE_WIDE    5  //������,��,X���ٸ�
#define UNIT_SIZE   16  //���鵥Ԫ�Ĵ�С
#define RIGHT_SQUARE_X     392  //���Ͻ���һ�鷽��������ʼX=392
#define RIGHT_SQUARE_Y      36  //���Ͻ���һ�鷽��������ʼY=36
#define J_SQUARE_X    143//���䷽�����ʼX:112,���㷽ʽ:
#define J_SQUARE_Y    8//���䷽�����ʼY,���㷽ʽ:XJX_QS_Y-UNIT_SIZE-9
#define YXQZGZS_X   20//��Ϸ��X���ܸ�����,���㷽ʽ:(XJX_ZZ_X-XJX_QS_X)/UNIT_SIZE
#define YXQZGZS_Y	35//��Ϸ��Y���ܸ�����,���㷽ʽ:(XJX_ZZ_Y-XJX_QS_Y)/UNIT_SIZE
int Game_area[YXQZGZS_Y][YXQZGZS_X];//��Ϸ���ʹ�ö�ά�����ʾ

int color0[YXQZGZS_Y][YXQZGZS_X] ;//��ʾ��Ϸ�������Ӧ����ɫ

//UP, DOWN, LEFT, RIGHT, SPACE.
#define KEY_UP      72  //�ϰ�����72
#define KEY_DOWN    80  //�°�����80
#define KEY_LEFT    75	//�󰴼���75
#define KEY_RIGHT   77	//�Ұ�����77
#define KEY_SPACE   32	//�ո񰴼���32

int score = 0;//�ܷ���
int grade = 0;//�ȼ�
int NewSquare = -1;//��һ�鷽������
int J_NewSquare = -1;//��ǰ�½���������
int speed = 500;

typedef long long int_64;

typedef enum _Square_facing _facing;//���鳯��
enum _Square_facing {//����ĳ���,����ı仯
	_KEY_UP,	//��
	_KEY_DOWN,	//��
	_KEY_LEFT,	//��
	_KEY_RIGHT	//��
};
typedef enum {//������ƶ�
	_move_DOWN,  //��
	_move_LEFT,	 //��
	_move_RIGHT	 //��
}_move;


//��ӭ����
void Welcome_interface() {//ȫ������
	//����һ��������Ŀ���̨����(������)
	initgraph(500, 600);//Ĭ�Ϻ�����(������)
	
	//���ô��ڱ���
	HWND windows= GetHWnd();//��õ�ǰ����,HWND������,windows�Ǳ������մ��ھ����
	SetWindowText(windows, _T("����˹����   ����:��ΰ��"));//���ô����ı�����

	//�����ı�������ʽ
	settextstyle(40, 0,_T( "΢���ź�"));
	setcolor(GREEN);//������ɫ(��ɫ)
	outtextxy(90,200,_T("����˹���� ����:��ΰ��"));
	outtextxy(90, 300, _T("��̴Ӷ���˹���鿪ʼ"));
	setbkcolor(RGB(153, 217, 234));//����(������)����ɫΪ����ɫ
	Sleep(3000);//����(��ͣ)����
}

//��ʼ����Ϸ��������
void Game_background() {
	cleardevice();//�����Ļ,����������
	
	//д�����,�ȼ�,����˵�����ı�
	char str[STRSIZE];//ת���ַ������õ�����
	settextstyle(42, 0, _T("΢���ź�"));
	setcolor(RGB(62, 72, 204));//������ɫ
	outtextxy(358, 126, _T("����:"));
	sprintf_s(str, "%d", score);//������ת��Ϊ�ַ���
	for (int i = 0, j = 0; i < STRSIZE; i++) {//����Ļ�������
		if (str[i] == '\0')break;
		if (score > 99999999 && i == 8) {
			outtextxy(358 + i * 17, 166, '\n');
			outtextxy(358 + j * 17, 166 + 40, str[i]);
			j++;
		}
		else {
			outtextxy(358 + i * 17, 166, str[i]);//���������뵽�˴�
		}
	}
	outtextxy(358, 251, _T("�ȼ�:"));
	sprintf_s(str, "%d", grade);//������ת��Ϊ�ַ���
	for (int i = 0; i < STRSIZE; i++) {//����ȼ�
		if (str[i] == '\0')break;
		outtextxy(358 + i * 17, 291, str[i]);//���ȼ����뵽�˴�
	}
	outtextxy(358, 338, _T("����˵��:"));
	outtextxy(365, 377, _T(" �� :��ת"));
	outtextxy(365, 418, _T(" �� :����"));
	outtextxy(350, 458, _T("  ��:����"));
	outtextxy(350, 498, _T("  ��:����"));
	outtextxy(355, 538, _T("�ո�:��ͣ"));
	
	//����Ϸ��������̨
	setcolor(RGB(250,18,33));//������ɫ(��ɫ)
	rectangle(DJX_QS_X, DJX_QS_Y, DJX_ZZ_X, DJX_ZZ_Y);//�������
	rectangle(XJX_QS_X, XJX_QS_Y, XJX_ZZ_X, XJX_ZZ_Y);//��С����
	setfillcolor(RGB(250, 18, 33));//���������ɫ
	floodfill(XJX_QS_X-1, XJX_QS_Y-1, RGB(250, 18, 33));//�������������һ����,����RED(�Լ�����)��ɫֹͣ
	
	//����һ�����ͼ����
	setcolor(RGB(255, 245, 0));//���û�����ɫ()
	rectangle(373, 16, 483, 118);//�������
	setbkcolor(RGB(255, 255, 255));//���ô����ڿ�ʼ������ı���ɫ,�����ٴ�����
	setfillcolor(RGB(255, 255, 255));//���������ɫ
	floodfill(386, 47, RGB(255, 245, 0));//�������������һ����,����(�Լ�����)��ɫֹͣ
	settextstyle(20, 0, _T("΢���ź�"));//��������
	setcolor(RGB(250, 18, 33));//������ɫ
	outtextxy(377, 17, _T("��һ��:"));//д���ı�
	setcolor(RGB(255, 245, 0));//���û�����ɫ
	rectangle(375, 18, 481, 116);//��С����
	setfillcolor(RGB(255, 245, 0));//���������ɫ
	floodfill(374, 17, RGB(255, 245, 0));//�������������һ����,����RED(�Լ�����)��ɫֹͣ
}

//����ı�ʾ,0-3=I,4-7=L,8-11=T,12-15=N,16-19��
int square[SQUARE_SPECIES * SQUARE_CHANGE][SQUARE_HIGH][SQUARE_WIDE] = {
	//I�ͷ����������̬
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

	  //L�ͷ����������̬
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

	  //�A�͵�������̬
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

	  //N�͵�������̬
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

  //���ε�������̬
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

	int Color[SQUARE_SPECIES] = {//��ɫ����
	GREEN,YELLOW,RED,BLUE,BROWN
	};


	//�������//������ʼ��:X,Y,���鳯��
	void Clear_square(int_64 X,int_64 Y, _facing facing) {
		int id = J_NewSquare * SQUARE_CHANGE + facing;
		setfillcolor(RGB(153, 217, 234));
		for (int_64 i = 0; i < SQUARE_HIGH; i++) {
			for (int_64 j = 0; j < SQUARE_WIDE; j++) {
				if (square[id][i][j] == 1) {
					int_64 x = X + j * UNIT_SIZE;
					int_64 y = Y + i * UNIT_SIZE;
					bar(x, y,x + UNIT_SIZE, y + UNIT_SIZE);//��һ���ޱ߿����,����ɫ��
				}
			}
		}
	}

//���Ʒ���
void drawing_box(int_64 X,int_64 Y,int rgb) {
	setbkcolor(RGB(255, 255,255));//����(������)����ɫΪ����ɫ
	setcolor(RGB(255, 245, 0));
	setfillcolor(Color[rgb]);//���������ɫ,�����ֵ����
	for (int_64 i = 0; i < SQUARE_HIGH; i++) {
		for (int_64 j = 0; j < SQUARE_WIDE; j++) {
			if(square[rgb * SQUARE_CHANGE][i][j]==1){
				fillrectangle(X + j * UNIT_SIZE, Y + i * UNIT_SIZE,//��һ���б߿����,����ɫ��
					X + j * UNIT_SIZE + UNIT_SIZE, Y + i * UNIT_SIZE + UNIT_SIZE);

			//setfillcolor(BLACK);//���������ɫ NewSquare
			//bar(SQUARE_X + j * UNIT_SIZE, SQUARE_Y + i * UNIT_SIZE,//��һ���ޱ߿����,����ɫ��
				//SQUARE_X + j * UNIT_SIZE + UNIT_SIZE, SQUARE_Y + i * UNIT_SIZE + UNIT_SIZE);
			}
		}
	}
}
void drawing_box(int_64 X, int_64 Y, int rgb, _facing facing) {
	setbkcolor(RGB(255, 255, 255));//����(������)����ɫΪ����ɫ
	setcolor(RGB(255, 245, 0));
	int id = J_NewSquare * SQUARE_CHANGE + facing;
	setfillcolor(Color[rgb]);//���������ɫ,�����ֵ����
	for (int_64 i = 0; i < SQUARE_HIGH; i++) {
		for (int_64 j = 0; j < SQUARE_WIDE; j++) {
			if (square[id][i][j] == 1) {
				fillrectangle(X + j * UNIT_SIZE, Y + i * UNIT_SIZE,//��һ���б߿����,����ɫ��
					X + j * UNIT_SIZE + UNIT_SIZE, Y + i * UNIT_SIZE + UNIT_SIZE);

				//setfillcolor(BLACK);//���������ɫ NewSquare
				//bar(SQUARE_X + j * UNIT_SIZE, SQUARE_Y + i * UNIT_SIZE,//��һ���ޱ߿����,����ɫ��
					//SQUARE_X + j * UNIT_SIZE + UNIT_SIZE, SQUARE_Y + i * UNIT_SIZE + UNIT_SIZE);
			}
		}
	}
}


//���Ͻ��·���Ĳ���
void new_square() {
	//��շ�������,���Ͻǵľ�������,���������򱳾�ɫ,����ɷ���
	clearrectangle(RIGHT_SQUARE_X, RIGHT_SQUARE_Y, RIGHT_SQUARE_X + UNIT_SIZE * SQUARE_WIDE, RIGHT_SQUARE_Y + UNIT_SIZE * SQUARE_HIGH);

	//���ѡ��һ�ַ���
	srand(time(NULL));//srand�����,����������ӵ�;(�����޷�������ʱ��(time)(ʲôʱ��ʼ))
	NewSquare = rand() % SQUARE_SPECIES;//ȡ�����޶�5,rand()ȡ�������,0-4�����ֵ
	drawing_box(RIGHT_SQUARE_X, RIGHT_SQUARE_Y, NewSquare);//������
}


//�ܷ��ƶ�
int moveable(int x,int y, _move moveb,_facing facing) {
	//���㵱ǰ���������Ͻ�����Ϸ����39*23�ڶ����е�,�ڶ����е�λ��
	//��ʼλ�õ���ʼ����λ��
	int moveX = (x - XJX_QS_X-1) / UNIT_SIZE; //���㷽��λ����һ�����
	//��Ϊ������ʼλ�����Զ����-1����,Ϊ�˲���������ʧ����,����:
	int moveY= ((y- J_SQUARE_Y) -(XJX_QS_Y+1)) / UNIT_SIZE;
	int shape = J_NewSquare * SQUARE_CHANGE + facing;//ȷ�Ϸ����λ��,����ڼ�����ά����
	int ret = 1;//����

	//�����ָ��λ�ÿ����ƶ�
	if (moveb == _move_DOWN) {
		//�ж��Ƿ�ʵ��
		for (int i = 0; i < SQUARE_HIGH; i++) {
			for (int j = 0; j < SQUARE_WIDE; j++) {
		//�Ƿ�ʵ��&&(ʵ�Ŀ�+i+1û������Ϸ��Y���ܸ�����||(����ʵ�ĸ���==1))
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

//�����Ϸ�Ƿ����
void Check_whether_the_game_is_over() {
	if (moveable(J_SQUARE_X, J_SQUARE_Y, _move_DOWN, _KEY_UP)==0) {
		setcolor(BLACK);//������ɫ
		settextstyle(42, 0, _T("΢���ź�"));
		outtextxy(120, 275, _T("��ʧ����."));
		Sleep(1000);//����1��
		system("pause");//��ͣ
		closegraph();//�ر�ͼ�ο�
		exit(0);//�������
	}
}

//�ܷ����,�жϵ�ǰ�����Ƿ����ת��δ��ָ������
int Can_it_be_deformed(int x,int y, _facing  facing0) {
	int shape= J_NewSquare * SQUARE_CHANGE + facing0;//ȷ�Ϸ����λ��

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

void wait(int interval) {//˯�ߺ���,˯һ����һ��
	int count = interval / 10;
	for (int i = 0; i < count; i++) {
		Sleep(10);
		if (_kbhit()) {//��ѽ,��������
			return;
		}
	}
}
//�̻�����(X��,Y��,��ɫ,����)
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


//�����ƶ�
void Square_movement() {
	int X = J_SQUARE_X, Y = J_SQUARE_Y; int curSpeed =speed;
	_facing  facing= _KEY_UP;
	int tj = 0;
	//�����Ϸ�Ƿ����
	Check_whether_the_game_is_over();
	while (1) {//���������½�
		
		Clear_square(X,Y,facing);//�����ǰ����
		if (_kbhit()) {//UP, DOWN, LEFT, RIGHT, SPACE.//�����̼���
			char key = _getch();//��һ���ַ�(ASCII��),�ַ�������������ֵ��key
			if (key == KEY_SPACE) {
				_getch();//����û�û�����ͻ�ͣ������
			}else if (key == KEY_UP) {//��
				//���� facing0=(ǿת������)((facing + 1) % 4);
				_facing  facing0 = (_facing)((facing + 1) % 4);
				if (Can_it_be_deformed(X, Y+ UNIT_SIZE, facing0)) {
					facing = facing0;//������ת��ֵ
				}
			}
			else if (key == KEY_DOWN) {//��
				tj++;
				tj%2 == 1 ? tj = 1,curSpeed = 50 : curSpeed = speed;
			}
			else if (key == KEY_LEFT) {//��
				if (moveable(X, Y+UNIT_SIZE/ LANDING_SPEED, _move_LEFT, facing) == 1) { X -= UNIT_SIZE; }
			}
			else if (key == KEY_RIGHT) {//��
				if (moveable(X, Y+UNIT_SIZE/ LANDING_SPEED, _move_RIGHT, facing) == 1) { X += UNIT_SIZE; }
			}
		}
		Y = UNIT_SIZE/ LANDING_SPEED +Y;
		drawing_box(X, Y, J_NewSquare, facing);
		//�����"�̻�"����
		if (moveable(X, Y, _move_DOWN, facing) == 0) {
			mark(X, Y, J_NewSquare,facing);
			break;
		}
		wait(curSpeed);//Sleep();�����Ῠ��
	}
}

//��Ϸ�����ɵ��䷽��,���̶�
void Drop_Square() {
	J_NewSquare = NewSquare;//ȷ���½����������
	drawing_box(J_SQUARE_X, J_SQUARE_Y, J_NewSquare);//��һ���մӶ����½��ķ���
	Sleep(100);//���û�����
	new_square();//���Ͻǲ����·���
	Sleep(1000);
	//�����ƶ�
	Square_movement();
}

//�������и���,���½�.i�Ǵ������Ŀ���,a[]�Ǵ���������������
void Eliminate0(int y) {
	for(int i=y;i>0;i--){//���������ȫ������
		for (int x = 0; x < YXQZGZS_X; x++) {//����һ�л�����
			if (Game_area[i - 1][x]) {//�������һ���Ƿ��и���
				Game_area[i][x] = 1;//��������и���,��ô���ӵ�����
				color0[i][x] = color0[i - 1][x];//����һ�и�����ɫ��ֵ������
				setfillcolor(color0[i][x]);//���������ɫ
				//��һ���б߿����,����ɫ��
				fillrectangle((XJX_QS_X + 1) + x * UNIT_SIZE, 24 + i * UNIT_SIZE,
					(XJX_QS_X + 1) + x * UNIT_SIZE + UNIT_SIZE, 24 + i * UNIT_SIZE + UNIT_SIZE);
			}
			else {
				Game_area[i][x] = 0;
				setfillcolor(RGB(153, 217, 234));//���������ɫ
				//��һ���ޱ߿����,����ɫ��
				bar((XJX_QS_X + 1) + x * UNIT_SIZE, 24 + i * UNIT_SIZE,
					(XJX_QS_X + 1) + x * UNIT_SIZE + UNIT_SIZE, 24 + i * UNIT_SIZE + UNIT_SIZE);
			}
		}
	}
}

//���·����͵ȼ�
void gxfsgxdj(int fs, int dj) {
	//int score = 0;//�ܷ���
	//int grade = 0;//�ȼ�
	//д�����,�ȼ�,����˵�����ı�
	setbkcolor(RGB(153, 217, 234));//����(������)����ɫΪ����ɫ
	char str[STRSIZE];//ת���ַ������õ�����
	settextstyle(42, 0, _T("΢���ź�"));
	setcolor(RGB(62, 72, 204));//������ɫ
	sprintf_s(str, "%d", fs);//������ת��Ϊ�ַ���
	for (int i = 0, j = 0; i < STRSIZE; i++) {//����Ļ�������
		if (str[i] == '\0')break;
		if (fs > 99999999 && i == 8) {
			outtextxy(358 + i * 17, 166, '\n');
			outtextxy(358 + j * 17, 166 + 40, str[i]);
			j++;
		}
		else {
			outtextxy(358 + i * 17, 166, str[i]);//���������뵽�˴�
		}
	}
	
	sprintf_s(str, "%d", dj);//������ת��Ϊ�ַ���
	for (int i = 0; i < STRSIZE; i++) {//����ȼ�
		if (str[i] == '\0')break;
		outtextxy(358 + i * 17, 291, str[i]);//���ȼ����뵽�˴�
	}
	// �����ٶ�, �ȼ�Խ�ߣ��ٶ�Խ�죬speedԽС��
	// ������500�� �����100
	speed = 500 - dj * 100;
	if (speed <= 100) {
		speed = 100;
	}
}

//�������и���,�����·������ȼ�
void Eliminate() {
	int j=0;
	int i = YXQZGZS_Y-1;
	for (i ;i >= 0; i--) {
		for (j= 0; j < YXQZGZS_X && Game_area[i][j]; j++) {
		/*
		//ִ�е��˴�

		//i����,û�п�λ,��ʱj>=YXQZGZS_X,
		//���j < 15(��) && Game_area[i][j]==1(��),Ϊ��ͻ������ȥ

		//i��û��,�п�λ,��ʱj<YXQZGZS_X
		//���j >= 15(��) || Game_area[i][j]==0(��),ѭ������Ϊ��,�ͻ�break;
		*/
		}
		if (j >= YXQZGZS_X) {
			//�½�
			Eliminate0(i);
			score += 10;//��һ��,�����ͼ�10
			grade = score / 50;
			i++;
		}
	}
	gxfsgxdj(score, grade);
}

