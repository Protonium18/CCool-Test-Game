#ifndef TILE_H
#define TILE_H

#include <windows.h>
#include <vector>
#include "Entity.h"
#include "Item.h"


class Item;
class Entity;

class Tile
{
	public:
		Tile();
		int id = 40;
		void entAppend(Entity* ent);
		void entRemove();
		bool isOccupied();
		bool isSolid();
		Entity* getEnt();
		char getChar();
		WORD getAttribs();
		Item* getInvItem(int pos);
		std::vector<Item*>* getInv();
		void removeInvItem(int pos);

	private:
		Entity* occupying_ent;
		bool is_occupied;
		bool is_solid;
		char character = '-';
		WORD attribs = 0x0002;
		std::vector<Item*> inventory;

};

#endif // TILE_H
