#ifndef ENTITY_H
#define ENTITY_H

#include "Tile.h"
#include "Structs.h"
#include "Item.h"

class Tile;

class Entity
{
	public:
		
		Entity(Tile (&rarray)[400], int x, int y, int width, char charinput = '&');
		void TileMove(Tile (&rarray)[400], int width, int x_offset, int y_offset);
		int getCurrentPosX();
		int getCurrentPosY();
		int getHP();
		void takeDamage(int damage);
		void Attack(Entity* target);
		Coord2D getCoords();
		Coord2D getOldCoords();
		char character;
		Item* equipped_item;


	private:
		int hp;
		int pos_x;
		int pos_y;
		int old_pos_x;
		int old_pos_y;
		Tile* occupied_tile;
		Item inventory[9];
};

#endif // ENTITY_H