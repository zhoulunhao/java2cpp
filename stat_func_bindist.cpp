
#include "stat_func_bindist.h"
#include "stat_win.h"
#include "stat_win_fac.h"
#include "stat_func.h"
#include "stat_win_time.h"
#include <set>


stat_func_bindist::stat_func_bindist(char *name)
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


stat_func_bindist::~stat_func_bindist()
{
	delete[] _name;
}

std::string stat_func_bindist::type(db_stat &st)
{
	return std::string("DOUBLE");
}

std::string stat_func_bindist::name()
{
	return std::string("BIN_DIST");
}

std::string stat_func_bindist::set(std::string &d, db_stat &stat, int cur_minute, std::string &cur_value)
{
	if (d.empty())
		d = "";
	if (cur_value.empty())
	{
		return d;
	}

	int min_win_time = stat.min_win_time(cur_minute);
	int cur_win_time = stat.cur_win_time(cur_minute);
	std::string value = cur_value;
	if(stat_win_LS::_fac == NULL)
		printf("LS::_fac = NULL\n");
	stat_win_fac<stat_win_LS *> fac(d, min_win_time, stat_win_LS::_fac,stat.dec_win_when_set());


	stat_win_fac<stat_win_LS *>::FI fi = fac.find_r(cur_win_time);
	if (fi.flag == 0)
	{
		return fac.tostring() + stat_win_LS(cur_win_time, 1, value).toString(fac.base_time1());
	}
	else if (fi.flag == 0)
	{
		stat_win_LS * e = fi.e;
		int rindex = fac.rindex();
		for (; e!=NULL; e = fac.next_r())
		{
			if (e->sV == value)
			{
				e->lV++;
				return fac.tostring();
			}
		}
		fac.insert1(rindex + 1, new stat_win_LS(cur_win_time, 1, value));
	}
	else
	{
		fac.insert1(fac.index1() +1, new stat_win_LS(cur_win_time, 1, value));
	}
	return min_len_string(fac);
}

std::string stat_func_bindist::min_len_string(stat_win_fac<stat_win_LS *> &fac)
{
	int max_count = stat_func::max_win_count;
	fac.reset_rindex();

	std::set<std::string> set1;
	stat_win_LS *i = NULL;
	for ( i = fac.next_r();i != NULL; i = fac.next_r())
	{
		set1.insert(i->sV);
		if ((int)set1.size() >= max_count)
			break;
	}

	fac.del_before(fac.rindex());
	return  fac.tostring();

}
std::string  stat_func_bindist::get(std::string &data, db_stat &stat, int cur_minute, std::string &cur_value)
{
	char buf[100];
	std::string value = "";
	sprintf(buf, "%.2f",(double)0);
	if (data.empty() || cur_value.empty())
		return buf;
	int min_win_time = stat.min_win_time(cur_minute);
	long c = 0;
	long vc = 0;
	stat_win_fac<stat_win_LS *> fac(data, min_win_time,
		stat_win_LS::_fac);
	stat_win_LS *w = fac.next();
	while (w->win_time!=0)
	{
		w = fac.next();
		c += w->lV;
		if (w->sV==(value))
			vc += w->lV;
	}

	if (c == 0)
		return buf;
	sprintf(buf, "%.2f", 1.0*vc / c);
	return buf;
}
bool stat_func_bindist::need_curval_when_get() const
{
	return true;
}
bool stat_func_bindist::need_curval_when_set()  const 
{
	return true;
}


std::map<std::string, std::string>  stat_func_bindist::getAll(std::string &data, db_stat &stat, int cur_minute)
{
	std::map<std::string, std::string> a;
	char buf[100];
	if (data.empty())
		return a;
	int min_win_time = stat.min_win_time(cur_minute);
	stat_win_fac<stat_win_LS *> fac (data, min_win_time,
		stat_win_LS::_fac);
	std::map<std::string, std::string> o;
	stat_win_LS *w = NULL;
	for (w = fac.next(); w != NULL; w = fac.next())
	{
		if (o.find(w->sV) != o.end()){
			sprintf(buf, "%.2f", (double)w->lV);
			std::string s = buf;
			o.insert(std::pair<std::string, std::string>(w->sV, s));
		}
		else
		{
			sprintf(buf, "%.2f",(double) w->lV);
			std::string s = buf;
			o.insert(std::pair<std::string, std::string>(w->sV, w->sV + s));
		}
	}
	return o;
}
std::string stat_func_bindist::getPatternValue(db_stat &st, stat_row &sd, db_userpattern &up, long txntime, int txn_minute, std::string &curVal)
{
	if (up.pattern_m.size() == 0)
		return "";
	std::list<Pattern> p_l = up.pattern_m.at(st.stat_id);
	if (p_l.size() == 0)
		return "";
	std::list<Pattern>::iterator it = p_l.begin();
	for (; it != p_l.end(); it++)
	{
		if ((*it).is_enable(txntime))
			return std::string("1");
	}
	return "";
}





int main()
{
	db_stat st;
	st.stat_unit_min = 4;
	stat_func_bindist *at = new stat_func_bindist;
	b64::init(b64::encode64,b64::decode64);
	b16::init(b16::encode16, b16::decode16);
		//stat_number_encode::init_m_codec();
	std::cout << at->name() << std::endl;
	std::cout << at->type(st) << std::endl;
	std::string d = "4400:1444320:5:2|7878:2788788:4:1|";
	//stat_win_LD * a = new stat_win_LD;
	//stat_win_fac<stat_win_LD *> f(d, 0x101, a);
	//f.win_items->push_back(a);
	int cur_minute = 32444444;
	stat_win_time::init_unit();
	printf("unit.size() = %d\n",(int)stat_win_time::unit.size());
	std::string cur_value = "4367432";
		
	
	std::string s = at->set(d, st, cur_minute, cur_value);
	std::cout << s << std::endl;

	s = at->get(d, st,cur_minute, cur_value);
	std::cout << d << std::endl;
	
	delete at;
	return 0;
}
