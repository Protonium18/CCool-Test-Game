#include <iostream>
#include <fstream>
#define _WIN32_WINNT 0x0500
#include <windows.h>
#include<string>
#include<chrono>
#include<thread>
#include <conio.h>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cwchar>
#include <stdlib.h>

#include "Tile.h"
#include "Entity.h"
#include "Functions.h"
#include "Structs.h"
#include "Window2D.h"
#include "Defs.h"

using namespace std;

std::vector<std::vector<Tile>> g_map_main;
Window2D RendSpace[5];
HANDLE g_hConOut = GetStdHandle(STD_OUTPUT_HANDLE);
std::vector<Entity*> g_ent_table;
int g_framecount = 0;
int g_turn_count = 0;
int g_framebcounter = 0;
bool g_blink = false;
unsigned short game_state = GM_ENGAGED;
signed int g_x_offset = 0;
signed int g_y_offset = 0;

Window2D* game_space = &RendSpace[1];
Window2D* score_space = &RendSpace[0];



void turn(){
    g_turn_count = g_turn_count + 1;
    //g_ent_table[1]->TileMove(&g_map_main, 1, 0);
}

void render() {

    int range_x = 0 + g_x_offset;
    int range_y = 0 + g_y_offset;
    //drawing tiles
    for (int i = 0 + g_x_offset; i < game_space->width + g_x_offset; i++) {
        for (int j = 0 + g_y_offset; j < game_space->height + g_y_offset; j++) {
            if (i >= 0 && j >= 0 && i < g_map_main.size() && j < g_map_main[0].size()) {
                Tile tile_render = g_map_main.at(i).at(j);
                fct::buffWrite(game_space, i - g_x_offset, j - g_y_offset, tile_render.getChar(), tile_render.getAttribs());
                if (tile_render.isOccupied() == true) {
                    fct::buffWrite(game_space, i - g_x_offset, j - g_y_offset, tile_render.getEnt()->character);
                }
                if (tile_render.getInv()->size() > 0) {
                    fct::buffWrite(game_space, i - g_x_offset, j - g_y_offset, 'i', tile_render.getInvItem(0)->getColor());
                    /*if (g_blink == false) {
                        fct::buffWrite(game_space, i, j, tile_render.getChar(), tile_render.getAttribs());
                    }*/

                    /*if(g_blink == true){
                        fct::buffWrite(game_space, i, j, tile_render.getChar(), tile_render.getAttribs() | 0x0080);

                    }*/
                }
            }
            else {
                fct::buffWrite(game_space, i-g_x_offset, j-g_y_offset, ' ');
            }
        }
    }

    //writing to console buffer
    for (int i = 0; i < 5; i++) {
        WriteConsoleOutputW(g_hConOut, RendSpace[i].text_buffer, RendSpace[i].dwBuffer, RendSpace[i].dwbuffercoord, &RendSpace[i].drawRect);

    }
}

void renderStart() {

}

void mapCreate(int width, int height) {
    for (int i = 0; i < width; i++) {
        g_map_main.push_back(std::vector<Tile>());

        for (int j = 0; j < height; j++) {
            g_map_main[i].push_back(Tile());
        }
    }

}

void center_camera() {
    g_x_offset = g_ent_table[0]->getCurrentPosX() - game_space->width / 2;
    g_y_offset = g_ent_table[0]->getCurrentPosY()- game_space->height / 2;
}

void mapOpen(string map) {
    std::ifstream file_open = fct::openFile(map);
    std::string str;
    std::string strtotal;
    std::vector<std::string> strvector;

    while (getline(file_open, str)) {
        strtotal += str;
        strvector.push_back(str);
    }
    if (g_map_main.size() > 0) {
        g_map_main.clear();
    }
    int x = std::stoi(strvector[0]);
    int y = std::stoi(strvector[1]);
    

    for (int i = 0; i < x; i++) {
        g_map_main.push_back(std::vector<Tile>());
        for (int j = 0; j < y; j++) {
            int input1 = std::stoi(to_string(strtotal[j * x + i+2]))-'0';
            g_map_main[i].push_back(Tile(input1));
        }
    }
    file_open.close();
}


int main()
{

    srand(time(0));

    short rows = 240;
    short columns = 240;
    COORD conBufferSize = { rows, columns };
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);  
    //_setmode(_fileno(stdout), _O_U16TEXT);
    HWND ConScreen = GetConsoleWindow();
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    SetConsoleScreenBufferSize(g_hConOut, conBufferSize);
    GetConsoleScreenBufferInfo(g_hConOut, &csbi);
    ShowWindow(ConScreen, SW_SHOWMAXIMIZED);
    CONSOLE_FONT_INFOEX cfi_to;
    cfi_to.cbSize = sizeof(cfi_to);
    cfi_to.nFont = 0;
    cfi_to.dwFontSize.X = 16;
    cfi_to.dwFontSize.Y = 18;
    cfi_to.FontFamily = FF_DONTCARE;
    cfi_to.FontWeight = FW_NORMAL;
    wcscpy_s(cfi_to.FaceName, L"Raster Fonts");
    SetCurrentConsoleFontEx(g_hConOut, false, &cfi_to);

    RendSpace[0] = Window2D(50, 5, 20, 20, ' ', 0x0008);
    RendSpace[1] = Window2D(5, 5, 40, 40, '-', 0x0002);;
    Window2D cool1 = Window2D(4, 4, 42, 42, ' ', 0x00FF);;
    WriteConsoleOutputW(g_hConOut, cool1.text_buffer, cool1.dwBuffer, cool1.dwbuffercoord, &cool1.drawRect);

    //mapCreate(400, 400);
    mapOpen("maps/Map1.txt");

    Entity ent1(&g_map_main, game_space, 4, 4);
    g_ent_table.push_back(&ent1);
    g_ent_table.push_back(new Entity(&g_map_main, game_space, 2, 5, 'V'));

    fct::buffWrite(&RendSpace[0], 0, 0, fct::RectCreate(20, 20, ' '), 0x0010);
    fct::buffWrite(&RendSpace[0], 1, 1, "Turn Count: ", 0x0008);

    fct::buffWrite(&RendSpace[0], 1, 3, "X: ", 0x0008);
    fct::buffWrite(&RendSpace[0], 7, 3, "Y: ", 0x0008);

    //g_map_main.at(5).at(10).getInv()->push_back(new Item);

    center_camera();

    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(60));
        g_framecount++;
        if (_kbhit != 0) {
            if (game_state == GM_ENGAGED) {
                //movement controls
                if (GetAsyncKeyState(0x57)) {
                    if (ent1.TileMove(&g_map_main, 0, -1)) {
                        g_y_offset--;
                        turn();
                    }
                }
                else if (GetAsyncKeyState(0x53)) {
                    if (ent1.TileMove(&g_map_main, 0, 1)) {
                        g_y_offset++;
                        turn();
                    }
                }
                else if (GetAsyncKeyState(0x41)) {
                    if (ent1.TileMove(&g_map_main, -1, 0)) {
                        g_x_offset--;
                        turn();
                    }
                }
                else if (GetAsyncKeyState(0x44)) {
                    if (ent1.TileMove(&g_map_main, 1, 0)) {
                        g_x_offset++;
                        turn();
                    }
                }
                //cam controls
                else if (GetAsyncKeyState(VK_UP)) {
                    g_y_offset--;
                }
                else if (GetAsyncKeyState(VK_DOWN)) {
                    g_y_offset++;
                }
                else if (GetAsyncKeyState(VK_RIGHT)) {
                    g_x_offset++;
                }
                else if (GetAsyncKeyState(VK_LEFT)) {
                    g_x_offset--;
                }
                else if (GetAsyncKeyState(0x43)) {
                    center_camera();
                }

                //game controls
                else if (GetAsyncKeyState(0x47)) {
                    ent1.takeItem(0);
                }

                else if (GetAsyncKeyState(0x42)) {
                    turn();
                }
            }
        }

        if (g_framecount % 10 == 0) {
            g_framebcounter++;
            if (g_framebcounter == 0) {
                g_blink = true;
            }

            else if (g_framebcounter == 5) {
                g_framebcounter = 0;
                g_blink = false;
            }


        }

        fct::buffWrite(score_space, 3, 3, to_string(ent1.getCurrentPosX()), 0x0008);
        fct::buffWrite(score_space, 9, 3, to_string(ent1.getCurrentPosY()), 0x0008);
        fct::buffWrite(score_space, 1, 2, std::to_string(g_turn_count), 0x0008);

        render();

    }
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
