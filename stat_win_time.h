#ifndef __STAT_WIN_TIME__H
#define  __STAT_WIN_TIME__H



#include "date_tool.h"
#include <vector>
class win_time_base;
class fixed;
class week;
class day;
class month;
class year;
class eternal;
class txn;
class session;

#define getlocalTime()  {static char str_time[100];\
struct tm *local_time = NULL;\
time_t utc_time;\
utc_time = time(NULL);\
local_time = (tm*)localtime(&utc_time);\
strftime(str_time, sizeof(str_time), fmt.c_str(), local_time);\
return str_time; }


class stat_win_time
{
public:

	static int Base_time();
	static int dec_win_when_set(int tm_unit);
	static int cur_win_time(int tm_unit, int txn_minute);
	static int min_win_time(int tm_unit, int num_unit, int txn_minute);
	static int minute_per_win(int tm_unit);
	class win_time_base
	{
	public:
		int dec_win_when_set();

		virtual int cur_win_time(int txn_minute);
		virtual int min_win_time(int num_unitint, int txn_minute);
		virtual int num_minute();

	};
	class fixed : public win_time_base
	{
	public:
		fixed();
		int unit_minute;
		fixed(int unit_minute);
		int cur_win_time(int txnMinute);
		int min_win_time(int numUnit, int txnMinute);
		int num_minute();

	};
	class day : public win_time_base
	{
	public:
		int num_minute();
		int cur_win_time(int txnMinute);
		int min_win_time(int numUnit, int txnMintue);

	};



	class week : public win_time_base
	{
	public:

		int num_minute();
		int cur_win_time(int txnMinute);
		int min_win_time(int numUnit, int txnMinute);

	};




	class month : public win_time_base
	{
	public:

		int num_minute();
		int cur_win_time(int txnMinute);
		int min_win_time(int numUnit, int txnMinute);

	};



	class year : public win_time_base
	{
	public:

		int num_minute();
		int cur_win_time(int txnMinute);
		int min_win_time(int numUnit, int txnMinute);

	};


	class session : public win_time_base
	{
	public:

		int num_minute();
		int cur_win_time(int txnMinute);
		int min_win_time(int numUnit, int txnMinute);

	};


	class eternal : public win_time_base
	{
	public:

		int num_minute();
		int cur_win_time(int txnMinute);
		int min_win_time(int numUnit, int txnMinute);

	};



	class txn : public win_time_base
	{
	public:

		int num_minute();
		int dec_win_when_set();
		int cur_win_time(int txnMinute);
		int min_win_time(int numUnit, int txnMinute);

	};


private:
	static int the_base_time;
public:

	static std::vector<stat_win_time::win_time_base*> unit;
	static int tm_offset ;//= TimeZone.getDefault().getRawOffset() / 1000 / 60;
	static void init_unit();


};

//std::vector<win_time_base*> stat_win_time::unit;

#endif