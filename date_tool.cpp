
#include "date_tool.h"
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

time_t gettimeoffset()
{
	//从1970-1-1 到现在经过的秒数
	time_t lt;
	lt = time(NULL);
	return lt;
}

std::string date_tool::FMT_DTS = "%Y-%m-%d %H:%M:%S.SSS";
std::string date_tool::FMT_DT = "%Y-%m-%d %H:%M:%S";
std::string date_tool::FMT_DT0 = "%Y-%m-%d %H:%M";
std::string date_tool::FMT_D = "%Y-%m-%d";
std::string date_tool::FMT_T = "%H:%M:%S";
std::string date_tool::FMT_T0 = "%H:%M";
long  date_tool::raw_offset = (long)gettimeoffset();
const char * date_tool::pattern = "(\\d{1,4}-\\d{1,2}-\\d{1,2})?(?:\\s+)?(\\d{1,2}\\:\\d{1,2}(\\:\\d{1,2}(\\.\\d{1,3})?)?)?";

//int64_t GetCurrentStamp64()
//{
//	boost::posix_time::ptime epoch(boost::gregorian::date(1970, boost::gregorian::Jan, 1));
//	boost::posix_time::time_duration time_from_epoch =
//		//  boost::posix_time::microsec_clock::universal_time() - epoch;
//
//		boost::posix_time::second_clock::universal_time() - epoch;
//
//	//return time_from_epoch.total_microseconds();
//	return time_from_epoch.total_seconds();
//}
std::string date_tool::now(const std::string &fmt)
{
	static char str_time[100];
	struct tm *local_time = NULL;
	time_t utc_time;
	utc_time = time(NULL);
	local_time = (tm*)localtime(&utc_time);
	strftime(str_time, sizeof(str_time), fmt.c_str(), local_time);
	return str_time;
}

std::string date_tool::now()
{
	return now(FMT_DT); 
}
std::string date_tool::now_date()
{
	return now(FMT_D);
}
std::string date_tool::now_time()
{
	return now(FMT_T);
}


long  date_tool::gettime(struct tm *s)
{
	return (long)mktime(s);
}
struct tm * date_tool::parse(std::string &str, const std::string &fmt)
{
	
	if(str.empty())
		return NULL;
	struct tm* t = NULL;
	strptime(str.c_str(),fmt.c_str(),t);
	return t;
}
struct tm * date_tool::parse(std::string str)
{
	char ymd[20];
	char  hm[20];
	char sec[20];
	char  mil[20];
	memset(ymd,'\0',sizeof(ymd));
	memset(hm,'\0',sizeof(hm));
	memset(sec,'\0',sizeof(sec));
	memset(mil,'\0',sizeof(mil));
	
	if (str.empty())
		return NULL;
		
	regex_t reg;
	char errbuf[1024];
	int cflags = REG_EXTENDED;
	const size_t nmatch = 5;
	regmatch_t matchs[5];
	int errcode = regcomp(&reg,pattern,cflags);
	if(errcode == 0)
	{
		errcode = regexec(&reg,str.c_str(),nmatch,matchs,REG_NOTBOL);
		if(errcode == REG_NOMATCH)
		{
			printf("NO matchs");
			exit(-1);
		}
		else if(errcode == 0)
		{
			memcpy(ymd,str.c_str()+matchs[0].rm_so,matchs[0].rm_eo-matchs[0].rm_so);
			memcpy(hm,str.c_str()+matchs[1].rm_so,matchs[1].rm_eo-matchs[1].rm_so);
			memcpy(sec,str.c_str()+matchs[2].rm_so,matchs[2].rm_eo-matchs[2].rm_so);
			memcpy(mil,str.c_str()+matchs[3].rm_so,matchs[3].rm_eo-matchs[3].rm_so);
		}
	}
	else if(errcode < 0)
	{
		regerror(errcode,&reg,errbuf,sizeof(errbuf));
		printf("errcode:%s\n",errbuf);
	}
	std::string fmt = "";
	if (ymd!=NULL && hm!=NULL && sec !=NULL && mil!=NULL)
	{
		fmt = FMT_DTS;
	}
	else if (ymd!=NULL && hm!=NULL && sec !=NULL)
		fmt = FMT_DT;
	else if (ymd!=NULL && hm!=NULL)
		fmt = FMT_DT0;
	else if (ymd!=NULL )
		fmt = FMT_D;
	else if (hm!=NULL && sec !=NULL)
		fmt = FMT_T;
	else
		fmt = FMT_T0;
	return parse(str, fmt);

}

struct tm * date_tool::parse_date(std::string &str)
{
	return parse(str, FMT_D);
}

std::string date_tool::format(std::string &str,const std::string &formatStr)
{
	if(str.empty())
		return NULL;
	return format(parse(str),formatStr);
}

std::string date_tool::format(struct tm *ts,const std::string &formatStr)
{
	if(ts== NULL)
		return NULL;
	static char buf[100];
	 strftime(buf,sizeof(buf),formatStr.c_str(),ts);
	 return buf;
}


long date_tool::tm_date(long d)
{
	d = raw_offset + d;
	return d / ( 24 * 60 * 60)*( 24 * 60 * 60) - raw_offset;
}
long date_tool::tm_time(long d)
{
	return (d - raw_offset) - tm_date(d);

}
