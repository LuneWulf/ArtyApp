int AddGun(void) {
    
    clear();

    // Adds a new gun to the end of the Type's gun array.

    if (MASTER.GunCount >= MAX_GUNS) {
        return -1; // ERROR: Gun limit exceeded.
    }

    char Grid[10];
    char Answer;

    while (true) {
        printf("    ENTER GUN GRID (MAX 10 DIGITS, MIN 2 DIGITS): ");
        scanf("%c", Grid);
        clear();

        while (true) {
            printf("    CONFIRM GRID %s IS CORRECT (Y/N):", Grid);
            scanf("%c", &Answer);
            clear();

            if (Answer == 'Y') {
                break;
            } else if (Answer == 'N') {
                break;
            } else {
                printf("    ERROR: ANSWER WAS NOT Y OR N!\n\n");
            }
        }

        if (Answer == 'Y') {
            break;
        }
    }

    long int Elevation;

    while (true) {
        printf("    ENTER GUN ELEVATION: ");
        scanf("%ld", &Elevation);
        clear();

        while (true) {
            printf("    CONFIRM ELEVATION %ld IS CORRECT (Y/N):", Elevation);
            scanf("%c", &Answer);
            clear();

            if (Answer == 'Y') {
                break;
            } else if (Answer == 'N') {
                break;
            } else {
                printf("    ERROR: ANSWER WAS NOT Y OR N!\n\n");
            }
        }

        if (Answer == 'Y') {
            break;
        }
    }

    int Type;

    while (true) {
        printf("    ENTER GUN TYPE: ");
        scanf("%d", &Type);
        clear();

        while (true) {
            printf("    CONFIRM GUN TYPE %d IS CORRECT (Y/N):", Type);
            scanf("%c", &Answer);
            clear();

            if (Answer == 'Y') {
                break;
            } else if (Answer == 'N') {
                break;
            } else {
                printf("    ERROR: ANSWER WAS NOT Y OR N!\n\n");
            }
        }

        if (Answer == 'Y') {
            break;
        }
    }
        
    long int x, y;

    GridToCoordinates(Grid, &x, &y);
    
    MASTER.Gun[MASTER.GunCount] = (struct Gun) {'\0', x, y, Elevation, Type};
    strcpy(MASTER.Gun[MASTER.GunCount].Grid, Grid);

    MASTER.GunCount++;

    return 0;
}
