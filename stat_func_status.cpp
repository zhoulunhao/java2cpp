#include "stat_func_status.h"
#include <string>
#include <list>
#include "stat_win.h"
#include "db_userpattern.h"
stat_func_status::stat_func_status(char *name)
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


stat_func_status::~stat_func_status()
{
	delete[] _name;
}
std::string stat_func_status::name()
	{
		return "STATUS";
	}



std::string stat_func_status::type(db_stat &st)
	{
		return "INT";
	}

std::string stat_func_status::set(std::string &d, db_stat &stat, int cur_minute, std::string cur_value)
{
		if (d.empty())
			d = "";

		int cur_win_time = stat.cur_win_time(cur_minute);
		std::string s = "1";
		stat_win_S  t (cur_win_time,s);
		return  t.toString(0);
}
std::string stat_func_status::get(std::string &data, db_stat &stat, int cur_minute, std::string cur_value)
	{
		
		if (data.empty())
			return "";

		int min_win_time = stat.min_win_time(cur_minute);
		stat_win_fac<stat_win_S*> fac(data, min_win_time,
			stat_win_S::_fac);
		stat_win_S *last = fac.next_r();
		if (last == NULL)
			return "";

		return "1";
	}
bool stat_func_status::need_curval_when_get() const
	{
		return false;
	}
bool stat_func_status::need_curval_when_set() const
	{
		return false;
	}
	
std::string stat_func_status::getAll(std::string &data, db_stat &stat, int cur_minute) {
		// TODO Auto-generated method stub
		return this->get(data, stat, cur_minute, std::string(""));
	}

std::string stat_func_status::getPatternValue(db_stat &st, stat_row &sd, db_userpattern &up,
		long txntime, int txn_minute, std::string &curVal) 
	{
		
		if (up.pattern_m.size() == 0)
			return "";
		//取该统计的行为习惯
		std::list<Pattern> p_l = up.pattern_m.at(st.stat_id);

		if (p_l.size() == 0)
			return "";
		std::list<Pattern>::iterator it;
		for (it = p_l.begin(); it != p_l.end();++it)
		{
			// 交易时间在行为习惯的有效期内
			if ((*it).is_enable(txntime))
			{
				return (*it).pattern_value;
			}
		}
		return "";
	}



