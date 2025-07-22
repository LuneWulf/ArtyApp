#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>

#include "Structs.c"

#ifndef TOOLS_H

#define TOOLS_H

void RecordLog(char *Message) {
    FILE *fp = fopen("Record.txt", "a");
    fprintf(fp, Message);
    fprintf(fp, "\n\n");
    fclose(fp);
}

void clear(void) {
    while (getc(stdin) != '\n');
}

#define InputNum(TYPE, FORMAT)                                                                              \
TYPE Input##TYPE(char *PrintStatement, TYPE Min, TYPE Max) {                                                \
    char Answer = 'N';                                                                                      \
    TYPE Value;                                                                                             \
    while (Answer != 'Y') {                                                                                 \
        printf("    %s", PrintStatement);                                                                   \
        scanf(#FORMAT, &Value);                                                                             \
        printf("\n");                                                                                       \
        clear();                                                                                            \
        if (Value < Min) {                                                                                  \
            printf("    ERROR: VALUE MUST BE GREATER THAN OR EQUAL TO " #FORMAT "\n\n", Min);               \
        } else if (Value > Max) {                                                                           \
            printf("    ERROR: VALUE MUST BE LESS THAN OR EQUAL TO " #FORMAT "\n\n", Max);                  \
        } else {                                                                                            \
            while (true) {                                                                                  \
                printf("    CONFIRM \"" #FORMAT "\" IS CORRECT (Y/N): ", Value);                            \
                scanf("%1c", &Answer);                                                                      \
                printf("\n");                                                                               \
                clear();                                                                                    \
                if (Answer == 'Y' || Answer == 'N') {                                                       \
                    break;                                                                                  \
                } else {                                                                                    \
                    printf("    ERROR: ANSWER MUST BE Y OR N!\n\n");                                        \
                }                                                                                           \
            }                                                                                               \
        }                                                                                                   \
    }                                                                                                       \
    return Value;                                                                                           \
}

// Inputint(char *PrintStatement, int Min, int Max);
InputNum(int, %d);

// Inputfloat(char *PrintStatement, float Min, float Max);
InputNum(float, %f);

// Inputdouble(char *PrintStatement, double Min, double Max);
InputNum(double, %lf);

void InputString(char *PrintStatement, char *String) {
    
    char Answer = 'N';

    while (Answer != 'Y') {

        printf("    %s", PrintStatement);
        scanf("%s", String);
        printf("\n");

        clear();

        while (true) {

            printf("    CONFIRM \"%s\" IS CORRECT (Y/N): ", String);
            scanf("%1c", &Answer);
            printf("\n");

            clear();

            if (Answer == 'Y') {
                break;
            } else if (Answer != 'N') {
                printf("    ERROR: ANSWER WAS NOT Y OR N!\n\n");
            }
        }
    }
}

char Confirm(char *PrintStatement) {
    
    char Answer = 'N';

    while (Answer != 'Y') {
        printf("    %s", PrintStatement);
        scanf("%c", &Answer);
        printf("\n");
        clear();

        if (Answer != 'Y' && Answer != 'N') {
            printf("    ERROR: ANSWER WAS NOT Y OR N!\n\n");
        } else {
            break;
        }  
    }

    return Answer;
}

float power(float x, int y) {

    // custom power function to allow for floats to be raised to an int power

    float temp = x;

    if (y > 1) {
        for (int i = 0; i < y - 1; ++i) {
            x = x * temp;
        }
    } else if (y == 1) {
        x = x;
    } else if (y == 0) {
        x = 1;
    } else if (y == -1) {
        x = ((float) 1) / x;
    } else {
        x = ((float) 1) / x;

        for (int i = 0; i > y; i--) {
            x = x * ((float) 1) / temp;
        }
    }

return x;
}

// Converts a string to the sum of the characters decimal value
int StrToInt(char *string) {

    int number = 0;

    for (int i = 0; i < strlen(string); i++) {
        number += (int) *(string + i);
    }

    return number;
}

// Converts a string of numbers to a long integer
long int NumberStrToLI(char *string) {
    int size = strlen(string);
    long int number = 0;

    for (int i = 0; i < size; i++) {
        number = number + (long int) ((*(string + i) - 48) * power(10, size - i - 1));
    }

    return number;
}

int GridToCoordinates(char grid[], long int *x, long int *y) {

    int size = strlen(grid);

    if (size % 2 != 0) {
        char *temp = malloc(sizeof(char) * (size + 1));
        temp[0] = '0';
        for (int i = 0; i < size; i++) {
            temp[i + 1] = grid[i];
        }

        size++;
        for (int i = 0; i < size; i++) {
            grid[i] = temp[i];
        }
    }
    

    if (size > 10) {
        printf("\n\nERROR: GRID OUT OF BOUNDS, MUST BE 10-DIGIT OR LOWER\n");
        *x = -1;
        return 1;
    } else if (size < 0) {
        printf("\n\nERROR: GRID OUT OF BOUNDS, MUST BE 2-DIGIT OR GREATER\n");
        *x = -1;
        return 1;
    } else {
        int middle = size / 2;
        char *X = malloc(sizeof(char)*middle);
        char *Y = malloc(sizeof(char)*middle);
        for (int i = 0; i < size; i++) {
            if (i < middle) {
                *(X + i) = grid[i];
            } else {
                *(Y + i - middle) = grid[i];
            }
        }

        *(X + middle) = '\0';
        *(Y + middle) = '\0';

        //Assign x and y and scale such that its unit is in meters.
        *x = NumberStrToLI(X) * power(10, 5 - middle);
        *y = NumberStrToLI(Y) * power(10, 5 - middle);

        return 0;
    }
}

void DisMillsToCoordinates(int distance, int direction, char *CurrentGrid, long int *x, long int *y) {
    float radians = (float) direction * M_PI / (float) (3200);

    GridToCoordinates(CurrentGrid, x, y);

    //printf("Radians: %f, pi: %f, direction: %ld\n", radians, M_PI, (direction * 3200));
    //printf("cos: %f, sin: %f", cos(radians) * (double) distance, sin(radians) * (double) distance);

    *x += round(cos(radians) * (double) distance);
    *y += round(sin(radians) * (double) distance);
}

float MillsFromCoordinate(long int dx, long int dy) {
    
    float mills = (atan((float) dx / (float) dy) * 6400) / (2 * M_PI);

    if (dy < 0) {
        mills += 3200;
    } else if (dx < 0 && dy >= 0) {
        mills += 6400;
    }

    return round(mills);
}

void GridsToDisMills(char *GridOne, char *GridTwo, float *Distance, float *Direction) {
    long int x_1, x_2, y_1, y_2;

    GridToCoordinates(GridOne, &x_1, &y_1);
    GridToCoordinates(GridTwo, &x_2, &y_2);

    *Distance = hypot((double) (x_2 - x_1), (double) (y_2 - y_1));

    *Direction = MillsFromCoordinate(x_2 - x_1, y_2 - y_1);
}

void Save(void) {

    FILE *fp = fopen("Types&Ammo.dat", "w+");
    
    fwrite(&MASTER, sizeof(struct MASTER), 1, fp);

}

void Load(void) {

    FILE *fp = fopen("Types&Ammo.dat", "r+");
    
    fread(&MASTER, sizeof(struct MASTER), 1, fp);

}

int ExitWithoutSaving(void) {
    
    clear();

    char Answer;
    
    while (true) {
        printf("    CONFIRM EXIT WITHOUT SAVING (Y/N):");
        scanf("%c", &Answer);
        clear();

        if (Answer == 'Y') {
            exit(0);
        } else if (Answer == 'N') {
            return 0;
        }
    }
}

#endif
