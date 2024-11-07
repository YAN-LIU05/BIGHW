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
  �������ƣ�star_replace0
  ��    �ܣ�����Ƿ�������ĺ���
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/

void star_replace0(int mp[MAX_ROWS][MAX_COLS], int flag[MAX_ROWS][MAX_COLS], int mark[MAX_ROWS][MAX_COLS], int row, int col, int x, int y, int target)
{

	if (x < 0 || x >= row || y < 0 || y >= col || flag[x][y] || mp[x][y] != target)
		return;
	flag[x][y] = 1;
	mark[x][y] = 1;

	int dx[] = { 1, -1, 0, 0 };
	int dy[] = { 0, 0, 1, -1 };
	for (int i = 0; i < 4; i++)
	{
		int nx = x + dx[i];
		int ny = y + dy[i];
		star_replace0(mp, flag, mark, row, col, nx, ny, target);
	}

}

/***************************************************************************
  �������ƣ�print_mark
  ��    �ܣ���ӡ��ǰ����(��ͬɫ��ʶ)
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void print_mark(int rows, int cols, int array[MIN_ROWS][MAX_ROWS], int mark[MIN_ROWS][MAX_ROWS], int num)
{
	if (num == 0 || num == 3)
		cout << "��ǰ����(��ͬɫ��ʶ):" << endl;
	else if (num == 1)
		cout << "��ֵͬ�鲢�������(��ͬɫ��ʶ):" << endl;
	else if (num == 2)
		cout << "����������:" << endl;
	cout << "  | ";
	for (int j = 0; j < cols; ++j)
		cout << " " << j << " ";
	cout << endl;
	cout << "--+-";
	for (int i = 0; i < cols; ++i)
		cout << "---";
	cout << endl;
	for (int i = 0; i < rows; ++i)
	{
		cout << static_cast<char>('A' + i) << " | ";
		for (int j = 0; j < cols; ++j)
		{
			if (num == 0 || num == 1)
			{
				if (mark[i][j] == 1)
				{
					cout << " ";
					cct_setcolor(COLOR_HYELLOW, COLOR_HBLUE);
					cout << array[i][j];
					cct_setcolor(COLOR_BLACK, COLOR_WHITE);
					cout << " ";
				}
				else
					cout << " " << array[i][j] << " ";
			}
			else if (num == 2 || num == 3)
			{
				if (array[i][j] == 0)
				{
					cout << " ";
					cct_setcolor(COLOR_HYELLOW, COLOR_HBLUE);
					cout << array[i][j];
					cct_setcolor(COLOR_BLACK, COLOR_WHITE);
					cout << " ";
				}
				else
					cout << " " << array[i][j] << " ";
			}

		}
		cout << endl;
	}
	cout << endl;
}

/***************************************************************************
  �������ƣ�star_check
  ��    �ܣ�����Ƿ�����ͬ������Ԫ��
  ���������
  �� �� ֵ��
  ˵    ������һ�����غ���
***************************************************************************/
int star_check(int mp[MAX_ROWS][MAX_COLS], int row, int col, int x, int y)
{
	int flag[MAX_ROWS][MAX_COLS];
	int mark[MAX_ROWS][MAX_COLS];
	memset(flag, 0, sizeof(flag));
	memset(mark, 0, sizeof(mark));

	int target = mp[x][y];

	star_replace0(mp, flag, mark, row, col, x, y, target);

	int dx[] = { 1, -1, 0, 0 };
	int dy[] = { 0, 0, 1, -1 };
	bool has_adjacent_same = false;

	for (int i = 0; i < 4; i++)
	{
		int nx = x + dx[i];
		int ny = y + dy[i];
		if (nx >= 0 && nx < row && ny >= 0 && ny < col && mark[nx][ny] == 1)
		{
			has_adjacent_same = true;
			break;
		}
	}

	return has_adjacent_same;
}

int star_check(int array[][MAX_COLS], int array_around[][MAX_COLS], int row0, int col0)
{
	array_around[row0][col0] = '*';

	// ��������λ�õ�ƫ����
	int directions[4][2] =
	{
		{-1, 0}, // ��
		{0, -1}, // ��
		{0, 1},  // ��
		{1, 0}   // ��
	};

	// ��������Ԫ��
	for (int i = 0; i < 4; i++)
	{
		int new_row = row0 + directions[i][0];
		int new_column = col0 + directions[i][1];

		if (new_row >= 0 && new_row < 10 && new_column >= 0 && new_column < 10)
		{
			if (array[row0][col0] == array[new_row][new_column] &&
				array_around[new_row][new_column] != '*')
			{
				array_around[new_row][new_column] = '*';
				star_check(array, array_around, new_row, new_column);
			}
		}
	}

	// ͳ�Ʊ�ǵ�Ԫ������
	int count = 0;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (array_around[i][j] == '*')
				count++;
		}
	}

	return (count == 1) ? 0 : 1; // �����Ƿ�������Ԫ��
}


/***************************************************************************
	�������ƣ�move_by_keyboard_and_mouse
	��    �ܣ���¼���ܼ����ƶ�λ��
	���������
	�� �� ֵ��
	˵    ����
***************************************************************************/
int move_by_keyboard_and_mouse(int rows, int cols, const int border, int array[][MAX_COLS], int choice, int total)
{
	int ret, maction;
	int keycode1, keycode2;
	int array_around[MAX_ROWS][MAX_COLS] = { 0 };
	int count = -1;
	bool changed = false;
	int chosen = 0;
	int i_last = 0, j_last = 0;
	int i = 0, j = 0;
	int X = 4, Y = 3;
	int end = 0;

	cct_enable_mouse();
	draw_block(0, 0, border, array, rows, cols, -1);
	cct_setcursor(CURSOR_INVISIBLE);

	cct_gotoxy(0, 2 + 2 + rows * (3 + border));
	cout << "��ͷ��/����ƶ����س���/�������ѡ��Q/�����Ҽ�����";

	while (1)
	{
		int i_now = 0, j_now = 0;
		int X_now, Y_now;
		ret = cct_read_keyboard_and_mouse(X_now, Y_now, maction, keycode1, keycode2);

		if (ret == CCT_MOUSE_EVENT)
		{
			location_trans(-1, i_now, j_now, X_now, Y_now, rows, cols, border);
			if (array[i_now][j_now] == 0) 
				i_now = j_now = -1;
			if (array[i][j] == 0) 
				i = j = -1;

			changed = (i != i_now || j != j_now);

			if (maction == MOUSE_ONLY_MOVED)
			{
				if (check_border(X_now, Y_now, border, rows, cols, array))
				{
					if (changed)
					{
						draw_block(i_now, j_now, border, array, rows, cols, -1);
						if (check_border(X, Y, border, rows, cols, array))
							draw_block(i, j, border, array, rows, cols, 1);
					}
					i_last = i_now;
					j_last = j_now;
				}
				else if (changed)
					draw_block(i, j, border, array, rows, cols, 1);
			}
			else if (maction == MOUSE_RIGHT_BUTTON_CLICK)
				end = 1;
			else if (maction == MOUSE_LEFT_BUTTON_CLICK && check_border(X_now, Y_now, border, rows, cols, array))
			{
				draw_block(i_now, j_now, border, array, rows, cols, -1);
				chosen++;
			}

			i = i_now, j = j_now; 
			X = X_now, Y = Y_now;

			if (!(choice == 'F' && !changed))
				print_title(ret, border, rows, cols, i_now, j_now, array);
		}
		else if (ret == CCT_KEYBOARD_EVENT)
		{
			i_now = i_last;
			j_now = j_last;

			if (keycode1 == 224)
			{
				switch (keycode2)
				{
					case KB_ARROW_UP:
						i_now = find_new_position(i_last, -1, rows, array[j_last]);
						break;
					case KB_ARROW_DOWN:
						i_now = find_new_position(i_last, 1, rows, array[j_last]);
						break;
					case KB_ARROW_LEFT:
						j_now = find_new_position(j_last, -1, cols, array[i_last]);
						break;
					case KB_ARROW_RIGHT:
						j_now = find_new_position(j_last, 1, cols, array[i_last]);
						break;
				}
				draw_block(i_now, j_now, border, array, rows, cols, -1);
				draw_block(i_last, j_last, border, array, rows, cols, 1);
			}
			else if (keycode1 == 13)  // ѡ��
			{
				draw_block(i_last, j_last, border, array, rows, cols, -1);
				chosen++;
				print_title(ret, border, rows, cols, i_last, j_last, array);
				changed = 0;
			}
			else if (keycode1 == 'Q' || keycode1 == 'q')
				end = 1;

			if (!((choice == 'F' && !changed) || chosen))
				print_title(ret, border, rows, cols, i_now, j_now, array);

			i = i_now, j = j_now;//��ֵ�ɵ�����ֵ
			X = X_now, Y = Y_now;
			i_last = i_now;
			j_last = j_now;
		}
		if (chosen)
		{
			if (chosen && (choice == 'D' || choice == 'E'))
				break;
			else if ((choice == 'F' || choice == 'G') && chosen)
			{
				count++;
				if (count == 0) 
				{
					// ��ʾ��ΧԪ��
					int is_around = draw_around(rows, cols, border, array, array_around, choice, i_last, j_last);
					if (choice == 'F')
					{
						cct_gotoxy(0, 4 + rows * (3 + border));
						cout << "��ͷ��/����ƶ�ȡ����ǰѡ�񣬻س���/��������ϳ�";
					}

					if (is_around == 0)
					{
						chosen = 0;
						count = -1; // ������һ��ѭ��
						continue;
					}
					continue;
				}
				else if (count > 0 && changed)
				{
					// ȡ������
					for (int i = 0; i < rows; i++)
					{
						for (int j = 0; j < cols; j++)
							draw_block(i, j, border, array, rows, cols, 1);
					}
					chosen = 0;
					count = -1;
					changed = 0;
					continue;
				}

				if (chosen == 2)
				{
					// �ϳ��߼�
					if (choice == 'F') 
					{
						cct_gotoxy(0, 2 + 2 + rows * (3 + border));
						cout << "ѡ����ɣ��������/�س���ʼ�ϳ�                        ";
						wait_for_action();
					}
					pop_together(rows, cols, border, array, i_last, j_last);

					// �½��߼�
					if (choice == 'F') 
					{
						cct_gotoxy(0, 2 + 2 + rows * (3 + border));
						cout << "�ϳ���ɣ��������/�س���ʼ�½�                        ";
						wait_for_action();
					}
					element_fall(array, array_around, rows, cols, 1, border);
					go_right(array, rows, cols, 1, border);

					if (choice == 'F') 
					{
						cct_gotoxy(0, 2 + 2 + rows * (3 + border));
						cct_setcolor(COLOR_BLACK, COLOR_HYELLOW);
						cout << "���κϳɽ�������C/������������µ�һ�κϳ�             " << endl;
						cct_setcolor();
						wait_for_action('C', true);
						return 0;
					}

					// �ж�ʣ������
					int left = 0;
					if (search_finish(array, left, rows, cols) == 0)
					{
						cct_setcolor(COLOR_BLACK, COLOR_HYELLOW);
						int score_gift = (left >= 10) ? 0 : (10 - left) * 180;
						total += score_gift;
						cct_gotoxy(0, 0);
						cout << "�����÷֣�" << score_gift << "  " << "�ܵ÷֣�" << total << "       ";
						cct_gotoxy(0, 4 + rows * (3 + border));
						cout << "ʣ��" << left << "�����ǣ��޿���������ؽ�����" << endl;
						cct_setcolor();
						cout << "�س�������һ��";
						int xg, yg;
						cct_getxy(xg, yg);
						while (1)
						{
							char ch_g;
							ch_g = _getche();
							if (ch_g == 13)
								break;
							else
							{
								cct_gotoxy(xg, yg);
								putchar(' ');
								cct_gotoxy(xg, yg);
							}
						}
						cout << endl;
						end = 2;
						break;
					}

					// ���µ÷�
					int count1 = 0;
					int score = 0;
					for (int i = 0; i < rows; ++i)
					{
						for (int j = 0; j < cols; ++j)
						{
							if (array_around[i][j] == '*')
							{
								count1++;
							}
						}
					}
					score = count1 * count1 * 5;
					total += score;
					count1 = 0;
					for (int i = 0; i < 10; i++)
					{
						for (int j = 0; j < 10; j++)
						{
							array_around[i][j] = array[i][j];
						}
					}
					copy_array(array, array_around, rows, cols);
					count = -1;
					chosen = 0;

					cct_gotoxy(0, 0);
					cout << "���ε÷֣�" << score << "  " << "�ܷ֣�" << total << "         ";
				}

			}
		}


		if (end)
			break;
	}
	cct_disable_mouse();
	cct_setcursor(CURSOR_VISIBLE_NORMAL);
	return end;
}




/***************************************************************************
	�������ƣ�find_new_position
	��    �ܣ������ڸ������е���λ��
	���������
	�� �� ֵ��
	˵    ����
***************************************************************************/
int find_new_position(int start, int direction, int cols, int rows[])
{
	int j_now = start;
	if (direction < 0)
	{
		for (int j_left = start - 1; j_left >= 0; j_left--)
		{
			if (rows[j_left] != 0)
			{
				j_now = j_left;
				break;
			}
		}
		if (j_now == start)
		{
			for (int j_1 = cols - 1; j_1 >= start; j_1--)
			{
				if (rows[j_1] != 0)
				{
					j_now = j_1;
					break;
				}
			}
		}
	}
	else {
		for (int j_right = start + 1; j_right < cols; j_right++)
		{
			if (rows[j_right] != 0)
			{
				j_now = j_right;
				break;
			}
		}
		if (j_now == start) {
			for (int j_1 = 0; j_1 <= start; j_1++)
			{
				if (rows[j_1] != 0)
				{
					j_now = j_1;
					break;
				}
			}
		}
	}
	return j_now;
}

/***************************************************************************
	�������ƣ�print_title
	��    �ܣ���ʾ��ǰ���λ��/����λ��/��ʾ��Ϣ��
	���������
	�� �� ֵ��
	˵    ����
***************************************************************************/
void print_title(int ret, int border, int rows, int cols, int i, int j, int array[][MAX_COLS])
{
	int X, Y;
	location_trans(1, i, j, X, Y, rows, cols, border);

	// ת���·�״̬�����д�ӡ
	cct_gotoxy(0, 2 + 2 + rows * (3 + border));

	bool valid_position = check_border(X, Y, border, rows, cols, array);

	// ��ӡ��Ϣ
	if (ret == CCT_MOUSE_EVENT || (ret == CCT_KEYBOARD_EVENT && border == 0))
	{
		if (valid_position) {
			if (ret == CCT_MOUSE_EVENT)
				cout << "[��ǰ���] " << (char)(i + 'A') << "��" << (char)(j + '0') << "��                                     ";
			else
				cout << "[��ǰ����] " << (char)(i + 'A') << "��" << (char)(j + '0') << "��                                     ";
		}
		else {
			if (ret == CCT_MOUSE_EVENT)
				cout << "[��ǰ���] λ�÷Ƿ�                                                    ";
			else
				cout << "[��ǰ����] λ�÷Ƿ�                                                    ";
		}
	}
}

/***************************************************************************
	�������ƣ�check_border
	��    �ܣ����ݲ�ͬ��border�ж��Ƿ��ںϷ�����
	���������
	�� �� ֵ��
	˵    ����
***************************************************************************/
bool check_border(int X, int Y, int border, int rows, int cols, int array[][MAX_COLS])
{
	// ����Ϸ�����ķ�Χ
	int y_min = 3;
	int y_max = 3 + rows * (3 + border);
	int x_min = 4;
	int x_max = 4 + (6 + border * 2) * cols;

	// ����Ƿ��ڻ�����Χ��
	if (Y < y_min || Y >= y_max || X < x_min || X >= x_max)
		return false;


	// ��� border Ϊ 1�����ж���ļ��
	if (border == 1)
		if (!((Y - 3) % 4 <= 2 && (X - 4) % 8 <= 5))
			return false;

	// ת�����겢�������ֵ
	int i, j;
	location_trans(-1, i, j, X, Y, rows, cols, border);
	return array[i][j] != 0; // ���ֵ��Ϊ0������ true
}


/***************************************************************************
	�������ƣ�draw_map
	��    �ܣ���ʾ����ȫ��ͼ��
	���������
	�� �� ֵ��
	˵    ����
***************************************************************************/
void draw_map(int rows, int cols, const int border, int array[][MAX_COLS], int choice)
{
	int if_g = 1;
	int total = 0;//�ܵ÷�
	while (if_g)
	{
		if (choice != 'G')
			if_g = 0;
		//��������������cmd���ڿ�ȸ߶�
		fill_array(array, rows, cols, 2);
		cct_setconsoleborder((6 + border * 2) * cols + 8, 3 * (rows + border * 2) + 10, -1, -1);
		cct_cls();
		//��ʾ�ⲿ�߿���
		draw_border(rows, cols, border, choice, 2);
		//��ɫ��
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
				draw_block(i, j, border, array, rows, cols, 1);
		}
		//��ʾ�Ϸ�״̬��
		int columns, lines, a, b;
		cct_getconsoleborder(columns, lines, a, b);
		cct_gotoxy(0, 0);
		cout << "��Ļ��ǰ����Ϊ��" << lines << "��" << columns << "��" << endl;

		int end = 0;
		end = move_by_keyboard_and_mouse(rows, cols, border, array, choice, total);
		if (end == 1)
			break;
	}
}


/***************************************************************************
	�������ƣ�wait_for_action
	��    �ܣ��ȴ��û������ĺ���
	���������
	�� �� ֵ��
	˵    ����
***************************************************************************/
void wait_for_action(char key, bool mouse_click)
{
	while (1)
	{
		int MX, MY, maction, keycode1, keycode2, ret;
		ret = cct_read_keyboard_and_mouse(MX, MY, maction, keycode1, keycode2);
		if ((mouse_click && ret == CCT_MOUSE_EVENT && maction == MOUSE_LEFT_BUTTON_CLICK) || (key && ret == CCT_KEYBOARD_EVENT && (keycode1 == key || keycode1 == (key - 32))))
			break;
		if (!mouse_click && ret == CCT_KEYBOARD_EVENT && keycode1 == 13)
			break;
	}
}

/***************************************************************************
	�������ƣ�go_right
	��    �ܣ��鿴����ȫ�㣬��ȫ���ƶ������Ҳ�
	�� �� ֵ��
	˵    ����
***************************************************************************/
void go_right(int array[][MAX_COLS], int rows, int cols, int have_block, int choice)
{
	int count = 0; // ��¼���ƶ���ȫ���е�����

	for (int j = 0; j < cols - count; j++)
	{
		bool is_all_zero = true;

		// ������Ƿ�ȫΪ��
		for (int i = 0; i < rows; i++)
		{
			if (array[i][j] != 0)
			{
				is_all_zero = false;
				break;
			}
		}

		if (is_all_zero)
		{
			// ��¼ȫ���е�λ��
			int col_to_move = j;
			count++;
			// ��ȫ�����ƶ������Ҳ�
			move_zero_column_to_right(array, rows, cols, col_to_move, have_block, choice);
			j--; // ���¼�鵱ǰ�е�λ��
		}
	}
}

/***************************************************************************
	�������ƣ�go_right
	��    �ܣ��ƶ�ָ���е����Ҳ�ĺ���
	�� �� ֵ��
	˵    ����
***************************************************************************/
void move_zero_column_to_right(int array[MAX_ROWS][MAX_COLS], int rows, int cols, int col_to_move, int have_block, int choice)
{
	for (int m = 0; m < rows; m++)
	{
		for (int n = col_to_move; n < cols - 1; n++)
		{
			array[m][n] = array[m][n + 1];
			array[m][n + 1] = 0;
			if (array[m][n] != 0 && have_block == 1) 
			{
				draw_block(m, n, choice, array, rows, cols, 1);
				Sleep(10);
				draw_block(m, n + 1, choice, array, rows, cols, 0);
				Sleep(10);
			}

		}
	}
}

/***************************************************************************
	�������ƣ�search_finish
	��    �ܣ�������0��Ԫ��->�Ƿ��п����������
	�� �� ֵ��0/1
	˵    ����null
***************************************************************************/
int search_finish(int array[MAX_ROWS][MAX_COLS], int& left, int row, int col)
{
	int is_have = 0;
	for (int i = 0; i < row; i++) 
	{
		for (int j = 0; j < col; j++)
		{
			if (array[i][j] != 0) 
			{
				int array_around[MAX_ROWS][MAX_COLS] = { 0 };
				int is_have_have = 0;
				is_have_have = star_check(array, row, col, i, j);
				if (is_have_have == 1)
					is_have = 1;
				left++;
			}
		}
	}
	if (is_have)
		return 1;
	else
		return 0;

}