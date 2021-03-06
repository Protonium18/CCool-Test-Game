#include "Tile.h"


Tile::Tile(){
	int v = 10;
	if (rand() % 20 == 1) {
		is_solid = true;
		character = 'X';
		attribs = C_LIGHTGRAY;
	}
	else {
		if (rand() % 500 == 1) {
			inventory.push_back(new Item("items/Text.txt"));
		}
		is_occupied = false;
		is_solid = false;
	}
}

Tile::Tile(int input) {
	switch (input) 
	{
		case 0:
			character = ' ';
			is_solid = true;
			attribs = 0x00FF;
			break;

		case 1:
			is_solid = false;
			character = '-';
			attribs = C_GREEN;
			break;

	}
		
}

void Tile::entAppend(Entity* ent) {
	occupying_ent = ent;
	is_occupied = true;
}

void Tile::entRemove(){
	occupying_ent = nullptr;
	is_occupied = false;
}

bool Tile::isOccupied() {
	return is_occupied;

}

bool Tile::isSolid() {
	return is_solid;

}

Entity* Tile::getEnt() {
	return occupying_ent;
}

char Tile::getChar() {
	return character;
}

WORD Tile::getAttribs() {
	return attribs;
}

Item* Tile::getInvItem(int pos) {
	return inventory.at(pos);
}

std::vector<Item*>* Tile::getInv() {
	return &inventory;
}

void Tile::removeInvItem(int pos) {
	inventory.erase(inventory.begin()+pos);
}