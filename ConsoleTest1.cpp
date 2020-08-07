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
#include "Functions.h"
#include "Structs.h"
#include "Window2D.h"


using namespace std;

std::vector<std::vector<Tile>> g_map_main;
Window2D RendSpace[5];
HANDLE g_hConOut = GetStdHandle(STD_OUTPUT_HANDLE);
std::vector<Entity*> g_ent_table;

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
    //g_ent_table[1]->TileMove(&g_map_main, 1, 0);
}

void render() {
    for (int i = 0; i < 5; i++) {
        WriteConsoleOutputW(g_hConOut, RendSpace[i].text_buffer, RendSpace[i].dwBuffer, RendSpace[i].dwbuffercoord, &RendSpace[i].drawRect);

    }
}

int main()
{
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

    int framecount = 0;
    int turn_count = 0;

    for (int ii = 0; ii < 20; ii++) {
        g_map_main.push_back(std::vector<Tile>());

        for (int jj = 0; jj < 20; jj++) {
            g_map_main[ii].push_back(Tile());
        }
    }

    /*g_map_main.height = 20;
    g_map_main.width = 20;
    for (int i = 0; i < g_map_main.width * g_map_main.height; i++) {
        g_map_main.VecMap.push_back(new Tile);
    }*/

    RendSpace[0] = Window2D(30, 5, 20, 20, ' ', 0x0008);
    RendSpace[1] = Window2D(5, 5, 20, 20, '-', 0x0002);;
    Window2D* game_space = &RendSpace[1];
    Window2D* score_space = &RendSpace[0];

    Entity ent1(&g_map_main, game_space, 4, 0);
    g_ent_table.push_back(&ent1);
    g_ent_table.push_back(new Entity(&g_map_main, game_space, 2, 5, 'V'));

    fct::buffWrite(&RendSpace[0], 0, 0, RectCreate(16, 16, ' '), 0x0010);
    fct::buffWrite(&RendSpace[0], 1, 1, "Turn Count: ", 0x0008);

    fct::buffWrite(&RendSpace[0], 1, 3, "X: ", 0x0008);
    fct::buffWrite(&RendSpace[0], 7, 3, "Y: ", 0x0008);
    

    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        framecount++;
        if (_kbhit != 0) {
            if (GetAsyncKeyState(VK_UP)) {
                ent1.TileMove(&g_map_main, 0, -1);
                turn(&turn_count);
            }
            else if (GetAsyncKeyState(VK_DOWN)) {
                ent1.TileMove(&g_map_main, 0, 1);
                turn(&turn_count);
            }
            else if (GetAsyncKeyState(VK_LEFT)) {
                ent1.TileMove(&g_map_main, -1, 0);
                turn(&turn_count);
            }
            else if (GetAsyncKeyState(VK_RIGHT)) {
                ent1.TileMove(&g_map_main, 1, 0);
                turn(&turn_count);
            }
            else if (GetAsyncKeyState(0x42)) {
                turn(&turn_count);
            }
        }
        fct::buffWrite(score_space, 3, 3, to_string(ent1.getCurrentPosX()), 0x0008);
        fct::buffWrite(score_space, 9, 3, to_string(ent1.getCurrentPosY()), 0x0008);
        fct::buffWrite(game_space, ent1.getCurrentPosX(), ent1.getCurrentPosY(), ent1.character);
        fct::buffWrite(game_space, g_ent_table[1]->getCurrentPosX(), g_ent_table[1]->getCurrentPosY(), g_ent_table[1]->character);
        fct::buffWrite(score_space, 1, 2, std::to_string(turn_count), 0x0008);

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
