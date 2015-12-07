

#include "db_userpattern.h"
#include <vector>
#include <limits.h>
#include "date_tool.h"
#include "bin_stream.h"


const std::string db_userpattern::split_0 = "\n";
const std::string db_userpattern::split_1 = "\\|";
const std::string db_userpattern::split_2 = "#";
std::vector<std::string> vec;




void split(const std::string& str, const std::string &sep, std::vector<std::string>& ret_)
{
	if (str.empty() || sep.empty())
	{
		return;
	}

	std::string tmp;
	std::string::size_type pos_begin = str.find_first_not_of(sep);
	std::string::size_type comma_pos = 0;

	while (pos_begin != std::string::npos)
	{
		comma_pos = str.find(sep, pos_begin);
		if (comma_pos != std::string::npos)
		{
			tmp = str.substr(pos_begin, comma_pos - pos_begin);
			pos_begin = comma_pos + sep.length();
		}
		else
		{
			tmp = str.substr(pos_begin);
			pos_begin = comma_pos;
		}

		if (!tmp.empty())
		{
			ret_.push_back(tmp);
			tmp.clear();
		}
	}
	return;
}
class bin_stream;
db_userpattern::db_userpattern()
{
	userid = "";
	pattern_s = "";
}


db_userpattern::db_userpattern(std::string &userid) :userid(userid)
{
	
}

db_userpattern db_userpattern::load_from(bin_stream &b)
{
	db_userpattern u;
	u.userid = b.load_string();
	u.pattern_s = b.load_string();
	u.pattern_m = db_userpattern::userPattern2Map(u.pattern_s);
	return u;
}


void db_userpattern::save_to(bin_stream &bs)
{
	bs.save(userid);
	bs.save(pattern_s);
}

std::map<int, std::list<Pattern> > db_userpattern::userPattern2Map(std::string &us)
{
	int STATID_INDEX = 0;
	int UPVALUE_INDEX = 1;
	int STARTDATE_INDEX = 2;
	int ENDDATE_INDEX = 3;
	int UPID_INDEX = 4;
	
	std::map<int, std::list<Pattern> > r;
	if (us.empty() || us.length() == 0) return r;
	std::vector<std::string> vecstr;
	split(us,split_0,vecstr);
	for (int i = 0; i < (int)vecstr.size(); i++)
	{
		std::vector<std::string> vecstr1;
		split(vecstr[i],split_1,vecstr1);
		std::list<Pattern> list1;
		std::string stat_id = "";
		for (int j = 0; j < (int)vecstr1.size();j++)
		{
			std::vector<std::string> vecstr2;
			split(vecstr1[j], split_2, vecstr2);
			std::string start_time = (int)vecstr2.size() > STARTDATE_INDEX ? vecstr2[STARTDATE_INDEX] : "";
			struct tm *d = date_tool::parse(std::string(start_time + "00:00:00"));
			long tm1 = date_tool::gettime(d);
			struct tm *d1 = date_tool::parse(std::string(start_time + "00:00:00"));
			long tm2 = date_tool::gettime(d1);
			long start_time_l = start_time.length() == 0 ? LONG_MIN : tm1/*date_tool::parse(start_time + " 00:00:00")*/;//.getTime();
			std::string end_time = (int)vecstr2.size() > ENDDATE_INDEX ? vecstr2[ENDDATE_INDEX] : "";
			long end_time_l = end_time.length() == 0 ? LONG_MAX : tm2/*date_tool::parse(end_time + " 24:00:00")*//*.getTime()*/;
			//long now = System.currentTimeMillis();
			/*if((start_time.length() == 0 || now >= start_time_l)
			&& (end_time.length() == 0 || now < end_time_l)){*/
			Pattern p;
			p.pattern_id = (int)vecstr2.size() > UPID_INDEX ? vecstr2[UPID_INDEX] : "";
			p.stat_id = (int)vecstr2.size() > STATID_INDEX ? vecstr2[STATID_INDEX] : "";
			p.pattern_value = (int)vecstr2.size() > UPVALUE_INDEX ? vecstr2[UPVALUE_INDEX] : "";
			p.start_time = start_time_l;
			p.end_time = end_time_l;
			list1.push_back(p);
		//}
			stat_id = vecstr2[0];
		}
		if (list1.size() > 0) {
			r.insert(std::pair<int,std::list<Pattern> >(atoi(stat_id.c_str()),list1));
		}
	}
	return r;
}



Pattern::Pattern()
{
	stat_id = "";
	 pattern_id = "";
	start_time = 0;
	end_time = 0;
	 pattern_value = "";
}


Pattern::~Pattern()
{
}
bool Pattern::is_enable(long txntime)
{
	return (txntime >= start_time) && (txntime < end_time);
}