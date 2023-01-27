# EnterpriseInformationManagementSystem

# 企业信息管理系统

## 一、简介

使用C++与MySQL完成简单的企业信息管理系统

## 二、部署

### （一）准备工作

语言：C++

数据库：MySQL

编译器：Visual Studio 2019

数据库软件：MySQL 8.0

[使用C++访问MySQL数据库](https://www.cnblogs.com/imreW/p/16988548.html)

### （二）建立数据库

数据库使用的MySQL，root创建 EMIS数据库，相应的表Manager，Department，Employee等可查看源码

超级管理员 账号admin 密码admin

~~~
用户 root
数据库 EMIS
表名 Manager，Department，Employee
Manager     mid,name,password,prem
Department  did,name,num
Employee    eid,name,gender,age,did
~~~

具体建表代码参考

~~~
create database EMIS;
use EMIS;
create table Employee(eid int,name varchar(20),gender int,age int,did int);
create table Department(did int,name varchar(40),num int);
create table Manager(mid int,name varchar(40),password varchar(20),prem int);
~~~



### （三）部署截图



## 四、运行截图



## 五、总结

### （一）连接数据库问题

解决方案：[使用C++访问MySQL数据库](https://www.cnblogs.com/imreW/p/16988548.html)

效果：成功连接

### （二）MySQL使用问题

解决方案：编写sql.h,sql.cpp

效果：减少了以后使用的麻烦

## 六、改进

### （一）sql.h,sql.cpp

sql.h,sql.cpp还不完善，没有创建数据库等操作，只有简单增删改查

