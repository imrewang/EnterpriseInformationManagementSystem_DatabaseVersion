#ifndef MANAGERSERVICE_IMPL_H
#define MANAGERSERVICE_IMPL_H

#include <iostream>
#include <string.h>
#include "managerservice.h"

class ManagerServiceImpl :public ManagerService
{
public:
	bool login(void);//��������Ա��½
	void menu(void);//ͨ������̨��ʾ���˵�
	void add(void);//ͨ������̨�������ӹ���Ա�˵���
	void del(void);//ͨ������̨����ɾ������Ա�˵���
	void unf(void);//ͨ������̨����ⶳ����Ա�˵���
	void list(void);//ͨ������̨�����г����й���Ա�˵���
};

#endif//MANAGERSERVICE_IMPL_H