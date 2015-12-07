

#ifndef __DATE__TOOL__H
#define __DATE__TOOL__H

#include <string>
#include <regex.h>

class date_tool
{
public:
	static  std::string FMT_DTS;
	static  std::string FMT_DT;
	static  std::string FMT_DT0;
	static  std::string FMT_D;
	static std::string FMT_T;
	static std::string FMT_T0;
	static long raw_offset;
	static std::string now(const std::string &fmt);
	static std::string now();
	static std::string now_date();
	static std::string now_time();
	static struct tm * parse(std::string &str, const std::string &fmt);
	static struct tm * parse(std::string str);
	//static Pattern pattern; //= Pattern.compile("(\\d{1,4}-\\d{1,2}-\\d{1,2})?(?:\\s+)?(\\d{1,2}\\:\\d{1,2}(\\:\\d{1,2}(\\.\\d{1,3})?)?)?");
	static const  char * pattern;
	static struct tm * parse_date(std::string &str);
	static std::string format(std::string &str, const std::string &formatStr);
	static std::string format(struct tm *ts, const std::string &formatStr);	
	static long gettime(struct tm *s);
	static long tm_date(long d);
	static long tm_time(long d);

};





#endif
