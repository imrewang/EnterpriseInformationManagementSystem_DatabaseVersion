#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <fstream>
#include "service_impl.h"
#include "tools.h"
#include "emis.h"


using namespace std;


void ServiceImpl::menu(void)//��ʾ��Ӫ�����Ӳ˵�
{
	cout << "****��ҵ��Ϣ����ϵͳ****" << endl;
	cout << "    1.���Ӳ���" << endl;
	cout << "    2.ɾ������" << endl;
	cout << "    3.�г�����" << endl;
	cout << "    4.����Ա��" << endl;
	cout << "    5.ɾ��Ա��" << endl;
	cout << "    6.�޸�Ա����Ϣ" << endl;
	cout << "    7.�г�����Ա��" << endl;
	cout << "    8.�г�����Ա��" << endl;
	cout << "    0.�˳���ϵͳ" << endl;
	cout << "______________________" << endl;
}

ServiceImpl::ServiceImpl()
{
}

bool ServiceImpl::manager_login(void)
{
	

	SQL sql("127.0.0.1", "root", "123zxcvbnm", "EMIS", 3306);

	cout << "�������û�����";
	string name;
	cin >> name;

	char* cmd = (char*)malloc(1024);
	sprintf_s(cmd, BUFFER_SIZE, "select name from Manager where name=\"%s\"", name.c_str());
	int selname = sql.select(cmd);

	if (selname <= 0)
	{
		cout << "û�в�ѯ���ʺ�" << endl;
		free(cmd);
		return false;
		
	}
	cout << "�ɹ���ѯ���ʺ�" << endl;
	while (1) {
		sprintf_s(cmd, BUFFER_SIZE, "select name from Manager where name=\"%s\" and prem>=3", name.c_str());
		int selprem = sql.select(cmd);
		if (selprem > 0) {
			cout << "�˻����ᣬ����ϵ��������Ա�ⶳ" << endl;
			free(cmd);
			return false;
		}

		cout << "���������룺";
		string password;
		cin >> password;
		

		sprintf_s(cmd, BUFFER_SIZE, "SELECT `password` FROM Manager WHERE `name`=\"%s\" AND `password`=\"%s\"", name.c_str(), password.c_str());
		int selpw = sql.select(cmd);
		

		if (selpw > 0)
		{
			cout << "�ɹ���¼" << endl;
			free(cmd);
			return true;
		}
		else {
			sprintf_s(cmd, BUFFER_SIZE, "UPDATE Manager SET prem=prem+1 where name=\"%s\"", name.c_str());
			int upd = sql.update(cmd);
			cout << "��������������" << endl;
		}
	}
	cout << "ʧ��" << endl;
	free(cmd);
	return false;
}


void ServiceImpl::addDept(void)//���Ӳ��Ų˵���
{
	SQL sql("127.0.0.1", "root", "123zxcvbnm", "EMIS", 3306);
	char* cmd = (char*)malloc(1024*sizeof(char));
	cout << "�����벿������";
	
	string name;
	cin >> name;

	cout << "�����벿��id��";
	int did;
	cin >> did;
	
	sprintf_s(cmd, BUFFER_SIZE, "insert into Department VALUES(%d,'%s',0)", did, name.c_str());
	

	int ins = sql.insert(cmd);

	if (0 == ins || ins == -1)
	{
		cout << "����ʧ�ܣ���鿴�����Ƿ��ظ�" << endl;
		_getch();
		_getch();
		free(cmd);
		return;
	}
	cout << "������ӳɹ�" << endl;
	_getch();
	_getch();
	free(cmd);
}
void ServiceImpl::deleteDept(void)//ɾ�����Ų˵���
{
	SQL sql("127.0.0.1", "root", "123zxcvbnm", "EMIS", 3306);
	char* cmd = (char*)malloc(1024);

	cout << "������Ҫɾ���Ĳ���id��";
	int did;
	cin >> did;

	sprintf_s(cmd, BUFFER_SIZE, "DELETE FROM Department where did=%d", did);
	int del = sql.remove(cmd);
	if (0 >= del)
	{
		cout << "ɾ��ʧ�ܣ���鿴id�Ƿ���ȷ" << endl;
		_getch();
		_getch();
		free(cmd);
		return;
	}

	sprintf_s(cmd, BUFFER_SIZE , "DELETE FROM Employee where did=%d", did);
	int del2 = sql.remove(cmd);
	if (del2 > 0)
	{
		cout << "�ò���Ա��ɾ���ɹ�" << endl;
	}
	else
		cout << "�ò�����Ա��" << endl;

	cout << "����ɾ���ɹ�" << endl;
	_getch();
	_getch();
	free(cmd);
}
void ServiceImpl::listDept(void)//�г����Ų˵���
{
	SQL sql("127.0.0.1", "root", "123zxcvbnm", "EMIS", 3306);
	char* cmd = (char*)malloc(1024);
	sprintf_s(cmd, BUFFER_SIZE, "select did,name,num from Department");
	int sel = sql.select(cmd);

	cout << "      ����id   ";
	cout << "      ������   ";
	cout << "    ��������" << endl;
	sql.showResult();

	if (sel > 0)
	{
		cout << "������" << endl;
	}

	_getch();
	free(cmd);
}
void ServiceImpl::addEmp(void)//����Ա���˵���
{
	cout << "�����벿�ű�ţ�";
	int d_id = 0;
	cin >> d_id;

	SQL sql("127.0.0.1", "root", "123zxcvbnm", "EMIS", 3306);
	char* cmd = (char*)malloc(1024);

	sprintf_s(cmd, BUFFER_SIZE, "select did from Department where did=%d", d_id);
	int sel = sql.select(cmd);
	if (sel <= 0)
	{
		cout << "sel:" << sel << endl;
		cout << "�ò��Ų�����" << endl;
		_getch();
		free(cmd);
		return;
	}
	int eid;
	string name;
	int gender = 0;
	int age;
	cout << "������Ա��id��";
	cin >> eid;
	cout << "������Ա��������";
	cin >> name;
	cout << "��ѡ��Ա���Ա�(0,��ʾ�У�1����ʾŮ),";

	switch (get_cmd('0', '1'))
	{
	case '0': gender = 0; break;
	case '1': gender = 1; break;
	}

	cout << "������Ա�����䣺";
	cin >> age;
	_getch();

	sprintf_s(cmd, BUFFER_SIZE, "insert into Employee VALUES(%d,'%s',%d,%d,%d)", eid, name.c_str(), gender, age, d_id);
	int ins = sql.insert(cmd);
	if (ins <= 0)
	{
		cout << "ins:" << ins << endl;
		cout << "�������󣬲���ʧ��" << endl;
		_getch();
		free(cmd);
		return;
	}

	sprintf_s(cmd, BUFFER_SIZE, "select did from Employee where did=%d", d_id);
	int count = sql.select(cmd);
	cout << "�ֲ�������:" << count << endl;
	sprintf_s(cmd, BUFFER_SIZE, "UPDATE Department SET num=%d where did=%d", count, d_id);
	int upd = sql.update(cmd);
	if (upd > 0)
	{
		cout << "�������ݸ������" << endl;
	}

	cout << "Ա����ӳɹ�" << endl;
	_getch();
	free(cmd);
}
void ServiceImpl::deleteEmp(void)//ɾ��Ա���˵���
{
	cout << "������Ա�����:";
	int id = -1, did = -1;
	cin >> id;
	cout << "������Ա���Ĳ���id:";
	cin >> did;
	_getch();

	SQL sql("127.0.0.1", "root", "123zxcvbnm", "EMIS", 3306);
	char* cmd = (char*)malloc(1024);

	sprintf_s(cmd, BUFFER_SIZE, "select eid from Employee where eid=%d", id);
	int sel = sql.select(cmd);
	if (sel <= 0)
	{
		cout << "sel:" << sel << endl;
		cout << "��Ա��������,ɾ��ʧ��" << endl;
		_getch();
		return;
	}
	sprintf_s(cmd, BUFFER_SIZE, "select did from Department where did=%d", did);
	int sel2 = sql.select(cmd);
	if (sel2 <= 0)
	{
		cout << "sel2:" << sel2 << endl;
		cout << "�ò��Ų�����,ɾ��ʧ��" << endl;
		_getch();
		return;
	}

	sprintf_s(cmd, BUFFER_SIZE, "DELETE FROM Employee where eid=%d", id);
	int del = sql.remove(cmd);
	if (del <= 0)
	{
		cout << "del:" << del << endl;
		cout << "������������,ɾ��ʧ��" << endl;
		_getch();
		return;
	}

	sprintf_s(cmd, BUFFER_SIZE, "select did from Employee where did=%d", did);
	int count = sql.select(cmd);
	cout << "�ֲ�������:" << count << endl;
	sprintf_s(cmd, BUFFER_SIZE, "UPDATE Department SET num=%d where did=%d", count, did);
	int upd = sql.update(cmd);
	if (upd > 0)
	{
		cout << "�������ݸ������" << endl;
	}

	cout << "ɾ��Ա���ɹ�" << endl;
	_getch();

}
void ServiceImpl::modifyEmp(void)//�޸�Ա����Ϣ�˵���
{
	cout << "������Ա�����:";
	int id = -1, old_did = -1;
	cin >> id;
	cout << "������Ա���Ĳ���id:";
	cin >> old_did;

	SQL sql("127.0.0.1", "root", "123zxcvbnm", "EMIS", 3306);
	char* cmd = (char*)malloc(1024);

	sprintf_s (cmd, BUFFER_SIZE, "select eid from Employee where eid=%d", id);
	int sel = sql.select(cmd);
	if (sel <= 0)
	{
		//cout << "selname:" << selname << endl;
		cout << "��Ա��������,�޸�ʧ��" << endl;
		_getch();
		return;
	}
	sprintf_s(cmd, BUFFER_SIZE, "select did from Department where did=%d", old_did);
	int sel2 = sql.select(cmd);
	if (sel2 <= 0)
	{
		//cout << "selpw:" << selpw << endl;
		cout << "�ò��Ų�����,�޸�ʧ��" << endl;
		_getch();
		return;
	}

	string name;
	cout << "������Ա������������";
	cin >> name;
	int gender = 0;
	cout << "��ѡ��Ա���Ա�(0,��ʾ�У�1����ʾŮ),";
	switch (get_cmd('0', '1'))
	{
	case '0': gender = 0; break;
	case '1': gender = 1; break;
	}

	cout << "������Ա���������䣺";
	int age = 0;
	cin >> age;

	cout << "������Ա�����²���id��";
	int did = 0;
	cin >> did;

	_getch();

	sprintf_s(cmd, BUFFER_SIZE, "UPDATE Employee SET name='%s',gender=%d,age=%d,did=%d where eid=%d", name.c_str(), gender, age, did, id);
	int upd = sql.update(cmd);
	if (upd <= 0)
	{
		cout << "upd:" << upd << endl;
		cout << "�������������޸�ʧ��" << endl;
		_getch();
		return;
	}

	sprintf_s(cmd, BUFFER_SIZE, "select did from Employee where did=%d", did);
	int count = sql.select(cmd);
	cout << "�ֲ�������:" << count << endl;
	sprintf_s(cmd, BUFFER_SIZE, "UPDATE Department SET num=%d where did=%d", count, did);
	upd = sql.update(cmd);


	cout << "�޸ĳɹ�" << endl;
	_getch();
}
void ServiceImpl::listEmp(void)//�г�����Ա���˵���
{
	int c_id;
	cout << "�����벿�ű��:";
	cin >> c_id;
	SQL sql("127.0.0.1", "root", "123zxcvbnm", "EMIS", 3306);
	char* cmd = (char*)malloc(1024);
	sprintf_s(cmd, BUFFER_SIZE, "select eid,name,gender,age,did from Employee where did=%d", c_id);
	int sel = sql.select(cmd);
	cout << "      Ա��id   ";
	cout << "      Ա����   ";
	cout << "�Ա�(0��1Ů)   ";
	cout << "        ����   ";
	cout << "      ����id" << endl;
	sql.showResult();
	if (sel > 0)
	{
		cout << "������" << endl;
	}
	cout << endl;
	_getch();
	_getch();
}
void ServiceImpl::listAllEmp(void)//�г�����Ա���˵���
{
	SQL sql("127.0.0.1", "root", "123zxcvbnm", "EMIS", 3306);
	char* cmd = (char*)malloc(1024);
	sprintf_s(cmd, BUFFER_SIZE, "select eid,name,gender,age,did from Employee");
	int sel = sql.select(cmd);
	cout << "      Ա��id   ";
	cout << "      Ա����   ";
	cout << "�Ա�(0��1Ů)   ";
	cout << "        ����   ";
	cout << "      ����id" << endl;
	sql.showResult();
	if (sel > 0)
	{
		cout << "������" << endl;
	}
	cout << endl;
	_getch();
}
