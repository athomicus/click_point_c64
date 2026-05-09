#ifndef OBJECTS_H
#define OBJECTS_H

#include "unity.h"

#define MAX_OBJECTS 5

typedef struct {
    unsigned int  x;
    unsigned int  y;
    unsigned char r;
    unsigned char *label;
    unsigned char active;
} GameObject;

// Tablica obiektów – zdefiniowana w objects.c
extern GameObject objects[MAX_OBJECTS];
extern unsigned char foundObject;
extern unsigned char lastObject;

// Deklaracje funkcji
void InitObjects(void);
void UpdateObjects(unsigned int cx, unsigned int cy);
void PrintLabel(unsigned char *text);

#endif