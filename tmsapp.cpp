#include "tmsapp.h"
#include <time.h>
#include <iostream>



int tmsapp::i = 0;
int tmsapp::key = 0;
std::string tmsapp::s = "";
std::string tmsapp::defaultValue = "";
bool tmsapp::print_console = false;
std::string tmsapp::str = "";
Properties tmsapp::configure = Properties();


Properties::Properties() :deviceconfig(""), Size(0)
{


}

Properties::~Properties()
{

}
std::string Properties::getProperty(const std::string &t1, const std::string &t2)
{
	return t1 + t2;
}
void Properties::put( std::string &t1, const std::string &t2)
{
	t1 += t2;
}
/*
static long nanoMs();
static void set_config(Properties config);
static std::string get_config(std::string &key, std::string &defaultValue);
static std::string get_config(std::string &key, std::string &defaultValue, bool print_console);
static int get_config(std::string &key, int defaultValue);
static int get_config(std::string &key, int defaultValue, bool print_console);
static bool is_cluster();
static void set_config(std::string &str, int i);
static void set_config(std::string &str, std::string &s);
*/
 long tmsapp::nanoMs()
{
	return clock() / 1000;
}

 void tmsapp::set_config(Properties &config)
{
	configure = config;
}

 std::string tmsapp::get_config(const std::string &key, const std::string &defaultValue)
{
	return get_config(key, defaultValue, true);
}
 std::string tmsapp::get_config(const std::string &key, const std::string &defaultValue, bool print_console)
{
	printf("**********************\n");
	std::string ret = configure.Size == 0 ? defaultValue : configure.getProperty(key, defaultValue);
	if (print_console)
		std::cout << key << "=" << ret << std::endl;
	return ret;
}


 int tmsapp::get_config(const std::string &key, int defaultValue)
{
	return get_config(key, defaultValue, true);
}
 int tmsapp::get_config(const std::string &key, int defaultValue, bool print_console)
{
	std::string v = get_config(key, "" + defaultValue, print_console);
	return atoi(v.c_str());

}
 bool tmsapp::is_cluster()
{
	return get_config("tmsapp.cluster", 0) != 0;
}

 void tmsapp::set_config(std::string &str, int i)
 {
	 static char buf[256];
	 sprintf(buf, "%.2f", (double)i);
	 std::string s = buf;
	 configure.put(str,s);
 }
 void tmsapp::set_config(std::string &str, const std::string &s)
 {
	 configure.put(str, s);
 }