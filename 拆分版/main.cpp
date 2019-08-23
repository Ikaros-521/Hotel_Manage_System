#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <termio.h>
#include "class.h"
#include "tools.h"

using namespace std;

Manage admin;

// 主函数
int main()
{
	admin.c_init();
	admin.r_init();
	while(1)
	{
		system("clear");
		admin.menu();
		switch(get_cmd('0','4'))
		{
			case '1': admin.find_room(); break;
			case '2': admin.get_room(); break;
			case '3': admin.renew_room(); break;
			case '4': admin.cancel_room(); break;
			case '0': admin.save_data(); return 0;
		}
		getch();
	}
	
}

