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
#include "90-02-b2-mine_sweeper.h"

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
	CONSOLE_GRAPHICS_INFO MineSweeper_CGI; //����һ��CGI����
	int choice;
	
    while (1)
    {
        cct_setconsoleborder(120, 40, 120, 9000);
        cct_setfontsize("������", 16);
        while (1)
        {
            cout << R"(������ɨ����Ϸ�ĵȼ�(����), ����\�м�\�߼�(1\2\3)  )";
            cin >> choice;
            if (choice >= 1 && choice <= 3)
                break;
            else if (!cin.good())
            {
                cin.clear();
                cin.ignore(INT_MAX, '\n');
            }
        }
       
        cct_cls();

        mine_map_all(&MineSweeper_CGI, choice);
        Sleep(3000);
        gmw_status_line(&MineSweeper_CGI, LOWER_STATUS_LINE, "���س�����", NULL);
        if (_getch() == '\r')
            break;
        else
            continue;
    }
    
}






















