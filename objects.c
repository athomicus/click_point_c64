#include "objects.h"

// Dane obiektów
GameObject objects[MAX_OBJECTS] = {
    { 80,  120, 20, "body",   1 },
    { 150, 100, 15, "knife",  1 },
    { 200, 140, 18, "fish",   1 },
    { 60,   80, 12, "scroll", 1 },
    { 240, 130, 16, "coal",   1 }
};

unsigned char foundObject = 255;
unsigned char lastObject  = 255;

// Funkcja pomocnicza – tylko w tym pliku (static)
static unsigned char IsCursorNear(unsigned int cx, unsigned int cy,
                                   unsigned int ox, unsigned int oy,
                                   unsigned char r)
{
    signed int dx = (signed int)cx - (signed int)ox;
    signed int dy = (signed int)cy - (signed int)oy;
    if (dx < 0) dx = -dx;
    if (dy < 0) dy = -dy;
    if (dx >= r) return 0;
    if (dy >= r) return 0;
    return 1;
}

// POPRAWKA – rzutowanie przy wywołaniu PrintStr
void PrintLabel(unsigned char *text)
{
    txtX = 0; txtY = TXT_ROWS - 1;
    inkColor = WHITE;
    paperColor = BLACK;
    PrintBlanks(TXT_COLS, 1);
    txtX = 0; txtY = TXT_ROWS - 1;
    PrintStr((unsigned char*)text);  // ← jawne rzutowanie
}

void UpdateObjects(unsigned int cx, unsigned int cy)
{
    unsigned char i;

    foundObject = 255;
    for (i = 0; i < MAX_OBJECTS; i++) {
        if (!objects[i].active) continue;
        if (IsCursorNear(cx, cy, objects[i].x, objects[i].y, objects[i].r)) {
            foundObject = i;
            break;
        }
    }

    if (foundObject != lastObject) {
    if (foundObject != 255) {
        PrintLabel(objects[foundObject].label);
    } else {
        PrintLabel((unsigned char*)"");
    }
    lastObject = foundObject;
}
}