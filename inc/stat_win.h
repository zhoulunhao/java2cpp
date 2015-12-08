

#ifndef __STAT_WIN_H

#define  __STAT_WIN_H

#include <string>
#include "stat_win_base.h"
#include "stat_win_fac.h"

template<typename T>
class stat_win_fac;
class stat_win_base;
class stat_win_S : public stat_win_base
{
public:
	static stat_win_S *_fac;
	std::string sV;
	//static stat_win_S *_array;
	
	stat_win_S();
	~stat_win_S();
	stat_win_S(int t, std::string &c);
	stat_win_base* from(std::string items[], stat_win_fac<stat_win_base *> *buff, int base_time);
	void appendTo(char **buf, int baseTime);
	//std::string *Array();
};

class stat_win_L: public stat_win_base
{
public:
	static stat_win_L *_fac;
	//static stat_win_L *_array;
	int lV;
	//std::string *Array();
	stat_win_L();
	~stat_win_L();
	stat_win_L(int t, int c);
	void appendTo(char **buf, int baseTime);
	stat_win_base*from(std::string items[], stat_win_fac<stat_win_base *> *buff, int base_time);

};


class stat_win_D : public stat_win_base
{

public:

	static stat_win_D *_fac;
	//static stat_win_D *_array;
	~stat_win_D();
	//std::string *Array();
	stat_win_D();
	stat_win_D(int t, double c);
	double dV;
	void appendTo(char **buf, int baseTime);
	stat_win_base *from(std::string items[], stat_win_fac<stat_win_base *> *buff, int base_time);


};



class stat_win_LD: public stat_win_base
{
public:
	static stat_win_LD *_fac;
	//static stat_win_LD *_array;

	//std::string * Array();
	~stat_win_LD();
	stat_win_LD();
	stat_win_LD(int t, int c, double v);
	int lV;
	double dV;
	void appendTo(char **buf, int baseTime);
	stat_win_base *from(std::string items[], stat_win_fac<stat_win_base *> *buff,int base_time);


}; 



class stat_win_LS :public stat_win_base
{
public:
	static stat_win_LS *_fac;
	//static stat_win_LS *_array;
	//std::string *Array();
	~stat_win_LS();
	stat_win_LS();
	stat_win_LS(int t, int c, std::string &v);
	int lV;
	std::string sV;
	void appendTo(char **buf, int baseTime);
	stat_win_base *from(std::string items[],stat_win_fac<stat_win_base *> *buff, int base_time);

};



#endif
