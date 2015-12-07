

#include <list>
#include <string>
#include "stat_win_fac.h"
#include "stat_func_count_equals.h"
#include "stat_func_bindist.h"



//class stat_func_count_equals : stat_func
//{
//public:
//	string type(db_stat &st);
//	string name();
//	string set(string &d, db_stat &stat, int cur_minute, string &cur_value);
//	string get(string &data, db_stat &stat, int cur_minute, string &cur_value);
//	bool need_curval_when_get();
//	bool need_curval_when_set();
//	string getAll(string &data, db_stat &stat, int cur_minute);
//	string getPatternValue(db_stat& st, stat_row &sd, db_userpattern &up, long txntime, int txn_minute, string &curVal);
//};
stat_func_count_equals::stat_func_count_equals(char *name)
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


stat_func_count_equals::~stat_func_count_equals()
{
	delete[] _name;
}

std::string stat_func_count_equals::name()
{
	return std::string("COUNT_EQUALS");
}
std::string stat_func_count_equals::type(db_stat &st)
{
	return std::string("INT");
}




std::string  stat_func_count_equals::get(std::string &data, db_stat &stat, int cur_minute, std::string &cur_value)
	{
		char buf[10];
		std::string value = "";
		if (data.empty() || cur_value.empty())
			return 0;
		int min_win_time = stat.min_win_time(cur_minute);
		long vc = 0;
		stat_win_fac<stat_win_LS *> fac(data, min_win_time,
			stat_win_LS::_fac);
		stat_win_LS *w = fac.next();
		for (; w != NULL; w = fac.next())
		{
			if (w->sV == cur_value)
			{
				vc += w->lV;
			}
			
		}
		sprintf(buf, "%.2f", (double)vc);
		return buf;
	}
	


std::map<std::string, std::string> stat_func_count_equals::getAll(std::string &data, db_stat &stat, int cur_minute)
	{
		char buf[10];
		std::map<std::string, std::string> a;
		if (data.empty())
			return a;
		int min_win_time = stat.min_win_time(cur_minute);
		stat_win_fac<stat_win_LS*> fac(data, min_win_time,
			stat_win_LS::_fac);
		stat_win_LS *w = fac.next();
		for (; w != NULL;w= fac.next())
		{
			sprintf(buf, "%.2f", (double)w->lV);
			if (a[w->sV].c_str()!=NULL)
			{
				
				a.insert(std::pair<std::string, std::string>(w->sV, buf));
			}
			else
			{
				a.insert(std::pair<std::string, std::string>(w->sV, w->sV + buf));
			}
		}
		return a;
	}


std::string stat_func_count_equals::getPatternValue(db_stat &st, stat_row &sd, db_userpattern &up, long txntime, int txn_minute, std::string & curVal)
	{
		
		std::list<Pattern> p_l = up.pattern_m.at(st.stat_id);
		if (p_l.empty())
			return 0;
		std::list<Pattern>::iterator it;
		it = p_l.begin();
		for (; it != p_l.end(); ++it)
		{
			if ((*it).is_enable(txntime))
			{
				return (*it).pattern_value;
			}
		}
		return "";
	}
