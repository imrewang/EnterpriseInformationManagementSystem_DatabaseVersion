#include <iostream>
#include <stdlib.h>
#include "tools.h"
#include "service_impl.h"
#include "serviceview_console_impl.h"
#include "managerservice_impl.h"
#include "managerview_console_impl.h"

using namespace std;

void menu(void)
{
	cout << "****��ҵ��Ϣ����ϵͳ****" << endl;
	cout << "    1.������ϵͳ" << endl;
	cout << "    2.ҵ����ϵͳ" << endl;
	cout << "    0.�˳�ϵͳ" << endl;
	cout << "______________________" << endl;
}

int main()
{
	ServiceViewConsoleImpl sv;
	ManagerViewConsoleImpl mv;
	while (1)
	{
		int sys = system("CLS");
		if (sys) {}
		menu();
		
		
		switch (get_cmd('0', '2'))
		{
		case '1': mv.manager_sys(); break;
		case '2': sv.service_sys(); break;
		case '0': return 0;
		}
		_getch();
	}
}


