/* 2352018 ������ ���� */
#include <iostream>
#include <conio.h>
#include "../include/cmd_console_tools.h"
#include "../include/bighw.h"
#include "90-01-b2-magic_ball.h"
using namespace std;


/***************************************************************************
  �������ƣ�print_mark
  ��    �ܣ���ӡ��ʼ��������
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void print_mark(int rows, int cols, int array[MIN_ROWS][MAX_ROWS])
{
    cout << endl;
    cout << "��ʼ���������ͬɫ��ʶ����" << endl;
    cout << "  | ";
    for (int j = 0; j < cols; ++j)
        cout << " " << j + 1 << " ";
    cout << endl;
    cout << "--+-";;
    for (int i = 0; i < cols; ++i)
        cout << "---";
    cout << endl;
    for (int i = 0; i < rows; ++i)
    {
        cout << static_cast<char>('A' + i) << " | ";
        for (int j = 0; j < cols; ++j)
        {
            // ��鲢��ǿ�������
            if (base_check0(array, i, j, rows, cols))
            {
                cout << " ";
                cct_setcolor(COLOR_HYELLOW, COLOR_HBLUE);
                cout << array[i][j];
                cct_setcolor(COLOR_BLACK, COLOR_WHITE);// ������ɫ
                cout << " ";
            }
            else
                cout << " " << array[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

/***************************************************************************
  �������ƣ�print_tips
  ��    �ܣ���ӡ��ʾ��
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void print_tips(int rows, int cols, int array[MIN_ROWS][MAX_ROWS])
{
    int directions[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };   //��������
    cout << endl;
    cout << "��ѡ���������ʾ����ͬɫ��ʶ����" << endl;
    cout << "  | ";
    for (int j = 0; j < cols; ++j)
        cout << " " << j + 1 << " ";
    cout << endl;
    cout << "--+-";;
    for (int i = 0; i < cols; ++i)
        cout << "---";
    cout << endl;
    for (int i = 0; i < rows; ++i)
    {
        cout << static_cast<char>('A' + i) << " | ";
        for (int j = 0; j < cols; ++j)
        {
            // ��鲢��ǿ�������
            if (base_check2(array, directions, i, j, rows, cols))
            {
                cout << " ";
                cct_setcolor(COLOR_HYELLOW, COLOR_HBLUE);
                cout << array[i][j];
                cct_setcolor(COLOR_BLACK, COLOR_WHITE);// ������ɫ
                cout << " ";
            }
            else
                cout << " " << array[i][j] << " ";
        }
        cout << endl;
    }
}

