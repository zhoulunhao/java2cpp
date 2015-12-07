#include <string>
#include <list>
#include "stat_func_snapshot.h"
#include "db_userpattern.h"
#include <limits>
#include "op.h"
#include "db_fd.h"
#include "stat_win.h"
#include "db_stat.h"
#include "date_tool.h"

stat_func_snapshot::stat_func_snapshot(char *name)
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


stat_func_snapshot::~stat_func_snapshot()
{
	delete[] _name;
}
std::string stat_func_snapshot::name()
	{
		return std::string("SNAPSHOT");
	}

std::string stat_func_snapshot::type(db_stat &st)
	{
		db_fd fd = st.datafd();
		return fd.type;
	}


std::string stat_func_snapshot::set(std::string &d, db_stat &stat, int cur_minute, std::string cur_value)
	{
		if (d.empty())
			d = "";

		if (cur_value.empty())
			return d;

		int cur_win_time = stat.cur_win_time(cur_minute);
		stat_win_S t(cur_win_time, cur_value);
		return t.toString(0);
	}


std::string stat_func_snapshot::get(std::string &data, db_stat &stat, int cur_minute, std::string cur_value)
	{
		if (data.empty())
			return "";
		int min_win_time = stat.min_win_time(cur_minute);
		stat_win_fac<stat_win_S*> fac(data, min_win_time,
			stat_win_S::_fac);
		stat_win_S *last = fac.next_r();
		if (last == NULL)
			return "";

		std::string mm = this->type(stat);
		switch (type_map::name2type(mm))
		{
		case op::time_:
		case op::datetime_:
		case op::long_:
			return last->sV;
		case op::double_:
			return last->sV;
		case op::string_:
		default:
			return last->sV;
		}
	}

std::string stat_func_snapshot::getAll(std::string &data, db_stat &stat, int cur_minute)
	{
		return get(data, stat, cur_minute, std::string(""));
	}

bool stat_func_snapshot::need_curval_when_get() const
	{
		return false;
	}
	

bool stat_func_snapshot::need_curval_when_set() const
	{
		return true;
	}




std::string  stat_func_snapshot::getPatternValue(db_stat &st, stat_row &sd, db_userpattern &up, long txntime, int txn_minute, std::string & curVal)
	{
		
		if (up.pattern_m.size() == 0)
			return "";
		std::list<Pattern> p_l = up.pattern_m.at(st.stat_id);
		if (p_l.size() == 0)
			return "";
		std::list<Pattern>::iterator it;
		for (it = p_l.begin(); it != p_l.end(); ++it)
		{
			if ((*it).is_enable(txntime))
			{
				std::string pattern_value = (*it).pattern_value;
				//std::string mm = type(st);
		
				std::string data_type = this->type(st);
				if (strcmp("DATETIME", data_type.c_str()) == 0)
				{
					char str_time[100];
					strftime(str_time, sizeof(str_time), "%Y-%m-%d %H:%M:%S", date_tool::parse(pattern_value));
					pattern_value = std::string(str_time);
				}
				switch (type_map::name2type(data_type))
				{
				case op::time_:
				case op::datetime_:
				case op::long_:
					return pattern_value;
				case op::double_:
					return pattern_value;
				case op::string_:
				default:
					return pattern_value;
				}
			}
		}
		return "";
	}
