/* 2352018 ������ ���� */
#include <iostream>
#include <windows.h>
#include <conio.h>
#include "../include/cmd_console_tools.h"
#include "../include/bighw.h"
#include "90-02-b1-popstar.h"
using namespace std;

int main()
{
	cct_setconsoleborder(120, 40, 120, 9000);
	cct_setfontsize("������", 16);
	int x, y;
	while (1)
	{
		int choice = all_menu('A');
		int choice0;
		if (choice >= 'a' && choice <= 'z')
			choice0 = choice - 'a' + 'A';
		else
			choice0 = choice;
		if (choice == 'Q' || choice == 'q')
		{
			cct_gotoxy(0, 30);
			break;
		}
		else
		{
			Sleep(200);
			cct_cls();
			//��亯��
			if ((choice >= 'A' && choice <= 'G') || (choice >= 'a' && choice <= 'g'))
				popstar_base_all(choice0);
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

					cout << "�����������������";
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
