#include "stat_win_base.h"


stat_win_base::stat_win_base()
	:win_time(0)
{
	
}
stat_win_base::stat_win_base(int t)
	: win_time(t)
{

}

stat_win_base::~stat_win_base()
{

}

std::string stat_win_base::toString(int baseTime)
{
	//shared_ptr<char> str = shared_ptr<char>(new char(64));
	char *buf = new char[100];
	this->appendTo(&buf, baseTime);
	return buf;
}


stat_win_base* stat_win_base::from(std::string *items, int base_time)
{
	
	return NULL;
}

//std::string stat_win_base::toString()
//{
//	char *buf = new char[100];
//	this->appendTo(&str.c_str(), 0);
//	return str;
//}
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