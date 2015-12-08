
#include "stat_func_sum.h"

#include <string>
#include <stdlib.h>
#include "stat_win.h"
#include "stat_win_fac.h"
#include "db_userpattern.h"

class db_userpattern;
class Pattern;


stat_func_sum::stat_func_sum(char *name)
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


stat_func_sum::~stat_func_sum()
{
	delete[] _name;
}
std::string stat_func_sum::type(db_stat &st)
	{
		return "DOUBLE";
	}

std::string stat_func_sum::name()
	{
		return "SUM";
	}


std::string stat_func_sum::set(std::string &d, db_stat &stat, int cur_minute, std::string cur_value)
	{
		if (d.empty())
			d = "";

		if (cur_value.empty())
			return d;
		double value;
		if (atoi(cur_value.c_str()))
			value = atoi(cur_value.c_str());
		int min_win_time = stat.min_win_time(cur_minute);
		int cur_win_time = stat.cur_win_time(cur_minute);

		stat_win_fac<stat_win_D*> fac(d, min_win_time, stat_win_D::_fac, stat
			.dec_win_when_set());
		stat_win_fac<stat_win_D*>::FI fi = fac.find_r(cur_win_time);
		if (fi.flag > 0)
		{
			return fac.tostring() + stat_win_D(cur_win_time, value).toString(fac.base_time1());
		}
		else if (fi.flag == 0)
		{
			fi.e->dV += value;
		}
		else
		{
			fac.insert1(fac.rindex() + 1,  new stat_win_D(cur_win_time, value));
		}

		return fac.tostring();
	}

std::string  stat_func_sum::get(std::string &data, db_stat &stat, int cur_minute, std::string cur_value)
	{
		char buf[100];
		if (data.empty())
			return "";

		int min_win_time = stat.min_win_time(cur_minute);
		stat_win_fac<stat_win_D*> fac(data, min_win_time,
			stat_win_D::_fac);

		stat_win_D *w = fac.next();
		if (w == NULL)
			return "";
		double c = 0;
		for (; w != NULL;w = fac.next())
		{
			c += w->dV;
		}
		sprintf(buf, "%.2f", c);
		return buf;
	}

bool stat_func_sum::need_curval_when_get() const
	{
		return false;
	}

bool stat_func_sum::need_curval_when_set() const
	{
		return true;
	}

std::string  stat_func_sum::getAll(std::string &data, db_stat &stat, int cur_minute) {
		// TODO Auto-generated method stub
		return get(data, stat, cur_minute, std::string(""));
	}

std::string stat_func_sum::getPatternValue(db_stat &st, stat_row& sd, db_userpattern &up,
		long txntime, int txn_minute, std::string &curVal) 
	{
		
		if (up.pattern_m.size() == 0)
			return "";

		//取该统计的行为习惯
		std::list<Pattern> p_l = up.pattern_m.at(st.stat_id);
		if (p_l.size() == 0)
			return "";

		std::list<Pattern>::iterator it = p_l.begin();
		for (; it != p_l.end();++it)
		{
			// 交易时间在行为习惯的有效期内
			if ((*it).is_enable(txntime))
			{
			return (*it).pattern_value;
			}
		}

		return "";
	}

















