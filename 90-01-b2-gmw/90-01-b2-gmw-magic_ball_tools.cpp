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
	�������ƣ�ball_base_all
	��    �ܣ���ʾ����ȫ��ͼ��
	���������
	�� �� ֵ��
	˵    ����
***************************************************************************/
int ball_base_all(CONSOLE_GRAPHICS_INFO* pMagicBall_CGI, int rows, int cols)
{
	/* ����1-9�������ú�����ʽ��ʾ�ڽ����ϣ�����״̬�� */
	const BLOCK_DISPLAY_INFO bdi_normal[] = {
		{BDI_VALUE_BLANK, -1, -1, "  "},  //0����ʾ���ÿո���伴��
		{1, COLOR_HBLACK, -1, "��"},
		{2, COLOR_YELLOW, -1, "��"},
		{3, COLOR_HGREEN, -1, "��"},
		{4, COLOR_HCYAN, -1, "��"},
		{5, COLOR_HRED, -1, "��"},
		{6, COLOR_HPINK, -1, "��"},
		{7, COLOR_HYELLOW, -1, "��"},
		{8, COLOR_CYAN, -1, "��"},
		{9, COLOR_WHITE, -1, "��"},
		{BDI_VALUE_END, -1, -1, NULL} //�жϽ�������Ϊ-999
	};
	const BLOCK_DISPLAY_INFO bdi_normal_choose[] = {
		{BDI_VALUE_BLANK, -1, -1, "  "},  //0����ʾ���ÿո���伴��
		{1, COLOR_HBLACK, 15, "��"},
		{2, COLOR_YELLOW, 15, "��"},
		{3, COLOR_HGREEN, 15, "��"},
		{4, COLOR_HCYAN, 15, "��"},
		{5, COLOR_HRED, 15, "��"},
		{6, COLOR_HPINK, 15, "��"},
		{7, COLOR_HYELLOW, 15, "��"},
		{8, COLOR_CYAN, 15, "��"},
		{9, COLOR_WHITE, 15, "��"},
		{BDI_VALUE_END, -1, -1, NULL} //�жϽ�������Ϊ-999
	};
	/* ����1-9�������ú�����ʽ��ʾ�ڽ����ϣ�ѡ��״̬�� */
	const BLOCK_DISPLAY_INFO bdi_selected[] = {
		{BDI_VALUE_BLANK, -1, -1, "  "},  //�հ�
		{1, COLOR_HBLACK, -1, "��"},
		{2, COLOR_YELLOW, -1, "��"},
		{3, COLOR_HGREEN, -1, "��"},
		{4, COLOR_HCYAN, -1, "��"},
		{5, COLOR_HRED, -1, "��"},
		{6, COLOR_HPINK, -1, "��"},
		{7, COLOR_HYELLOW, -1, "��"},
		{8, COLOR_CYAN, -1, "��"},
		{9, COLOR_WHITE, -1, "��"},
		{BDI_VALUE_END, -1, -1, NULL} //�жϽ�������Ϊ-999
	};
	/* ����1-9�������ú�����ʽ��ʾ�ڽ����ϣ���������ʾ״̬�� */
	const BLOCK_DISPLAY_INFO bdi_prompt[] = {
		{BDI_VALUE_BLANK, -1, -1, "  "},  //�հ�
		{1, COLOR_HBLACK, -1, "��"},
		{2, COLOR_YELLOW, -1, "��"},
		{3, COLOR_HGREEN, -1, "��"},
		{4, COLOR_HCYAN, -1, "��"},
		{5, COLOR_HRED, -1, "��"},
		{6, COLOR_HPINK, -1, "��"},
		{7, COLOR_HYELLOW, -1, "��"},
		{8, COLOR_CYAN, -1, "��"},
		{9, COLOR_WHITE, -1, "��"},
		{BDI_VALUE_END, -1, -1, NULL} //�жϽ�������Ϊ-999
	};
	/* ����1-9�������ú�����ʽ��ʾ�ڽ����ϣ���������ʾ״̬�� */
	const BLOCK_DISPLAY_INFO bdi_prompt_choose[] = {
		{BDI_VALUE_BLANK, -1, -1, "  "},  //�հ�
		{1, COLOR_HBLACK, 15, "��"},
		{2, COLOR_YELLOW, 15, "��"},
		{3, COLOR_HGREEN, 15, "��"},
		{4, COLOR_HCYAN, 15, "��"},
		{5, COLOR_HRED, 15, "��"},
		{6, COLOR_HPINK, 15, "��"},
		{7, COLOR_HYELLOW, 15, "��"},
		{8, COLOR_CYAN, 15, "��"},
		{9, COLOR_WHITE, 15, "��"},
		{BDI_VALUE_END, -1, -1, NULL} //�жϽ�������Ϊ-999
	};
	/* ����1-9�������ú�����ʽ��ʾ�ڽ����ϣ���ը/����״̬�� */
	const BLOCK_DISPLAY_INFO bdi_exploded[] = {
		{BDI_VALUE_BLANK, -1, -1, "  "},  //�հ�
		{1, COLOR_HBLACK, -1, "��"},
		{2, COLOR_YELLOW, -1, "��"},
		{3, COLOR_HGREEN, -1, "��"},
		{4, COLOR_HCYAN, -1, "��"},
		{5, COLOR_HRED, -1, "��"},
		{6, COLOR_HPINK, -1, "��"},
		{7, COLOR_HYELLOW, -1, "��"},
		{8, COLOR_CYAN, -1, "��"},
		{9, COLOR_WHITE, -1, "��"},
		{BDI_VALUE_END, -1, -1, NULL} //�жϽ�������Ϊ-999
	};

	srand(static_cast<unsigned int>(time(nullptr)));
	int array[MAX_ROWS][MAX_COLS];   //�������Ϊ�����
	fill_array(array, rows, cols, 1);
	gmw_init(pMagicBall_CGI);
	gmw_set_font(pMagicBall_CGI, "������", 32);							//����
	gmw_set_ext_rowcol(pMagicBall_CGI, 0, 0, 0, 30);						//�ұ���30��
	gmw_set_color(pMagicBall_CGI, COLOR_BLACK, COLOR_HWHITE);			//����������ɫ
	gmw_set_frame_default_linetype(pMagicBall_CGI, 4);					//��Ϸ���������ͣ��ᵥ��˫
	gmw_set_frame_color(pMagicBall_CGI, COLOR_HWHITE, COLOR_BLACK);		//��Ϸ��������ɫ
	
	gmw_set_frame_style(pMagicBall_CGI, 2, 1, false);						//��Ϸ��������ÿ��ɫ���2��1���޷ָ���
	gmw_set_ext_rowcol(pMagicBall_CGI, 0, 3, 0, 10);						
	gmw_set_rowno_switch(pMagicBall_CGI, true);							//��ʾ�к�
	gmw_set_colno_switch(pMagicBall_CGI, true);							//��ʾ�б�
	gmw_set_status_line_switch(pMagicBall_CGI, TOP_STATUS_LINE, true);	//��Ҫ��״̬��
	gmw_set_status_line_switch(pMagicBall_CGI, LOWER_STATUS_LINE, true);	//��Ҫ��״̬��

	char temp[256];
	int i, j;
	int directions[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };   //��������
	/* ��row/col��ֵ������Ϸ���������� */
	gmw_set_rowcol(pMagicBall_CGI, rows, cols);

	/* ��ʾ��� */

	gmw_draw_frame(pMagicBall_CGI);

	/* ��״̬����ʾ���� */

	sprintf(temp, "��Ļ��%d�� %d��", pMagicBall_CGI->lines, pMagicBall_CGI->cols);
	cct_showstr(0, 0, temp, 0, 15);

	/* ���ڲ�����չ�ֵ���Ļ�� */
	for (i = 0; i < rows; i++)
		for (j = 0; j < cols; j++) 
				gmw_draw_block(pMagicBall_CGI, i, j, array[i][j], bdi_normal);
	int arrayCopy[MAX_ROWS][MAX_COLS];
	int arrayCopy0[MAX_ROWS][MAX_COLS];
	int arrayCopy1[MAX_ROWS][MAX_COLS];

    copy_array(array, arrayCopy, rows, cols);
	copy_array(array, arrayCopy0, rows, cols);
	while (base_check1(arrayCopy, rows, cols)) 
	{
		for (i = 0; i < rows; i++)
			for (j = 0; j < cols; j++)
				gmw_draw_block(pMagicBall_CGI, i, j, arrayCopy[i][j], bdi_normal);
		// ��һ������ǿ������Ŀ�
		for (int i = 0; i < rows; i++) 
			for (int j = 0; j < cols; j++)
				if (base_check0(arrayCopy0, i, j, rows, cols)) 
					gmw_draw_block(pMagicBall_CGI, i, j, arrayCopy[i][j], bdi_selected);

		cct_setcursor(CURSOR_INVISIBLE);

		// �ڶ�����ִ��������������������Ϊ0
		copy_array(arrayCopy, arrayCopy1, rows, cols);
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++) 
			{
				if (base_check0(arrayCopy1, i, j, rows, cols)) 
				{
					for (int k = 0; k < 5; k++) 
					{
						gmw_draw_block(pMagicBall_CGI, i, j, arrayCopy[i][j], bdi_exploded);
						Sleep(50);
						gmw_draw_block(pMagicBall_CGI, i, j, 0, bdi_normal); // 0�ǿհ�
						Sleep(50);
					}
					arrayCopy[i][j] = 0; // ����Ϊ0
				}
			}
		}

		// ��������������Ŀ�����
		for (int j = 0; j < cols; j++) 
		{
			int targetRow = rows - 1; // �ӵײ���ʼ��Ŀ����
			for (int i = rows - 1; i >= 0; --i) 
			{
				if (arrayCopy[i][j] != 0) // �ҵ���0��
				{ 
					// ���Ŀ���в����ڵ�ǰ�У����ƶ�
					if (i != targetRow) 
					{
						gmw_move_block(pMagicBall_CGI, i, j, arrayCopy[i][j], 0, bdi_normal, UP_TO_DOWN, targetRow - i);
						Sleep(50);
					}
					arrayCopy[targetRow][j] = arrayCopy[i][j]; // ����Ŀ��λ��
					if (targetRow != i) 
						arrayCopy[i][j] = 0; // ��ԭλ������Ϊ0
					targetRow--; // �ƶ�Ŀ���е���һ��
				}
			}
		}

		// ���Ĳ��������ֵ
		srand(static_cast<unsigned int>(time(nullptr))); // ��ʼ�����������
		for (int i = 0; i < rows; i++) 
		{
			for (int j = 0; j < cols; j++) {

				if (arrayCopy[i][j] == 0) { // �����0���������ֵ
					arrayCopy[i][j] = (rand() % 9) + 1; // ���1��9֮������ֵ
					gmw_draw_block(pMagicBall_CGI, i, j, arrayCopy[i][j], bdi_normal); // �����¿�
					Sleep(50);
				}
			}
		}
		copy_array(arrayCopy, arrayCopy0, rows, cols);
	}

	for (i = 0; i < rows; i++)
		for (j = 0; j < cols; j++)
		{
			if (base_check2(arrayCopy, directions, i, j, rows, cols))
				gmw_draw_block(pMagicBall_CGI, i, j, arrayCopy[i][j], bdi_prompt);
			else
				gmw_draw_block(pMagicBall_CGI, i, j, arrayCopy[i][j], bdi_normal);
		}
	int num0 = 0;
	int score_all = 0, score = 0;
	int loop = 1;
	int maction, old_mrow, old_mcol, mrow = -1, mcol = -1;
	int keycode1, keycode2;
	int ret;
	int i1 = 0, j1 = 0, i2 = 0, j2 = 0;
	int count0 = 0;
	cct_setcursor(CURSOR_INVISIBLE);
	while (loop) {
		count0 = 0;
		score = 0;
		old_mrow = mrow;
		old_mcol = mcol;
		ret = gmw_read_keyboard_and_mouse(pMagicBall_CGI, maction, mrow, mcol, keycode1, keycode2);

		if (ret == CCT_MOUSE_EVENT) 
		{
			if (maction == MOUSE_ONLY_MOVED) 
			{
				/* ��ʱ��mrow��mcol�϶����ղŲ�ͬ */

				/* ��һ��ɫ��仯��color_linez��������λ�ö���ɫ�飬�˴�ֱ����3���棩����ͬ��Ϸ�˴���ͬ�������Ǹ���ʾ */

				/* ԭɫ��������ʾ */
				if (old_mrow >= 0 && old_mcol >= 0)
					if (base_check2(arrayCopy, directions, old_mrow, old_mcol, rows, cols))
						gmw_draw_block(pMagicBall_CGI, old_mrow, old_mcol, arrayCopy[old_mrow][old_mcol], bdi_prompt);
					else
						gmw_draw_block(pMagicBall_CGI, old_mrow, old_mcol, arrayCopy[old_mrow][old_mcol], bdi_normal);

				/* ��ɫ�����ԣ���Ϊ��������ɫ�鶼��ֵ���˴���3����� */
				if (base_check2(arrayCopy, directions, mrow, mcol, rows, cols))
					gmw_draw_block(pMagicBall_CGI, mrow, mcol, arrayCopy[mrow][mcol], bdi_prompt_choose);
				else
					gmw_draw_block(pMagicBall_CGI, mrow, mcol, arrayCopy[mrow][mcol], bdi_normal_choose);

			}
			else if (maction == MOUSE_RIGHT_BUTTON_CLICK) 
			{
				/* ��״̬����ʾ���� */
				gmw_status_line(pMagicBall_CGI, LOWER_STATUS_LINE, "[�����Ҽ�]", NULL);
				loop = 0;
			}
			else 
			{
				char temp0[256];
				num0++;
				if (base_check2(arrayCopy, directions, mrow, mcol, rows, cols))
				{
					sprintf(temp0, "[��ǰѡ��] %c��%d��", char('A' + mrow), mcol); //δ����mrow����26��mcol����99�������������Ҫ�������д���
					gmw_status_line(pMagicBall_CGI, LOWER_STATUS_LINE, temp0);
					if (num0 % 2 == 1)
					{
					    i1 = mrow;
					    j1 = mcol;
					}
					if (num0 % 2 == 0)
					{
						i2 = mrow;
						j2 = mcol;
						int tmp0;
						tmp0 = arrayCopy[i1][j1];
						arrayCopy[i1][j1] = arrayCopy[i2][j2];
						arrayCopy[i2][j2] = tmp0;
						if (base_check0(arrayCopy, i1, j1, rows, cols) || base_check0(arrayCopy, i2, j2, rows, cols))
						{

							for (i = 0; i < rows; i++)
								for (j = 0; j < cols; j++)
									gmw_draw_block(pMagicBall_CGI, i, j, arrayCopy[i][j], bdi_normal);
							sprintf(temp, "����%c��%d��<=>%c��%d��", char(i1 + 'A'), j1, char(i2 + 'A'), j2);
							gmw_status_line(pMagicBall_CGI, LOWER_STATUS_LINE, temp, NULL);
							

							while (base_check1(arrayCopy, rows, cols))
							{

								// ��һ������ǿ������Ŀ�
								for (int i = 0; i < rows; i++) 
									for (int j = 0; j < cols; j++) 
										if (base_check0(arrayCopy, i, j, rows, cols)) 
											gmw_draw_block(pMagicBall_CGI, i, j, arrayCopy[i][j], bdi_selected);
											Sleep(100);
								Sleep(100);
								cct_setcursor(CURSOR_INVISIBLE);

								// �ڶ�����ִ��������������������Ϊ0
								copy_array(arrayCopy, arrayCopy1, rows, cols);
								for (int i = 0; i < rows; i++)
								{
									for (int j = 0; j < cols; j++) 
									{
										if (base_check0(arrayCopy1, i, j, rows, cols)) 
										{
											for (int k = 0; k < 5; k++) 
											{
												gmw_draw_block(pMagicBall_CGI, i, j, arrayCopy[i][j], bdi_exploded);
												Sleep(50);
												gmw_draw_block(pMagicBall_CGI, i, j, 0, bdi_normal); // 0�ǿհ�
												Sleep(50);
											}
											arrayCopy[i][j] = 0; // ����Ϊ0
										}
									}
								}

								// ��������������Ŀ�����
								for (int j = 0; j < cols; j++) 
								{
									int targetRow = rows - 1; // �ӵײ���ʼ��Ŀ����
									for (int i = rows - 1; i >= 0; --i) 
									{
										if (arrayCopy[i][j] != 0)  // �ҵ���0��
										{
											// ���Ŀ���в����ڵ�ǰ�У����ƶ�
											if (i != targetRow) 
											{
												gmw_move_block(pMagicBall_CGI, i, j, arrayCopy[i][j], 0, bdi_normal, UP_TO_DOWN, targetRow - i);
												Sleep(50);
											}
											arrayCopy[targetRow][j] = arrayCopy[i][j]; // ����Ŀ��λ��
											if (targetRow != i) 
												arrayCopy[i][j] = 0; // ��ԭλ������Ϊ0
											targetRow--; // �ƶ�Ŀ���е���һ��
										}
									}
								}

								// ���Ĳ��������ֵ
								srand(static_cast<unsigned int>(time(nullptr))); // ��ʼ�����������
								for (int i = 0; i < rows; i++) 
								{
									for (int j = 0; j < cols; j++) 
									{
										if (arrayCopy[i][j] == 0) // �����0���������ֵ
										{ 
											score++;
											arrayCopy[i][j] = (rand() % 9) + 1; // ���1��9֮������ֵ
											gmw_draw_block(pMagicBall_CGI, i, j, arrayCopy[i][j], bdi_normal); // �����¿�
											Sleep(50);
										}
									}
								}
								copy_array(arrayCopy, arrayCopy0, rows, cols);
							}
							score_all += score;
							sprintf(temp, "��Ļ��%d�� %d�� (��ǰ����:%d)", pMagicBall_CGI->lines, pMagicBall_CGI->cols, score_all);
							cct_showstr(0, 0, temp, 0, 15);
							for (i = 0; i < rows; i++)
								for (j = 0; j < cols; j++)
								{
									if (base_check2(arrayCopy, directions, i, j, rows, cols))
										gmw_draw_block(pMagicBall_CGI, i, j, arrayCopy[i][j], bdi_prompt);
									else
										gmw_draw_block(pMagicBall_CGI, i, j, arrayCopy[i][j], bdi_normal);
								}
							for (int i = 0; i < rows; i++)
							{
								for (int j = 0; j < cols; j++)
								{
									if (base_check2(arrayCopy0, directions, i, j, rows, cols))
									{
										count0++; // ����ҵ�����������λ�ã����Ӽ���
									}
								}
							}

							if (count0 == 0) 
								loop = 0; // ���û���ҵ��κ�����������λ�ã��˳�ѭ��
					    }
						else
						{
							sprintf(temp, "���ܽ���%c��%d��<=>%c��%d��", char(i1 + 'A'), j1, char(i2 + 'A'), j2);
							gmw_status_line(pMagicBall_CGI, LOWER_STATUS_LINE, temp, NULL);
							num0 = 0;
						}
					
					}

				}
				else
				{
					i1 = mrow;
					j1 = mcol;
					sprintf(temp, "����ѡ��%c��%d��", char(i1 + 'A'), j1);
					gmw_status_line(pMagicBall_CGI, LOWER_STATUS_LINE, temp, NULL);
				}

				
			}
		}

	}
	sprintf(temp, "���շ���:%d", score_all);
	gmw_status_line(pMagicBall_CGI, LOWER_STATUS_LINE, temp, "�޿�������, ��Ϸ����!");
	Sleep(300);
	gmw_status_line(pMagicBall_CGI, LOWER_STATUS_LINE, "��С�������������End����... ", "");
	return 0;
}
