#ifndef __STAT_FUNC__BINDIST__H
#define __STAT_FUNC__BINDIST__H

#include <string>
#include "db_stat.h"
#include "stat_row.h"
#include "db_userpattern.h"
#include "stat_win.h"
#include "stat_win_fac.h"
#include "db_userpattern.h"
#include "stat_func.h"
class stat_func;
class stat_win_LS;
template<typename T>
class stat_win_fac;

class stat_func_bindist : public stat_func
{
public:
	char *_name;
	stat_func_bindist(char *name = NULL);
	~stat_func_bindist();
	std::string type(db_stat &st);
	std::string name();
	std::string set(std::string &d, db_stat &stat, int cur_minute, std::string &cur_value);
	std::string min_len_string(stat_win_fac<stat_win_LS *> &fac);
	std::string get(std::string &data, db_stat &stat, int cur_minute, std::string &cur_value);
	bool need_curval_when_get() const;
	bool need_curval_when_set() const;


	std::map<std::string, std::string> getAll(std::string &data, db_stat &stat, int cur_minute);
	std::string getPatternValue(db_stat &st, stat_row &sd, db_userpattern &up, long txntime, 
		int txn_minute, std::string &curVal);

};
#endif

