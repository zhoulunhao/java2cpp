#include "stat_func.h"
#include "tmsapp.h"
#include "stat_func_avg.h"
#include <algorithm>
#include "stat_func_bindist.h"
#include "stat_func_bindist_rang.h"
#include "stat_func_count.h"
#include "stat_func_count_equals.h"
#include "stat_func_count_uniq.h"
#include "stat_func_dummy.h"
#include "stat_func_max.h"
#include "stat_func_min.h"
#include "stat_func_nmdist.h"
#include "stat_func_snapshot.h"
#include "stat_func_sum.h"
#include "stat_func_status.h"

std::vector<stat_func *> stat_func::g_func;
int stat_func::max_win_count = 15;

stat_func::stat_func() 
{
	
}

stat_func::~stat_func()
{
	
}


void stat_func::get_max_win_count()
{
	max_win_count = tmsapp::get_config("tms.stat.maxwincount", 15);
}


std::string toLowercase(std::string &s)
{
	for (int i = 0; i < (int)s.size(); i++)
		s[i] = tolower(s[i]);
	return s;
}


//bool compareTo(stat_func &o,stat_func &p)
//{
//	std::string ms = toLowercase(p.name());
//	std::string mt = toLowercase(o.name());
//	return ms < mt;
//}


//void sort_the_name(std::vector<stat_func *>::iterator &a, std::vector<stat_func *>::iterator &b,
//	bool (*compare_name)(stat_func &,stat_func &))
//{
//	std::vector<std::string> vec;
//	std::vector<std::string>::iterator it = vec.begin();
//	for (; a != b; a++)
//	{
//		vec.push_back((*a)->name());
//	}
//	std::sort(it, vec.end(), compare_name);
//}


class comp
{
	public:
		bool operator()( stat_func *a, stat_func *b)
		{
			return a->name() < b-> name();
		}
};

void stat_func::init_and_sort_array()
{
	g_func.push_back(new stat_func_avg());
	g_func.push_back(new stat_func_bindist_rang());
	g_func.push_back(new stat_func_bindist());
	g_func.push_back(new stat_func_count_uniq());
	g_func.push_back(new stat_func_count());
	g_func.push_back(new stat_func_count_equals());
	g_func.push_back(new stat_func_max());
	g_func.push_back(new stat_func_min());
	g_func.push_back(new stat_func_nmdist());
	g_func.push_back(new stat_func_sum());
	g_func.push_back(new stat_func_status());
	g_func.push_back(new stat_func_snapshot());
	std::sort(g_func.begin(), g_func.end(),comp());
}


bool binarysearch(std::vector<stat_func *>::iterator a, std::vector<stat_func *>::iterator b, 
	stat_func_dummy  &sdm)
{
	while (a != b)
	{
		std::vector<stat_func *>::iterator mid = a + (b - a) / 2;
		if (sdm.name().compare((*mid)->name()) == 0)
			return true;
		else if (sdm.name().compare((*mid)->name()) > 0)
		{
			b = mid - 1;
		}
		else
			a = mid + 1;
	}
	return false;
}

const std::vector<stat_func *>::iterator findit( std::vector<stat_func *>::iterator a, std::vector<stat_func *>::iterator b,
	stat_func_dummy  &sdm)
{
	for (; a != b; a++)
	{
		if ((*a)->name() == sdm.name())
			break;
	}
	return a;
}





int stat_func::get_local_id(const std::string &name)
{
	std::vector<stat_func *>::iterator it;
	stat_func_dummy sdm(name);
	bool c = binarysearch(g_func.begin(), g_func.end(), sdm);
	if (c)
	{
		it = findit(g_func.begin(), g_func.end(), sdm);
	}
	return it - g_func.begin();
}
stat_func stat_func::get_name(const std::string &name)
{
	if (name.empty())
		return stat_func();
	int index = get_local_id(name);
	if (index < 0)
		return stat_func();
	return *g_func[index];	
}


//
//string get_online(string &data, db_stat &stat, int cur_minute, string &cur_value)
//{
//	string tmp = set(data, stat, cur_minute, cur_value);
//	string s = get(tmp, stat, cur_minute, cur_value);
//	return s;
//}

bool stat_func::is_empty(const std::string &d)
{
	return d.empty() || d.length() == 0;
}
std::string stat_func::toString(std::string &o)
{
	return o;
}


std::string stat_func::name()
{
	return "";
}
std::string stat_func::type(db_stat &st)
{
	return "";
}
std::string stat_func::get(const std::string &data, db_stat &stat, int cur_minute,
	const  std::string &cur_value) const
{
	return "";
}
std::string stat_func::getPatternValue(const db_stat &st, stat_row &sd, db_userpattern &up,
	long txntime, int txn_minute, const std::string &curVal) const
{
	return "";
}
std::string stat_func::set(std::string &d, db_stat &stat, int cur_minute, std::string &cur_value)
{
	return "";
}
bool stat_func::need_curval_when_get() const
{
	return false;
}
bool stat_func::need_curval_when_set() const
{
	return false;
}
std::string stat_func::getAll(const std::string  &data, const db_stat &stat, int cur_minute) const
{
	return "";
}
