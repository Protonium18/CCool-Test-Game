#ifndef TILE_H
#define TILE_H

#include <windows.h>
#include "Entity.h"


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

	private:
		Entity* occupying_ent;
		bool is_occupied;
		bool is_solid;
		char character = '-';
		WORD attribs = 0x0002;

};

#endif // TILE_H
