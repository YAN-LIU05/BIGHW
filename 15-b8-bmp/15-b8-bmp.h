/* 2352018 ������ ���� */
#pragma once

//����������κ�ͷ�ļ����ر���<Windows.h>���鵽����0�������ǵ���-20 ������

//���в���������ϣ��˽������⼸��Ԥ������������ã����ܷ�������ҵ�������㣡����
//#pragma pack(show) //�Ծ�����Ϣ����ʽ��ʾ��ǰ�ֽڶ����ֵ
//#pragma pack(push) //����ǰ�ֽڶ���ֵѹ�������ջ��ջ��
//#pragma pack(push, 4) //����ǰ�ֽڶ���ֵѹ�������ջ��ջ����Ȼ���ٽ�4���õ�ǰֵ
//#pragma pack(pop)  //��������ջջ�����ֽڶ���ֵ����������Ϊ��ǰֵ
//#pragma pack() //���������ǻָ�Ĭ��ֵ

//������������Ҫ�Ľṹ�壨�ࣩ����������������
#define my_RGB(r, g, b) ((unsigned int)(((b) & 0xFF) | (((g) & 0xFF) << 8) | (((r) & 0xFF) << 16))) 

class bitmap {
private:
    int b_width;               // ͼ����
    int b_height;              // ͼ��߶�
    short biBitCount;          // λ��
    int biClrUsed;             // ��ɫ����ɫ��
    unsigned long bfoffBits;   // λͼ����ƫ��
    int filesize;              // �ļ���С
    unsigned char* bmp_data;   // λͼ����
    unsigned char(*color_board)[4]; // ��ɫ������

    // �ڲ���������ȡ������ɫ
    unsigned int get_pixel(int row, int col) const;


public:
    bitmap(const char* const filename);
    ~bitmap();
    int show(const int top_left_x, const int top_left_y, const int angle, const bool is_mirror,
        void (*draw_point)(const int x, const int y, const unsigned char red, const unsigned char green, const unsigned char blue)) const;
};
