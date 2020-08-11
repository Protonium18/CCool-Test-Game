#include "Functions.h"

namespace fct {
    void buffWrite(Window2D* window, int pos_x, int pos_y, char character, WORD attrib) {
        window->text_buffer[pos_y * window->width + pos_x].Char.UnicodeChar = character;
        window->text_buffer[pos_y * window->width + pos_x].Attributes = attrib;

    }

    void buffWrite(Window2D* window, int pos_x, int pos_y, std::string instring, WORD attrib) {
        int strLength = instring.length();
        for (int i = 0; i < strLength; i++) {
            window->text_buffer[pos_y * window->width + pos_x + i].Char.UnicodeChar = instring[i];
            window->text_buffer[pos_y * window->width + pos_x + i].Attributes = attrib;
        }
    }

    void buffWrite(Window2D* window, int pos_x, int pos_y, StrShape2D inshape, WORD attrib) {
        int in_width = inshape.width;
        int in_height = inshape.height;
        int v = 0;



        for (int i = 0; i < in_width; i++) {
            for (int j = 0; j < in_height; j++) {
                if (inshape.content[j * in_width + i] == '.') {

                }
                else {
                    window->text_buffer[(pos_y + j) * window->width + pos_x + i].Char.UnicodeChar = inshape.content[j * in_width + i];
                    window->text_buffer[(pos_y + j) * window->width + pos_x + i].Attributes = attrib;
                }
            }

        }
    }

    StrShape2D RectCreate(int x_dim, int y_dim, char borderChar) {
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
                //cout << i << " | " << j << " | " << dpos << endl;

                if (j == 0 || j == y_dim - 1) {
                    outShape.content[dpos] = borderChar;
                }

                else if (i == 0) {
                    outShape.content[dpos] = borderChar;
                }

                else if (i == x_dim - 1) {
                    outShape.content[dpos] = borderChar;
                }

            }

        }

        return outShape;

    }

    std::ifstream openFile(std::string inputname) {
        std::ifstream file;
        file.open(inputname, std::ios::out);
        if (file.is_open()) {
            return file;
        }
        else {
            std::cout << "Issue opening file!" << std::endl;
        }
        
    }

}