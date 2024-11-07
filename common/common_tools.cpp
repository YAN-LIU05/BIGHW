/* 2352018 ������ ���� */
#include <iostream>
#include <cstdlib> 
#include <ctime> 
#include <windows.h>
#include <conio.h>
#include <iomanip>
#include "../include/bighw.h"
#include "../include/cmd_console_tools.h"

using namespace std;

/***************************************************************************
  �������ƣ�
  ��    �ܣ����ַ���str�ĳ���
  ���������
  �� �� ֵ���ַ�������
  ˵    ����
***************************************************************************/
int tj_strlen(const char* str)
{
	/* ע�⣺�����ڲ��������κ���ʽ�����飨������̬���飩 */
	int length = 0;
	if (str == NULL)
	{
		return 0;
	}

	while (*str != '\0')
	{
		length++;
		str++;
	}

	return length;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ����ַ���s2���Ƶ�s1��,����s1��ԭ����,����ʱ����\0
  ���������
  �� �� ֵ���µ�s1
  ˵    ����
***************************************************************************/
char* tj_strcpy(char* s1, const char* s2)
{
	/* ע�⣺�����ڲ��������κ���ʽ�����飨������̬���飩 */
	if (s1 == NULL)
	{
		return s1;
	}

	char* s = s1;

	if (s2 == NULL)
	{
		*s = '\0';
	}
	else
	{
		for (; *s2 != '\0'; s++, s2++)
		{
			*s = *s2;
		}
		*s = '\0';
	}

	return s1;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ��Ƚ��ַ���s1��s2�Ĵ�С,Ӣ����ĸ���ִ�Сд
  ���������
  �� �� ֵ�����Ϊ0,������Ϊ��1��������ַ���ASCII��ֵ
  ˵    ����
***************************************************************************/
int tj_strcasecmp(const char* s1, const char* s2)
{
	/* ע�⣺�����ڲ��������κ���ʽ�����飨������̬���飩 */
	if (s1 == NULL || s2 == NULL)
	{
		int t = (s1 != NULL) - (s2 != NULL);
		return t;
	}
	char s_1, s_2;
	while (1)
	{
		if (*s1 >= 'A' && *s1 <= 'Z')
		{
			s_1 = *s1 + 'a' - 'A';
		}
		else
		{
			s_1 = *s1;
		}
		if (*s2 >= 'A' && *s2 <= 'Z')
		{
			s_2 = *s2 + 'a' - 'A';
		}
		else
		{
			s_2 = *s2;
		}
		if (s_1 == s_2)
		{
			if (s_1 == '\0')
				break;
			s1++;
			s2++;
		}
		else
		{
			break;
		}
	}
	return s_1 - s_2;
}

/***************************************************************************
  �������ƣ�print_origin
  ��    �ܣ���ӡ��ʼ����
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void print_origin(int rows, int cols, int array[][MAX_ROWS], int num1, int num2)
{

	cout << "  | ";
	if (num2 == 0)
	{
		for (int j = 0; j < cols; ++j)
			cout << " " << j + 1 << " ";
	}
	else if (num2 == 1)
	{
		for (int j = 0; j < cols; ++j)
			cout << " " << j << " ";
	}
	cout << endl;
	cout << "--+-";;
	for (int i = 0; i < cols; ++i)
		cout << "---";
	cout << endl;
	for (int i = 0; i < rows; ++i)
	{
		cout << static_cast<char>('A' + i) << " | ";
		if (num1 == 1)
		{
			for (int j = 0; j < cols; ++j)
				cout << " " << array[i][j] << " ";
		}
		else if (num1 == 0)
		{
			for (int j = 0; j < cols; ++j)
			{
				if (array[i][j] == 1)
				{
					cout << " " << "*" << " ";

				}
				else
				{
					cout << " " << "0" << " ";
				}
			}

		}
		cout << endl;
	}
	cout << endl;
}

/***************************************************************************
  �������ƣ�zero_drop
  ��    �ܣ�����Ԫ������
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void zero_drop(int array[MAX_ROWS][MAX_COLS], int rows, int cols)
{
	// �Ӿ���ײ���ʼ���ϱ�������0����ķ�0Ԫ������
	for (int j = 0; j < cols; ++j)   //�Ӿ���ײ���ʼ���ϱ���
	{
		for (int i = rows - 1; i >= 0; --i)   //�����ǰԪ����0������Ҫ��������ķ�0Ԫ��
		{
			if (array[i][j] == 0)  //�ӵ�ǰλ�����ϲ��ҵ�һ����0Ԫ��
			{
				for (int k = i - 1; k >= 0; --k)
				{
					if (array[k][j] != 0)
					{
						// ���ҵ��ķ�0Ԫ���ƶ�����ǰ0��λ��
						array[i][j] = array[k][j];
						// ����ԭ����λ������Ϊ0
						array[k][j] = 0;
						break;
					}
				}
			}
		}
	}
}

/***************************************************************************
  �������ƣ�draw_border
  ��    �ܣ������߿�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void draw_border(int rows, int cols, bool border, int choice, int which)
{
	if (which == 1)
	{
		cout << endl;
		cct_gotoxy(0, 1);
		int temp = rows;
		rows = cols;
		cols = temp;
		cct_gotoxy(0, 1);
		int hight = (border) ? cols * 3 + (cols - 1) : cols * 3;
		set_botton(true, border ? hight + 3 : hight + 2);

		cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
		if (!border)
		{
			cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
			cout << "�X "; 
			for (int i = 0; i < rows; i++) 
			{
				cout << "�T ";
				if (choice == 4)
					Sleep(TIME);
			}
			cout << "�[ ";
			for (int i = 0; i < cols; i++)
			{
				cct_gotoxy(0, i + 2);
				cout << "�U ";
				cct_gotoxy(rows * 2 + 2, i + 2);
				cout << "�U ";
				if (choice == 4)
					Sleep(TIME);
			}
			cct_gotoxy(0, cols + 2);
			cout << "�^ ";
			for (int i = 0; i < rows; i++) 
			{
				cout << "�T ";
				if (choice == 4)
					Sleep(TIME);
			}
			cout << "�a ";
		}

		if (border)
		{
			cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
			cout << "�X ";
			for (int i = 0; i < rows; i++)
			{
				cout << "�T ";
				if (choice == 5)
					Sleep(TIME);
				if (i == rows - 1)
					break;
				cout << "�j ";
				if (choice == 5)
					Sleep(TIME);
			}

			cout << "�[ ";
			for (int i = 0; i < cols * 2; i += 2)
			{
				for (int j = 0; j <= rows * 4; j += 4)
				{

					if (j == 0)
					{
						cct_gotoxy(0, i + 2);
						cout << "�U  ";
					}
					if (j == rows * 4)
					{
						cct_gotoxy(j - 1, i + 2);
						cout << " �U ";
					}
					if (j > 0 && j < rows * 4)
					{
						cct_gotoxy(j - 1, i + 2);
						cout << " �U  ";
					}

					if (choice == 5)
						Sleep(TIME);
				}
				if (i < cols * 2 - 2)
				{
					cct_gotoxy(0, i + 3);
					cout << "�d ";
					for (int i = 0; i < rows; i++)
					{
						cout << "�T ";
						if (choice == 5)
							Sleep(TIME);
						if (i == rows - 1)
							break;
						cout << "�p ";
						if (choice == 5)
							Sleep(TIME);
					}
					cout << "�g ";
				}
			}
			cct_gotoxy(0, cols * 2 + 1);
			cout << "�^ ";
			for (int i = 0; i < rows; i++)
			{
				cout << "�T ";
				if (choice == 5)
					Sleep(TIME);
				if (i == rows - 1)
					break;
				cout << "�m ";
				if (choice == 5)
					Sleep(TIME);
			}
			cout << "�a ";
		}
	}



	if (which == 2)
	{
		cout << endl;
		//��һ�б�ͷ
		cout << " ";
		Sleep(5);
		for (int i = 0; i < cols; i++)
		{
			if (i == 0)
				cout << setw(6) << i;
			else
				cout << setw(6 + border * 2) << i;
		}
		cout << endl;

		//��һ�������
		cout << "  ";
		Sleep(5);
		cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
		cout << "�X ";
		Sleep(5);
		for (int i = 0; i < cols; i++)
		{
			cout << "�T �T �T ";
			if ((border == 1) && (i != cols - 1))
				cout << "�j ";
			Sleep(5);
		}
		cout << "�[ ";
		Sleep(5);
		cct_setcolor(COLOR_BLACK, COLOR_WHITE);
		cout << endl;

		//�в�
		for (int i = 0; i < rows; i++)
		{
			cout << "  ";
			Sleep(5);
			single_outline(cols, border);
			cout << endl;
			cout << (char)('A' + i) << " ";
			Sleep(5);
			single_outline(cols, border);
			cout << endl;
			cout << "  ";
			Sleep(5);
			single_outline(cols, border);
			cout << endl;
			if ((i != rows - 1) && (border == 1))
			{
				cout << "  ";
				Sleep(5);
				cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
				cout << "�d ";
				Sleep(5);
				for (int i = 0; i < cols; i++)
				{
					cout << "�T �T �T ";
					if (i != cols - 1)
					{
						cout << "�p ";
					}
					Sleep(5);
				}
				cout << "�g ";
				Sleep(5);
				cct_setcolor(COLOR_BLACK, COLOR_WHITE);
				cout << endl;
			}
		}

		//���һ�������
		cout << "  ";
		Sleep(5);
		cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
		cout << "�^ ";
		Sleep(5);
		for (int i = 0; i < cols; i++)
		{
			cout << "�T �T �T ";
			if ((border == 1) && (i != cols - 1))
				cout << "�m ";
			Sleep(5);
		}
		cout << "�a ";
		Sleep(5);
	}
	cct_setcolor(COLOR_BLACK, COLOR_WHITE);
	cout << endl;

}

/***************************************************************************
  �������ƣ�set_botton
  ��    �ܣ���������
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void set_botton(bool set, int num)
{
	static int Y = 0;
	if (set)
		Y = num;
	else
		cct_gotoxy(0, Y);
}

/***************************************************************************
	�������ƣ�element_fall
	��    ��  ��ά������������
	���������
	�� �� ֵ��
	˵    ����
***************************************************************************/
void element_fall(int array[][MAX_COLS], int array_around[][MAX_COLS], int rows, int cols, int have_block, int border) {
	// ��ɫ��λ����Ϊ 0
	for (int j = 0; j < cols; j++) {
		for (int i = 0; i < rows; i++) {
			if (array_around[i][j] == '*') {
				array[i][j] = 0; // ֱ�Ӳ���
			}
		}
	}

	// ð�ݲ������� 0 ð�ݵ��·�
	int is_stable;
	do {
		is_stable = 1; // ���赱ǰ״̬�ȶ�
		for (int j = 0; j < cols; j++) {
			for (int i = rows - 1; i > 0; i--) {
				if (array[i][j] == 0 && array[i - 1][j] != 0) {
					// ����
					int temp = array[i - 1][j];
					array[i - 1][j] = array[i][j];
					array[i][j] = temp;

					// �����ɫ�������������ɫ����
					if (have_block == 1) {
						draw_block(i, j, border, array, rows, cols, 1);
						Sleep(5);
						draw_block(i - 1, j, border, array, rows, cols, 0);
					}
					is_stable = 0; // ���Ϊ���ȶ�
				}
			}
		}
	} while (!is_stable); // ֱ��״̬�ȶ�Ϊֹ
}

/***************************************************************************
	�������ƣ�draw_block
	��    �ܣ���һ��ɫ��
	���������
	�� �� ֵ��
	˵    ������X,YΪ���Ļ�ɫ�飬��X,YΪ����λ��
***************************************************************************/
void draw_block(int i, int j, int border, int array[][MAX_COLS], int rows, int cols, int state)
{
	int X, Y;
	int color_fg = 0, color_bg = 0;

	//��0��������ʾ����
	if (array[i][j] == 0)
		state = 0;
	switch (state)
	{
		case 1:
			color_fg = COLOR_BLACK;
			color_bg = array[i][j] + 8;
			break;
		case -1:
			color_fg = COLOR_HWHITE;
			color_bg = array[i][j] + 8;
			break;
		case -2:
			color_fg = COLOR_WHITE;
			color_bg = array[i][j] + 8;
			break;
		case 0: // �����˵�����
			color_fg = COLOR_HWHITE;
			color_bg = COLOR_HWHITE;
			break;
	}

	cct_setcolor(color_bg, color_fg);
	location_trans(1, i, j, X, Y, rows, cols, border);
	cct_gotoxy(X - 2, Y - 1);
	cout << "�X �T �[ ";
	cct_gotoxy(X - 2, Y);
	cout << "�U ��U ";
	cct_gotoxy(X - 2, Y + 1);
	cout << "�^ �T �a ";
	cct_setcolor(COLOR_BLACK, COLOR_WHITE);
}

/***************************************************************************
	�������ƣ�location_trans
	��    �ܣ���һ��array�ڲ�����������αͼ��������������λ��ת���ĺ���
	���������
	�� �� ֵ��
	˵    ����1 ������������α����������� ��֮Ϊ-1
***************************************************************************/
void location_trans(const int drc, int& i, int& j, int& X, int& Y, int rows, int cols, int border)
{
	// ���� Y �� X ��λ��
	if (drc == 1)
	{
		Y = 4 + (3 + border) * i;
		X = 6 + (6 + border * 2) * j;
	}
	else if (drc == -1)
	{
		// �ںϷ������ڵķ�Χ
		int y_min = 3;
		int y_max = (border == 0) ? 3 + rows * 3 : 3 + rows * (3 + border);
		int x_min = 4;
		int x_max = 4 + (6 + border * 2) * cols;

		if ((Y >= y_min && Y < y_max) && (X >= x_min && X < x_max))
		{
			if (border == 1)
			{
				if (((Y - 3) % 4 >= 0 && (Y - 3) % 4 <= 2) && ((X - 4) % 8 >= 0 && (X - 4) % 8 <= 5))
				{
					i = (Y - 3) / (3 + border);
					j = (X - 4) / (6 + border * 2);
				}
				else
				{
					i = -1;
					j = -1;
				}
			}
			else
			{
				i = (Y - 3) / (3 + border);
				j = (X - 4) / (6 + border * 2);
			}
		}
		else
		{
			i = -1;
			j = -1;
		}
	}
}

/***************************************************************************
	�������ƣ�single_outline
	��    �ܣ�����һ�еĳ�ʼ�����
	���������
	�� �� ֵ��
	˵    ����
***************************************************************************/
void single_outline(int col, const int border)
{
	cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
	cout << "�U ";
	Sleep(5);
	for (int i = 0; i < col; i++)
	{
		int x, y;
		cct_getxy(x, y);
		cct_showch(x, y, ' ', COLOR_HWHITE, COLOR_BLACK, 6);
		if ((i != col - 1) && (border == 1))
		{
			cout << "�U ";
			Sleep(5);
		}
		Sleep(5);
	}
	cout << "�U ";
	Sleep(5);
	cct_setcolor(COLOR_BLACK, COLOR_WHITE);
}

/***************************************************************************
	�������ƣ�find_empty_above
	��    �ܣ���ָ�����ϲ��Ҵӵ�ǰ������ֱ����һ�еĵ�һ������Ԫ��
	���������
	�� �� ֵ��
	˵    ����
***************************************************************************/
int find_empty_above(int i_last, int j_last, int array[][MAX_COLS], int rows)
{
	for (int i = rows - 1; i >= 0; i--)
	{
		if (array[i][j_last] != 0)
		{
			return i + 1;
		}
	}
	return 0; // ���û���ҵ�������0
}

/***************************************************************************
	�������ƣ�fill_array
	��    �ܣ��������
	���������
	�� �� ֵ��
	˵    ����
***************************************************************************/
void fill_array(int array[MAX_ROWS][MAX_COLS], int rows, int cols, int num)
{
	int opt = 0;
	switch (num)
	{
		case 1:
			opt = 9;
			break;
		case 2:
			opt = 5;
			break;
	}
	srand(static_cast<unsigned int>(time(nullptr)));
	for (int i = 0; i < rows; ++i) 
	{
		for (int j = 0; j < cols; ++j) 
		{
			array[i][j] = (rand() % opt) + 1; // ���1��9֮��������
		}
	}
}

/***************************************************************************
	�������ƣ�copy_array
	��    �ܣ���������
	���������
	�� �� ֵ��
	˵    ����
***************************************************************************/
void copy_array(const int source[MAX_ROWS][MAX_COLS], int destination[MAX_ROWS][MAX_COLS], int rows, int cols) 
{
	for (int i = 0; i < rows; ++i) 
	{
		for (int j = 0; j < cols; ++j) 
		{
			destination[i][j] = source[i][j];
		}
	}
}

/***************************************************************************
  �������ƣ�base_check0
  ��    �ܣ�����Ƿ��������
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
bool base_check0(const int array[MAX_ROWS][MAX_COLS], int row, int col, int rows, int cols)
{
	if (row >= rows || col >= cols)
		return 0;

	int count = 1; // ��Ŀ��Ԫ�ؿ�ʼ����
	for (int j = col + 1; j < cols && count < 3; j++) //���Ҽ��
	{
		if (array[row][j] == array[row][col])
		{
			count++;
			if (count >= 3)
				return 1;
		}
		else
			break; // ������ͬ��Ԫ�أ�ֹͣ���
	}
	for (int j = col - 1; j >= 0 && count < 3; j--) //������
	{
		if (array[row][j] == array[row][col])
		{
			count++;
			if (count >= 3)
				return 1;
		}
		else
			break; // ������ͬ��Ԫ�أ�ֹͣ���
	}

	count = 1; // ���ü���
	for (int i = row + 1; i < rows && count < 3; i++) //���¼��
	{
		if (array[i][col] == array[row][col])
		{
			count++;
			if (count >= 3)
				return 1;
		}
		else
			break; // ������ͬ��Ԫ�أ�ֹͣ���
	}
	for (int i = row - 1; i >= 0 && count < 3; i--) //���ϼ��
	{
		if (array[i][col] == array[row][col])
		{
			count++;
			if (count >= 3)
				return 1;
		}
		else
			break; // ������ͬ��Ԫ�أ�ֹͣ���
	}

	return 0; // û���ҵ���������
}

/***************************************************************************
  �������ƣ�base_check1
  ��    �ܣ�����Ƿ��г�ʼ��������
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
bool base_check1(const int array[MAX_ROWS][MAX_COLS], int rows, int cols)
{
	int num = 0;
	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			if (base_check0(array, i, j, rows, cols))
				num++;
		}
	}
	if (num)
		return 1;
	else
		return 0;
}

/***************************************************************************
  �������ƣ�base_check2
  ��    �ܣ�����Ƿ������ʾ
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
bool base_check2(const int array[MAX_ROWS][MAX_COLS], const int directions[4][2], int row, int col, int rows, int cols)
{
	if (row < 0 || row >= rows || col < 0 || col >= cols)
		return 0;

	// ����һ������ĸ�����ģ�⽻��
	int arrayCopy[MAX_ROWS][MAX_COLS];
	copy_array(array, arrayCopy, rows, cols);

	// �������Ԫ�ؽ������Ƿ�������������
	for (int i = 0; i < 4; ++i)
	{
		int nextRow = row + directions[i][0];
		int nextCol = col + directions[i][1];
		if (nextRow >= 0 && nextRow < rows && nextCol >= 0 && nextCol < cols)   //����
		{
			int temp = arrayCopy[nextRow][nextCol];
			arrayCopy[nextRow][nextCol] = arrayCopy[row][col];
			arrayCopy[row][col] = temp;

			if (col - 1 >= 0 && row - 1 >= 0)
			{
				if (base_check0(arrayCopy, row, col, rows, cols) || base_check0(arrayCopy, row + 1, col, rows, cols) || base_check0(arrayCopy, row - 1, col, rows, cols)
					|| base_check0(arrayCopy, row, col + 1, rows, cols) || base_check0(arrayCopy, row, col - 1, rows, cols))
					return 1;
			}
			else if (col - 1 >= 0 && row - 1 < 0)
			{
				if (base_check0(arrayCopy, row, col, rows, cols) || base_check0(arrayCopy, row + 1, col, rows, cols) || base_check0(arrayCopy, row, col + 1, rows, cols)
					|| base_check0(arrayCopy, row, col - 1, rows, cols))
					return 1;
			}
			else if (col - 1 < 0 && row - 1 >= 0)
			{
				if (base_check0(arrayCopy, row, col, rows, cols) || base_check0(arrayCopy, row + 1, col, rows, cols) || base_check0(arrayCopy, row - 1, col, rows, cols)
					|| base_check0(arrayCopy, row, col + 1, rows, cols))
					return 1;
			}
			else
			{
				if (base_check0(arrayCopy, row, col, rows, cols) || base_check0(arrayCopy, row + 1, col, rows, cols) || base_check0(arrayCopy, row, col + 1, rows, cols))
					return 1;
			}

			// �ָ�����ǰ������״̬
			temp = arrayCopy[nextRow][nextCol];
			arrayCopy[nextRow][nextCol] = arrayCopy[row][col];
			arrayCopy[row][col] = temp;
		}
	}

	return 0;
}
