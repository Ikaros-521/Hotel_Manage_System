#ifndef CLASS_H
#define CLASS_H

#include <iostream>
#include <string.h>

using namespace std;

class Customer
{
public:
	string name; //姓名
	string id; //身份证
	string family1; //家属1
	string family2; //家属2
	short floor; //楼层
	short room_num; //房间号
	short day; //时间
	Customer(string name="0",string id="0",string family1="0",string family2="0",short floor=0,short room_num=0,short day=0)
	{
		this->name = name;
		this->id = id;
		this->family1 = family1;
		this->family2 = family2;
		this->floor = floor;
		this->room_num = room_num;
		this->day = day;
	}
};

class Room
{
public:
	short floor; //楼层
	short room_num; //房间号
	short room_type; //房间类型
	short price; //价格
	short use; //是否使用
	Room(short floor=0,short room_num=0,short room_type=0,short price=0,short use=0)
	{
		this->floor = floor;
		this->room_num = room_num;
		this->room_type = room_type;
		this->price = price;
		this->use = use;
	}

};


#endif//CLASS_H
