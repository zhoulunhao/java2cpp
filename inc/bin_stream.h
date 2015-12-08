

#ifndef __BIN__STREAM__H
#define __BIN__STREAM__H
#include <string>
#include <string.h>
#include <stdlib.h>

class bin_stream
{
private:
	static int min_buf_size;
	char * _buff;
	int _len;
	int _pos;
	int _buf_error;

public:
	~bin_stream();
	bin_stream();
	bin_stream(int len);
	bin_stream(char *buff);
	bin_stream(char *buff, int len);
	char *array();
	char *to_bytes();
	char *to_bytes(int skip_len);
	bool good();
	bool can_read(int len);
	bool can_read(int len, int pos);
	bool check_buff_size(int len);
	bool check_buff_size(int len, int pos);
	int size();
	int max_size();
	void ppos(int pos);
	int gpos();
	void gpos(int pos);
	void reserve(int len);

	void grow(int cap);
	bin_stream save(char b);
	bin_stream save(short i);
	bin_stream save(int i);
	bin_stream save(long long i);
	bin_stream save(float i);
	bin_stream save(double i);
	bin_stream save(std::string &s);
	bin_stream save2(std::string &s);
	bin_stream save(char *s);
	bin_stream save(unsigned char *s);
	bin_stream off_save(int len);
	int c_int(char b);
	int c_int(short b);
	long c_long(int i);
	char load_byte();
	short load_short();
	int load_int();
	long load_long();
	float load_float();
	double load_double();
	char * load_byte_array();
	unsigned char * load_char_array();
	std::string load_string();
	std::string load_string2();
	int off_load();

	bool load_bool();
	bin_stream save(bool b);

};






void  arraycopyof(char *dest, int pos, char *src, int _pos, int length);
#endif