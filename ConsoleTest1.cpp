#include <iostream>
#define _WIN32_WINNT 0x0500
#include <windows.h>
#include<string>
#include<chrono>
#include<thread>
#include <conio.h>
#include <vector>
#include <algorithm>
#include <ctime>


#include "Tile.h"
#include "Entity.h"
#include "Structs.h"

using namespace std;

Tile g_map_array[400];
std::vector<Entity*> g_ent_table;

template<int l>
void buffWrite(CHAR_INFO (&buffer)[l], int pos_x, int pos_y, int width, char character, WORD attrib = 0x0001) {
    buffer[pos_y * width + pos_x].Char.UnicodeChar = character;
    buffer[pos_y * width + pos_x].Attributes = attrib;

}

template<int l>
void buffWrite(CHAR_INFO(&buffer)[l], int pos_x, int pos_y, int width, string instring, WORD attrib = 0x0001) {
    int strLength = instring.length();
    for (int i = 0; i < strLength; i++) {
        buffer[pos_y * width + pos_x+i].Char.UnicodeChar = instring[i];
        buffer[pos_y * width + pos_x+i].Attributes = attrib;
    }
}

template<int l>
void buffWrite(CHAR_INFO(&buffer)[l], int pos_x, int pos_y, int width, StrShape2D inshape, WORD attrib = 0x0001) {
    int in_width = inshape.width;
    int in_height = inshape.height;
    int v = 0;



    for (int j = 0; j < in_width; j++) {
        for (int i = 0; i < in_height; i++) {
            if (inshape.content[j * in_width + i] == '.') {

            }
            else {
                //int debug1 = pos_y + j * in_width + pos_x + i;
                //buffer[(pos_y+j) * width + pos_x+i].Char.UnicodeChar = inshape.content[v++];
                buffer[(pos_y + j) * width + pos_x + i].Char.UnicodeChar = inshape.content[j * in_width + i];
                //possibly better?
                //buffer[(pos_y + j) * in_width + pos_x + i].Char.UnicodeChar = '0' + debug1;
                buffer[(pos_y + j) * width + pos_x + i].Attributes = attrib;
            }
        }

    }
}

StrShape2D RectCreate(int x_dim, int y_dim, char borderChar){
    StrShape2D outShape;
    outShape.width = x_dim;
    outShape.height = y_dim;

    int dpos;

    for (int v = 0; v < x_dim * y_dim; v++) {
        outShape.content.append(".");
    }
    
    for (int i = 0; i < x_dim; i++) {
        for (int j = 0; j < y_dim; j++) {
            dpos = (j * x_dim + i);

            if (i == 0 || i == x_dim - 1) {
                outShape.content[dpos] = borderChar;
            }
            if (i > 0 && j == 0 || j == y_dim-1){
                outShape.content[dpos] = borderChar;
            }

        }

    }

    return outShape;

}

void buffFill(CHAR_INFO buffinput[400], char charinput = '-', WORD attribs = 0x0001) {
    for (int i = 0; i < 400; i++) {
        buffinput[i].Char.UnicodeChar = charinput;
        buffinput[i].Attributes = attribs;
    }
}

void turn(int* turncount){
    *turncount = *turncount + 1;
    //g_ent_table[1]->TileMove(g_map_array, 20, 1, 0);
}

int main()
{
    short rows = 240;
    short columns = 240;
    COORD conBufferSize = { rows, columns };
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);  
    //_setmode(_fileno(stdout), _O_U16TEXT);
    HANDLE hConOut = GetStdHandle(STD_OUTPUT_HANDLE);
    HWND ConScreen = GetConsoleWindow();
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    SetConsoleScreenBufferSize(hConOut, conBufferSize);
    GetConsoleScreenBufferInfo(hConOut, &csbi);
    ShowWindow(ConScreen, SW_SHOWMAXIMIZED);

    CHAR_INFO write[400];

    for (int i = 0; i < 400; i++) {
        write[i].Char.UnicodeChar = '-';
        write[i].Attributes = 0x008 | 0x0002;
    }
        
    COORD dwbuffer = { 20 ,20 };
    COORD dwbuffercoord = { 0,0 };
    SMALL_RECT wRect{
     5, 5, 25, 25

    };

    int framecount = 0;
    int turn_count = 0;

    Item testitem;

    Entity ent1(g_map_array, 5, 5, 20);

    g_ent_table.push_back(&ent1);
    g_ent_table.push_back(new Entity(g_map_array, 2, 5, 20, 'V'));

    StrShape2D coolrect = RectCreate(16, 16, ' ');

    ConWindow2D window_2;
    window_2.drawRect = { 30, 5, 45, 20 };

    buffFill(window_2.text_buffer, ' ', 0x0008);

    ConWindow2D RendSpace[5];
    RendSpace[0] = window_2;
    buffWrite(RendSpace[0].text_buffer, 0, 0, 20, coolrect, 0x0010);
    buffWrite(RendSpace[0].text_buffer, 1, 1, 20, "Turn Count: ", 0x0008);

    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        framecount++;
        if (_kbhit != 0) {
            if (GetAsyncKeyState(VK_UP)) {
                ent1.TileMove(g_map_array, 20, 0, -1);
                buffWrite(write, ent1.getOldCoords().x, ent1.getOldCoords().y, 20, '-', 0x0002);
                turn(&turn_count);
            }
            else if (GetAsyncKeyState(VK_DOWN)) {
                ent1.TileMove(g_map_array, 20, 0, 1);
                buffWrite(write, ent1.getOldCoords().x, ent1.getOldCoords().y, 20, '-', 0x0002);
                turn(&turn_count);
            }
            else if (GetAsyncKeyState(VK_LEFT)) {
                ent1.TileMove(g_map_array, 20, -1, 0);
                buffWrite(write, ent1.getOldCoords().x, ent1.getOldCoords().y, 20, '-', 0x0002);
                turn(&turn_count);
            }
            else if (GetAsyncKeyState(VK_RIGHT)) {
                ent1.TileMove(g_map_array, 20, 1, 0);
                buffWrite(write, ent1.getOldCoords().x, ent1.getOldCoords().y, 20, '-', 0x0002);
                turn(&turn_count);
            }
            else if (GetAsyncKeyState(0x42)) {
                turn(&turn_count);
            }
        }
        buffWrite(write, ent1.getCurrentPosX(), ent1.getCurrentPosY(), 20, ent1.character);
        buffWrite(write, g_ent_table[1]->getCurrentPosX(), g_ent_table[1]->getCurrentPosY(), 20, g_ent_table[1]->character);
        buffWrite(RendSpace[0].text_buffer, 1, 2, 20, std::to_string(turn_count), 0x0008);

        WriteConsoleOutputW(hConOut, write, dwbuffer, dwbuffercoord, &wRect);
        WriteConsoleOutputW(hConOut, RendSpace[0].text_buffer, RendSpace[0].dwBuffer, RendSpace[0].dwbuffercoord, &RendSpace[0].drawRect);


    }

    wcout << "Hello World!\n";
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
