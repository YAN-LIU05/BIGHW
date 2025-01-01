/* 2352018 ������ ���� */
#pragma once
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
#include <sstream>

#include "../include/class_aat.h"
#include "../include_mariadb_x86/mysql/mysql.h"
using namespace std;

class hw_check;
class Student;
class Homework;

enum ARGS {
	ARGS_HELP = 0, ARGS_DEBUG, ARGS_ACTION, ARGS_CNO, ARGS_STU,
	ARGS_FILE, ARGS_CHAPTER, ARGS_WEEK, ARGS_DISPLAY, ARGS_CFGFILE
};
enum FILES_KIND {
	ERROR_FILE = 0, SOURCE_FILE, PDF_FILE, OTHER_FILE
};
enum PRINT_SITUATIONS {
	END_OF_NOT_ALL = 0, STUDENT_OF_ALL, END_OF_ALL
};
enum FILE_SITUATIONS {
	PASS = 0,                  // ͨ��
	NOT_SUBMIT,                // δ�ύ
	NOT_PDF,                   // �����PDF�ļ���ֻ��base��ʹ��
	NOT_WIN,                   // VS�޷�����
	NOT_GB,                    // ������GB����

	LESS_THAN_3_BIT,           // �ļ�С��3�ֽ�
	NO_FIRST_LINE,             // ����Ч����
	FIRST_LINE_ERROR_COMMIT,   // ���ж���ע�͸�ʽ����ȷ
	FIRST_LINE_NOT_COMMIT,     // ���в���ע����
	FIRST_LINE_NOT_3,          // ���в�������
	FIRST_LINE_CHECK_ERROR,    // ���м�����

	LESS_THAN_2_LINE,          // �ļ�С������
	SECOND_LINE_NOT_COMMIT,    // ���в���ע��
	SECOND_LINE_ERROR,         // ������������
	OTHER_ERROR                // ������������������
};
enum CROSS_SITUATIONS {
	NO = 0, NAME, CORRECT, ABANDON
};

int is_stu_valid(const string& stuno);
int get_file_kind(const string& filename);
bool is_UTF8_file(ifstream& fin);
bool is_WIN_file(ifstream& fin);
int is_PDF_file(ifstream& fin);
string replaceDot(const string& input);
string removeSpaces(const string& str);
int  is_valid_comment(const vector<char>& firstlinecontent, vector<char>& comcontent);
vector<string> split_by_space(const vector<char>& comcontent);
FILE_SITUATIONS get_base(const string& filepath, const string& filename);
FILE_SITUATIONS get_print_first(const string& filepath, const string& filename, const Student& student);
FILE_SITUATIONS get_print_second(const string& filepath, vector<Student>& check_stulist, const string& own_no);
FILE_SITUATIONS check_file_size(ifstream& fin, const string& filepath);
FILE_SITUATIONS check_file_encoding(ifstream& fin);
FILE_SITUATIONS read_first_line(ifstream& fin, vector<char>& firstlinecontent);
bool read_and_clean_line(ifstream& fin, vector<char>& line_content);

const string FILESTATUS_STR[] = { "��ȷ" ,"δ�ύ" , "PDF�ļ���ʽ����ȷ" , "Դ�ļ���ʽ����ȷ(VS�޷�ʶ��)",
								  "Դ�ļ���ʽ����ȷ(��GB����)",  "�ļ�С��3�ֽ�","����Ч����",
								  "���ж���ע�͸�ʽ����ȷ", "���в���ע����","���в�������","���м�����",
								  "�ļ�С������", "���в���ע��","������������","" };
const string STUDENT_INFORMATION[] = { "��ϸ��Ϣ", "ѧ����ϸ��Ϣ", "������ϸ��Ϣ", "" };
const string NOT_MATCH[] = { "ѧ�Ų�ƥ��", "������ƥ��", "�༶��ƥ��", "" };
const string CROSS_ERROR[] = { "�Է�ѧ�Ų�����", "�Է���������ȷ", "ûд��������", "��������", "" };
const int FILE_STATUS_NUM = 14;