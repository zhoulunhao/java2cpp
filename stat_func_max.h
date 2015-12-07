#ifndef __STAT_FUNC__MAX__H
#define __STAT_FUNC__MAX__H


#include "db_userpattern.h"
#include "stat_func.h"

class stat_func_max: public stat_func
{
public:
	char *_name;
	stat_func_max(char *name = NULL);
	~stat_func_max();
	std::string type(db_stat &st);
	std::string name();
	std::string set(std::string &d, db_stat &stat, int cur_minute, std::string cur_value);
	std::string get(std::string &data, db_stat &stat, int cur_minute, std::string cur_value);
	bool need_curval_when_get() const;
	bool need_curval_when_set() const;
	std::string getAll(std::string &data, db_stat &stat, int cur_minute);
	std::string getPatternValue(db_stat& st, stat_row &sd, db_userpattern &up,
		long txntime, int txn_minute, std::string &curVal);
};
#endif
