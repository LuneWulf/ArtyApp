#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#include "Tools.c"
#include "Structs.c"

#ifndef TARGETMANIPULATION_H

#define TARGETMANIPULATION_H

void AddTarget(void) {

    char Grid[11], Answer;

    InputString("ENTER TARGET GRID (MAX 10 DIGITS, MIN 2 DIGITS): ", Grid);

    float z = Inputfloat("ENTER TARGET HEIGHT ASL: ", -1000, 10000);

    MASTER.Target[MASTER.TargetCount] = (struct Target) {'\0', z};
    strcpy(MASTER.Target[MASTER.TargetCount].Grid, Grid);
    MASTER.TargetCount++;
}

void RemoveTarget(int Target) {

    MASTER.Target[Target - 1] = (struct Target) {0, 0, 0};

    for (int tgt = Target; tgt < MASTER.TargetCount; tgt++) {
        MASTER.Target[tgt - 1] = MASTER.Target[tgt];
    }

    MASTER.TargetCount--;    

}

#endif
