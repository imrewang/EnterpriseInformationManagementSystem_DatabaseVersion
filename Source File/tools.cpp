#include "tools.h"
#include <string.h>
#include <stdbool.h>

#include <iostream>

using namespace std;

void clear_stdin(void)
{
	//stdin->_IO_read_ptr = stdin->_IO_read_end;//清理输入缓冲区
	//cin.ignore(std::numeric_limits< streamsize >::max(), '\n');
	cin.clear();
	cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
}

char get_cmd(char start, char end)
{
	//clear_stdin();

	printf("请输入指令:");
	while (true)
	{
		char val = _getch();
		if (val >= start && val <= end)
		{
			printf("%c\n", val);
			return val;
		}
	}
}

char* get_pw(char* passwd, bool is_show, size_t size)
{
	if (NULL == passwd) return NULL;

	unsigned int count = 0;
	do {
		char val = _getch();
		if (127 == val)
		{
			if (count > 0)
			{
				if (is_show)printf("\b \b");
				count--;
			}
			continue;
		}
		else if (10 == val)
		{
			break;
		}
		passwd[count++] = val;
		if (is_show) printf("get_pw*");
	} while (count < size - 1);

	passwd[count] = '\0';
	return passwd;
}