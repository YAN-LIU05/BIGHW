/* 2352018 ������ ���� */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <climits>
#include <conio.h>
#include <iomanip>
#include <windows.h>
#include <sstream>
#include "../include/cmd_console_tools.h"
#include "../include/cmd_gmw_tools.h"
using namespace std;

/* --------------------------------------------------
		�˴����Ը�����Ҫ�ľ�̬ȫ�ֱ������������٣����û�У�����̬ȫ��ֻ������/�궨�壨�������ޣ���
   -------------------------------------------------- */


   /* --------------------------------------------------
		   �˴����Ը�����Ҫ���ڲ��������ߺ���
		   1�����������ޣ�����Ϊ gmw_inner_*
		   2����������
		   3��������static������ȷ��ֻ�ڱ�Դ�ļ���ʹ��
	  -------------------------------------------------- */
	  /***************************************************************************
		�������ƣ�
		��    �ܣ������ܵĳߴ�
		���������CONSOLE_GRAPHICS_INFO* const pCGI������ṹָ��
		�� �� ֵ����
		˵    �������ݿ�ܵ�ɫ��ߴ�ͷָ������ü����ܵ��ܿ�Ⱥ��ܸ߶ȡ�
	  ***************************************************************************/
static void gmw_inner_calculate_frame_size(CONSOLE_GRAPHICS_INFO* const pCGI)
{
	if (pCGI->CFI.separator)
	{
		// ����ܿ��
		pCGI->CFI.bwidth = (pCGI->CFI.block_width + pCGI->CFI.separator * 2) * pCGI->col_num + 2;
		// ����ܸ߶�
		pCGI->CFI.bhigh = (pCGI->CFI.block_high + pCGI->CFI.separator) * pCGI->row_num + 1;
	}
	else
	{
		pCGI->CFI.bwidth = pCGI->CFI.block_width * pCGI->col_num + 4; // 2*2
		pCGI->CFI.bhigh = pCGI->CFI.block_high * pCGI->row_num + 2; // 1*2
	}
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ������ܵ���ʼλ��
  ���������CONSOLE_GRAPHICS_INFO* const pCGI������ṹָ��
  �� �� ֵ����
  ˵    ���������ⲿ��������״̬����Ϣ�����ܵ���ʼ���꣨x, y����
***************************************************************************/
static void gmw_inner_calculate_start_positions(CONSOLE_GRAPHICS_INFO* const pCGI)
{
	// �����ʼx����
	pCGI->start_x = pCGI->extern_left_cols + 2 * pCGI->draw_frame_with_row_no;
	// �����ʼy����
	pCGI->start_y = pCGI->extern_up_lines + pCGI->top_status_line + pCGI->draw_frame_with_col_no;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�������Ļ���ܳߴ�
  ���������CONSOLE_GRAPHICS_INFO* const pCGI������ṹָ��
  �� �� ֵ����
  ˵    ���������ⲿ����������ܳߴ��״̬����Ϣ������Ļ���ܿ�Ⱥ͸߶ȡ�
***************************************************************************/
static void gmw_inner_calculate_screen_size(CONSOLE_GRAPHICS_INFO* const pCGI)
{
	// ��Ļ�ܸ߶�
	pCGI->lines = pCGI->extern_up_lines + pCGI->top_status_line + pCGI->draw_frame_with_col_no +
		pCGI->CFI.bhigh + pCGI->lower_status_line + pCGI->extern_down_lines + 4;
	// ��Ļ�ܿ��
	pCGI->cols = pCGI->extern_left_cols + 2 * pCGI->draw_frame_with_row_no +
		pCGI->CFI.bwidth + pCGI->extern_right_cols + 1;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�����״̬������ʼλ��
  ���������CONSOLE_GRAPHICS_INFO* const pCGI������ṹָ��
  �� �� ֵ����
  ˵    ���������ⲿ��������״̬����Ϣ��������״̬������ʼ���꣨x, y����
***************************************************************************/
static void gmw_inner_calculate_status_line_positions(CONSOLE_GRAPHICS_INFO* const pCGI)
{
	// ��״̬����ʼx����
	pCGI->SLI.top_start_x = pCGI->extern_left_cols;
	// ��״̬����ʼy����
	pCGI->SLI.top_start_y = pCGI->extern_up_lines;
	// ��״̬����ʼx����
	pCGI->SLI.lower_start_x = pCGI->extern_left_cols;
	// ��״̬����ʼy����
	pCGI->SLI.lower_start_y = pCGI->extern_up_lines + pCGI->top_status_line + pCGI->draw_frame_with_col_no + pCGI->CFI.bhigh;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�����������ز���
  ���������CONSOLE_GRAPHICS_INFO* const pCGI������ṹָ��
  �� �� ֵ����
  ˵    �������ø������㺯���������ܳߴ硢��ʼλ�á���Ļ�ߴ��״̬��λ�õȡ�
***************************************************************************/
static void gmw_inner_calculate_all(CONSOLE_GRAPHICS_INFO* const pCGI)
{
	gmw_inner_calculate_frame_size(pCGI);
	gmw_inner_calculate_start_positions(pCGI);
	gmw_inner_calculate_screen_size(pCGI);
	gmw_inner_calculate_status_line_positions(pCGI);
}

/***************************************************************************
  �������ƣ�
  ���ܣ������ַ���ĩβ���ܴ��ڵ������ַ��ض�����
  ���������char* s - �����ַ���ָ��
  ����ֵ����
  ˵��������ַ��������һ���ַ��������ַ���ǰ�벿�֣�����ضϣ�
		�Ա������롣
***************************************************************************/
static void gmw_inner_dealwith_chinese_char(char* s)
{
	char* last = s;
	// �����ҵ��ַ�����ĩβ
	while (*last != 0) last++;
	last = last - 1; // ָ�����һ���ַ�

	// ������һ���ַ���ASCII�ַ������账��
	if (*last > 0) return;

	char* ps = s;
	// ����ַ����е�ÿ���ַ�
	while (ps < last)
	{
		// �����ASCII�ַ����ƶ�����һ���ַ�
		if (*ps > 0) ps++;
		// ����������ַ������������ֽ�
		else if (*ps < 0) ps += 2;
	}

	// ���ָ���ѳ�������ַ���˵���޽ض�
	if (ps > last) return;

	// �����һ���ַ�����Ϊ���������ض��ַ���
	*last = 0;
}


/***************************************************************************
  �������ƣ�
  ��    �ܣ����ַ���s2���Ƶ�s1��,����s1��ԭ����,����ʱ����\0
  ���������
  �� �� ֵ���µ�s1
  ˵    ����
***************************************************************************/
static char* gmw_inner_strcpy(char* s1, const char* s2)
{
	/* ע�⣺�����ڲ��������κ���ʽ�����飨������̬���飩 */
	if (s1 == NULL)
		return s1;

	char* s = s1;

	if (s2 == NULL)
		*s = '\0';
	else
	{
		for (; *s2 != '\0'; s++, s2++)
			*s = *s2;
		*s = '\0';
	}

	return s1;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ��Ƚ��ַ���s1��s2�Ĵ�С,Ӣ����ĸҪ���ִ�Сд
  ���������
  �� �� ֵ�����Ϊ0,������Ϊ��1��������ַ���ASCII��ֵ
  ˵    ����
***************************************************************************/
static int gmw_inner_strcmp(const char* s1, const char* s2)
{
	/* ע�⣺�����ڲ��������κ���ʽ�����飨������̬���飩 */
	if (s1 == NULL || s2 == NULL)
	{
		int t = (s1 != NULL) - (s2 != NULL);
		return t;
	}

	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}

	return *s1 - *s2;
}
/***************************************************************************
  �������ƣ�
  ��    �ܣ����ַ���s2��ǰ1en���ַ����Ƶ�s1��,����ʱ����\0,��1en��s2�ĳ��ȴ�,����s2���ȸ��ַ�����(����\0)
  ���������
  �� �� ֵ���µ�s1
  ˵    ����
***************************************************************************/
static char* gmw_inner_strncpy(char* s1, const char* s2, const int len)
{
	/* ע�⣺�����ڲ��������κ���ʽ�����飨������̬���飩 */
	if (s1 == NULL || s2 == NULL)
	{
		return s1;
	}

	char* s_1 = s1;
	const char* s_2 = s2 + len;
	if (size_t(len) > strlen(s2) + 1)
	{
		while (*s2 != '\0')
		{
			*s_1 = *s2;
			s_1++;
			s2++;
		}
	}
	else
	{
		while (s2 < s_2)
		{
			*s_1 = *s2;
			s_1++;
			s2++;
		}
	}
	return s1;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�����״̬������ʾ״̬
  ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
			const int type						��״̬�����ͣ���/�£�
			const bool on_off					��true - ��Ҫ��false - ����Ҫ
  �� �� ֵ��0 - �ɹ���-1 - ʧ��
***************************************************************************/
static int gmw_inner_set_status_line(CONSOLE_GRAPHICS_INFO* const pCGI, const int type, const bool on_off)
{
	if (type == TOP_STATUS_LINE)
	{
		pCGI->SLI.is_top_status_line = on_off;
		pCGI->top_status_line = on_off;
	}
	else if (type == LOWER_STATUS_LINE)
	{
		pCGI->SLI.is_lower_status_line = on_off;
		pCGI->lower_status_line = on_off;
	}
	else
		return -1; // ��Ч��״̬������
	return 0; // �ɹ�
}
/***************************************************************************
  �������ƣ�
  ��    �ܣ�����״̬����ɫ����������ɫ��
  ���������int* color_ptr		��ָ��Ҫ���õ���ɫ����
			const int color		����ɫֵ
			const int default_color��Ĭ����ɫֵ
***************************************************************************/
static void gmw_inner_set_normal_bg_color(int* color_ptr, const int color, const int default_color)
{
	if (color == -1)
		*color_ptr = default_color;
	else
		*color_ptr = color;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�����״̬����ɫ������ǰ��ɫ��
  ���������int* color_ptr		��ָ��Ҫ���õ���ɫ����
			const int color		����ɫֵ
			const int default_color��Ĭ����ɫֵ
***************************************************************************/
static void gmw_inner_set_normal_fg_color(int* color_ptr, const int color, const int default_color)
{
	if (color == -1)
		*color_ptr = default_color;
	else
		*color_ptr = color;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�����������ɫ������
  ���������CONSOLE_GRAPHICS_INFO *const pCGI������ṹָ��
		   const int bgcolor				���������ڱ���ɫ
		   const int fgcolor				����������ǰ��ɫ
  �� �� ֵ��
  ˵    ����������ɫ������ķ�װ
***************************************************************************/
static void gmw_inner_set_color_and_font(CONSOLE_GRAPHICS_INFO* const pCGI, const int bgcolor, const int fgcolor)
{
	gmw_set_color(pCGI, bgcolor, fgcolor);
	gmw_set_font(pCGI);
	gmw_set_ext_rowcol(pCGI);
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���������ܵĲ���
  ���������CONSOLE_GRAPHICS_INFO *const pCGI������ṹָ��
  �� �� ֵ��
  ˵    ������������ܵ����͡�������ɫ��
***************************************************************************/
static void gmw_inner_set_frame_parameters(CONSOLE_GRAPHICS_INFO* const pCGI)
{
	gmw_set_frame_default_linetype(pCGI, 1);
	gmw_set_frame_style(pCGI);
	gmw_set_frame_color(pCGI);
	gmw_set_block_default_linetype(pCGI, 1);
	gmw_set_block_border_switch(pCGI);
	gmw_set_delay(pCGI, DELAY_OF_DRAW_FRAME, 0);
	gmw_set_delay(pCGI, DELAY_OF_DRAW_BLOCK, 0);
	gmw_set_delay(pCGI, DELAY_OF_BLOCK_MOVED, BLOCK_MOVED_DELAY_MS);
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�����״̬���Ĳ���
  ���������CONSOLE_GRAPHICS_INFO *const pCGI������ṹָ��
  �� �� ֵ��
  ˵    ��������״̬������ʾ״̬����ɫ
***************************************************************************/
static void gmw_inner_set_status_line_parameters(CONSOLE_GRAPHICS_INFO* const pCGI)
{
	gmw_set_status_line_switch(pCGI, TOP_STATUS_LINE, true);
	gmw_set_status_line_switch(pCGI, LOWER_STATUS_LINE, true);
	gmw_set_status_line_color(pCGI, TOP_STATUS_LINE);
	gmw_set_status_line_color(pCGI, LOWER_STATUS_LINE);
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ��������к���ʾ
  ���������CONSOLE_GRAPHICS_INFO *const pCGI������ṹָ��
  �� �� ֵ��
  ˵    ���������кź��кŵ���ʾ״̬
***************************************************************************/
static void gmw_inner_set_row_col_display(CONSOLE_GRAPHICS_INFO* const pCGI)
{
	gmw_set_rowno_switch(pCGI);
	gmw_set_colno_switch(pCGI);
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ������к�
  ���������CONSOLE_GRAPHICS_INFO *const pCGI������ṹָ��
  �� �� ֵ��
  ˵    ����
***************************************************************************/
static void gmw_inner_draw_column_numbers(const CONSOLE_GRAPHICS_INFO* const pCGI)
{
	cct_gotoxy(pCGI->start_x + 1 + pCGI->CFI.block_width / 2, pCGI->start_y - 1);
	for (int i = 0; i < pCGI->col_num; i++)
	{
		if (i < 100)
			cout << setiosflags(ios::left)
			<< setw(2 * pCGI->CFI.separator + pCGI->CFI.block_width) << i
			<< resetiosflags(ios::left);
		else
			cout << setiosflags(ios::left)
			<< setw(2 * pCGI->CFI.separator + pCGI->CFI.block_width) << "**"
			<< resetiosflags(ios::left);
		Sleep(pCGI->delay_of_draw_frame);
	}
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ������к�
  ���������CONSOLE_GRAPHICS_INFO *const pCGI������ṹָ��
  �� �� ֵ��
  ˵    ����
***************************************************************************/
static void gmw_inner_draw_row_numbers(const CONSOLE_GRAPHICS_INFO* const pCGI)
{
	for (int i = 0; i < pCGI->row_num; i++)
	{
		cct_gotoxy(pCGI->extern_left_cols, pCGI->start_y + pCGI->CFI.separator +
			pCGI->CFI.block_high / 2 + i * (1 * pCGI->CFI.separator + pCGI->CFI.block_high));
		if (i < 26)
			cout << char(i + 'A') << ' ';
		else if (i < 52)
			cout << char(i - 26 + 'a') << ' ';
		else
			cout << '*' << ' ';
		Sleep(pCGI->delay_of_draw_frame);
	}
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ��������еĿ��Ԫ��
  ���������const CONSOLE_GRAPHICS_INFO *const pCGI������ṹָ��
			int j����ǰ������
  �� �� ֵ����
***************************************************************************/
static void gmw_inner_draw_top_line(const CONSOLE_GRAPHICS_INFO* const pCGI, int j)
{
	if (j == 0)  // ���Ͻ�
		cout << pCGI->CFI.top_left << " ";
	else if (j == pCGI->CFI.bwidth / 2 - 1)  // ���Ͻ�
		cout << pCGI->CFI.top_right << " ";
	else if (j % (pCGI->CFI.block_width / 2 + 1) == 0) // �Ϸֽ�
		cout << pCGI->CFI.h_top_separator << " ";
	else  // ˮƽ��
		cout << pCGI->CFI.h_normal << " ";
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�����ĩ�еĿ��Ԫ��
  ���������const CONSOLE_GRAPHICS_INFO *const pCGI������ṹָ��
			int j����ǰ������
  �� �� ֵ����
***************************************************************************/
static void gmw_inner_draw_bottom_line(const CONSOLE_GRAPHICS_INFO* const pCGI, int j)
{
	if (j == 0)  // ���½�
		cout << pCGI->CFI.lower_left << " ";
	else if (j == pCGI->CFI.bwidth / 2 - 1)  // ���½�
		cout << pCGI->CFI.lower_right << " ";
	else if (j % (pCGI->CFI.block_width / 2 + 1) == 0) // �·ֽ�
		cout << pCGI->CFI.h_lower_separator << " ";
	else  // ˮƽ��
		cout << pCGI->CFI.h_normal << " ";
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ������м���еĿ��Ԫ��
  ���������const CONSOLE_GRAPHICS_INFO *const pCGI������ṹָ��
			int j����ǰ������
  �� �� ֵ����
***************************************************************************/
static void gmw_inner_draw_middle_line(const CONSOLE_GRAPHICS_INFO* const pCGI, int j)
{
	if (j == 0)  // ��ֽ�
		cout << pCGI->CFI.v_left_separator << " ";
	else if (j == pCGI->CFI.bwidth / 2 - 1)  // �ҷֽ�
		cout << pCGI->CFI.v_right_separator << " ";
	else if (j % (pCGI->CFI.block_width / 2 + 1) == 0) // �зֽ�
		cout << pCGI->CFI.mid_separator << " ";
	else  // ˮƽ��
		cout << pCGI->CFI.h_normal << " ";
}


/***************************************************************************
  �������ƣ�
  ��    �ܣ����ƴ��ָ��ߵĿ��
  ���������CONSOLE_GRAPHICS_INFO *const pCGI��ָ������ṹ��ָ��
  �� �� ֵ����
  ˵    ���������趨���ƴ��зָ��ߵĿ�ܣ������к��еķֽ硣
***************************************************************************/
static void gmw_inner_draw_frame_with_separator(const CONSOLE_GRAPHICS_INFO* const pCGI)
{
	for (int i = 0; i < pCGI->CFI.bhigh; i++)
	{
		cct_gotoxy(pCGI->start_x, pCGI->start_y + i);
		for (int j = 0; j < pCGI->CFI.bwidth / 2; j++)
		{
			if (i == 0)
				gmw_inner_draw_top_line(pCGI, j); // ���û������еĺ���
			else if (i == pCGI->CFI.bhigh - 1)
				gmw_inner_draw_bottom_line(pCGI, j); // ���û���ĩ�еĺ���
			else if (i % (pCGI->CFI.block_high + 1) == 0)
				gmw_inner_draw_middle_line(pCGI, j); // ���û����м���еĺ���
			else //�м����
			{
				if (j % (pCGI->CFI.block_width / 2 + 1) == 0)
					cout << pCGI->CFI.v_normal << " ";
				else
					cout << "  ";
			}
			Sleep(pCGI->delay_of_draw_frame);
		}
	}
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ������޷ָ��ߵĿ��
  ���������CONSOLE_GRAPHICS_INFO *const pCGI��ָ������ṹ��ָ��
  �� �� ֵ����
  ˵    ���������趨���Ʋ����ָ��ߵĿ�ܡ�
***************************************************************************/
static void gmw_inner_draw_frame_without_separator(const CONSOLE_GRAPHICS_INFO* const pCGI)
{
	for (int i = 0; i < pCGI->CFI.bhigh; i++)
	{
		cct_gotoxy(pCGI->start_x, pCGI->start_y + i);
		for (int j = 0; j < pCGI->CFI.bwidth / 2; j++)
		{
			if (i == 0 && j == 0) // ���Ͻ�
				cout << pCGI->CFI.top_left << " ";
			else if (i == pCGI->CFI.bhigh - 1 && j == 0) // ���½�
				cout << pCGI->CFI.lower_left << " ";
			else if (i == 0 && j == pCGI->CFI.bwidth / 2 - 1) // ���Ͻ�
				cout << pCGI->CFI.top_right << " ";
			else if (i == pCGI->CFI.bhigh - 1 && j == pCGI->CFI.bwidth / 2 - 1) // ���½�
				cout << pCGI->CFI.lower_right << " ";
			else if (i == 0 || i == pCGI->CFI.bhigh - 1) // ˮƽ��
				cout << pCGI->CFI.h_normal << " ";
			else if (j == 0 || j == pCGI->CFI.bwidth / 2 - 1) // ��ֱ��
				cout << pCGI->CFI.v_normal << " ";
			else
				cout << "  "; // �м�ո�
			Sleep(pCGI->delay_of_draw_frame);
		}
	}
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���״̬����Ⱦ��ʾ��Ϣ
  ���������const CONSOLE_GRAPHICS_INFO* const pCGI  ������ṹָ��
			const int type                          ��״̬�����ͣ���/�£�
			const char* catchy_line                 ����Ҫ�ر��ע����Ϣ
			const char* line                        ��������Ϣ
			int wide_border                          ������������
  �� �� ֵ����
  ˵    �������ݲ�ͬ���͵�״̬�����ù��λ�ú���ɫ���������Ϣ
***************************************************************************/
static void gmw_inner_render_status_line(const CONSOLE_GRAPHICS_INFO* const pCGI, const int type, const char* catchy_line, const char* line, int wide_border)
{
	// ����״̬���������ù��λ�úͱ���ɫ
	if (type == TOP_STATUS_LINE)
	{
		cct_gotoxy(pCGI->SLI.top_start_x, pCGI->SLI.top_start_y);
		cct_setcolor(pCGI->SLI.top_catchy_bgcolor, pCGI->SLI.top_catchy_fgcolor);
	}
	else if (type == LOWER_STATUS_LINE)
	{
		cct_gotoxy(pCGI->SLI.lower_start_x, pCGI->SLI.lower_start_y);
		cct_setcolor(pCGI->SLI.lower_catchy_bgcolor, pCGI->SLI.lower_catchy_fgcolor);
	}

	// �����Ҫ�ر��ע����Ϣ
	cout << catchy_line;

	// ����״̬����������������Ϣ�ı���ɫ
	if (type == TOP_STATUS_LINE)
		cct_setcolor(pCGI->SLI.top_normal_bgcolor, pCGI->SLI.top_normal_fgcolor);
	else if (type == LOWER_STATUS_LINE)
		cct_setcolor(pCGI->SLI.lower_normal_bgcolor, pCGI->SLI.lower_normal_fgcolor);

	// ���������Ϣ
	cout << line;

	// ���������Ϣ���ر��ע����Ϣ����С�����ƿ�ȣ������ո�
	if (static_cast<size_t>(strlen(line) + strlen(catchy_line)) < static_cast<size_t>(wide_border))
		cout << setw(wide_border - strlen(line) - strlen(catchy_line)) << " ";
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�׼��״̬����Ϣ��
  ���������const char* msg                        ��������Ϣ
			const char* catchy_msg                 ����Ҫ�ر��ע����Ϣ
			int wide_border                        ������������
			char* line                             ���洢������Ϣ���ַ���
			char* catchy_line                      ���洢�ر��ע��Ϣ���ַ���
  �� �� ֵ����
  ˵    ����������Ϣ���ȣ�ȷ��������ᳬ��������ƣ����������Ľض�
***************************************************************************/
static void prepare_status_melineage(const char* msg, const char* catchy_msg, int wide_border, char* line, char* catchy_line)
{
	int len;
	if (msg == NULL)
		len = 0; // ���������ϢΪ�գ�����Ϊ0
	else
		len = strlen(msg); // �����ȡ������Ϣ�ĳ���

	int catchy_len;
	if (catchy_msg == NULL)
		catchy_len = 0; // ����ر��ע��ϢΪ�գ�����Ϊ0
	else
		catchy_len = strlen(catchy_msg); // �����ȡ�ر��ע��Ϣ�ĳ���

	if (len != 0) // ���������Ϣ��Ϊ��
	{
		if (catchy_len == 0) // ����ر��ע��ϢΪ��
		{
			gmw_inner_strncpy(line, msg, wide_border); // ����������Ϣ
			gmw_inner_dealwith_chinese_char(line); // ������ܵ����Ľض�
		}
		else
		{
			if (catchy_len >= wide_border) // ����ر��ע��Ϣ��������
			{
				gmw_inner_strncpy(catchy_line, catchy_msg, wide_border); // ֻ�����ر��ע��Ϣ
				gmw_inner_dealwith_chinese_char(catchy_line); // ������ܵ����Ľض�
			}
			else
			{
				int wide_border2 = wide_border - catchy_len; // ����ʣ����
				gmw_inner_strcpy(catchy_line, catchy_msg); // �����ر��ע��Ϣ
				gmw_inner_strncpy(line, msg, wide_border2); // ����������Ϣ
				gmw_inner_dealwith_chinese_char(line); // ������ܵ����Ľض�
			}
		}
	}
	else  // ���������ϢΪ��
	{
		line[0] = '\0'; // ȷ��������ϢΪ�մ�
		catchy_line[0] = '\0'; // ȷ���ر��ע��ϢΪ�մ�
	}
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�������ת��Ϊ�ַ����飨�ַ�������
  ���������int num����ת����������
			char* buffer�����ڴ��ת��������ַ����顣
			size_t buffer_size���ַ�����Ĵ�С��ȷ�������������
  �� �� ֵ����
  ˵    �����˺���������ת��Ϊ�ַ�����ʽ���������������ת������ַ����� '\0' ������
***************************************************************************/
static void gmw_inner_int_to_char_array(int num, char* buffer, int buffer_size)
{
	int len = 0; // �ַ�����ʵ�ʳ���
	bool is_negative = false; // ����Ƿ�Ϊ����

	// ����Ƿ�Ϊ����
	if (num < 0)
	{
		is_negative = true; // ���ø������
		num = -num; // ������ת��Ϊ�����Ա㴦��
	}

	// ������ת��Ϊ�ַ�����
	do
	{
		if (len < buffer_size - 1) // ȷ���пռ����ֹ��
			buffer[len++] = (num % 10) + '0'; // ȡ�����λ���ֲ�ת��Ϊ�ַ�
		num /= 10; // �Ƴ����λ����
	} while (num > 0); // ֱ���������ֶ�������

	// ����Ǹ�������Ӹ���
	if (is_negative)
		if (len < buffer_size - 1)
			buffer[len++] = '-'; // ��Ӹ���

	buffer[len] = '\0'; // ����ַ���������

	// ��ת�ַ����飬�õ���ȷ������˳��
	for (int i = 0; i < len / 2; ++i)
	{
		char temp = buffer[i];
		buffer[i] = buffer[len - i - 1]; // �����ַ�
		buffer[len - i - 1] = temp; // �����ַ�
	}
}


/***************************************************************************
  �������ƣ�
  ��    �ܣ������ṩ��ֵ�����е��ַ������ֻ����ݣ���
  ���������const CONSOLE_GRAPHICS_INFO* const pCGI������̨ͼ����Ϣ�ṹ���ָ�롣
			const BLOCK_DISPLAY_INFO* pBDI����ʾ��Ϣ�ṹ���ָ�롣
			int start_direction_x�������ʼ x ���ꡣ
			int start_direction_y�������ʼ y ���ꡣ
			int bdi_value����Ҫ��ʾ��ֵ
   �� �� ֵ��
   ˵    ����
***************************************************************************/
static void gmw_inner_fill_character(const CONSOLE_GRAPHICS_INFO* const pCGI, const BLOCK_DISPLAY_INFO* pBDI, int start_direction_x, int start_direction_y, int bdi_value)
{
	int char_start_x, char_start_y;

	// ���û����������Ҫ��ʾ����
	if (pBDI->content == NULL)
	{
		if (bdi_value != 0) // ���� BDI_VALUE_BLANK Ϊ 0
		{
			char_start_x = start_direction_x + 2 * pCGI->CBI.block_border;
			char_start_y = start_direction_y + (pCGI->CFI.block_high - 1) / 2;

			// �����ַ������Դ洢����
			char value[12]; // �㹻�洢�������ַ���
			gmw_inner_int_to_char_array(bdi_value, value, sizeof(value)); // ת������Ϊ�ַ���

			// �����ַ�������
			int value_len = 0;
			while (value[value_len] != '\0')
				value_len++; // �����ַ�������

			// ����ո񳤶��Ծ�����ʾ
			int blank_len = (pCGI->CFI.block_width - 2 * (pCGI->CBI.block_border + 1) - value_len) / 2;

			// ȷ���ո񳤶Ȳ�Ϊ��
			if (blank_len < 0)
				blank_len = 0;

			// �ƶ������λ��
			cct_gotoxy(char_start_x, char_start_y);
			for (int i = 0; i < blank_len; i++)
				cout << ' '; // ����ո�
			cout << value; // �������
		}
	}
	// ��������ݣ�ֱ�����
	else
	{
		char_start_x = start_direction_x + (pCGI->CFI.block_width - 1) / 2;
		char_start_y = start_direction_y + (pCGI->CFI.block_high - 1) / 2;

		cct_gotoxy(char_start_x, char_start_y); // �ƶ������λ��
		cout << pBDI->content; // �������
	}
}


/***************************************************************************
  �������ƣ�
  ��    �ܣ��������ɫ�飬�����߿�򲻰����߿�
  ���������const CONSOLE_GRAPHICS_INFO* const pCGI������̨ͼ����Ϣ�ṹ���ָ�롣
			int start_direction_x�������ʼ x ���ꡣ
			int start_direction_y�������ʼ y ���ꡣ
			bool need_delay���Ƿ���Ҫ�ӳٻ��ơ�
			int bdi_value����Ҫ��ʾ��ֵ��
  �� �� ֵ����
  ˵    ���������Ƿ��б߿����ɫ�飬���б߿�����Ʊ߿���ڲ���䡣
***************************************************************************/
static void gmw_inner_fill_block(const CONSOLE_GRAPHICS_INFO* const pCGI, int start_direction_x, int start_direction_y, bool need_delay, int bdi_value)
{
	// �����Ƿ��б߿���д���
	bool has_border = pCGI->CBI.block_border && bdi_value != 0;

	// ����ÿһ��
	for (int i = 0; i < pCGI->CFI.block_high; i++)
	{
		cct_gotoxy(start_direction_x, start_direction_y + i); // �ƶ�����ǰ�е���ʼλ��
		// ����ÿһ��
		for (int j = 0; j < pCGI->CFI.block_width / 2; j++)
		{
			if (has_border)
			{
				// ����
				if (i == 0)
				{
					if (j == 0)
						cout << pCGI->CBI.top_left << " "; // ���Ͻ�
					else if (j == pCGI->CFI.block_width / 2 - 1)
						cout << pCGI->CBI.top_right << " "; // ���Ͻ�
					else
						cout << pCGI->CBI.h_normal << " "; // �м䲿��
				}
				// ĩ��
				else if (i == pCGI->CFI.block_high - 1)
				{
					if (j == 0)
						cout << pCGI->CBI.lower_left << " "; // ���½�
					else if (j == pCGI->CFI.block_width / 2 - 1)
						cout << pCGI->CBI.lower_right << " "; // ���½�
					else
						cout << pCGI->CBI.h_normal << " "; // �м䲿��
				}
				// ��ͨ��
				else
				{
					if (j == 0 || j == pCGI->CFI.block_width / 2 - 1)
						cout << pCGI->CBI.v_normal << " "; // ����
					else
						cout << "  "; // �ո�
				}
			}
			else
				cout << "  "; // �ޱ߿�ʱ���ո�
			if (need_delay)
				Sleep(pCGI->delay_of_draw_block); // �ӳ�
		}
	}
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���ָ���������ɫ�鲢����ַ���
  ���������const CONSOLE_GRAPHICS_INFO* const pCGI������̨ͼ����Ϣ�ṹ���ָ�롣
			const int start_direction_x�������ʼ x ���ꡣ
			const int start_direction_y�������ʼ y ���ꡣ
			const int bdi_value����Ҫ��ʾ��ֵ��
			const BLOCK_DISPLAY_INFO* const bdi����Ÿ�ֵ��Ӧ����ʾ��Ϣ�Ľṹ�����顣
			bool need_delay���Ƿ���Ҫ�ӳٻ��ƣ�Ĭ��Ϊ true��
  �� �� ֵ����
  ˵    �������� bdi_value �� bdi �л�ȡ��ʾ��Ϣ����������ɫ����ƿ������ַ���
***************************************************************************/
static void gmw_inner_draw_block_direction(const CONSOLE_GRAPHICS_INFO* const pCGI, const int start_direction_x, const int start_direction_y, const int bdi_value, const BLOCK_DISPLAY_INFO* const bdi, bool need_delay = true)
{
	// ����ɫ����Ϣ
	const BLOCK_DISPLAY_INFO* pBDI = bdi;
	while (pBDI->value != bdi_value && pBDI->value != -1)
		pBDI++;

	// �����ɫ
	int block_bg_color;
	if (pBDI->bgcolor == -1)
		block_bg_color = pCGI->CFI.bgcolor; // ʹ��Ĭ�ϱ���ɫ
	else
		block_bg_color = pBDI->bgcolor; // ʹ���Զ��屳��ɫ

	int block_fg_color;
	if (pBDI->fgcolor == -1)
		block_fg_color = pCGI->CFI.fgcolor; // ʹ��Ĭ��ǰ��ɫ
	else
		block_fg_color = pBDI->fgcolor; // ʹ���Զ���ǰ��ɫ

	cct_setcolor(block_bg_color, block_fg_color); // ������ɫ

	gmw_inner_fill_block(pCGI, start_direction_x, start_direction_y, need_delay, bdi_value); // ���ɫ��
	gmw_inner_fill_character(pCGI, pBDI, start_direction_x, start_direction_y, bdi_value);  // ����ַ�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ��ڴ�ֱ�������ƶ�ָ����ɫ��
  ���������
	const CONSOLE_GRAPHICS_INFO *const pCGI	������̨ͼ����Ϣ�ṹ��ָ��
	const int start_direction_x					�������ʼ������
	const int start_direction_y					�������ʼ������
	const int distance						���ƶ����루��1��ʼ����Ϊ��֤��ȷ�ԣ����򲻼�飩
	const int bdi_value						����Ҫ��ʾ��ֵ
	const BLOCK_DISPLAY_INFO *const bdi		������ʾ��Ϣ�Ľṹ��ָ��
	const int direction						���ƶ�����-1��ʾ���ϣ�1��ʾ����
  �� �� ֵ����
  ˵    �������ݸ����ķ���;��룬���¿��λ�ò���ʾ�ƶ�Ч��
***************************************************************************/
static void gmw_inner_move_block_vertical(const CONSOLE_GRAPHICS_INFO* pCGI, int start_direction_x, int start_direction_y, int distance, int bdi_value, const BLOCK_DISPLAY_INFO* bdi, int direction)
{
	int end_direction_y = start_direction_y + direction * distance * (pCGI->CFI.block_high + 1 * pCGI->CFI.separator);

	if (direction == -1) // �����ƶ�
	{
		for (int y = start_direction_y - 1; y >= end_direction_y; y--)
		{
			gmw_inner_draw_block_direction(pCGI, start_direction_x, y, bdi_value, bdi, false);
			cct_gotoxy(start_direction_x, y + pCGI->CFI.block_high); // ���µĿ��е�λ��
			cct_setcolor(pCGI->CFI.bgcolor, pCGI->CFI.fgcolor);
			for (int i = 0; i < pCGI->CFI.block_width / 2; i++) {
				if ((start_direction_y - y) % (pCGI->CFI.block_high + 1 * pCGI->CFI.separator) == 0)
					cout << pCGI->CFI.h_normal << " "; // �������ֽ���
				else
					cout << "  "; // ���հ�
			}
			Sleep(pCGI->delay_of_block_moved);
		}
	}
	else if (direction == 1) // �����ƶ�
	{
		for (int y = start_direction_y + 1; y <= end_direction_y; y++)
		{
			gmw_inner_draw_block_direction(pCGI, start_direction_x, y, bdi_value, bdi, false);
			cct_gotoxy(start_direction_x, y - 1); // ���µĿ��е�λ��
			cct_setcolor(pCGI->CFI.bgcolor, pCGI->CFI.fgcolor);
			for (int i = 0; i < pCGI->CFI.block_width / 2; i++)
			{
				if ((y - start_direction_y) % (pCGI->CFI.block_high + 1 * pCGI->CFI.separator) == 0)
					cout << pCGI->CFI.h_normal << " "; // �������ֽ���
				else
					cout << "  "; // ���հ�
			}
			Sleep(pCGI->delay_of_block_moved);
		}
	}
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���ˮƽ�������ƶ�ָ����ɫ��
  ���������
	const CONSOLE_GRAPHICS_INFO *const pCGI	������̨ͼ����Ϣ�ṹ��ָ��
	const int start_direction_x					�������ʼ������
	const int start_direction_y					�������ʼ������
	const int col_no							���кţ���0��ʼ����Ϊ��֤��ȷ�ԣ����򲻼�飩
	const int distance						���ƶ����루��1��ʼ����Ϊ��֤��ȷ�ԣ����򲻼�飩
	const int bdi_value						����Ҫ��ʾ��ֵ
	const BLOCK_DISPLAY_INFO *const bdi		������ʾ��Ϣ�Ľṹ��ָ��
	const int direction						���ƶ�����-1��ʾ����1��ʾ����
  �� �� ֵ����
  ˵    �������ݸ����ķ���;��룬���¿��λ�ò���ʾ�ƶ�Ч��
***************************************************************************/
static void gmw_inner_move_block_horizontal(const CONSOLE_GRAPHICS_INFO* pCGI, int start_direction_x, int start_direction_y, int col_no, int distance, int bdi_value, const BLOCK_DISPLAY_INFO* bdi, int direction)
{
	int end_direction_x = start_direction_x + direction * distance * (pCGI->CFI.block_width + 2 * pCGI->CFI.separator);

	if (direction == -1)  // �����ƶ�
	{
		for (int x = start_direction_x - 2; x >= end_direction_x; x -= 2)
		{
			gmw_inner_draw_block_direction(pCGI, x, start_direction_y, bdi_value, bdi, false);
			for (int i = 0; i < pCGI->CFI.block_high; i++)
			{
				cct_gotoxy(x + pCGI->CFI.block_width, start_direction_y + i); // ���µĿ��е�λ��
				cct_setcolor(pCGI->CFI.bgcolor, pCGI->CFI.fgcolor);
				if (((start_direction_x - x) / 2) % (pCGI->CFI.block_width / 2 + 1 * pCGI->CFI.separator) == 0)
					cout << pCGI->CFI.v_normal << " "; // �������ֽ���
				else
					cout << "  "; // ���հ�
			}
			Sleep(pCGI->delay_of_block_moved);
		}
	}
	else if (direction == 1)  // �����ƶ�
	{
		for (int x = start_direction_x + 2; x <= end_direction_x; x += 2)
		{
			gmw_inner_draw_block_direction(pCGI, x, start_direction_y, bdi_value, bdi, false);
			for (int i = 0; i < pCGI->CFI.block_high; i++) {
				cct_gotoxy(x - 2, start_direction_y + i); // ���µĿ��е�λ��
				cct_setcolor(pCGI->CFI.bgcolor, pCGI->CFI.fgcolor);
				if (((x - start_direction_x) / 2) % (pCGI->CFI.block_width / 2 + 1 * pCGI->CFI.separator) == 0)
					cout << pCGI->CFI.v_normal << " "; // �������ֽ���
				else
					cout << "  "; // ���հ�
			}
			Sleep(pCGI->delay_of_block_moved);
		}
	}
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ��ڴ�ֱ�������ƶ�ָ����ɫ�飨�ޱ߿������
  ���������
	const CONSOLE_GRAPHICS_INFO *const pCGI	������̨ͼ����Ϣ�ṹ��ָ��
	const int start_direction_x					�������ʼ������
	const int block_start_direction_y0					����ĳ�ʼ������
	const int row_no							���кţ���0��ʼ����Ϊ��֤��ȷ�ԣ����򲻼�飩
	const int distance						���ƶ����루��1��ʼ����Ϊ��֤��ȷ�ԣ����򲻼�飩
	const int bdi_value						����Ҫ��ʾ��ֵ
	const BLOCK_DISPLAY_INFO *const bdi		������ʾ��Ϣ�Ľṹ��ָ��
	const int direction						���ƶ�����-1��ʾ���ϣ�1��ʾ����
  �� �� ֵ����
  ˵    �������ݸ����ķ���;��룬���¿��λ�ò���ʾ�ƶ�Ч�����Ҳ����Ʊ߿�
***************************************************************************/
static void gmw_inner_move_block_vertical_no_border(const CONSOLE_GRAPHICS_INFO* pCGI, int start_direction_x, int block_start_direction_y0, int row_no, int distance, int bdi_value, const BLOCK_DISPLAY_INFO* bdi, int direction)
{
	int end_direction_x = start_direction_x;
	int end_direction_y = block_start_direction_y0 + (row_no + direction * distance) * (pCGI->CFI.block_high + pCGI->CFI.separator);
	int start_direction_y = block_start_direction_y0 + row_no * (pCGI->CFI.block_high + 1 * pCGI->CFI.separator);

	if (direction == -1)  // �����ƶ�
	{
		for (int y = start_direction_y - 1; y >= end_direction_y; y--)
		{
			gmw_inner_draw_block_direction(pCGI, start_direction_x, y, bdi_value, bdi, false);
			cct_gotoxy(start_direction_x, y + pCGI->CFI.block_high); // ���µĿ��е�λ��
			cct_setcolor(pCGI->CFI.bgcolor, pCGI->CFI.fgcolor);
			for (int i = 0; i < pCGI->CFI.block_width / 2; i++)
				cout << "  "; // ���հ�
			Sleep(pCGI->delay_of_block_moved);
		}
	}
	else if (direction == 1)  // �����ƶ�
	{
		for (int y = start_direction_y + 1; y <= end_direction_y; y++)
		{
			gmw_inner_draw_block_direction(pCGI, start_direction_x, y, bdi_value, bdi, false);
			cct_gotoxy(start_direction_x, y - 1); // ���µĿ��е�λ��
			cct_setcolor(pCGI->CFI.bgcolor, pCGI->CFI.fgcolor);
			for (int i = 0; i < pCGI->CFI.block_width / 2; i++)
				cout << "  "; // ���հ�
			Sleep(pCGI->delay_of_block_moved);
		}
	}
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���ˮƽ�������ƶ�ָ����ɫ�飨�ޱ߿������
  ���������
	const CONSOLE_GRAPHICS_INFO *const pCGI	������̨ͼ����Ϣ�ṹ��ָ��
	const int block_start_direction_x0					����ĳ�ʼ������
	const int start_direction_x					�������ʼ������
	const int start_direction_y					�������ʼ������
	const int col_no							���кţ���0��ʼ����Ϊ��֤��ȷ�ԣ����򲻼�飩
	const int distance						���ƶ����루��1��ʼ����Ϊ��֤��ȷ�ԣ����򲻼�飩
	const int bdi_value						����Ҫ��ʾ��ֵ
	const BLOCK_DISPLAY_INFO *const bdi		������ʾ��Ϣ�Ľṹ��ָ��
	const int direction						���ƶ�����-1��ʾ����1��ʾ����
  �� �� ֵ����
  ˵    �������ݸ����ķ���;��룬���¿��λ�ò���ʾ�ƶ�Ч�����Ҳ����Ʊ߿�
***************************************************************************/
static void gmw_inner_move_block_horizontal_no_border(const CONSOLE_GRAPHICS_INFO* pCGI, int block_start_direction_x0, int start_direction_x, int start_direction_y, int col_no, int distance, int bdi_value, const BLOCK_DISPLAY_INFO* bdi, int direction)
{
	int end_direction_x = block_start_direction_x0 + (col_no + direction * distance) * (pCGI->CFI.block_width + 2 * pCGI->CFI.separator);
	int end_direction_y = start_direction_y;

	if (direction == -1) // �����ƶ�
	{
		for (int x = start_direction_x - 2; x >= end_direction_x; x -= 2)
		{
			gmw_inner_draw_block_direction(pCGI, x, start_direction_y, bdi_value, bdi, false);
			for (int i = 0; i < pCGI->CFI.block_high; i++)
			{
				cct_gotoxy(x + pCGI->CFI.block_width, start_direction_y + i); // ���µĿ��е�λ��
				cct_setcolor(pCGI->CFI.bgcolor, pCGI->CFI.fgcolor);
				cout << "  "; // ���հ�
			}
			Sleep(pCGI->delay_of_block_moved);
		}
	}
	else if (direction == 1)  // �����ƶ�
	{
		for (int x = start_direction_x + 2; x <= end_direction_x; x += 2)
		{
			gmw_inner_draw_block_direction(pCGI, x, start_direction_y, bdi_value, bdi, false);
			for (int i = 0; i < pCGI->CFI.block_high; i++)
			{
				cct_gotoxy(x - 2, start_direction_y + i); // ���µĿ��е�λ��
				cct_setcolor(pCGI->CFI.bgcolor, pCGI->CFI.fgcolor);
				cout << "  "; // ���հ�
			}
			Sleep(pCGI->delay_of_block_moved);
		}
	}
}

/***************************************************************************
  �������ƣ�gmw_inner_get_mouse_position
  ���ܣ������������ȷ��������Ϸ����ĺϷ�λ��
  ���������
	const CONSOLE_GRAPHICS_INFO* const pCGI	������ṹָ�룬������Ϸ�����λ����Ϣ�Ϳ������
	int X										�����ĵ�ǰX����
	int Y										�����ĵ�ǰY����
	int& MRow									��������������ڷ�����������кţ���0��ʼ��
	int& MCol									��������������ڷ�����������кţ���0��ʼ��
  ����ֵ��
	bool�������������ںϷ������ڷ���true�����򷵻�false
***************************************************************************/
static bool gmw_inner_get_mouse_position(const CONSOLE_GRAPHICS_INFO* const pCGI, int X, int Y, int& MRow, int& MCol)
{
	int block_start_direction_x0 = pCGI->start_x + 2;
	int block_start_direction_y0 = pCGI->start_y + 1;
	int start_direction_x, start_direction_y;
	MRow = MCol = -1;

	for (int i = 0; i < pCGI->row_num; i++)
	{
		for (int j = 0; j < pCGI->col_num; j++)
		{
			start_direction_y = block_start_direction_y0 + i * (pCGI->CFI.block_high + 1 * pCGI->CFI.separator);
			start_direction_x = block_start_direction_x0 + j * (pCGI->CFI.block_width + 2 * pCGI->CFI.separator);
			if (start_direction_x <= X && X < start_direction_x + pCGI->CFI.block_width && start_direction_y <= Y && Y < start_direction_y + pCGI->CFI.block_high)
			{
				MRow = i;
				MCol = j;
				return true; // λ�úϷ�
			}
		}
	}
	return false; // λ�÷Ƿ�
}

/***************************************************************************
  �������ƣ�gmw_inner_handle_mouse_event
  ���ܣ���������¼����������кŲ���ʾ״̬��Ϣ
  ���������
	const CONSOLE_GRAPHICS_INFO* const pCGI	������ṹָ�룬������Ϸ�����λ����Ϣ�Ϳ������
	int X										�����ĵ�ǰX����
	int Y										�����ĵ�ǰY����
	int& MRow									��������������ڷ�����������кţ���0��ʼ��
	int& MCol									��������������ڷ�����������кţ���0��ʼ��
	int& MAction								�������������ʾ����¼�������
	int& MRow_last								�����������ǰһ�����λ�õ��к�
	int& MCol_last								�����������ǰһ�����λ�õ��к�
	const bool update_lower_status_line		������ֵ��ָʾ�Ƿ���״̬���и�����Ϣ
  ����ֵ��
	bool������¼�������Ч����true�����򷵻�false
***************************************************************************/
static bool gmw_inner_handle_mouse_event(const CONSOLE_GRAPHICS_INFO* const pCGI, int X, int Y, int& MRow, int& MCol, int& MAction, int& MRow_last, int& MCol_last, const bool update_lower_status_line)
{
	if (MAction == MOUSE_ONLY_MOVED)
	{
		if (gmw_inner_get_mouse_position(pCGI, X, Y, MRow, MCol))
		{
			if (!(MRow_last == MRow && MCol_last == MCol) && update_lower_status_line)
			{
				char display[30] = { 0 };
				sprintf(display, "[��ǰ���] %c��%d��", MRow + 'A', MCol);
				gmw_status_line(pCGI, LOWER_STATUS_LINE, display);
			}
			return true; // ��Ч������ƶ�
		}
		else
			if (update_lower_status_line)
				gmw_status_line(pCGI, LOWER_STATUS_LINE, "[��ǰ���] λ�÷Ƿ�");
	}
	else if (MAction == MOUSE_LEFT_BUTTON_CLICK || MAction == MOUSE_RIGHT_BUTTON_CLICK)
	{
		if (gmw_inner_get_mouse_position(pCGI, X, Y, MRow, MCol))
			return true; // �Ϸ����
		else
			if (update_lower_status_line)
				gmw_status_line(pCGI, LOWER_STATUS_LINE, "[��ǰ���] λ�÷Ƿ�");
	}

	return false; // ��Ч�¼�
}


/* -----------------------------------------------
		ʵ����������ĺ���������������׼����
   ----------------------------------------------- */
   /***************************************************************************
	 �������ƣ�
	 ��    �ܣ�������Ϸ����ܵ�������
	 ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
			   const int row						������(������Ϊ0���������ޣ���Ϊ��֤��ȷ��)
			   const int col						������(������Ϊ0���������ޣ���Ϊ��֤��ȷ��)
	 �� �� ֵ��
	 ˵    ����1��ָ��������Ϸ�ľ������������ֵ
			   2�����еı仯�ᵼ��CONSOLE_GRAPHICS_INFO�ṹ����������Աֵ�ı仯��Ҫ����
   ***************************************************************************/
int gmw_set_rowcol(CONSOLE_GRAPHICS_INFO* const pCGI, const int row, const int col)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;

	if (row < 0 || col < 0)
	{
		if (row < 0) pCGI->row_num = 0;
		if (col < 0) pCGI->col_num = 0;
		return 0; // �����һ������
	}

	pCGI->row_num = row;
	pCGI->col_num = col;
	gmw_inner_calculate_all(pCGI);
	return 0; // �ɹ�����������
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ������������ڣ�����Ϸ�������������ڵ�����cmd���ڣ�����ɫ
  ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
		   const int bg_color					��ǰ��ɫ��ȱʡCOLOR_BLACK��
		   const int fg_color					������ɫ��ȱʡCOLOR_WHITE��
		   const bool cascade					���Ƿ�����ȱʡΪtrue-������
  �� �� ֵ��
  ˵    ����1��cascade = trueʱ
				ͬ���޸���Ϸ���������ɫ
				ͬ���޸�����״̬���������ı��ı���ɫ��ǰ��ɫ����Ŀ�ı��ı���ɫ��ǰ��ɫ���䣩
			2���������ɫֵ���󼰳�ͻ����Ҫ��Ϊ��֤
				������ɫ��0-15
					ǰ��ɫ����ɫ��ֵһ�µ����޷���������
					ǰ��ɫ������״̬����Ŀǰ��ɫ�������޷�������Ŀ��ʾ
					...
***************************************************************************/
int gmw_set_color(CONSOLE_GRAPHICS_INFO* const pCGI, const int bgcolor, const int fgcolor, const bool cascade)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;

	// ����������ɫ
	pCGI->area_bgcolor = bgcolor;
	pCGI->area_fgcolor = fgcolor;

	if (cascade)
	{
		// �޸Ŀ��
		pCGI->CFI.bgcolor = bgcolor;
		pCGI->CFI.fgcolor = fgcolor;

		// �޸���״̬��
		pCGI->SLI.top_normal_bgcolor = bgcolor;
		pCGI->SLI.top_normal_fgcolor = fgcolor;
		pCGI->SLI.top_catchy_bgcolor = bgcolor;

		// �޸���״̬��
		pCGI->SLI.lower_normal_bgcolor = bgcolor;
		pCGI->SLI.lower_normal_fgcolor = fgcolor;
		pCGI->SLI.lower_catchy_bgcolor = bgcolor;
	}

	return 0; // �ɹ�������ɫ
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ����ô��ڵ�����
  ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
		   const char *fontname					���������ƣ�ֻ����"Terminal"��"������"���֣������򷵻�-1�����ı����壩
		   const int fs_high					������߶ȣ�ȱʡ������Ϊ16�������������ƣ���Ϊ��֤��
		   const int fs_width					������߶ȣ�ȱʡ������Ϊ8�������������ƣ���Ϊ��֤��
  �� �� ֵ��
  ˵    ����1����cmd_console_tools�е�setfontsize���ƣ�Ŀǰֻ֧�֡��������塱�͡������塱
			2������������������ֱ�ӷ��أ�����ԭ�������ò���
***************************************************************************/
int gmw_set_font(CONSOLE_GRAPHICS_INFO* const pCGI, const char* fontname, const int fs_high, const int fs_width)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;

	// �����������
	if (gmw_inner_strcmp(fontname, "������") != 0 && gmw_inner_strcmp(fontname, "Terminal") != 0)
		return -1; // ���岻֧��

	// ������������
	gmw_inner_strcpy(pCGI->CFT.font_type, fontname);

	// ���������С
	if (fs_high <= 0)
		pCGI->CFT.font_size_high = 16; // Ĭ��ֵ
	else
		pCGI->CFT.font_size_high = fs_high;

	if (fs_width <= 0)
		pCGI->CFT.font_size_width = 8; // Ĭ��ֵ
	else
		pCGI->CFT.font_size_width = fs_width;

	return 0; // �ɹ���������
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�������ʱ
  ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
		   const int type						����ʱ�����ͣ�ĿǰΪ3�֣�
		   const int delay_ms					����msΪ��λ����ʱ
			   ���߿����ʱ��0 ~ �������ޣ���Ϊ��֤��ȷ��<0����0��
			   ��ɫ�����ʱ��0 ~ �������ޣ���Ϊ��֤��ȷ��<0����0��
			   ɫ���ƶ�����ʱ��BLOCK_MOVED_DELAY_MS ~ �������ޣ���Ϊ��֤��ȷ�� <BLOCK_MOVED_DELAY_MS ���� BLOCK_MOVED_DELAY_MS��
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int gmw_set_delay(CONSOLE_GRAPHICS_INFO* const pCGI, const int type, const int delay_ms)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;

	// �����ʱ���͵���Ч��
	if (type < DELAY_OF_DRAW_FRAME || type > DELAY_OF_BLOCK_MOVED)
		return -1; // ������Ч

	// ������ʱ
	if (type == DELAY_OF_DRAW_FRAME)
	{
		if (delay_ms < 0)
			pCGI->delay_of_draw_frame = 0;
		else
			pCGI->delay_of_draw_frame = delay_ms;
	}
	else if (type == DELAY_OF_DRAW_BLOCK)
	{
		if (delay_ms < 0)
			pCGI->delay_of_draw_block = 0;
		else
			pCGI->delay_of_draw_block = delay_ms;
	}
	else if (type == DELAY_OF_BLOCK_MOVED)
	{
		if (delay_ms < BLOCK_MOVED_DELAY_MS)
			pCGI->delay_of_block_moved = BLOCK_MOVED_DELAY_MS;
		else
			pCGI->delay_of_block_moved = delay_ms;
	}

	return 0; // �ɹ�������ʱ
}

/***************************************************************************
  �������ƣ�
  ���������������Ϸ����ܽṹ֮����Ҫ�����Ķ�������
  ��    �ܣ�CONSOLE_GRAPHICS_INFO *const pCGI	��
		   const int up_lines					���ϲ�������У�ȱʡ������Ϊ0���������ޣ���Ϊ��֤��
		   const int down_lines				���²�������У�ȱʡ������Ϊ0���������ޣ���Ϊ��֤��
		   const int left_cols					����߶�����У�ȱʡ������Ϊ0���������ޣ���Ϊ��֤��
		   const int right_cols				���ұ߶�����У�ȱʡ������Ϊ0���������ޣ���Ϊ��֤��
  �� �� ֵ��
  ˵    �����������еı仯�ᵼ��CONSOLE_GRAPHICS_INFO�ṹ����������Աֵ�ı仯��Ҫ����
***************************************************************************/
int gmw_set_ext_rowcol(CONSOLE_GRAPHICS_INFO* const pCGI, const int up_lines, const int down_lines, const int left_cols, const int right_cols)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;

	// ���ö������У�����ʹ���������ʽ
	if (up_lines < 0)
		pCGI->extern_up_lines = 0;
	else
		pCGI->extern_up_lines = up_lines;

	if (down_lines < 0)
		pCGI->extern_down_lines = 0;
	else
		pCGI->extern_down_lines = down_lines;

	if (left_cols < 0)
		pCGI->extern_left_cols = 0;
	else
		pCGI->extern_left_cols = left_cols;

	if (right_cols < 0)
		pCGI->extern_right_cols = 0;
	else
		pCGI->extern_right_cols = right_cols;


	gmw_inner_calculate_all(pCGI);
	return 0; // �ɹ����ö�������
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���� CONSOLE_FRAME_TYPE �ṹ�е�11�����ͣ�ȱʡ4�֣�
  ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
			const int type						��1 - ȫ�� 2 - ȫ���� 3 - ��˫���� 4 - �ᵥ��˫
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int gmw_set_frame_default_linetype(CONSOLE_GRAPHICS_INFO* const pCGI, const int type)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI == NULL || pCGI->inited != CGI_INITED) return -1;

	const char* lineChars[5][11] = {
		{ NULL },
		{ "�X", "�^", "�[", "�a", "�T", "�U", "�j", "�m", "�d", "�g", "�p" },
		{ "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��" },
		{ "�V", "�\", "�Y", "�_", "�T", "��", "�h", "�k", "�b", "�e", "�n" },
		{ "�W", "�]", "�Z", "�`", "��", "�U", "�i", "�l", "�c", "�f", "�o" }
	};

	if (type < 1 || type > 4) return -1;

	for (int i = 0; i < 11; i++)
		gmw_inner_strcpy(((char*)&pCGI->CFI) + (i * sizeof(pCGI->CFI.top_left)), lineChars[type][i]);

	return 0;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���� CONSOLE_FRAME_TYPE �ṹ�е�11������
  ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
			const char *...						����11�֣������.h���˴���
  �� �� ֵ��
  ˵    ����Լ��Ϊһ�������Ʊ��������ʹ���������ݣ���Ϊ��֤2�ֽ�
			1������2�ֽ���ֻȡǰ2�ֽ�
			2�������NULL���������ո����
			3�������1�ֽڣ���һ���ո������˶�������ʾ�ң������
***************************************************************************/
int gmw_set_frame_linetype(CONSOLE_GRAPHICS_INFO* const pCGI, const char* top_left, const char* lower_left, const char* top_right,
	const char* lower_right, const char* h_normal, const char* v_normal, const char* h_top_separator,
	const char* h_lower_separator, const char* v_left_separator, const char* v_right_separator, const char* mid_separator)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI == NULL || pCGI->inited != CGI_INITED) return -1;

	const char* lineChars[11] = { top_left, lower_left, top_right, lower_right, h_normal,
								  v_normal, h_top_separator, h_lower_separator,
								  v_left_separator, v_right_separator, mid_separator };

	for (int i = 0; i < 11; i++)
		gmw_inner_strcpy(((char*)&pCGI->CFI) + (i * sizeof(pCGI->CFI.top_left)), lineChars[i]);

	return 0; // �ɹ�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���� CONSOLE_FRAME_TYPE �ṹ�е�ɫ��������С���Ƿ���Ҫ�ָ��ߵ�
  ������������������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
			const int block_width						����ȣ�����ȱʡ2����ΪԼ�������Ϊ�����Ʊ�����������������Ҫ+1��
			const int block_high						���߶ȣ�����ȱʡ1��
			const bool separator						���Ƿ���Ҫ�ָ��ߣ�ȱʡΪtrue����Ҫ�ָ��ߣ�
  �� �� ֵ��
  ˵    ������ܴ�С/�Ƿ���Ҫ�ָ��ߵȵı仯�ᵼ��CONSOLE_GRAPHICS_INFO�ṹ����������Աֵ�ı仯��Ҫ����
***************************************************************************/
int gmw_set_frame_style(CONSOLE_GRAPHICS_INFO* const pCGI, const int block_width, const int block_high, const bool separator)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;

	// ���ÿ���
	if (block_width < 0)
		pCGI->CFI.block_width = 2;
	else
	{
		if (block_width % 2 == 1)
			pCGI->CFI.block_width = block_width + 1;
		else
			pCGI->CFI.block_width = block_width;
	}

	// ���ÿ�߶�
	if (block_high < 0)
		pCGI->CFI.block_high = 1;
	else
		pCGI->CFI.block_high = block_high;

	// ���÷ָ���
	pCGI->CFI.separator = separator;
	gmw_inner_calculate_all(pCGI); // �����ڲ�����
	return 0; // ���سɹ�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���� CONSOLE_BORDER_TYPE �ṹ�е���ɫ
  ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
			const int bg_color					������ɫ��ȱʡ -1��ʾ�ô��ڱ���ɫ��
			const int fg_color					��ǰ��ɫ��ȱʡ -1��ʾ�ô���ǰ��ɫ��
  �� �� ֵ��
  ˵    �����������ɫֵ���󼰳�ͻ����Ҫ��Ϊ��֤
				������ɫ��0-15��ǰ��ɫ����ɫ��ֵһ�µ����޷��������ݵ�
***************************************************************************/
int gmw_set_frame_color(CONSOLE_GRAPHICS_INFO* const pCGI, const int bgcolor, const int fgcolor)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;

	// ���ñ���ɫ
	if (bgcolor == -1)
		pCGI->CFI.bgcolor = pCGI->area_bgcolor; // ʹ�ô��ڱ���ɫ
	else
		pCGI->CFI.bgcolor = bgcolor; // ʹ���ṩ�ı���ɫ

	// ����ǰ��ɫ
	if (fgcolor == -1)
		pCGI->CFI.fgcolor = pCGI->area_fgcolor; // ʹ�ô���ǰ��ɫ
	else
		pCGI->CFI.fgcolor = fgcolor; // ʹ���ṩ��ǰ��ɫ

	return 0; // ���سɹ�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���� CONSOLE_BLOCK_INFO �ṹ�е�6�����ͣ�ȱʡ4�֣�
  ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
			const int type						��1 - ȫ˫�� 2 - ȫ���� 3 - ��˫���� 4 - �ᵥ��˫
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int gmw_set_block_default_linetype(CONSOLE_GRAPHICS_INFO* const pCGI, const int type)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;

	// ���������ַ�
	const char* lineChars[5][11] = {
		{ NULL },
		{ "�X", "�^", "�[", "�a", "�T", "�U", "�j", "�m", "�d", "�g", "�p" },
		{ "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��" },
		{ "�V", "�\", "�Y", "�_", "�T", "��", "�h", "�k", "�b", "�e", "�n" },
		{ "�W", "�]", "�Z", "�`", "��", "�U", "�i", "�l", "�c", "�f", "�o" }
	};

	// ���������Ч��
	if (type < 1 || type > 4)
		return -1;

	// ��������ַ�
	for (int i = 0; i < 11; i++) {
		gmw_inner_strcpy(((char*)&pCGI->CBI) + (i * sizeof(pCGI->CBI.top_left)), lineChars[type][i]);
	}

	return 0; // ���سɹ�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���� CONSOLE_BLOCK_INFO �ṹ�е�6������
  ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
		   const char *...					����6�֣������.h���˴���
  �� �� ֵ��
  ˵    ����Լ��Ϊһ�������Ʊ��������ʹ���������ݣ���Ϊ��֤2�ֽ�
			1������2�ֽ���ֻȡǰ2�ֽ�
			2�������NULL���������ո����
			3�������1�ֽڣ���һ���ո������˶�������ʾ�ң������
***************************************************************************/
int gmw_set_block_linetype(CONSOLE_GRAPHICS_INFO* const pCGI, const char* top_left, const char* lower_left, const char* top_right, const char* lower_right, const char* h_normal, const char* v_normal)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;

	const char* lineChars[6] = {
		top_left, lower_left, top_right, lower_right, h_normal, v_normal
	};

	char restore[CFI_LEN] = { 0 }; // �洢��ʱ�ַ�

	for (int i = 0; i < 6; i++)
	{
		const char* src = lineChars[i];
		if (src == NULL)
			gmw_inner_strcpy(((char*)&pCGI->CBI) + (i * sizeof(pCGI->CBI.top_left)), "  "); // NULLʱ���������ո�
		else if (strlen(src) == 2)
			gmw_inner_strcpy(((char*)&pCGI->CBI) + (i * sizeof(pCGI->CBI.top_left)), src); // ��������2�ֽ��ַ�
		else if (strlen(src) == 1)
		{
			restore[0] = src[0];
			restore[1] = ' ';
			restore[2] = '\0';
			gmw_inner_strcpy(((char*)&pCGI->CBI) + (i * sizeof(pCGI->CBI.top_left)), restore); // 1�ֽ��ַ����ո�
		}
		else
		{
			gmw_inner_strncpy(restore, src, 2);
			restore[2] = '\0';
			gmw_inner_strcpy(((char*)&pCGI->CBI) + (i * sizeof(pCGI->CBI.top_left)), restore); // ����2�ֽڣ���ȡǰ2�ֽ�
		}
	}

	return 0; // ���سɹ�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�����ÿ����Ϸɫ��(����)�Ƿ���ҪС�߿�
  ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
		   const bool on_off					��true - ��Ҫ flase - ����Ҫ��ȱʡfalse��
  �� �� ֵ��
  ˵    �����߿�Լ��Ϊ�����Ʊ����˫��
***************************************************************************/
int gmw_set_block_border_switch(CONSOLE_GRAPHICS_INFO* const pCGI, const bool on_off)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;
	pCGI->CBI.block_border = on_off;
	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ������Ƿ���ʾ����״̬��
  ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
			const int type						��״̬�����ͣ���/�£�
			const bool on_off					��true - ��Ҫ flase - ����Ҫ��ȱʡtrue��
  �� �� ֵ��
  ˵    ����1��״̬�������Լ�����£�
			   1.1����״̬��ֻ��һ�У������������Ϸ�����/�б�����棬Ϊ��������ʼһ�У�����������Ͻ����������״̬�������꣩
			   1.2����״̬��ֻ��һ�У������������·����ߵ�����
			   1.3��״̬���Ŀ��Ϊ�������ȣ������Ϣ������ض�
		   2�����еı仯�ᵼ��CONSOLE_GRAPHICS_INFO�ṹ����������Աֵ�ı仯��Ҫ����
***************************************************************************/
int gmw_set_status_line_switch(CONSOLE_GRAPHICS_INFO* const pCGI, const int type, const bool on_off)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1; // ����ʼ��״̬

	gmw_inner_set_status_line(pCGI, type, on_off); // ���÷�װ��������״̬��
	gmw_inner_calculate_all(pCGI); // ������ز���
	return 0; // ���سɹ�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���������״̬������ɫ
  ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
			const int type						��״̬�����ͣ���/�£�
			const int normal_bgcolor			�������ı�����ɫ��ȱʡ -1��ʾʹ�ô��ڱ���ɫ��
			const int normal_fgcolor			�������ı�ǰ��ɫ��ȱʡ -1��ʾʹ�ô���ǰ��ɫ��
			const int catchy_bgcolor			����Ŀ�ı�����ɫ��ȱʡ -1��ʾʹ�ô��ڱ���ɫ��
			const int catchy_fgcolor			����Ŀ�ı�ǰ��ɫ��ȱʡ -1��ʾʹ������ɫ��
  ���������
  �� �� ֵ��
  ˵    �����������ɫֵ���󼰳�ͻ����Ҫ��Ϊ��֤
				������ɫ��0-15��ǰ��ɫ����ɫ��ֵһ�µ����޷��������ݵ�
***************************************************************************/
int gmw_set_status_line_color(CONSOLE_GRAPHICS_INFO* const pCGI, const int type, const int normal_bgcolor, const int normal_fgcolor, const int catchy_bgcolor, const int catchy_fgcolor)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;
	int* normal_bg;
	int* normal_fg;
	int* catchy_bg;
	int* catchy_fg;

	if (type == TOP_STATUS_LINE)
	{
		normal_bg = &pCGI->SLI.top_normal_bgcolor;
		normal_fg = &pCGI->SLI.top_normal_fgcolor;
		catchy_bg = &pCGI->SLI.top_catchy_bgcolor;
		catchy_fg = &pCGI->SLI.top_catchy_fgcolor;
	}
	else
	{
		normal_bg = &pCGI->SLI.lower_normal_bgcolor;
		normal_fg = &pCGI->SLI.lower_normal_fgcolor;
		catchy_bg = &pCGI->SLI.lower_catchy_bgcolor;
		catchy_fg = &pCGI->SLI.lower_catchy_fgcolor;
	}
	// ������ɫ
	gmw_inner_set_normal_bg_color(normal_bg, normal_bgcolor, pCGI->area_bgcolor);
	gmw_inner_set_normal_fg_color(normal_fg, normal_fgcolor, pCGI->area_fgcolor);
	gmw_inner_set_normal_bg_color(catchy_bg, catchy_bgcolor, pCGI->area_bgcolor);
	gmw_inner_set_normal_fg_color(catchy_fg, catchy_fgcolor, COLOR_HYELLOW);
	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ������Ƿ���ʾ�к�
  ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
			const bool on_off					��true - ��ʾ flase - ����ʾ��ȱʡfalse��
  �� �� ֵ��
  ˵    ����1���к�Լ��Ϊ��ĸA��ʼ�������У��������26�����a��ʼ������52��ͳһΪ*��ʵ��Ӧ�ò����ܣ�
			2���Ƿ���ʾ�кŵı仯�ᵼ��CONSOLE_GRAPHICS_INFO�ṹ����������Աֵ�ı仯��Ҫ����
***************************************************************************/
int gmw_set_rowno_switch(CONSOLE_GRAPHICS_INFO* const pCGI, const bool on_off)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;
	pCGI->draw_frame_with_row_no = on_off;
	gmw_inner_calculate_all(pCGI);
	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ������Ƿ���ʾ�б�
  ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
			const bool on_off					��true - ��ʾ flase - ����ʾ��ȱʡfalse��
  �� �� ֵ��
  ˵    ����1���б�Լ��Ϊ����0��ʼ�������У�����0-99������99ͳһΪ**��ʵ��Ӧ�ò����ܣ�
			2���Ƿ���ʾ�б�ı仯�ᵼ��CONSOLE_GRAPHICS_INFO�ṹ����������Աֵ�ı仯��Ҫ����
***************************************************************************/
int gmw_set_colno_switch(CONSOLE_GRAPHICS_INFO* const pCGI, const bool on_off)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;
	pCGI->draw_frame_with_col_no = on_off;
	gmw_inner_calculate_all(pCGI);
	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���ӡ CONSOLE_GRAPHICS_INFO �ṹ���еĸ���Աֵ
  ���������
  �� �� ֵ��
  ˵    ����1�����������ã���ӡ��ʽ�Զ���
			2������������������δ���ù������Բ�ʵ��
***************************************************************************/
int gmw_print(const CONSOLE_GRAPHICS_INFO* const pCGI)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;
	// ��ӡ�ṹ���Ա
	cout << "CONSOLE_GRAPHICS_INFO:" << endl;
	cout << "  ��ʼ�����: " << pCGI->inited << endl;
	cout << "  ���򱳾�ɫ: " << pCGI->area_bgcolor << endl;
	cout << "  ����ǰ��ɫ: " << pCGI->area_fgcolor << endl;
	cout << "  ��״̬��: " << (pCGI->SLI.is_top_status_line ? "����" : "����") << endl;
	cout << "  ��״̬��: " << (pCGI->SLI.is_lower_status_line ? "����" : "����") << endl;
	cout << "  ����: " << pCGI->row_num << endl;
	cout << "  ����: " << pCGI->col_num << endl;
	cout << "  ��ʼ���� (X, Y): (" << pCGI->start_x << ", " << pCGI->start_y << ")" << endl;
	cout << "  ��������: " << pCGI->lines << ", ��������: " << pCGI->cols << endl;

	// ���Ը�����Ҫ��Ӹ����ӡ����

	return 0; // �ɹ�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ��� CONSOLE_GRAPHICS_INFO �ṹ����ȱʡֵ���г�ʼ��
  ���������CONSOLE_GRAPHICS_INFO *const pCGI������ṹָ��
		   const int row					����Ϸ����ɫ��������ȱʡ10��
		   const int col					����Ϸ����ɫ��������ȱʡ10��
		   const int bgcolor				���������ڱ���ɫ��ȱʡ COLOR_BLACK��
		   const int fgcolor				���������ڱ���ɫ��ȱʡ COLOR_WHITE��
  �� �� ֵ��
  ˵    �������ڱ�����/ǰ���ף�����16*8�����������޶������У�����״̬�����У����к�/�б꣬�������Ϊ˫�ߣ�ɫ����2/�߶�1/��С�߿���ɫ��
***************************************************************************/
int gmw_init(CONSOLE_GRAPHICS_INFO* const pCGI, const int row, const int col, const int bgcolor, const int fgcolor)
{
	/* �����ñ�� */
	pCGI->inited = CGI_INITED;
	/*�����������*/
	gmw_set_rowcol(pCGI, row, col);
	gmw_inner_set_color_and_font(pCGI, bgcolor, fgcolor);
	gmw_inner_set_frame_parameters(pCGI);
	gmw_inner_set_status_line_parameters(pCGI);
	gmw_inner_set_row_col_display(pCGI);
	gmw_inner_calculate_all(pCGI);
	/*���������*/
	gmw_inner_calculate_all(pCGI);
	return 0;  // �ɹ�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�������Ϸ���
  ���������const CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
  �� �� ֵ��
  ˵    ��������ɲο�demo��Ч��
***************************************************************************/
int gmw_draw_frame(const CONSOLE_GRAPHICS_INFO* const pCGI)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;
	cct_setcolor(pCGI->area_bgcolor, pCGI->area_fgcolor);
	cct_setfontsize(pCGI->CFT.font_type, pCGI->CFT.font_size_high, 0);
	cct_cls();

	cct_setconsoleborder(pCGI->cols, pCGI->lines);
	cct_setcolor(pCGI->area_bgcolor, pCGI->area_fgcolor);
	// �����к�
	if (pCGI->draw_frame_with_col_no)
		gmw_inner_draw_column_numbers(pCGI);

	// �����к�
	if (pCGI->draw_frame_with_row_no)
		gmw_inner_draw_row_numbers(pCGI);

	//�����
	cct_setcolor(pCGI->CFI.bgcolor, pCGI->CFI.fgcolor);

	if (pCGI->CFI.separator) //�����޷ָ��������������
		gmw_inner_draw_frame_with_separator(pCGI);
	else
		gmw_inner_draw_frame_without_separator(pCGI);
	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���״̬������ʾ��Ϣ
  ���������const CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
		   const int type							��ָ������/��״̬��
		   const char *msg						��������Ϣ
		   const char *catchy_msg					����Ҫ�ر��ע����Ϣ����������Ϣǰ��ʾ��
  �� �� ֵ��
  ˵    ����1���������޶�Ϊ����ܵĿ�ȣ����к��б�λ�ã����������ȥ
			2��������һ���ַ���ĳ���ֵ�ǰ������ᵼ�º������룬Ҫ����
***************************************************************************/
int gmw_status_line(const CONSOLE_GRAPHICS_INFO* const pCGI, const int type, const char* msg, const char* catchy_msg)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;

	if (type == TOP_STATUS_LINE && !pCGI->SLI.is_top_status_line)
		return 0;
	if (type == LOWER_STATUS_LINE && !pCGI->SLI.is_lower_status_line)
		return 0;

	cct_setfontsize(pCGI->CFT.font_type, pCGI->CFT.font_size_high, 0);
	int wide_border = 2 * pCGI->draw_frame_with_row_no + pCGI->CFI.bwidth; // �������
	char* line = new char[wide_border + 1]();
	char* catchy_line = new char[wide_border + 1]();
	if (line == NULL || catchy_line == NULL) return -1;

	prepare_status_melineage(msg, catchy_msg, wide_border, line, catchy_line);
	gmw_inner_render_status_line(pCGI, type, catchy_line, line, wide_border);

	delete[] line;
	delete[] catchy_line;
	return 0; // �ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���ʾĳһ��ɫ��(����Ϊ�ַ���������Ϊrow/col)
  ���������const CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
		   const int row_no						���кţ���0��ʼ����Ϊ��֤��ȷ�ԣ����򲻼�飩
		   const int col_no						���кţ���0��ʼ����Ϊ��֤��ȷ�ԣ����򲻼�飩
		   const int bdi_value						����Ҫ��ʾ��ֵ
		   const BLOCK_DISPLAY_INFO *const bdi		����Ÿ�ֵ��Ӧ����ʾ��Ϣ�Ľṹ������
  �� �� ֵ��
  ˵    ����1��BLOCK_DISPLAY_INFO �ĺ����ͷ�ļ����÷��ο���������
			2��bdi_valueΪ BDI_VALUE_BLANK ��ʾ�հ׿飬Ҫ���⴦��
***************************************************************************/
int gmw_draw_block(const CONSOLE_GRAPHICS_INFO* const pCGI, const int row_no, const int col_no, const int bdi_value, const BLOCK_DISPLAY_INFO* const bdi)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;
	//λ��
	int block_start_direction_x0 = pCGI->start_x + 2;
	int block_start_direction_y0 = pCGI->start_y + 1;
	int start_direction_x = block_start_direction_x0 + col_no * (pCGI->CFI.block_width + 2 * pCGI->CFI.separator);
	int start_direction_y = block_start_direction_y0 + row_no * (pCGI->CFI.block_high + 1 * pCGI->CFI.separator);
	gmw_inner_draw_block_direction(pCGI, start_direction_x, start_direction_y, bdi_value, bdi);
	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ��ƶ�ĳһ��ɫ��
  ���������const CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
		   const int row_no						���кţ���0��ʼ����Ϊ��֤��ȷ�ԣ����򲻼�飩
		   const int col_no						���кţ���0��ʼ����Ϊ��֤��ȷ�ԣ����򲻼�飩
		   const int bdi_value						����Ҫ��ʾ��ֵ
		   const int blank_bdi_value				���ƶ����������ڶ���Ч����ʾʱ���ڱ�ʾ�հ׵�ֵ��һ��Ϊ0���˴���Ϊ�������룬�ǿ��ǵ����ܳ��ֵ����������
		   const BLOCK_DISPLAY_INFO *const bdi		�������ʾֵ/�հ�ֵ��Ӧ����ʾ��Ϣ�Ľṹ������
		   const int direction						���ƶ�����һ�����֣������cmd_gmw_tools.h
		   const int distance						���ƶ����루��1��ʼ����Ϊ��֤��ȷ�ԣ����򲻼�飩
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int gmw_move_block(const CONSOLE_GRAPHICS_INFO* const pCGI, const int row_no, const int col_no, const int bdi_value, const int blank_bdi_value, const BLOCK_DISPLAY_INFO* const bdi, const int direction, const int distance)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;
	//λ��
	int block_start_direction_x0 = pCGI->start_x + 2;
	int block_start_direction_y0 = pCGI->start_y + 1;//���޷ֽ��߶���һ��
	int start_direction_x = block_start_direction_x0 + col_no * (pCGI->CFI.block_width + 2 * pCGI->CFI.separator);//��������(row_no,col_no)λ�õ�ɫ����ʼ����
	int start_direction_y = block_start_direction_y0 + row_no * (pCGI->CFI.block_high + 1 * pCGI->CFI.separator);
	//�зָ���
	if (pCGI->CFI.separator)
	{
		switch (direction)
		{

			case DOWN_TO_UP:
				gmw_inner_move_block_vertical(pCGI, start_direction_x, start_direction_y, distance, bdi_value, bdi, -1);
				break;

			case UP_TO_DOWN:
				gmw_inner_move_block_vertical(pCGI, start_direction_x, start_direction_y, distance, bdi_value, bdi, 1);
				break;

			case RIGHT_TO_LEFT:
				gmw_inner_move_block_horizontal(pCGI, start_direction_x, start_direction_y, col_no, distance, bdi_value, bdi, -1);
				break;

			case LEFT_TO_RIGHT:
				gmw_inner_move_block_horizontal(pCGI, start_direction_x, start_direction_y, col_no, distance, bdi_value, bdi, 1);
				break;
		}
	}

	//�޷ָ���
	else
	{
		switch (direction)
		{
			case DOWN_TO_UP:
				gmw_inner_move_block_vertical_no_border(pCGI, start_direction_x, block_start_direction_y0, row_no, distance, bdi_value, bdi, -1);
				break;

			case UP_TO_DOWN:
				gmw_inner_move_block_vertical_no_border(pCGI, start_direction_x, block_start_direction_y0, row_no, distance, bdi_value, bdi, 1);
				break;

			case RIGHT_TO_LEFT:
				gmw_inner_move_block_horizontal_no_border(pCGI, block_start_direction_x0, start_direction_x, start_direction_y, col_no, distance, bdi_value, bdi, -1);
				break;

			case LEFT_TO_RIGHT:
				gmw_inner_move_block_horizontal_no_border(pCGI, block_start_direction_x0, start_direction_x, start_direction_y, col_no, distance, bdi_value, bdi, 1);
				break;
		}

	}
	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ������̻����
  ���������const CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
		   int &MAction							��������� CCT_MOUSE_EVENT�����ֵ��Ч��Ϊ MOUSE_ONLY_MOVED/MOUSE_LEFT_BUTTON_CLICK/MOUSE_RIGHT_BUTTON_CLICK ����֮һ
													   ������� CCT_KEYBOARD_EVENT�����ֵ��Ч
		   int &MRow								��������� CCT_MOUSE_EVENT �� MAction = MOUSE_ONLY_MOVED/MOUSE_LEFT_BUTTON_CLICK�����ֵ��Ч����ʾ���ѡ�����Ϸ������кţ���0��ʼ��
												   ���������ֵ��Ч�����������Чֵ���´��󣬲��Ǳ������Ĵ�!!!��
		   int &MCol								��������� CCT_MOUSE_EVENT �� MAction = MOUSE_ONLY_MOVED/MOUSE_LEFT_BUTTON_CLICK�����ֵ��Ч����ʾ���ѡ�����Ϸ������кţ���0��ʼ��
												   ���������ֵ��Ч�����������Чֵ���´��󣬲��Ǳ������Ĵ�!!!��
		   int &KeyCode1							��������� CCT_KEYBOARD_EVENT�����ֵ��Ч��Ϊ�����ļ��루���˫���룬��Ϊ��һ����
												   ���������Ч�����������Чֵ���´��󣬲��Ǳ������Ĵ�!!!��
		   int &KeyCode2							��������� CCT_KEYBOARD_EVENT�����ֵ��Ч��Ϊ�����ļ��루���˫���룬��Ϊ�ڶ���������ǵ����룬��Ϊ0��
												   ���������Ч�����������Чֵ���´��󣬲��Ǳ������Ĵ�!!!��
		   const bool update_lower_status_line		������ƶ�ʱ���Ƿ�Ҫ�ڱ���������ʾ"[��ǰ���] *��*��/λ�÷Ƿ�"����Ϣ��true=��ʾ��false=����ʾ��ȱʡΪtrue��
  �� �� ֵ����������Լ��
		   1�����������ƶ����õ���MRow/MCol�봫�����ͬ(���ָ��΢С���ƶ�)���򲻷��أ�������
							  �õ����зǷ�λ�ã��򲻷��أ����� update_lower_status_line ����������״̬����ʾ"[��ǰ���] λ�÷Ƿ�"
							  �õ���MRow/MCol�봫��Ĳ�ͬ(��������һ���仯)������ update_lower_status_line ����������״̬����ʾ"[��ǰ���] *��*��"���ٷ���MOUSE_ONLY_MOVED����Щ��Ϸ���غ�Ҫ����ɫ��Ĳ�ͬ��ɫ��ʾ��
		   2������ǰ������������ҵ�ǰ���ָ��ͣ��������Ϸ�����*��*���ϣ��򷵻� CCT_MOUSE_EVENT ��MAction Ϊ MOUSE_LEFT_BUTTON_CLICK, MRow Ϊ�кţ�MCol Ϊ�б�
								  �ҵ�ǰ���ָ��ͣ���ڷǷ����򣨷���Ϸ������Ϸ�����еķָ��ߣ����򲻷��أ����� update_lower_status_line ����������״̬����ʾ"[��ǰ���] λ�÷Ƿ�"
		   3������ǰ�������Ҽ������ж����ָ��ͣ�������Ƿ�Ϸ���ֱ�ӷ��� CCT_MOUSE_EVENT ��MAction Ϊ MOUSE_LEFT_BUTTON_CLICK, MRow��MCol������
		   4��������¼����ϵ�ĳ������˫���밴��������ֱ�ӷ��� CCT_KEYBOARD_EVENT��KeyCode1/KeyCode2��Ϊ��Ӧ�ļ���ֵ
 ˵    ����ͨ������ cmd_console_tools.cpp �е� read_keyboard_and_mouse ����ʵ��
***************************************************************************/
int gmw_read_keyboard_and_mouse(const CONSOLE_GRAPHICS_INFO* const pCGI, int& MAction, int& MRow, int& MCol, int& KeyCode1, int& KeyCode2, const bool update_lower_status_line)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;

	int X, Y, MRow_last, MCol_last;
	int ret;
	bool loop = true;
	while (loop) // ���߸���ʵ����Ҫ���������˳�
	{
		MRow_last = MRow;
		MCol_last = MCol;
		cct_enable_mouse();
		ret = cct_read_keyboard_and_mouse(X, Y, MAction, KeyCode1, KeyCode2);

		if (ret == CCT_MOUSE_EVENT)
		{
			if (gmw_inner_handle_mouse_event(pCGI, X, Y, MRow, MCol, MAction, MRow_last, MCol_last, update_lower_status_line))
				return CCT_MOUSE_EVENT; // ��Ч������¼�
		}
		else if (ret == CCT_KEYBOARD_EVENT)
				return CCT_KEYBOARD_EVENT; // ���ؼ����¼�
		// ���Կ�����ӳ�ʱ���ƻ��ض������˳�ѭ��
	}

	return 0; // �����ʵ���Ĭ�Ϸ���ֵ
}