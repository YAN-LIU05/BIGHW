/* 2352018 ������ ���� */
#include <iostream>
#include <fstream>
//������������κ�ͷ�ļ����ر���<Windows.h>���鵽����0�������ǵ���-20!!!!!
using namespace std;

#include "15-b8-bmp.h"

/***************************************************************************
  �������ƣ�bitmap(const char* const filename)
  ��    �ܣ����캯������ȡָ���� BMP ͼ���ļ�
  ���������const char* const filename - �ļ���
  �� �� ֵ����
  ˵    ������ȡ BMP �ļ�������ͼ����Ϣ
***************************************************************************/
bitmap::bitmap(const char* const filename) 
{
    // ���ļ�
    ifstream in(filename, ios::in | ios::binary);
    if (!in.is_open()) 
    {
        cout << "���ļ�ʧ�ܣ�" << endl;
        exit(-1);
    }

    // ���ļ�ͷ��Ч����
    in.seekg(2, ios::cur);  // �����ļ���ʶ��
    in.read((char*)&filesize, sizeof(int));
    in.seekg(4, ios::cur);   // ���������ֽ�
    in.read((char*)&bfoffBits, sizeof(unsigned long));  // λͼ����ƫ��

    // ��λͼ��Ϣͷ��Ч����
    in.seekg(4, ios::cur);   // ������Ϣͷ
    in.read((char*)&b_width, sizeof(int));   // ���
    in.read((char*)&b_height, sizeof(int));  // �߶�
    in.seekg(2, ios::cur);   // ����ɫ�������Ϣ
    in.read((char*)&biBitCount, sizeof(short));  // λ��
    in.seekg(16, ios::cur);  // ��������δ����Ϣ
    in.read((char*)&biClrUsed, sizeof(int));   // ��ɫ����ɫ��

    if (biClrUsed == 0)
        biClrUsed = (1 << biBitCount);  // Ĭ��ʹ�õ���ɫ��

    // ��ȡ��ɫ�壨����У�
    in.seekg(4, ios::cur);   // ���������ֽ�
    if (biBitCount <= 8) // �����8λ�����£���ȡ��ɫ��
    {   
        color_board = new unsigned char[biClrUsed][4];
        memset(color_board, 0, sizeof(color_board));  // ��ʼ��
        in.read((char*)color_board, biClrUsed * 4);  // ��ȡ��ɫ������
    }
    else 
        color_board = NULL;

    // ��ȡλͼ����
    bmp_data = new unsigned char[filesize];
    in.read((char*)bmp_data, filesize - bfoffBits);  // ��ȡλͼ���ݲ���
    in.close();  // �ر��ļ�
}


/***************************************************************************
  �������ƣ�~bitmap()
  ��    �ܣ������������ͷ��ڴ�
  �����������
  �� �� ֵ����
  ˵    �����ͷ��ڴ�
***************************************************************************/
bitmap::~bitmap()
{
    delete[] color_board;
    delete[] bmp_data;
}

/***************************************************************************
  �������ƣ�get_pixel(int row, int col) const
  ��    �ܣ����������ȡ������ɫ
  ���������row - �У�col - ��
  �� �� ֵ�����ص� RGB ��ɫ
  ˵    ��������ͼ����ָ��λ�õ���ɫ
***************************************************************************/
unsigned int bitmap::get_pixel(int row, int col) const 
{
    // �����к�����Ӧ BMP ������ϵͳ���ӵײ���ʼ��
    int b_row = (b_height) > 0 ? (b_height - row - 1) : row;
    int b_col = col;
    int RowByteCnt = (((b_width * biBitCount) + 31) >> 5) << 2; // ÿ�е��ֽ���

    if (biBitCount <= 8) // 8λ������ͼ��
    {  
        // ÿ���ֽڶ�Ӧ��������
        int PixelPerByte = 8 / biBitCount;
        // �����ֽ�ƫ��
        int pixelOffset = (b_row * RowByteCnt) + b_col / PixelPerByte;
        // ��ȡ��ɫ�����ɫ����
        unsigned int index = bmp_data[pixelOffset];
        // ���㵱ǰ����������λƫ����
        int indexOffset = (PixelPerByte - 1 - b_col % PixelPerByte) * biBitCount;
        index >>= indexOffset;
        index = index % biClrUsed;  // ȷ����������Խ��
        // �ӵ�ɫ���л�ȡ��ɫ
        unsigned char B = color_board[index][0];
        unsigned char G = color_board[index][1];
        unsigned char R = color_board[index][2];
        return my_RGB(R, G, B);  // ʹ�ú귵��RGB��ɫֵ
    }
    else // 24λ��32λͼ��
    {  
        // ÿ�����ص��ֽ���
        int bytesPerPixel = biBitCount / 8;
        // �����ֽ�ƫ��
        int pixelOffset = (b_row * RowByteCnt) + bytesPerPixel * b_col;

        // ����24/32λͼ��BMP��Ĭ�ϴ洢˳��ΪBGR
        unsigned char B = bmp_data[pixelOffset];
        unsigned char G = bmp_data[pixelOffset + 1];
        unsigned char R = bmp_data[pixelOffset + 2];

        return my_RGB(R, G, B);  // ʹ�ú귵��RGB��ɫֵ
    }
}

/***************************************************************************
  �������ƣ�show
  ��    �ܣ����ݸ��������ꡢ�Ƕȡ��Ƿ������Ϣ����ʾͼ��
  ���������top_left_x - ���Ͻ� x ���꣬top_left_y - ���Ͻ� y ����
            angle - ��ת�Ƕȣ�is_mirror - �Ƿ���
            draw_point - ���Ƶ�����ĺ���ָ��
  �� �� ֵ����ʾͼ���������
  ˵    �������ݸ����Ĳ�������ͼ�񣬿�����ת������
***************************************************************************/
int bitmap::show(const int top_left_x, const int top_left_y, const int angle, const bool is_mirror,
    void (*draw_point)(const int x, const int y, const unsigned char red, const unsigned char green, const unsigned char blue)) const
{
    // ������ת�;���Ĳ���������ͼ���ÿ������
    int pixel_count = 0;
    for (int row = 0; row < b_height; row++) 
    {
        for (int col = 0; col < b_width; col++)
        {
            unsigned int color = get_pixel(row, col);
            unsigned char R = (color >> 16) & 0xFF;
            unsigned char G = (color >> 8) & 0xFF;
            unsigned char B = color & 0xFF;
            int new_x = top_left_x + col;
            int new_y = top_left_y + row;

            // ���������ת
            if (is_mirror) 
                new_x = top_left_x + (b_width - col - 1);
            if (angle == 90) 
            {
                int temp = new_x;
                new_x = top_left_y + (b_width - new_y - 1);
                new_y = top_left_x + temp;
            }
            else if (angle == 180) 
            {
                new_x = top_left_x + (b_width - new_x - 1);
                new_y = top_left_y + (b_height - new_y - 1);
            }
            else if (angle == 270) 
            {
                int temp = new_x;
                new_x = top_left_x + (b_height - new_y - 1);
                new_y = top_left_y + temp;
            }

            draw_point(new_x, new_y, R, G, B);
            pixel_count++;
        }
    }
    return pixel_count;
}