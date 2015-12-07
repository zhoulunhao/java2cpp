#include <string>
#include <list>
#include "stat_func_nmdist.h"
#include <limits>
#include "db_userpattern.h"


stat_func_nmdist::stat_func_nmdist(char *name)
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


stat_func_nmdist::~stat_func_nmdist()
{
	delete[] _name;
}
std::string stat_func_nmdist::type(db_stat &st)
	{
		return std::string("DOUBLE");
	}

std::string stat_func_nmdist::name()
	{
		return std::string("NM_DIST");
	}

std::string stat_func_nmdist::set(std::string &d, db_stat &stat, int cur_minute, std::string& cur_value)
	{
		return "";
	}

std::string stat_func_nmdist::get(std::string &data, db_stat &stat, int cur_minute, std::string &cur_value)
	{
		return "";
	}

bool stat_func_nmdist::need_curval_when_get() const
	{
		return true;
	}

bool stat_func_nmdist::need_curval_when_set() const
	{
		return true;
	}


std::string stat_func_nmdist::getAll(std::string &data, db_stat &stat, int cur_minute) {
		// TODO Auto-generated method stub
		return "";
	}




std::string stat_func_nmdist::getPatternValue(db_stat &st, stat_row &sd, db_userpattern &up,
		long txntime, int txn_minute, std::string  &curVal) {
		// TODO Auto-generated method stub&
		return "";
	}
