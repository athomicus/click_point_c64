#include <conio.h>
#include "unity.h"

// Predkosc kursora
#define CUR_SPEED 1

// Poprawna tablica kolorow - nie mozna przekazac 0!
unsigned char cursorColors[] = {WHITE};//, BLACK, RED, GREEN, BLUE, YELLOW, CYAN, MAGENTA };

unsigned char currentScene = 0;
unsigned char joy;

// Pozycja kursora
unsigned int curX = 160;
unsigned int curY = 100;

void LoadScene(unsigned char scene)
{
    HideBitmap();
    if (scene == 0) {
        LoadBitmap("scene1.img");
    } else {
        LoadBitmap("scene3.img");
    }
    ShowBitmap();
}
void UpdateCursor(void)
{
    joy = GetJoy(0);

    // Ruch kursora
    if (!(joy & JOY_UP))    { if (curY > CUR_SPEED)       curY -= CUR_SPEED; }
    if (!(joy & JOY_DOWN))  { if (curY < 199 - CUR_SPEED) curY += CUR_SPEED; }
    if (!(joy & JOY_LEFT))  { if (curX > CUR_SPEED)       curX -= CUR_SPEED; }
    if (!(joy & JOY_RIGHT)) { if (curX < 319 - CUR_SPEED) curX += CUR_SPEED; }

    // Rysuj kursor jako sprite 0
    LocateSprite(curX, curY);
    SetSprite(0, 0); // ramka 0 = kursor 
    //nmumer klatki z pliku sprites.dat (0, 1, 2...)
      //        który sprite na ekranie (0=kursor, 1=goblin...)
}
int main(void)
{
    bordercolor(COLOR_BLACK);
    bgcolor(COLOR_BLACK);
    InitSFX(); 
   
    InitBitmap();
    InitJoy();   
 
    
    LoadSprites("sprites.dat");//muisi byc sprites.dat tak jest w unity
    SetupSprites(14, 12, 21, cursorColors); // 14 oveerweitr w gimp klatka, 21x21 px, kolor 0 = przezroczysty
    EnableSprite(0);
RecolorSprite(0, 0, WHITE);  // kolor indywidualny (10) = bialy
RecolorSprite(0, 1, WHITE);  // shared $D025 (01) = bialy  ← TO NAPRAWI FIOLET
RecolorSprite(0, 2, BLACK);  // shared $D026 (11) = czarny
    
    
    
    LoadBitmap("scene1.img"); //zaldowujesz png w kodzie odczytujesz img
    ShowBitmap();

    

    while (1) {
        UpdateCursor();
        //joy = GetJoy(0);
        //czeka na button
        if (!(joy & JOY_BTN1)) {
            //cgetc();
            currentScene = !currentScene;
            LoadScene(currentScene);
        }
    }

    return 0;
}