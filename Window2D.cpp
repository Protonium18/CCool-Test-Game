#include "Window2D.h"


Window2D::Window2D() {

}

Window2D::Window2D(short x, short y, short w, short h, char fillchar, WORD attribs) {
	width = w;
	height = h;
	drawRect = { x, y, x + width, y + height };
	for (int i = 0; i < 10000; i++) {
		text_buffer[i].Char.UnicodeChar = fillchar;
		text_buffer[i].Attributes = attribs;
		//std::cout << text_buffer[i].Attributes;
		//std::cout << text_buffer[i].Char.AsciiChar;
	}
	dwBuffer = { width, height };


}