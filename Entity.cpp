#include "Entity.h"

Entity::Entity(std::vector<std::vector<Tile>>* rarray, Window2D* activewindow, int x, int y, char charinput, std::string in_name)
	: pos_x(x), pos_y(y), hp(100), character(charinput), occupied_tile(&rarray->at(x).at(y)), active_window(activewindow), name(in_name)
{
	rarray->at(x).at(y).entAppend(this);
	inventory.push_back(new Item(&fct::openFile("items/Text.txt")));
	equipped_item = inventory.at(0);
}

bool Entity::TileMove(std::vector<std::vector<Tile>>* rarray, int x_offset, int y_offset) {
	int new_pos_x = pos_x + x_offset;
	int new_pos_y = pos_y + y_offset;

	if (new_pos_x > -1 && new_pos_y > -1 && new_pos_x < rarray->size() && new_pos_y < rarray->at(0).size() ) {
		Tile* tile_new = &rarray->at(new_pos_x).at(new_pos_y);
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
			
			if (occupied_tile->getInv()->size() > 0) {
				std::cout << "Items here!" << std::endl;
			}
			return true;
		}

		else if (tile_new->isOccupied() == true) {
			Attack(tile_new->getEnt());
			return false;
		}

		else if (tile_new->isSolid() == true) {
			return false;
		}

		else {
			return false;
			std::wcout << "Invalid tile." << std::endl;
		}
	}
	else {
		return false;
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
	std::cout << pos_x << std::endl;
	std::cout << pos_y << std::endl;
	return EntCoords;
}

Coord2D Entity::getOldCoords() {
	Coord2D returnCoords = { old_pos_x, old_pos_y };
	return returnCoords;
}

void Entity::takeItem(int pos) {
	if (occupied_tile->getInv()->size() > 0 && pos < occupied_tile->getInv()->size()) {
		inventory.push_back(occupied_tile->getInvItem(pos));
		occupied_tile->removeInvItem(pos);
		std::cout << "Item taken!" << std::endl;
	}
	else {
		std::cout << "No items!" << std::endl;
	}
}

int Entity::operator+(Entity ent) {
	std::cout << hp + ent.getHP() << std::endl;
	return hp + ent.getHP();
}