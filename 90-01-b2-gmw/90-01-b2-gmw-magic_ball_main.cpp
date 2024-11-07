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
#include "90-01-b2-gmw-magic_ball.h"

using namespace std;

/***************************************************************************
  �������ƣ�main
  ��    �ܣ����ú���
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int main()
{
    int rows, cols;
    char input[MAX_LENGTH] = { 0 };
    bool end = false;
    int index = 0; // ���ڸ��������еĵ�ǰλ��
    CONSOLE_GRAPHICS_INFO pMagicBall_CGI;
	cct_setconsoleborder(120, 40, 120, 9000);
	cct_setfontsize("������", 16);
    while (1)
    {
        cout << "����������(5-9)��" << endl;
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
        cout << "����������(5-9)��" << endl;
        cin >> cols;

        if (cols >= MIN_COLS && cols <= MAX_COLS)
            break;
        else if (!cin.good())
        {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
        }
    }
    ball_base_all(&pMagicBall_CGI, rows, cols);

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
            gmw_status_line(&pMagicBall_CGI, LOWER_STATUS_LINE, "�����������������", "");
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