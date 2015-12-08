#ifndef __STAT_NUMBER_ENCODE_H
#define __STAT_NUMBER_ENCODE_H

#include <string>
#include "tmsapp.h"

class codec;
class stat_number_encode
{
public:

	stat_number_encode();
	~stat_number_encode();
	static int use_base64;
	static void setM_codec(int i);
	static std::string encode(int i);
	static std::string encode(long i);
	static int decode_int(std::string s);
	static int decode_long(std::string s);
	static void modify(codec &s);

public:
	static void init_m_codec();
	static codec *m_codec;

};

class codec
{
public:
	virtual std::string encode(int i);
	virtual std::string encode(long i);
	virtual int decode_int(std::string &s);
	virtual long decode_long(std::string &s);
};


class b64 : public codec
{
public:
	static unsigned short encode64[64];
	static int decode64[128];
	static void init( unsigned short *encode64, int* decode64);
	std::string encode(int i);
	std::string encode(long i);
	int decode_int(std::string &s);
	long decode_long(std::string &s);

};


class b16 : public codec
{
public:
	static unsigned short encode16[16];
	static int decode16[128];
	static void init(unsigned short *encode16, int* decode16);
	std::string encode(int i);
	std::string encode(long i);
	int decode_int(std::string &s);
	long decode_long(std::string &s);


};



class b10 : public codec
{
public:
	std::string encode(int i);
	std::string encode(long i);
	int decode_int(std::string &s);
	long decode_long(std::string &s);
};
#endif