void AddTarget(void) {

    long int x, y, z;
    char Grid[10], Answer;

    while (true) {

        printf("    ENTER TARGET GRID (MAX 10 DIGITS, MIN 2 DIGITS): ");
        scanf("%10s", &Grid);
        printf("\n");

        clear();

        printf("    IS GRID %s CORRECT? (Y/N): ", &Grid);
        scanf("%1c", &Answer);
        printf("\n");

        if (Answer == 'Y') {
            break;
        } else if (Answer != 'N') {
            printf("    ERROR: ANSWER WAS NOT Y OR N!\n\n");
        }
    }

    GridToCoordinates(Grid, &x, &y);

    while (true) {
        printf("    ENTER TARGET ELEVATION (METERS): ");
        scanf("%ld", &z);
        printf("\n");

        clear();

        while (true) {
            printf("    CONFIRM ELEVATION %ld IS CORRECT? (Y/N): ", z);
            scanf("%1c", &Answer);
            printf("\n");

            clear();

            if (Answer == 'Y') {
                break;
            } else if (Answer != 'N') {
                printf("    ERROR: ASNWER WAS NOT Y OR N!\n\n");
            }
        }

        if (Answer == 'Y') {
            break;
        }
    }

    MASTER.Target[MASTER.TargetCount] = (struct Target) {'\0', x, y, z};
    strcpy(MASTER.Target[MASTER.TargetCount].Grid, Grid);
    MASTER.TargetCount++;
}
