#ifndef STRUCTS_H
#define STRUCTS_H
#include <string>
#include <windows.h>

struct Coord2D {
    int x;
    int y;
};

struct StrShape2D {
    std::string content;
    int width = 1;
    int height = 1;

};

struct ConWindow2D {
    CHAR_INFO text_buffer[400];
    COORD dwBuffer = {20, 20};
    COORD dwbuffercoord = { 0,0 };
    SMALL_RECT drawRect;

};


#endif
