int AddGun(void) {
    
    // Adds a new gun to the end of the Type's gun array.

    if (MASTER.GunCount >= MAX_GUNS) {
        return -1; // ERROR: Gun limit exceeded.
    }

    char Grid[10];
    char Answer;

    while (true) {
        printf("    ENTER GUN GRID (MAX 10 DIGITS, MIN 2 DIGITS): ");
        scanf("%s" &Grid);

        while (true) {
            printf("    CONFIRM GRID %s IS CORRECT (Y/N):", Grid);
            scanf("%c", &Answer);

            if (Answer = 'Y') {
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
        scanf("%ld" &Elevation);

        while (true) {
            printf("    CONFIRM ELEVATION %ld IS CORRECT (Y/N):", Elevation);
            scanf("%c", &Answer);

            if (Answer = 'Y') {
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
        scanf("%d" &Type);

        while (true) {
            printf("    CONFIRM GUN TYPE %d IS CORRECT (Y/N):", Type);
            scanf("%c", &Answer);

            if (Answer = 'Y') {
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
    
    MASTER.Gun[MASTER.GunCount] = (struct Gun) {x, y, Elevation, Type};

    MASTER.GunCount++;

    return 0;
}

int RemoveGun(void) {
    
    int GunID;
    char Answer;

    while (true) {
        while (true) {
            printf("    ENTER ID OF GUN BEING REMOVED: ");
            scanf("%d", &GunID);

            if (GunID < 1 || GunID > MASTER.GunCount) {
                printf("    ERROR: GUN NOT DEFINED\n\n")
            } else {
                break;
            }
        }

        printf("    CONFIRM REMOVE GUN %d (Y/N): ", GunID);
        scanf("%c", &Answer);

        if (Answer == 'Y') {
            break;
        } else if (Answer != 'N') {
            printf("    ERROR: ANSWER WAS NOT Y OR N!\n\n");
        }
    }

    if (GunID < MASTER.GunCount) {

        // Remove gun with specified ID, then move guns with a greater ID down 1 ID.
        // Ensures no blank spaces in the gun storage.

        MASTER.Gun[GunID - 1] = (struct Gun) {0, 0, 0, 0};

        for (int Gun = GunID; Gun < MASTER.GunCount; Gun++) {
            
            MASTER.Gun[Gun - 1] = MASTER.Gun[Gun];
        }

        MASTER.GunCount--;

    } else {

        // If the gun is at the end of the storage, then just remove it and continue.

        MASTER.Gun[GunID - 1] = (struct Gun) {0, 0, 0, 0};

        MASTER.GunCount--;
    }

    return 0;
}
