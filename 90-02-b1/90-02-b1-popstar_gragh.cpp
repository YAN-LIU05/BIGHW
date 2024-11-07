/* 2352018 ������ ���� */
#include <iostream>
#include <cstdlib> 
#include <ctime> 
#include <windows.h>
#include <conio.h>
#include <iomanip>
#include "../include/cmd_console_tools.h"
#include "../include/bighw.h"
#include "90-02-b1-popstar.h"

using namespace std;

/***************************************************************************
	�������ƣ�draw_around
	��    �ܣ�ѡ���Ժ���ʾ��Χ����Ԫ��
	���������
	�� �� ֵ��
	˵    ����
***************************************************************************/
bool draw_around(int rows, int cols, int border, int array[][MAX_COLS], int array_around[][MAX_COLS], int choice, int i_last, int j_last)
{
	// ����ԭʼ���鵽��ΧԪ������
	for (int i = 0; i < 10; i++) 
		for (int j = 0; j < 10; j++) 
			array_around[i][j] = array[i][j];

	// �����Χ����Ԫ��
	
	if (star_check(array, array_around, i_last, j_last) == 0)
	{
		cct_gotoxy(0, 4 + rows * (3 + border));
		cct_setcolor(COLOR_BLACK, COLOR_HYELLOW);
		cout << "��Χ����ֵͬ ";
		cct_setcolor(COLOR_BLACK, COLOR_WHITE);
		cout << "��ͷ��/����ƶ� �س���/�������ѡ�� Q�˳�";
		Sleep(1000);
		for (int i = 0; i < 10; i++)
			for (int j = 0; j < 10; j++)
				array_around[i][j] = array[i][j];
		return false;
	}

	// ��ʾ����Ԫ��
	for (int i = 0; i < rows; i++) 
	{
		for (int j = 0; j < cols; j++) 
		{
			if (array_around[i][j] == '*') 
			{
				if (i != i_last || j != j_last) 
					draw_block(i, j, border, array, rows, cols, -2);
				else 
					draw_block(i_last, j_last, border, array, rows, cols, -1);
			}
		}
	}
	return true;
}

/***************************************************************************
	�������ƣ�popstar_compound
	��    �ܣ��ϳ����ڵ�����
	���������
	�� �� ֵ��
	˵    ����
***************************************************************************/
void pop_together(int rows, int cols, int border, int array[][MAX_COLS], int i_last, int j_last)
{
	int array_around[MAX_ROWS][MAX_COLS] = { 0 };
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			array_around[i][j] = array[i][j];
	star_check(array, array_around, i_last, j_last);
	for (int i = 0; i < rows; i++) 
	{
		for (int j = 0; j < cols; j++) 
		{
			if (array_around[i][j] == '*') 
			{
				draw_block(i, j, border, array, rows, cols, 0);
			}
		}
	}
}
