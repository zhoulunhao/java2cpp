
#include "op.h"

#include <iostream>
#include <stdio.h>




class type_map;
std::string op::op_name[33] = { "null", "long", "double", "time", "datetime",
"span", "string", "+", "-", "-",
"*", "/", "%", "=", "!=",
"<", "<=", ">", ">=", "and",
"or", "in", "notin", "id", "func",
"stat", "table", "param", "const", "any",
"stat_param_", "rule", "op_end" };

std::string op::op_name_loc[33] = { "空值", "整数", "浮点数", "时间", "日期",// 
"时间段", "字符串", "加上", "减去", "负的", //
"乘以", "除以", "取余数", "等于", "不等于", //
"小于", "小于等于", "大于", "大于等于", "并且", //
"或者", "包含于", "不包含于", "标示符", "函数", //
"统计", "名单", "函数参数", "常量", "any",//
"统计参数", "规则", "op_end" };
std::vector<type_map> type_map::g_tm;
op::op()
{

}

op::~op()
{

}



class comp
{
	public:
		bool operator()(const type_map &a,const type_map &b)
		{
			return a.tms_type_name < b.tms_type_name;
		}
};
type_map::type_map(const type_map &o)
{
	tms_type_name = o.tms_type_name;
	cond_type = o.cond_type;

}
type_map::type_map(std::string &name, const char type)
{
	
	tms_type_name = name;
	cond_type = type;
}


type_map::type_map(std::string name, const char type)
{
	tms_type_name = name;
	cond_type = type;
}


//bool type_map::operator< (const type_map &a)
//{
//	return tms_type_name < a.tms_type_name;
//}

//bool littleandless(const type_map a, const type_map b)
//{
//	return a.tms_type_name < b.tms_type_name;
//}





void type_map::init_g_tm_and_sort()
{
	g_tm.push_back(type_map(std::string("STRING"), string_));
	g_tm.push_back(type_map(std::string("INT"), long_));
	g_tm.push_back(type_map(std::string("LONG"), long_));
	g_tm.push_back(type_map(std::string("FLOAT"), double_));
	g_tm.push_back(type_map(std::string("DOUBLE"), double_));
	g_tm.push_back(type_map(std::string("MONEY"), double_));
	g_tm.push_back(type_map(std::string("TIME"), time_));
	g_tm.push_back(type_map(std::string("DATETIME"), datetime_));
	g_tm.push_back(type_map(std::string("DEVID"), string_));
	g_tm.push_back(type_map(std::string("IP"), string_));
	g_tm.push_back(type_map(std::string("USERID"), string_));
	g_tm.push_back(type_map(std::string("ACC"), string_));
	g_tm.push_back(type_map(std::string("CODE"), string_));
	std::sort(g_tm.begin(), g_tm.end(),comp());
	
}



char type_map::name2type(std::string &name)
{
	std::vector<type_map>::iterator it;
	for (it = g_tm.begin(); it != g_tm.end(); it++)
	{
		if ((*it).tms_type_name == name)
			return (*it).cond_type;
	}
	return 0;
}
bool type_map::operator==(const type_map &s)
{
	if (this->tms_type_name == s.tms_type_name)
		return true;
	else
		return false;
}

std::string type_map::type2name(int type)
{
	char b_type = (char)type;
	if (b_type == double_)
		return std::string("DOUBLE");
	else if (b_type == long_)
	{
		return std::string("LONG");
	}
	else if (b_type == datetime_)
	{
		return std::string("DATETIME");
	}
	else if (b_type == time_){
		return std::string("TIME");
	}
	else
	{
		return std::string("STRING");
	}

}


//int main()
//{
//	type_map::init_g_tm_and_sort();
//	std::vector<type_map>::iterator it;
//	std::cout << "排序后" << std::endl;
//	for(it = type_map::g_tm.begin();it!=type_map::g_tm.end();++it)
//	{
//		
//		
//		std::cout << (*it).tms_type_name<< '\t '<< std::endl;
//		printf("%d\n",(*it).cond_type);
//	}
//	
//	std::string str = "zhoulunhao";
//	type_map a("zhoulunhao", 77);
//	std::string s = "FLOAT";
//	char c = a.name2type(s);
//	printf("c = %d\n", c);
//	/*std::cout << c << std::endl;*/
//	
//	return 0;
//
//}