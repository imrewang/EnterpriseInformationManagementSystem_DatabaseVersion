#ifndef SERVICEIMPL_H
#define SERVICEIMPL_H

#include "service.h"

class ServiceImpl :public Service
{
public:
	ServiceImpl();
	bool manager_login(void);
	void menu(void);//��ʾ��Ӫ�����Ӳ˵�
	void addDept(void);//���Ӳ��Ų˵���
	void deleteDept(void);//ɾ�����Ų˵���
	void listDept(void);//�г����Ų˵���
	void addEmp(void);//����Ա���˵���
	void deleteEmp(void);//ɾ��Ա���˵���
	void modifyEmp(void);//�޸�Ա����Ϣ�˵���
	void listEmp(void);//�г�����Ա���˵���
	void listAllEmp(void);//�г�����Ա���˵���
};

#endif//SERVICEIMPL_H