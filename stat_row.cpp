#include "stat_row.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "stat_number_encode.h"

stat_row::stat_row()
{
	m_param = "";
	m_value = "";
	m_txn_val = "";
	m_row_type = 0;
	m_stat_id = 0;
	m_txn_time = 0;
	//m_stat_value = NULL;
	//m_query_batch = NULL;

}

stat_row::~stat_row()
{

}



stat_row::stat_row(int statId, std::string &mParam, int row_type, std::string &txn_value, long txnTime)
{
	m_stat_id = statId;
	m_param = mParam;
	m_txn_time = txnTime;
	m_txn_val = txn_value;
	m_row_type = row_type;
}


bool stat_row::is_query()
{
	return 0 != (m_row_type & QUERY);
}
bool stat_row::is_clear()
{
	return 0 != (m_row_type & CLEAR);
}
std::string stat_row::toString()
{
	char buf[100];
	sprintf(buf, "%.2f",(double) m_stat_id);
	return "[" + m_param + buf + "|" + ":" + m_value + "]";
}
std::string stat_row::get_value()
{
	return m_value;
}
void stat_row::set_value(std::string v)
{
	m_value = v;
}
//int stat_row::dec_query_batch()
//{
//	int ret = 1;
//	if (this->m_query_batch != NULL)
//	{
//		ret = m_query_batch->dec();
//		m_query_batch = NULL;
//	}
//	return ret;
//}
//void stat_row::set_stat_value(stat_value &sr)
//{
//	*m_stat_value = sr;
//}
//stat_value& stat_row::get_stat_value()
//{
//	return get_stat_value(true);
//}


//stat_value & stat_row::get_stat_value(bool newifnull)
//{
//	if (m_stat_value == NULL && newifnull)
//	{
//		return *m_stat_value = *(new stat_value(m_param));
//	}
//	return *m_stat_value;
//}


//void stat_row::do_stat_lob(db_stat_cache &dc)
//{
//	if (is_query())
//	{
//
//	}
//	else if (is_clear())
//	{
//		m_stat_value->del(m_stat_id);
//	}
//	else
//	{
//		std::string v = m_stat_value->get(m_stat_id);
//		db_stat m_stat = dc.get_by_statid(m_stat_id);
//		v = m_stat.func_st->set(v, m_stat, (int)(m_txn_time / 1000 / 60), m_txn_val);
//		m_stat_value->set(m_stat.stat_id, v);
//	}
//}
void stat_row::to_net_request(std::string &sb)
{

	
	sb.append(stat_number_encode::encode(m_row_type)).append("\t");
	sb.append(m_param).append("\t");
	sb.append(stat_number_encode::encode(m_stat_id));
	if (is_query() || is_clear())
		sb.append("\n");
	else
	{
		sb.append("\t");
		sb.append(stat_number_encode::encode(m_txn_time)).append("\t");
		if (m_txn_val.empty())
			sb.append("");
		else
			sb.append("'").append(m_txn_val).append("'");
		sb.append("\n");
	}

}


//stat_row stat_row::from_net_request(std::string &line, counter &c)
//{
//	stat_row row;
//	int from = row.read_stat_type(line, 0);
//	from = row.read_stat_param(line, from);
//	from = row.read_stat_id(line, from);
//	if (row.is_query())
//	{
//		*row.m_query_batch = c;
//		c.inc();
//	}
//
//	else if (!row.is_clear())
//	{
//		from = row.read_stat_txn_time(line, from);
//		from = row.read_txn_value(line, from);
//	}
//	return row;
//}
int indexof(std::string &cc, int p, char ch)
{
	int count = 0;
	const char *s = cc.c_str() + p;
	while (*s++ != '\0')
	{
		count++;
		if (*s == ch)
			return p + count;
	}
	return 100;
}


int stat_row::read_stat_type(std::string &line, int from)
{
	int p = indexof(line,from ,item_sp);
	if (p <= from)
		std::cout << "分析统计元素'stat_row_type'出错" << std::endl;
	m_row_type = stat_number_encode::decode_int(line.substr(from, p-from));
	return p + 1;
}
int stat_row::read_stat_id(std::string &line, int from)
{
	int p = indexof(line,from,item_sp);
	if (p < 0)
		p = line.length();
	if (p <= from)
		std::cout << "分析统计元素'stat_row_type'出错" << std::endl;
	m_stat_id = stat_number_encode::decode_int(line.substr(from, p-from));
	return p + 1;

}
int stat_row::read_stat_param(std::string &line, int from)
{
	int p = indexof(line,from,item_sp);
	if (p < 0)
		p = line.length();
	if (p <= from)
		std::cout << "分析统计元素'stat_row_type'出错" << std::endl;
	m_param = line.substr(from, p-from);
	return p + 1;
}


int stat_row::read_stat_value(std::string &line, int from)
{
	int p =indexof(line,from,item_sp);
	if (p < 0)
		p = line.length();
	if (p <= from)
		std::cout << "分析统计元素'stat_row_type'出错" << std::endl;
	set_value(line.substr(from, p-from));
	return p + 1;
}


int stat_row::read_txn_value(std::string &line, int from)
{
	int p = indexof(line,from,item_sp);
	if (p < 0)
		p = line.length();
	if (p <= from)
		std::cout << "分析统计元素'stat_row_type'出错" << std::endl;

	std::string v = line.substr(from, p-from);
	if (v.length() == 0)
	{
		m_txn_val = std::string("");
	}
	else
	{
		m_txn_val = v.substr(1, v.length() - 2);
	}
		
	return p + 1;
}

int stat_row::read_stat_txn_time(std::string &line, int from)
{
	int p = indexof(line,from,item_sp);
	if (p < 0)
		p = line.length();
	if (p <= from)
		std::cout << "分析统计元素'stat_row_type'出错" << std::endl;
	m_txn_time = stat_number_encode::decode_long(line.substr(from, p-from));
	return p + 1;
}
//void stat_row::set_query_counter(counter &queryCounter)
//{
//	m_query_batch = &queryCounter;
//	if (m_query_batch != NULL)
//	{
//		m_query_batch->inc();
//	}
//}
//void stat_row::set_error()
//{
//	if (m_query_batch == NULL)
//		return;
//	m_query_batch->set_error(-1);
//}