#ifndef _STAT_WIN_FAC_H
#define _STAT_WIN_FAC_H

#include <list>
#include <vector>
#include <string>
#include "stat_win_base.h"
#include "stat_number_encode.h"
#include <assert.h>
#include <iostream>

#include <stdio.h>
#include <iterator>
class stat_win_base;

template<typename T>
class stat_win_fac 
{
public:
	static const char win_split = '|';
	static const char item_split = ':';
	T fact;
	std::list<T> *win_items;
	int basetime, pos, pos_r;
public:
	
	stat_win_fac()
	{
		win_items = NULL;
		basetime = 0;
		pos = 0;
		pos_r = 0;
	}

	~stat_win_fac()
	{
		if(win_items->size()==0)
			delete win_items;
		else
		{
			typename std::list<T>::iterator it = win_items->begin();
			for(;it!=win_items->end();++it)
			{
				delete *it;
			}
			delete win_items;
		}
	}

	stat_win_fac(std::string &buf, int min_valid_time, T fac, int dec = 0)
	{
		win_items = new std::list<T>;
		fact = fac;
		pos = basetime = 0;
		if (buf.empty())
		{
			pos_r = -1;
		}
		else
		{
			init_items(buf, min_valid_time);
			pos_r = (win_items)->size() - 1;
			printf("pos_r = %d\n", pos_r);
		}
		
		typename std::list<T>::iterator it;
		for (it = win_items->begin(); it != (win_items)->end(); it++)
		{ 
			if ((*it) == NULL)
				break;
			//空指针怎么搞？？？
			printf("%d\n", (*it)->win_time);
			(*it)->win_time -= dec;
		}
	
		if ((win_items)->size() > 0)
			basetime = (win_items)->front()->win_time;
		printf("basetime= %d\n", basetime);
	}


	int skip_(std::string &cc, int p, char ch)
	{
		int count = 0;
		const char *s = cc.c_str() + p;
		while (*s++ != '\0')
		{
			count++;
			if (*s == ch)
				return p + count;
		}
		return 100;
	}


	int skip_r(std::string &cc, int p, char ch)
	{
		std::string c = cc.substr(0, p);
		return c.find_last_of(ch);
	}


	void init_items(std::string &cc, int min_valid_time)
	{
		//std::list<T> listt(new std::list<T>);/*= win_items*/;
		/*win_items.push_front(fact);*/
		int p = 0;
		int i = 0;
		int time = 0;
		int len = cc.length();
		for (; p < len;)
		{
			i = p;
			p = skip_(cc, i, item_split);
			printf("p = %d\n", p);
			time = stat_number_encode::decode_int(cc.substr(i, p-i)) + basetime;
			printf("%d\n", stat_number_encode::decode_int(cc.substr(i, p-i)));
			if (i == 0)
				basetime = time;
			if (time < min_valid_time)
			{
				p = skip_(cc, p, win_split) + 1;
				continue;
			}
			p = i;
			break;
		}
		//typename std::list<T>::iterator it = win_items->begin();
		for (; p < len;)
		{
			printf("p = %d\n", p);
			i = skip_(cc, p, win_split);
			
			int  ted = p == 0 ? 0 : basetime;
			printf("win_items.size() = %d\n",(int)win_items->size());
			win_items->push_back((T)fact->from(items(cc, p, i), /*(stat_win_fac<stat_win_base*>) *this,*/ ted));
			//it = win_items->erase(it);
			printf("win_items.size() = %d\n",(int)win_items->size());
			p = i + 1;
		}

		printf("fact->win_time = %d\n", fact->win_time);
		printf("win_items.size() = %d\n", (int)win_items->size());
		if (win_items->empty())
		{
			basetime = 0;
		}
		else
		{
			basetime = win_items->front()->win_time;
		}
	}

	std::string * items(std::string &cc,int s, int e)
	{
		std::string ret[5];
		int len = 0;
		for (; s < e;)
		{
			int i = skip_(cc, s, item_split);
			printf("i = %d\n", i);
			if (i < 0)
				i = e;
			ret[len++] = cc.substr(s, (i >= e ? e : i) -s);
			s = i + 1;
		}
		std::string *str = new std::string[len];
		for (int i = 0; i < len; i++)
		{
			str[i] = ret[i];
			std::cout << str[i] << std::endl;
		}
		return str;
	}
	
	class FI
	{
	public:
		int flag;// -1 业务时间早于最早的，0，业务时间等于某窗口，1业务时间大于最大窗口或无窗口
		T e;
		FI(int flag, T &e)
		{
			flag = flag;
			e = e;
		}
		FI(int flag)
		{
			flag = flag;
		}
	};
	
	FI find_r(int cur_win_time)
	{
		T n = next_r();
		if (n->win_time < cur_win_time)
			return FI(1);
		////否则，查找最后一个相等的时间窗
		for (; n!=NULL ; n = next_r())
		{
			if (n->win_time == cur_win_time)
				return FI(0, n);
			if (n->win_time < cur_win_time)
			{
				pos_r++;
				return FI(-1);
			}
		}
		// 没有找到，当前时间不在所有的时间窗中，返回第一个
		return FI(-1);
	}

//	T get(std::list<T> *a)
//	{
//		
//		typename std::list<T>::iterator it = a->begin();
//		int i = 0;
//		pos+=1;
//		for (; i < pos&&it != a->end();i++, ++it)
//		{
//		}
//		if (i == pos)
//		{
//			return *it;
//		}
//		return NULL;
//	}

//	T get2(std::list<T> *a)
//	{
//		
//		typename std::list<T>::iterator it = a->begin();
//		int i = 0;
//		pos_r -= 1;
//		for (; i < pos_r&& it != a->end(); i++, ++it)
//		{
//		}
//		if (i == pos_r)
//		{
//			return *it;
//		}
//		return NULL;
//	}
	T next()
	{
		printf("pos = %d  (win_items).size() = %d\n  ", pos, (int)(win_items)->size());
		if (pos >= (int)(win_items)->size())
			return NULL;
		typename std::list<T>::iterator it = (win_items)->begin();
		std::advance(it,pos++);
		return (*it);
	}


	T next_r()
	{
		if (pos_r < 0 || pos_r >= (int)(win_items)->size())
			return NULL;
		typename std::list<T>::iterator it = win_items->begin();
		std::advance(it,pos_r--);
		return (*it);
	}

	std::string tostring()
	{
		if ((win_items)->empty())
			return "";
		char *buf = new char[512];
		if (buf == NULL)
			return "";
		if (win_items->front() == NULL)
			return "";
		printf("win_items.front().win_time = %d\n", (win_items)->front()->win_time);
		(win_items)->front()->appendTo(&buf, 0);
		typename std::list<T>::iterator it = (win_items)->begin();
		printf("(win_items).size() = %d\n",(int)(win_items)->size());
		std::advance(it, 1);
		for (; it != (win_items)->end(); it++)
		{
			if (*it == NULL)
				break;
			(*(it))->appendTo(&buf, this->basetime);
			printf("this->basetime = %d\n", this->basetime);
		}
		return buf;
	}

	int base_time1()
	{
		return this->basetime;
	}

	int rindex()
	{
		return this->pos_r;
	}

	int index1()
	{
		return this->pos;
	}

	void insert1(int i, T e)
	{
		typename std::list<T>::iterator it = (win_items)->begin();
		for (int im = 0; it != (win_items)->end() && im < i; im++)
			it++;
		(win_items)->insert(it, e);
		if (e->win_time < basetime)
			basetime = e->win_time;
	}

	void reset_rindex()
	{
		this->pos_r = (win_items)->size() - 1;
	}

	void del_before(int rindex)
	{
		if (rindex < 0)
			return;
		std::list<T> windows_items;
		typename std::list<T>::iterator it = (win_items)->begin();
		for (int i = 0; (i < rindex + 1) && it != (win_items)->end(); i++, it++)
		{
		}
		for (; it != (win_items)->end(); it++)
			windows_items.push_back(*it);

		this->pos_r = windows_items.size() - 1;
		this->pos = 0;
		if (windows_items.size() > 0)
			this->basetime = windows_items.front()->win_time;
	}
	int size()
	{
		return (win_items)->size();
	}
};
//template<typename T>
//std::list<T> *stat_win_fac<T>::win_items = new std::list<T>(32) ;


#endif // !_STAT_WIN_FAC_H
