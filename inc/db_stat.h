
#ifndef __DB__STAT__H
#define __DB__STAT__H

#include <vector>
#include <string>
#include <list>
#include "db_fd.h"
class db_fd;

class range_m;

class db_stat
{

public:
	db_stat();
	~db_stat();
	int stat_id; // 统计主键，自动递增
	std::string stat_name; // 统计名称，例如S1
	std::string stat_desc; // 统计的汉字描述
	std::string stat_txn; // 定义统计所在的交易
	//std::string stat_param_fd; // 统计引用字段，使用此变量时，需要传入的对象值
	std::string stat_fd_name; // 被统计字段名
	//std::string stat_func_name; // "统计函数"
	//std::string stat_cond; // 统计条件，如果为空，则为无条件统计
	//int stat_cond_result; // 交易结果条件，0处理中时计算，1成功时计算，2失败时计算，3全部计算
	//int stat_online; // 是否事中计算
	int stat_unit_min; // 周期
	int stat_num_unit; // 记录周期数
	//int is_continues; // 是否连续，有条件时，条件不成功则清空
	//int is_valid; // 是否有效
	//int is_operational; // 是否只是用于运算，不保存
	//std::string storecolumn; // 存储到交易流水表中的字段
	//std::string datatype; // 统计的数据类型
	//std::string fn_param;
	db_fd stat_data_fd;
	//int *param_fd_index; // 统计所引用的交易内字段的索引
	//int stat_fd_index;
	//stat_func func_st; // 统计函数
	std::list<range_m> range1;
	
	int index;
	bool comp_by_statid(db_stat &o1, db_stat &o2);
	bool comp_by_txnid_statname(db_stat &o1, db_stat &o2);
	bool comp_by_txnid_statid(db_stat &o1, db_stat &o2);
	int get_index();

	int dec_win_when_set();
	int min_win_time(int cur_minute);
	
	db_fd datafd();
	int cur_win_time(int cur_minute);
	int range_index(long curValue);
//	void post_init(db_tab tab, db_fd_cache dfc);
	std::string toString();
//void post_init(db_tab tab, db_fd_cache dfc);
	std::string type();
	bool is_user_pattern(int fd_user_index);
};




//class db_stat_cache
//{
//public:
//	std::list<db_stat> list_;
//	std::list<db_stat> list_txn_name;
//	std::list<std::list<db_stat>> g_list_txn;
//	//db_tab_cache g_dtc;
//	//db_fd_cache g_dfc;
//
//	db_stat get(int index);
//	int get_index(int stat_id);
//	db_stat get_by_statid(int stat_id);
//
//	db_stat get(std::string txn, std::string name);
//	std::list<db_stat> get_txn_stats(std::string txn);
//
//	std::list<db_fd> get_txn_storefd(db_tab &tab);
//	std::list<db_stat> get_txn_stats(int txn);
//
////	static db_stat_cache load(data_source ds, db_tab_cache dtc, db_fd_cache dfc);
//
//	void init(data_source ds);
//	void init_txn();
//
//	std::list<db_stat> sub(std::string txn);
//	int range_index(std::string curValue);
//	
//	std::list<db_stat> all();
//	
//private :
//	//std::list<db_stat> get_txn_stats(db_tab tab);
//
//public:
//	static db_stat mk_this(int id, std::string txn, std::string name);
//	std::string std::string();
//	//db_fd datafd();
//	int get_index();
//	int dec_win_when_set();
//	int min_win_time(int cur_minute);
//	int cur_win_time(int cur_minute);
//	std::string type();
//	bool is_user_pattern(int fd_user_index);
//};

class range_m
{
public:
	range_m();
	range_m(double d,double e);
	bool include(double n);
	double min;
	double max;
};

//class tm_range : public range_m
//{
//public:
//	static std::string h24;
//	static std::string h00;
//	tm_range(std::string &d, std::string &e);
//	bool include(std::string &n);
//	std::string toString();
//};




#endif