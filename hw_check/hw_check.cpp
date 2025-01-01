/* 2352018 ������ ���� */
#define _CRT_SECURE_NO_WARNINGS
#include "hw_check_class.h"
#include "../include/class_aat.h"
#include "../include/class_cft.h"
#include "../include_mariadb_x86/mysql/mysql.h"

/***************************************************************************
  �������ƣ�get_print_first
  ��    �ܣ���ȡ����ӡ����
  ���������
  �� �� ֵ��
  ˵    ����
 ***************************************************************************/
FILE_SITUATIONS get_print_first(const string& filepath, const string& filename, const Student& student)
{
    ifstream fin;
    string _filepath = filepath;
    // ����ļ���С
    FILE_SITUATIONS result = check_file_size(fin, filepath);
    if (result != PASS)
        return result; // ����ļ���С������Ҫ��ֱ�ӷ���
    fin.open(_filepath, ios::in | ios::binary); // �Զ�����ģʽ���ļ�
    // ����ļ�����
    result = check_file_encoding(fin);
    vector<char> firstlinecontent;
    if (result != PASS)
        return result; // ����ļ�������󣬷��ش���״̬
    // ��ȡ�ļ�����
    result = read_first_line(fin, firstlinecontent);
    if (result != PASS)
        return result; // �����ȡ����ʧ�ܣ����ش���״̬
    fin.close();
    string str(firstlinecontent.begin(), firstlinecontent.end()); // ����������תΪ�ַ���
    // ���������������2���ַ�����ʾ��ʽ������Ҫ��
    if (firstlinecontent.size() < 2)
    {
        cout << FILESTATUS_STR[FIRST_LINE_NOT_COMMIT];
        cout << " [" << str << "]" << endl;
        return FIRST_LINE_NOT_COMMIT; // �����������ݲ����Ϲ淶�Ĵ���
    }
    vector<char> comcontent;
    int comstatus = is_valid_comment(firstlinecontent, comcontent);
    // �ж�ע�͸�ʽ�Ƿ�Ϸ�
    if (comstatus == (int)FIRST_LINE_NOT_COMMIT)
    {
        cout << FILESTATUS_STR[FIRST_LINE_NOT_COMMIT];
        cout << " [" << str << "]" << endl;
        return FIRST_LINE_NOT_COMMIT; // ���ע�͸�ʽ����ȷ�����ش���
    }
    else if (comstatus == (int)FIRST_LINE_ERROR_COMMIT)
    {
        cout << "���в��Ƿ���Ҫ���/* */��ʽ [" << str << "]" << endl;
        return FIRST_LINE_ERROR_COMMIT; // ���ע�͸�ʽ���󣬷��ش���
    }
    int have_no = 0, have_major = 0, have_name = 0;
    vector<string> comitem = split_by_space(comcontent); // ��ע�����ݰ��ո��ֳ���
    // ���ע�����3����˵����ʽ����
    if (comitem.size() != 3)
    {
        cout << FILESTATUS_STR[FIRST_LINE_NOT_3];
        cout << " [" << str << "]" << endl;
        return FIRST_LINE_NOT_3; // ע����������󣬷��ش���
    }

    /* ��Ӧע���е�ѧ����Ϣ */
    auto it = find(comitem.begin(), comitem.end(), student.no);
    if (it != comitem.end()) // �ж�ѧ���Ƿ���ע����
        have_no = 1;

    // ����רҵ����е� | �ָ���
    size_t delimiter_pos = student.majorshort.find('|');
    if (delimiter_pos != string::npos)
    {
        // ����� |������ | ǰ��Ĳ����Ƿ������ comitem ��
        string part1 = student.majorshort.substr(0, delimiter_pos);
        string part2 = student.majorshort.substr(delimiter_pos + 1);
        if (find(comitem.begin(), comitem.end(), part1) != comitem.end() || find(comitem.begin(), comitem.end(), part2) != comitem.end())
            have_major = 1;
    }
    else
    {
        // ���û�� |��ֱ�Ӳ�������רҵ���
        it = find(comitem.begin(), comitem.end(), student.majorshort);
        if (it != comitem.end())
            have_major = 1;
    }

    it = find(comitem.begin(), comitem.end(), student.majorfull);
    if (it != comitem.end()) // ���ȫ��רҵ�Ƿ�ƥ��
        have_major = 1;

    it = find(comitem.begin(), comitem.end(), student.name);
    if (it != comitem.end()) // ��������Ƿ�ƥ��
        have_name = 1;

    // ���ѧ�š�רҵ�������Ƿ�ƥ��
    if ((have_no + have_major + have_name) == 3)
    {
        cout << FILESTATUS_STR[PASS] << endl;
        return PASS; // ���������Ϣƥ�䣬����PASS
    }
    else
    {
        cout << "����";
        if (!have_no)
            cout << NOT_MATCH[0];
        if (!have_name)
            cout << NOT_MATCH[1];
        if (!have_major)
            cout << NOT_MATCH[2];
        cout << " [" << str << "]" << endl;
        return FIRST_LINE_CHECK_ERROR; // �������Ϣ��ƥ�䣬���ش���
    }
}

/***************************************************************************
  �������ƣ�get_print_second
  ��    �ܣ���ȡ����ӡ����
  ���������
  �� �� ֵ��
  ˵    ����
 ***************************************************************************/
FILE_SITUATIONS get_print_second(const string& filepath, vector<Student>& check_stulist, const string& own_no)
{
    ifstream fin;
    string _filepath = filepath;
    // ����ļ���С
    FILE_SITUATIONS result = check_file_size(fin, filepath);
    if (result != PASS)
        return result; // ����ļ���С������Ҫ��ֱ�ӷ���
    fin.open(_filepath, ios::in | ios::binary); // �Զ�����ģʽ���ļ�
    // ����ļ�����
    if (is_UTF8_file(fin)) // һ����sourcefile������Ҫ�ж��Ƿ����GB����
    {
        cout << FILESTATUS_STR[NOT_GB] << endl;
        fin.close();
        return NOT_GB; // ����ļ����벻����Ҫ�󣬷��ر������
    }
    fin.clear();
    fin.seekg(0, ios::beg);

    string line;
    size_t line_count = 0;
    while (getline(fin, line))
    {
        line_count++;
        if (line_count > 1)
            break; // ������ֶ���һ�У���������ѭ��
    }
    if (line_count <= 1)
    {
        fin.close();
        cout << FILESTATUS_STR[SECOND_LINE_ERROR] << endl; // ������������
        return SECOND_LINE_ERROR; // �ļ������������У����ش���
    }
    fin.clear();
    fin.seekg(0, ios::beg);
    //ѭ������ֱ���ҵ����в���
    vector<char> line_content, firstlinecontent, secondlinecontent;
    line_count = 0;
    while (!fin.eof())
    {
        if (read_and_clean_line(fin, line_content))
        {
            ++line_count;
            if (line_count == 1)
                firstlinecontent = line_content; // ��¼��������
            else if (line_count == 2)
            {
                secondlinecontent = line_content; // ��¼��������
                break;
            }
        }
        if (fin.eof())
        {
            cout << FILESTATUS_STR[LESS_THAN_2_LINE] << endl; // �ļ�С������
            fin.close();
            return LESS_THAN_2_LINE; // �ļ������������У����ش���
        }
    }
    fin.close();
    // �Դ��н��м�� 
    if (secondlinecontent.size() < 2)
    {
        cout << FILESTATUS_STR[SECOND_LINE_NOT_COMMIT] << endl;
        return SECOND_LINE_NOT_COMMIT; // �������ݲ�����ע�͸�ʽ
    }
    vector<char> comcontent;
    int comstatus = is_valid_comment(secondlinecontent, comcontent); // �������Ƿ�Ϊ��Чע��
    if (comstatus == (int)FIRST_LINE_NOT_COMMIT || comstatus == (int)FIRST_LINE_ERROR_COMMIT)
    {
        cout << FILESTATUS_STR[SECOND_LINE_NOT_COMMIT] << endl; // ���в���ע��
        return SECOND_LINE_NOT_COMMIT;
    }
    vector<string> comitem = split_by_space(comcontent); // ���ע������
    // �õ�����ѧ������
    FILE_SITUATIONS status = validate_student_info(comitem, own_no, check_stulist); // ��֤ѧ����Ϣ
    if (status != PASS) return status;  // ���ѧ����Ϣ��֤ʧ�ܣ��򷵻ش���

    cout << FILESTATUS_STR[PASS] << endl;
    return PASS; // �����֤ͨ��������PASS
}

/***************************************************************************
  �������ƣ�cross_check
  ��    �ܣ�������
  ���������
  �� �� ֵ��
  ˵    ����
 ***************************************************************************/
void hw_check::cross_check(const vector<vector<Student>>& total_check_stulist, const vector<Student>& total_stulist)
{
    cout << "����������" << endl;
    for (size_t i = 0; i < total_stulist.size(); i++) // i�ǵ�ǰ����ѧ��
    {
        if (cno == "10108001" || cno == "10108002" || cno == "5000244001602")
            cout << setw(3) << i + 1 << ": " << cno << "-" << total_stulist[i].no << "-" << total_stulist[i].name << endl;
        else
        {
            if (i + 1 < 88)
                cout << setw(3) << i + 1 << ": " << 10108001 << "-" << total_stulist[i].no << "-" << total_stulist[i].name << endl;
            else
                cout << setw(3) << i + 1 << ": " << 10108002 << "-" << total_stulist[i].no << "-" << total_stulist[i].name << endl;
        }
        for (size_t j = 0; j < total_check_stulist[i].size(); j++) // j�Ǻ��㻥���ѧ��
        {
            cout << '\t' << total_check_stulist[i][j].no << " " << total_check_stulist[i][j].name << '\t';
            size_t k = 0;
            for (; k < total_stulist.size(); k++) // k�ǻ���ѧ����total_stulist�е����
                if (total_stulist[k].no == total_check_stulist[i][j].no)
                    break;
            if (k == total_stulist.size())
                cout << CROSS_ERROR[NO] << endl;
            else
            {
                if (total_stulist[k].name != total_check_stulist[i][j].name)
                {
                    cout << CROSS_ERROR[NAME] << endl;
                    continue;
                }
                size_t m = 0;
                for (; m < total_check_stulist[k].size(); m++) // �����Է���check_list������û����
                {
                    if (total_check_stulist[k][m].no == total_stulist[i].no) // ѧ�Ŷ�
                    {
                        if (total_check_stulist[k][m].name != total_stulist[i].name) // ������
                            cout << CROSS_ERROR[CORRECT] << endl;
                        else
                            cout << endl; // �����ԣ���һ��
                        break;
                    }
                }
                if (m == total_check_stulist[k].size())
                    cout << CROSS_ERROR[ABANDON] << endl;
            }
        }
    }
}

/***************************************************************************
  �������ƣ�validate_student_info
  ��    �ܣ���֤ѧ����Ϣ
  ���������
  �� �� ֵ��
  ˵    ����
 ***************************************************************************/
FILE_SITUATIONS validate_student_info(const vector<string>& comitem, const string& own_no, vector<Student>& check_stulist)
{
    for (size_t i = 0; i < comitem.size(); i = i + 2)
    {
        if (i >= comitem.size() - 1) // ���ڽ�β�����ִ˴���
        {
            cout << "��[" << i / 2 << "]��ѧ���������Ϣ��ȫ(ֻ����һ��)���������ݺ���" << endl;
            return OTHER_ERROR;
        }

        string stu_no = comitem[i], stu_name = comitem[i + 1];

        // ѧ�ų��ȼ��
        if (stu_no.length() != 7)
        {
            cout << "��" << i / 2 + 1 << "λͬѧ��ѧ��[" << stu_no << "]����7λ���������ݺ���" << endl;
            return OTHER_ERROR;
        }

        // ѧ����Ч�Լ��
        if (!is_stu_valid(stu_no))
        {
            cout << "��" << i / 2 + 1 << "λͬѧ��ѧ��[" << stu_no << "]���з����ִ��ڣ��������ݺ���" << endl;
            return OTHER_ERROR;
        }

        // ����д�Լ�����Ϣ
        if (stu_no == own_no)
        {
            cout << "��[" << i / 2 + 1 << "]��д���Լ����������ݺ���" << endl;
            return OTHER_ERROR;
        }

        // ��ӵ�ѧ��������
        Student temp_check_stu;
        temp_check_stu.no = stu_no;
        temp_check_stu.name = stu_name;
        check_stulist.push_back(temp_check_stu);
    }

    return PASS; // ����ѧ����Ϣ��֤ͨ��
}

/***************************************************************************
  �������ƣ�print_hw_check_result
  ��    �ܣ���ӡ�����
  ���������
  �� �� ֵ��
  ˵    ����
 ***************************************************************************/
void hw_check::print_hw_check_result(int choice, const int file_status[], const int total_num[])
{
    // ���ڴ洢���״̬�ַ�������
    size_t maxlen = 0, filestatus_cnt = 0;
    // ����secondline����ʱ��״̬��
    int secondlinestatus_set[] = { PASS, NOT_SUBMIT, NOT_GB, NOT_WIN, LESS_THAN_2_LINE, SECOND_LINE_NOT_COMMIT, SECOND_LINE_ERROR, OTHER_ERROR , -1 };

    // ����action��ֵ������filestatus_cnt������Ҫ������ļ�״̬����
    if (this->action == "base")
        filestatus_cnt = 5;
    else if (this->action == "firstline")
        filestatus_cnt = 11;
    else if (this->action == "secondline")
        filestatus_cnt = 15;

    // �������״̬�ַ������ȣ��Ա�������
    for (size_t i = 0; i < filestatus_cnt; i++)
    {
        if (should_skip_status(i, secondlinestatus_set, this->action))
            continue;
        if ((choice == STUDENT_OF_ALL || choice == END_OF_NOT_ALL) && file_status[i] != 0)
            maxlen = max(FILESTATUS_STR[i].length(), maxlen);
        if (choice == END_OF_ALL && total_num[i] != 0)
            maxlen = max(FILESTATUS_STR[i].length(), maxlen);
    }

    // ���������ʽΪ�Ҷ��룬����������ַ�
    cout << setiosflags(ios::right);
    char setfill_char = '=';
    // ���ÿ�Ⱥ�����ַ�������choice��ֵ����
    int setw_word = 2, setw_seg = 12;
    if (choice == STUDENT_OF_ALL)
        setfill_char = '-';
    cout << setfill(setfill_char) << setw(setw_seg + maxlen) << setfill_char << endl;
    // ��ӡѧ����Ϣ����
    cout << STUDENT_INFORMATION[choice] << endl;
    cout << setfill(setfill_char) << setw(setw_seg + maxlen) << setfill_char << endl;
    // ��������ַ�ΪĬ�Ͽո�
    cout << setfill(' ');

    // ��������ӡÿ���ļ�״̬������
    for (size_t i = 0; i <= filestatus_cnt; i++)
    {
        if (should_skip_status(i, secondlinestatus_set, this->action))
            continue;
        // �����END_OF_ALL����total_num[i]��Ϊ0�����ӡ����
        if (choice == END_OF_ALL && total_num[i] != 0)
        {
            cout << setw(maxlen + setw_word) << FILESTATUS_STR[i] << " : ";
            cout << total_num[i] << endl;
        }
        // �����STUDENT_OF_ALL��END_OF_NOT_ALL����file_status[i]��Ϊ0�����ӡÿ��ѧ����״̬����
        if ((choice == STUDENT_OF_ALL || choice == END_OF_NOT_ALL) && file_status[i] != 0)
        {
            // ���action��"secondline"����Ҫ���⴦��OTHER_ERROR״̬
            if (this->action == "secondline")
            {
                if (i == OTHER_ERROR)
                    continue; // ��PASS�ϲ�������Ҫ������ӡ
                cout << setw(maxlen + setw_word) << FILESTATUS_STR[i] << " : ";
                int temp = file_status[OTHER_ERROR];
                if (temp < 0)
                    temp = 0;
                if (i == PASS) {
                    cout << file_status[i] + temp << endl;
                }
                else
                    cout << file_status[i] << endl;
            }
            else
            {
                cout << setw(maxlen + setw_word) << FILESTATUS_STR[i] << " : ";
                cout << file_status[i] << endl;
            }
        }
    }
    // ��ӡ�ײ��ָ��ߡ�
    cout << setfill(setfill_char) << setw(setw_seg + maxlen) << setfill_char << endl;
    // ���������ʽΪ����룬����������ַ�ΪĬ�Ͽո�
    cout << resetiosflags(ios::right) << setiosflags(ios::left);
    cout << setfill(' ');
}

/***************************************************************************
  �������ƣ�hw_check_all
  ��    �ܣ��ܼ�⺯��
  ���������
  �� �� ֵ��
  ˵    ����
 ***************************************************************************/
int hw_check::hw_check_all()
{
    // ���ڴ洢ѧ����������󳤶�
    int max_stu_length = 0;
    // ����ѧ���б�stulist������ÿ��ѧ����������󳤶�
    for (size_t i = 0; i < this->stulist.size(); i++)
    {
        int templen = this->stulist[i].name.length();
        max_stu_length = max(max_stu_length, templen);
    }

    // ���ڴ洢��ҵ�ļ�������󳤶�
    int max_hwfile_length = 0;
    // ����hwlist������ÿ���ļ�������󳤶�
    for (size_t i = 0; i < this->hwlist.size(); i++)
    {
        int templen = this->hwlist[i].filename.length();
        max_hwfile_length = max(max_hwfile_length, templen);
    }

    cout << setiosflags(ios::left);
    // ���ڴ洢�ָ��Ŀκ�
    vector<string> cnos;
    // ʹ��stringstream��getline�����ָ��Ŀκ��ַ���cno
    stringstream ss(cno);
    string temp_cno;
    while (getline(ss, temp_cno, ','))
    {
        // �Ƴ�ÿ���κ�ǰ��Ŀո�
        temp_cno.erase(remove(temp_cno.begin(), temp_cno.end(), ' '), temp_cno.end());
        cnos.push_back(temp_cno);
    }

    // �ж��Ƿ���Ҫ��������ļ���ѧ��
    bool file_is_all = this->file == "all" ? true : false;
    bool stu_is_all = this->stu == "all" ? true : false;
    // ����ѧ������
    int stunum_cnt = 0;
    // ��¼�ļ�״̬������
    int file_status[FILE_STATUS_NUM] = { 0 };
    // ��¼�ܵ��ļ�״̬����
    int total_num[FILE_STATUS_NUM] = { 0 };
    // �洢���л���ѧ������
    vector<vector<Student>> total_check_stulist;

    // ������Ǽ�������ļ��������ǰ�κš�ѧ��������Դ�ļ���
    if (!file_is_all)
        cout << "�κ� : " << cno << " ѧ������ : " << stulist.size() << " Դ�ļ��� : " << this->file << endl;

    // �������пκź�ѧ�������ÿ��ѧ������ҵ�ļ�
    for (const auto& current_cno : cnos) {
        for (const auto& student : this->stulist)
        {
            // �����ǰѧ���ĿκŲ�ƥ�䣬����
            if (student.cno != current_cno)
                continue;
            // ��ӡѧ����Ϣ��
            print_student_info(student, file_is_all, stu_is_all, stunum_cnt, max_stu_length, student.cno == "5000244001602");

            // ������ҵ�ļ��б����ÿ���ļ���״̬
            for (const auto& hwfile : this->hwlist)
            {
                // �����ļ�·��
                string filepath = src_rootdir + student.cno + "-" + student.no + "/" + (file_is_all ? hwfile.filename : this->file);
                if (file_is_all)
                    cout << "  " << setw(max_hwfile_length) << hwfile.filename << " : ";
                // ����ļ�״̬����¼
                FILE_SITUATIONS filestatus = check_and_record_file_status(filepath, file_is_all ? hwfile.filename : this->file, student, total_check_stulist);
                ++file_status[filestatus];
                // ������Ǽ�������ļ�������ѭ��
                if (!file_is_all) break;
            }

            // �����Ҫ��������ļ��������ܵ��ļ�״̬��������ӡ���
            if (file_is_all)
            {
                for (size_t i = 0; i < FILE_STATUS_NUM; i++)
                    total_num[i] += file_status[i];
                print_file_check_result(file_status[PASS], hwlist.size());
                print_hw_check_result(1, file_status, total_num);// ��ӡ��Ϣ1
                // ����file_status����
                memset(file_status, 0, sizeof(file_status));
                cout << endl;
            }
        }
    }
    cout << endl;

    // �����Ҫ��������ļ�������ܵļ����
    if (file_is_all)
    {
        cout << "�����" << stulist.size() << "��ѧ���ļ�飬�ļ�����:" << stulist.size() * hwlist.size() << "��ͨ������:" << total_num[PASS] << "������ͨ��" << total_num[PASS] << "��" << endl;
        print_hw_check_result(2, file_status, total_num); // ��ӡ��Ϣ2
    }
    else
    {
        // ������Ǽ�������ļ���ֻ����ļ������
        print_file_check_result(file_status[PASS], stulist.size());
        print_hw_check_result(0, file_status, total_num); // ��ӡ��Ϣ0
    }
    cout << endl;

    if (this->action == "secondline")
    {
        cross_check(total_check_stulist, stulist);
        cout << endl;
    }

    return 0;
}

/***************************************************************************
  �������ƣ�should_skip_status
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
 ***************************************************************************/
bool hw_check::should_skip_status(int i, const int secondlinestatus_set[], const std::string& action)
{
    // ��� action ���� "base" �� i == 2������
    if (action != "base" && i == 2)
        return true;

    // ��� action �� "secondline"����Ҫ����Ƿ��� secondlinestatus_set ��
    if (action == "secondline")
    {
        size_t j = 0;
        for (; secondlinestatus_set[j] != -1; j++)
        {
            if (i == secondlinestatus_set[j])
                return false; // �ҵ�ƥ�������ִ��
        }
        return true; // δ�ҵ�ƥ�������
    }

    // Ĭ�ϲ�����
    return false;
}

/***************************************************************************
  �������ƣ�print_student_info
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
 ***************************************************************************/
void hw_check::print_student_info(const Student& student, bool file_is_all, bool stu_is_all, int& stunum_cnt, int max_stu_length, bool is_special)
{
    if (file_is_all)
        cout << setw(3) << ++stunum_cnt << ": ѧ��-" << student.no << " ����-" << replaceDot(student.name) << " �κ�-" << student.cno << " �ļ�����-" << hwlist.size() << endl;
    else
    {
        if (stu_is_all)
            cout << setw(3) << ++stunum_cnt << ": " << student.no << "/" << setw(max_stu_length) << replaceDot(student.name) << " : ";
        else
            if (student.cno == "5000244001602")
                cout << setw(3) << ++stunum_cnt << ": " << student.no << "/" << setw(max_stu_length) << replaceDot(student.name) << "           : ";
            else
                cout << setw(3) << ++stunum_cnt << ": " << student.no << "/" << setw(max_stu_length) << replaceDot(student.name) << "   : ";
    }
}

/***************************************************************************
  �������ƣ�check_and_record_file_status
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
 ***************************************************************************/
FILE_SITUATIONS hw_check::check_and_record_file_status(const string& filepath, const string& filename, const Student& student, vector<vector<Student>>& total_check_stulist) 
{
    FILE_SITUATIONS filestatus = PASS; // Ĭ��״̬��ͨ��
    if (this->action == "base")
    {
        filestatus = get_base(filepath, filename);
        cout << FILESTATUS_STR[filestatus] << endl;
    }
    else if (this->action == "firstline")
    {
        filestatus = get_print_first(filepath, filename, student);
    }
    else if (this->action == "secondline")
    {
        vector<Student> check_stulist; // ���еĻ���ѧ������
        filestatus = get_print_second(filepath, check_stulist, student.no);
        if (filestatus == OTHER_ERROR)
            filestatus = PASS; // �����ж�
        total_check_stulist.push_back(check_stulist);
    }

    return filestatus;
}

/***************************************************************************
  �������ƣ�print_file_check_result
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
 ***************************************************************************/
void hw_check::print_file_check_result(int pass_count, int total_count) 
{
    string str = "�ļ�";
    if (total_count == stulist.size())
        str = "ѧ��";
    if (pass_count == total_count)
        cout << "ȫ��ͨ��" << pass_count << "/" << total_count << "��" << str << "������ͨ��" << pass_count << "��" << endl;
    else 
        cout << "���ͨ��" << pass_count << "/" << total_count << "��" << str << "������ͨ��" << pass_count << "��" << endl;
}
