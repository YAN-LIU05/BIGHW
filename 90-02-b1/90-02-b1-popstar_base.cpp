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
  �������ƣ�popstar_base_all
  ��    �ܣ�base�Ļ��ܺ���
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int popstar_base_all(int choice)
{
    int rows, cols;
    int row0, col0;
    int x, y;
    int count1 = 0;
    int score = 0;
    int total = 0;
    char input[MAX_LENGTH] = { 0 };
    int index = 0; // ���ڸ��������еĵ�ǰλ��
    bool end = false;
    // ������֤
    while (1)
    {
        cout << "����������(8-10)��" << endl;
        cin >> rows;

        if (rows >= MIN_ROWS && rows <= MAX_ROWS)
            break;
        else if (!cin.good())
        {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
        }
    }
    while (1)
    {
        cout << "����������(8-10)��" << endl;
        cin >> cols;

        if (cols >= MIN_COLS && cols <= MAX_COLS)
            break;
        else if (!cin.good())
        {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
        }
    }

    srand(static_cast<unsigned int>(time(nullptr)));
    int array[MAX_ROWS][MAX_COLS];   //�������Ϊ�����
    int flag[MAX_ROWS][MAX_COLS];
    int mark[MAX_ROWS][MAX_COLS];
    int array_copy[MAX_ROWS][MAX_COLS];
    int target;
    bool one_round = 1;
    fill_array(array, rows, cols, 2);
    if ((choice >= 'A' && choice <= 'C'))
    {
        print_origin(rows, cols, array, 1, 1);
    }

    switch (choice)
    {
        case 'A':
        case 'B':
        case 'C':
            while (one_round)
            {
                if (choice == 'A' || choice == 'B')
                    one_round = 0;
                while (1)
                {
                    cout << "������ĸ + ������ʽ[��:a2]�����������:";
                    cct_getxy(x, y);
                    while (!end)
                    {
                        char ch = _getch();
                        if (index < MAX_LENGTH - 1)
                        {
                            cout << ch;
                            input[index++] = ch;
                            input[index] = '\0';
                        }
                        if (index == 3 && input[0] >= 'a' && input[0] <= ('a' + rows - 1) && input[1] >= '0' && input[1] < '0' + cols && input[2] == '\r')
                        {
                            row0 = input[0] - 'a';
                            col0 = input[1] - '0';
                            end = true;
                        }

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
                    cout << endl;
                    cout << "����Ϊ" << char(row0 + 'A') << "��" << col0 << "��" << "        " << endl;


                    for (int i = 0; i < rows; ++i)
                    {
                        for (int j = 0; j < cols; ++j)
                        {
                            array_copy[i][j] = array[i][j];
                        }
                    }
                    copy_array(array, array_copy, rows, cols);
                    memset(flag, 0, sizeof(flag));
                    memset(mark, 0, sizeof(mark));
                    target = array[row0][col0];

                    star_replace0(array, flag, mark, rows, cols, row0, col0, target);

                    if (star_check(array, rows, cols, row0, col0))
                    {
                        cout << endl;
                        cout << "���ҽ������:" << endl;
                        print_origin(rows, cols, mark, 0, 1);
                        print_mark(rows, cols, array, mark, 0);
                        if (choice == 'B' || choice == 'C')
                        {
                            cout << "��ȷ���Ƿ��" << char(row0 + 'A') << col0 << "����Χ����ֵͬ����(Y/N/Q):";
                            char ch2;
                            ch2 = _getch();
                            while (1)
                            {
                                if (ch2 == 'Y' || ch2 == 'N' || ch2 == 'Q' || ch2 == 'y' || ch2 == 'n' || ch2 == 'q')
                                    break;
                                ch2 = _getch();
                            }
                            cout << ch2 << endl;
                            if (ch2 == 'Q' || ch2 == 'q')
                                break;
                            if (ch2 == 'N' || ch2 == 'n')
                            {
                                index = 0;
                                input[0] = '\0';
                                end = false;
                                continue;
                            }
                            if (ch2 == 'Y' || ch2 == 'y')
                            {
                                for (int i = 0; i < rows; ++i)
                                {
                                    for (int j = 0; j < cols; ++j)
                                    {
                                        if (mark[i][j] == 1)
                                        {
                                            array_copy[i][j] = 0;
                                            count1++;
                                        }
                                    }
                                }
                                cout << endl;
                                print_mark(rows, cols, array_copy, mark, 1);
                                score = count1 * count1 * 5;
                                total += score;
                                count1 = 0;
                                cout << "���ε÷�: " << score << " �ܵ÷�: " << total << endl << endl;
                                cout << "���س������������������ ...";
                                char cha = _getch();
                                while (1)
                                {
                                    if (cha == '\r')
                                        break;
                                    cha = _getch();
                                }
                                cout << endl;
                                zero_drop(array_copy, rows, cols);
                                print_mark(rows, cols, array_copy, mark, 2);
                                if (choice == 'C')
                                {
                                    score = 0;
                                    int left = 0;
                                    //�ж��Ƿ������һ������
                                    if (search_finish(array_copy, left, rows, cols)) 
                                    {
                                        //�´���ʾ��Ϣ
                                        cout << endl;
                                        cout << "������������,���س���������һ�ε����� ..." << endl << endl;
                                        //star_replace0(array_copy, flag, mark, rows, cols, row0, col0, target);
                                        
                                        index = 0;
                                        input[0] = '\0';
                                        row0 = 0;
                                        col0 = 0;
                                        end = false;
                                        int x, y;
                                        cct_getxy(x, y);
                                        for (int i = 0; i < rows; ++i)
                                        {
                                            for (int j = 0; j < cols; ++j)
                                            {
                                                array[i][j] = array_copy[i][j];
                                            }
                                        }
                                        copy_array(array_copy, array, rows, cols);
                                        while (1)
                                        {
                                            char cha0;
                                            cha0 = _getche();
                                            if (cha0 == 13)
                                            {
                                                break;
                                            }
                                            else
                                            {
                                                cct_gotoxy(x, y);
                                                putchar(' ');
                                                cct_gotoxy(x, y);
                                            }
                                        }
                                        go_right(array, rows, cols, 0, choice);
                                        print_mark(rows, cols, array, mark, 3);
                                    }
                                    else 
                                    {
                                        cout << endl;
                                        cct_setcolor(COLOR_HYELLOW, COLOR_RED);
                                        if (left == 0)
                                            cout << "����ȫ�����������̫����������" << endl;
                                        else 
                                            cout << "ʣ��" << left << "��������������ؽ���!" << endl;
                                        cct_setcolor(COLOR_BLACK, COLOR_WHITE);
                                        one_round = 0;
                                    }
                                }
                            }
                        }
                        break;
                    }
                    else
                    {
                        cout << "����ľ�������λ�ô���������ֵͬ,����������" << endl;
                        index = 0;
                        input[0] = '\0';
                        end = false;
                    }
                }
            }
            break;
        case 'D':
        case 'E':
        case 'F':
        case 'G':
            int numde;
            if (choice == 'D' || choice == 'E')
                cct_cls();
            
            if (choice == 'D')
                numde = 0;
            if (choice == 'E' || choice =='F' || choice == 'G')
                numde = 1;
            draw_map(rows, cols, numde, array, choice);
            cout << endl;
            break;
    }
    return 0;
}

