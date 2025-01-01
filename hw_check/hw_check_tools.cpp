/* 2352018 ������ ���� */
#define _CRT_SECURE_NO_WARNINGS
#include "hw_check.h"
#include "../include/class_aat.h"
#include "../include/class_cft.h"
#include "../include_mariadb_x86/mysql/mysql.h"

/***************************************************************************
  �������ƣ�is_stu_valid
  ��    �ܣ����cmd����Ĳ���stu�Ƿ�Ϸ�
  ���������
  �� �� ֵ��
  ˵    �����ж�ѧ�ų����Ƿ�Ϊ7�����Ƿ�Ϊȫ����
 ***************************************************************************/
int is_stu_valid(const string& stu)
{
    if (stu.length() != 7)  // ѧ�ű�����7λ
        return 0;  // ���Ȳ��ԣ����ز��Ϸ�
    for (size_t i = 0; i < stu.length(); i++)
        if (stu[i] < '0' || stu[i] > '9')  // ���ÿ���ַ��Ƿ�Ϊ����
            return 0;  // ���ڷ������ַ������ز��Ϸ�
    return 1;  // �Ϸ�ѧ��
}

/***************************************************************************
  �������ƣ�is_PDF_file
  ��    �ܣ�����ļ��Ƿ���PDF��ʽ
  ���������
  �� �� ֵ��
  ˵    ����ͨ���ļ�ͷ����Ƿ���PDF�ļ�
 ***************************************************************************/
int is_PDF_file(ifstream& fin)
{
    fin.clear();  // ����ļ������κδ���״̬
    fin.seekg(0, ios::beg);  // ���ļ�ָ���ƶ����ļ���ͷ
    char header[8];
    fin.read(header, 8);  // ��ȡ�ļ�ͷ��ǰ8���ֽ�

    // ����ļ�ͷ�Ƿ��� "%PDF-1." ��ͷ
    string pdf_file(header, 7);
    if (pdf_file == "%PDF-1.")
    {
        char version = header[7];  // ��ȡ�汾���ַ�
        if (version >= '0' && version <= '9')  // �жϰ汾���Ƿ���Ч
            return 1;  // ��PDF�ļ�
    }
    return 0;  // ����PDF�ļ�
}

/***************************************************************************
  �������ƣ�is_UTF8_file
  ��    �ܣ�����ļ��Ƿ���UTF-8�����ʽ
  ���������
  �� �� ֵ��
  ˵    �������ֽڼ���ļ��Ƿ����UTF-8�����׼
 ***************************************************************************/
bool is_UTF8_file(ifstream& fin)
{
    unsigned char temp_ch;
    bool ascii = true;  // Ĭ����Ϊ��ASCII�ַ���UTF-8���Ӽ���
    fin.clear();  // ����ļ������κδ���״̬
    fin.seekg(0, ios::beg);  // ���ļ�ָ���Ƶ���ͷ

    while (true)
    {
        temp_ch = fin.get();  // ��ȡ�ļ��е���һ���ַ�
        if (fin.eof())  // �����ļ�ĩβ
            break;

        if ((temp_ch & 0x80) == 0)  // 1�ֽ��ַ� (ASCII)
            continue;
        else if ((temp_ch & 0xe0) == 0xc0)  // 2�ֽ��ַ�
        {
            temp_ch = fin.get();
            if (fin.eof() || (temp_ch & 0xc0) != 0x80)
                return false;  // ���ǺϷ���UTF-8�ַ�
            ascii = false;
        }
        else if ((temp_ch & 0xf0) == 0xe0)  // 3�ֽ��ַ�
        {
            for (int i = 0; i < 2; ++i)
            {
                temp_ch = fin.get();
                if (fin.eof() || (temp_ch & 0xc0) != 0x80)
                    return false;  // ���ǺϷ���UTF-8�ַ�
            }
            ascii = false;
        }
        else if ((temp_ch & 0xf8) == 0xf0)  // 4�ֽ��ַ�
        {
            for (int i = 0; i < 3; ++i)
            {
                temp_ch = fin.get();
                if (fin.eof() || (temp_ch & 0xc0) != 0x80)
                    return false;  // ���ǺϷ���UTF-8�ַ�
            }
            ascii = false;
        }
        else
            return false;  // ��Ч���ֽ�ģʽ
    }
    return !ascii;  // ���û��ASCII�ַ�������UTF-8����
}

/***************************************************************************
  �������ƣ�is_WIN_file
  ��    �ܣ�����ļ��Ƿ�ʹ��Windows��ʽ�Ļ��з���CRLF��
  ���������
  �� �� ֵ��
  ˵    ��������ļ��Ƿ�����س����ͻ��з�����ϣ�\r\n��
 ***************************************************************************/
bool is_WIN_file(ifstream& fin)
{
    char ch;
    bool hasCR = false;  // �Ƿ��ֻس�����\r��
    bool hasLF = false;  // �Ƿ��ֻ��з���\n��

    while (fin.get(ch))  // ����ַ���ȡ�ļ�
    {
        if (ch == '\r')  // �س���
            hasCR = true;
        else if (ch == '\n')  // ���з�
            hasLF = true;
    }

    // �ļ����� \r ��û�� \n��˵���� Macintosh (CR) ��ʽ
    if (hasCR && !hasLF)
        return false;
    return true;  // �ļ���Windows��ʽ
}

/***************************************************************************
  �������ƣ�get_file_kind
  ��    �ܣ��ж��ļ�����
  ���������
  �� �� ֵ��
  ˵    ���������ļ���չ���ж��ļ�����
 ***************************************************************************/
int get_file_kind(const string& filename)
{
    size_t len = filename.length();
    size_t dotPos = string::npos;

    // �ֶ������ļ��������һ�����λ��
    for (int i = len - 1; i >= 0; i--)
    {
        if (filename[i] == '.')
        {
            dotPos = i;
            break;
        }
    }

    // ����ҵ��˵㣬��ȡ��չ��
    if (dotPos != string::npos)
    {
        string extension_name = filename.substr(dotPos + 1);
        for (char& c : extension_name)  // ����չ��ת��ΪСд
            c = my_tolower(c);

        // ������չ�������ļ�����
        if (extension_name == "h" || extension_name == "hpp" || extension_name == "c" || extension_name == "cpp")
            return SOURCE_FILE;  // Դ�����ļ�
        else if (extension_name == "pdf")
            return PDF_FILE;  // PDF�ļ�
        else
            return OTHER_FILE;  // �����ļ�����
    }
    return ERROR_FILE;  // ��Ч�ļ�
}

/***************************************************************************
  �������ƣ�replaceDot
  ��    �ܣ��滻�����еġ�Ϊ��
  ���������
  �� �� ֵ��
  ˵    �������������滻Ϊ��.����������������������
 ***************************************************************************/
string replaceDot(const string& input)
{
    string result = input;
    size_t pos = 0;
    while ((pos = result.find("��", pos)) != string::npos)
    {
        result.replace(pos, 2, ".");  // "��"ռ2���ֽ�
        pos += 1;  // ��������
    }
    return result;
}

/***************************************************************************
  �������ƣ�removeSpaces
  ��    �ܣ��Ƴ��ַ����е����пո�
  ���������
  �� �� ֵ��
  ˵    �������ַ����е����пո��ַ��Ƴ�
 ***************************************************************************/
string removeSpaces(const string& str)
{
    string result;

    // ����ԭʼ�ַ���������ַ�����
    for (char ch : str) 
    {
        if (ch != ' ')  // ����ַ����ǿո�����ӵ�����ַ���
            result += ch;
    }
    return result;
}

/***************************************************************************
  �������ƣ�replaceString
  ��    �ܣ��滻�ַ����е�ָ���ַ�
  ���������
  �� �� ֵ��
  ˵    ���������ַ�������ָ���ַ��滻Ϊ�µ��ַ�
 ***************************************************************************/
void replaceString(string& str, char old_value, char new_value)
{
    for (size_t i = 0; i < str.size(); ++i)
        if (str[i] == old_value)  // �ҵ�Ŀ���ַ�
            str[i] = new_value;  // �滻�ַ�
}

/***************************************************************************
  �������ƣ�is_valid_comment
  ��    �ܣ��ж��Ƿ�Ϊ�Ϸ�ע�͸�ʽ
  ���������
  �� �� ֵ��
  ˵    �����ж��Ƿ�Ϊ����ע�ͻ����ע�͸�ʽ
 ***************************************************************************/
int is_valid_comment(const vector<char>& first_line, vector<char>& comcontent)
{
    // ��ⵥ��ע��
    if (first_line[0] == '/' && first_line[1] == '/')
    {
        size_t start = 2;
        comcontent.assign(first_line.begin() + start, first_line.end());
        return 1;
    }
    /* ������ע�� */
    size_t len = first_line.size();
    if (first_line[0] == '/' && first_line[1] == '*')
    {
        if (first_line[len - 1] == '/' && first_line[len - 2] == '*')
        {
            size_t start = 2;
            comcontent.assign(first_line.begin() + start, first_line.end() - 2);
            return 1;  // �Ϸ��Ķ���ע��
        }
        else
            return (int)FIRST_LINE_ERROR_COMMIT;  // ����ע�͸�ʽ����ȷ
    }
    return (int)FIRST_LINE_NOT_COMMIT;  // ����ע����
}

/***************************************************************************
  �������ƣ�split_by_space
  ��    �ܣ����ո�ָ��ַ���
  ���������
  �� �� ֵ��
  ˵    ����ʹ�� stringstream ���ո�ָ��ַ���
 ***************************************************************************/
vector<string> split_by_space(const vector<char>& comcontent)
{
    string str(comcontent.begin(), comcontent.end());  // ���ַ�����תΪ�ַ���
    stringstream ss(str);  // ʹ�� stringstream ���зָ�
    istream_iterator<string> begin(ss), end;
    vector<string> result(begin, end);
    return result;
}

/***************************************************************************
  �������ƣ�get_base
  ��    �ܣ���ȡ�ļ�����״̬
  ���������
  �� �� ֵ���ļ�״̬
  ˵    �����ж��ļ����͡������ʽ�����з���ʽ
 ***************************************************************************/
FILE_SITUATIONS get_base(const string& filepath, const string& filename)
{
    ifstream fin;
    string _filepath = filepath;
    fin.open(_filepath, ios::in | ios::binary);  // �Զ�����ģʽ���ļ�
    if (!fin.is_open())
    {
        return NOT_SUBMIT;  // �ļ��޷��򿪣�����δ�ύ״̬
    }

    int file_kind = get_file_kind(filename);  // ��ȡ�ļ�����
    if (file_kind == SOURCE_FILE)
    {
        if (is_UTF8_file(fin))  // ����Ƿ�ΪUTF-8�ļ�
        {
            fin.close();
            return NOT_GB;  // ����GB�����ļ�
        }
        if (!is_WIN_file(fin))  // ����Ƿ�ΪWindows���з���ʽ
        {
            fin.close();
            return NOT_WIN;  // ����Windows��ʽ
        }
    }

    if (file_kind == PDF_FILE)
    {
        if (!is_PDF_file(fin))  // ����Ƿ�ΪPDF�ļ�
        {
            fin.close();
            return NOT_PDF;  // ����PDF�ļ�
        }
    }

    fin.close();
    return PASS;  // �ļ�ͨ�����
}

/***************************************************************************
  �������ƣ�check_file_size
  ��    �ܣ�����ļ���С���Ƿ����
  ���������
  �� �� ֵ��
  ˵    ����
 ***************************************************************************/
FILE_SITUATIONS check_file_size(ifstream& fin, const string& filepath)
{
    fin.open(filepath, ios::in | ios::binary | ios::ate);
    if (!fin.is_open())
    {
        cout << FILESTATUS_STR[NOT_SUBMIT] << endl;
        return NOT_SUBMIT;
    }
    streamsize filesize = fin.tellg();
    if (filesize < 3)
    {
        cout << FILESTATUS_STR[LESS_THAN_3_BIT] << endl;
        fin.close();
        return LESS_THAN_3_BIT;
    }
    fin.close();
    return PASS;
}

/***************************************************************************
  �������ƣ�check_file_encoding
  ��    �ܣ�����ļ�����
  ���������
  �� �� ֵ��
  ˵    ����
 ***************************************************************************/
FILE_SITUATIONS check_file_encoding(ifstream& fin)
{
    if (is_UTF8_file(fin))
    {
        cout << FILESTATUS_STR[NOT_GB] << endl;
        fin.close();
        return NOT_GB;
    }
    if (!is_WIN_file(fin))
    {
        cout << FILESTATUS_STR[NOT_WIN] << endl;
        fin.close();
        return NOT_WIN;
    }
    return PASS;
}

/***************************************************************************
  �������ƣ�read_first_line
  ��    �ܣ��������
  ���������
  �� �� ֵ��
  ˵    ����
 ***************************************************************************/
FILE_SITUATIONS read_first_line(ifstream& fin, vector<char>& firstlinecontent)
{
    fin.clear();
    fin.seekg(0, ios::beg);
    vector<char> line_content;
    char ch;
    while (!fin.eof())
    {
        while ((ch = fin.get()) != '\r' && ch != '\n' && (!fin.eof()))
            line_content.push_back(ch);
        if (ch == '\r')
            ch = fin.get();  // �������'\r'��˵����Windows����Ҫ�ٶ�һ��
        // ȥ����β�ո��Tab
        while (!line_content.empty() && (line_content.front() == ' ' || line_content.front() == '\t'))
            line_content.erase(line_content.begin());
        while (!line_content.empty() && (line_content.back() == ' ' || line_content.back() == '\t'))
            line_content.pop_back();
        if (!line_content.empty())
        {
            firstlinecontent = line_content;
            break;
        }
        if (fin.eof())
        {
            cout << FILESTATUS_STR[NO_FIRST_LINE] << endl;
            fin.close();
            return NO_FIRST_LINE;
        }
    }
    return PASS;
}

/***************************************************************************
  �������ƣ�read_and_clean_line
  ��    �ܣ���ȡ�ļ��е���Ч�в�ȥ��ǰ��ո���Tab
  ���������
  �� �� ֵ��
  ˵    ����
 ***************************************************************************/
bool read_and_clean_line(ifstream& fin, vector<char>& line_content) 
{
    line_content.clear();
    char ch;

    // �����ȡ�ַ�ֱ���������л��ļ�����
    while ((ch = fin.get()) != '\r' && ch != '\n' && !fin.eof()) 
        line_content.push_back(ch);

    // �����ȡ�� '\r'�������� Windows �Ļ��з�
    if (ch == '\r') 
        ch = fin.get();

    // ȥ����ǰ��Ŀո�� Tab
    while (!line_content.empty() && (line_content.front() == ' ' || line_content.front() == '\t')) 
        line_content.erase(line_content.begin());

    while (!line_content.empty() && (line_content.back() == ' ' || line_content.back() == '\t')) 
        line_content.pop_back();

    return !line_content.empty(); // �����Ƿ��ȡ����Ч����
}