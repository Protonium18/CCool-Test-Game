#ifndef WINDOWS2D_H
#define WINDOWS2D_H

#include <windows.h>

class Window2D
{
	public:
		Window2D();
		Window2D(short x, short y, short w, short h, char fillchar = 'V', WORD attribs = 0x0010);
		short width;
		short height;
		COORD dwBuffer;
		COORD dwbuffercoord = { 0,0 };
		CHAR_INFO* text_buffer = new CHAR_INFO[10000];
		SMALL_RECT drawRect;

	private:
		short pos_x;
		short pos_y;
};

#endif