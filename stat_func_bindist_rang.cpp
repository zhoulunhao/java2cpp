#include <string>
#include <stdio.h>
#include "stat_func.h"
#include "stat_func_bindist_rang.h"
#include "db_userpattern.h"
#include "stat_func_bindist.h"


class stat_func_bindist;


stat_func_bindist_rang::stat_func_bindist_rang(char *name)
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


stat_func_bindist_rang::~stat_func_bindist_rang()
{
	delete[] _name;
}
std::string stat_func_bindist_rang::type(db_stat &st)
	{
		return std::string("DOUBLE");
	}
std::string stat_func_bindist_rang::name()
	{
		return std::string("RANGE_BIN_DIST");
	}
std::string stat_func_bindist_rang::set(std::string &d, db_stat &stat, int cur_minute, std::string &cur_value)
{

	if (cur_value.empty())
		return d;
	int index = stat.range_index(atoi(cur_value.c_str()));
	if (index < 0)
		return d;
	char buf[10];
	sprintf(buf,"%.2f", (double)index);
	std::string mm = buf;
	stat_func_bindist r;
	return r.set(d, stat, cur_minute, mm);
}//set())
std::string stat_func_bindist_rang::get(std::string &data, db_stat &stat, int cur_minute, std::string &cur_value)
{

	char buf[10];
	if (data.empty() || cur_value.empty())
		return std::string("0");
	int index = stat.range_index(atoi(cur_value.c_str()));
	if (index < 0)
		return std::string("0");
	sprintf(buf, "%.2f", (double)index);
	std::string mm = buf;
	return stat_func_bindist().get(data,stat,cur_minute,mm);
}
bool stat_func_bindist_rang::need_curval_when_get() const
	{
		return true;
	}
bool stat_func_bindist_rang::need_curval_when_set() const
	{
		return true;
	}
std::map<std::string, std::string> getAll(std::string &data, db_stat &stat, int cur_minute)
{

	return stat_func_bindist().getAll(data, stat, cur_minute);


}
std::string stat_func_bindist_rang::getPatternValue(db_stat& st, stat_row &sd, db_userpattern &up, long txntime, int txn_minute, std::string &curVal)
	{
		std::list<Pattern> p_l = up.pattern_m.at(st.stat_id);
		if(p_l.size() == 0)
			return "";
		std::list<Pattern>::iterator it = p_l.begin();
		for (; it != p_l.end(); ++it)
		{
			if ((*it).is_enable(txntime))
			{
				if (curVal.empty())
					continue;
				int index = st.range_index(atoi(curVal.c_str()));
				if (atoi((*it).pattern_value.c_str()) == index)
				{
					return std::string("1");
				}
			}
		}
		return 0;
	}

