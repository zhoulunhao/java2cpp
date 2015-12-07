#ifndef __STAT_ROW__H
#define  __STAT_ROW__H
#include <string>


class stat_row
{
public:
	const static int QUERY = 1;
	const static int CLEAR = 2;

	int m_row_type;
	int m_stat_id;
	std::string m_param;
	std::string m_txn_val;
	long m_txn_time;
	//stat_value *m_stat_value;
	//counter *m_query_batch;
	const static char item_sp = '\t';
private:
	std::string m_value;
public:
	stat_row();
	~stat_row();
	
	stat_row(int statId, std::string &mParam, int row_type,  std::string &txn_value,long txnTime=0);
	bool is_query();
	bool is_clear();
	std::string toString();
	std::string get_value();
	void set_value(std::string v);
	int dec_query_batch();
	//void set_stat_value(stat_value &sr);
	//stat_value& get_stat_value();
	//stat_value & get_stat_value(bool newifnull);
	//void do_stat_lob(db_stat_cache &dc);
	void to_net_request(std::string &sb);
	//static stat_row from_net_request(std::string &line, counter &c);
	int read_stat_type(std::string &line, int from);
	int read_stat_id(std::string &line, int from);
	int read_stat_param(std::string &line, int from);
	int read_stat_value(std::string &line, int from);
	int read_txn_value(std::string &line, int from);
	int read_stat_txn_time(std::string &line, int from);
	//void set_query_counter(counter &queryCounter);
	void set_error();


};

#endif