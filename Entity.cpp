#include "Entity.h"

#include <iostream>
#include "Structs.h"
#include "Item.h"
#include "Window2D.h"
#include "Functions.h"
#include <vector>

Entity::Entity(std::vector<std::vector<Tile>>* rarray, Window2D* activewindow, int x, int y, char charinput) {
	rarray->at(x).at(y).entAppend(this);
	pos_x = x;
	pos_y = y;
	occupied_tile = &rarray->at(x).at(y);
	hp = 100;
	character = charinput;
	/*Item fists;
	inventory[0] = &fists;*/
	equipped_item = &inventory[0];
	active_window = activewindow;
}

void Entity::TileMove(std::vector<std::vector<Tile>>* rarray, int x_offset, int y_offset) {
	int new_pos_x = pos_x + x_offset;
	int new_pos_y = pos_y + y_offset;

	if (new_pos_x > -1 && new_pos_y > -1 && new_pos_x < rarray->size() && new_pos_y < rarray->at(0).size() ) {
		Tile* tile_new = &rarray->at(new_pos_y).at(new_pos_x);
		if (tile_new->isOccupied() == false && tile_new->isSolid() == false) {

			occupied_tile->entRemove();
			tile_new->entAppend(this);

			occupied_tile = tile_new;
			old_pos_x = pos_x;
			old_pos_y = pos_y;
			fct::buffWrite(active_window, old_pos_x, old_pos_y, occupied_tile->getChar(), occupied_tile->getAttribs());
			fct::buffWrite(active_window, new_pos_x, new_pos_y, character);
			pos_x = new_pos_x;
			pos_y = new_pos_y;
		}

		else if (tile_new->isOccupied() == true) {
			Attack(tile_new->getEnt());
		}

		else if (tile_new->isSolid() == true) {

		}

		else {
			std::wcout << "Invalid tile." << std::endl;
		}
	}
	else {
		std::cout << "Invalid tile!" << std::endl;
	}
}

int Entity::getCurrentPosX(){
	return pos_x;
}
	
int Entity::getCurrentPosY(){
	return pos_y;
}

int Entity::getHP() {
	return hp;
}

void Entity::Attack(Entity* target) {
	target->takeDamage(this->equipped_item->damage);
	std::wcout << this->equipped_item->damage;
}

void Entity::takeDamage(int damage) {
	hp-=damage;
	if (hp <= 0) {
		std::wcout << "Destroyed!" << std::endl;
		occupied_tile->entRemove();
	}
}

Coord2D Entity::getCoords() {
	Coord2D EntCoords = { pos_x, pos_y };
	return EntCoords;
}

Coord2D Entity::getOldCoords() {
	Coord2D returnCoords = { old_pos_x, old_pos_y };
	return returnCoords;
}