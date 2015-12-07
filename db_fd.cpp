

#include "db_fd.h"

#include <stdio.h>

db_fd::db_fd() :is_key(), is_sys(0),is_query(0),is_list(0),orderby(0),txn_order(0),is_null(0),
dblen(0), tab_name(""), fd_name(""), ref_name(""), name(""), desc(""),
type(""), dbtype(""), code(""), cvt_func(""), link(""), srcid(""), srcdefault(""), is_txn_field(0), tab_id(0)
{ 
}

db_fd::~db_fd()
{

}

std::string db_fd::toString()
{
	return "[" + fd_name + "," + ref_name + "," + type + "]";
}

std::string db_fd::toStringL()
{
	char buf[10];
	sprintf(buf, "%.2f", (double)dblen);
	std::string s = buf;
	return "[" + this->name + "," + fd_name + "," + srcid + "," + type + "(" + s + ")]";
}



