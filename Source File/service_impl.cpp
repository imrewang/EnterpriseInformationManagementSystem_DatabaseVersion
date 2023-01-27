#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <fstream>
#include "service_impl.h"
#include "tools.h"
#include "emis.h"


using namespace std;


void ServiceImpl::menu(void)//显示运营管理子菜单
{
	cout << "****企业信息管理系统****" << endl;
	cout << "    1.增加部门" << endl;
	cout << "    2.删除部门" << endl;
	cout << "    3.列出部门" << endl;
	cout << "    4.增加员工" << endl;
	cout << "    5.删除员工" << endl;
	cout << "    6.修改员工信息" << endl;
	cout << "    7.列出部门员工" << endl;
	cout << "    8.列出所有员工" << endl;
	cout << "    0.退出子系统" << endl;
	cout << "______________________" << endl;
}

ServiceImpl::ServiceImpl()
{
}

bool ServiceImpl::manager_login(void)
{
	

	SQL sql("127.0.0.1", "root", "root", "EMIS", 3306);

	cout << "请输入用户名：";
	string name;
	cin >> name;

	char* cmd = (char*)malloc(1024);
	sprintf_s(cmd, BUFFER_SIZE, "select name from Manager where name=\"%s\"", name.c_str());
	int selname = sql.select(cmd);

	if (selname <= 0)
	{
		cout << "没有查询到帐号" << endl;
		free(cmd);
		return false;
		
	}
	cout << "成功查询到帐号" << endl;
	while (1) {
		sprintf_s(cmd, BUFFER_SIZE, "select name from Manager where name=\"%s\" and prem>=3", name.c_str());
		int selprem = sql.select(cmd);
		if (selprem > 0) {
			cout << "账户冻结，请联系超级管理员解冻" << endl;
			free(cmd);
			return false;
		}

		cout << "请输入密码：";
		string password;
		cin >> password;
		

		sprintf_s(cmd, BUFFER_SIZE, "SELECT `password` FROM Manager WHERE `name`=\"%s\" AND `password`=\"%s\"", name.c_str(), password.c_str());
		int selpw = sql.select(cmd);
		

		if (selpw > 0)
		{
			cout << "成功登录" << endl;
			free(cmd);
			return true;
		}
		else {
			sprintf_s(cmd, BUFFER_SIZE, "UPDATE Manager SET prem=prem+1 where name=\"%s\"", name.c_str());
			int upd = sql.update(cmd);
			cout << "请重新输入密码" << endl;
		}
	}
	cout << "失败" << endl;
	free(cmd);
	return false;
}


void ServiceImpl::addDept(void)//增加部门菜单项
{
	SQL sql("127.0.0.1", "root", "root", "EMIS", 3306);
	char* cmd = (char*)malloc(1024*sizeof(char));
	cout << "请输入部门名：";
	
	string name;
	cin >> name;

	cout << "请输入部门id：";
	int did;
	cin >> did;
	
	sprintf_s(cmd, BUFFER_SIZE, "insert into Department VALUES(%d,'%s',0)", did, name.c_str());
	

	int ins = sql.insert(cmd);

	if (0 == ins || ins == -1)
	{
		cout << "增加失败，请查看数据是否重复" << endl;
		_getch();
		_getch();
		free(cmd);
		return;
	}
	cout << "部门添加成功" << endl;
	_getch();
	_getch();
	free(cmd);
}
void ServiceImpl::deleteDept(void)//删除部门菜单项
{
	SQL sql("127.0.0.1", "root", "root", "EMIS", 3306);
	char* cmd = (char*)malloc(1024);

	cout << "请输入要删除的部门id：";
	int did;
	cin >> did;

	sprintf_s(cmd, BUFFER_SIZE, "DELETE FROM Department where did=%d", did);
	int del = sql.remove(cmd);
	if (0 >= del)
	{
		cout << "删除失败，请查看id是否正确" << endl;
		_getch();
		_getch();
		free(cmd);
		return;
	}

	sprintf_s(cmd, BUFFER_SIZE , "DELETE FROM Employee where did=%d", did);
	int del2 = sql.remove(cmd);
	if (del2 > 0)
	{
		cout << "该部门员工删除成功" << endl;
	}
	else
		cout << "该部门无员工" << endl;

	cout << "部门删除成功" << endl;
	_getch();
	_getch();
	free(cmd);
}
void ServiceImpl::listDept(void)//列出部门菜单项
{
	SQL sql("127.0.0.1", "root", "root", "EMIS", 3306);
	char* cmd = (char*)malloc(1024);
	sprintf_s(cmd, BUFFER_SIZE, "select did,name,num from Department");
	int sel = sql.select(cmd);

	cout << "      部门id   ";
	cout << "      部门名   ";
	cout << "    部门人数" << endl;
	sql.showResult();

	if (sel > 0)
	{
		cout << "输出完毕" << endl;
	}

	_getch();
	free(cmd);
}
void ServiceImpl::addEmp(void)//增加员工菜单项
{
	cout << "请输入部门编号：";
	int d_id = 0;
	cin >> d_id;

	SQL sql("127.0.0.1", "root", "root", "EMIS", 3306);
	char* cmd = (char*)malloc(1024);

	sprintf_s(cmd, BUFFER_SIZE, "select did from Department where did=%d", d_id);
	int sel = sql.select(cmd);
	if (sel <= 0)
	{
		cout << "sel:" << sel << endl;
		cout << "该部门不存在" << endl;
		_getch();
		free(cmd);
		return;
	}
	int eid;
	string name;
	int gender = 0;
	int age;
	cout << "请输入员工id：";
	cin >> eid;
	cout << "请输入员工姓名：";
	cin >> name;
	cout << "请选择员工性别(0,表示男，1，表示女),";

	switch (get_cmd('0', '1'))
	{
	case '0': gender = 0; break;
	case '1': gender = 1; break;
	}

	cout << "请输入员工年龄：";
	cin >> age;
	_getch();

	sprintf_s(cmd, BUFFER_SIZE, "insert into Employee VALUES(%d,'%s',%d,%d,%d)", eid, name.c_str(), gender, age, d_id);
	int ins = sql.insert(cmd);
	if (ins <= 0)
	{
		cout << "ins:" << ins << endl;
		cout << "数据有误，插入失败" << endl;
		_getch();
		free(cmd);
		return;
	}

	sprintf_s(cmd, BUFFER_SIZE, "select did from Employee where did=%d", d_id);
	int count = sql.select(cmd);
	cout << "现部门人数:" << count << endl;
	sprintf_s(cmd, BUFFER_SIZE, "UPDATE Department SET num=%d where did=%d", count, d_id);
	int upd = sql.update(cmd);
	if (upd > 0)
	{
		cout << "部门数据更新完毕" << endl;
	}

	cout << "员工添加成功" << endl;
	_getch();
	free(cmd);
}
void ServiceImpl::deleteEmp(void)//删除员工菜单项
{
	cout << "请输入员工编号:";
	int id = -1, did = -1;
	cin >> id;
	cout << "请输入员工的部门id:";
	cin >> did;
	_getch();

	SQL sql("127.0.0.1", "root", "root", "EMIS", 3306);
	char* cmd = (char*)malloc(1024);

	sprintf_s(cmd, BUFFER_SIZE, "select eid from Employee where eid=%d", id);
	int sel = sql.select(cmd);
	if (sel <= 0)
	{
		cout << "sel:" << sel << endl;
		cout << "该员工不存在,删除失败" << endl;
		_getch();
		return;
	}
	sprintf_s(cmd, BUFFER_SIZE, "select did from Department where did=%d", did);
	int sel2 = sql.select(cmd);
	if (sel2 <= 0)
	{
		cout << "sel2:" << sel2 << endl;
		cout << "该部门不存在,删除失败" << endl;
		_getch();
		return;
	}

	sprintf_s(cmd, BUFFER_SIZE, "DELETE FROM Employee where eid=%d", id);
	int del = sql.remove(cmd);
	if (del <= 0)
	{
		cout << "del:" << del << endl;
		cout << "输入数据有误,删除失败" << endl;
		_getch();
		return;
	}

	sprintf_s(cmd, BUFFER_SIZE, "select did from Employee where did=%d", did);
	int count = sql.select(cmd);
	cout << "现部门人数:" << count << endl;
	sprintf_s(cmd, BUFFER_SIZE, "UPDATE Department SET num=%d where did=%d", count, did);
	int upd = sql.update(cmd);
	if (upd > 0)
	{
		cout << "部门数据更新完毕" << endl;
	}

	cout << "删除员工成功" << endl;
	_getch();

}
void ServiceImpl::modifyEmp(void)//修改员工信息菜单项
{
	cout << "请输入员工编号:";
	int id = -1, old_did = -1;
	cin >> id;
	cout << "请输入员工的部门id:";
	cin >> old_did;

	SQL sql("127.0.0.1", "root", "root", "EMIS", 3306);
	char* cmd = (char*)malloc(1024);

	sprintf_s (cmd, BUFFER_SIZE, "select eid from Employee where eid=%d", id);
	int sel = sql.select(cmd);
	if (sel <= 0)
	{
		//cout << "selname:" << selname << endl;
		cout << "该员工不存在,修改失败" << endl;
		_getch();
		return;
	}
	sprintf_s(cmd, BUFFER_SIZE, "select did from Department where did=%d", old_did);
	int sel2 = sql.select(cmd);
	if (sel2 <= 0)
	{
		//cout << "selpw:" << selpw << endl;
		cout << "该部门不存在,修改失败" << endl;
		_getch();
		return;
	}

	string name;
	cout << "请输入员工的新姓名：";
	cin >> name;
	int gender = 0;
	cout << "请选择员工性别(0,表示男，1，表示女),";
	switch (get_cmd('0', '1'))
	{
	case '0': gender = 0; break;
	case '1': gender = 1; break;
	}

	cout << "请输入员工的新年龄：";
	int age = 0;
	cin >> age;

	cout << "请输入员工的新部门id：";
	int did = 0;
	cin >> did;

	_getch();

	sprintf_s(cmd, BUFFER_SIZE, "UPDATE Employee SET name='%s',gender=%d,age=%d,did=%d where eid=%d", name.c_str(), gender, age, did, id);
	int upd = sql.update(cmd);
	if (upd <= 0)
	{
		cout << "upd:" << upd << endl;
		cout << "输入数据有误，修改失败" << endl;
		_getch();
		return;
	}

	sprintf_s(cmd, BUFFER_SIZE, "select did from Employee where did=%d", did);
	int count = sql.select(cmd);
	cout << "现部门人数:" << count << endl;
	sprintf_s(cmd, BUFFER_SIZE, "UPDATE Department SET num=%d where did=%d", count, did);
	upd = sql.update(cmd);


	cout << "修改成功" << endl;
	_getch();
}
void ServiceImpl::listEmp(void)//列出部门员工菜单项
{
	int c_id;
	cout << "请输入部门编号:";
	cin >> c_id;
	SQL sql("127.0.0.1", "root", "root", "EMIS", 3306);
	char* cmd = (char*)malloc(1024);
	sprintf_s(cmd, BUFFER_SIZE, "select eid,name,gender,age,did from Employee where did=%d", c_id);
	int sel = sql.select(cmd);
	cout << "      员工id   ";
	cout << "      员工名   ";
	cout << "性别(0男1女)   ";
	cout << "        年龄   ";
	cout << "      部门id" << endl;
	sql.showResult();
	if (sel > 0)
	{
		cout << "输出完毕" << endl;
	}
	cout << endl;
	_getch();
	_getch();
}
void ServiceImpl::listAllEmp(void)//列出所有员工菜单项
{
	SQL sql("127.0.0.1", "root", "root", "EMIS", 3306);
	char* cmd = (char*)malloc(1024);
	sprintf_s(cmd, BUFFER_SIZE, "select eid,name,gender,age,did from Employee");
	int sel = sql.select(cmd);
	cout << "      员工id   ";
	cout << "      员工名   ";
	cout << "性别(0男1女)   ";
	cout << "        年龄   ";
	cout << "      部门id" << endl;
	sql.showResult();
	if (sel > 0)
	{
		cout << "输出完毕" << endl;
	}
	cout << endl;
	_getch();
}
