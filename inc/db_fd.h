#ifndef __DB_FD__H
#define __DB_FD__H

#include <string>


class db_fd
{

public:
	db_fd();
	~db_fd();
	int is_key; // 是否主键
	int is_sys; // 字段类型（系统字段、用户字段）
	int is_query; // 是否可被系统自定义查询作为条件
	int is_list; // 是否可被自定义查询显示
	int orderby; // 显示、查询时的序号
	int txn_order; // 模型中的字段排序
	int is_null; // 是否允许为空
	int dblen; // 字段字节长度

	std::string tab_name; // 表名称，交易流水表名称
	std::string fd_name; // 字段数据名称,用户定义公式时的引用名
	std::string ref_name; // 用户定义公式时的引用名，缺省为fd_name
	std::string name; // 字段显示名称
	std::string desc; // 字段描述性文字，说明
	std::string type; // 系统数据类型
	std::string dbtype; // 数据库类型
	std::string code; // 该字段引用的代码类型
	std::string cvt_func; // 数据转换函数
	std::string link; // 该字段所描述对象的显示视图描述
	std::string srcid; // 数据来源名称
	std::string srcdefault; // 数据来源为空时的缺省值

	int is_txn_field;
	int tab_id;

	std::string toString();
	std::string toStringL();
	
};


#endif