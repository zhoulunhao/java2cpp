
#include "stat_number_encode.h"
#include "stat_win.h"
#include <string.h>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
class stat_win_base;
stat_win_S *stat_win_S::_fac = new stat_win_S ;
stat_win_L *stat_win_L::_fac = new stat_win_L ;
stat_win_D *stat_win_D::_fac = new stat_win_D ;
stat_win_LD *stat_win_LD::_fac = new stat_win_LD ;
stat_win_LS *stat_win_LS::_fac = new stat_win_LS ;

stat_win_S::stat_win_S() :stat_win_base(0), sV("")
{
	
}
stat_win_S::stat_win_S(int t, std::string& c) : stat_win_base(t), sV(c)
{
	
}

stat_win_S::~stat_win_S()
{
	
}
stat_win_base *stat_win_S::from(std::string items[], stat_win_fac<stat_win_base *> *buff, int base_time)
{
	int t = stat_number_encode::decode_int(items[0])+ base_time;
	std::string c = (int)items->length() > 1 ? items[1] : "";
	stat_win_S *ret = new stat_win_S(t, c);
	if(ret == NULL)
	{
		printf("new stat_win_S error\n");
		
	}
	ret->fac = buff;
	delete[] items;
	items = NULL;
	return ret;
}

void stat_win_S::appendTo(char **buf, int baseTime)
{
		strcat(*buf, stat_number_encode::encode(this->win_time - baseTime).c_str());
		strcat(*buf, ":");
		strcat(*buf, sV.c_str());
		strcat(*buf, "|");
}
//stat_win_S *Array()
//{
//	return _array;
//}

//string *stat_win_L::Array()
//{
//	return _array;
//}
stat_win_L::stat_win_L() :stat_win_base(0), lV(0)
{
	
}

stat_win_L::~stat_win_L()
{
	
}
stat_win_L::stat_win_L(int t, int c) :stat_win_base(t), lV(c)
{
	
}
void stat_win_L::appendTo(char **buf, int baseTime)
{

	strcat(*buf, stat_number_encode::encode(this->win_time - baseTime).c_str());
	strcat(*buf, ":");
	strcat(*buf, stat_number_encode::encode(lV).c_str());
	strcat(*buf, "|");
}
stat_win_base * stat_win_L::from(std::string items[], stat_win_fac<stat_win_base *> *buff, int base_time)
{
	int t = stat_number_encode::decode_int(items[0]) + base_time;
	int c = stat_number_encode::decode_int(items[1]);
	stat_win_L *ret = new stat_win_L(t, c);
	ret->fac = buff;
	if(ret == NULL)
	{
		printf("new stat_win_L error\n");
		
	}
	delete[] items;
	items = NULL;
	return ret;
}

stat_win_D::stat_win_D() :stat_win_base(0), dV(0.00000)
{
	
}

stat_win_D::~stat_win_D()
{
	
}

stat_win_D::stat_win_D(int t, double c) :stat_win_base(t), dV(c)
{
}

void stat_win_D::appendTo(char **buf, int baseTime)
{
	char buf1[100];
	sprintf(buf1, "%.2f", dV);
	strcat(*buf, stat_number_encode::encode(this->win_time - baseTime).c_str());
	strcat(*buf, ":");
	strcat(*buf, buf1);
	strcat(*buf, "|");
}

stat_win_base *stat_win_D::from(std::string items[], stat_win_fac<stat_win_base *> *buff, int base_time)
{
	int t = stat_number_encode::decode_int(items[0]) + base_time;
	double c = atoi(items[1].c_str());
	stat_win_D  *ret  = new stat_win_D(t, c);
	
	if(ret == NULL)
	{
		printf("new stat_win_D error\n");
	}
	ret->fac = buff;
	delete[] items;
	items = NULL;
	return ret;
}


stat_win_LD::stat_win_LD() :stat_win_base(0), lV(0), dV(0.0000)
{
	
}
stat_win_LD::~stat_win_LD()
{
	
}

stat_win_LD::stat_win_LD(int t, int c, double v) : stat_win_base(t), lV(c), dV(v)
{
	
}

void stat_win_LD::appendTo(char **buf, int baseTime)
{
	char buf1[100];
	sprintf(buf1, "%.2f", dV);
	printf("sizeof(stat_number_encode::encode(this->win_time - baseTime).c_str()) = %s\n",
		stat_number_encode::encode(this->win_time - baseTime).c_str());
	strcat(*buf, stat_number_encode::encode(this->win_time - baseTime).c_str());
	
	strcat(*buf, ":");
	strcat(*buf, stat_number_encode::encode(lV).c_str());
	strcat(*buf, ":");
	strcat(*buf, buf1);
	strcat(*buf, "|");
}

stat_win_base *stat_win_LD::from(std::string items[], stat_win_fac<stat_win_base *> *buff, int base_time)
{
	int t = stat_number_encode::decode_int(items[0]) + base_time;
	int c = stat_number_encode::decode_int(items[1]);
	double v = atoi(items[2].c_str());
	stat_win_LD *ret = new stat_win_LD(t, c, v);
	
	if(ret == NULL)
	{
		printf("new stat_win_LD error\n");
		
	}
	ret->fac = buff;
	delete[] items;
	items = NULL;
	return ret;
}

stat_win_LS::stat_win_LS() :stat_win_base(0), lV(0), sV("")
{

}
stat_win_LS::~stat_win_LS()
{
	
}

stat_win_LS::stat_win_LS(int t, int c, std::string &v) :stat_win_base(t), lV(c), sV(v)
{
	
}


void stat_win_LS::appendTo(char **buf, int baseTime)
{
	strcat(*buf, stat_number_encode::encode(this->win_time - baseTime).c_str());
	strcat(*buf, ":");
	strcat(*buf, stat_number_encode::encode(lV).c_str());
	strcat(*buf, ":");
	strcat(*buf, sV.c_str());
	strcat(*buf, "|");
}

stat_win_base *stat_win_LS::from(std::string items[], stat_win_fac<stat_win_base *> *buff, int base_time)
{
	int t = stat_number_encode::decode_int(items[0]) + base_time;
	int c = stat_number_encode::decode_int(items[1]);
	std::string v = items[2];
	stat_win_LS *ret = new stat_win_LS(t, c, v);
	
	if(ret == NULL)
	{
		printf("new stat_win_LS error\n");
		
	}
	ret->fac = buff;
	delete[] items;
	items = NULL;
	return ret;
}