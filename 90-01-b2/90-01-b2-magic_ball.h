/* 2352018 ������ ���� */
#pragma once

#define MIN_ROWS  5
#define MAX_ROWS  10
#define MIN_COLS  5
#define MAX_COLS  10
#define TIME 20


int ball_base_all(int choice);   //base�Ļ��ܺ���


void print_mark(int rows, int cols, int array[MIN_ROWS][MAX_ROWS]);   //��ӡ��ʼ��������
void print_tips(int rows, int cols, int array[MIN_ROWS][MAX_ROWS]);   //��ӡ��ʾ��
void base_remove(int array[MAX_ROWS][MAX_COLS], int rows, int cols, int choice);   //��ͬ���ֵ�������0������
void draw_ball(int i, int j, int color, int border);   //��������
void draw_clean(int i, int j, int color);   //��������
void draw_nine(int array[MIN_ROWS][MAX_ROWS], int rows, int cols, int choice);   //��9���Ļ��ܺ���
int draw_fall(int array[MAX_ROWS][MAX_COLS], int rows, int cols, int choice, int array0[MAX_ROWS][MAX_COLS], int have_score);   //��������
void move_elements_down(int array[][MAX_COLS], int rows, int cols);   //�ò�������



int tj_strcasecmp(const char* s1, const char* s2);   //�Ƚ��ַ���s1��s2�Ĵ�С,Ӣ����ĸ���ִ�Сд
