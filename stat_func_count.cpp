

#include <string>
#include "stat_func_count.h"

#include <list>
#include "stat_win.h"
#include "stat_win_fac.h"





//string type(db_stat &st);
//string name();
//string set(string &d, db_stat &stat, int cur_minute, string &cur_value);
//string get(string &data, db_stat stat, int cur_minute, string &cur_value);
//bool need_curval_when_get();
//bool need_curval_when_set();
//string getAll(string &data, db_stat stat, int cur_minute);
//string getPatternValue(db_stat& st, stat_row &sd, db_userpattern &up, long txntime, int txn_minute, string &curVal);
//
//

stat_func_count::stat_func_count(char *name)
{
	if (name == NULL)
	{
		_name = new char[1];
		*_name = '\0';
	}
	else
	{
		int len = strlen(name);
		_name = new char[len + 1];
		strcpy(_name, name);
	}
}


stat_func_count::~stat_func_count()
{
	delete[] _name;
}

std::string stat_func_count::type(db_stat &st)
{
	return std::string("INT");
}
std::string stat_func_count::name()
{
	return std::string("COUNT");
}

std::string stat_func_count::set(std::string &d, db_stat &st, int cur_minute, std::string cur_value)
{
	if (d.empty())
		return std::string("");
	int min_win_time = st.min_win_time(cur_minute);
	int cur_win_time = st.cur_win_time(cur_minute);

	stat_win_fac<stat_win_L  *> fac(d, min_win_time, stat_win_L::_fac,st
		.dec_win_when_set());
	stat_win_fac<stat_win_L *>::FI fi = fac.find_r(cur_win_time);
	if (fi.flag > 0)
	{
		return fac.tostring() + stat_win_L(cur_win_time, 1).toString(fac.base_time1());
	}
	else if (fi.flag == 0)
	{
		fi.e->lV++;
	}
	else
	{
		fac.insert1(fac.rindex() + 1, new stat_win_L(cur_win_time, 1));
	}
	return fac.tostring();
}

std::string stat_func_count::get(std::string &data, db_stat &stat, int cur_minute, std::string cur_value)
{
	char buf[10];
	if (data.empty())
		return 0;
	int min_win_time = stat.min_win_time(cur_minute);

	stat_win_fac<stat_win_L *> fac(data,min_win_time,stat_win_L::_fac);
	long c = 0;
	stat_win_L *w;
	for (; (w = fac.next());)
	{
		c += w->lV;
	}
	sprintf(buf, "%.2f", (double)c);
	return buf;
}

std::string stat_func_count::getAll(std::string &data, db_stat &stat, int cur_time)
{
	
	return this->get(data, stat, cur_time, std::string(""));;
}
bool stat_func_count::need_curval_when_get() const
{
	return false;
}
bool stat_func_count::need_curval_when_set() const
{
	return true;
}

std::string stat_func_count::getPatternValue(db_stat &st, stat_row &sd, db_userpattern &up,
	long txntime, int txn_minute, std::string  &curVal)
{
	
	std::list <Pattern> p_l = up.pattern_m.at(st.stat_id);
	if(p_l.size() == 0)
		return "";
	std::list<Pattern> ::iterator it;
	it = p_l.begin();
	for (; it != p_l.end(); ++it)
	{
		if ((*it).is_enable(txntime))
		{
			return (*it).pattern_value;
		}
	}
	return std::string("");
}

