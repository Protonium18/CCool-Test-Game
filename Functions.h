#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string>
#include <windows.h>
#include <fstream>
#include <iostream>

#include "Window2D.h"
#include "Structs.h"

class Window2D;
struct StrShape2D;

namespace fct {

	void buffWrite(Window2D* window, int pos_x, int pos_y, char character, WORD attrib = 0x0001);
	void buffWrite(Window2D* window, int pos_x, int pos_y, std::string instring, WORD attrib = 0x0001);
	void buffWrite(Window2D* window, int pos_x, int pos_y, StrShape2D inshape, WORD attrib = 0x0001);
	StrShape2D RectCreate(int x_dim, int y_dim, char borderChar);
	std::ifstream openFile(std::string inputname);

}

#endif

