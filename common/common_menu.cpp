/* 2352018 大数据 刘彦 */
#include <iostream>
#include <conio.h>
#include "../include/bighw.h"
using namespace std;

/***************************************************************************
  函数名称：all_menu
  功    能：显示各菜单项，读入正确的选项后返回
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
char all_menu(int num)
{
    int len;
    int len0;
    const char a[10][50] =
    {
        "0.退出",
        "1.基本解",
        "2.基本解(步数记录)",
        "3.内部数组显示(横向)",
        "4.内部数组显示(纵向+横向)",
        "5.图形解-预备-画三个圆柱",
        "6.图形解-预备-在起始柱上画n个盘子",
        "7.图形解-预备-第一次移动",
        "8.图形解-自动移动版本",
        "9.图形解-游戏版"
    };
    const char arr[20][100] =
    {
        " 0.退出",
        " 1.内部数组，生成初始状态，寻找是否有初始可消除项",
        " 2.内部数组，消除初始可消除项后非0项下落并用0填充",
        " 3.内部数组，消除初始可消除项后查找消除提示",
        " 4.n*n的框架(无分隔线)，显示初始状态",
        " 5.n*n的框架(有分隔线)，显示初始状态",
        " 6.n*n的框架(无分隔线)，显示初始状态及初始可消除项",
        " 7.n*n的框架(有分隔线)，消除初始可消除项后显示消除提示",
        " 8.cmd图形界面完整版(有分隔线，鼠标移动时显示坐标，右键退出)",
        " 9.cmd图形界面完整版",
        "Q.退出",
        "A.命令行找出可消除项并标识",
        "B.命令行完成一次消除(分步骤显示)",
        "C.命令行完成一关(分步骤显示)",
        "D. 伪图形界面下用鼠标选择一个色块(无分隔线)",
        "E. 伪图形界面下用鼠标选择一个色块(有分隔线)",
        "F.伪图形界面完成一次消除(分步骤)",
        "G.伪图形界面完整版"
    };

    char a0[20][100];
    if (num == 0)
    {
        for (int i = 0; i < 10; i++)
        {
            tj_strcpy(a0[i], a[i]);
        }
        len0 = 10;

    }
    if (num == 1)
    {
        for (int i = 0; i < 10; i++)
        {
            tj_strcpy(a0[i], arr[i]);
        }
        len0 = 10;
    }
    if (num == 'A')
    {
        for (int i = 0; i < 10; i++)
        {
            tj_strcpy(a0[i], arr[i + 10]);
        }
        len0 = 8;
    }
    len = tj_strlen(a[0]);
    for (int i = 0; i < len0; i++)
    {
        if (i > 0)
        {
            if (tj_strlen(a0[i]) > tj_strlen(a0[i - 1]))
                len = tj_strlen(a0[i]);
        }
    }
    for (int i = 0; i < len; i++)
    {
        cout << "-";
    }
    cout << endl;
    for (int i = 1; i < len0; i++)
    {
        cout << a0[i] << endl;
    }
    cout << a0[0] << endl;
    for (int i = 0; i < len; i++)
    {
        cout << "-";
    }
    cout << endl;
    cout << "[请选择:]";
    char ch1;
    ch1 = _getch();
    while (1)
    {
        if ((num == 0 || num == 1) && ch1 >= 48 && ch1 <= 57)
        {
            break;
        }
        else if ((ch1 >= 'A' && ch1 <= 'G') || ch1 == 'Q')
        {
            break;
        }
        else if ((ch1 >= 'a' && ch1 <= 'g') || ch1 == 'q')
        {
            break;
        }

        ch1 = _getch();  // 获取用户按下的键的 ASCII 值

    }
    cout << ch1 << endl;

    return ch1;   // 返回用户按下的键的数值
}
