#include <conio.h>
#include "unity.h"
#include "objects.h"

#define CUR_SPEED 1

unsigned char cursorColors[] = {WHITE};
unsigned char currentScene = 0;
unsigned char joy;
unsigned int  curX = 160;
unsigned int  curY = 100;

void UpdateCursor(void)
{
    joy = GetJoy(0);
    if (!(joy & JOY_UP))    { if (curY > CUR_SPEED)       curY -= CUR_SPEED; }
    if (!(joy & JOY_DOWN))  { if (curY < 199 - CUR_SPEED) curY += CUR_SPEED; }
    if (!(joy & JOY_LEFT))  { if (curX > CUR_SPEED)       curX -= CUR_SPEED; }
    if (!(joy & JOY_RIGHT)) { if (curX < 319 - CUR_SPEED) curX += CUR_SPEED; }
    LocateSprite(curX, curY);
    SetSprite(0, 0);
}

void LoadScene(unsigned char scene)
{
    HideBitmap();
    LoadBitmap(scene == 0 ? "home.img" : "scene3.img");
    ShowBitmap();
}

int main(void)
{
    bordercolor(COLOR_BLACK);
    bgcolor(COLOR_BLACK);
    InitSFX();
    InitBitmap();
    InitJoy();
    LoadSprites("sprites.dat");
    SetupSprites(14, 12, 21, cursorColors);
    EnableSprite(0);
    LoadBitmap("home.img");
    ShowBitmap();

    while (1) {
        UpdateCursor();        // ruch kursora
        UpdateObjects(curX, curY);  // wykrywanie + napis

        if (!(joy & JOY_BTN1)) {
            currentScene = !currentScene;
            LoadScene(currentScene);
        }
    }

    return 0;
}