#include "db_stat.h"
#include "stat_win_time.h"
#include "db_fd.h"
#include <stdio.h>
class range;
db_stat::db_stat()
{
	index = 0;
	stat_id = 0;
	stat_name = "";
	stat_desc = "";
	stat_txn = "";
	//this->stat_param_fd = "";
	stat_fd_name = "";
	//stat_func_name = "";
	//stat_cond = "";
	//stat_cond_result = 0;
	//stat_online = 0;
	stat_unit_min = 0;
	stat_num_unit = 0;
	//is_continues = 0;
	//is_valid = 0;
	//is_operational = 0;
	//storecolumn = "";
	//datatype = "";
	//fn_param = "";
	/*param_fd_index = NULL;
	stat_fd_index = 0;*/
	stat_data_fd = db_fd();
}
db_stat::~db_stat()
{

}
	
int db_stat::get_index()
{
	return this->index;
}

int db_stat::dec_win_when_set()
{
	return stat_win_time::dec_win_when_set(this->stat_unit_min);
}
int db_stat::min_win_time(int cur_minute)
{
	return stat_win_time::min_win_time(this->stat_unit_min, stat_num_unit - 1, cur_minute);
}

int db_stat::cur_win_time(int cur_minute)
{
	return stat_win_time::cur_win_time(this->stat_unit_min, cur_minute);
}


bool db_stat::comp_by_statid(db_stat &o1, db_stat &o2)
{
	if (o1.stat_id == o2.stat_id)
		return true;
	else
		return false;
}
bool db_stat::comp_by_txnid_statname(db_stat &o1, db_stat &o2)
{
	bool c = o1.stat_txn.compare(o2.stat_txn);
	if (c)
	{
		return c;
	}
	return o1.stat_name.compare(o2.stat_name);
}


bool db_stat::comp_by_txnid_statid(db_stat &o1, db_stat &o2)
{
	bool c = o1.stat_txn.compare(o2.stat_txn);
	if (c)
		return c;
	return comp_by_statid(o1, o2);
}

// std::string db_stat::type()
// {
// 	return this->func_st.type();
// }





std::string db_stat::toString()
{
	static char buf[124];
	sprintf(buf, "%d", stat_id);
	std::string s = buf;
	return "[" + stat_txn + "," + s + "," + stat_name + "," + stat_desc + "]";
}
//void db_stat::post_init(db_tab tab, db_fd_cache dfc)
//{
//
//}


bool db_stat::is_user_pattern(int fd_user_index)
{
	return false;
}


 int db_stat::range_index(long curValue)
{
	if (curValue == 0)
		return -1;
	std::list<range_m>::iterator it = range1.begin();
	//int len = range1.size();
	int i = 0;
	for (; it != range1.end();it++, i++)
	{
		range_m r = (*it);
		if (r.include(curValue))
			return i;
	}

	return -1;
}

 db_fd db_stat::datafd()
 {
	 if (stat_fd_name.empty())
		 return db_fd();
	 return this->stat_data_fd;
 }



 range_m::range_m()
 {
	 min = 0;
	 max = 0;
 }
 range_m::range_m(double d, double e) :min(d), max(e)
 {
	 
 }
 bool range_m::include(double n)
 {
	 if (n == 0.00000)
		 return false;
	 return min <= n && n < max;
 }


 //std::string tm_range::h24 = ;
 //std::string tm_range::h00;
 //tm_range::tm_range(std::string &d, std::string &e)
 //{

 //}
 //bool tm_range::include(std::string &n)
 //{

 //}
 //std::string tm_range::toString()
 //{

 //}