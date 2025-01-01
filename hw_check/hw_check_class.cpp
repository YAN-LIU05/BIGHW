/* 2352018 ������ ���� */
#define _CRT_SECURE_NO_WARNINGS
#include "hw_check_class.h"
#include "../include/class_aat.h"
#include "../include/class_cft.h"
#include "../include_mariadb_x86/mysql/mysql.h"

/***************************************************************************
  �������ƣ�
  ��    �ܣ����캯��
  ���������
  �� �� ֵ��
  ˵    ����
 ***************************************************************************/
Student::Student(const string& s1, const string& s2, const string& s3, const string& s4, const string& s5, const string& s6, const string& s7, const string& s8)
{
    term = s1;
    grade = s2;
    no = s3;
    name = s4;
    sex = s5;
    majorfull = s6;
    majorshort = s7;
    cno = s8;
}
Student::Student()
{
    term = "";
    grade = "";
    no = "";
    name = "";
    sex = "";
    majorfull = "";
    majorshort = "";
    cno = "";
}

Homework::Homework(const string& s1, const string& s2, const string& s3, const string& s4, const string& s5, const string& s6, const string& s7)
{
    kind = s1;
    cno = s2;
    number = s3;
    chapter = s4;
    week = s5;
    filename = s6;
    point = s7;
}

Config::Config()
{
    db_host = "";
    db_port = 0;
    db_name = "";
    db_username = "";
    db_passwd = "";
    db_currterm = "";
    src_rootdir = "";
}

hw_check::hw_check()
{
    action = "";
    cno = "";
    stu = "";
    file = "";
    chapter = -1;
    week = -1;
    cfgfile = "";
    display = "";
}

/***************************************************************************
  �������ƣ�read_db_config
  ��    �ܣ���ȡ�����ļ�
  ���������
  �� �� ֵ��
  ˵    ������ȡ�����ļ��е����ݿ���ļ�Ŀ¼��Ϣ
 ***************************************************************************/
int  Config::read_config(const string& cfgfile)
{
    string _cfgfile = cfgfile;
    config_file_tools cf(_cfgfile);  // ʹ�ù������ȡ�����ļ�
    if (!cf.is_read_succeeded())  // ����Ƿ�ɹ���ȡ�����ļ�
    {
        cerr << "�޷��������ļ�[" << cfgfile << "]����������." << endl;
        return 0;  // ��ȡ�����ļ�ʧ�ܣ�����0
    }

    // ��ȡ�����ļ��еĸ������ã���ʧ�������������Ϣ������0
    if (cf.item_get_string("[�ļ�Ŀ¼]", "src_rootdir", Config::src_rootdir) < 0)
    {
        cerr << "ȡ�����ļ� [" << cfgfile << "] ��" << "[�ļ�Ŀ¼]" << "���[" << "src_rootdir" << "]���ֵ����." << endl;
        return 0;
    }
    if (cf.item_get_string("[���ݿ�]", "db_host", Config::db_host) < 0)
    {
        cerr << "ȡ�����ļ� [" << cfgfile << "] ��" << "[���ݿ�]" << "���[" << "db_host" << "]���ֵ����." << endl;
        return 0;
    }
    if (cf.item_get_int("[���ݿ�]", "db_port", Config::db_port) < 0)
    {
        cerr << "ȡ�����ļ� [" << cfgfile << "] ��" << "[���ݿ�]" << "���[" << "db_port" << "]���ֵ����." << endl;
        return 0;
    }
    if (cf.item_get_string("[���ݿ�]", "db_name", Config::db_name) < 0)
    {
        cerr << "ȡ�����ļ� [" << cfgfile << "] ��" << "[���ݿ�]" << "���[" << "db_name" << "]���ֵ����." << endl;
        return 0;
    }
    if (cf.item_get_string("[���ݿ�]", "db_username", Config::db_username) < 0)
    {
        cerr << "ȡ�����ļ� [" << cfgfile << "] ��" << "[���ݿ�]" << "���[" << "db_username" << "]���ֵ����." << endl;
        return 0;
    }
    if (cf.item_get_string("[���ݿ�]", "db_passwd", Config::db_passwd) < 0)
    {
        cerr << "ȡ�����ļ� [" << cfgfile << "] ��" << "[���ݿ�]" << "���[" << "db_passwd" << "]���ֵ����." << endl;
        return 0;
    }
    if (cf.item_get_string("[���ݿ�]", "db_currterm", Config::db_currterm) < 0)
    {
        cerr << "ȡ�����ļ� [" << cfgfile << "] ��" << "[���ݿ�]" << "���[" << "db_currterm" << "]���ֵ����." << endl;
        return 0;
    }
    return 1;  // �����ļ���ȡ�ɹ�������1
}

/***************************************************************************
  �������ƣ�read_cmd
  ��    �ܣ���ȡ�����������в���
  ���������
  �� �� ֵ��
  ˵    �������������в�������ֵ��hw_check���е���Ӧ��Ա
 ***************************************************************************/
int  hw_check::read_cmd(const args_analyse_tools* const args)
{
    // �ж�ѧ���ļ��Ƿ���Ч�������Ϊ"all"����֤���ļ�
    if (args[ARGS_STU].get_string() != "all")
    {
        if (!is_stu_valid(args[ARGS_STU].get_string()))  // ����ļ��Ƿ���Ч
        {
            cout << "�ļ�[" << args[ARGS_STU].get_string() << "]�޷���." << endl;
            cout << endl;
            cout << "[--���ش���--] ��ȡ [--stu] ָ�����ļ�����." << endl;
            return -2;  // ����-2��ʾѧ���ļ���ȡ����
        }
    }

    // ����κ�cno������䳤���Ƿ�Ϸ�
    if (args[ARGS_CNO].get_string().length() >= 17)
    {

        this->action = args[ARGS_ACTION].get_string();
        this->cno = args[ARGS_CNO].get_string();
        this->stu = args[ARGS_STU].get_string();
        this->file = args[ARGS_FILE].get_string();
        this->chapter = args[ARGS_CHAPTER].existed() ? args[ARGS_CHAPTER].get_int() : -1;
        this->week = args[ARGS_WEEK].existed() ? args[ARGS_WEEK].get_int() : -1;
        this->cfgfile = args[ARGS_CFGFILE].get_string();
        this->display = args[ARGS_DISPLAY].get_string();
        return 1;  
    }

    // ����γ̺ų��Ȳ���8λ��13λ���򷵻ش���
    if (args[ARGS_CNO].get_string().length() != 8 && args[ARGS_CNO].get_string().length() != 13)
    {
        cout << "�κŲ���8/13λ" << endl;
        return -1;  // ����-1��ʾ�κŸ�ʽ����
    }

    // ������������
    this->action = args[ARGS_ACTION].get_string();
    this->cno = args[ARGS_CNO].get_string();
    this->stu = args[ARGS_STU].get_string();
    this->file = args[ARGS_FILE].get_string();
    this->chapter = args[ARGS_CHAPTER].existed() ? args[ARGS_CHAPTER].get_int() : -1;
    this->week = args[ARGS_WEEK].existed() ? args[ARGS_WEEK].get_int() : -1;
    this->cfgfile = args[ARGS_CFGFILE].get_string();
    this->display = args[ARGS_DISPLAY].get_string();
    return 1;
}

/***************************************************************************
  �������ƣ�read_db_content
  ��    �ܣ���ȡ���ݿ�����
  �����������
  �� �� ֵ������1��ʾ�ɹ�������0��ʾʧ��
  ˵    �����������ݿⲢִ��SQL��ѯ����ȡ���ݿ��е���ҵ��ѧ����Ϣ
 ***************************************************************************/
int  hw_check::read_db_content()
{
    MYSQL* mysql;
    MYSQL_RES* result;
    MYSQL_ROW row;

    // ��ʼ��MySQL����
    if ((mysql = mysql_init(nullptr)) == nullptr)
    {
        cerr << "mysql_init failed" << endl;
        return 0;  // ��ʼ��ʧ�ܣ�����0
    }

    // ���ӵ�MySQL���ݿ�
    if (mysql_real_connect(mysql, db_host.c_str(), db_username.c_str(), db_passwd.c_str(), db_name.c_str(), db_port, NULL, 0) == NULL)
    {
        cerr << "mysql_real_connect failed(" << mysql_error(mysql) << ")" << endl;
        return 0;  // ����ʧ�ܣ�����0
    }

    mysql_set_character_set(mysql, "gbk");  // �����ַ���ΪGBK

    // ������ѯ�����ȡ��ҵ��Ϣ
    string sql_hwquery_command = "select * from view_hwcheck_hwlist";
    if (cno.length() == 8 || cno.length() == 13)
        sql_hwquery_command = sql_hwquery_command + " where hw_cno = " + cno;
    else if (cno == "10108001,10108002")
        sql_hwquery_command = sql_hwquery_command + " where hw_cno in " + "('10108001', '10108002')";

    result = execute_query(mysql, sql_hwquery_command);  // ִ�в�ѯ
    if (result == nullptr) 
    {
        mysql_close(mysql);
        return 0; 
    }

    if ((int)mysql_num_rows(result) <= 0)  // �����ѯ���Ϊ��
    {
        cerr << "��ѯ������Ҫ��ļ�¼Ϊ0." << endl;
        mysql_free_result(result);
        mysql_close(mysql);
        return 0;  // ��ѯ���Ϊ�գ�����0
    }

    mysql_free_result(result);  // �ͷŽ����

    // ����½ں��ܴε�ɸѡ����
    if (chapter != -1)
        sql_hwquery_command = sql_hwquery_command + " and hw_chapter = " + to_string(chapter);
    if (week != -1)
        sql_hwquery_command = sql_hwquery_command + " and hw_week = " + to_string(week);

    // ִ�в�ѯ�����ȡ��ҵ����
    result = execute_query(mysql, sql_hwquery_command);
    if (result == nullptr) 
    {
        mysql_close(mysql);
        return 0;  
    }

    // ����ѯ���������ҵ�б�
    while ((row = mysql_fetch_row(result)) != nullptr)
    {
        Homework hw(row[0], row[1], row[2], row[3], row[4], row[5], row[6]);
        hwlist.push_back(hw);
    }
    mysql_free_result(result);  // �ͷŽ����

    // ��ȡѧ����Ϣ
    string sql_stuquery_command = "select * from view_hwcheck_stulist";
    if (cno.length() == 8 || cno.length() == 13)
        sql_stuquery_command = sql_stuquery_command + " where stu_cno = " + cno;
    else if (removeSpaces(cno) == "10108001,10108002")
        sql_stuquery_command = sql_stuquery_command + " where stu_cno in " + "('10108001', '10108002')";
    if (stu != "all")
        sql_stuquery_command = sql_stuquery_command + " and stu_no = " + stu;

    // ִ�в�ѯ����ȡѧ����Ϣ
    result = execute_query(mysql, sql_stuquery_command);
    if (result == nullptr) 
    {
        mysql_close(mysql);
        return 0;  
    }

    // ����ѯ�������ѧ���б�
    while ((row = mysql_fetch_row(result)) != nullptr)
    {
        Student stu(row[0], row[1], row[2], row[3], row[4], row[5], row[6], row[7]);
        stulist.push_back(stu);
    }
    mysql_free_result(result);  // �ͷŽ����

    mysql_close(mysql);  // �ر�MySQL����

    if (!check_file_validity())
        return 0;  

    return 1;  
}

/***************************************************************************
  �������ƣ�execute_query
  ��    �ܣ�ִ��MySQL��ѯ�����ؽ��
  ���������
  �� �� ֵ��
  ˵    ����ִ��MySQL��ѯ�������󣬷��ؽ����
 ***************************************************************************/
MYSQL_RES* hw_check::execute_query(MYSQL* mysql, const string& query)
{
    if (mysql_query(mysql, query.c_str()))  // ִ��SQL��ѯ
    {
        cerr << "mysql_query failed(" << mysql_error(mysql) << ")" << endl;
        return nullptr;  // ��ѯʧ�ܣ�����nullptr
    }

    MYSQL_RES* result = mysql_store_result(mysql);  // �洢��ѯ���
    if (result == nullptr)
    {
        cout << "mysql_store_result failed" << endl;
        return nullptr;  // �洢���ʧ�ܣ�����nullptr
    }

    return result;  // ���ز�ѯ�����
}

/***************************************************************************
  �������ƣ�check_file_validity
  ��    �ܣ�����ļ���ʽ����Ч��
  ���������
  �� �� ֵ��
  ˵    �������ݲ�ͬ�ļ�鶯��������ļ���ʽ�Ƿ�Ϸ�
 ***************************************************************************/
bool hw_check::check_file_validity()
{
    if (this->action == "firstline")
    {
        if (this->file == "all")  // ��������ļ�
        {
            for (auto it = hwlist.begin(); it != hwlist.end();)
            {
                if (get_file_kind(it->filename) != SOURCE_FILE)  // ����ļ�����Դ�����ļ�����ɾ��
                    it = hwlist.erase(it);
                else
                    ++it;
            }
        }
        else
        {
            if (get_file_kind(this->file) != SOURCE_FILE)  // ��鵥���ļ�
            {
                cerr << "���м����ļ�[" << this->file << "]������Դ�����ļ�." << endl;
                return false;  // �ļ���ʽ��Ч������false
            }
        }
    }
    else if (this->action == "secondline")
    {
        if (get_file_kind(this->file) != SOURCE_FILE)  // �������ļ�
        {
            cerr << "���м����ļ�[" << this->file << "]������Դ�����ļ�." << endl;
            return false;  
        }
    }
    return true; 
}