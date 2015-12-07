
#include "bin_stream.h"
#include <limits.h>
int bin_stream::min_buf_size = 256;

void arraycopyof(char *dest, int pos, char *src,int _pos, int length)
{
	if (pos < 0 || _pos < 0 || length < 0)
		return;
	if ((unsigned int)length + (unsigned int)_pos >(unsigned int) (sizeof(src) / sizeof(char)) ||
		(unsigned int)length + (unsigned int)pos >(unsigned int) (sizeof(src) / sizeof(char)))
	{
		return;
	}
	if (length == 0)
		return;
	char *d = dest + (unsigned int)pos;
	char *s = src + (unsigned int)_pos;
	memmove(d, s, (unsigned int)length);	
}



bin_stream::bin_stream()
{
	grow(min_buf_size);
	_buff = NULL;
	_buf_error = 0;
	_len = 0;
	_pos = 0;
}

bin_stream::bin_stream(int len)
{
	grow(len);
}

bin_stream::bin_stream(char *buff)
{
	if (buff == NULL)
	{
		_buff = new char[1];
		*_buff = '\0';
	}
	else
	{

		_buff = new char[strlen(buff) + 1];
		strcpy(_buff, buff);
		_len = strlen(buff);
	}

}
bin_stream::~bin_stream()
{
	delete[] _buff;
}


bin_stream::bin_stream(char *buff, int len)
{
	if (buff == NULL)
	{
		_buff = new char[1];
		*_buff = '\0';
	}
	else
	{
		_buff = new char[strlen(buff) + 1];
		strcpy(_buff, buff);
		_len = len;
	}
}

char *bin_stream::array()
{
	return _buff;
}


char *bin_stream::to_bytes()
{
	return to_bytes(0);
}


char *bin_stream::to_bytes(int skip_len)
{
	if (skip_len < 0)
		return NULL;
	int len = size() - skip_len;
	if (len <= 0)
		return NULL;
	char *ret = new char[len+1];
	arraycopyof(_buff, skip_len, ret, 0, len);
	return ret;
}

bool bin_stream::good()
{
	return this->_buf_error == 0;
}

bool bin_stream::can_read(int len)
{
	return good() && can_read(len, _pos);
}

bool bin_stream::can_read(int len, int pos)
{
	return pos + len <= (int)strlen(_buff);
}

bool bin_stream::check_buff_size(int len)
{
	return check_buff_size(len, _pos);
}

bool bin_stream::check_buff_size(int len, int pos)
{
	if (pos + len <= (int)strlen(_buff))
		return true;

	_buf_error = 1;

	return false;
}

 int bin_stream::size()
{
	return _len;
}


 int bin_stream::max_size()
 {
	 return strlen(_buff);
 }

 void bin_stream::ppos(int pos)
 {
	 _len = pos;
 }

 int bin_stream::gpos()
 {
	 return _pos;
 }

void bin_stream::gpos(int pos)
 {
	 _pos = pos;
 }

void bin_stream::reserve(int len)
 {
	if (len <= (int)strlen(_buff))
		 return;

	char * t = new char[len + 1];
	arraycopyof(_buff, 0, t, 0, _len);
	_buff = t;
 }

 void bin_stream::grow(int cap)
 {
	 int n = cap > min_buf_size ? cap : min_buf_size;
	 if (_buff == NULL)
	 {
		 _buff = new char[n];
		 return;
	 }

	 if (cap < (int)strlen(_buff))
		 return;
	 int m= (int)strlen(_buff) > min_buf_size ? strlen(_buff) : min_buf_size;
	 while (m < cap)
		 m += m >> 2;

	 reserve(m);
 }

 bin_stream bin_stream::save(char b)
 {
	 grow(_len + 1);
	 _buff[_len++] = b;

	 return *this;
 }

bin_stream bin_stream::save(short i)
 {
	 grow(_len + 2);
	 _buff[_len++] = (char)((i >> 8) & 0xff);
	 _buff[_len++] = (char)(i & 0xff);

	 return *this;
 }

 bin_stream bin_stream::save(int i)
 {
	 grow(_len + 4);
	 _buff[_len++] = (char)((i >> 24) & 0xff);
	 _buff[_len++] = (char)((i >> 16) & 0xff);
	 _buff[_len++] = (char)((i >> 8) & 0xff);
	 _buff[_len++] = (char)(i & 0xff);

	 return *this;
 }

  bin_stream bin_stream::save(long long i)
 {
	 save((int)(i >> 32));
	 return save((int)(i & 0xFFFFFFFFL));
 }

 bin_stream bin_stream::save(float i)
 {
	 unsigned y;
	 memcpy(&y,&i,4);
	 return save((int)y);
 }

  bin_stream bin_stream::save(double i)
 {
	 unsigned long long y;
	 memcpy(&y,&i,8);
	 return save((int)y);
 }

  bin_stream bin_stream::save(std::string &s)
 {
	 if (s.empty())
		 return off_save(INT_MAX);
	
	save(const_cast<char *>(s.c_str()));
	return *this;
 }

  bin_stream bin_stream::save2(std::string &s)
 {
	 if (s.empty())
		 return save(INT_MAX);

	 return save(const_cast<char *>(s.c_str()));
 }

  bin_stream bin_stream::save(char* s)
 {
	 if (s == NULL)
	 {
		 return off_save(INT_MAX);
	 }

	 off_save(strlen(s));
	 grow(_len + strlen(s));
	 arraycopyof(s, 0, _buff, _len, strlen(s));
	 _len += strlen(s);

	 return *this;
 }

  bin_stream bin_stream::save(unsigned char* s)
  {
	  if (s == NULL)
		  return off_save(INT_MAX);
	  grow(_len + strlen((char *)s) * 2 + 4);
	  off_save(strlen((char *)s));
	  for (int i = 0; i < (int)strlen((char *)s); i++)
		  save((short)s[i]);
	  return *this;
  }


 bin_stream bin_stream::off_save(int len)
 {
	 while (len > 0x7F)
	 {
		 save((char)(len & 0x7F));
		 len >>= 7;
	 }

	 save((char)(len | 0x80));

	 return *this;
 }

int bin_stream::c_int(char b)
 {
	 return 0xff & b;
 }

 int bin_stream::c_int(short b)
 {
	 return 0xffff & b;
 }

 long bin_stream::c_long(int i)
 {
	 return 0xffffffffL & i;
 }

char  bin_stream::load_byte()
 {
	 if (!this->check_buff_size(1))
		 return -1;

	 return _buff[_pos++];
 }

 short bin_stream::load_short()
 {
	 if (!this->check_buff_size(2))
		 return -1;

	 int ret = c_int(_buff[_pos++]) << 8;
	 return (short)(ret | c_int(_buff[_pos++]));
 }

 int bin_stream::load_int()
 {
	 int ret = c_int(load_short()) << 16;
	 return (ret) | c_int(load_short());
 }

  long bin_stream::load_long()
 {
	 long ret = c_long(load_int()) << 32;
	 return (ret) | c_long(load_int());
 }

float bin_stream::load_float()
 {
	 return (float)load_int();
 }

 double bin_stream::load_double()
 {
	 return (double)load_long();
 }

 char* bin_stream::load_byte_array()
 {
	 int len = off_load();
	 if (len == INT_MAX)
		 return NULL;

	 char* ret = new char[len+1];

	 if (!this->check_buff_size(len))
		 return NULL;

	arraycopyof(_buff, _pos, ret, 0, len);
	 _pos += len;

	 return ret;
 }

unsigned char *bin_stream::load_char_array()
 {
	 int len = off_load();
	 if (len == INT_MAX)
		 return NULL;

	 
	 unsigned char *ret = new unsigned char[len+1];

	 if (!this->check_buff_size(len * 2))
		 return NULL;

	 for (int i = 0; i < len; i++)
		 ret[i] = (char) this->load_short();

	 return ret;
 }

std::string bin_stream::load_string()
 {
	 char* b = load_byte_array();
	 if (b == NULL)
		 return "";
	 return std::string(b);
 }

std::string bin_stream::load_string2()
 {
	 unsigned char * b = load_char_array();
	 if (b == NULL)
		 return "";

	 return std::string((char *)b);
 }

 int bin_stream::off_load()
 {
	 int ret = 0, c;
	 for (int i = 0; i < 5; i++)
	 {
		 c = c_int(load_byte());
		 if ((c & 0x80) == 0x80)
		 {
			 return ret | ((c ^ 0x80) << i * 7);
		 }

		 ret |= c << (i * 7);
	 }

	 return 0;
 }

 bool bin_stream:: load_bool()
 {
	 return this->load_byte() != 0;
 }

 bin_stream bin_stream::save(bool b)
 {
	 return this->save((char)(b ? 1 : 0));
 }

