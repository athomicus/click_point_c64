#include <conio.h>
#include "unity.h"

#define CUR_SPEED 3
#define MAX_ITEMS 1

unsigned char cursorColors[] = { WHITE };
unsigned char joy;
unsigned int curX = 160;
unsigned int curY = 100;

// Struktura przedmiotu - wzorzec z Goblin/scene.c
typedef struct {
    unsigned char x, y, w, h;
    unsigned char active;
    unsigned char *name;
    unsigned char *chunk;   // chunk z pliku .chk (tlo bez przedmiotu)
} SceneItem;

SceneItem items[MAX_ITEMS] = {
       { 12, 168, 84, 32, 1, "Scroll", 0 } //po Y ok ale x * 2 i w* 2 musi byc chyba
};

unsigned char CursorOverItem(void)
{
    unsigned char i;
    for (i = 0; i < MAX_ITEMS; i++) {
        if (!items[i].active) continue;
        if (curX >= (items[i].x)*2 && curX <= (items[i].x)*2 + (items[i].w)*2 &&   curY >= items[i].y && curY <= items[i].y + (items[i].h))
            return i;
    }
    return 255;
}

void ShowItemName(unsigned char index)
{
    txtX = 0; txtY = 24;
    PrintBlanks(32, 1);
    if (index != 255) {
        txtX = 0; txtY = 24;
        PrintStr(items[index].name);
    }
}

void UpdateCursor(void)
{
    unsigned char over;
    joy = GetJoy(0);

    if (!(joy & JOY_UP))    { if (curY > CUR_SPEED)       curY -= CUR_SPEED; }
    if (!(joy & JOY_DOWN))  { if (curY < 199 - CUR_SPEED) curY += CUR_SPEED; }
    if (!(joy & JOY_LEFT))  { if (curX > CUR_SPEED)       curX -= CUR_SPEED; }
    if (!(joy & JOY_RIGHT)) { if (curX < 319 - CUR_SPEED) curX += CUR_SPEED; }

    LocateSprite(curX, curY);
    SetSprite(0, 0);

    over = CursorOverItem();
    ShowItemName(over);
}

int main(void)
{
    unsigned char  over;

    bordercolor(COLOR_BLACK);
    bgcolor(COLOR_BLACK);

    InitBitmap();
    InitJoy();

    LoadSprites("sprites.dat");
    SetupSprites(1, 12, 21, cursorColors);
    EnableSprite(0);

    // KROK 1: Zaladuj i pokaz bitmape Z przedmiotami (jak w Goblinie)
    LoadBitmap("01.img");
    ShowBitmap();

    // KROK 2: LoadChunk - zaladuj gotowe chunki z plikow .chk
    // (pliki .chk generowane przez Unity Builder z 01A.png - scena BEZ przedmiotow)
    LoadChunk(&items[0].chunk, "scroll.chk");


    // LoadChunk(&items[1].chunk, "mikstura.chk");
    // LoadChunk(&items[2].chunk, "mapa.chk");

    while (1) {
        UpdateCursor();

        if (!(joy & JOY_BTN1)) {
            over = CursorOverItem();
            if (over != 255) {
                // Wez przedmiot - przywroc tlo przez DrawChunk (jak w Goblinie)
                SetChunk(items[over].chunk, items[over].chunk[0], items[over].chunk[1]);
                //SetChunk(items[over].chunk, 24, 176);
                //SetChunk(items[over].chunk, items[over].x, items[over].y);
                items[over].active = 0;

                // Wyswietl komunikat
                txtX = 0; txtY = 24;
                PrintBlanks(32, 1);
                txtX = 0; txtY = 24;
                PrintStr("Wziales: ");
                PrintStr(items[over].name);
            }
        }
    }

    return 0;
}