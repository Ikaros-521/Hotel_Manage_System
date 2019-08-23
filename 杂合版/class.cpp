#include <iostream>
#include <fstream>
#include "tools.h"
#include "class.h"

using namespace std;

Customer* cust[30];
Room* room[30];

void menu(void);	// 菜单
int room_index(short room_num);	// 房间下标
int cust_index(short room_num); // 顾客下标
void find_room(void);	// 剩余房间
void get_room(void);	// 开房
int used(short room_num);	// 房间使用情况
void show_cust(void);	// 显示入住顾客
int room_price(short room_num);	// 房间价格
void renew_room(void);	// 续费
void cancel_room(void);	// 退房
void c_init(void);	// 顾客初始化
void r_init(void);	// 房间初始化
void save_data(void);	// 保存数据

short live = 0; // 被订房间数

// 主函数
int main()
{
	c_init();
	r_init();
	while(1)
	{
		menu();
		switch(get_cmd('0','4'))
		{
			case '1': find_room(); break;
			case '2': get_room(); break;
			case '3': renew_room(); break;
			case '4': cancel_room(); break;
			case '0': save_data(); return 0;
		}
	}
	
}

// 返回房间的下标
int room_index(short room_num)
{
	short num = room_num;
	for(int i=0; i<30; i++)
	{
		if(num == room[i]->room_num)
		{
			return i;
		}
	}
	return -1;
}

// 返回顾客的下标
int cust_index(short room_num)
{
	short num = room_num;
	for(int i=0; i<30; i++)
	{
		if(num == cust[i]->room_num)
		{
			return i;
		}
	}
	return -1;
}

// 查询剩余房间
void find_room(void)
{
	for(int i=0; i<30; i++)
	{
		if(i == 10 || i == 20)
		{
			cout << endl;
		}
		if(room[i]->use != 0)
		{
			continue;
		}
		cout << room[i]->room_num << " ";
	}
	cout << endl;
}

// 开房
void get_room(void)
{
	cout << "现有房间如下" << endl;
	find_room();
	
//	cout << "已经入住的人员" << endl;
//	show_cust();

	cout << "请输入您选择的房间:";
	short room_num;
	cin >> room_num;
	int flag = used(room_num);
	if(flag == 1)
	{
		cout << "此房间不能使用，请重新选择" << endl;
		return;
	}
	else if(flag == -1)
	{
		cout << "此房间不存在，请重新选择" << endl;	
		return;
	}
	else
	{
		cout << "您选择的房间是:" << room_num << endl;
	}

	int index = room_index(room_num);
	short type = room[index]->room_type;

	cout << "请输入您的姓名:";
	string name;
	cin >> name;
	cout << "请输入您的身份证:";
	string id;
	cin >> id;
	cout << "请输入您的2位家属(0，表示没有)" << endl;
	string family1,family2;
	cin >> family1 >> family2;

	if(type == 1)
	{
		if(family1 != "0" || family2 != "0")
		{
			cout << "人数过多，开房失败" << endl;
			return;
		}
	}
	else if(type == 2)
	{
		if(family1 != "0" && family2 != "0")
		{
			cout << "人数过多，开房失败" << endl;
			return;
		}
	}
	else
	{
	}

	cout << "请输入要订的天数:";
	short day;
	cin >> day;
	short pay = day*room[index]->price;
	cout << "请支付" << pay << "元" << endl;
	short money = 0,change = 0;
	cout << "收您：";
	cin >> money;
	cout << "元" << endl;
	change = money-pay;
	if(change < 0)
	{
		cout << "余额不足，请充值" << endl;		
		return;
	}
	cout << "找您" << change << "元" << endl;

	short floor = room_num/100;

	cust[live++] = new Customer(name,id,family1,family2,floor,room_num,day);

	cout << "已订房间:" << live << endl;

	for(int i=0; i<30; i++)
	{
		if(room[i]->room_num == room_num)
		{
			room[i]->use = 1;
		}
	}

	cout << "开房成功,欢迎您的入住，祝你生活愉快!" << endl;
}

// 使用情况
int used(short room_num)
{
	short num = room_num;
	for(int i=0; i<30; i++)
	{
		if(num == room[i]->room_num)
		{
			if(room[i]->use == 1)
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
	}
	return -1;
}

// 显示顾客
void show_cust(void)
{
	for(int i=0; i<30; i++)
	{
		if(cust[i]->name == "0")
		{
			break;
		}
		else
		{
			cout << "姓名:" << cust[i]->name << "," << "房间:" << cust[i]->room_num << ",";

			string f1,f2;
			f1 = cust[i]->family1;
			f2 = cust[i]->family2;
			cout << "家属1:";
			if(f1 == "0") cout << " ,";
			else cout << f1 << ",";
			cout << "家属2:";
			if(f2 == "0") cout << " ";
			else cout << f2;
		}
	}
}

// 房间价格
int room_price(short room_num)
{
	short num = room_num;
	for(int i=0; i<30; i++)
	{
		if(room[i]->room_num == num)
		{
			return room[i]->price;
		}
	}
	return 0;
}

// 续费
void renew_room(void)
{
	cout << "请输入你的房间号:";
	short room_num;
	cin >> room_num;
	int flag = used(room_num);
	if(flag == -1 || flag == 0)
	{
		cout << "您输入的房间号有误" << endl;
		return;
	}

	int index = cust_index(room_num);

	cout << "您的房间剩余:" << cust[index]->day << "天" << endl;

	cout << "请输入你要续的天数：";
	short day;
	cin >> day;
	short pay = day*room_price(room_num);
	cout << "请支付" << pay << "元" << endl;
	short price = 0,change = 0;
	cin >> price;
	change = price-pay;
	if(change < 0)
	{
		cout << "余额不足，请充值" << endl;
		return;
	}
	cout << "收您" << price <<"元，找您" << change << "元" << endl;

	string rename = cust[index]->name,reid = cust[index]->id;
	string refamily1=cust[index]->family1,refamily2=cust[index]->family2;
	short refloor = cust[index]->floor,reday = cust[index]->day+day;
	cust[index] = new Customer(rename,reid,refamily1,refamily2,refloor,room_num,reday);
	
	cout << "续费成功，房间的使用时间为:" << reday <<"天" << endl;

}

// 退房
void cancel_room(void)
{
	cout << "请输入您的房间号:";
	short room_num;
	string name;
	cin >> room_num;
	cout << "请输入您的姓名:";
	cin >> name;
	int flag = used(room_num);
	if(flag == 0 || flag == -1)
	{
		cout << "您输入的房间有误。" << endl;
		return;
	}
	else
	{
		short refloor = 0,retype = 0,reprice = 0;

		int i = cust_index(room_num);
		if(i != -1)
		{
			if(cust[i]->name == name)
			{
				short price = room[room_index(room_num)]->price;
				short change = cust[i]->day*price;
				cout << "退还您" << change << "元" << endl;

				cust[i] = new Customer("0","0","0","0",0,0,0);
				int j = room_index(room_num);
				refloor = room[j]->floor;
				retype = room[j]->room_type;
				reprice = room[j]->price;
				room[j] = new Room(refloor,room_num,retype,reprice,0);

				cout << "退房成功，感谢您的光顾，欢迎下次光临！"<< endl;
				live--;
				return;
			}
			else
			{
				//cout << cust[i]->name << endl;
				cout << "您输入的相关信息有误" << endl;
				return;
			}
		}
		else
		{
			cout << "您输入的信息有误" << endl;
			return;
		}
	}
}

void c_init(void)
{
	fstream ci("data/cust.txt",ios::in);
	if(!ci.good())
	{
		cout << "cust.txt数据加载异常" << endl;
	}

	for(int i=0; i<30; i++)
	{
		string name,id,family1,family2;
		short floor,room_num,day;
		ci >> name >> id >> family1 >> family2;
		ci >> floor >> room_num >> day;
		cust[i] = new Customer(name,id,family1,family2,floor,room_num,day);
		if(name != "0")
		{
			live++;
		}
	}
}

void r_init(void)
{
	fstream ri("data/room.txt",ios::in);
	if(!ri.good())
	{
		cout << "room.txt数据加载异常" << endl;
	}

	for(int i=0; i<30; i++)
	{
		short floor,room_num,room_type,price,use;
		ri >> floor >> room_num;
		ri >> room_type >> price >> use;
		room[i] = new Room(floor,room_num,room_type,price,use);		
	}
}

void save_data(void)
{
	fstream co("data/cust.txt",ios::out);
	fstream ro("data/room.txt",ios::out);

	for(int i=0; i<30; i++)
	{
		co << cust[i]->name << " " << cust[i]->id << " ";
		co << cust[i]->family1 << " " << cust[i]->family2 << " ";
		co << cust[i]->floor << " " << cust[i]->room_num << " ";
		co << cust[i]->day << "\n";

		ro << room[i]->floor << " " << room[i]->room_num << " ";
		ro << room[i]->room_type << " " << room[i]->price << " ";
		ro << room[i]->use << "\n";
	}
}

void menu(void)
{
	cout << "***欢迎使用酒店管理系统***" << endl;
	cout << "   1、查询房间" << endl;
	cout << "   2、开房" << endl;
	cout << "   3、续费" << endl;
	cout << "   4、退房" << endl;
	cout << "   0、退出系统" << endl;
	cout << "-----------------------" << endl;
}

