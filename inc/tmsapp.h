#ifndef __TMSAPP_H
#define __TMSAPP_H
#include <string>
#include <stdio.h>
#include <stdlib.h>
class Properties
{
public:
	Properties();
	~Properties();
	std::string getProperty(const std::string &,const  std::string &);
	void  put( std::string &t1, const std::string &t2);
	std::string deviceconfig;
	int Size;
};
class tmsapp 
{
private:
	static Properties configure;
public:

	static long nanoMs();
	static void set_config(Properties &config);
	static std::string get_config(const std::string &key, const std::string &defaultValue);
	static std::string get_config(const std::string &key, const std::string &defaultValue, bool print_console);
	static int get_config(const std::string &key, int defaultValue);
	static int get_config(const std::string &key, int defaultValue, bool print_console);
	static bool is_cluster();
	static void set_config(std::string &str, int i);
	static void set_config(std::string &str, const std::string &s);
public:
	static std::string key;
	static std::string defaultValue;
	static bool print_console;
	static std::string str;
	static std::string s;
	static int i;
};



#endif