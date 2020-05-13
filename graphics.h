//
// Created by dunka on 13.11.2019.
//

#ifndef TREE_GRAPHICS_H

#include "D:\\TX\TXlib.h"

const int High = 800;
const int With = 800;

const int  COLOR_MENU_TEXT      = TX_GREEN;
const int  COLOR_MENU_RECTANGLE = TX_BLACK;
const char FONT_TEXT[]          = "Times New Roman";

enum what {
    MENU_PLAY       = 1,
    MENU_DIFF       = 2,
    MENU_TREE       = 3,
    MENU_DEFINITION = 4,
    MENU_EXIT       = 5,
    MENU_END        = 10000,
};


struct Button {
    int what;
    char* name       = nullptr;

    int high_of_text = 0;

    int x0           = 0;
    int y0           = 0;

    int x1           = 0;
    int y1           = 0;
};

void Draw (struct Button* menu, HDC back)
{
    ASSERT (menu)
    ASSERT (back)

    txClear ();

    txBitBlt (txDC(), 0, 0, With, High, back, 0, 0);


    txSetFillColor (COLOR_MENU_RECTANGLE);
    txSetColor     (COLOR_MENU_TEXT);

    for (int i = 0; ; i++)
    {
        if (menu->high_of_text == 0) break;

        txSelectFont   (FONT_TEXT, menu->high_of_text);

        txRectangle (menu->x0, menu->y0, menu->x1, menu->y1);


        txTextOut (menu->x0, menu->y0, menu->name);

        menu++;
    }
}

int CheckMenu (struct Button* menu)
{
    ASSERT (menu)

    int x = 0;
    int y = 0;

    struct Button* tmp = menu;
    while (true)
    {
        x = txMouseX ();
        y = txMouseY ();
        unsigned int button = txMouseButtons();

        while (tmp->what != MENU_END)
        {
            if    ((button == 1) && (x >= tmp->x0) && (x <= tmp->x1)
                                 && (y >= tmp->y0) && (y <= tmp->y1))
            {
                return tmp->what;
            }
            tmp++;
        }
        tmp = menu;

        txSleep (0);
    }

}




#define TREE_GRAPHICS_H

#endif //TREE_GRAPHICS_H
