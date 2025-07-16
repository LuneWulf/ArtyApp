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

long int StrToLI(char *string) {
    int size = strlen(string);
    long int number = 0;

    for (int i = 0; i < size; i++) {
        number = number + (long int) ((*(string + i) - 48) * power(10, size - i - 1));
        //printf("number: %ld, added: %ld\n", number, (long int) ((*(string + i) - 48) * pow(10, size - i - 1)));
        //printf("%f\n", power(10, size - i - 1));
        //printf("size: %d\n", size);
    }

    return number;
}

int GridToCoordinates(char grid[], long int *x, long int *y) {

    int size = strlen(grid);

    //printf("size %d\n", size);

    // is size even
    float even = (float) size / (float) 2 - size / 2;
    if (even != 0) {
        char *temp = malloc(sizeof(char) * (size + 1));
        temp[0] = '0';
        for (int i = 0; i < size; i++) {
            temp[i + 1] = grid[i];

            //printf("%c %c\n", temp[i + 1], grid[i]);
        }

        //printf("%s\n", temp);

        size++;
        for (int i = 0; i < size; i++) {
            grid[i] = temp[i];
        }

        //printf("%s\n", grid);
    }

    //printf("size %d\n", size);
    

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

        //printf("test\n");

        //printf("%s, %s\n", X, Y);

        //Assign x and y and scale such that its unit is in meters.
        *x = StrToLI(X) * power(10, 5 - middle);
        *y = StrToLI(Y) * power(10, 5 - middle);

        //printf("x: %ld, y: %ld\n", *x, *y);
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

long int MillsFromCoordinate(long int dx, long int dy) {
    
    long int mills = (atan((double) dy / (double) dx) * 6400) / (2 * M_PI);

    if (dx < 0) {
        if (mills < 0) {
            mills += 6400;
        } else {
            mills += 3200;
        }
    } else if (dx > 0) {
        if (mills < 0) {
            mills += 3200;
        }
    } else {
        if (mills < 0) {
            mills += 6400;
        }
    }

    return mills;
}

void GridsToDisMills(char *GridOne, char *GridTwo, long int *Distance, long int *Direction) {
    long int x_1, x_2, y_1, y_2;

    GridToCoordinates(GridOne, &x_1, &y_1);
    GridToCoordinates(GridTwo, &x_2, &y_2);

    *Distance = hypot((double) (x_1 - x_2), (double) (y_1 - y_2));

    *Direction = MillsFromCoordinate(x_1 - x_2, y_1 - y_2);
}

void Save() {

}

int ExitWithoutSaving(void) {
    
    char Answer;
    
    while (true) {
        printf("    CONFIRM EXIT WITHOUT SAVING (Y/N):");
        scanf("%c" %Answer);

        if (Answer == 'Y') {
            exit(0);
        } else if (Answer == 'N') {
            return 0;
        }
    }
}

int EnterCommand(Min, Max) {
    
    // Prompts the user for a command and then
    // verifies that the command is in the defined range.

    int command;

    while (true) {
        printf("    ENTER COMMAND: ");
        scanf("%d", &command);
        printf("\n");

        if (command >= Min && command <= Max) {
            break;
        } else {
            printf("    ERROR: COMMAND OUT OF RANGE RETRY!\n\n");
        }
    }

    return command;
}

int EnterType() {
    
    // Prompts the user for a type and then
    // verifies that the type is defined.

    int type;

    while (true) {
        printf("    ENTER GUN TYPE: ");
        scanf("%d", &type);
        printf("\n");

        if (type >= 1 && type <= MASTER.TypeCount) {
            break;
        } else {
            printf("    ERROR: GUN TYPE NOT DEFINED\n\n");
        }
    }

    return type;
}

int EnterAmmo(int type) {
    
    // Prompts the user for an ammo type and then
    // verifies that the ammo type is defined.

    int ammo;

    while (true) {
        printf("    ENTER AMMO TYPE: ");
        scanf("%d", &ammo);
        printf("\n");

        if (ammo >= 1 && ammo <= MASTER.Types[type - 1].AmmoCount) {
            break;
        } else {
            printf("    ERROR: AMMO TYPE NOT DEFINED\n\n");
        }
    }

    return ammo;
}

int EnterGunID() {

    // Prompts the user for a gun ID and then
    // verifies that the gun ID is defined.

    int GunID;

    while (true) {
        printf("    ENTER GUN ID TYPE: ");
        scanf("%d", &GunID);
        printf("\n");

        if (GunID >= 1 && GunID <= MASTER.GunCount) {
            break;
        } else {
            printf("    ERROR: GUN NOT DEFINED\n\n");
        }
    }

    return GunID;    
}