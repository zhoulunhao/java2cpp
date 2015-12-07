#include "stat_func_dummy.h"

#include "stat_row.h"
#include "db_userpattern.h"

stat_func_dummy::stat_func_dummy(char *name)
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

stat_func_dummy::~stat_func_dummy()
{
	delete[] _name;
}
stat_func_dummy::stat_func_dummy(const std::string &name)
{
	int len = name.size();
	_name = new char[len + 1];
	strcpy(_name, name.c_str());
}


std::string stat_func_dummy::type(db_stat &db)
{
	return "";
}

std::string stat_func_dummy::name()
{
	return this->_name;
}

//std::string set(std::string &d, db_stat stat, int cur_minute, std::string &cur_value);
std::string stat_func_dummy::set(std::string &d, db_stat &stat, int cur_minute, std::string &cur_value)
{
	return "";
}

std::string stat_func_dummy::get(std::string &data, db_stat &stat, int cur_minute, std::string &cur_value) const
{
	return "";
}


bool stat_func_dummy::need_curval_when_get() const
{
	return false;
}


bool stat_func_dummy::need_curval_when_set() const
{
	return true;
}



std::string stat_func_dummy::getAll(std::string &data, db_stat &stat, int cur_minute)
{
	return "";
}


std::string stat_func_dummy::getPatternValue(db_stat &st, stat_row &sd, db_userpattern &up,
	long txntime, int txn_minute, std::string & curVal) const 
{
	return "";
}
