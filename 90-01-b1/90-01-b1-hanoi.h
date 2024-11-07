/* 2352018 ������ ���� */
#pragma once

/* ------------------------------------------------------------------------------------------------------

	 ���ļ����ܣ�
	1��Ϊ�˱�֤ hanoi_main.cpp/hanoi_menu.cpp/hanoi_multiple_solutions.cpp ���໥���ʺ����ĺ�������
	2��һ�����ϵ�cpp���õ��ĺ궨�壨#define����ȫ��ֻ����const����������������
	3�����Բο� cmd_console_tools.h ��д���������Ķ�����ᣩ


   ------------------------------------------------------------------------------------------------------ */
#define LOC_X_A 11
#define LOC_X_B 21
#define LOC_X_C 31
#define LOC_Y_4 14
#define LOC_Y_8 34
#define LOC_ROW_X 0
#define LOC_ROW_Y 19
#define LOC_COLUMN 10
#define LOC_LINE_X 10
#define LOC_LINE_Y 13
#define LOC_ENTER_X 0
#define LOC_ENTER_Y 30
#define BOTTOM_WIDTH 23
#define BOTTOM_X 1
#define BOTTOM_Y 15
#define STICK_WIDTH 1
#define LOC_TOWER 32
#define TIME_SLEEP 45
#define X_9 60
#define Y_9 35
#define MAX_9 20



//��������
void my_speed();   //�����ƶ��ٶ�,�������趨��speed��ֵ
void my_input(int& storey, char& src, char& dst, char& tmp);   //���벢�����������
int hanoi_all(int choice);   //����������ŵ�����������
char hanoi_move(int n, char src, char tmp, char dst);
void hanoi(int n, char src, char tmp, char dst, int choice);   //��ŵ���ݹ麯��

//���ܺ���
void print();   //��ӡ����
void printTower1(int tower[], char label);   //��ӡ�����һ��
void printTower2(int tower[], char label);   //��ӡ����ڶ���
void printTower3(int tower[], char label);   //��ӡ���������
void move(char src, char dst);   //�ƶ�����
void moveA(char dst);   //�ƶ�����A
void moveB(char dst);   //�ƶ�����B
void moveC(char dst);   //�ƶ�����C
void move_plate(char src, char dst);   //�ƶ�����
void print_line(int n, char src, char tmp, char dst, int choice);   //�����������
void print_row(int n, char src, char tmp, char dst, int choice);   //�����������
void print_column_base(int choice);   //�����������Ļ����ṹ
void print_column_tower(int choice);   //������������е���
void init(int n, int src, int choice);   //��ʼ��
int init_plate_height(char src);   //��ʼ�����Ӹ߶�
int init_plate_width(char src);   //��ʼ�����ӿ��
int init_plate_color(char src);   //��ʼ��������ɫ
int init_plate_dst(char dst);   //��ʼ��Ŀ����
void getInput(char(&input)[MAX_9]);

//��������
void draw_tower(int n, int src, int choice);   //��ӡ���������Ӻ���
void draw_move(char src, char x, int i);   //���ƶ�ʱ�ĸ�������1
void drawCharacter(int x, int y, int flag, int color, int width);   //���ƶ�ʱ�ĸ�������2
char capital(char x);   //ת��д
void my_sleep();   //����ʱ��
void blank();