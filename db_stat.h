
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
	int stat_id; // ͳ���������Զ�����
	std::string stat_name; // ͳ�����ƣ�����S1
	std::string stat_desc; // ͳ�Ƶĺ�������
	std::string stat_txn; // ����ͳ�����ڵĽ���
	//std::string stat_param_fd; // ͳ�������ֶΣ�ʹ�ô˱���ʱ����Ҫ����Ķ���ֵ
	std::string stat_fd_name; // ��ͳ���ֶ���
	//std::string stat_func_name; // "ͳ�ƺ���"
	//std::string stat_cond; // ͳ�����������Ϊ�գ���Ϊ������ͳ��
	//int stat_cond_result; // ���׽��������0������ʱ���㣬1�ɹ�ʱ���㣬2ʧ��ʱ���㣬3ȫ������
	//int stat_online; // �Ƿ����м���
	int stat_unit_min; // ����
	int stat_num_unit; // ��¼������
	//int is_continues; // �Ƿ�������������ʱ���������ɹ������
	//int is_valid; // �Ƿ���Ч
	//int is_operational; // �Ƿ�ֻ���������㣬������
	//std::string storecolumn; // �洢��������ˮ���е��ֶ�
	//std::string datatype; // ͳ�Ƶ���������
	//std::string fn_param;
	db_fd stat_data_fd;
	//int *param_fd_index; // ͳ�������õĽ������ֶε�����
	//int stat_fd_index;
	//stat_func func_st; // ͳ�ƺ���
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