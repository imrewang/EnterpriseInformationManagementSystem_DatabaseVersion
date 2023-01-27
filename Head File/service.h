#ifndef SERVICE_H
#define SERVICE_H

class Service
{
public:
	virtual bool manager_login(void) = 0;
	virtual void menu(void) = 0;//��ʾ��Ӫ�����Ӳ˵�
	virtual void addDept(void) = 0;//���Ӳ��Ų˵���
	virtual void deleteDept(void) = 0;//ɾ�����Ų˵���
	virtual void listDept(void) = 0;//�г����Ų˵���
	virtual void addEmp(void) = 0;//����Ա���˵���
	virtual void deleteEmp(void) = 0;//ɾ��Ա���˵���
	virtual void modifyEmp(void) = 0;//�޸�Ա����Ϣ�˵���
	virtual void listEmp(void) = 0;//�г�����Ա���˵���
	virtual void listAllEmp(void) = 0;//�г�����Ա���˵���
};

#endif//SERVICE_H
