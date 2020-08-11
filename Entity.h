#ifndef ENTITY_H
#define ENTITY_H

#include "Tile.h"
#include "Structs.h"
#include "Item.h"
#include "Window2D.h"
#include <vector>
#include <string>
#include "Functions.h"

class Window2D;
class Tile;
class Item;
struct VecMap2D;
struct Coord2D;

class Entity
{
	public:
		
		Entity(std::vector<std::vector<Tile>>* rarray, Window2D* activewindow, int x, int y, char charinput = '&', std::string name_in = "Default");
		void TileMove(std::vector<std::vector<Tile>>* rarray, int x_offset, int y_offset);
		int getCurrentPosX();
		int getCurrentPosY();
		int getHP();
		void takeDamage(int damage);
		void Attack(Entity* target);
		Coord2D getCoords();
		Coord2D getOldCoords();
		char character;
		Item* equipped_item;
		void takeItem(int pos);
		int operator+(Entity);


	private:
		std::string name;
		int hp;
		int pos_x;
		int pos_y;
		int old_pos_x;
		int old_pos_y;
		Tile* occupied_tile;
		std::vector<Item*> inventory;
		Window2D* active_window;
};
#endif // ENTITY_H

