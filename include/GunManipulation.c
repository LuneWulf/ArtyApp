#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#include "Tools.c"
#include "Structs.c"
#include "TypeAccess.c"

#ifndef GUNMANIPULATION_H

#define GUNMANIPULATION_H

void AddGun(void) {
    
    char Grid[11];
    char Answer;

    InputString("ENTER GUN GRID (MAX 10 DIGITS, MIN 2 DIGITS): ", Grid);

    float Height = Inputfloat("ENTER GUN HEIGHT ASL: ", -1000, 10000);

    printf("    SELECT GUN TYPE FROM LIST:\n");
    ListAllTypes(false);

    int Type = Inputint("ENTER GUN TYPE ID: ", 1, MASTER.TypeCount);
        
    MASTER.Gun[MASTER.GunCount] = (struct Gun) {'\0', Height, Type};
    strcpy(MASTER.Gun[MASTER.GunCount].Grid, Grid);

    MASTER.GunCount++;
}

void RemoveGun(int GunID) {

    MASTER.Gun[GunID - 1] = (struct Gun) {'\0', 0, 0, 0, 0};

    for (int Gun = GunID; Gun < MASTER.GunCount; Gun++) {        
        MASTER.Gun[Gun - 1] = MASTER.Gun[Gun];
    }

    MASTER.GunCount--;

}

#endif
