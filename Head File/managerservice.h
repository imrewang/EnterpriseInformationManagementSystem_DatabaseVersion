#ifndef MANAGERSERVICE_H
#define MANAGERSERVICE_H

#include <iostream>

using namespace std;

class ManagerService
{
public:
	virtual bool login(void) = 0;//��������Ա��½
	virtual void menu(void) = 0;//ͨ������̨��ʾ���˵�
	virtual void add(void) = 0;//ͨ������̨�������ӹ���Ա�˵���
	virtual void del(void) = 0;//ͨ������̨����ɾ������Ա�˵���
	virtual void unf(void) = 0;//ͨ������̨����ⶳ����Ա�˵���
	virtual void list(void) = 0;//ͨ������̨�����г����й���Ա�˵���
};

#endif//MANAGERSERVICE_H