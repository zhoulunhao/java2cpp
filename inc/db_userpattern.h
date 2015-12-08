#ifndef __DB_USERPATTERN__H
#define  __DB_USERPATTERN__H


#include <string>
#include <map>
#include <list>
#include <vector>
#include "bin_stream.h"
#include <string.h>




class Pattern;
class db_userpattern
{
private:
	const static std::string split_0;
	const static std::string split_1;
	const static std::string split_2;
public:
	std::string userid;// �û�ID
	std::string pattern_s;// ��Ϊϰ���ַ���
	std::map<int, std::list<Pattern> > pattern_m;// ��Ϊϰ�߶���

	db_userpattern();

	db_userpattern(std::string &userid);

	/**
	* ��������:������Ϊϰ�߻���
	* @param bin_stream
	* @return
	*/

	static db_userpattern load_from(bin_stream &b);

	
 	/**
	* ��������:���»�������
	* @param bs
	*/
	void save_to(bin_stream &bs);
	static std::map<int, std::list<Pattern> > userPattern2Map(std::string &us);
};

class Pattern
{

public:
	Pattern();
	~Pattern();
	std::string stat_id;
	std::string pattern_id;
	long start_time;
	long end_time;
	std::string pattern_value;
	bool is_enable(long txntime);
};
	



#endif
