/* 2352018 ������ ���� */
#include <iostream>
#include <conio.h>
#include "../include/cmd_console_tools.h"
#include "../include/bighw.h"
#include "90-01-b1-hanoi.h"
using namespace std;
/* ----------------------------------------------------------------------------------

	 ���ļ����ܣ�
	1����main����
	2����ʼ����Ļ
	3�����ò˵�������hanoi_menu.cpp�У�������ѡ��
	4������ѡ����ò˵������Ӧ��ִ�к�����hanoi_multiple_solutions.cpp�У�

	 ���ļ�Ҫ��
	1������������ȫ�ֱ��������ⲿȫ�ֺ;�̬ȫ�֣�const��#define�������Ʒ�Χ�ڣ�
	2����̬�ֲ����������������ƣ���ʹ��׼��Ҳ�ǣ����á����á��ܲ��þ�������
	3���������ϵͳͷ�ļ����Զ���ͷ�ļ��������ռ��

   ----------------------------------------------------------------------------------- */

   /***************************************************************************
	 �������ƣ�main
	 ��    �ܣ����ú���
	 ���������
	 �� �� ֵ��
	 ˵    ����
   ***************************************************************************/
int main()
{
	/* demo������ִ�д˾䣬��cmd��������Ϊ40��x120�У�����������120�У�����9000�У���cmd�����Ҳ���д�ֱ�����ˣ�*/
	cct_setconsoleborder(120, 40, 120, 9000);

	while (1)
	{
		int choice = all_menu(0);
		int choice0 = choice - 48;
		if (choice0 == 0)
		{
			cct_gotoxy(0, 30);
			break;
		}
		else
		{
			hanoi_all(choice0);
			cout << endl;
			cct_setcursor(CURSOR_VISIBLE_NORMAL);
			cout << "���س�������";
			while (_getch() != 13);
			{
				cct_cls();
			}
		}
	}

	return 0;
}