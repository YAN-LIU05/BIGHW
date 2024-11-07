/* 2352018 ������ ���� */
#include <iostream>
#include <iomanip>
#include <windows.h>
#include <conio.h>
#include "../include/cmd_console_tools.h"
#include "../include/bighw.h"
#include "90-01-b1-hanoi.h"
using namespace std;

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

/* ----------------------------------------------------------------------------------

     ���ļ����ܣ�
    1����ű� hanoi_main.cpp �и��ݲ˵�����ֵ���õĸ��˵����Ӧ��ִ�к���

     ���ļ�Ҫ��
    1�����������ⲿȫ�ֱ�����const��#define�������Ʒ�Χ�ڣ�
    2�������徲̬ȫ�ֱ�����������Ҫ��������Ҫ�����ĵ���ʾ��ȫ�ֱ�����ʹ��׼���ǣ����á����á��ܲ��þ������ã�
    3����̬�ֲ����������������ƣ���ʹ��׼��Ҳ�ǣ����á����á��ܲ��þ�������
    4���������ϵͳͷ�ļ����Զ���ͷ�ļ��������ռ��

   ----------------------------------------------------------------------------------- */
int hanoi0[3][10];
int top[3];
int Count = 0;// �ƶ�����������
int speed;

/***************************************************************************
  �������ƣ�capital
  ��    �ܣ�ת��д
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
char capital(char x)
{
    if (x == 'a' || x == 'A')
        x = 'A';
    if (x == 'B' || x == 'b')
        x = 'B';
    if (x == 'c' || x == 'C')
        x = 'C';
    return x;
}

/***************************************************************************
  �������ƣ�my_sleep
  ��    �ܣ�����ʱ��
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void my_sleep()
{
    switch (speed)
    {
        case 1:
            Sleep(50);
            break;
        case 2:
            Sleep(40);
            break;
        case 3:
            Sleep(30);
            break;
        case 4:
            Sleep(20);
            break;
        case 5:
            Sleep(10);
            break;
    }
}

/***************************************************************************
  �������ƣ�draw_tower
  ��    �ܣ���ӡ���������Ӻ���
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void draw_tower(int n, int src, int choice)
{
    int i, j, k, m;
    int bottom, stick;   //��ӡ����������
    int color1, color2;   //�̺ͱ�������ɫ
    int startX, startY;   //��ӡ�̵�λ��
    for (i = 0; i < 3; i++)   //��ӡ����
    {
        bottom = BOTTOM_X + LOC_TOWER * i;
        Sleep(TIME_SLEEP);
        cct_showstr(bottom, BOTTOM_Y, " ", COLOR_HYELLOW, COLOR_HYELLOW, BOTTOM_WIDTH);
    }

    for (j = 14; j > 1; j--)   //��ӡ����
    {
        for (k = 0; k < 3; k++)
        {
            stick = BOTTOM_Y + LOC_TOWER * k - BOTTOM_X - 2;
            Sleep(45);
            cct_showch(stick, j + 1, ' ', COLOR_HYELLOW, COLOR_HYELLOW, STICK_WIDTH);
        }
    }
    // ���ı���ɫ����Ϊ��ɫ��������ɫ����Ϊ��ɫ
    cct_setcolor(COLOR_BLACK, COLOR_WHITE);

    if (choice == 6 || choice == 7 || choice == 8 || choice == 9)
    {
        int num = src - 'A';

        // ѭ�����ƶ�̬����
        for (m = n; m >= 1; m--)
        {
            Sleep(TIME_SLEEP);

            // ���㵱ǰ��������ɫֵ
            color1 = COLOR_BLUE + m;
            color2 = COLOR_BLUE + m;

            // ���㵱ǰ������λ��
            startX = LOC_LINE_X + LOC_TOWER * num - m + 2;
            startY = LOC_LINE_Y - n + m + 1;
            cct_showch(startX, startY, ' ', color1, color2, 1 + 2 * m);
        }
        // ���ı���ɫ����Ϊ��ɫ��������ɫ����Ϊ��ɫ
        cct_setcolor(COLOR_BLACK, COLOR_WHITE);
    }
}

/***************************************************************************
  �������ƣ�draw_move
  ��    �ܣ����ƶ�ʱ�ĸ�������1
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void draw_move(char src, char x, int i)
{
    int height = init_plate_height(src);
    int width = init_plate_width(src);
    int loc_x = (x - 'A') * LOC_TOWER + (BOTTOM_WIDTH + BOTTOM_X - width + 1) / 2;
    int color = init_plate_color(src);

    cct_showch((x - 'A') * LOC_TOWER + 1, i, ' ', COLOR_BLACK, COLOR_WHITE, BOTTOM_WIDTH);
    if (i > 2 && i < 15)   //��ӡ��
        cct_showch((x - 'A') * LOC_TOWER + (BOTTOM_WIDTH + BOTTOM_X) / 2, i, ' ', COLOR_HYELLOW, COLOR_HYELLOW, STICK_WIDTH);
    //����Ļ�ϵ��ض�λ�û���һ����
    cct_showch(loc_x, i + 1, ' ', COLOR_BLACK + color, COLOR_BLACK + color, width);
    height = i - 1;
}

/***************************************************************************
  �������ƣ�drawCharacter
  ��    �ܣ����ƶ�ʱ�ĸ�������2
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void drawCharacter(int x, int y, int flag, int color, int width)
{
    cct_showch(x, y, ' ', COLOR_BLACK, COLOR_WHITE, width);

    // ����ˮƽ�����ֵ����������ɫ�ַ���λ��
    int offset = (flag > 0) ? 1 : -1;
    int color0 = COLOR_BLACK + color;

    // ���ƾ����ض���ɫ���ַ�
    cct_showch(x + offset, y, ' ', color0, color0, width);
}


/***************************************************************************
  �������ƣ�printTower1
  ��    �ܣ���ӡ�����һ��
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void printTower1(int tower[], char label)
{
    cout << label << ":";
    for (int i = 0; i < 10; ++i)
    {
        if (hanoi0[0][i] == 0)
        {
            cout << "  "; // �����ո��ʾû����
        }
        else
        {
            cout << setw(2) << tower[i];
        }
    }
    cout << " ";
}

/***************************************************************************
  �������ƣ�printTower2
  ��    �ܣ���ӡ����ڶ���
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void printTower2(int tower[], char label)
{
    cout << label << ":";
    for (int i = 0; i < 10; ++i)
    {
        if (hanoi0[1][i] == 0)
        {
            cout << "  "; // �����ո��ʾû����
        }
        else
        {
            cout << setw(2) << tower[i];
        }
    }
    cout << " ";
}

/***************************************************************************
  �������ƣ�printTower3
  ��    �ܣ���ӡ���������
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void printTower3(int tower[], char label)
{
    cout << label << ":";
    for (int i = 0; i < 10; ++i)
    {
        if (hanoi0[2][i] == 0)
        {
            cout << "  "; // �����ո��ʾû����
        }
        else
        {
            cout << setw(2) << tower[i];
        }
    }
    cout << " ";
}

/***************************************************************************
  �������ƣ�print
  ��    �ܣ���ӡ����
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void print()
{
    printTower1(hanoi0[0], 'A');
    printTower2(hanoi0[1], 'B');
    printTower3(hanoi0[2], 'C');
}

/***************************************************************************
  �������ƣ�moveA
  ��    �ܣ��ƶ�����A
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void moveA(char dst)
{
    int a;
    a = hanoi0[0][--top[0]];
    hanoi0[0][top[0]] = 0;
    if (dst == 'B')
    {
        hanoi0[1][top[1]++] = a;
    }
    if (dst == 'C')
    {
        hanoi0[2][top[2]++] = a;
    }
}

/***************************************************************************
  �������ƣ�moveB
  ��    �ܣ��ƶ�����B
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void moveB(char dst)
{
    int b;
    b = hanoi0[1][--top[1]];
    hanoi0[1][top[1]] = 0;
    if (dst == 'A')
    {
        hanoi0[0][top[0]++] = b;
    }
    if (dst == 'C')
    {
        hanoi0[2][top[2]++] = b;
    }
}

/***************************************************************************
  �������ƣ�moveC
  ��    �ܣ��ƶ�����C
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void moveC(char dst)
{
    int c;
    c = hanoi0[2][--top[2]];
    hanoi0[2][top[2]] = 0;
    if (dst == 'A')
    {
        hanoi0[0][top[0]++] = c;
    }
    if (dst == 'B')
    {
        hanoi0[1][top[1]++] = c;
    }
}

/***************************************************************************
  �������ƣ�move
  ��    �ܣ��ƶ�����
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void move(char src, char dst)
{
    if (src == 'A')
        moveA(dst);
    if (src == 'B')
        moveB(dst);
    if (src == 'C')
        moveC(dst);
}

/***************************************************************************
  �������ƣ�move_plate
  ��    �ܣ��ƶ�����
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void move_plate(char src, char dst)
{
    int height = init_plate_height(src);
    int width = init_plate_width(src);
    int loc_x = (src - 'A') * LOC_TOWER + (BOTTOM_WIDTH + BOTTOM_X - width + 1) / 2;
    int color = init_plate_color(src);
    int loc_y = init_plate_dst(dst);
    int flag = (dst - src) * LOC_TOWER;
    int i = height, j = height;
    //������
    for (; i > 1; i--)
    {
        Sleep(TIME_SLEEP);
        cct_showch((src - 'A') * 32 + 1, i, ' ', COLOR_BLACK, COLOR_WHITE, BOTTOM_WIDTH);
        if (i > 2 && i < 15)   //��ӡ��
            cct_showch((src - 'A') * LOC_TOWER + (BOTTOM_WIDTH + BOTTOM_X) / 2, i, ' ', COLOR_HYELLOW, COLOR_HYELLOW, STICK_WIDTH);
        //����Ļ�ϵ��ض�λ�û���һ����
        cct_showch(loc_x, i - 1, ' ', COLOR_BLACK + color, COLOR_BLACK + color, width);
        height = i - 1;
    }
    i = height;
    //ƽ����
    while (1)
    {
        Sleep(TIME_SLEEP);
        cct_showch(loc_x, height, ' ', COLOR_BLACK, COLOR_WHITE, width);
        drawCharacter(loc_x, height, flag, color, width);

        // ����x��λ��
        loc_x += (flag > 0) ? 1 : (flag < 0) ? -1 : 0;

        // ����Ƿ�ﵽֹͣ����
        int locate = flag + (src - 'A') * LOC_TOWER + (BOTTOM_WIDTH + BOTTOM_X - width + 1) / 2;
        if (loc_x == locate)
            break;
    }
    //������
    j = height;
    while (j < loc_y)
    {
        Sleep(TIME_SLEEP);
        draw_move(src, dst, j);
        j++;
    }
    cct_setcolor(COLOR_BLACK, COLOR_WHITE);
}

/***************************************************************************
  �������ƣ�print_all
  ��    �ܣ���ӡ
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void print_all(int n, char src, char tmp, char dst, int choice)
{
    char dst_7 = 0;
    switch (choice)
    {
        case 1:
            print_line(n, src, tmp, dst, 1);
            break;
        case 2:
            print_line(n, src, tmp, dst, 2);
            break;
        case 3:
            print_row(n, src, tmp, dst, 3);
            break;
        case 4:
            switch (speed)
            {
                case 0:
                    if (_getch() == 13)   //���س�������ʾ,�س���ASCII���ֵΪ13
                    {
                        print_row(n, src, tmp, dst, 4);
                        print_column_base(4);
                        print_column_tower(4);
                    }
                    break;
                case 1:
                    Sleep(250);
                    print_row(n, src, tmp, dst, 4);
                    print_column_base(4);
                    print_column_tower(4);
                    break;
                case 2:
                    Sleep(200);
                    print_row(n, src, tmp, dst, 4);
                    print_column_base(4);
                    print_column_tower(4);
                    break;
                case 3:
                    Sleep(150);
                    print_row(n, src, tmp, dst, 4);
                    print_column_base(4);
                    print_column_tower(4);
                    break;
                case 4:
                    Sleep(100);
                    print_row(n, src, tmp, dst, 4);
                    print_column_base(4);
                    print_column_tower(4);
                    break;
                case 5:
                    Sleep(50);
                    print_row(n, src, tmp, dst, 4);
                    print_column_base(4);
                    print_column_tower(4);
                    break;
            }
            break;
        case 7:
            dst_7 = hanoi_move(n, src, tmp, dst);
            move_plate(src, dst_7);
            break;
        case 8:
            switch (speed)
            {
                case 0:
                    if (_getch() == 13)
                    {
                        print_row(n, src, tmp, dst, 8);
                        print_column_base(8);
                        print_column_tower(8);
                        move(dst, src);
                        move_plate(src, dst);
                        move(src, dst);
                    }
                    break;//���س�������ʾ,�س���ASCII���ֵΪ13
                case 1:
                    Sleep(250);
                    print_row(n, src, tmp, dst, 8);
                    print_column_base(8);
                    print_column_tower(8);
                    move(dst, src);
                    move_plate(src, dst);
                    move(src, dst);
                    break;
                case 2:
                    Sleep(200);
                    print_row(n, src, tmp, dst, 8);
                    print_column_base(8);
                    print_column_tower(8);
                    move(dst, src);
                    move_plate(src, dst);
                    move(src, dst);
                    break;
                case 3:
                    Sleep(150);
                    print_row(n, src, tmp, dst, 8);
                    print_column_base(8);
                    print_column_tower(8);
                    move(dst, src);
                    move_plate(src, dst);
                    move(src, dst);
                    break;
                case 4:
                    Sleep(100);
                    print_row(n, src, tmp, dst, 8);
                    print_column_base(8);
                    print_column_tower(8);
                    move(dst, src);
                    move_plate(src, dst);
                    move(src, dst);
                    break;
                case 5:
                    Sleep(50);
                    print_row(n, src, tmp, dst, 8);
                    print_column_base(8);
                    print_column_tower(8);
                    move(dst, src);
                    move_plate(src, dst);
                    move(src, dst);
                    break;
            }
            break;
        case 9:
            print_row(n, src, tmp, dst, 9);
            print_column_base(9);
            print_column_tower(9);
            move(dst, src);
            move_plate(src, dst);
            move(src, dst);
            break;
    }
}

/***************************************************************************
  �������ƣ�print_line
  ��    �ܣ������������
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void print_line(int n, char src, char tmp, char dst, int choice)
{
    switch (choice)
    {
        case 1:
            cout << n << "# " << src << "-->" << dst << endl;
            break;
        case 2:
            cout << "��" << setw(4) << Count << " ��" << "(" << setw(2) << n << "#" << ": " << src << "-->" << dst << ")  " << endl;
            break;
    }
}

/***************************************************************************
  �������ƣ�print_row
  ��    �ܣ������������
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void print_row(int n, char src, char tmp, char dst, int choice)
{
    switch (choice)
    {
        case 3:
            break;
        case 4:
            cct_gotoxy(LOC_ROW_X, LOC_ROW_Y);
            break;
        case 8:
            cct_gotoxy(LOC_ROW_X, LOC_ROW_Y + 18);
            break;
        case 9:
            cct_gotoxy(LOC_ROW_X, LOC_ROW_Y + 14);
            break;
    }
    cout << "��" << setw(4) << Count << " ��" << "(" << setw(2) << n << ")" << ": " << src << "-->" << dst << " ";
    move(src, dst);
    print();
    cout << endl;
}

/***************************************************************************
  �������ƣ�print_column_base
  ��    �ܣ������������Ļ����ṹ
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void print_column_base(int choice)
{
    int i;
    cct_gotoxy(0, 0);
    switch (choice)
    {
        case 4:
            for (i = 0; i < 21; i++)
            {
                cout << endl;
            }
            //��ӡ�����ṹ
            cct_gotoxy(LOC_LINE_X, LOC_LINE_Y);
            for (int j = 0; j < 23; j++)
                cout << "=";
            cct_gotoxy(LOC_X_A, LOC_Y_4);
            cout << "A";
            cct_gotoxy(LOC_X_B, LOC_Y_4);
            cout << "B";
            cct_gotoxy(LOC_X_C, LOC_Y_4);
            cout << "C";
            break;
        case 8:
            for (i = 0; i < 21; i++)
            {
                cout << endl;
            }
            //��ӡ�����ṹ
            cct_gotoxy(LOC_LINE_X, LOC_LINE_Y + 20);
            for (int j = 0; j < 23; j++)
                cout << "=";
            cct_gotoxy(LOC_X_A, LOC_Y_8);
            cout << "A";
            cct_gotoxy(LOC_X_B, LOC_Y_8);
            cout << "B";
            cct_gotoxy(LOC_X_C, LOC_Y_8);
            cout << "C";
            break;
        case 9:
            for (i = 0; i < 21; i++)
            {
                cout << endl;
            }
            //��ӡ�����ṹ
            cct_gotoxy(LOC_LINE_X, LOC_LINE_Y + 15);
            for (int j = 0; j < 23; j++)
                cout << "=";
            cct_gotoxy(LOC_X_A, LOC_Y_8 - 5);
            cout << "A";
            cct_gotoxy(LOC_X_B, LOC_Y_8 - 5);
            cout << "B";
            cct_gotoxy(LOC_X_C, LOC_Y_8 - 5);
            cout << "C";
            break;
    }
}

/***************************************************************************
  �������ƣ�print_column_tower
  ��    �ܣ�������������е���
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void print_column_tower(int choice)
{
    int i, j, h;

    switch (choice)
    {
        case 4:
            for (i = 0; i < 3; i++)
            {
                h = LOC_Y_4 - 2;
                for (j = 0; j < 10; ++j)
                {
                    cct_gotoxy(LOC_COLUMN * (i + 1), h);
                    if (hanoi0[i][j] == 0)
                    {
                        cout << "  "; // �����ո��ʾû����
                    }
                    else
                    {
                        cout << setw(2) << hanoi0[i][j];
                    }
                    h--;
                }
                cout << " ";
            }
            break;
        case 8:
            for (i = 0; i < 3; i++)
            {
                h = LOC_Y_8 - 2;
                for (j = 0; j < 10; ++j)
                {
                    cct_gotoxy(LOC_COLUMN * (i + 1), h);
                    if (hanoi0[i][j] == 0)
                    {
                        cout << "  "; // �����ո��ʾû����
                    }
                    else
                    {
                        cout << setw(2) << hanoi0[i][j];
                    }
                    h--;
                }
                cout << " ";
            }
            break;
        case 9:
            for (i = 0; i < 3; i++)
            {
                h = LOC_Y_8 - 7;
                for (j = 0; j < 10; ++j)
                {
                    cct_gotoxy(LOC_COLUMN * (i + 1), h);
                    if (hanoi0[i][j] == 0)
                    {
                        cout << "  "; // �����ո��ʾû����
                    }
                    else
                    {
                        cout << setw(2) << hanoi0[i][j];
                    }
                    h--;
                }
                cout << " ";
            }
            break;
    }
}

/***************************************************************************
  �������ƣ�init
  ��    �ܣ���ʼ��
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void init(int n, int src, int choice)
{
    int i;
    if (src == 'A')
    {
        for (i = 0; i < n; i++)
        {
            hanoi0[0][i] = n - i;
        }
        top[0] = n;
    }
    if (src == 'B')
    {
        for (i = 0; i < n; i++)
        {
            hanoi0[1][i] = n - i;
        }
        top[1] = n;
    }
    if (src == 'C')
    {
        for (i = 0; i < n; i++)
        {
            hanoi0[2][i] = n - i;
        }
        top[2] = n;
    }
    if (choice == 3 || choice == 4 || choice == 8 || choice == 9)
    {
        cout << "��ʼ:";   // ��ӡ��ʼ״̬
        cout << "                ";
        print();
        cout << endl;
    }
}

/***************************************************************************
  �������ƣ�init_plate_height
  ��    �ܣ���ʼ�����Ӹ߶�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int init_plate_height(char src)
{
    int height, width;
    height = 0;
    width = 0;
    if (src == 'A')
    {
        height = BOTTOM_Y - top[0];
    }
    if (src == 'B')
    {
        height = BOTTOM_Y - top[1];
    }
    if (src == 'C')
    {
        height = BOTTOM_Y - top[2];
    }

    return height;
}

/***************************************************************************
  �������ƣ�init_plate_width
  ��    �ܣ���ʼ�����ӿ��
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int init_plate_width(char src)
{
    int width = 0;
    if (src == 'A')
    {
        width = 2 * hanoi0[0][top[0] - 1] + 1;
    }
    if (src == 'B')
    {
        width = 2 * hanoi0[1][top[1] - 1] + 1;
    }
    if (src == 'C')
    {
        width = 2 * hanoi0[2][top[2] - 1] + 1;
    }

    return width;
}

/***************************************************************************
  �������ƣ�init_plate_color
  ��    �ܣ���ʼ��������ɫ
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int init_plate_color(char src)
{
    int color = 0;
    if (src == 'A')
    {
        color = hanoi0[0][top[0] - 1];
    }
    if (src == 'B')
    {
        color = hanoi0[1][top[1] - 1];
    }
    if (src == 'C')
    {
        color = hanoi0[2][top[2] - 1];
    }

    return color + 1;
}

/***************************************************************************
  �������ƣ�init_plate_dst
  ��    �ܣ���ʼ��Ŀ����
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int init_plate_dst(char dst)
{
    int loc_y = BOTTOM_Y - top[dst - 'A'] - 1;
    return loc_y;
}

/***************************************************************************
  �������ƣ�speed
  ��    �ܣ������ƶ��ٶ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void my_speed()
{
    while (1)
    {
        cout << "�������ƶ��ٶ�(0-5: 0-���س�������ʾ 1-��ʱ� 5-��ʱ���) ";
        cin >> speed;
        if (cin.good() && speed >= 0 && speed <= 5)
            break;
        else
        {
            cin.clear();
            cin.ignore(65536, '\n');
        }
    }
}

/***************************************************************************
  �������ƣ�hanoi_move
  ��    �ܣ�7
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
char hanoi_move(int n, char src, char tmp, char dst)
{
    char src0 = src;
    char dst0 = dst;
    char tmp0 = tmp;
    int n0 = n;
    // �ƶ� n-1 �����Ӵ�Դ�����м���
    while (n0 > 1)
    {
        src0 = tmp0;
        tmp0 = dst0;
        dst0 = src0;
        n0 -= 1;
    }
    // �����һ�����Ӵ�Դ���ƶ���Ŀ����
    char result = dst0;

    return result;
}

/***************************************************************************
  �������ƣ�my_input
  ��    �ܣ����벢�����������
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void my_input(int& storey, char& src, char& dst, char& tmp)
{
    cout << endl;
    while (1)
    {
        cout << "�����뺺ŵ���Ĳ���(1-10)" << endl;
        cin >> storey;
        if (cin.good() && storey >= 1 && storey <= 10)
        {
            cin.ignore(65536, '\n');
            break;
        }
        else
        {
            cin.clear();
            cin.ignore(65536, '\n');
        }
    }
    while (1)
    {
        cout << "��������ʼ��(A-C)" << endl;
        cin >> src;
        src = capital(src);
        if (cin.good() && (src >= 'A' && src <= 'C'))
        {
            cin.ignore(65536, '\n');
            break;
        }
        else
        {
            cin.clear();
            cin.ignore(65536, '\n');
        }
    }
    while (1)
    {
        cout << "������Ŀ����(A-C)" << endl;
        cin >> dst;
        dst = capital(dst);
        if (dst == src)
        {
            cout << "Ŀ����(" << dst << ")��������ʼ��(" << src << ")��ͬ" << endl;
            cin.clear();
            cin.ignore(65536, '\n');
        }
        else if (cin.good() == 1 && (dst >= 'A' && dst <= 'C'))
        {
            cin.ignore(65536, '\n');
            break;
        }
        else
        {
            cin.clear();
            cin.ignore(65536, '\n');
        }
    }

    src = capital(src);
    dst = capital(dst);
    if ((src == 'B' && dst == 'C') || (src == 'C' && dst == 'B'))
        tmp = 'A';
    if ((src == 'A' && dst == 'C') || (src == 'C' && dst == 'A'))
        tmp = 'B';
    if ((src == 'A' && dst == 'B') || (src == 'B' && dst == 'A'))
        tmp = 'C';   //ȷ��������
}

/***************************************************************************
  �������ƣ�my_input_9
  ��    �ܣ����벢�����������
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void getInput(char(&input)[MAX_9])
{
    while (1)
    {
        int i = 0;
        while (1)
        {
            input[i] = _getche();
            if (input[i] == 13)
            {
                input[i] = '\0';
                break;
            }

            if (input[i] < 33 || input[i] > 126)
            {
                // ����Ƿ�ΪСд��ĸ���������д��ĸ'A'���'a' - 'A'
                if (input[i] >= 'a' && input[i] <= 'z' && input[i] - 'a' == 'a' - 'A')
                {
                    _getche();
                }
                // ���Ǵ�ӡ�ַ��滻Ϊ�ַ���������
                input[i] = '\0';
                if (i == MAX_9 - 1)
                {
                    i = 0;
                    cct_gotoxy(X_9, Y_9);
                    cout << "                                         ";
                    cct_gotoxy(X_9, Y_9);
                }
                continue;
            }
            i++;
            if (i == MAX_9)
            {
                i = 0;
                cct_gotoxy(X_9, Y_9);
                cout << "                                         ";
                cct_gotoxy(X_9, Y_9);
            }
        }

        for (int i0 = 0; i0 < 2; i0++)
        {
            input[i0] = capital(input[i0]);
        }

        if (i == 2)
            break;
        bool x1 = input[1] >= 'A' && input[1] <= 'C';
        bool x2 = input[0] >= 'A' && input[0] <= 'C';
        if (x1 && x2)
            break;
        if (input[0] != input[1])
            break;
        if (i == 1 && (input[0] == 'Q' || input[0] == 'q'))   //�˳�����
            break;

        cct_gotoxy(X_9, Y_9);
        for (int j = 0; j <= i + 3; j++)
        {
            cout << " ";
        }
        cct_gotoxy(X_9, Y_9);
    }
}

/***************************************************************************
  �������ƣ�hanoi_all
  ��    �ܣ�����������ŵ�����������
  ���������
  �� �� ֵ��
  ˵    �������ݲ�����ͬ��ѡ��ͬ����
***************************************************************************/
int hanoi_all(int choice)
{
    char src = 0, dst = 0, tmp = 0;
    int storey = 0;
    if (choice != 0)
    {
        if (choice != 5)
        {
            my_input(storey, src, dst, tmp);
        }
    }
    if (choice == 4 || choice == 8)
    {
        my_speed();
    }

    switch (choice)
    {
        case 1:
            hanoi(storey, src, tmp, dst, 1);
            break;
        case 2:
            hanoi(storey, src, tmp, dst, 2);
            break;
        case 3:
            init(storey, src, 3);
            hanoi(storey, src, tmp, dst, 3);
            break;
        case 4:
            cct_cls();
            cout << "�� " << src << " �ƶ��� " << dst << "���� " << storey << " �㣬��ʱ����Ϊ " << speed;
            cct_gotoxy(LOC_ROW_X, LOC_ROW_Y);
            init(storey, src, 4);
            print_column_base(4);
            print_column_tower(4);
            hanoi(storey, src, tmp, dst, 4);
            cct_gotoxy(LOC_ENTER_X, LOC_ENTER_Y);
            break;
        case 5:
            cct_cls();
            draw_tower(storey, src, 5);
            cct_gotoxy(LOC_ENTER_X, LOC_ENTER_Y);
            break;
        case 6:
            cct_cls();
            cout << "�� " << src << " �ƶ��� " << dst << "���� " << storey << " ��";
            cct_setcursor(CURSOR_INVISIBLE);
            draw_tower(storey, src, 6);
            cct_gotoxy(LOC_ENTER_X, LOC_ENTER_Y);
            break;
        case 7:
            cct_cls();
            cout << "�� " << src << " �ƶ��� " << dst << "���� " << storey << " ��";
            cct_setcursor(CURSOR_INVISIBLE);
            init(storey, src, 7);
            draw_tower(storey, src, 7);
            print_all(storey, src, tmp, dst, 7);
            cct_gotoxy(LOC_ENTER_X, LOC_ENTER_Y);
            break;
        case 8:
            cct_cls();
            cout << "�� " << src << " �ƶ��� " << dst << "���� " << storey << " �㣬��ʱ����Ϊ " << speed;
            cct_setcursor(CURSOR_INVISIBLE);
            cct_gotoxy(LOC_ROW_X, LOC_ROW_Y + 18);
            init(storey, src, 8);
            print_column_base(8);
            print_column_tower(8);
            draw_tower(storey, src, 8);
            hanoi(storey, src, tmp, dst, 8);
            cct_gotoxy(LOC_ENTER_X, LOC_ENTER_Y + 18);
            break;
        case 9:
            char input[20];
            cct_cls();
            cout << "�� " << src << " �ƶ��� " << dst << "���� " << storey << " ��";
            cct_setcursor(CURSOR_INVISIBLE);
            cct_gotoxy(LOC_ROW_X, LOC_ROW_Y + 18);
            cct_gotoxy(0, Y_9 - 2);
            init(storey, src, 9);
            print_column_base(9);
            print_column_tower(9);
            draw_tower(storey, src, 9);
            cct_gotoxy(0, Y_9);
            cct_setcursor(CURSOR_VISIBLE_NORMAL);
            cout << "�������ƶ�������(������ʽ��AC=A���˵������ƶ���C��Q=�˳�) ��";
            while (1)
            {
                getInput(input);
                blank();
                if (input[0] == 'A')
                {
                    if (top[0] == 0)
                    {
                        cout << endl;
                        cout << "Դ��Ϊ��!";
                        blank();
                        continue;
                    }
                    if (input[1] == 'B')
                    {
                        if (hanoi0[0][top[0] - 1] > hanoi0[1][top[1] - 1] && hanoi0[1][top[1] - 1] != 0)
                        {
                            cout << endl;
                            cout << "����ѹС�̣��Ƿ��ƶ���";
                            blank();
                            continue;
                        }
                    }
                    else
                    {
                        if (hanoi0[0][top[0] - 1] > hanoi0[2][top[2] - 1] && hanoi0[2][top[2] - 1] != 0)
                        {
                            cout << endl;
                            cout << "����ѹС�̣��Ƿ��ƶ���";
                            blank();
                            continue;
                        }
                    }
                }
                if (input[0] == 'B')
                {
                    if (top[1] == 0)
                    {
                        cout << endl;
                        cout << "Դ��Ϊ��!";
                        blank();
                        continue;
                    }
                    if (input[1] == 'A') {
                        if (hanoi0[1][top[1] - 1] > hanoi0[0][top[0] - 1] && hanoi0[0][top[0] - 1] != 0) {
                            cout << endl;
                            cout << "����ѹС�̣��Ƿ��ƶ���";
                            blank();
                            continue;
                        }
                    }
                    else {
                        if (hanoi0[1][top[1] - 1] > hanoi0[2][top[2] - 1] && hanoi0[2][top[2] - 1] != 0) {
                            cout << endl;
                            cout << "����ѹС�̣��Ƿ��ƶ���";
                            blank();
                            continue;
                        }
                    }
                }
                if (input[0] == 'C')
                {
                    if (top[2] == 0)
                    {
                        cout << endl;
                        cout << "Դ��Ϊ��!";
                        blank();
                        continue;
                    }
                    if (input[1] == 'B') {
                        if (hanoi0[2][top[2] - 1] > hanoi0[1][top[1] - 1] && hanoi0[1][top[1] - 1] != 0) {
                            cout << endl;
                            cout << "����ѹС�̣��Ƿ��ƶ���";
                            blank();
                            continue;
                        }
                    }
                    else {
                        if (hanoi0[2][top[2] - 1] > hanoi0[0][top[0] - 1] && hanoi0[0][top[0] - 1] != 0) {
                            cout << endl;
                            cout << "����ѹС�̣��Ƿ��ƶ���";
                            blank();
                            continue;
                        }
                    }
                }
                Count++;
                int n0 = 0;
                if (input[0] == 'A')
                {
                    n0 = hanoi0[0][top[0] - 1];
                }
                if (input[0] == 'B')
                {
                    n0 = hanoi0[1][top[1] - 1];
                }
                if (input[0] == 'C')
                {
                    n0 = hanoi0[2][top[2] - 1];
                }
                print_all(n0, input[0], tmp, input[1], 9);

                for (int i = 0; i <= 1; i++)
                {
                    cout << " ";
                }
                cct_gotoxy(X_9, Y_9);
                if ((dst == 'A' && top[0] == storey) || (dst == 'B' && top[1] == storey) || (dst == 'C' && top[2] == storey))
                {
                    cout << endl;
                    cout << "��Ϸ����" << endl;
                    break;
                }
            }
    }
    return 0;
}


/***************************************************************************
  �������ƣ�blank
  ��    �ܣ��������
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void blank()
{
    Sleep(1000);
    cct_gotoxy(60, 35);
    cout << "  ";
    cct_gotoxy(0, 36);
    cout << "                                         ";
    cct_gotoxy(0, 37);
    cout << "                                         ";
    cct_gotoxy(60, 35);
}

/***************************************************************************
  �������ƣ�hanoi
  ��    �ܣ���ŵ���ݹ麯��
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void hanoi(int n, char src, char tmp, char dst, int choice)
{
    if (n == 1)
    {
        Count++;
        print_all(n, src, tmp, dst, choice);
    }
    else
    {
        hanoi(n - 1, src, dst, tmp, choice);
        Count++;
        print_all(n, src, tmp, dst, choice);
        hanoi(n - 1, tmp, src, dst, choice);
    }
}