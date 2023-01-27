#include "managerservice_impl.h"
#include <fstream>
#include <stdio.h>
#include <iomanip>
#include <stdlib.h>
#include "tools.h"
#include "emis.h"

using namespace std;

//超级管理员登陆
bool ManagerServiceImpl::login(void)
{
	string a_name = "admin";
	string a_password = "admin";
	cout << "请输入用户名：";
	string name;
	cin >> name;

	cout << "请输入密码：";
	string password;
	cin>>password;
	cout << endl;



	if (name == a_name && password == a_password)
	{
		cout << "登陆成功" << endl;
		_getch();
		return true;
	}
	else
	{
		cout << "用户名或密码错误" << endl;
		return false;
	}
}


//通过控制台显示主菜单
void ManagerServiceImpl::menu(void)
{
	cout << "****企业信息管理系统****" << endl;
	cout << "    1.增加管理员" << endl;
	cout << "    2.删除管理员" << endl;
	cout << "    3.解冻管理员" << endl;
	cout << "    4.列出所有管理员" << endl;
	cout << "    0.退出子系统" << endl;
	cout << "______________________" << endl;
}


//通过控制台处理增加管理员菜单项
void ManagerServiceImpl::add(void)
{
	SQL sql("127.0.0.1", "root", "123zxcvbnm", "EMIS", 3306);
	char* cmd = (char*)malloc(1024);

	cout << "请输入管理员id：";
	int add_m_id;
	cin >> add_m_id;
	cout << "请输入管理员用户名：";
	string add_n;
	cin >> add_n;
	cout << "请输入管理员密码：";
	string add_pw;
	cin >> add_pw;

	sprintf_s(cmd, BUFFER_SIZE, "INSERT INTO Manager VALUES(%d,'%s','%s',0)", add_m_id, add_n.c_str(), add_pw.c_str());
	int ins = sql.insert(cmd);
	if (0 == ins || ins == -1)
	{
		cout << "增加失败，请查看数据是否重复" << endl;
		_getch();
		_getch();
		return;
	}


	cout << "管理员添加成功" << endl;
	_getch();
	_getch();
}


//通过控制台处理删除管理员菜单项
void ManagerServiceImpl::del(void)
{
	SQL sql("127.0.0.1", "root", "123zxcvbnm", "EMIS", 3306);
	char* cmd = (char*)malloc(1024);

	cout << "请输入要删除的管理员id：";
	int del_mid;
	cin >> del_mid;


	sprintf_s(cmd, BUFFER_SIZE, "DELETE FROM Manager where mid=%d", del_mid);
	int del = sql.remove(cmd);
	if (0 == del || del == -1)
	{
		cout << "删除失败，请查看id是否正确" << endl;
		_getch();
		_getch();
		return;
	}
	cout << "管理员删除成功" << endl;

	_getch();
	_getch();
}


//通过控制台处理解冻管理员菜单项
void ManagerServiceImpl::unf(void)
{
	SQL sql("127.0.0.1", "root", "123zxcvbnm", "EMIS", 3306);
	char* cmd = (char*)malloc(1024);
	memset(cmd, 0, BUFFER_SIZE);

	
	cout << "请输入要解冻的管理员id：";
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
		cout << "解冻失败，请查看id是否正确" << endl;
		_getch();
		free(cmd);
		return;
	}
	cout << "    管理员id   ";
	cout << "管理员用户名   ";
	cout << "    管理员锁" << endl;
	sql.showResult();

	sprintf_s(cmd, BUFFER_SIZE, "UPDATE Manager SET prem=0 where mid=%d", unf_mid);
	int upd = sql.update(cmd);
	
	if (upd > 0)
	{
		cout << "管理员解冻成功" << endl;
	}
	
	
	_getch();
	free(cmd);
}


//通过控制台处理列出所有管理员菜单项
void ManagerServiceImpl::list(void)
{
	SQL sql("127.0.0.1", "root", "123zxcvbnm", "EMIS", 3306);
	char* cmd = (char*)malloc(1024);
	sprintf_s(cmd, BUFFER_SIZE, "select mid,name,prem from Manager");
	int sel = sql.select(cmd);
	cout << "    管理员id   ";
	cout << "管理员用户名   ";
	cout << "    管理员锁" << endl;
	sql.showResult();
	if (sel > 0)
	{
		cout << "输出成功" << endl;
	}

	_getch();
}