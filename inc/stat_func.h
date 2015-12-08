#ifndef __STAT_FUNC__H
#define __STAT_FUNC__H
#include <vector>
#include <list>
#include "stat_row.h"
#include "db_stat.h"
#include "db_userpattern.h"

class db_stat;

class stat_func
{
public:
	stat_func();
	~stat_func();
	static int max_win_count;
	static std::vector<stat_func *> g_func;
	static void get_max_win_count();
	static void init_and_sort_array();
	static int get_local_id(const std::string &name) ;
	static stat_func get_name(const std::string &name)  ;
	/*bool  compareTo( stat_func &o);*/
	virtual std::string name();
	virtual std::string type(db_stat &st);
	virtual std::string get(const std::string &data, db_stat &stat, int cur_minute,
		const  std::string &cur_value) const ;
	virtual std::string getPatternValue(const db_stat &st, stat_row &sd, db_userpattern &up, 
		long txntime, int txn_minute, const std::string &curVal) const ;
	virtual std::string set(std::string &d, db_stat &stat, int cur_minute, std::string &cur_value);
	virtual bool need_curval_when_get() const;
	virtual bool need_curval_when_set() const ;
	//string get_online(std::string &data, db_stat &stat, int cur_minute, string &cur_value);
	virtual std::string getAll(const std::string  &data, const db_stat &stat, int cur_minute) const;
	
protected:
	bool is_empty(const std::string &d);
	std::string toString(std::string &o);
};

//bool little(stat_func &s, stat_func &t);
//void sort_the_name(std::vector<stat_func *>::iterator &a, std::vector<stat_func *>::iterator &b,
//	bool(*compare)(stat_func *, stat_func *));
//bool binaryseacrch(std::vector<stat_func *>::iterator &a, std::vector<stat_func *>::iterator &b,
//	stat_func_dummy & sdm, bool(*compare)(stat_func *, stat_func *));
//std::vector<stat_func *>::iterator findit(std::vector<stat_func *>::iterator &a, std::vector<stat_func *>::iterator &b,
//	stat_func_dummy & sdm);

#endif