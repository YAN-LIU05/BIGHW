/* 2352018 ������ ���� */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdlib> 
#include <ctime> 
#include <windows.h>
#include <conio.h>
#include <iomanip>
#include "../include/cmd_console_tools.h"
#include "../include/cmd_gmw_tools.h"
#include "../include/bighw.h"
#include "90-02-b1-gmw-popstar.h"

using namespace std;


/***************************************************************************
  �������ƣ�main
  ��    �ܣ����ܺ���
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int main()
{
    CONSOLE_GRAPHICS_INFO PopStar_CGI; //����һ��CGI����
    int rows, cols;
    //int row0, col0;
    //int x, y;
    int count1 = 0;
    int score = 0;
    int total = 0;
    char input[MAX_LENGTH] = { 0 };
    int index = 0; // ���ڸ��������еĵ�ǰλ��
    bool end = false;
    // ������֤
    while (1)
    {
        cct_setconsoleborder(120, 40, 120, 9000);
        cct_setfontsize("������", 16);
        cout << "����������(8-10)��" << endl;
        cin >> rows;

        if (rows >= MIN_ROWS && rows <= MAX_ROWS)
            break;
        else if (!cin.good())
        {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
        }
    }
    while (1)
    {
        cout << "����������(8-10)��" << endl;
        cin >> cols;

        if (cols >= MIN_COLS && cols <= MAX_COLS)
            break;
        else if (!cin.good())
        {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
        }
    }

    srand(static_cast<unsigned int>(time(nullptr)));
    int array[MAX_ROWS][MAX_COLS];   //�������Ϊ�����
    bool one_round = 1;
    fill_array(array, rows, cols, 2);
    draw_map(rows, cols, 1, array, 'G', &PopStar_CGI);
    gmw_status_line(&PopStar_CGI, LOWER_STATUS_LINE, "��С�������������End����... ", "");
    cout << endl;
    int x = 0, y = 0;


    while (!end)
    {
        char ch = _getch();
        if (index < MAX_LENGTH - 1)
        {
            cout << ch;
            input[index++] = ch;   //���ַ���ӵ�����������
            input[index] = '\0';   //ȷ���ַ����Կ��ַ���β
        }
        if (tj_strcasecmp(input, "End\r") == 0)	  //����Ƿ�������������"End\r"
        {
            end = true;
            cout << endl;
        }

        else if (ch == '\r')
        {
            gmw_status_line(&PopStar_CGI, LOWER_STATUS_LINE, "�����������������", "");
            cout << endl;
            cct_getxy(x, y);
            cout << "         ";
            cct_gotoxy(x, y);
            index = 0;
            input[0] = '\0';
            
        }
    }
   
    return 0;
}

