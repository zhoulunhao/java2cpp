#ifndef __DB_FD__H
#define __DB_FD__H

#include <string>


class db_fd
{

public:
	db_fd();
	~db_fd();
	int is_key; // �Ƿ�����
	int is_sys; // �ֶ����ͣ�ϵͳ�ֶΡ��û��ֶΣ�
	int is_query; // �Ƿ�ɱ�ϵͳ�Զ����ѯ��Ϊ����
	int is_list; // �Ƿ�ɱ��Զ����ѯ��ʾ
	int orderby; // ��ʾ����ѯʱ�����
	int txn_order; // ģ���е��ֶ�����
	int is_null; // �Ƿ�����Ϊ��
	int dblen; // �ֶ��ֽڳ���

	std::string tab_name; // �����ƣ�������ˮ������
	std::string fd_name; // �ֶ���������,�û����幫ʽʱ��������
	std::string ref_name; // �û����幫ʽʱ����������ȱʡΪfd_name
	std::string name; // �ֶ���ʾ����
	std::string desc; // �ֶ����������֣�˵��
	std::string type; // ϵͳ��������
	std::string dbtype; // ���ݿ�����
	std::string code; // ���ֶ����õĴ�������
	std::string cvt_func; // ����ת������
	std::string link; // ���ֶ��������������ʾ��ͼ����
	std::string srcid; // ������Դ����
	std::string srcdefault; // ������ԴΪ��ʱ��ȱʡֵ

	int is_txn_field;
	int tab_id;

	std::string toString();
	std::string toStringL();
	
};


#endif