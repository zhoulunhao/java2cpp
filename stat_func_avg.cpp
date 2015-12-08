#include "stat_func_avg.h"

#include <iostream>
#include "stat_win_fac.h"
#include "stat_win.h"
#include "stat_number_encode.h"
class codec;
class stat_number_encode;
template<typename T>
class stat_win_fac;

stat_func_avg::stat_func_avg(char *name)
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


stat_func_avg::~stat_func_avg()
{
	delete[] _name;
}

std::string stat_func_avg::name()
{
	return std::string("AVG");
}
std::string stat_func_avg::type(db_stat &st)
{
	return std::string("DOUBLE");
}


std::string stat_func_avg::set(std::string &d, db_stat stat, int cur_minute, std::string &cur_value)

{
	if (d.empty())
		d = "";
	if (cur_value.empty())
		return d;
	int min_win_time = stat.min_win_time(cur_minute);
	int cur_win_time = stat.cur_win_time(cur_minute);

	double value = (double)atoi(cur_value.c_str());
	stat_win_fac<stat_win_LD *> fac(d, min_win_time, stat_win_LD::_fac,stat
		.dec_win_when_set());
	stat_win_fac<stat_win_LD *>::FI fi = fac.find_r(cur_win_time);

	if (fi.flag > 0)
	{
		return fac.tostring() + stat_win_LD(cur_win_time, 1, value).toString(fac.base_time1());
	}
	else if (fi.flag == 0)
	{
		fi.e->lV++;
		fi.e->dV += (double)atoi(cur_value.c_str());

	}
	else{
		fac.insert1(fac.rindex() + 1,  new stat_win_LD(cur_win_time, 1, value));
	}
	return std::string("");
}




std::string stat_func_avg::get(std::string &data, db_stat &stat, int cur_minute, std::string cur_value) const
{
	char buf[10];
	if (data.empty())
		return "";
	int min_win_time = stat.min_win_time(cur_minute);
	stat_win_fac<stat_win_LD *> fac (data, min_win_time,
		stat_win_LD::_fac);
	int c = 0;
	double v = 0;
	stat_win_LD* w = fac.next();
	for (; w != NULL; w = fac.next())
	{
		c += w->lV;
		v += w->dV;
	}
	sprintf(buf, "%.2f", (c != 0) ? (v / c):0);
	std::string s = buf;
	return s;

}


bool stat_func_avg::need_curval_when_get() const
{
	return false;
}

bool stat_func_avg::need_curval_when_set() const
{
	return true;
}

std::string  stat_func_avg::getAll(std::string &data, db_stat &stat, int cur_minute)
{
	return this->get(data, stat, cur_minute, std::string(""));
}

std::string stat_func_avg::getPatternValue(db_stat &st, stat_row &sd, db_userpattern &up,
	long txntime, int txn_minute, std::string &curVal)
{
	
	if (&up == NULL || up.pattern_m.size() == 0)
		return std::string("");
	std::list<Pattern> p_l= up.pattern_m.at(st.stat_id);
	if (p_l.empty())
		return std::string("");
	std::list<Pattern> ::iterator it = p_l.begin();
	for (; it != p_l.end();it++)
	{
		if ((*it).is_enable(txntime))
		{
			return (*it).pattern_value;
		}
	}
	return std::string("");
}




//int main()
//{
//	std::string s = "100:20:100|2:10:100.0|3:10:200.0|";
//	stat_win_LD * a = new stat_win_LD;
//	b64::init(b64::encode64,b64::decode64);
//	b16::init(b16::encode16, b16::decode16);
//	//stat_number_encode::init_m_codec();
//	a->win_time = 12;
//	std::cout << a->dV << '\t'<< a->lV << '\t'<< a->win_time<< '\t' << a->_fac << std::endl;
//	stat_win_fac<stat_win_LD *> f(s, 0x101, a);
//	//f.insert1(0, a);
//	printf("%s^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n", f.tostring().c_str());
//	//std::cout << f.tostring() << "********************"<< std::endl;
//	//stat_win_LD *w = f.next();
////	if (w == NULL)
////	{
////		printf("w = is NULL\n");
////	}
//	for (stat_win_LD *w = NULL; NULL != (w = f.next());)
//	{
//		std::cout << w->dV  << "&&&&&&&&&&&&&&&&&&&&"<< w->lV << std::endl;
//	}
//	delete a;
//	
//	return 0;
//
//}

// 		String s = "100:20:100|2:10:100.0|3:10:200.0|";
// 		stat_win_fac<stat_win_LD> fac = new stat_win_fac<stat_win_LD>(s, -2, new stat_win_LD());

// 		for (stat_win_LD w = null; null != (w = fac.next());)
// 			System.out.println(w);

// 		System.out.println(fac.toString());
// 	}

// 	{
// 		String s = "100:20:100|2:10:100.0|3:10:200.0|";
// 		stat_win_fac<stat_win_LD> fac = new stat_win_fac<stat_win_LD>(s, 0xFF,
// 				new stat_win_LD());

// 		for (stat_win_LD w = null; null != (w = fac.next());)
// 			System.out.println(w);
// 		System.out.println(fac.toString());
// 	}
// 	{
// 		String s = "100:20:100|2:10:100.0|3:10:200.0|";
// 		stat_win_fac<stat_win_LD> fac = new stat_win_fac<stat_win_LD>(s, 0x101,
// 				new stat_win_LD());

// 		for (stat_win_LD w = null; null != (w = fac.next());)
// 			System.out.println(w);
// 		System.out.println(fac.toString());
// 	}

// 	{
// 		String s = "100:20:100|2:10:100.0|3:10:200.0|";
// 		stat_win_fac<stat_win_LD> fac = new stat_win_fac<stat_win_LD>(s, 0x103,
// 				new stat_win_LD());

// 		for (stat_win_LD w = null; null != (w = fac.next());)
// 			System.out.println(w);
// 		System.out.println(fac.toString());
// 	}

// 	{
// 		String s = "100:20:100|2:10:100.0|3:10:200.0|";
// 		stat_win_fac<stat_win_LD> fac = new stat_win_fac<stat_win_LD>(s, 0x104,
// 				new stat_win_LD());
// 		for (stat_win_LD w = null; null != (w = fac.next());)
// 			System.out.println(w);
// 		System.out.println(fac.toString());
// 	}
// }
