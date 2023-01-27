#include "serviceview_console_impl.h"
#include <stdlib.h>
#include<iostream>

using namespace std;


void ServiceViewConsoleImpl::service_sys(void)
{
	ServiceImpl si;
	if (!si.manager_login())
	{
		cout << "µÇÂ½Ê§°Ü" << endl;
		return;
	}
	cout << 111 << endl;
	while (1)
	{
		int sys = system("cls");
		if (sys > 0) {}
		si.menu();
		switch (get_cmd('0', '8'))
		{
		case '1': si.addDept(); break;
		case '2': si.deleteDept(); break;
		case '3': si.listDept(); break;
		case '4': si.addEmp(); break;
		case '5': si.deleteEmp(); break;
		case '6': si.modifyEmp(); break;
		case '7': si.listEmp(); break;
		case '8': si.listAllEmp(); break;
		case '0':  return;
		}
	}
}
