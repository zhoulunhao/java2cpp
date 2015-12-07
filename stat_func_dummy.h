#ifndef __STAT_FUNC__DUMMY__H
#define __STAT_FUNC__DUMMY__H

#include "stat_func.h"
#include "db_userpattern.h"

class stat_func;


class stat_func_dummy :public stat_func
{
public:
	char *_name;
	stat_func_dummy(char *name = NULL);
	~stat_func_dummy();
	stat_func_dummy(const std::string &name);
	std::string type(db_stat &st);
	std::string name();
	std::string set(std::string &d, db_stat &stat, int cur_minute, std::string &cur_value);
	std::string get(std::string &data, db_stat &stat, int cur_minute, std::string &cur_value) const;
	bool need_curval_when_get() const;
	bool need_curval_when_set() const;
	std::string getAll(std::string &data, db_stat &stat, int cur_minute);
	std::string getPatternValue(db_stat& st, stat_row &sd, db_userpattern &up, 
		long txntime, int txn_minute, std::string &curVal) const;
};
#endif
