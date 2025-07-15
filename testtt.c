#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "lib.c"

int main(void) {

    int *p = malloc(sizeof(int) * 4);

    printf("size: %d", *(p+4));

}