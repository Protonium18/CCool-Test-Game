#ifndef ITEM_H
#define ITEM_H

#include <iostream>
#include <string>
#include <windows.h>
#include <fstream>


class Item
{
	public:
		Item(std::string in_name = "Generic", int dmg = 20, int rangevar = 5);
		Item(std::ifstream* in_file);
		std::string name;
		int damage;
		int range_var;
		WORD getColor();
	private:
		WORD color;
};

#endif
