#include "managerview_console_impl.h"
#include "managerservice_impl.h"
#include <stdlib.h>
#include "tools.h"

void ManagerViewConsoleImpl::manager_sys(void)
{
	ManagerServiceImpl ms;
	if (!ms.login())
	{
		return;
	}
	while (1)
	{
		int sys = system("CLS");
		if (sys) {}
		ms.menu();//通过控制台显示主菜单
		switch (get_cmd('0', '4'))
		{
		case '1': ms.add(); break;
		case '2': ms.del(); break;
		case '3': ms.unf(); break;
		case '4': ms.list(); break;
		case '0':  return;
		}
		//getch();
	}
}