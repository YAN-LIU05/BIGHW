/* 2352018 大数据 刘彦 */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include "../include/class_aat.h"
//如有必要，可以加入其它头文件
using namespace std;

#if !ENABLE_LIB_COMMON_TOOLS //不使用lib才有效

/* ---------------------------------------------------------------
	 允许加入其它需要static函数（内部工具用）
   ---------------------------------------------------------------- */
static int* alloc_and_copy_array(const int* source, int size)
{
	int* array = new(nothrow) int[size];
	if (!array)
	{
		cerr << "动态申请 extargs_int_set 空间失败" << endl;
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
		cerr << "动态申请 extargs_double_set 空间失败" << endl;
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
		cerr << "动态申请 extargs_string_set 空间失败" << endl;
		exit(-1);
	}

	for (int i = 0; i < size; ++i)
		array[i] = source[i];

	return array;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：null
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
	have_int_def = have_double_def = have_str_def = have_ip_def = false;
	is_intrange = is_doublerange = is_intset = is_double_set = is_strset = false;
	default_length = value_length = 2;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：boolean
 ***************************************************************************/
args_analyse_tools::args_analyse_tools(const char* name, const enum ST_EXTARGS_TYPE type, const int ext_num, const bool def)
{
	if (type != ST_EXTARGS_TYPE::boolean)
	{
		cout << "args_analyse_tools类构造函数错误,传的参数type=" << int(type) << ",不是boolean(1)" << endl;
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
	have_int_def = have_double_def = have_str_def = have_ip_def = false;
	is_intrange = is_doublerange = is_intset = is_double_set = is_strset = false;
	default_length = (def) ? 5 : 6;
	value_length = 2;

}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：int_with_default、int_with_error
 ***************************************************************************/
args_analyse_tools::args_analyse_tools(const char* name, const enum ST_EXTARGS_TYPE type, const int ext_num, const int def, const int _min, const int _max)
{
	if (type != ST_EXTARGS_TYPE::int_with_default && type != ST_EXTARGS_TYPE::int_with_error)
	{
		cout << "args_analyse_tools类构造函数错误,传的参数type=" << int(type) << ",不是int_with_default(2)或int_with_error(3)" << endl;
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
		extargs_int_default = INVALID_INT_VALUE_OF_SET; // 重置int缺省值
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

	is_intrange = true;
	is_bool = is_int = is_double = is_string = is_ip = false;
	have_int_def = have_double_def = have_str_def = have_ip_def = false;
	is_doublerange = is_intset = is_double_set = is_strset = false;
	value_length = 2;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：int_with_set_default、int_with_set_error
 ***************************************************************************/
args_analyse_tools::args_analyse_tools(const char* name, const enum ST_EXTARGS_TYPE type, const int ext_num, const int def_of_set_pos, const int* const set)
{
	if (type != ST_EXTARGS_TYPE::int_with_set_default && type != ST_EXTARGS_TYPE::int_with_set_error)
	{
		cout << "args_analyse_tools类构造函数错误,传的参数type=" << int(type) << ",不是int_with_set_default(4)或int_with_set_error(5)" << endl;
		exit(-1);
	}

	int size = 0;
	for (; set[size] != INVALID_INT_VALUE_OF_SET; ++size)
		;
	++size; // 结束标志的额外空间

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

	is_intset = true;
	is_bool = is_int = is_double = is_string = is_ip = false;
	have_int_def = have_double_def = have_str_def = have_ip_def = false;
	is_intrange = is_doublerange = is_double_set = is_strset = false;
	value_length = 2;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：str、ipaddr_with_default、ipaddr_with_error
 ***************************************************************************/
args_analyse_tools::args_analyse_tools(const char* name, const enum ST_EXTARGS_TYPE type, const int ext_num, const string def)
{
	if (type != ST_EXTARGS_TYPE::ipaddr_with_default && type != ST_EXTARGS_TYPE::ipaddr_with_error && type != ST_EXTARGS_TYPE::str)
	{
		cout << "args_analyse_tools类构造函数错误,传的参数type=" << int(type) << ",不是str(10)或ipaddr_with_default(13)或ipaddr_with_error(14)" << endl;
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
		int parts[4] = { 0 };  // 存储四个IP部分
		stringstream ss(def);  // 将 IP 字符串流化
		string part;
		int i = 0;

		// 按照 '.' 分割IP地址的每一部分并转换成整数
		while (getline(ss, part, '.'))
			parts[i++] = stoi(part);  // 将字符串转换为整数并存入数组
		unsigned int ipAddress = 0;
		for (i = 0; i < 4; ++i)
			ipAddress |= (parts[i] << (24 - (i * 8)));  // 通过位操作构建无符号整数
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
	have_int_def = have_double_def = have_str_def = have_ip_def = false;
	is_intrange = is_doublerange = is_intset = is_double_set = is_strset = false;
	default_length = (int)def.size() + 1;
	value_length = 2;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：str_with_set_default、str_with_set_error
 ***************************************************************************/
args_analyse_tools::args_analyse_tools(const char* name, const enum ST_EXTARGS_TYPE type, const int ext_num, const int def_of_set_pos, const string* const set)
{
	if (type != ST_EXTARGS_TYPE::str_with_set_default && type != ST_EXTARGS_TYPE::str_with_set_error)
	{
		cout << "args_analyse_tools类构造函数错误,传的参数type=" << int(type) << ",不是str_with_set_default(11)或str_with_set_error(12)" << endl;
		exit(-1);
	}

	int size = 0;
	for (; set[size] != ""; ++size)
		;
	++size; // 结束标志的额外空间

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
	is_strset = true;
	is_bool = is_int = is_double = is_string = is_ip = false;
	have_int_def = have_double_def = have_str_def = have_ip_def = false;
	is_intrange = is_doublerange = is_intset = is_double_set = false;
	value_length = 2;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：f
  返 回 值：
  说    明：double_with_default、double_with_error
 ***************************************************************************/
args_analyse_tools::args_analyse_tools(const char* name, const enum ST_EXTARGS_TYPE type, const int ext_num, const double	def, const double _min, const double _max)
{
	if (type != ST_EXTARGS_TYPE::double_with_default && type != ST_EXTARGS_TYPE::double_with_error)
	{
		cout << "args_analyse_tools类构造函数错误,传的参数type=" << int(type) << ",不是double_with_default(6)或double_with_error(7)" << endl;
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
		extargs_double_default = INVALID_INT_VALUE_OF_SET; // 重置int缺省值
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

	is_doublerange = true;
	is_bool = is_int = is_double = is_string = is_ip = false;
	have_int_def = have_double_def = have_str_def = have_ip_def = false;
	is_intrange = is_intset = is_double_set = is_strset = false;
	value_length = 2;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：double_with_set_default、double_with_set_error
 ***************************************************************************/
args_analyse_tools::args_analyse_tools(const char* name, const enum ST_EXTARGS_TYPE type, const int ext_num, const int def_of_set_pos, const double* const set)
{
	if (type != ST_EXTARGS_TYPE::double_with_set_default && type != ST_EXTARGS_TYPE::double_with_set_error)
	{
		cout << "args_analyse_tools类构造函数错误,传的参数type=" << int(type) << ",不是double_with_set_default(8)或double_with_set_error(9)" << endl;
		exit(-1);
	}

	int size = 0;
	for (; set[size] != INVALID_DOUBLE_VALUE_OF_SET; ++size)
		;
	++size; // 结束标志的额外空间

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

	is_double_set = true;
	is_bool = is_int = is_double = is_string = is_ip = false;
	have_int_def = have_double_def = have_str_def = have_ip_def = false;
	is_intrange = is_doublerange = is_intset = is_strset = false;
	value_length = 2;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
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
	 允许AAT中自定义成员函数的实现（private）
   ---------------------------------------------------------------- */

   /***************************************************************************
	 函数名称：
	 功    能：
	 输入参数：
	 返 回 值：
	 说    明：已实现，不要动
	***************************************************************************/
const string args_analyse_tools::get_name() const
{
	return this->args_name;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：加!!后，只能是0/1
			已实现，不要动
 ***************************************************************************/
const int args_analyse_tools::existed() const
{
	return !!this->args_existed;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：已实现，不要动
 ***************************************************************************/
const int args_analyse_tools::get_int() const
{
	return this->extargs_int_value;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：已实现，不要动
 ***************************************************************************/
const double args_analyse_tools::get_double() const
{
	return this->extargs_double_value;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：已实现，不要动
 ***************************************************************************/
const string args_analyse_tools::get_string() const
{
	return this->extargs_string_value;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：已实现，不要动
 ***************************************************************************/
const unsigned int args_analyse_tools::get_ipaddr() const
{
	return this->extargs_ipaddr_value;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：将 extargs_ipaddr_value 的值从 0x7f000001 转为 "127.0.0.1"
 ***************************************************************************/
const string args_analyse_tools::get_str_ipaddr() const
{
	stringstream ss;
	ss << ((extargs_ipaddr_value >> 24) & 0xFF) << '.' // 获取第一段 IP 地址
		<< ((extargs_ipaddr_value >> 16) & 0xFF) << '.' // 获取第二段 IP 地址
		<< ((extargs_ipaddr_value >> 8) & 0xFF) << '.'  // 获取第三段 IP 地址
		<< (extargs_ipaddr_value & 0xFF);               // 获取第四段 IP 地址
	return ss.str();
}


/***************************************************************************
  函数名称：
  功    能：
  输入参数：follow_up_args：是否有后续参数
			0  ：无后续参数
			1  ：有后续参数
  返 回 值：
  说    明：友元函数
***************************************************************************/
int args_analyse_process(const int argc, const char* const* const argv, args_analyse_tools* const args, const int follow_up_args)
{
	return 0; //此句根据需要修改
}


/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：友元函数
***************************************************************************/
int args_analyse_print(const args_analyse_tools* const args) {
	int name_length = 5, type_length = 5, default_length = 8;
	int exists_length = 7, value_length = 6, ranset_length = 10; // exists参数的7已经为最大值，不需要再判断

	// 计算每个列宽度
	for (int i = 0; args[i].extargs_type != ST_EXTARGS_TYPE::null; i++) {
		name_length = max(name_length, (int)args[i].args_name.size() + 1);
		type_length = max(type_length, (int)type_name[(int)args[i].extargs_type].size() + 1);
		value_length = max(value_length, args[i].value_length);

		// 计算ranset_length
		int ran_len = 0, set_len = 0;

		if (args[i].is_intrange) { // intrange类型
			// 计算数字的位数
			int min_len = 1, max_len = 1;
			int int_min = args[i].extargs_int_min;
			int int_max = args[i].extargs_int_max;

			while (int_min / 10) {
				min_len++;
				int_min = int_min / 10;
			}

			while (int_max / 10) {
				max_len++;
				int_max = int_max / 10;
			}

			ran_len = min_len + max_len + 5; // [ .. ] 空格
		}
		else if (args[i].is_intset) { // intset类型
			for (int j = 0; args[i].extargs_int_set[j] != INVALID_INT_VALUE_OF_SET; j++) {
				// 计算数字的位数
				int int_value = args[i].extargs_int_set[j];
				int bit_len = 1;
				while (int_value / 10) {
					bit_len++;
					int_value = int_value / 10;
				}
				set_len += (bit_len + 1); // 每个数字长度加上 1 (因为有 "/")
			}
		}

		else if (args[i].is_strset) { // strset
			for (int j = 0; args[i].extargs_string_set[j] != ""; j++) {
				set_len += ((int)args[i].extargs_string_set[j].size() + 1);
			}
		}
		else if (args[i].extargs_type == ST_EXTARGS_TYPE::double_with_default || args[i].extargs_type == ST_EXTARGS_TYPE::double_with_error || 
			args[i].extargs_type == ST_EXTARGS_TYPE::double_with_set_default || args[i].extargs_type == ST_EXTARGS_TYPE::double_with_set_error) {
			// 计算double的最大长度
			int double_len = 0;
			stringstream ss;
			ss << fixed << setprecision(6) << args[i].extargs_double_min;
			double_len = ss.str().size(); // 初始设置为 min 的长度
			ss.str("");
			ss << fixed << setprecision(6) << args[i].extargs_double_max;
			double_len = max(double_len, (int)ss.str().size()); // 最大值的长度
			ran_len = double_len + 2; // "[  .. ]" 空格

			// 如果是 double with set (set的情况)
			if (args[i].extargs_type == ST_EXTARGS_TYPE::double_with_set_default || args[i].extargs_type == ST_EXTARGS_TYPE::double_with_set_error) {
				for (int j = 0; args[i].extargs_double_set[j] != INVALID_DOUBLE_VALUE_OF_SET; j++) {
					ss.str(""); // 清空字符串流
					ss << fixed << setprecision(6) << args[i].extargs_double_set[j];
					set_len += ss.str().size(); // 计算每个 double 的长度
					if (args[i].extargs_double_set[j + 1] != INVALID_DOUBLE_VALUE_OF_SET) {
						set_len += 1; // 每个值之间有 '/'，加上分隔符的长度
					}
				}
			}
		}
		else {
			ran_len = 2;
			set_len = 2;
		}

		// 选择最大的长度
		ranset_length = max(ranset_length, max(ran_len, set_len) + 1);


		// 对于 double 类型，计算最大长度并更新 default_length 和 value_length
		if (args[i].extargs_type == ST_EXTARGS_TYPE::double_with_default || args[i].extargs_type == ST_EXTARGS_TYPE::double_with_set_default 
			|| args[i].extargs_type == ST_EXTARGS_TYPE::double_with_error || args[i].extargs_type == ST_EXTARGS_TYPE::double_with_set_error) {
			// 确保宽度足够显示浮动小数（6位小数）
			int double_length = 0;
			stringstream ss;
			ss << fixed << setprecision(6) << args[i].extargs_double_default;
			double_length = ss.str().size(); // 获取显示时需要的字符数

			default_length = max(default_length, double_length);
		}
		else {
			string default_print = "/";

			// 获取类型的整数值
			int type_id = static_cast<int>(args[i].extargs_type);

			switch (type_id) {
				case static_cast<int>(ST_EXTARGS_TYPE::boolean): {
					default_print = args[i].extargs_bool_default ? "true" : "false";
					break;
				}
				case static_cast<int>(ST_EXTARGS_TYPE::int_with_default):
				case static_cast<int>(ST_EXTARGS_TYPE::int_with_set_default): {
					default_print = to_string(args[i].extargs_int_default);
					break;
				}
				case static_cast<int>(ST_EXTARGS_TYPE::str_with_set_default):
				case static_cast<int>(ST_EXTARGS_TYPE::str): {
					if (!args[i].extargs_string_default.empty()) {
						default_print = args[i].extargs_string_default;
					}
					break;
				}
				case static_cast<int>(ST_EXTARGS_TYPE::ipaddr_with_default): {
					unsigned int ip = args[i].extargs_ipaddr_default;
					stringstream ss;
					ss << ((ip >> 24) & 0xFF) << '.' // 获取第一段 IP 地址
						<< ((ip >> 16) & 0xFF) << '.' // 获取第二段 IP 地址
						<< ((ip >> 8) & 0xFF) << '.'  // 获取第三段 IP 地址
						<< (ip & 0xFF);               // 获取第四段 IP 地址
					default_print = ss.str();
					break;
				}
				default: {
					// 默认情况下保持默认值 "/"
					break;
				}
			}

			default_length = max(default_length, static_cast<int>(default_print.size()) + 1);

		}
	}

	cout << resetiosflags(ios::right) << setiosflags(ios::left);

	// 打印表头线
	int all_length = name_length + type_length + default_length + exists_length + value_length + ranset_length + 1;
	cout << setw(all_length) << setfill('=') << '=' << endl;

	// 打印表头
	cout << " " << setw(name_length) << setfill(' ') << head[0] << setw(type_length) << head[1] << setw(default_length) << head[2] << setw(exists_length) << head[3] << setw(value_length) << head[4] << head[5] << endl;

	cout << setw(all_length) << setfill('=') << '=' << endl;

	// 打印参数内容
	for (int i = 0; args[i].extargs_type != ST_EXTARGS_TYPE::null; i++) {
		cout << " " << setw(name_length) << setfill(' ') << args[i].args_name;
		cout << setw(type_length) << type_name[(int)args[i].extargs_type];

		// 计算默认值
		string default_print = "/";

		// 获取类型的整数值
		int type_id = static_cast<int>(args[i].extargs_type);

		switch (type_id) {
			case static_cast<int>(ST_EXTARGS_TYPE::boolean): {
				default_print = args[i].extargs_bool_default ? "true" : "false";
				break;
			}
			case static_cast<int>(ST_EXTARGS_TYPE::int_with_default):
			case static_cast<int>(ST_EXTARGS_TYPE::int_with_set_default): {
				default_print = to_string(args[i].extargs_int_default);
				break;
			}
			case static_cast<int>(ST_EXTARGS_TYPE::double_with_default):
			case static_cast<int>(ST_EXTARGS_TYPE::double_with_set_default): {
				default_print = to_string(args[i].extargs_double_default);
				break;
			}
			case static_cast<int>(ST_EXTARGS_TYPE::str_with_set_default):
			case static_cast<int>(ST_EXTARGS_TYPE::str): {
				if (!args[i].extargs_string_default.empty()) {
					default_print = args[i].extargs_string_default;
				}
				break;
			}
			case static_cast<int>(ST_EXTARGS_TYPE::ipaddr_with_default): {
				unsigned int ip = args[i].extargs_ipaddr_default;
				stringstream ss;
				ss << ((ip >> 24) & 0xFF) << '.' // 获取第一段 IP 地址
					<< ((ip >> 16) & 0xFF) << '.' // 获取第二段 IP 地址
					<< ((ip >> 8) & 0xFF) << '.'  // 获取第三段 IP 地址
					<< (ip & 0xFF);               // 获取第四段 IP 地址
				default_print = ss.str();
				break;
			}
			default: {
				// 如果不匹配任何类型，保持 default_print 为 "/"
				break;
			}
		}

		// 计算 default_length
		default_length = max(default_length, static_cast<int>(default_print.size()) + 1);

		cout << setw(default_length) << default_print;

		// 打印 exists
		cout << setw(exists_length) << args[i].args_existed;

		// 打印 value
		string value_print = "/";
		if (args[i].args_existed) {
			if (args[i].is_bool) {
				value_print = "true";
			}
			else if (args[i].is_intrange || args[i].is_intset) {
				value_print = to_string(args[i].extargs_int_value);
			}
			else if (args[i].is_string || args[i].is_strset) {
				value_print = args[i].extargs_string_value;
			}
			else if (args[i].is_ip) {
				string value_print0 = "/";

				// 处理 IP 地址类型
				if (args[i].args_existed && args[i].is_ip) {
					unsigned int ip = args[i].extargs_ipaddr_value;
					stringstream ss;
					ss << ((ip >> 24) & 0xFF) << '.' // 获取第一段 IP 地址
						<< ((ip >> 16) & 0xFF) << '.' // 获取第二段 IP 地址
						<< ((ip >> 8) & 0xFF) << '.'  // 获取第三段 IP 地址
						<< (ip & 0xFF);               // 获取第四段 IP 地址
					value_print0 = ss.str();
				}
				value_print = value_print0;
			}
			else if (args[i].is_double) {
				value_print = to_string(args[i].extargs_double_value);
			}
		}
		cout << setw(value_length) << value_print;

		// 打印 range/set
		if (args[i].is_intrange) {
			cout << "[" << args[i].extargs_int_min << ".." << args[i].extargs_int_max << "]";
		}
		else if (args[i].is_intset) {
			for (int j = 0; args[i].extargs_int_set[j] != INVALID_INT_VALUE_OF_SET; j++) {
				cout << (j == 0 ? "" : "/") << args[i].extargs_int_set[j];
			}
		}
		else if (args[i].is_strset) {
			for (int j = 0; args[i].extargs_string_set[j] != ""; j++) {
				cout << (j == 0 ? "" : "/") << args[i].extargs_string_set[j];
			}
		}
		else if (args[i].extargs_type == ST_EXTARGS_TYPE::double_with_default || args[i].extargs_type == ST_EXTARGS_TYPE::double_with_error) {
			cout << fixed << setprecision(6) << "[" << args[i].extargs_double_min << ".." << args[i].extargs_double_max << "]";
		}
		else if (args[i].extargs_type == ST_EXTARGS_TYPE::double_with_set_default || args[i].extargs_type == ST_EXTARGS_TYPE::double_with_set_error) {
			for (int j = 0; args[i].extargs_double_set[j] != INVALID_DOUBLE_VALUE_OF_SET; j++) {
				cout << (j == 0 ? "" : "/") << fixed << setprecision(6) << args[i].extargs_double_set[j];
			}
		}
		else {
			cout << "/";
		}
		cout << endl;
	}

	// 打印表尾线
	cout << setw(all_length) << setfill('=') << '=' << endl;
	cout << defaultfloat << endl;
	return 0;
}
#endif // !ENABLE_LIB_COMMON_TOOLS
