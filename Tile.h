#ifndef TILE_H
#define TILE_H

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

	private:
		Entity* occupying_ent;
		bool is_occupied;
		bool is_solid;

};

#endif // TILE_H
