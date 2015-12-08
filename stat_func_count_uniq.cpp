

#include <list>

#include <string>
#include <set>
#include "stat_win.h"
#include "stat_win_fac.h"
#include "db_userpattern.h"

#include "stat_func_count_uniq.h"



stat_func_count_uniq::stat_func_count_uniq(char *name)
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


stat_func_count_uniq::~stat_func_count_uniq()
{
	delete[] _name;
}

	std::string stat_func_count_uniq::type(db_stat &st)
	{
		return std::string("INT");
	}

	std::string stat_func_count_uniq::name()
	{
		return std::string("COUNT_UNIQ");
	}

	std::string stat_func_count_uniq::set(std::string &d, db_stat &stat, int cur_minute, std::string cur_value)
	{
		int min_win_time = stat.min_win_time(cur_minute);
		int cur_win_time = stat.cur_win_time(cur_minute);
		std::string value = cur_value;
		stat_win_fac<stat_win_S*> fac(d, min_win_time, stat_win_S::_fac, stat
			.dec_win_when_set() );
		stat_win_fac<stat_win_S*>::FI fi = fac.find_r(cur_win_time);
		if (fi.flag > 0)
		{
			fac.insert1(fac.size(), new stat_win_S(cur_win_time,value));
		}
		else if (fi.flag==0)
		{
			stat_win_S *e = fi.e;
			int rindex = fac.rindex();
			for (; e!=NULL; e = fac.next_r())
			{
				if (e->sV == value)
					return fac.tostring();
			}
			fac.insert1(rindex + 2, new stat_win_S(cur_win_time,value));

		}
		else
		{
			fac.insert1(fac.rindex() + 1,new  stat_win_S(cur_win_time, value));

		}
		return min_len_string(fac);


	}

	std::string stat_func_count_uniq::min_len_string(stat_win_fac<stat_win_S*>& fac)
	{
		int max_count = stat_func::max_win_count;
		fac.reset_rindex();

		std::set<std::string> set1;
		//std::set<std::string>::iterator it;
		//it = set1.begin();
		stat_win_S* i;
		for (i = fac.next_r(); i != NULL; i = fac.next_r())
		{
			set1.insert(i->sV);
			if ((int)set1.size() >= max_count)
				break;
		}
		fac.del_before(fac.rindex());
		return fac.tostring();
	}

	std::string stat_func_count_uniq::get(std::string &data, db_stat &stat, int cur_minute, std::string cur_value)
	{
		char buf[100];
		if (data.empty())
			return "0";
		int min_win_time = stat.min_win_time(cur_minute);

		stat_win_fac<stat_win_S*> fac(data, min_win_time,
			stat_win_S::_fac);
		std::set<std::string> set1;
		
		
		stat_win_S *i;
		for (i = fac.next() ; i != NULL; i = fac.next())
		{
			set1.insert(i->sV);
		}
		sprintf(buf, "%.2f",(double)set1.size());
		return buf;
	}

	bool stat_func_count_uniq::need_curval_when_get() const
	{
		return false;
	}
	bool stat_func_count_uniq::need_curval_when_set() const
	{
		return true;
	}

	std::string stat_func_count_uniq::getAll(std::string &data, db_stat &stat, int cur_minute)
	{
		char buf[100];
		if (data.empty())
			return "";
		int min_win_time = stat.min_win_time(cur_minute);
		stat_win_fac<stat_win_S*> fac(data, min_win_time,
			stat_win_S::_fac);
		std::set<std::string> set1;
		stat_win_S *i = fac.next();
		for (; i != NULL ; i = fac.next())
		{
			set1.insert(i->sV);
		}
		sprintf(buf, "%.2f", (double)set1.size());
		return buf;
	}

	std::string stat_func_count_uniq::getPatternValue(db_stat &st, stat_row &sd, db_userpattern &up,
		long txntime, int txn_minute, std::string &curVal)
	{
		
		if (up.pattern_m.size() == 0)
			return "";
		std::list<Pattern> p_l = up.pattern_m.at(st.stat_id);
		if (p_l.size() == 0)
			return "";
		std::list<Pattern> ::iterator it;
		for (it = p_l.begin(); it != p_l.end(); ++it)
		{
			if ((*it).is_enable(txntime))
			{
				return (*it).pattern_value;
			}
		}
		return std::string("");
	}
	


