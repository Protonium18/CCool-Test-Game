#include "Tile.h"

Tile::Tile(){
	int v = 10;
	is_occupied = false;
	is_solid = false;
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