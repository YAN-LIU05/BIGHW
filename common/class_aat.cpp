/* 2352018 ������ ���� */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include "../include/class_aat.h"
//���б�Ҫ�����Լ�������ͷ�ļ�
using namespace std;

#if !ENABLE_LIB_COMMON_TOOLS //��ʹ��lib����Ч

/* ---------------------------------------------------------------
	 �������������Ҫstatic�������ڲ������ã�
   ---------------------------------------------------------------- */
static int* alloc_and_copy_array(const int* source, int size)
{
	int* array = new(nothrow) int[size];
	if (!array)
	{
		cerr << "��̬���� extargs_int_set �ռ�ʧ��" << endl;
		exit(-1);
	}

	for (int i = 0; i < size; ++i)
		array[i] = source[i];

	return array;
}

static double* alloc_and_copy_array(const double* source, int size)
{
	double* array = new(nothrow) double[size];
	if (!array)
	{
		cerr << "��̬���� extargs_double_set �ռ�ʧ��" << endl;
		exit(-1);
	}

	for (int i = 0; i < size; ++i)
		array[i] = source[i];

	return array;
}

static string* alloc_and_copy_array(const string* source, int size)
{
	string* array = new(nothrow) string[size];
	if (!array)
	{
		cerr << "��̬���� extargs_string_set �ռ�ʧ��" << endl;
		exit(-1);
	}

	for (int i = 0; i < size; ++i)
		array[i] = source[i];

	return array;
}

static bool Is_int(const string str)
{
	int flag = 0;
	int len = str.length();
	if (len == 0)
		return false;
	if (str[0] == '+' || str[0] == '-')
	{
		if (len == 1)
			return false;
		flag = 1;
	}
	for (int i = flag; i < len; i++)
	{
		if (str[i] < '0' || str[i] > '9')
			return false;
	}
	return true;
}

static bool Is_double(const string str) 
{
	int len = str.length();
	if (len == 0) return false;

	int flag = 0;
	bool hasDot = false;
	bool hasE = false;

	// �������
	if (str[0] == '+' || str[0] == '-') 
	{
		flag = 1;
		if (len == 1) return false;  // ֻ�з���ʱ������false
	}

	// �����ַ��������ÿ���ַ�
	for (int i = flag; i < len; i++) 
	{
		if (str[i] >= '0' && str[i] <= '9') 
			// ��������֣���������
			continue;
		else if (str[i] == '.') 
		{
			// �����С���㣬����Ƿ��Ѿ����ֹ�С����
			if (hasDot || hasE) return false;
			hasDot = true;
		}
		else if (str[i] == 'e' || str[i] == 'E') 
		{
			// �����ָ�����֣�����Ƿ��Ѵ���ָ������
			if (hasE || i == flag || i == len - 1) return false;
			hasE = true;
		}
		else if (str[i] == '+' || str[i] == '-') 
		{
			// ����Ƿ��ţ�����Ƿ���ָ�����ֲ��ҷ��ź�������
			if (str[i - 1] != 'e' && str[i - 1] != 'E') return false;
		}
		else 
			return false; // �����ַ��Ƿ�
	}

	return true;
}


static bool Is_IP(const char* IP)
{
	int dots = 0;
	int num = 0;
	int segmentLength = 0;
	// ���� IP ��ַ��ÿ���ַ�
	for (int i = 0; IP[i] != '\0'; ++i) 
	{
		if (IP[i] == '.')
		{
			// ÿ���α���������һ������
			if (segmentLength == 0 || num > 255)
				return false;
			dots++;
			segmentLength = 0;  // ���öγ���
			num = 0;            // ���öε�ֵ
		}
		else if (IP[i] >= '0' && IP[i] <= '9')
		{
			// ������ֲ��ۻ�
			num = num * 10 + (IP[i] - '0');
			segmentLength++;
			// ������ִ���255��ֱ�ӷ���false
			if (num > 255)
				return false;
		}
		else
			// ������������ֺͷǵ���ַ�������false
			return false;
	}
	// ���һ����ҲӦ������Ч�����֣����Ե��β��
	if (segmentLength == 0 || num > 255) 
		return false;

	// �����������IP ��ַ������3����
	return dots == 3;
}


/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����null
 ***************************************************************************/
args_analyse_tools::args_analyse_tools()
{
	args_name.clear();
	extargs_type = ST_EXTARGS_TYPE::null;
	extargs_num = 0;
	args_existed = 0;

	extargs_bool_default = false;

	extargs_int_default = INVALID_INT_VALUE_OF_SET;
	extargs_int_min = DEFINE_INT_MIN;
	extargs_int_max = DEFINE_INT_MAX;
	extargs_int_set = NULL;

	extargs_double_default = INVALID_DOUBLE_VALUE_OF_SET;
	extargs_double_min = DEFINE_DOUBLE_MIN;
	extargs_double_max = DEFINE_DOUBLE_MAX;
	extargs_double_set = NULL;

	extargs_string_default = "";
	extargs_string_set = nullptr;

	extargs_ipaddr_default = (192 << 24) + (168 << 16) + (80 << 8) + 230;


	extargs_int_value = INVALID_INT_VALUE_OF_SET;
	extargs_double_value = INVALID_DOUBLE_VALUE_OF_SET;
	extargs_string_value.clear();
	extargs_ipaddr_value = 0;

	memset(pad, 0, sizeof(pad));

	is_bool = is_int = is_double = is_string = is_ip = false;
	have_intrange = have_doublerange = have_intset = have_doubleset = have_stringset = false;
	default_length = value_length = 2;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����boolean
 ***************************************************************************/
args_analyse_tools::args_analyse_tools(const char* name, const enum ST_EXTARGS_TYPE type, const int ext_num, const bool def)
{
	if (type != ST_EXTARGS_TYPE::boolean)
	{
		cout << "args_analyse_tools�๹�캯������,���Ĳ���type=" << int(type) << ",����boolean(1)" << endl;
		exit(-1);
	}
	args_name = name;
	extargs_type = type;
	extargs_num = ext_num;
	args_existed = 0;

	extargs_bool_default = def;

	extargs_int_default = INVALID_INT_VALUE_OF_SET;
	extargs_int_min = DEFINE_INT_MIN;
	extargs_int_max = DEFINE_INT_MAX;
	extargs_int_set = NULL;

	extargs_double_default = INVALID_DOUBLE_VALUE_OF_SET;
	extargs_double_min = DEFINE_DOUBLE_MIN;
	extargs_double_max = DEFINE_DOUBLE_MAX;
	extargs_double_set = NULL;

	extargs_string_default = "";
	extargs_string_set = nullptr;

	extargs_ipaddr_default = (192 << 24) + (168 << 16) + (80 << 8) + 230;

	extargs_int_value = INVALID_INT_VALUE_OF_SET;
	extargs_double_value = INVALID_DOUBLE_VALUE_OF_SET;
	extargs_string_value.clear();
	extargs_ipaddr_value = 0;

	memset(pad, 0, sizeof(pad));

	is_bool = true;
	is_int = is_double = is_string = is_ip = false;
	have_intrange = have_doublerange = have_intset = have_doubleset = have_stringset = false;
	default_length = (def) ? 5 : 6;
	value_length = 2;

}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����int_with_default��int_with_error
 ***************************************************************************/
args_analyse_tools::args_analyse_tools(const char* name, const enum ST_EXTARGS_TYPE type, const int ext_num, const int def, const int _min, const int _max)
{
	if (type != ST_EXTARGS_TYPE::int_with_default && type != ST_EXTARGS_TYPE::int_with_error)
	{
		cout << "args_analyse_tools�๹�캯������,���Ĳ���type=" << int(type) << ",����int_with_default(2)��int_with_error(3)" << endl;
		exit(-1);
	}
	args_name = name;
	extargs_type = type;
	extargs_num = ext_num;
	args_existed = 0;

	extargs_bool_default = false;

	extargs_int_default = def;
	extargs_int_min = _min;
	extargs_int_max = _max;
	extargs_int_set = NULL;

	extargs_double_default = INVALID_DOUBLE_VALUE_OF_SET;
	extargs_double_min = DEFINE_DOUBLE_MIN;
	extargs_double_max = DEFINE_DOUBLE_MAX;
	extargs_double_set = NULL;

	extargs_string_default = "";
	extargs_string_set = nullptr;

	extargs_ipaddr_default = (192 << 24) + (168 << 16) + (80 << 8) + 230;

	if (type == ST_EXTARGS_TYPE::int_with_set_error)
	{
		extargs_int_default = INVALID_INT_VALUE_OF_SET; // ����intȱʡֵ
		default_length = 2;
	}
	else
	{
		int count = 1;
		int temp = extargs_int_default;
		while (temp / 10)
		{
			count++;
			temp = temp / 10;
		}
		default_length = count + 1;
	}
	extargs_int_value = extargs_int_default;
	extargs_double_value = INVALID_DOUBLE_VALUE_OF_SET;
	extargs_string_value.clear();
	extargs_ipaddr_value = 0;


	memset(pad, 0, sizeof(pad));

	have_intrange = true;
	is_bool = is_int = is_double = is_string = is_ip = false;
	have_doublerange = have_intset = have_doubleset = have_stringset = false;
	value_length = 2;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����int_with_set_default��int_with_set_error
 ***************************************************************************/
args_analyse_tools::args_analyse_tools(const char* name, const enum ST_EXTARGS_TYPE type, const int ext_num, const int def_of_set_pos, const int* const set)
{
	if (type != ST_EXTARGS_TYPE::int_with_set_default && type != ST_EXTARGS_TYPE::int_with_set_error)
	{
		cout << "args_analyse_tools�๹�캯������,���Ĳ���type=" << int(type) << ",����int_with_set_default(4)��int_with_set_error(5)" << endl;
		exit(-1);
	}

	int size = 0;
	for (; set[size] != INVALID_INT_VALUE_OF_SET; ++size)
		;
	++size; // ������־�Ķ���ռ�

	args_name = name;
	extargs_type = type;
	extargs_num = ext_num;
	args_existed = 0;

	extargs_bool_default = false;

	extargs_int_default = set[def_of_set_pos];
	extargs_int_min = DEFINE_INT_MIN;
	extargs_int_max = DEFINE_INT_MAX;
	extargs_int_set = alloc_and_copy_array(set, size);


	extargs_double_default = INVALID_DOUBLE_VALUE_OF_SET;
	extargs_double_min = DEFINE_DOUBLE_MIN;
	extargs_double_max = DEFINE_DOUBLE_MAX;
	extargs_double_set = NULL;

	extargs_string_default = "";
	extargs_string_set = nullptr;

	extargs_ipaddr_default = (192 << 24) + (168 << 16) + (80 << 8) + 230;

	if (type == ST_EXTARGS_TYPE::int_with_set_error)
	{
		//extargs_int_default = INVALID_INT_VALUE_OF_SET; 
		default_length = 2;
	}
	else
	{
		int count = 1;
		int temp = extargs_int_default;
		while (temp / 10)
		{
			count++;
			temp = temp / 10;
		}
		default_length = count + 1;
	}
	extargs_int_value = extargs_int_default;
	extargs_double_value = INVALID_DOUBLE_VALUE_OF_SET;
	extargs_string_value.clear();
	extargs_ipaddr_value = 0;


	memset(pad, 0, sizeof(pad));

	have_intset = true;
	is_bool = is_int = is_double = is_string = is_ip = false;
	have_intrange = have_doublerange = have_doubleset = have_stringset = false;
	value_length = 2;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����str��ipaddr_with_default��ipaddr_with_error
 ***************************************************************************/
args_analyse_tools::args_analyse_tools(const char* name, const enum ST_EXTARGS_TYPE type, const int ext_num, const string def)
{
	if (type != ST_EXTARGS_TYPE::ipaddr_with_default && type != ST_EXTARGS_TYPE::ipaddr_with_error && type != ST_EXTARGS_TYPE::str)
	{
		cout << "args_analyse_tools�๹�캯������,���Ĳ���type=" << int(type) << ",����str(10)��ipaddr_with_default(13)��ipaddr_with_error(14)" << endl;
		exit(-1);
	}
	args_name = name;
	extargs_type = type;
	extargs_num = ext_num;
	args_existed = 0;

	extargs_bool_default = false;

	extargs_int_default = INVALID_INT_VALUE_OF_SET;
	extargs_int_min = DEFINE_INT_MIN;
	extargs_int_max = DEFINE_INT_MAX;
	extargs_int_set = NULL;

	extargs_double_default = INVALID_DOUBLE_VALUE_OF_SET;
	extargs_double_min = DEFINE_DOUBLE_MIN;
	extargs_double_max = DEFINE_DOUBLE_MAX;
	extargs_double_set = NULL;

	extargs_string_default = (type == ST_EXTARGS_TYPE::str) ? def : "";
	extargs_string_set = nullptr;

	extargs_ipaddr_default = (192 << 24) + (168 << 16) + (80 << 8) + 230;
	if (type == ST_EXTARGS_TYPE::ipaddr_with_default)
	{
		int parts[4] = { 0 };  // �洢�ĸ�IP����
		stringstream ss(def);  // �� IP �ַ�������
		string part;
		int i = 0;

		// ���� '.' �ָ�IP��ַ��ÿһ���ֲ�ת��������
		while (getline(ss, part, '.'))
			parts[i++] = stoi(part);  // ���ַ���ת��Ϊ��������������
		unsigned int ipAddress = 0;
		for (i = 0; i < 4; ++i)
			ipAddress |= (parts[i] << (24 - (i * 8)));  // ͨ��λ���������޷�������
		extargs_ipaddr_default = ipAddress;
	}
	else if (type == ST_EXTARGS_TYPE::ipaddr_with_error)
		extargs_ipaddr_default = 0;

	extargs_int_value = INVALID_INT_VALUE_OF_SET;
	extargs_double_value = INVALID_DOUBLE_VALUE_OF_SET;
	extargs_string_value = extargs_string_default;
	extargs_ipaddr_value = extargs_ipaddr_default;

	memset(pad, 0, sizeof(pad));

	if (type == ST_EXTARGS_TYPE::str)
	{
		is_string = true;
		is_ip = false;
	}
	else
	{
		is_string = false;
		is_ip = true;
	}
	is_bool = is_int = is_double = false;
	have_intrange = have_doublerange = have_intset = have_doubleset = have_stringset = false;
	default_length = (int)def.size() + 1;
	value_length = 2;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����str_with_set_default��str_with_set_error
 ***************************************************************************/
args_analyse_tools::args_analyse_tools(const char* name, const enum ST_EXTARGS_TYPE type, const int ext_num, const int def_of_set_pos, const string* const set)
{
	if (type != ST_EXTARGS_TYPE::str_with_set_default && type != ST_EXTARGS_TYPE::str_with_set_error)
	{
		cout << "args_analyse_tools�๹�캯������,���Ĳ���type=" << int(type) << ",����str_with_set_default(11)��str_with_set_error(12)" << endl;
		exit(-1);
	}

	int size = 0;
	for (; set[size] != ""; ++size)
		;
	++size; // ������־�Ķ���ռ�

	args_name = name;
	extargs_type = type;
	extargs_num = ext_num;
	args_existed = 0;

	extargs_bool_default = false;

	extargs_int_default = INVALID_INT_VALUE_OF_SET;
	extargs_int_min = DEFINE_INT_MIN;
	extargs_int_max = DEFINE_INT_MAX;
	extargs_int_set = NULL;

	extargs_double_default = INVALID_DOUBLE_VALUE_OF_SET;
	extargs_double_min = DEFINE_DOUBLE_MIN;
	extargs_double_max = DEFINE_DOUBLE_MAX;
	extargs_double_set = NULL;

	extargs_string_default = "";
	extargs_string_default = set[def_of_set_pos];
	extargs_string_set = alloc_and_copy_array(set, size);

	extargs_ipaddr_default = (192 << 24) + (168 << 16) + (80 << 8) + 230;

	extargs_int_value = INVALID_INT_VALUE_OF_SET;
	extargs_double_value = INVALID_DOUBLE_VALUE_OF_SET;
	extargs_string_value = extargs_string_default;
	extargs_ipaddr_value = 0;

	memset(pad, 0, sizeof(pad));

	default_length = int(extargs_string_default.size()) + 1;
	have_stringset = true;
	is_bool = is_int = is_double = is_string = is_ip = false;
	have_intrange = have_doublerange = have_intset = have_doubleset = false;
	value_length = 2;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������f
  �� �� ֵ��
  ˵    ����double_with_default��double_with_error
 ***************************************************************************/
args_analyse_tools::args_analyse_tools(const char* name, const enum ST_EXTARGS_TYPE type, const int ext_num, const double	def, const double _min, const double _max)
{
	if (type != ST_EXTARGS_TYPE::double_with_default && type != ST_EXTARGS_TYPE::double_with_error)
	{
		cout << "args_analyse_tools�๹�캯������,���Ĳ���type=" << int(type) << ",����double_with_default(6)��double_with_error(7)" << endl;
		exit(-1);
	}
	args_name = name;
	extargs_type = type;
	extargs_num = ext_num;
	args_existed = 0;

	extargs_bool_default = false;

	extargs_int_default = INVALID_INT_VALUE_OF_SET;
	extargs_int_min = DEFINE_INT_MIN;
	extargs_int_max = DEFINE_INT_MAX;
	extargs_int_set = NULL;

	extargs_double_default = def;
	extargs_double_min = _min;
	extargs_double_max = _max;
	extargs_double_set = NULL;

	extargs_string_default = "";
	extargs_string_set = nullptr;

	extargs_ipaddr_default = (192 << 24) + (168 << 16) + (80 << 8) + 230;

	if (type == ST_EXTARGS_TYPE::double_with_set_error)
	{
		extargs_double_default = INVALID_INT_VALUE_OF_SET; // ����intȱʡֵ
		default_length = 2;
	}
	else
	{
		int count = 1;
		double temp = extargs_double_default;
		while (temp / 10)
		{
			count++;
			temp = temp / 10;
		}
		default_length = count + 1;
	}
	extargs_int_value = INVALID_INT_VALUE_OF_SET;
	extargs_double_value = extargs_double_default;
	extargs_string_value.clear();
	extargs_ipaddr_value = 0;

	memset(pad, 0, sizeof(pad));

	have_doublerange = true;
	is_bool = is_int = is_double = is_string = is_ip = false;
	have_intrange = have_intset = have_doubleset = have_stringset = false;
	value_length = 2;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����double_with_set_default��double_with_set_error
 ***************************************************************************/
args_analyse_tools::args_analyse_tools(const char* name, const enum ST_EXTARGS_TYPE type, const int ext_num, const int def_of_set_pos, const double* const set)
{
	if (type != ST_EXTARGS_TYPE::double_with_set_default && type != ST_EXTARGS_TYPE::double_with_set_error)
	{
		cout << "args_analyse_tools�๹�캯������,���Ĳ���type=" << int(type) << ",����double_with_set_default(8)��double_with_set_error(9)" << endl;
		exit(-1);
	}

	int size = 0;
	for (; set[size] != INVALID_DOUBLE_VALUE_OF_SET; ++size)
		;
	++size; // ������־�Ķ���ռ�

	args_name = name;
	extargs_type = type;
	extargs_num = ext_num;
	args_existed = 0;

	extargs_bool_default = false;

	extargs_int_default = INVALID_INT_VALUE_OF_SET;
	extargs_int_min = DEFINE_INT_MIN;
	extargs_int_max = DEFINE_INT_MAX;
	extargs_int_set = NULL;

	extargs_double_default = set[def_of_set_pos];
	extargs_double_min = DEFINE_DOUBLE_MIN;
	extargs_double_max = DEFINE_DOUBLE_MAX;
	extargs_double_set = alloc_and_copy_array(set, size);

	extargs_string_default = "";
	extargs_string_set = nullptr;

	extargs_ipaddr_default = (192 << 24) + (168 << 16) + (80 << 8) + 230;

	if (type == ST_EXTARGS_TYPE::double_with_set_error)
	{
		//extargs_double_default = INVALID_DOUBLE_VALUE_OF_SET;
		default_length = 2;
	}
	else
	{
		int count = 1;
		double temp = extargs_double_default;
		while (temp / 10)
		{
			count++;
			temp = temp / 10;
		}
		default_length = count + 1;
	}
	extargs_int_value = INVALID_INT_VALUE_OF_SET;
	extargs_double_value = extargs_double_default;
	extargs_string_value.clear();
	extargs_ipaddr_value = 0;


	memset(pad, 0, sizeof(pad));

	have_doubleset = true;
	is_bool = is_int = is_double = is_string = is_ip = false;
	have_intrange = have_doublerange = have_intset = have_stringset = false;
	value_length = 2;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
 ***************************************************************************/
args_analyse_tools::~args_analyse_tools()
{
	if (extargs_int_set != NULL)
		delete[] extargs_int_set;
	if (extargs_double_set != NULL)
		delete[] extargs_double_set;
	if (extargs_string_set != NULL)
		delete[] extargs_string_set;
}

/* ---------------------------------------------------------------
	 ����AAT���Զ����Ա������ʵ�֣�private��
   ---------------------------------------------------------------- */

   /***************************************************************************
	 �������ƣ�
	 ��    �ܣ�
	 ���������
	 �� �� ֵ��
	 ˵    ������ʵ�֣���Ҫ��
	***************************************************************************/
const string args_analyse_tools::get_name() const
{
	return this->args_name;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ������!!��ֻ����0/1
			��ʵ�֣���Ҫ��
 ***************************************************************************/
const int args_analyse_tools::existed() const
{
	return !!this->args_existed;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ������ʵ�֣���Ҫ��
 ***************************************************************************/
const int args_analyse_tools::get_int() const
{
	return this->extargs_int_value;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ������ʵ�֣���Ҫ��
 ***************************************************************************/
const double args_analyse_tools::get_double() const
{
	return this->extargs_double_value;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ������ʵ�֣���Ҫ��
 ***************************************************************************/
const string args_analyse_tools::get_string() const
{
	return this->extargs_string_value;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ������ʵ�֣���Ҫ��
 ***************************************************************************/
const unsigned int args_analyse_tools::get_ipaddr() const
{
	return this->extargs_ipaddr_value;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ������ extargs_ipaddr_value ��ֵ�� 0x7f000001 תΪ "127.0.0.1"
 ***************************************************************************/
const string args_analyse_tools::get_str_ipaddr() const
{
	stringstream ss;
	ss << ((extargs_ipaddr_value >> 24) & 0xFF) << '.' // ��ȡ��һ�� IP ��ַ
		<< ((extargs_ipaddr_value >> 16) & 0xFF) << '.' // ��ȡ�ڶ��� IP ��ַ
		<< ((extargs_ipaddr_value >> 8) & 0xFF) << '.'  // ��ȡ������ IP ��ַ
		<< (extargs_ipaddr_value & 0xFF);               // ��ȡ���Ķ� IP ��ַ
	return ss.str();
}


/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������follow_up_args���Ƿ��к�������
			0  ���޺�������
			1  ���к�������
  �� �� ֵ��
  ˵    ������Ԫ����
***************************************************************************/
int args_analyse_process(const int argc, const char* const* const argv, args_analyse_tools* const args, const int follow_up_args)
{
	int cnt = 1;
	for (int i = 1; i < argc; i++, cnt++) 
	{
		string str = argv[i];
		if (str.length() >= 2 && str.substr(0, 2) == "--") 
		{
			int index = -1;
			for (int j = 0; !args[j].get_name().empty(); j++) {
				if (argv[i] == args[j].get_name()) {
					index = j;
					break;
				}
			}

			if (index == -1) {
				if (follow_up_args)
					return cnt;
				else if (string(argv[i]) == "--") {
					cout << "����[--]��ʽ�Ƿ�(����--��ͷ����Ч����)." << endl;
					return -1;
				}
				else {
					cout << "����[" << argv[i] << "]�Ƿ�." << endl;
					return -1;
				}
			}//��ʽ��ȷ��ƥ�䲻��
			if (args[index].args_existed) {
				cout << "����[" << argv[i] << "]�ظ�." << endl;
				return -1;
			}//�ظ�����
			args[index].args_existed = 1;
			if (args[index].extargs_num == 0)
				continue;
			else if (i == argc - 1 || (i < argc - 1 && str.length() >= 2 && argv[i + 1][0] == '-' && argv[i + 1][1] == '-')) {
				cout << "����[" << argv[i] << "]" << (i == argc - 1 ? "�ĸ��Ӳ�������" : "ȱ�ٸ��Ӳ���") << ". (����:";
				switch (args[index].extargs_type)
				{
					case ST_EXTARGS_TYPE::int_with_default:
					case ST_EXTARGS_TYPE::int_with_error:
						cout << item_name[int(ST_EXTARGS_TYPE::int_with_default)];
						cout << ", ��Χ[" << args[index].extargs_int_min << ".." << args[index].extargs_int_max << "]";
						if (args[index].extargs_type == ST_EXTARGS_TYPE::int_with_set_error)
							;
						else
							cout << " ȱʡ:" << args[index].extargs_int_default;
						break;
					case ST_EXTARGS_TYPE::int_with_set_default:
					case ST_EXTARGS_TYPE::int_with_set_error:
						cout << item_name[int(ST_EXTARGS_TYPE::int_with_set_default)];
						cout << ", ��Χ[";
						for (const int* p = args[index].extargs_int_set; *p != INVALID_INT_VALUE_OF_SET;) {
							cout << *p++;
							cout << (*p == INVALID_INT_VALUE_OF_SET ? "]" : "/");
						}
						if (args[index].extargs_type == ST_EXTARGS_TYPE::int_with_set_error)
							;
						else
							cout << " ȱʡ:" << args[index].extargs_int_default;
						break;
					case ST_EXTARGS_TYPE::double_with_default:
					case ST_EXTARGS_TYPE::double_with_error:
						cout << item_name[int(ST_EXTARGS_TYPE::double_with_default)];
						cout << ", ��Χ[" << args[index].extargs_double_min << ".." << args[index].extargs_double_max << "]";
						if (args[index].extargs_type == ST_EXTARGS_TYPE::double_with_set_error)
							;
						else
							cout << " ȱʡ:" << args[index].extargs_double_default;
						break;
					case ST_EXTARGS_TYPE::double_with_set_default:
					case ST_EXTARGS_TYPE::double_with_set_error:
						cout << item_name[int(ST_EXTARGS_TYPE::double_with_set_default)];
						cout << ", ��Χ[";
						for (const double* p = args[index].extargs_double_set; *p != INVALID_DOUBLE_VALUE_OF_SET;) {
							cout << *p++;
							cout << (*p == INVALID_DOUBLE_VALUE_OF_SET ? "]" : "/");
						}
						if (args[index].extargs_type == ST_EXTARGS_TYPE::double_with_set_error)
							;
						else
							cout << " ȱʡ:" << args[index].extargs_double_default;
						break;
					case ST_EXTARGS_TYPE::str:
						cout << item_name[int(ST_EXTARGS_TYPE::str)];
						if (!args[index].extargs_string_default.empty())
							cout << " ȱʡ:" << args[index].extargs_string_default;
						break;
					case ST_EXTARGS_TYPE::ipaddr_with_default:
					case ST_EXTARGS_TYPE::ipaddr_with_error:
						cout << item_name[int(ST_EXTARGS_TYPE::ipaddr_with_default)];
						if (args[index].extargs_type == ST_EXTARGS_TYPE::ipaddr_with_error)
							;
						else
							cout << " ȱʡ:" << args[index].get_str_ipaddr();
						break;
					case ST_EXTARGS_TYPE::str_with_set_default:
					case ST_EXTARGS_TYPE::str_with_set_error:
						cout << item_name[int(ST_EXTARGS_TYPE::str_with_set_default)];
						cout << ", ��ȡֵ[";
						for (const string* p = args[index].extargs_string_set; !p->empty();) {
							cout << *p++;
							cout << (p->empty() ? "]" : "/");
						}
						if (args[index].extargs_type == ST_EXTARGS_TYPE::str_with_set_error)
							;
						else
							cout << " ȱʡ:" << args[index].extargs_string_default;
				}
				cout << ")" << endl;
				return -1;
			}//ȱ�ٸ��Ӳ���
			else {
				switch (args[index].extargs_type)
				{
					case ST_EXTARGS_TYPE::int_with_default:
					case ST_EXTARGS_TYPE::int_with_error:
					{
						if (!Is_int(argv[i + 1])) {
							cout << "����[" << argv[i] << "]�ĸ��Ӳ�����������. (����:";
							cout << item_name[int(ST_EXTARGS_TYPE::int_with_default)];
							cout << ", ��Χ[" << args[index].extargs_int_min << ".." << args[index].extargs_int_max << "]";
							if (args[index].extargs_type == ST_EXTARGS_TYPE::int_with_set_error)
								cout << ")" << endl;
							else
								cout << " ȱʡ:" << args[index].extargs_int_default << ")" << endl;
							return -1;
						}
						int value1 = atoi(argv[i + 1]);
						if (value1 < args[index].extargs_int_min || value1 > args[index].extargs_int_max) {
							if (args[index].extargs_type == ST_EXTARGS_TYPE::int_with_error) {
								cout << "����[" << argv[i] << "]�ĸ��Ӳ���ֵ(" << value1 << ")�Ƿ�. (����:";
								cout << item_name[int(ST_EXTARGS_TYPE::int_with_error)];
								cout << ", ��Χ[" << args[index].extargs_int_min << ".." << args[index].extargs_int_max << "])" << endl;
								return -1;
							}
							else
								value1 = args[index].extargs_int_default;
						}
						args[index].extargs_int_value = value1;
						break;
					}
					case ST_EXTARGS_TYPE::double_with_default:
					case ST_EXTARGS_TYPE::double_with_error:
					{
						if (!Is_double(argv[i + 1])) {
							cout << "����[" << argv[i] << "]�ĸ��Ӳ������Ǹ�����. (����:";
							cout << item_name[int(ST_EXTARGS_TYPE::double_with_default)];
							cout << ", ��Χ[" << args[index].extargs_double_min << ".." << args[index].extargs_double_max << "]";
							if (args[index].extargs_type == ST_EXTARGS_TYPE::double_with_set_error)
								cout << ")" << endl;
							else
								cout << " ȱʡ:" << args[index].extargs_double_default << ")" << endl;
							return -1;
						}
						double value01 = atof(argv[i + 1]);
						if (value01 < args[index].extargs_double_min || value01 > args[index].extargs_double_max) {
							if (args[index].extargs_type == ST_EXTARGS_TYPE::double_with_error) {
								cout << "����[" << argv[i] << "]�ĸ��Ӳ���ֵ(" << value01 << ")�Ƿ�. (����:";
								cout << item_name[int(ST_EXTARGS_TYPE::double_with_error)];
								cout << ", ��Χ[" << args[index].extargs_double_min << ".." << args[index].extargs_double_max << "])" << endl;
								return -1;
							}
							else
								value01 = args[index].extargs_double_default;
						}
						args[index].extargs_double_value = value01;
						break;
					}
					case ST_EXTARGS_TYPE::int_with_set_default:
					case ST_EXTARGS_TYPE::int_with_set_error:
					{
						if (!Is_int(argv[i + 1])) {
							cout << "����[" << argv[i] << "]�ĸ��Ӳ�����������. (����:";
							cout << item_name[int(ST_EXTARGS_TYPE::int_with_set_default)];
							cout << ", ��Χ[";
							for (const int* p = args[index].extargs_int_set; *p != INVALID_INT_VALUE_OF_SET;) {
								cout << *p++;
								cout << (*p == INVALID_INT_VALUE_OF_SET ? "]" : "/");
							}
							if (args[index].extargs_type == ST_EXTARGS_TYPE::int_with_set_error)
								cout << ")" << endl;
							else
								cout << " ȱʡ:" << args[index].extargs_int_default << ")" << endl;
							return -1;
						}
						int value2 = atoi(argv[i + 1]);
						bool flag = false;
						for (const int* p = args[index].extargs_int_set; *p != INVALID_INT_VALUE_OF_SET; p++) {
							if (*p == value2) {
								flag = true;
								break;
							}
						}
						if (!flag) {
							if (args[index].extargs_type == ST_EXTARGS_TYPE::int_with_set_error) {
								cout << "����[" << argv[i] << "]�ĸ��Ӳ���ֵ(" << value2 << ")�Ƿ�. (����:";
								cout << item_name[int(ST_EXTARGS_TYPE::int_with_set_error)];
								cout << ", ��Χ[";
								for (const int* p = args[index].extargs_int_set; *p != INVALID_INT_VALUE_OF_SET;) {
									cout << *p++;
									cout << (*p == INVALID_INT_VALUE_OF_SET ? "]" : "/");
								}
								cout << ")" << endl;
								return -1;
							}
							else
								value2 = args[index].extargs_int_default;
						}
						args[index].extargs_int_value = value2;
						break;
					}
					case ST_EXTARGS_TYPE::double_with_set_default:
					case ST_EXTARGS_TYPE::double_with_set_error:
					{
						if (!Is_double(argv[i + 1])) {
							cout << "����[" << argv[i] << "]�ĸ��Ӳ�����������. (����:";
							cout << item_name[int(ST_EXTARGS_TYPE::double_with_set_default)];
							cout << ", ��Χ[";
							for (const double* p = args[index].extargs_double_set; *p != INVALID_DOUBLE_VALUE_OF_SET;) {
								cout << *p++;
								cout << (*p == INVALID_DOUBLE_VALUE_OF_SET ? "]" : "/");
							}
							if (args[index].extargs_type == ST_EXTARGS_TYPE::double_with_set_error)
								cout << ")" << endl;
							else
								cout << " ȱʡ:" << args[index].extargs_double_default << ")" << endl;
							return -1;
						}
						double value2 = atof(argv[i + 1]);
						bool flag = false;
						for (const double* p = args[index].extargs_double_set; *p != INVALID_DOUBLE_VALUE_OF_SET; p++) {
							if (*p == value2) {
								flag = true;
								break;
							}
						}
						if (!flag) {
							if (args[index].extargs_type == ST_EXTARGS_TYPE::double_with_set_error) {
								cout << "����[" << argv[i] << "]�ĸ��Ӳ���ֵ(" << value2 << ")�Ƿ�. (����:";
								cout << item_name[int(ST_EXTARGS_TYPE::double_with_set_error)];
								cout << ", ��Χ[";
								for (const double* p = args[index].extargs_double_set; *p != INVALID_DOUBLE_VALUE_OF_SET;) {
									cout << *p++;
									cout << (*p == INVALID_DOUBLE_VALUE_OF_SET ? "]" : "/");
								}
								cout << ")" << endl;
								return -1;
							}
							else
								value2 = args[index].extargs_double_default;
						}
						args[index].extargs_double_value = value2;
						break;
					}
					case ST_EXTARGS_TYPE::str:
						if (i < argc - 1 && argv[i + 1][0] == '-' && argv[i + 1][1] == '-') {
							cout << "����[" << argv[i] << "]ȱ�ٸ��Ӳ���. (����:" << item_name[int(ST_EXTARGS_TYPE::str)];
							if (!args[index].extargs_string_default.empty())
								cout << " ȱʡ:" << args[index].extargs_string_default << ")" << endl;
							else
								cout << ")" << endl;
							return -1;
						}
						args[index].extargs_string_value = argv[i + 1];
						break;
					case ST_EXTARGS_TYPE::str_with_set_default:
					case ST_EXTARGS_TYPE::str_with_set_error:
					{
						if (i < argc - 1 && argv[i + 1][0] == '-' && argv[i + 1][1] == '-') {
							cout << "����[" << argv[i] << "]�ĸ��Ӳ�������. (����:";
							cout << item_name[int(ST_EXTARGS_TYPE::str_with_set_default)];
							cout << ", ��ȡֵ[";
							for (const string* p = args[index].extargs_string_set; !p->empty();) {
								cout << *p++;
								cout << (p == args[index].extargs_string_set ? "]" : "/");
							}
							if (args[index].extargs_type == ST_EXTARGS_TYPE::str_with_set_error)
								cout << ")" << endl;
							else
								cout << " ȱʡ:" << args[index].extargs_string_default << ")" << endl;
							return -1;
						}
						string strvalue = argv[i + 1];
						bool flag = false;
						for (const string* p = args[index].extargs_string_set; !p->empty(); p++) {
							if (*p == strvalue) {
								flag = true;
								break;
							}
						}
						if (!flag) {
							if (args[index].extargs_type == ST_EXTARGS_TYPE::str_with_set_error) {
								cout << "����[" << argv[i] << "]�ĸ��Ӳ���ֵ(" << argv[i + 1] << ")�Ƿ�. (����:";
								cout << item_name[int(ST_EXTARGS_TYPE::str_with_set_error)];
								cout << ", ��ȡֵ[";
								for (const string* p = args[index].extargs_string_set; !p->empty();) {
									cout << *p++;
									cout << (p == args[index].extargs_string_set ? "]" : "/");
								}
								cout << ")" << endl;
								return -1;
							}
							else
								strvalue = args[index].extargs_string_default;
						}
						args[index].extargs_string_value = strvalue;
						break;
					}
					case ST_EXTARGS_TYPE::ipaddr_with_default:
					case ST_EXTARGS_TYPE::ipaddr_with_error:
						if (!Is_IP(argv[i + 1])) {
							if (args[index].extargs_type == ST_EXTARGS_TYPE::ipaddr_with_error) {
								cout << "����[" << argv[i] << "]�ĸ��Ӳ���ֵ(" << argv[i + 1] << ")�Ƿ�. (����:" << item_name[int(ST_EXTARGS_TYPE::ipaddr_with_error)] << ")";
								return -1;
							}
							else
								args[index].extargs_ipaddr_value = args[index].extargs_ipaddr_default;
						}
						else
						{
							unsigned int my_ip = 0;
							int point[5] = { -1, 0, 0, 0, (int)strlen(argv[i + 1]) }; // �洢 '.' ��λ��
							int pointCnt = 0;

							// ���� argv[i + 1]������ÿ�����λ��
							for (int j = 0; argv[i + 1][j]; j++) {
								if (argv[i + 1][j] == '.') {
									point[++pointCnt] = j;
								}
							}

							// ȷ�����λ������Ч�ģ�Ӧ���� 3 ���㣩
							if (pointCnt == 3) {
								for (int j = 0; j <= 3; j++) {
									my_ip |= atoi(argv[i + 1] + point[j] + 1) << (3 - j) * 8;
								}
							}

							// ��ת����� IP ��ַ�洢����Ӧλ��
							args[index].extargs_ipaddr_value = my_ip;
						}	
						break;
				}
				i++, cnt++;
			}
		}
		else if (follow_up_args)
			return cnt;
		else {
			cout << "����[" << argv[i] << "]��ʽ�Ƿ�(����--��ͷ����Ч����)." << endl;
			return -1;
		}
	}
	return cnt; //�˾������Ҫ�޸�range
}


/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ������Ԫ����
***************************************************************************/
int args_analyse_print(const args_analyse_tools* const args) 
{
	int name_length = 5, type_length = 5, default_length = 8, exists_length = 7, value_length = 6, ranset_length = 10; 

	// �ò�����������ÿ���п��
	for (int i = 0; args[i].extargs_type != ST_EXTARGS_TYPE::null; i++) 
	{
		name_length = max(name_length, (int)args[i].args_name.size() + 1);
		type_length = max(type_length, (int)type_name[(int)args[i].extargs_type].size() + 1);
		value_length = max(value_length, args[i].value_length);

		// ����range_length
		int range_length = 0, set_len = 0;

		if (args[i].have_intrange) // intrange����
		{ 
			// �������ֵ�λ��
			int min_len = 1, max_len = 1;
			int int_min = args[i].extargs_int_min;
			int int_max = args[i].extargs_int_max;

			while (int_min / 10) 
			{
				min_len++;
				int_min = int_min / 10;
			}

			while (int_max / 10) 
			{
				max_len++;
				int_max = int_max / 10;
			}

			range_length = min_len + max_len + 5; // [ .. ] �ո�
		}
		else if (args[i].have_intset) { // intset����
			for (int j = 0; args[i].extargs_int_set[j] != INVALID_INT_VALUE_OF_SET; j++) 
			{
				// �������ֵ�λ��
				int int_value = args[i].extargs_int_set[j];
				int bit_len = 1;
				while (int_value / 10) 
				{
					bit_len++;
					int_value = int_value / 10;
				}
				set_len += (bit_len + 1); // ÿ�����ֳ��ȼ��� 1 (��Ϊ�� "/")
			}
		}

		else if (args[i].have_stringset)  // strset
			for (int j = 0; args[i].extargs_string_set[j] != ""; j++) 
				set_len += ((int)args[i].extargs_string_set[j].size() + 1);
		else if (args[i].extargs_type == ST_EXTARGS_TYPE::double_with_default || args[i].extargs_type == ST_EXTARGS_TYPE::double_with_error ||
			args[i].extargs_type == ST_EXTARGS_TYPE::double_with_set_default || args[i].extargs_type == ST_EXTARGS_TYPE::double_with_set_error) 
		{
			// ����double����󳤶�
			int double_len = 0;
			stringstream ss;
			ss << fixed << setprecision(6) << args[i].extargs_double_min;
			double_len = ss.str().size(); // ��ʼ����Ϊ min �ĳ���
			ss.str("");
			ss << fixed << setprecision(6) << args[i].extargs_double_max;
			double_len = max(double_len, (int)ss.str().size()); // ���ֵ�ĳ���
			range_length = double_len + 2; // "[  .. ]" �ո�

			// ����� double with set (set�����)
			if (args[i].extargs_type == ST_EXTARGS_TYPE::double_with_set_default || args[i].extargs_type == ST_EXTARGS_TYPE::double_with_set_error) 
			{
				for (int j = 0; args[i].extargs_double_set[j] != INVALID_DOUBLE_VALUE_OF_SET; j++) 
				{
					ss.str(""); // ����ַ�����
					ss << fixed << setprecision(6) << args[i].extargs_double_set[j];
					set_len += ss.str().size(); // ����ÿ�� double �ĳ���
					if (args[i].extargs_double_set[j + 1] != INVALID_DOUBLE_VALUE_OF_SET) 
						set_len += 1; // ÿ��ֵ֮���� '/'�����Ϸָ����ĳ���
				}
			}
		}
		else 
		{
			range_length = 2;
			set_len = 2;
		}

		// ѡ�����ĳ���
		ranset_length = max(ranset_length, max(range_length, set_len) + 1);


		// ���� double ���ͣ�������󳤶Ȳ����� default_length �� value_length
		if (args[i].extargs_type == ST_EXTARGS_TYPE::double_with_default || args[i].extargs_type == ST_EXTARGS_TYPE::double_with_set_default
			|| args[i].extargs_type == ST_EXTARGS_TYPE::double_with_error || args[i].extargs_type == ST_EXTARGS_TYPE::double_with_set_error) 
		{
			// ȷ������㹻��ʾ����С����6λС����
			int double_length = 0;
			stringstream ss;
			ss << fixed << setprecision(6) << args[i].extargs_double_default;
			double_length = ss.str().size(); // ��ȡ��ʾʱ��Ҫ���ַ���

			default_length = max(default_length, double_length);
		}
		else 
		{
			string default_print = "/";

			// ��ȡ���͵�����ֵ
			int type_id = static_cast<int>(args[i].extargs_type);

			switch (type_id) 
			{
				case static_cast<int>(ST_EXTARGS_TYPE::boolean): 
					default_print = args[i].extargs_bool_default ? "true" : "false";
					break;
				case static_cast<int>(ST_EXTARGS_TYPE::int_with_default):
				case static_cast<int>(ST_EXTARGS_TYPE::int_with_set_default): 
					default_print = to_string(args[i].extargs_int_default);
					break;
				case static_cast<int>(ST_EXTARGS_TYPE::double_with_default):
				case static_cast<int>(ST_EXTARGS_TYPE::double_with_set_default): 
					default_print = to_string(args[i].extargs_double_default);
					break;
				case static_cast<int>(ST_EXTARGS_TYPE::str_with_set_default):
				case static_cast<int>(ST_EXTARGS_TYPE::str): 
					if (!args[i].extargs_string_default.empty()) 
						default_print = args[i].extargs_string_default;
					break;
				case static_cast<int>(ST_EXTARGS_TYPE::ipaddr_with_default): 
				{
					unsigned int ip = args[i].extargs_ipaddr_default;
					stringstream ss;
					ss << ((ip >> 24) & 0xFF) << '.' << ((ip >> 16) & 0xFF) << '.' << ((ip >> 8) & 0xFF) << '.' << (ip & 0xFF);               
					default_print = ss.str();
					break;
				}
				default: 
					// Ĭ������±���Ĭ��ֵ "/"
					break;
			}

			default_length = max(default_length, static_cast<int>(default_print.size()) + 1);

			string value_print = "/";
			int value_length0 = 0;
			if (args[i].args_existed) 
			{
				if (args[i].is_bool) 
					value_print = "true";
				else if (args[i].have_intrange || args[i].have_intset) 
					value_print = to_string(args[i].extargs_int_value);
				else if (args[i].have_doublerange || args[i].have_doubleset) 
				{
					stringstream ss;
					ss << fixed << setprecision(6) << args[i].extargs_double_value;
					value_print = ss.str();
					value_length0 = ss.str().size();
				}
				else if (args[i].is_string || args[i].have_stringset) 
					value_print = args[i].extargs_string_value;
				else if (args[i].is_ip) 
				{
					string value_print0 = "/";

					// ���� IP ��ַ����
					if (args[i].args_existed && args[i].is_ip) 
					{
						unsigned int ip = args[i].extargs_ipaddr_value;
						stringstream ss;
						ss << ((ip >> 24) & 0xFF) << '.' << ((ip >> 16) & 0xFF) << '.' << ((ip >> 8) & 0xFF) << '.' << (ip & 0xFF);
						value_print0 = ss.str();
					}
					value_print = value_print0;
				}
				if (!(args[i].have_doublerange || args[i].have_doubleset)) 
					value_length0 = value_print.size();
			}
			value_length = max(value_length, value_length0 + 1);    //warning:����û�б�
		}
	}

	for (int i = 0; args[i].extargs_type != ST_EXTARGS_TYPE::null; i++) 
	{
		// ����Ĭ��ֵ
		string default_print = "/";
		int value_length0 = 0;
		// ��ȡ���͵�����ֵ
		int type_id = static_cast<int>(args[i].extargs_type);

		switch (type_id) {
			case static_cast<int>(ST_EXTARGS_TYPE::boolean): 
				default_print = args[i].extargs_bool_default ? "true" : "false";
				break;
			case static_cast<int>(ST_EXTARGS_TYPE::int_with_default):
			case static_cast<int>(ST_EXTARGS_TYPE::int_with_set_default): 
				default_print = to_string(args[i].extargs_int_default);
				break;
			case static_cast<int>(ST_EXTARGS_TYPE::double_with_default):
			case static_cast<int>(ST_EXTARGS_TYPE::double_with_set_default):
			{
				int value_length0 = 0;
				stringstream ss;
				ss << fixed << setprecision(6) << args[i].extargs_double_value;
				value_length0 = ss.str().size();  // ��ȡ������ֵ�ĳ���
				break;
			}
			case static_cast<int>(ST_EXTARGS_TYPE::str_with_set_default):
			case static_cast<int>(ST_EXTARGS_TYPE::str): 
				if (!args[i].extargs_string_default.empty()) 
					default_print = args[i].extargs_string_default;
				break;
			case static_cast<int>(ST_EXTARGS_TYPE::ipaddr_with_default): 
			{
				unsigned int ip = args[i].extargs_ipaddr_default;
				stringstream ss;
				ss << ((ip >> 24) & 0xFF) << '.' // ��ȡ��һ�� IP ��ַ
					<< ((ip >> 16) & 0xFF) << '.' // ��ȡ�ڶ��� IP ��ַ
					<< ((ip >> 8) & 0xFF) << '.'  // ��ȡ������ IP ��ַ
					<< (ip & 0xFF);               // ��ȡ���Ķ� IP ��ַ
				default_print = ss.str();
				break;
			}
			default: 
				// �����ƥ���κ����ͣ����� default_print Ϊ "/"
				break;
		}

		// ���� default_length
		default_length = max(default_length, static_cast<int>(default_print.size()) + 1);

		string value_print = "/";
		if (args[i].args_existed) 
		{
			if (args[i].is_bool) 
				value_print = "true";
			else if (args[i].have_intrange || args[i].have_intset) 
				value_print = to_string(args[i].extargs_int_value);
			else if (args[i].have_doublerange || args[i].have_doubleset) 
			{
				stringstream ss;
				ss << fixed << setprecision(6) << args[i].extargs_double_value;
				value_print = ss.str();
				value_length0 = ss.str().size();
			}
			else if (args[i].is_string || args[i].have_stringset) 
				value_print = args[i].extargs_string_value;
			else if (args[i].is_ip) 
			{
				string value_print0 = "/";

				// ���� IP ��ַ����
				if (args[i].args_existed && args[i].is_ip) 
				{
					unsigned int ip = args[i].extargs_ipaddr_value;
					stringstream ss;
					ss << ((ip >> 24) & 0xFF) << '.' // ��ȡ��һ�� IP ��ַ
						<< ((ip >> 16) & 0xFF) << '.' // ��ȡ�ڶ��� IP ��ַ
						<< ((ip >> 8) & 0xFF) << '.'  // ��ȡ������ IP ��ַ
						<< (ip & 0xFF);               // ��ȡ���Ķ� IP ��ַ
					value_print0 = ss.str();
				}
				value_print = value_print0;
			}
			if (!(args[i].have_doublerange || args[i].have_doubleset)) 
				value_length0 = value_print.size();
		}
		value_length = max(value_length, value_length0 + 1);
	}

	cout << resetiosflags(ios::right) << setiosflags(ios::left);

	// ��ӡ��ͷ��
	int all_length = name_length + type_length + default_length + exists_length + value_length + ranset_length + 1;
	cout << setw(all_length) << setfill('=') << '=' << endl;

	// ��ӡ��ͷ
	cout << " " << setw(name_length) << setfill(' ') << head[0] << setw(type_length) << head[1] << setw(default_length) << head[2] << setw(exists_length) << head[3] << setw(value_length) << head[4] << head[5] << endl;

	cout << setw(all_length) << setfill('=') << '=' << endl;

	// ��ӡ��������
	for (int i = 0; args[i].extargs_type != ST_EXTARGS_TYPE::null; i++) 
	{
		cout << " " << setw(name_length) << setfill(' ') << args[i].args_name;
		cout << setw(type_length) << type_name[(int)args[i].extargs_type];

		// ����Ĭ��ֵ
		string default_print = "/";
		int value_length0 = 0;
		// ��ȡ���͵�����ֵ
		int type_id = static_cast<int>(args[i].extargs_type);

		switch (type_id)
		{
			case static_cast<int>(ST_EXTARGS_TYPE::boolean):
				default_print = args[i].extargs_bool_default ? "true" : "false";
				break;
			case static_cast<int>(ST_EXTARGS_TYPE::int_with_default):
			case static_cast<int>(ST_EXTARGS_TYPE::int_with_set_default):
				default_print = to_string(args[i].extargs_int_default);
				break;
			case static_cast<int>(ST_EXTARGS_TYPE::double_with_default):
			case static_cast<int>(ST_EXTARGS_TYPE::double_with_set_default):
				default_print = to_string(args[i].extargs_double_default);
				break;
			case static_cast<int>(ST_EXTARGS_TYPE::str_with_set_default):
			case static_cast<int>(ST_EXTARGS_TYPE::str):
				if (!args[i].extargs_string_default.empty())
					default_print = args[i].extargs_string_default;
				break;
			case static_cast<int>(ST_EXTARGS_TYPE::ipaddr_with_default):
			{
				unsigned int ip = args[i].extargs_ipaddr_default;
				stringstream ss0;
				ss0 << ((ip >> 24) & 0xFF) << '.' << ((ip >> 16) & 0xFF) << '.' << ((ip >> 8) & 0xFF) << '.' << (ip & 0xFF);
				default_print = ss0.str();
				break;
			}
			default:
				// �����ƥ���κ����ͣ����� default_print Ϊ "/"
				break;
		}

		// ���� default_length
		default_length = max(default_length, static_cast<int>(default_print.size()) + 1);

		cout << setw(default_length) << default_print;

		// ��ӡ exists
		cout << setw(exists_length) << args[i].args_existed;

		// ��ӡ value
		string value_print = "/";
		if (args[i].args_existed)
		{
			if (args[i].is_bool)
				value_print = "true";
			else if (args[i].have_intrange || args[i].have_intset)
				value_print = to_string(args[i].extargs_int_value);
			else if (args[i].have_doublerange || args[i].have_doubleset)
			{
				stringstream ss;
				ss << fixed << setprecision(6) << args[i].extargs_double_value;
				value_print = ss.str();
				value_length0 = ss.str().size();
			}
			else if (args[i].is_string || args[i].have_stringset)
				value_print = args[i].extargs_string_value;
			else if (args[i].is_ip)
			{
				string value_print0 = "/";
				// ���� IP ��ַ����
				if (args[i].args_existed && args[i].is_ip)
				{
					unsigned int ip = args[i].extargs_ipaddr_value;
					stringstream ss;
					ss << ((ip >> 24) & 0xFF) << '.' << ((ip >> 16) & 0xFF) << '.' << ((ip >> 8) & 0xFF) << '.' << (ip & 0xFF);
					value_print0 = ss.str();
				}
				value_print = value_print0;
			}
			if (!(args[i].have_doublerange || args[i].have_doubleset))
				value_length0 = value_print.size();
		}
		// ���� value_length
		value_length = max(value_length, value_length0 + 1);
		cout << setw(value_length) << value_print;

		// ��ӡ range/set
		if (args[i].have_intrange)
			cout << "[" << args[i].extargs_int_min << ".." << args[i].extargs_int_max << "]";
		else if (args[i].have_intset)
			for (int j = 0; args[i].extargs_int_set[j] != INVALID_INT_VALUE_OF_SET; j++)
				cout << (j == 0 ? "" : "/") << args[i].extargs_int_set[j];
		else if (args[i].have_stringset)
			for (int j = 0; args[i].extargs_string_set[j] != ""; j++)
				cout << (j == 0 ? "" : "/") << args[i].extargs_string_set[j];
		else if (args[i].extargs_type == ST_EXTARGS_TYPE::double_with_default || args[i].extargs_type == ST_EXTARGS_TYPE::double_with_error)
			cout << fixed << setprecision(6) << "[" << args[i].extargs_double_min << ".." << args[i].extargs_double_max << "]";
		else if (args[i].extargs_type == ST_EXTARGS_TYPE::double_with_set_default || args[i].extargs_type == ST_EXTARGS_TYPE::double_with_set_error)
			for (int j = 0; args[i].extargs_double_set[j] != INVALID_DOUBLE_VALUE_OF_SET; j++)
				cout << (j == 0 ? "" : "/") << fixed << setprecision(6) << args[i].extargs_double_set[j];
		else
			cout << "/";
		cout << endl;
	}

	// ��ӡ��β��
	cout << setw(all_length) << setfill('=') << '=' << endl;
	cout << defaultfloat << endl;
	return 0;
}
#endif // !ENABLE_LIB_COMMON_TOOLS