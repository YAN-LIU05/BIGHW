/* 2352018 ������ ���� */
#include <iostream>
#include <conio.h>
#include <windows.h>
#include "../include/cmd_console_tools.h"
#include "../include/bighw.h"
#include "90-01-b2-magic_ball.h"
using namespace std;

#define MAX_LENGTH 256

/***************************************************************************
  �������ƣ�main
  ��    �ܣ����ú���
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int main()
{
	/* demo������ִ�д˾䣬��cmd��������Ϊ40��x120�У����������120�У�����9000�У���cmd�����Ҳ���д�ֱ�����ˣ�*/
	cct_setconsoleborder(120, 40, 120, 9000);
	cct_setfontsize("������", 16);
	int x, y;
	while (1)
	{
		int choice = all_menu(1);
		int choice0 = choice - 48;
		if (choice0 == 0)
		{
			cct_gotoxy(0, 30);
			break;
		}
		else
		{
			Sleep(200);
			cct_cls();
			//��亯��
			if (choice0 >= 1 && choice0 <= 9)
				ball_base_all(choice0);
			cct_setcursor(CURSOR_VISIBLE_NORMAL);
			cout << "��С�������������End����...";
			cct_getxy(x, y);
			char input[MAX_LENGTH] = { 0 };
			int index = 0; // ���ڸ��������еĵ�ǰλ��
			bool end = false;

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
					end = true;
				else if (ch == '\r')
				{
					cout << endl;
					if (choice0 <= 3 && choice0 >= 1)
						cout << "�����������������";
					if (choice0 == 4 || choice0 == 5)
						cout << "��С�������������End����...";
					index = 0;
					input[0] = '\0';
					cct_gotoxy(x, y);
					for (int i = 1; i < 10; i++)
						cout << " ";
					cct_gotoxy(x, y);
				}
			}
			cct_setconsoleborder(120, 40, 120, 9000);
			cct_setfontsize("������", 16);
			cct_cls();
		}
	}

	return 0;
}