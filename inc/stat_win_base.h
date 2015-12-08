#ifndef __STAT_WIN_BASE__H
#define __STAT_WIN_BASE__H
#include <string>
#include "stat_win_fac.h"
template<typename T>
class stat_win_fac;

class stat_win_base
{
public:
	stat_win_base();
	~stat_win_base();
	stat_win_base(int t);
	stat_win_fac<stat_win_base *> *fac;
	int win_time;
	
public:
	std::string toString(int baseTime=0);
	
	stat_win_base &operator=(const stat_win_base &s);
	virtual void appendTo(char **buf, int base_time);
	virtual stat_win_base* from(std::string *items, stat_win_fac<stat_win_base *> *buff,int base_time);
	
	//virtual 
	//std::string *Array();
};


#endif