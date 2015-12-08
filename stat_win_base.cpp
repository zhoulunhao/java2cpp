#include "stat_win_base.h"


stat_win_base::stat_win_base()
	:win_time(0)
{
	fac = NULL;
}
stat_win_base::stat_win_base(int t)
	: win_time(t)
{
	fac = NULL;
}

stat_win_base::~stat_win_base()
{
	
}

std::string stat_win_base::toString(int baseTime)
{
	char *buf = new char[100];
	this->appendTo(&buf, baseTime);
	return buf;
}


stat_win_base* stat_win_base::from(std::string *items,stat_win_fac<stat_win_base *> *buff, int base_time)
{
	
	return NULL;
}

void stat_win_base::appendTo(char **buf, int base_time)
{
	return ;
}


stat_win_base & stat_win_base::operator=(const stat_win_base &a)
{
	if (this->win_time == a.win_time)
	{
		return *this;
	}
	else
	{
		this->win_time = a.win_time;	
		return *this;
	}
}