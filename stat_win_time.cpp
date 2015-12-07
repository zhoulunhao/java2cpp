
#include "stat_win_time.h"
#include <sys/time.h>
#include <time.h>
int getbasetime()
{
	time_t ts;
	struct tm t;
	t.tm_year = 2013;
	t.tm_mon = 1;
	t.tm_mday = 1;
	t.tm_hour = 0;
	t.tm_min = 0;
	t.tm_sec = 0;
	ts = mktime(&t);
	return ts ;
}


int gettmoffset()
{
	struct timeval tv;
	 gettimeofday(&tv,NULL);
	//return tv.tv_sec;   //·µ»ØÃë
	return tv.tv_usec;    //·µ»ØÎ¢Ãë
}


std::vector<stat_win_time::win_time_base*> stat_win_time::unit;

int stat_win_time::the_base_time = getbasetime() / 1000 / 60;
int stat_win_time::tm_offset = gettmoffset() / 1000 / 60;

int stat_win_time::Base_time()
{
	return the_base_time;
}


int stat_win_time::dec_win_when_set(int tm_unit)
{
	if(tm_unit>=(int)unit.size())
		return -1;
	return unit[tm_unit]->dec_win_when_set();
}


void stat_win_time::init_unit()
{
	unit.push_back(new fixed(1));
	unit.push_back(new fixed(5));
	unit.push_back(new fixed(60));
	unit.push_back(new day());
	unit.push_back(new week());
	unit.push_back(new month());
	unit.push_back(new year());
	unit.push_back(new eternal());
	unit.push_back(new txn());
	unit.push_back(new session());
}

int stat_win_time::cur_win_time(int tm_unit,int txn_minute)
{
	if(tm_unit >=(int) unit.size())
		return -1;
	return unit[tm_unit]->cur_win_time(txn_minute)-Base_time();
}

int stat_win_time::min_win_time(int tm_unit,int num_unit,int txn_minute)
{
	if(tm_unit>=(int)unit.size())
		return -1;
	return unit[tm_unit]->min_win_time(num_unit,txn_minute)-Base_time();
}
int stat_win_time::minute_per_win(int tm_unit)
{
	return unit[tm_unit]->num_minute();
}

int stat_win_time::win_time_base::dec_win_when_set()
{
	return 0;
}
int stat_win_time::win_time_base::cur_win_time(int txn_minute)
{
	return 0;
}
int stat_win_time::win_time_base::min_win_time(int num_unitint, int txn_minute)
{
	return 0;
}
int stat_win_time::win_time_base::num_minute()
{
	return 0;
}



stat_win_time::fixed::fixed() :unit_minute(0)
{
}

stat_win_time::fixed::fixed(int unit_minute) : unit_minute(unit_minute)
{
	
}
int stat_win_time::fixed::cur_win_time(int txnMinute)
{
	return txnMinute-txnMinute%unit_minute;
}


int stat_win_time::fixed::min_win_time(int numUnit, int txnMinute)
{
	return cur_win_time(txnMinute) - numUnit * unit_minute;
}

int stat_win_time::fixed::num_minute()
{
	return unit_minute;
}


int stat_win_time::day::num_minute()
{
	return 24*60;
}

int stat_win_time::day::cur_win_time(int txnMinute)
{
	return (txnMinute + stat_win_time::tm_offset) / (24 * 60) * (24 * 60) - stat_win_time::tm_offset;
}


int stat_win_time::day::min_win_time(int numUnit, int txnMinute)
{
	return  (cur_win_time(txnMinute) - numUnit * 24 * 60);
}

int stat_win_time::week::num_minute()
{
	return 7*24*60;
}

int stat_win_time::week::cur_win_time(int txnMinute)
{
	return (txnMinute + stat_win_time::tm_offset - 4 * 24 * 60) / (7 * 24 * 60) * (7 * 24 * 60)
		- stat_win_time::tm_offset + 4 * 24 * 60;
}

int stat_win_time::week::min_win_time(int numUnit, int txnMinute)
{
	return (cur_win_time(txnMinute) - numUnit * 7 * 24 * 60);
}

int stat_win_time::month::num_minute()
{
	return 30*24*60;
}

int stat_win_time::month::cur_win_time(int txnMinute)
{	
	long long  count;
	time_t lt;
	count = txnMinute * 1000 * 60;
	lt = (time_t)count;
	struct tm *ts = localtime(&lt);
	ts->tm_year = ts->tm_year;
	ts->tm_mon = 0;
	ts->tm_mday = 1;
	ts->tm_hour = 0;
	ts->tm_min = -tm_offset;
	ts->tm_sec = 0;
	return (int)mktime(ts)/1000/60;
}


int stat_win_time::month::min_win_time(int numUnit, int txnMinute)
{
	long long  count;
	time_t lt;
	count = txnMinute * 1000 * 60;
	lt = (time_t)count;
	struct tm *ts = localtime(&lt);
	ts->tm_year = ts->tm_year;
	ts->tm_mon -= numUnit;
	ts->tm_mday = 1;
	ts->tm_hour = 0;
	ts->tm_min = -tm_offset;
	ts->tm_sec = 0;
	return (int)mktime(ts)/1000/60;
}

int	stat_win_time::year::num_minute()
{
	return 365 * 24 * 60;;
}
int stat_win_time::year::cur_win_time(int txnMinute)
{
	long long  count;
	time_t lt;
	count = txnMinute * 1000 * 60;
	lt = (time_t)count;
	struct tm *ts = localtime(&lt);
	ts->tm_year = ts->tm_year;
	ts->tm_mon = 0;
	ts->tm_mday = 1;
	ts->tm_hour = 0;
	ts->tm_min = -tm_offset;
	ts->tm_sec = 0;
	return (int)mktime(ts)/1000/60;
}
int stat_win_time::year::min_win_time(int numUnit, int txnMinute)
{
	long long  count;
	time_t lt;
	count = txnMinute * 1000 * 60;
	lt = (time_t)count;
	struct tm *ts = localtime(&lt);
	ts->tm_year = ts->tm_year-numUnit;
	ts->tm_mon = 0;
	ts->tm_mday = 1;
	ts->tm_hour = 0;
	ts->tm_min = -tm_offset;
	ts->tm_sec = 0;
	return (int)mktime(ts)/1000/60;
}

int	stat_win_time::session::num_minute()
{
	return 1;
}
int stat_win_time::session::cur_win_time(int txnMinute)
{
	return stat_win_time::Base_time();
}
int stat_win_time::session::min_win_time(int numUnit, int txnMinute)
{
	return stat_win_time::Base_time();
}


int	stat_win_time::eternal::num_minute()
{
	return 100 * 365 * 24 * 60;
}
int stat_win_time::eternal::cur_win_time(int txnMinute)
{
	return stat_win_time::Base_time();
}
int stat_win_time::eternal::min_win_time(int numUnit, int txnMinute)
{
	return stat_win_time::Base_time();
}


int	stat_win_time::txn::num_minute()
{
	return 1;
}
int stat_win_time::txn::dec_win_when_set()
{
	return 1;
}


int stat_win_time::txn::cur_win_time(int txnMinute)
{
	return stat_win_time::Base_time();
}
int stat_win_time::txn::min_win_time(int numUnit, int txnMinute)
{
	return stat_win_time::Base_time()- numUnit;
}