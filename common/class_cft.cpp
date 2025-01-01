/* 2352018 ������ ���� */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <sstream>
/* ����Լ���Ҫ��ͷ�ļ���ע������ */
#include "../include/class_cft.h"
using namespace std;

/* ����һ��ʼʹ��get���ж�ȡ��ֻ���ڴ���homework.confʱ����ȡ��Ч���ݷǿ�,������,Ҳû�зָ��������������� */

/* ���������Զ��庯����ʵ�֣��Ѹ��������ݲ�ȫ�� */
char my_tolower(char ch) 
{
	if (ch >= 'A' && ch <= 'Z') 
		return ch + ('a' - 'A');
	return ch;
}

int my_strcasecmp(const char* s1, const char* s2) 
{
	while (*s1 && *s2) 
	{
		char c1 = my_tolower(static_cast<unsigned char>(*s1));
		char c2 = my_tolower(static_cast<unsigned char>(*s2));
		if (c1 != c2) 
			return c1 - c2;
		++s1;
		++s2;
	}
	return my_tolower(static_cast<unsigned char>(*s1)) -
		my_tolower(static_cast<unsigned char>(*s2));
}

int find_group(const vector<string>& source, const char* const name, const bool group_is_case_sensitive)
{
	if (name == nullptr)
		return -1;

	if (name == "")
		return 0;
	for (size_t i = 0; i < source.size() - 1; i++)
	{


		if (source[i].size() != strlen(name))
			continue;
		//if (i == source.size() - 1)
		//	break;
		if (!group_is_case_sensitive)
		{
			// �����ִ�Сд�ıȽ�
			bool match = true;
			for (size_t j = 0; j < source[i].size(); ++j)
			{
				if (j >= strlen(name) || my_tolower(source[i][j]) != my_tolower(name[j]))
				{
					match = false;
					break;
				}
			}
			if (match && strlen(name) == source[i].size())
			{
				//if (i == source.size() - 1)
				//	return static_cast<int>(i - 1);
				return static_cast<int>(i);
			}
		}
		else
		{
			// ���ִ�Сд�ıȽ�
			if (source[i] == name)
			{
				//if (i == source.size() - 1)
				//	return static_cast<int>(i - 1);
				return static_cast<int>(i);
			}
		}
	}


	return 0; // δ�ҵ�ƥ�����
}

int find_group(const vector<string>& source, const string& name, const bool group_is_case_sensitive)
{
	if (name == "")
		return 0;
	int group_index = -1;
	for (size_t i = 0; i < source.size() - 1; ++i)
	{
		if (i == source.size() - 1)
			break;
		if (source[i].size() != name.size())
			continue;
		if (!group_is_case_sensitive)
		{
			group_index = 1;
			for (size_t j = 0; j < source[i].size(); ++j)  // �����ִ�Сд����дʵ��
			{
				if (my_tolower(source[i][j]) != my_tolower(name[j]))
				{
					group_index = -1;
					break;
				}
			}
			if (group_index != -1)
			{
				group_index = (int)(i);
				break;
			}
		}
		else
		{
			if (source[i] == name) // ������ִ�Сд��ֱ��ʹ�� == ��������бȽ�
			{
				group_index = (int)(i); // �ҵ�ƥ�����¼����λ��
				break;
			}
		}
	}
	if (group_index == -1)
		return -1;
	else
		return group_index;
}

int find_item(const vector<item>& source, const char* const name, const bool item_is_case_sensitive)
{
	int item_index = -1;
	if (name == NULL)
		return -1;
	for (size_t i = 0; i < source.size(); ++i)
	{
		if (source[i].name.size() != strlen(name))
			continue;
		if (!item_is_case_sensitive)
		{
			item_index = 1;
			for (size_t j = 0; j < source[i].name.size(); ++j)  // �����ִ�Сд����дʵ��
			{
				if (my_tolower(source[i].name[j]) != my_tolower(name[j]))
				{
					item_index = -1;
					break;
				}
			}
			if (item_index != -1)
			{
				item_index = (int)(i);
				break;
			}
		}
		else
		{
			if (source[i].name == name) // ������ִ�Сд��ֱ��ʹ�� == ��������бȽ�
			{
				item_index = (int)(i); // �ҵ�ƥ�����¼����λ��
				break;
			}
		}
	}
	if (item_index == -1)
		return -1;
	else
		return item_index;
}

int find_item(const vector<item>& source, const string& name, const bool item_is_case_sensitive)
{
	int item_index = -1;
	for (size_t i = 0; i < source.size(); ++i)
	{
		if (source[i].name.size() != name.size())
			continue;
		if (!item_is_case_sensitive)
		{
			item_index = 1;
			for (size_t j = 0; j < source[i].name.size(); ++j)  // �����ִ�Сд����дʵ��
			{
				if (my_tolower(source[i].name[j]) != my_tolower(name[j]))
				{
					item_index = -1;
					break;
				}
			}
			if (item_index != -1)
			{
				item_index = (int)(i);
				break;
			}
		}
		else
		{
			if (source[i].name == name) // ������ִ�Сд��ֱ��ʹ�� == ��������бȽ�
			{
				item_index = (int)(i); // �ҵ�ƥ�����¼����λ��
				break;
			}
		}
	}
	if (item_index == -1)
		return -1;
	else
		return item_index;
}

int read_cfgfile(config_file_tools& cfg)
{
	if (!cfg.is_read_succeeded())
		return 0;

	cfg.in.clear();
	cfg.in.seekg(0, ios::beg);  // �ļ�ָ��������ͷ
	int beg_index = 0, end_index = 0;
	int line_num = 0, last_group_num = 0, new_group_num = 0;
	vector<char> line_content;
	char ch;
	string current_value;  // �洢���е�ֵ
	bool value_pending = false;  // ����Ƿ��ڵȴ�������Ϊֵ��һ����

	while (!cfg.in.eof())
	{
		// ��ȡһ�в�ȥ����β��ע�ͺͿհ�
		while ((ch = cfg.in.get()) != '\r' && ch != '\n' && (!cfg.in.eof()))
		{
			if (ch == ';' || ch == '#' || ch == '<') // ע�ʹ���
			{
				while ((ch = cfg.in.get()) != '\r' && ch != '\n' && (!cfg.in.eof()))
					;

				break;
			}
			if (ch == '/') {
				char next_ch = cfg.in.peek();  // �鿴��һ���ַ�
				if (next_ch == '/') {
					// ��˫б��ע�ͣ���������
					while ((ch = cfg.in.get()) != '\r' && ch != '\n' && (!cfg.in.eof()));
					if (ch == '\r') {
						ch = cfg.in.get();  // Windows���з�����
					}
					break;  // ������ǰ��ѭ��
				}
			}
			line_content.push_back(ch);
		}
		++line_num;



		// ȥ���ո�/tab
		if (!line_content.empty()) {
			while (!line_content.empty() && (line_content.front() == ' ' || line_content.front() == '\t'))
				line_content.erase(line_content.begin());
			while (!line_content.empty() && (line_content.back() == ' ' || line_content.back() == '\t'))
				line_content.pop_back();
		}

		// �����δ�����ֵ������Ƿ���Ҫ����ƴ����һ��
		if (value_pending && !line_content.empty()) {
			current_value += " " + string(line_content.begin(), line_content.end());
			line_content.clear();
			continue;
		}

		// ��������� [group]����������
		if (!line_content.empty() && line_content.front() == '[' && line_content.back() == ']')
		{
			beg_index = 1;
			end_index = (int)line_content.size() - 2;
			while (line_content[beg_index] == ' ' || line_content[beg_index] == '\t')
				++beg_index;
			while (line_content[end_index] == ' ' || line_content[end_index] == '\t')
				--end_index;

			string temp(line_content.data() + beg_index, end_index - beg_index + 1);
			temp.push_back(']');
			temp.insert(temp.begin(), '[');
			cfg.all_group.push_back(temp);  // ��������
		}
		else
		{
			// ���ݷָ�������������ֵ
			int equal_pos = -1;
			if (cfg.item_separate_character_type == BREAK_CTYPE::Equal) {
				// �����Equalģʽ������ '='
				for (size_t i = 0; i < line_content.size(); ++i)
				{
					if (line_content[i] == '=')
					{
						equal_pos = (int)i;
						break;
					}
				}
			}
			else {
				// �����Spaceģʽ�����ҵ�һ���ո��Tab
				for (size_t i = 0; i < line_content.size(); ++i)
				{
					if (line_content[i] == ' ' || line_content[i] == '\t')
					{
						equal_pos = (int)i;
						break;
					}
				}
			}
			item temp_item;
			if (equal_pos == -1) {
				// ����Ƿ�Ϊ�������� [group]��
				if (!line_content.empty() && line_content.front() == '[' && line_content.back() == ']') {
					string temp(line_content.data() + beg_index, end_index - beg_index + 1);
					temp.push_back(']');
					temp.insert(temp.begin(), '[');
					cfg.all_group.push_back(temp);  // ��������
				}


				continue;
			}

			// ��������
			beg_index = 0;
			end_index = equal_pos - 1;
			while (line_content[beg_index] == ' ' || line_content[beg_index] == '\t')
				++beg_index;
			while (line_content[end_index] == ' ' || line_content[end_index] == '\t')
				--end_index;

			//item temp_item;
			string item_name(line_content.begin() + beg_index, line_content.begin() + end_index + 1);
			if (item_name.find('[') != string::npos || item_name.find(']') != string::npos) {
				// ������ǰ�д���
				continue;
			}
			temp_item.name = item_name;

			// �������ֵ
			beg_index = equal_pos + 1;
			end_index = (int)line_content.size() - 1;
			if (beg_index > end_index)
				temp_item.value = "";  // �����ֵ
			else
			{
				while (line_content[beg_index] == ' ' || line_content[beg_index] == '\t')
					++beg_index;
				while (line_content[end_index] == ' ' || line_content[end_index] == '\t')
					--end_index;

				int length = end_index - beg_index + 1;
				string value(line_content.begin() + beg_index, line_content.begin() + end_index + 1);
				temp_item.value = value;
			}


			if (cfg.item_separate_character_type == BREAK_CTYPE::Equal)
				temp_item.expression = temp_item.name + " = " + temp_item.value;
			else
				temp_item.expression = temp_item.name + " " + temp_item.value;
			// ������
			if (cfg.all_group.empty())
				cfg.all_group.push_back("");  // ���⴦��û��������


			new_group_num = (int)cfg.all_group.size();
			while (last_group_num < new_group_num)
			{
				cfg.all_item.push_back(vector<item>());
				++last_group_num;
			}
			cfg.all_item[new_group_num - 1].push_back(temp_item);  // ��ӵ���ǰ��

		}

		// ��������Ϊ��һ����׼��
		line_content.clear();
		beg_index = end_index = 0;
	}
	return 1;
}


/***************************************************************************
  �������ƣ� 
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
config_file_tools::config_file_tools(const char* const _cfgname, const enum BREAK_CTYPE _ctype)
{
	this->cfgname = _cfgname;
	this->item_separate_character_type = _ctype;
	this->_is_open = false;  // Ĭ��ֵ
	ifstream fin(_cfgname);
	// ·���ָ���ת��
	for (size_t i = 0; i < this->cfgname.size(); ++i)
	{
		if (this->cfgname[i] == '\\')
			this->cfgname[i] = '/';  // �� '\\' �滻Ϊ '/'
	}
	string line;
	int line_cnt = 1;
	while (getline(fin, line))
	{
		line_cnt++;
		size_t line_len = line.length() + 2;
	}
	cfg_list.push_back(line);
	// �������ļ�
	this->in.open(this->cfgname, ios::in | ios::binary);
	this->all_group.clear();  // ���������
	this->all_item.clear();   // ���������

	// ��ȡ�����ļ�����
	if (!read_cfgfile(*this)) 
		this->_is_open = false;
	else 
		this->_is_open = true;
	fin.close();
}


/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
config_file_tools::config_file_tools(const string& _cfgname, const enum BREAK_CTYPE _ctype)
{
	this->cfgname = _cfgname;
	this->item_separate_character_type = _ctype;
	this->_is_open = false;  // Ĭ��ֵ
	ifstream fin(_cfgname);
	// ·���ָ���ת��
	for (size_t i = 0; i < this->cfgname.size(); ++i)
	{
		if (this->cfgname[i] == '\\')
			this->cfgname[i] = '/';  // �� '\\' �滻Ϊ '/'
	}
	string line;
	int line_cnt = 1;
	while (getline(fin, line))
	{
		line_cnt++;
		size_t line_len = line.length() + 2;
	}
	cfg_list.push_back(line);
	// �������ļ�
	this->in.open(this->cfgname, ios::in | ios::binary);
	this->all_group.clear();  // ���������
	this->all_item.clear();   // ���������

	// ��ȡ�����ļ�����
	if (!read_cfgfile(*this)) 
		this->_is_open = false;
	else 
		this->_is_open = true;
	fin.close();
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
config_file_tools::~config_file_tools()
{
	all_group.clear();
	all_item.clear();
	in.close();
}


/***************************************************************************
  �������ƣ�
  ��    �ܣ��ж϶������ļ��Ƿ�ɹ�
  ���������
  �� �� ֵ��true - �ɹ����Ѷ������е���/��
		   false - ʧ�ܣ��ļ�ĳ�г���/�ļ�ȫ����ע�����
  ˵    ����
***************************************************************************/
bool config_file_tools::is_read_succeeded() const
{
	if (!in.is_open())
		return false;
	else
		return true;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ����������ļ��е�������
  ���������vector <string>& ret : vector ��ÿ��Ϊһ������
  �� �� ֵ������������������������ļ���������Ϊ1������Ϊ"��
  ˵    ����
***************************************************************************/
int config_file_tools::get_all_group(vector <string>& ret)
{
	ret.clear();
	for (size_t i = 0; i < all_group.size(); i++)
		ret.push_back(all_group[i]);
	return static_cast<int>(ret.size());
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�����ָ�����������������ԭʼ����
  ���������const char* const group_name������
		   vector <string>& ret��vector ��ÿ��Ϊһ�����ԭʼ����
		   const bool is_case_sensitive = false : �����Ƿ��Сд���У�true-��Сд���� / Ĭ��false-��Сд������
  �� �� ֵ�����������0��ʾ��
  ˵    ����
***************************************************************************/
int config_file_tools::get_all_item(const char* const group_name, vector<string>& ret, const bool is_case_sensitive)
{
	ret.clear();  // ��շ��ص�����
	// �����������
	int group_index = find_group(all_group, group_name, is_case_sensitive);
	if (group_index == -1) 
	{
		if (all_group.empty())
		{
			all_group.push_back("");
			group_index = 0;
		}
		else 
			return 0;
	}

	
	// ����ҵ�ָ���飬���ظ����е�������

	for (size_t i = 0; i < all_item[group_index].size(); i++) 
		ret.push_back(all_item[group_index][i].expression);  // ����ı��ʽ���뷵���б�

	return (int)ret.size();  // �����ҵ�������
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�����/��ĿΪstring��ʽ������ͬ��
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int config_file_tools::get_all_item(const string& group_name, vector <string>& ret, const bool is_case_sensitive)
{
	ret.clear();
	int group_index = find_group(all_group, group_name, !is_case_sensitive);
	if (group_index == -1)
		return 0;
	else
		for (size_t i = 0; i < all_item[group_index].size(); i++)
			ret.push_back(all_item[group_index][i].expression);
	return (int)ret.size();
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�ȡĳ���ԭʼ���ݣ�=��������ַ���string��ʽ��
  ���������const char* const group_name
		   const char* const item_name
		   string &ret
		   const bool group_is_case_sensitive = false : �����Ƿ��Сд���У�true-��Сд���� / Ĭ��false-��Сд������
		   const bool item_is_case_sensitive = false  : �����Ƿ��Сд���У�true-��Сд���� / Ĭ��false-��Сд������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int config_file_tools::item_get_raw(const char* const group_name, const char* const item_name, string& ret, const bool group_is_case_sensitive, const bool item_is_case_sensitive)
{
	if (group_name == nullptr || item_name == nullptr)
		return 0;
	int group_index = find_group(all_group, group_name, group_is_case_sensitive);
	if (group_index == all_group.size())
		return 0;
	int item_index = find_item(all_item[group_index], item_name, item_is_case_sensitive);
	if (item_index == all_item[group_index].size())
		return 0;
	ret = all_item[group_index][item_index].value;
	return 1;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�����/��ĿΪstring��ʽ������ͬ��
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int config_file_tools::item_get_raw(const string& group_name, const string& item_name, string& ret, const bool group_is_case_sensitive, const bool item_is_case_sensitive)
{
	/* ��������ʵ�� */
	return this->item_get_raw(group_name.c_str(), item_name.c_str(), ret, group_is_case_sensitive, item_is_case_sensitive);
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�ȡĳ������ݣ���������Ϊchar��
  ���������const char* const group_name               ������
		   const char* const item_name                ������
		   const bool group_is_case_sensitive = false : �����Ƿ��Сд���У�true-��Сд���� / Ĭ��false-��Сд������
		   const bool item_is_case_sensitive = false  : �����Ƿ��Сд���У�true-��Сд���� / Ĭ��false-��Сд������
  �� �� ֵ��1 - �������������
		   0 - ���������������
  ˵    ����
***************************************************************************/
int config_file_tools::item_get_null(const char* const group_name, const char* const item_name, const bool group_is_case_sensitive, const bool item_is_case_sensitive)
{
	if (group_name == nullptr || item_name == nullptr)
		return 0;
	int group_index = find_group(all_group, group_name, group_is_case_sensitive);
	if (group_index == all_group.size())
		return 0;
	int item_index = find_item(all_item[group_index], item_name, item_is_case_sensitive);
	if (item_index == all_item[group_index].size())
		return 0;
	return 1;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�����/��ĿΪstring��ʽ������ͬ��
  ���������
  �� �� ֵ��
  ˵    ������Ϊ���ߺ���һ���ڳ����ʼ���׶α����ã������ڳ���ִ���б���Ƶ�ε��ã�
		   �������ֱ���׿ǣ�����΢Ӱ��Ч�ʣ�����Ӱ���������ܣ��Ը�Ƶ�ε��ã��˷������ʺϣ�
***************************************************************************/
int config_file_tools::item_get_null(const string& group_name, const string& item_name, const bool group_is_case_sensitive, const bool item_is_case_sensitive)
{
	/* ��������ʵ�� */
	return this->item_get_null(group_name.c_str(), item_name.c_str(), group_is_case_sensitive, item_is_case_sensitive);
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�ȡĳ������ݣ���������Ϊchar��
  ���������const char* const group_name               ������
		   const char* const item_name                ������
		   char& value                                ��������char��ֵ������1ʱ���ţ�����0�򲻿��ţ�
		   const char* const choice_set = nullptr     ���Ϸ���char�ļ��ϣ����磺"YyNn"��ʾ�Ϸ�����ΪY/N�Ҳ��ִ�Сд���ò�����Ĭ��ֵnullptr����ʾȫ���ַ���������飩
		   const char def_value = DEFAULT_CHAR_VALUE  ��������/�����Ƿ�������µ�Ĭ��ֵ���ò�����Ĭ��ֵDEFAULT_CHAR_VALUE�����������
															��ֵ��   DEFAULT_CHAR_VALUE ʱ������0��ֵ�����ţ�
															��ֵ���� DEFAULT_CHAR_VALUE ʱ����value=def_value������1
		   const bool group_is_case_sensitive = false : �����Ƿ��Сд���У�true-��Сд���� / Ĭ��false-��Сд������
		   const bool item_is_case_sensitive = false  : �����Ƿ��Сд���У�true-��Сд���� / Ĭ��false-��Сд������
  �� �� ֵ��1 - ȡ����ȷֵ
			   δȡ��ֵ/δȡ����ȷֵ��������ȱʡֵ��������Ϊȱʡֵ��
		   0 - δȡ����ֻ��Ϊδָ��Ĭ��ֵ������²Ż᷵��0��
  ˵    ����
***************************************************************************/
int config_file_tools::item_get_char(const char* const group_name, const char* const item_name, char& value,
	const char* const choice_set, const char def_value, const bool group_is_case_sensitive, const bool item_is_case_sensitive)
{
	value = def_value; // ��ʼ��ΪĬ��ֵ

	// ����������
	int group_index = -1;
	for (size_t i = 0; i < all_group.size(); ++i)
	{
		bool match = group_is_case_sensitive ? (all_group[i] == group_name) : (my_strcasecmp(all_group[i].c_str(), group_name) == 0);
		if (match) 
		{
			group_index = static_cast<int>(i);
			break;
		}
	}

	if (group_index == -1)  // δ�ҵ���
		return def_value == DEFAULT_CHAR_VALUE ? 0 : 1;

	// ����������
	int item_index = -1;
	for (size_t i = 0; i < all_item[group_index].size(); ++i) 
	{
		bool match = item_is_case_sensitive ? (all_item[group_index][i].name == item_name) : (my_strcasecmp(all_item[group_index][i].name.c_str(), item_name) == 0);
		if (match) 
		{
			item_index = static_cast<int>(i);
			break;
		}
	}

	if (item_index == -1)  // δ�ҵ���
		return def_value == DEFAULT_CHAR_VALUE ? 0 : 1;

	// ��ȡ��ֵ
	const string& item_value = all_item[group_index][item_index].value;
	if (item_value.empty() || item_value.size() != 1) // ֵΪ�ջ��ǵ��ַ�
		return def_value == DEFAULT_CHAR_VALUE ? 0 : 1;

	char parsed_value = item_value[0];

	// ����Ƿ��ںϷ�������
	if (choice_set != nullptr && strchr(choice_set, parsed_value) == nullptr) 
		return def_value == DEFAULT_CHAR_VALUE ? 0 : 1;

	// ��ֵ������
	value = parsed_value;
	return 1; // ����1��ʾ�ɹ���ȡ�Ϸ�ֵ
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�����/��ĿΪstring��ʽ������ͬ��
  ���������
  �� �� ֵ��
  ˵    ������Ϊ���ߺ���һ���ڳ����ʼ���׶α����ã������ڳ���ִ���б���Ƶ�ε��ã�
		   �������ֱ���׿ǣ�����΢Ӱ��Ч�ʣ�����Ӱ���������ܣ��Ը�Ƶ�ε��ã��˷������ʺϣ�
***************************************************************************/
int config_file_tools::item_get_char(const string& group_name, const string& item_name, char& value,
	const char* const choice_set, const char def_value, const bool group_is_case_sensitive, const bool item_is_case_sensitive)
{
	/* ��������ʵ�� */
	return this->item_get_char(group_name.c_str(), item_name.c_str(), value, choice_set, def_value, group_is_case_sensitive, item_is_case_sensitive);
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�ȡĳ������ݣ���������Ϊint��
  ���������const char* const group_name               ������
		   const char* const item_name                ������
		   int& value                                 ��������int��ֵ������1ʱ���ţ�����0�򲻿��ţ�
		   const int min_value = INT_MIN              : �������ݷ�Χ�����ޣ�Ĭ��ΪINT_MIN
		   const int max_value = INT_MAX              : �������ݷ�Χ�����ޣ�Ĭ��ΪINT_MAX
		   const int def_value = DEFAULT_INT_VALUE    ��������/�����Ƿ�������µ�Ĭ��ֵ���ò�����Ĭ��ֵ DEFAULT_INT_VALUE�����������
															��ֵ��   DEFAULT_INT_VALUE ʱ������0��ֵ�����ţ�
															��ֵ���� DEFAULT_INT_VALUE ʱ����value=def_value������1
		   const bool group_is_case_sensitive = false : �����Ƿ��Сд���У�true-��Сд���� / Ĭ��false-��Сд������
		   const bool item_is_case_sensitive = false  : �����Ƿ��Сд���У�true-��Сд���� / Ĭ��false-��Сд������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int config_file_tools::item_get_int(const char* const group_name, const char* const item_name, int& value,
	const int min_value, const int max_value, const int def_value, const bool group_is_case_sensitive, const bool item_is_case_sensitive)
{
	// ��� def_value ��Ĭ��ֵ�����ص�ֵ������
	if (def_value == DEFAULT_INT_VALUE) 
		value = def_value;

	// ����������
	int group_index = find_group(all_group, group_name, group_is_case_sensitive);
	if (group_index == -1)  // δ�ҵ���
		return def_value == DEFAULT_INT_VALUE ? 0 : 1;

	// ����������
	int item_index = find_item(all_item[group_index], item_name, item_is_case_sensitive);
	if (item_index == -1) 
		return 0;  // δ�ҵ������ 0 ��ʾֵ������

	// ��ȡ���ֵ�����Խ������Ϊ����
	const string& item_value = all_item[group_index][item_index].value;
	char* endptr;
	long parsed_value = strtol(item_value.c_str(), &endptr, 10);

	// �������Ƿ�ɹ�
	if (*endptr != '\0' || parsed_value < min_value || parsed_value > max_value) 
	{
		// ����ʧ�ܻ�ֵ������Χ
		if (def_value != DEFAULT_INT_VALUE) 
			value = def_value;  // ����ΪĬ��ֵ
		return 0;  // ���� 0 ��ʾֵ������
	}

	// �����ɹ����ڷ�Χ�ڣ���ֵ���� value
	value = static_cast<int>(parsed_value);
	return 1;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�����/��ĿΪstring��ʽ������ͬ��
  ���������
  �� �� ֵ��
  ˵    ������Ϊ���ߺ���һ���ڳ����ʼ���׶α����ã������ڳ���ִ���б���Ƶ�ε��ã�
		   �������ֱ���׿ǣ�����΢Ӱ��Ч�ʣ�����Ӱ���������ܣ��Ը�Ƶ�ε��ã��˷������ʺϣ�
***************************************************************************/
int config_file_tools::item_get_int(const string& group_name, const string& item_name, int& value,
	const int min_value, const int max_value, const int def_value, const bool group_is_case_sensitive, const bool item_is_case_sensitive)
{
	/* ��������ʵ�� */
	return this->item_get_int(group_name.c_str(), item_name.c_str(), value, min_value, max_value, def_value, group_is_case_sensitive, item_is_case_sensitive);
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�ȡĳ������ݣ���������Ϊdouble��
  ���������const char* const group_name                  ������
		   const char* const item_name                   ������
		   double& value                                 ��������int��ֵ������1ʱ���ţ�����0�򲻿��ţ�
		   const double min_value = __DBL_MIN__          : �������ݷ�Χ�����ޣ�Ĭ��ΪINT_MIN
		   const double max_value = __DBL_MAX__          : �������ݷ�Χ�����ޣ�Ĭ��ΪINT_MAX
		   const double def_value = DEFAULT_DOUBLE_VALUE ��������/�����Ƿ�������µ�Ĭ��ֵ���ò�����Ĭ��ֵDEFAULT_DOUBLE_VALUE�����������
																��ֵ��   DEFAULT_DOUBLE_VALUE ʱ������0��ֵ�����ţ�
																��ֵ���� DEFAULT_DOUBLE_VALUE ʱ����value=def_value������1
		   const bool group_is_case_sensitive = false     : �����Ƿ��Сд���У�true-��Сд���� / Ĭ��false-��Сд������
		   const bool item_is_case_sensitive = false      : �����Ƿ��Сд���У�true-��Сд���� / Ĭ��false-��Сд������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int config_file_tools::item_get_double(const char* const group_name, const char* const item_name, double& value,
	const double min_value, const double max_value, const double def_value, const bool group_is_case_sensitive, const bool item_is_case_sensitive)
{
	if (def_value == DEFAULT_DOUBLE_VALUE) 
		value = def_value;
	// ����������
	int group_index = find_group(all_group, group_name, group_is_case_sensitive);
	if (group_index == -1)  // δ�ҵ���
		return def_value == DEFAULT_DOUBLE_VALUE ? 0 : 1;

	// ����������
	int item_index = find_item(all_item[group_index], item_name, item_is_case_sensitive);
	if (item_index == -1)
		return -1;

	// ��ȡ���ֵ
	const string& item_value = all_item[group_index][item_index].value;
	if (item_value.empty())
		return 0;

	// ��֤�Ƿ�Ϊ��Ч������
	const char* str = item_value.c_str();
	char* endptr = nullptr;
	double temp_value = strtod(str, &endptr);

	// �������Ƿ�ɹ�
	if (*endptr != '\0' || str == endptr) // ����Ƿ�������ַ���ĩβ
		return 0;

	// ��鷶Χ�Ƿ�Ϸ�
	if (temp_value < min_value || temp_value > max_value)
		return 0;

	value = temp_value;
	return 1;

}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�����/��ĿΪstring��ʽ������ͬ��
  ���������
  �� �� ֵ��
  ˵    ������Ϊ���ߺ���һ���ڳ����ʼ���׶α����ã������ڳ���ִ���б���Ƶ�ε��ã�
		   �������ֱ���׿ǣ�����΢Ӱ��Ч�ʣ�����Ӱ���������ܣ��Ը�Ƶ�ε��ã��˷������ʺϣ�
***************************************************************************/
int config_file_tools::item_get_double(const string& group_name, const string& item_name, double& value,
	const double min_value, const double max_value, const double def_value, const bool group_is_case_sensitive, const bool item_is_case_sensitive)
{
	/* ��������ʵ�� */
	return this->item_get_double(group_name.c_str(), item_name.c_str(), value, min_value, max_value, def_value, group_is_case_sensitive, item_is_case_sensitive);
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�ȡĳ������ݣ���������Ϊchar * / char []��
  ���������const char* const group_name                  ������
		   const char* const item_name                   ������
		   char *const value                             ��������C��ʽ���ַ���������1ʱ���ţ�����0�򲻿��ţ�
		   const int str_maxlen                          ��ָ��Ҫ������󳤶ȣ���β�㣩
																���<1�򷵻ؿմ�(����DEFAULT_CSTRING_VALUE����Ȼ����������ͬ����Ҫ����defaultֵ���ܻ��)
																���>MAX_STRLEN ������ΪMAX_STRLEN
		   const char* const def_str                     ������������µ�Ĭ��ֵ���ò�����Ĭ��ֵDEFAULT_CSTRING_VALUE�����������
																��ֵ��   DEFAULT_CSTRING_VALUE ʱ������0��ֵ�����ţ�
																��ֵ���� DEFAULT_CSTRING_VALUE ʱ����value=def_value������1��ע�⣬����ֱ��=��
		   const bool group_is_case_sensitive = false : �����Ƿ��Сд���У�true-��Сд���� / Ĭ��false-��Сд������
		   const bool item_is_case_sensitive = false  : �����Ƿ��Сд���У�true-��Сд���� / Ĭ��false-��Сд������
  �� �� ֵ��
  ˵    ����1��Ϊ�򻯣�δ��\"����ת�崦��������ͨ�ַ�
		   2����β�����󳤶�Ϊstr_maxlen������ʱҪ��֤���㹻�ռ�
		   3����� str_maxlen ������ϵͳԤ������� MAX_STRLEN���� MAX_STRLEN ȡ
***************************************************************************/
int config_file_tools::item_get_cstring(const char* const group_name, const char* const item_name, char* const value,
	const int str_maxlen, const char* const def_value, const bool group_is_case_sensitive, const bool item_is_case_sensitive)
{
	string ret = "";
	int temp_max_len = str_maxlen;
	if (str_maxlen > MAX_STRLEN)
		temp_max_len = MAX_STRLEN;
	else if (str_maxlen < 1) 
	{
		value[0] = '\0';//���ؿմ�
		return 0;
	}
	int have_value = item_get_raw(group_name, item_name, ret, group_is_case_sensitive, item_is_case_sensitive);//��ȡԭʼֵ
	if (have_value) 
	{
		size_t ret_len = ret.length();
		char* p = new char[ret_len + 1];//����ռ�
		if (p == nullptr) 
		{
			cout << "�ڴ����ʧ��" << endl;
			return 0;
		}
		istringstream is(ret.c_str());
		is >> p;
		is.clear();
		if (is.fail()) 
		{
			delete[]p;//�ͷſռ�
			if (def_value != DEFAULT_CSTRING_VALUE) 
			{
				strcpy(value, def_value);
				return 1;
			}
			else
				return 0;
		}
		else {
			int len = strlen(p);
			if (len >= temp_max_len) 
				len = temp_max_len - 1; // ���Ƴ���
			strncpy(value, p, len);
			value[len] = '\0'; // ȷ�� value ���� '\0' ��β
			delete[]p;//�ͷſռ�
			return 1;
		}
	}
	else
	{
		if (def_value != DEFAULT_CSTRING_VALUE) 
		{
			strcpy(value, def_value);
			return 1;
		}
		else
			return 0;
	}
	return 0;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�����/��ĿΪstring��ʽ������ͬ��
  ���������
  �� �� ֵ��
  ˵    ������Ϊ���ߺ���һ���ڳ����ʼ���׶α����ã������ڳ���ִ���б���Ƶ�ε��ã�
		   �������ֱ���׿ǣ�����΢Ӱ��Ч�ʣ�����Ӱ���������ܣ��Ը�Ƶ�ε��ã��˷������ʺϣ�
***************************************************************************/
int config_file_tools::item_get_cstring(const string& group_name, const string& item_name, char* const value,
	const int str_maxlen, const char* const def_value, const bool group_is_case_sensitive, const bool item_is_case_sensitive)

{
	/* ��������ʵ�� */
	return item_get_cstring(group_name.c_str(), item_name.c_str(), value, str_maxlen, def_value, group_is_case_sensitive, item_is_case_sensitive);
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�ȡĳ������ݣ���������Ϊ string ��
  ���������const char* const group_name               ������
		   const char* const item_name                ������
		   string &value                              ��������string��ʽ���ַ���������1ʱ���ţ�����0�򲻿��ţ�
		   const string &def_value                    ������������µ�Ĭ��ֵ���ò�����Ĭ��ֵDEFAULT_STRING_VALUE�����������
															��ֵ��   DEFAULT_STRING_VALUE ʱ������0��ֵ�����ţ�
															��ֵ���� DEFAULT_STRING_VALUE ʱ����value=def_value������1
		   const bool group_is_case_sensitive = false : �����Ƿ��Сд���У�true-��Сд���� / Ĭ��false-��Сд������
		   const bool item_is_case_sensitive = false  : �����Ƿ��Сд���У�true-��Сд���� / Ĭ��false-��Сд������
  �� �� ֵ��
  ˵    ����Ϊ�򻯣�δ��\"����ת�崦��������ͨ�ַ�
***************************************************************************/
int config_file_tools::item_get_string(const char* const group_name, const char* const item_name, string& value,
	const string& def_value, const bool group_is_case_sensitive, const bool item_is_case_sensitive)
{
	value = def_value;

	int group_index = find_group(all_group, group_name, group_is_case_sensitive);
	if (group_index == -1)  // δ�ҵ���
		return def_value == DEFAULT_STRING_VALUE ? 0 : 1;

	int item_index = find_item(all_item[group_index], item_name, item_is_case_sensitive);
	if (item_index == -1) 
		return 0;

	if (!all_item[group_index][item_index].value.empty())
	{
		value = all_item[group_index][item_index].value;
		return 1;
	}

	return 0;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�����/��ĿΪstring��ʽ������ͬ��
  ���������
  �� �� ֵ��
  ˵    ������Ϊ���ߺ���һ���ڳ����ʼ���׶α����ã������ڳ���ִ���б���Ƶ�ε��ã�
		   �������ֱ���׿ǣ�����΢Ӱ��Ч�ʣ�����Ӱ���������ܣ��Ը�Ƶ�ε��ã��˷������ʺϣ�
***************************************************************************/
int config_file_tools::item_get_string(const string& group_name, const string& item_name, string& value,
	const string& def_value, const bool group_is_case_sensitive, const bool item_is_case_sensitive)
{
	/* ��������ʵ�� */
	return this->item_get_string(group_name.c_str(), item_name.c_str(), value, def_value, group_is_case_sensitive, item_is_case_sensitive);
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�ȡĳ������ݣ���������Ϊ IPv4 ��ַ��32bit���ͣ�������
  ���������const char* const group_name               ������
		   const char* const item_name                ������
		   unsigned int &value                        ��������IP��ַ��32λ���ͷ�ʽ������1ʱ���ţ�����0�򲻿��ţ�
		   const unsigned int &def_value              ������������µ�Ĭ��ֵ���ò�����Ĭ��ֵDEFAULT_IPADDR_VALUE�����������
															��ֵ��   DEFAULT_IPADDR_VALUE ʱ������0��ֵ�����ţ�
															��ֵ���� DEFAULT_IPADDR_VALUE ʱ����value=def_value������1
		   const bool group_is_case_sensitive = false : �����Ƿ��Сд���У�true-��Сд���� / Ĭ��false-��Сд������
		   const bool item_is_case_sensitive = false  : �����Ƿ��Сд���У�true-��Сд���� / Ĭ��false-��Сд������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int config_file_tools::item_get_ipaddr(const char* const group_name, const char* const item_name, unsigned int& value,
	const unsigned int& def_value, const bool group_is_case_sensitive, const bool item_is_case_sensitive)
{
	// ��ʼ������ֵΪĬ��ֵ
	value = def_value;

	// ����������
	int group_index = find_group(all_group, group_name, group_is_case_sensitive);
	if (group_index == -1) 
		// ���û���ҵ��飬����0����ʾʧ�ܣ���1����ʾʹ��Ĭ��ֵ�ɹ���
		return def_value == DEFAULT_IPADDR_VALUE ? 0 : 1;

	// ����������
	int item_index = find_item(all_item[group_index], item_name, item_is_case_sensitive);
	if (item_index == -1) 
		// ���û���ҵ������0����ʾʧ�ܣ���1����ʾʹ��Ĭ��ֵ�ɹ���
		return def_value == DEFAULT_IPADDR_VALUE ? 0 : 1;

	// ��ȡ���ֵ
	const string& item_value = all_item[group_index][item_index].value;
	if (item_value.empty()) 
		// ���ֵΪ�գ�����0��1��ʹ��Ĭ��ֵ��
		return def_value == DEFAULT_IPADDR_VALUE ? 0 : 1;

	// �������ʮ���Ƹ�ʽ�� IP ��ַ
	unsigned int ip_value = 0;
	vector<string> octets;
	stringstream ss(item_value);
	string octet;
	int part;

	while (getline(ss, octet, '.')) 
	{
		if (octet.empty()) 
			// ����Ƿ����룬���ж�������ĵ�
			return def_value == DEFAULT_IPADDR_VALUE ? 0 : 1;

		// ʹ�� istringstream ����ת��������Ƿ�ɹ�
		istringstream part_stream(octet);
		part_stream >> part;

		if (part_stream.fail() || part < 0 || part > 255) 
			// ת��ʧ�ܻ���ֵ������Χ
			return def_value == DEFAULT_IPADDR_VALUE ? 0 : 1;

		ip_value = (ip_value << 8) | part;
	}

	// ����Ƿ�������ĸ�����
	if (ss.fail() && !ss.eof()) 
		// ����ʧ�ܻ�û�е�������ĩβ
		return def_value == DEFAULT_IPADDR_VALUE ? 0 : 1;

	if (ss.eof() && ip_value < 0x100000000 && item_value.size() != 0) 
	{
		// �����������ĩβ���������ĸ�����
		value = ip_value;
		return 1;
	}

	return def_value == DEFAULT_IPADDR_VALUE ? 0 : 1;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�����/��ĿΪstring��ʽ������ͬ��
  ���������
  �� �� ֵ��
  ˵    ������Ϊ���ߺ���һ���ڳ����ʼ���׶α����ã������ڳ���ִ���б���Ƶ�ε��ã�
		   �������ֱ���׿ǣ�����΢Ӱ��Ч�ʣ�����Ӱ���������ܣ��Ը�Ƶ�ε��ã��˷������ʺϣ�
***************************************************************************/
int config_file_tools::item_get_ipaddr(const string& group_name, const string& item_name, unsigned int& value,
	const unsigned int& def_value, const bool group_is_case_sensitive, const bool item_is_case_sensitive)
{
	/* ��������ʵ�� */
	return this->item_get_ipaddr(group_name.c_str(), item_name.c_str(), value, def_value, group_is_case_sensitive, item_is_case_sensitive);
}
