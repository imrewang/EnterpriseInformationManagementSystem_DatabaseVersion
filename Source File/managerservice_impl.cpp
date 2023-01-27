#include "managerservice_impl.h"
#include <fstream>
#include <stdio.h>
#include <iomanip>
#include <stdlib.h>
#include "tools.h"
#include "emis.h"

using namespace std;

//��������Ա��½
bool ManagerServiceImpl::login(void)
{
	string a_name = "admin";
	string a_password = "admin";
	cout << "�������û�����";
	string name;
	cin >> name;

	cout << "���������룺";
	string password;
	cin>>password;
	cout << endl;



	if (name == a_name && password == a_password)
	{
		cout << "��½�ɹ�" << endl;
		_getch();
		return true;
	}
	else
	{
		cout << "�û������������" << endl;
		return false;
	}
}


//ͨ������̨��ʾ���˵�
void ManagerServiceImpl::menu(void)
{
	cout << "****��ҵ��Ϣ����ϵͳ****" << endl;
	cout << "    1.���ӹ���Ա" << endl;
	cout << "    2.ɾ������Ա" << endl;
	cout << "    3.�ⶳ����Ա" << endl;
	cout << "    4.�г����й���Ա" << endl;
	cout << "    0.�˳���ϵͳ" << endl;
	cout << "______________________" << endl;
}


//ͨ������̨�������ӹ���Ա�˵���
void ManagerServiceImpl::add(void)
{
	SQL sql("127.0.0.1", "root", "123zxcvbnm", "EMIS", 3306);
	char* cmd = (char*)malloc(1024);

	cout << "���������Աid��";
	int add_m_id;
	cin >> add_m_id;
	cout << "���������Ա�û�����";
	string add_n;
	cin >> add_n;
	cout << "���������Ա���룺";
	string add_pw;
	cin >> add_pw;

	sprintf_s(cmd, BUFFER_SIZE, "INSERT INTO Manager VALUES(%d,'%s','%s',0)", add_m_id, add_n.c_str(), add_pw.c_str());
	int ins = sql.insert(cmd);
	if (0 == ins || ins == -1)
	{
		cout << "����ʧ�ܣ���鿴�����Ƿ��ظ�" << endl;
		_getch();
		_getch();
		return;
	}


	cout << "����Ա��ӳɹ�" << endl;
	_getch();
	_getch();
}


//ͨ������̨����ɾ������Ա�˵���
void ManagerServiceImpl::del(void)
{
	SQL sql("127.0.0.1", "root", "123zxcvbnm", "EMIS", 3306);
	char* cmd = (char*)malloc(1024);

	cout << "������Ҫɾ���Ĺ���Աid��";
	int del_mid;
	cin >> del_mid;


	sprintf_s(cmd, BUFFER_SIZE, "DELETE FROM Manager where mid=%d", del_mid);
	int del = sql.remove(cmd);
	if (0 == del || del == -1)
	{
		cout << "ɾ��ʧ�ܣ���鿴id�Ƿ���ȷ" << endl;
		_getch();
		_getch();
		return;
	}
	cout << "����Աɾ���ɹ�" << endl;

	_getch();
	_getch();
}


//ͨ������̨����ⶳ����Ա�˵���
void ManagerServiceImpl::unf(void)
{
	SQL sql("127.0.0.1", "root", "123zxcvbnm", "EMIS", 3306);
	char* cmd = (char*)malloc(1024);
	memset(cmd, 0, BUFFER_SIZE);

	
	cout << "������Ҫ�ⶳ�Ĺ���Աid��";
	int unf_mid;
	cin >> unf_mid;
	if (cin.fail())
	{
		cin.clear();
		clear_stdin();
	}


	sprintf_s(cmd, BUFFER_SIZE, "select mid,name,prem from Manager where mid=%d", unf_mid);
	int sel = sql.select(cmd);

	if (sel <= 0) {
		cout << "�ⶳʧ�ܣ���鿴id�Ƿ���ȷ" << endl;
		_getch();
		free(cmd);
		return;
	}
	cout << "    ����Աid   ";
	cout << "����Ա�û���   ";
	cout << "    ����Ա��" << endl;
	sql.showResult();

	sprintf_s(cmd, BUFFER_SIZE, "UPDATE Manager SET prem=0 where mid=%d", unf_mid);
	int upd = sql.update(cmd);
	
	if (upd > 0)
	{
		cout << "����Ա�ⶳ�ɹ�" << endl;
	}
	
	
	_getch();
	free(cmd);
}


//ͨ������̨�����г����й���Ա�˵���
void ManagerServiceImpl::list(void)
{
	SQL sql("127.0.0.1", "root", "123zxcvbnm", "EMIS", 3306);
	char* cmd = (char*)malloc(1024);
	sprintf_s(cmd, BUFFER_SIZE, "select mid,name,prem from Manager");
	int sel = sql.select(cmd);
	cout << "    ����Աid   ";
	cout << "����Ա�û���   ";
	cout << "    ����Ա��" << endl;
	sql.showResult();
	if (sel > 0)
	{
		cout << "����ɹ�" << endl;
	}

	_getch();
}