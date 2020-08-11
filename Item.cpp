#include "Item.h"

Item::Item(std::string in_name, int dmg, int rangevar)
	: damage(dmg), range_var(rangevar), name(in_name)
{
	color = 0x0001;

}

Item::Item(std::ifstream* in_file) {
	if (in_file->is_open()) {
		std::string str;
		std::string str_array[10];
		int i = 0;

		while (std::getline(*in_file, str)) {
			str_array[i] = str;
			i++;
		}
		name = str_array[0];
		damage = std::stoi(str_array[1]);
		range_var = std::stoi(str_array[2]);

		in_file->close();
		

	}
	else {
		std::cout << "Issue reading file." << std::endl;
	}
}

WORD Item::getColor() {
	return color;
}