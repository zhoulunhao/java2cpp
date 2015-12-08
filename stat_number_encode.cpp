
#include "stat_number_encode.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <iostream>

void  stat_number_encode::init_m_codec()
{
	if (use_base64 == 1)
		m_codec = new b64();
	else
		m_codec = new b10();
}


codec * stat_number_encode::m_codec = new b64();
int stat_number_encode::use_base64 = tmsapp::get_config("tms.stat.base64", 0);
unsigned short b16::encode16[16] = { 0 };
int b16::decode16[128] = { 0 };

unsigned short b64::encode64[64] = { 0 };
int b64::decode64[128] = { 0 };

stat_number_encode::stat_number_encode()
{
	
}
stat_number_encode::~stat_number_encode()
{
	delete m_codec;
}

void stat_number_encode::modify(codec &s)
{
	if (use_base64 == 1){
		m_codec = new b64();
		if(m_codec == NULL)
		{
			delete m_codec;
			m_codec = NULL;
		}
	}
	else{
		m_codec = new b10();
		if(m_codec == NULL)
		{
			delete m_codec;
			m_codec = NULL;
		}
	}
}
void stat_number_encode::setM_codec(int i)
{
	if (i == 1){
		m_codec = new b64();
		if(m_codec == NULL)
		{
			delete m_codec;
			m_codec = NULL;
		}
	}
	else{
		m_codec =new b10();
		if(m_codec == NULL)
		{
			delete m_codec;
			m_codec = NULL;
		}
	}
}

std::string stat_number_encode::encode(int i)
{
	return m_codec->encode(i);
}
std::string stat_number_encode::encode(long i)
{
	return m_codec->encode(i);
}
int stat_number_encode::decode_int(std::string s)
{
	return m_codec->decode_int(s);
}
int stat_number_encode::decode_long(std::string s)
{
	return m_codec->decode_long(s);
}
std::string codec::encode(int i)
{
	return 0;
}
std::string codec::encode(long i)
{
	return 0;
}
int codec::decode_int(std::string &s)
{
	return 0;
}
long codec::decode_long(std::string &s)
{
	return 0;
}


void b64::init(unsigned short *encode64, int* decode64)
{
	int i = 0;
	for (int j = 'A'; j <= 'Z'; j++)
	{
		encode64[i] = (short)j;
		decode64[j] = i++;
	}

	for (int j = 'a'; j <= 'z'; j++)
	{
		encode64[i] = (short)j;
		decode64[j] = i++;
	}

	for (int j = '0'; j <= '9'; j++)
	{
		encode64[i] = (short)j;
		decode64[j] = i++;
	}
	{
		encode64[i] = '+';
		decode64['+'] = i++;
		encode64[i] = '-';
		decode64['-'] = i++;
	}
}


std::string b64::encode(int i)
{
	printf("i = %d  %s  %d\n",i,__func__,__LINE__);
	char cc[16];
	int k = 0;
	do
	{
		cc[k++] =encode64[(int)i & 0x3f];
		i >>= 6;
	} while (i != 0);
	char *c = new char[k + 1];
	strncpy(c, cc, k);
	return c;
}
std::string b64::encode(long i)
{
	printf("i = %ld  %s  %d\n",i,__func__,__LINE__);
	char cc[16];
	int k = 0;
	do
	{
		cc[k++] = encode64[(int)(i & 0x3f)];
		i >>= 6;
	} while (i != 0);
	char *c = new char[k+1];
	strncpy(c, cc, k);
	return c;
}
int b64::decode_int(std::string &s)
{
	std::cout << s << '\t'<< __func__  << '\t'<< __LINE__ << std::endl;
	
	int ret = 0;
	for (int i = 0, len = s.length(); i < len; i++)
		ret |= decode64[(int)s.at(i)] << (i * 6);

	return ret;
}
long b64::decode_long(std::string &s)
{
	std::cout << s << '\t'<< __func__  << '\t'<< __LINE__ << std::endl;
	long ret = 0;
	for (int i = 0, len = s.length(); i < len; i++)
		ret |= ((long)decode64[(int)s.at(i)]) << (i * 6);

	return ret;
}

void b16::init(unsigned short *encode16, int* decode16)
{
	int i = 0;
	for (int j = '0'; j <= '9'; j++)
	{
		encode16[i] = (short)j;
		decode16[j] = i++;
	}
	for (int j = 'A'; j <= 'F'; j++)
	{
		encode16[i] = (short)j;
		decode16[j] = i++;
	}
}

std::string b16::encode(int i)
{
	printf("i = %d  %s  %d\n",i,__func__,__LINE__);
	char cc[8];
	int k = 0;
	do
	{
		cc[k++] = encode16[i & 0xf];
		i >>= 4;
	} while (i != 0);
	char *c = new char[k + 1];
	strncpy(c, cc, k);
	return c;
}

std::string b16::encode(long i)
{
	printf("i = %ld  %s  %d\n",i,__func__,__LINE__);
	char cc[16] ;
	int k = 0;
	do
	{
		cc[k++] = encode16[(int)(i & 0xf)];
		i >>= 4;
	} while (i != 0);
	char *c = new char[k + 1];
	strncpy(c, cc, k);
	return c;
	
}
int b16::decode_int(std::string &s)
{
	std::cout << s << '\t'<< __func__  << '\t'<< __LINE__ << std::endl;
	int ret = 0;
	for (int i = 0, len = s.length(); i < len; i++)
		ret |= decode16[(int)s.at(i)] << (i << 2);

	return ret;
}

long  b16::decode_long(std::string &s)
{
	std::cout << s << '\t'<< __func__  << '\t'<< __LINE__ << std::endl;
	long ret = 0;
	for (int i = 0, len = s.length(); i < len; i++)
		ret |= ((long)decode16[(int)s.at(i)]) << (i << 2);

	return ret;
}

std::string b10::encode(int i)
{
	printf("i = %d  %s  %d\n",i,__func__,__LINE__);
	char buf[100];
	sprintf(buf, "%.2f", (double)i);
	return buf;
}
std::string b10::encode(long i)
{
	printf("i = %ld  %s  %d\n",i,__func__,__LINE__);
	char buf[100];
	sprintf(buf, "%.2f",(double)i);
	return buf;
}
int b10::decode_int(std::string &s)
{
	return (int)atoi(s.c_str());
}
long b10::decode_long(std::string &s)
{
	return (long)atoi(s.c_str());
}