#ifndef TILE_H
#define TILE_H

#include <windows.h>
#include <vector>
#include <stdlib.h>

#include "Defs.h"
#include "Entity.h"
#include "Item.h"


class Item;
class Entity;

class Tile
{
	public:
		Tile();
		Tile(int input);
		int id;
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
		bool is_occupied = false;
		bool is_solid;
		char character = '~';
		WORD attribs = C_GREEN;
		std::vector<Item*> inventory;

};

#endif // TILE_H
