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
  �������ƣ�mine_map_all
  ��    �ܣ�ɨ�����в���
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int mine_map_all(CONSOLE_GRAPHICS_INFO* MineSweeper_CGI, int choice)
{
    // ��ʼ�������͵�ͼ
    int mine_map[MAX_ROWS_MINE + 2][MAX_COLS_MINE + 2];
    int if_mine[MAX_ROWS_MINE + 2][MAX_COLS_MINE + 2];
    int mines;
    int remain0;
    char temp[255];
    int rows, cols;

    // ����ѡ�������������͵�����
    switch (choice)
    {
        case 1:
            rows = 9;
            cols = 9;
            mines = 10;
            break;
        case 2:
            rows = 16;
            cols = 16;
            mines = 40;
            break;
        case 3:
            rows = 16;
            cols = 30;
            mines = 99;
            break;
    }

    // ������ʾ�����ɫ����ʽ
    const BLOCK_DISPLAY_INFO bdi_normal[] = {
                {BDI_VALUE_BLANK, COLOR_HWHITE, -1, NULL},  //0����ʾ���ÿո���伴��
                {1, COLOR_WHITE, 1, NULL},
                {2, COLOR_WHITE, 2, NULL},
                {3, COLOR_WHITE, 3, NULL},
                {4, COLOR_WHITE, 4, NULL},
                {5, COLOR_WHITE, 5, NULL},
                {6, COLOR_WHITE, 6, NULL},
                {7, COLOR_WHITE, 7, NULL},
                {8, COLOR_WHITE, 8, NULL},
                {9, COLOR_WHITE, COLOR_HRED, "*"},
                {BDI_VALUE_END, -1, -1, NULL} //�жϽ�������Ϊ-999
    };
    const BLOCK_DISPLAY_INFO bdi_mark[] = {
                {BDI_VALUE_BLANK, COLOR_HWHITE, -1, NULL},  //0����ʾ���ÿո���伴��
                {1, COLOR_HRED, COLOR_RED, "#"},
                {2, COLOR_YELLOW, COLOR_YELLOW, NULL},
                {BDI_VALUE_END, -1, -1, NULL} //�жϽ�������Ϊ-999
    };

    // ��ʼ����Ϸ����
    gmw_init(MineSweeper_CGI);
    gmw_set_rowcol(MineSweeper_CGI, rows, cols);
    gmw_set_font(MineSweeper_CGI, "������", 24);							//����
    gmw_set_ext_rowcol(MineSweeper_CGI, 0, 0, 0, 1000);						//�ұ���30��
    gmw_set_color(MineSweeper_CGI, COLOR_BLACK, COLOR_HWHITE);			//����������ɫ
    gmw_set_frame_default_linetype(MineSweeper_CGI, 4);					//��Ϸ���������ͣ��ᵥ��˫
    gmw_set_frame_color(MineSweeper_CGI, COLOR_HWHITE, COLOR_BLACK);		//��Ϸ��������ɫ
    gmw_set_frame_style(MineSweeper_CGI, 2, 1, true);						//��Ϸ��������ÿ��ɫ���2��1���޷ָ���
    gmw_set_ext_rowcol(MineSweeper_CGI, 0, 3, 0, 10);						
    gmw_set_rowno_switch(MineSweeper_CGI, true);							//��ʾ�к�
    gmw_set_colno_switch(MineSweeper_CGI, true);							//��ʾ�б�
    gmw_set_status_line_switch(MineSweeper_CGI, TOP_STATUS_LINE, true);	//��Ҫ��״̬��
    gmw_set_status_line_switch(MineSweeper_CGI, LOWER_STATUS_LINE, true);	//��Ҫ��״̬��
    // ���ƿ��
    gmw_draw_frame(MineSweeper_CGI);

    // ״̬����ʼ��Ϣ
    gmw_status_line(MineSweeper_CGI, TOP_STATUS_LINE, "ESC�˳�,�ո���ʾʱ��");
    gmw_status_line(MineSweeper_CGI, LOWER_STATUS_LINE, "[��ǰ���]");
    srand(unsigned int(time(0)));

    // ��ʼ����ͼ����
    for (int i = 0; i < MAX_ROWS_MINE + 2; i++)
    {
        for (int j = 0; j < MAX_COLS_MINE + 2; j++)
        {
            if_mine[i][j] = 0; // ���ױ��
            mine_map[i][j] = 0; // δ�򿪱��
        }
    }

    // ������õ���
    for (int i = 0; i < mines; i++)
    {
        int r = 1 + rand() % rows; // �����
        int c = 1 + rand() % cols; // �����
        if (if_mine[r][c] == 9) // ����Ƿ��ѷ��õ���
        {
            i--; // ����
            continue;
        }
        else
            if_mine[r][c] = 9; // ���õ���
    }

    // ����ÿ��������Χ�ĵ�������
    for (int i = 1; i <= rows; i++)
    {
        for (int j = 1; j <= cols; j++)
        {
            if (if_mine[i][j] == 9)
                continue; // ���׸�������
            else
                if_mine[i][j] = check_mine(i, j, mine_map, if_mine);
        }
    }

    // ��ʼ��䣺ȫ���ر�
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            gmw_draw_block(MineSweeper_CGI, i, j, 2, bdi_mark);

    // ��Ϸ��ѭ��
    int MRow, MCol, MAction, keycode1, keycode2;
    int time = 0; // ��¼�Ƿ�Ϊ��һ��
    bool win = false; // �Ƿ�ʤ��
    int remain = mines; // ��¼ʣ�������

    time_t start_time = clock(); // ��¼��ʼʱ��
    while (1) {
        int ret = gmw_read_keyboard_and_mouse(MineSweeper_CGI, MAction, MRow, MCol, keycode1, keycode2, true);
        cct_setcursor(CURSOR_INVISIBLE); // ���ع��
        switch (ret)
        {
            case CCT_MOUSE_EVENT:
                if (MAction == MOUSE_LEFT_BUTTON_CLICK) // �����
                {
                    if (mine_map[MRow + 1][MCol + 1] == 0) {
                        if (if_mine[MRow + 1][MCol + 1] == 9) // ����
                        {
                            mine_map[MRow + 1][MCol + 1] = 1;
                            gmw_draw_block(MineSweeper_CGI, MRow, MCol, if_mine[MRow + 1][MCol + 1], bdi_normal);
                            time_t end_time = clock();
                            sprintf(temp, "��ǰʱ��:%f��,ESC�˳�,�ո���ʾʱ��", double(end_time - start_time) / CLOCKS_PER_SEC);
                            gmw_status_line(MineSweeper_CGI, TOP_STATUS_LINE, temp);
                            gmw_status_line(MineSweeper_CGI, LOWER_STATUS_LINE, "��Ϸ����,������");
                            return -1; // �˳�
                        }

                        // ��δ֪����
                        open_unknown_area(MRow + 1, MCol + 1, rows, cols, mine_map, if_mine);
                        // ������ʾ״̬
                        for (int i = 0; i < rows; i++)
                        {
                            for (int j = 0; j < cols; j++)
                            {
                                if (mine_map[i + 1][j + 1] == 0) // �ر�
                                    gmw_draw_block(MineSweeper_CGI, i, j, 2, bdi_mark);
                                else if (mine_map[i + 1][j + 1] == 1) // ��
                                    gmw_draw_block(MineSweeper_CGI, i, j, if_mine[i + 1][j + 1], bdi_normal);
                                else if (mine_map[i + 1][j + 1] == -1) // ���
                                    gmw_draw_block(MineSweeper_CGI, i, j, 1, bdi_mark);
                            }
                        }
                    }

                    // ����ʣ������
                    remain0 = remain < 0 ? 0 : remain;
                    sprintf(temp, "ʣ������:%d��,ESC�˳�,�ո���ʾʱ��", remain0);
                    gmw_status_line(MineSweeper_CGI, TOP_STATUS_LINE, temp);
                }

                // �����Ҽ����
                if (MAction == MOUSE_RIGHT_BUTTON_CLICK) {
                    if (mine_map[MRow + 1][MCol + 1] == 0) {
                        mine_map[MRow + 1][MCol + 1] = -1; // �����
                        gmw_draw_block(MineSweeper_CGI, MRow, MCol, 1, bdi_mark);
                        remain--;
                    }
                    else if (mine_map[MRow + 1][MCol + 1] == -1) {
                        mine_map[MRow + 1][MCol + 1] = 0; // ȡ�����
                        gmw_draw_block(MineSweeper_CGI, MRow, MCol, 2, bdi_mark);
                        remain++;
                    }

                    // ����ʣ������
                    remain0 = remain < 0 ? 0 : remain;
                    sprintf(temp, "ʣ������:%d��,ESC�˳�,�ո���ʾʱ��", remain0);
                    gmw_status_line(MineSweeper_CGI, TOP_STATUS_LINE, temp);
                }
                break;

            case CCT_KEYBOARD_EVENT:
                if (keycode1 == 27) // ESC�˳�
                    return -1;
                else if (keycode1 == 32) { // �ո���ʾʱ��
                    time_t end_time = clock();
                    sprintf(temp, "��ǰʱ��:%f��,ESC�˳�,�ո���ʾʱ��", double(end_time - start_time) / CLOCKS_PER_SEC);
                    gmw_status_line(MineSweeper_CGI, TOP_STATUS_LINE, temp);
                }
        }

        // ����Ƿ��ʤ
        int cnt = 0;
        for (int i = 1; i <= rows; i++)
        {
            for (int j = 1; j <= cols; j++)
            {
                if (mine_map[i][j] == 1)
                    cnt++; // �����Ѵ򿪵ĸ���
            }
        }
        if (cnt == (rows * cols - mines)) // ʤ������
        { 
            for (int i = 0; i < rows; i++)
            {
                for (int j = 0; j < cols; j++)
                {
                    if (mine_map[i + 1][j + 1] == 0) // �ر�
                        gmw_draw_block(MineSweeper_CGI, i, j, 2, bdi_mark);
                    else if (mine_map[i + 1][j + 1] == 1) // ��
                        gmw_draw_block(MineSweeper_CGI, i, j, if_mine[i + 1][j + 1], bdi_normal);
                    else if (mine_map[i + 1][j + 1] == -1) // ���
                        gmw_draw_block(MineSweeper_CGI, i, j, 1, bdi_mark);
                }
            }

            // ��Ϸʤ������
            time_t end_time = clock(); // ��¼����ʱ��
            double elapsed_time = double(end_time - start_time) / CLOCKS_PER_SEC;
            sprintf(temp, "��ǰʱ��:%f��,ESC�˳�,�ո���ʾʱ��", elapsed_time);
            gmw_status_line(MineSweeper_CGI, TOP_STATUS_LINE, temp);
            gmw_status_line(MineSweeper_CGI, LOWER_STATUS_LINE, ",��Ӯ��", "��Ϸ����");
            return 0; // �˳�
        }
    }
    return 0; // Ĭ�Ϸ���
}


/***************************************************************************
  �������ƣ�check_mine
  ��    �ܣ�����
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int check_mine(int row, int col, int mine_map[MAX_ROWS_MINE + 2][MAX_COLS_MINE + 2], int if_mine[MAX_ROWS_MINE + 2][MAX_COLS_MINE + 2])
{
	int cnt = 0;
	for (int i = row - 1; i <= row + 1; i++) {
		for (int j = col - 1; j <= col + 1; j++) {
			if (i == row && j == col)
				continue;
			if (if_mine[i][j] == 9)
				cnt++;
		}
	}
	return cnt;
}

/***************************************************************************
  �������ƣ�open_unknown_area
  ��    �ܣ���û���׵ĵط�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void open_unknown_area(int row, int col, int row_num, int col_num, int mine_map[MAX_ROWS_MINE + 2][MAX_COLS_MINE + 2], int if_mine[MAX_ROWS_MINE + 2][MAX_COLS_MINE + 2])
{
	// �߽���
	if (row < 1 || row > row_num || col < 1 || col > col_num) {
		return; // ������Χ
	}

	// �򿪵�ǰ����
	mine_map[row][col] = 1;

	// ����ǿշ��飬�ݹ����Χ�ķ���
	if (if_mine[row][col] == 0) {
		for (int i = row - 1; i <= row + 1; i++) {
			for (int j = col - 1; j <= col + 1; j++) {
				// ȷ����λ������Ч��Χ����δ��
				if (mine_map[i][j] == 0) {
					open_unknown_area(i, j, row_num, col_num, mine_map, if_mine);
				}
			}
		}
	}
}