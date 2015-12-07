
#ifndef __OP__H
#define __OP__H

#include <vector>
#include <string>
#include <algorithm>


class op
{
public:
	op();
	~op();

	static const char long_ = 1;
	static const char double_ =2;
	static const char time_  =3;
	static const char datetime_ =4;
	static const char span_ =5;
	static const char string_ = 6;
	static const char add_ = 7;
	static const char neg_ = 8;
	static const char sub_ = 9;
	static const char mul_ = 10;
	static const char div_ = 11;
	static const char mod_ = 12;
	static const char eq_ = 13;
	static const char ne_ = 14;
	static const char lt_ = 15;
	static const char le_ = 16;
	static const char gt_ = 17;
	static const char ge_ = 18;
	static const char and_  =19;
	static const char or_ = 20;
	static const char in_ = 21;
	static const char notin_ = 22;
	static const char id_ = 23;
	static const char func_ = 24;
	static const char stat_ = 25;
	static const char table_ = 26;
	static const char param_ = 27;
	static const char const_ = 28;
	static const char any_= 29;
	static const char stat_param_ = 30;
	static const char rule_ = 31;
	static const char op_end_ = 32;
	
public:
	static std::string op_name[33];
	static std::string op_name_loc[33];

};



class type_map: public op
{
public:
	std::string tms_type_name;
	char cond_type;
	bool operator==(const type_map &s);
	type_map(std::string &name, const char type);
	type_map(std::string name, const char type);
	//bool operator<(const type_map &a);
	type_map(const type_map &o);
	int compareTo(type_map &o);
	
public:
	static std::vector<type_map> g_tm;
	static void init_g_tm_and_sort();
	static char name2type(std::string &name);
	static std::string type2name(int type);
};


#endif